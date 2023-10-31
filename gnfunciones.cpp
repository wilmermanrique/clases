#include <C_archiv.hpp>
#include <ctype.h>
#include <password.h>
#include "conecta.hpp"
#include "jsonUtils.h"
#include "lnxlmax.hpp"
#include "gnfunciones.h"
#include "conecta.hpp"
#include "gnlog.h"

int iSecModo = 0;
void soapError( struct soap *pSoap, char *cError );
int abrirConexion( C_ODBC *xOdbc, char *cIP,char *cBD ,char *cUsuario)
{
	int iRespuesta = E00001_ERROR_DEFAULT;
	char cMensaje[TAM_MAX_BUFF] = {0}, cClave[40] = {0};

	generarPasswordDB( cUsuario, cBD, cClave );

	if ( xOdbc->Open( "PostgreSQL", cIP, cUsuario, cClave, cBD ) )
	{
		iRespuesta = _OK_;
	}
	else
	{
		iRespuesta = E00001_ERROR_CONEXION_DB;
		xOdbc->GetLastError();
		mysnprintf( cMensaje,sizeof(cMensaje), "Error de conexion a IP:'%.15s' DB: %.30s ERROR: %.256s", cIP, cBD, xOdbc->LastErrStr() );
		logx( cMensaje , _LOGINFO_);
	}
	if ( iRespuesta == _OK_ )
	{
		//
	}

	return iRespuesta;
}

int abrirConexion2( C_ODBC *xOdbc, char *cIP,char *cBD ,char *cUsuario,char *cClave)
{
	int iRespuesta = E00001_ERROR_DEFAULT;
	char cMensaje[TAM_MAX_BUFF] = {0};

	//generarPasswordDB( cUsuario, cBD, cClave );
        

	if ( xOdbc->Open( "PostgreSQL", cIP, cUsuario, cClave, cBD ) == TRUE )
	{
		iRespuesta = _OK_;        
	}
	else
	{
		iRespuesta = E00001_ERROR_CONEXION_DB;
		xOdbc->GetLastError();
		mysnprintf( cMensaje,sizeof(cMensaje), "Error de conexion a IP:'%.15s' DB: %.20s %.30s", cIP, cBD, xOdbc->LastErrStr() );
		logx( cMensaje , _LOGINFO_);
	}
	
	return iRespuesta;
}

int abrirConexionCartera( C_ODBC *xOdbcCartera, char *cIpBDCartera,char *cBDCartera ,char *cUsuarioCartera)
{
	int iRespuesta = E00001_ERROR_DEFAULT;
	char cMensaje[TAM_MAX_BUFF] = {0}, cClaveCartera[40] = {0};	

    mysnprintf(cClaveCartera,sizeof(cClaveCartera),"%.32s","6fc8f75fd8047d07032686cfd1dca20f");    
	
	if  ( xOdbcCartera->Open("PostgreSQL", cIpBDCartera, cUsuarioCartera, cClaveCartera, cBDCartera ) == TRUE )
	{
		iRespuesta = _OK_;											
	}
	else
	{		
		iRespuesta = E00001_ERROR_CONEXION_DB;
		xOdbcCartera->GetLastError();
		mysnprintf( cMensaje,sizeof(cMensaje), "Error de conexion a IP:'%.15s' DB: %.20s %.30s", cIpBDCartera, cBDCartera, xOdbcCartera->LastErrStr() );
		logx( cMensaje , _LOGINFO_);		
	}	
	return iRespuesta;
}

int abrirConexionCorreos( C_ODBC *odbcCorreos, char *cIpBDCorreos,char *cBDCorreos ,char *cUsuarioCorreos)
{
	int iRespuesta = E00001_ERROR_DEFAULT;
	char cMensaje[TAM_MAX_BUFF] = {0}, cClaveCorreos[40] = {0};	

    mysnprintf(cClaveCorreos,sizeof(cClaveCorreos),"%.32s","b403c0846e9541820fd15b6694fbd7a4");    
	
	mysnprintf(cMensaje,sizeof(cMensaje),"cIpBDCorreos[%.20s],cBDCorreos[%.30s],cUsuarioCorreos[%.64s]",cIpBDCorreos,cBDCorreos,cUsuarioCorreos);
	
	if  ( odbcCorreos->Open("PostgreSQL", cIpBDCorreos, cUsuarioCorreos, cClaveCorreos, cBDCorreos ) == TRUE )
	{
		iRespuesta = _OK_;											
	}
	else
	{		
		iRespuesta = E00001_ERROR_CONEXION_DB;
		odbcCorreos->GetLastError();
		mysnprintf( cMensaje,sizeof(cMensaje), "Error de conexion a IP:'%.15s' DB: %.30s %.256s", cIpBDCorreos, cBDCorreos, odbcCorreos->LastErrStr() );
		logx( cMensaje, _LOGINFO_);		
	}	
	return iRespuesta;
}

void strtrim(char* str, int size) {
    int start = 0; // number of leading spaces
    char* buffer = str;
    while (*str && *str++ == ' ') ++start;
    while (*str++); // move to end of string
    int end = str - buffer - 1; 
    while (end > 0 && buffer[end - 1] == ' ') --end; // backup over trailing spaces
    if(end < size)
    {
        buffer[end] = 0; // remove trailing spaces
    }
    if (end <= start || start == 0) return; // exit if no leading spaces or string is now empty
    str = buffer + start;
    while ((*buffer++ = *str++));  // remove leading spaces: K&R
}

bool consultarParametro( C_ODBC *odbc, const char* cParametro, char *cValor)
{
	bool bRespuesta = false;
	char cSql[256] = {0}, cLog[256] = {0};

	CRegistro parametro( odbc, false );
	
	parametro.agregarCampoChar( "valor", 256 );
	
	mysnprintf( cSql,255, "SELECT TRIM(valor) FROM tdconfiguracion WHERE elemento = TRIM('%.256s');", cParametro );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			bRespuesta = true;
			mysnprintf( cValor,255, "%.256s", parametro.valorChar( "valor" ) );
		}
		else
		{
			mysnprintf( cLog,255, "No se encontro el parametro: '%.128s'", cParametro );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{	
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);		
	}

    return bRespuesta;
}

bool consultarDescripcion( C_ODBC *odbc, long lCodigo, int iTalla, char *cDescripcion, int iFormato, char *cSql)
{		
	bool bRespuesta = true;
	char cLog[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoChar("robuscardeptoclasfamequivalente", 40 );

	mysnprintf( cSql,100, "SELECT robuscardeptoclasfamequivalente FROM roBuscarDeptoClasFamEquivalente('%ld','%d');", lCodigo, iTalla);
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			mysnprintf( cDescripcion,40, "%.40s", parametro.valorChar( "robuscardeptoclasfamequivalente" ));
		}
		else
		{
			bRespuesta = false;

			mysnprintf( cLog,sizeof(cLog), "No se encontro el codigo: '%d'", lCodigo );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool realizarConsulta( C_ODBC *odbc, char *cSql, char *cNombreCampo, char *cValor)
{		
	bool bRespuesta = true;
	char cLog[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoChar( cNombreCampo, 32 );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		if( parametro.Leer() )
		{
			mysnprintf( cValor,32, "%.32s", parametro.valorChar( cNombreCampo ));
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog), "No se encontro el campo: '%.32s'", cNombreCampo );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

int consultarIpServidor( C_ODBC *odbc,char *cSql)
{	
	char cIpServidor [16] = {0};
	int Respuesta = 1;    
	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar("cIpServidor", 16 );

	mysprintf( cSql, "SELECT ipservidor FROM sysServidores WHERE tiposervidor = %d;",SERV_CREDITO  );
	if( parametro.Exec( cSql ) )
	{		
		parametro.activarCols();		
		if( parametro.Leer() )
		{		
			mysnprintf( cIpServidor,16, "%.16s", parametro.valorChar( "cIpServidor" ));
			logx( cIpServidor , _LOGINFO_);
		}
		else
		{
			Respuesta = 0;
		}
	}
	else
	{
		Respuesta = 0;
		logx( "error en la consulta" , _LOGINFO_);		
	}
	return Respuesta;
}

bool obtenerDatosEmpleado(C_ODBC *odbc, long lNumEmpleado,sDatosempleado *sEmpleado)
{
	bool bRespuesta = true;
	char cSql[256] = {0}, cLog[256] = {0};

	CRegistro hecatalogoempleados( odbc );
	
	hecatalogoempleados.agregarCampoChar( "nombre", 22 );
	hecatalogoempleados.agregarCampoChar( "apellidopaterno", 17 );
	hecatalogoempleados.agregarCampoChar( "apellidomaterno", 17 );
	hecatalogoempleados.agregarCampoEntero( "numeropuesto", DT_ENTERO_CORTO );
    hecatalogoempleados.agregarCampoEntero( "centro", DT_ENTERO );
	
	mysnprintf( cSql,255, "SELECT trim(nombre),TRIM(apellidopaterno),TRIM(apellidomaterno),numeropuesto,centro FROM hecatalogoempleados WHERE numemp = %ld Limit 1;", lNumEmpleado  );
	if( hecatalogoempleados.Exec( cSql ) )
	{
		hecatalogoempleados.activarCols();
		
		if( hecatalogoempleados.Leer() )
		{
			mysnprintf( sEmpleado->cNombre,32, "%.32s", hecatalogoempleados.valorChar( "nombre" ) );
			mysnprintf( sEmpleado->cApellidoPaterno,17, "%.17s", hecatalogoempleados.valorChar( "apellidopaterno" ) );
			mysnprintf( sEmpleado->cApellidoMaterno,17, "%.17s", hecatalogoempleados.valorChar( "apellidomaterno" ) );
			sEmpleado->iPermisos = hecatalogoempleados.valorShort( "numeropuesto" );
			sEmpleado->iCentro = hecatalogoempleados.valorShort( "centro" );

		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "ERROR AL OBTENER LOS DATOS DEL EMPLEADO : [%.150s]", hecatalogoempleados.error() );
			logx( cLog , _LOGINFO_);

			bRespuesta = false;
		}
	}
	else
	{
		bRespuesta = false;
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar hecatalogoempleados. [%.150s]", hecatalogoempleados.error() );
		logx( cLog , _LOGINFO_);		
	}

	return bRespuesta;
}

bool obtenerClaveEmpleado(C_ODBC *odbc, long lNumEmpleado,sDatosClaveempleado *sEmpleado)
{
	bool bRespuesta = true;
	char cSql[256] = {0}, cLog[256] = {0};

	CRegistro heclaveempleados( odbc );

	heclaveempleados.agregarCampoChar( "cClave", 17 );
	
	mysnprintf( cSql,sizeof(cSql), "SELECT trim(clave) as cClave FROM hetemplateempleado WHERE empleadoregistrado= %ld Limit 1;", lNumEmpleado  );
	if( heclaveempleados.Exec( cSql ) )
	{
		heclaveempleados.activarCols();

		if( heclaveempleados.leer() )
		{
			 mysnprintf( sEmpleado->cClaveEmpleado,sizeof(sEmpleado->cClaveEmpleado), "%.17s", heclaveempleados.valorChar( "cClave" ) );
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "ERROR AL OBTENER LOS DATOS CLAVE DEL EMPLEADO : [%.150s]", heclaveempleados.error() );
			logx( cLog , _LOGINFO_);
			bRespuesta = false;
		}
	}
	else
	{
		bRespuesta = false;
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar hecatalogoempleados. [%.150s]", heclaveempleados.error() );
		logx( cLog , _LOGINFO_);		
	}

	return bRespuesta;
}

bool obtenerDatosConexionBD( int iControl, char *cPwd, char *cUsr, char *cBd, long numTienda)
{
	bool bRegresa = true;
	char cBdPwd[25] = {0};

	switch ( iControl )
    {
        case CONECTA_TIENDANUMERO:
            mysnprintf( cBd,30, "tienda.%04ld", numTienda );
            mysnprintf( cBdPwd,25, "tienda.%04ld", numTienda );
            mysnprintf( cUsr,30, "systienda%04ld", numTienda );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_GLOBALTIENDAS:
            mysnprintf( cBd,30,"%s", "globaltiendas" );
            mysnprintf( cBdPwd,25,"%s", "globaltiendas" );
            mysnprintf( cUsr,30,"%s", "sysglobaltiendas" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_GLOBALBODEGAM:
            mysnprintf( cBd,30,"%s", "globalbodegam" );
            mysnprintf( cBdPwd,25,"%s", "globalbodegam" );
            mysnprintf( cUsr,30,"%s", "sysbodegam" );
            break;
        case CONECTA_TIENDASMUEBLESTX:
            mysnprintf( cBd,30, "tiendasMueblesTX.%05ld", numTienda );
            mysnprintf( cBdPwd,25,"%s", "tiendasMueblesTX" );
            mysnprintf( cUsr,30,"%s", "systiendasmueblestx" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CARTERA:
            mysnprintf( cBd,30,"%s", "cartera" );
            mysnprintf( cBdPwd,25,"%s", "cartera" );
            mysnprintf( cUsr,30,"%s", "systiendacartera" );
            break;
        case CONECTA_ENVIOSDEDINERO:
            mysnprintf( cBd,30,"%s", "enviosdinero" );
            mysnprintf( cBdPwd,25,"%s", "enviosdinero" );
            mysnprintf( cUsr,25,"%s", "systiendaenviosdinero" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_SOLICITUDES:
            mysnprintf( cBd,30,"%s", "solicitudes" );
            mysnprintf( cBdPwd,25,"%s", "solicitudes" );
            mysnprintf( cUsr,25,"%s", "systiendasolicitudes" );
            break;
        case CONECTA_TIENDA:
            mysnprintf( cBd,30,"%s", "tienda" );
            mysnprintf( cBdPwd,25,"%s", "tienda" );
            mysnprintf( cUsr,30,"%s", "systienda" );
            break;
        case CONECTA_HUELLASCLIENTE:
            mysnprintf( cBd,30,"%s", "huellascte" );
            mysnprintf( cBdPwd,25,"%s", "huellascte" );
            mysnprintf( cUsr,30,"%s", "systiendahuellascte" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_HUELLASEMPLEADOS:
            mysnprintf( cBd,30,"%s", "huellasemps" );
            mysnprintf( cBdPwd,25,"%s", "huellasemps" );
            mysnprintf( cUsr,30,"%s", "syshuellasemps" );
            break;
        case CONECTA_PERSONAL:
            mysnprintf( cBd,30,"%s", "personal" );
            mysnprintf( cBdPwd,25,"%s", "personal" );
            mysnprintf( cUsr,30,"%s", "syspersonal" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_TRAMITES:
            mysnprintf( cBd,30,"%s", "tramites" );
            mysnprintf( cBdPwd,25,"%s", "tramites" );
            mysnprintf( cUsr,30,"%s", "systiendatramites" );
            break;
        case CONECTA_APARTADO:
            mysnprintf( cBd,30, "apartado.0%04ld", numTienda );
            mysnprintf( cBdPwd,25,"%s", "apartado.00000" );
            mysnprintf( cUsr,30,"%s", "sysbodegaapartado" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_TIENDASMUEBLESRX:
            mysnprintf( cBd,30, "tiendasMueblesRX.%05ld", numTienda );
            mysnprintf( cBdPwd,25,"%s", "tiendasMueblesRX" );
            mysnprintf( cUsr,30,"%s", "systiendasmueblesrx" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_RD100NUMERO:
            mysnprintf( cBd,30, "rd100.%04ld", numTienda );
            mysnprintf( cBdPwd,24, "rd100.%04ld", numTienda );
            mysnprintf( cUsr,30, "sysrd100%04ld", numTienda );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_SORTEOCINE:
            mysnprintf( cBd,30,"%s", "sorteocine" );
            mysnprintf( cBdPwd,25,"%s", "sorteocine" );
            mysnprintf( cUsr,30,"%s", "syssorteocine" );
            mysnprintf( cPwd,30,"%s", "d07032686cfd" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_PROGCCAJAS:
            mysnprintf( cBd,30,"%s", "progccajas" );
            mysnprintf( cBdPwd,25,"%s", "progccajas" );
            mysnprintf( cUsr,30,"%s", "systiendaprogc" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CREDITO:
            mysnprintf( cBd,30,"%s", "credito" );
            mysnprintf( cBdPwd,25,"%s", "credito" );
            mysnprintf( cUsr,30,"%s", "systiendacredito" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CUENTASPERDIDAS:
            mysnprintf( cBd,30,"%s", "ctasperdidas" );
            mysnprintf( cBdPwd,25,"%s", "ctasperdidas" );
            mysnprintf( cUsr,30,"%s", "systiendactasperdidas" );
            break;
       /* case CONECTA_PROGC:
            mysnprintf( cBd,30,"%s", "progc" );
            mysnprintf( cBdPwd,25,"%s", "progc" );
            mysnprintf( cUsr,30,"%s", "sysprogc" );
            mysnprintf( cPwd,40,"%s", "6d39699d6d1fd26ce917c002fe723378" );
            break;*/ //Se comenta por vulnerabilidad y no se utiliza
        /*case CONECTA_INFORME:
            mysnprintf( cBd,30,"%s", "Informe" );
            mysnprintf( cBdPwd,25,"%s", "Informe" );
            mysnprintf( cUsr,30,"%s", "systiendas" );
            mysnprintf( cPwd,40,"%s", "dfb8cce651618e9efd876645d7c2fe95" );
            break; *///Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_AFOREGLOBAL:
            mysnprintf( cBd,30,"%s", "aforeglobal" );
            mysnprintf( cBdPwd,25,"%s", "aforeglobal" );
            mysnprintf( cUsr,30,"%s", "sysaforeglobal" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_SALDOSYPENDIENTES:
            mysnprintf( cBd,30,"%s", "consultadesaldos" );
            mysnprintf( cBdPwd,25,"%s", "consultadesaldos" );
            mysnprintf( cUsr,30,"%s", "Tiendas" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_FACTURA_FISCAL:
            mysnprintf( cBd,30,"%s", "facturafiscal" );
            mysnprintf( cBdPwd,25,"%s", "facturafiscal" );
            mysnprintf( cUsr,30,"%s", "sysfactura" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_FRAUDES:
            mysnprintf( cBd,30,"%s", "fraudes" );
            mysnprintf( cBdPwd,25,"%s", "fraudes" );
            mysnprintf( cUsr,30,"%s", "sysfacturacionantifraudes" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_BODEGAMUEBLES:
            mysnprintf( cBd,30, "bodegamuebles.%05ld", numTienda );
            mysnprintf( cBdPwd,25,"%s", "bodegamuebles" );
            mysnprintf( cUsr,30,"%s", "sysprogsbm" );
            break; //Se comenta por vulnerabilidad y no se utiliza
       /* case CONECTA_COMCLN:
            mysnprintf( cBd,30,"%s", "cajas" );
            mysnprintf( cBdPwd,25,"%s", "cajas" );
            mysnprintf( cUsr,30,"%s", "sysmesaayuda" );
            mysnprintf( cPwd,40,"%s", "mesaayuda" );
            break; *///Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_SYSSISTEMAS:
            mysnprintf( cBd,30,"%s", "sistemas" );
            mysnprintf( cBdPwd,25,"%s", "utilerias2007" );
            mysnprintf( cUsr,30,"%s", "syssistemas" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_BODEGA_ROPA:
            mysnprintf( cBd,30,"%s", "bodega" );
            mysnprintf( cBdPwd,25,"%s", "bodega" );
            mysnprintf( cUsr,30,"%s", "sysprogsropa" );
            break; //Se comenta por vulnerabilidad y no se utiliza
       /* case CONECTA_CAMBIOSTDA:
            mysnprintf( cBd,30,"%s", "peticionescmmi" );
            mysnprintf( cBdPwd,25,"%s", "peticionescmmi" );
            mysnprintf( cUsr,30,"%s", "syscmmi" );
            mysnprintf( cPwd,40,"%s", "7c6e6c2b6c9b0eaa5e0fa153e0dec1d1" );
            break;*/ //Se comenta por vulnerabilidad y no se utiliza
        /*case CONECTA_CORREO_MICRO:
            mysnprintf( cBd,30,"%s", "correomicro" );
            mysnprintf( cBdPwd,25,"%s", "correomicro" );
            mysnprintf( cUsr,30,"%s", "syscorreomicroprog" );
            mysnprintf( cPwd,40,"%s", "79be633888cc5cea152081bd4432ec7d" );
            break; *///Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CENTRAL_R:
            mysnprintf( cBd,30,"%s", "ropa" );
            mysnprintf( cBdPwd,25,"%s", "ropa" );
            mysnprintf( cUsr,30,"%s", "sysropa" );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CENTRAL_M:
            mysnprintf( cBd,30,"%s", "muebles" );
            mysnprintf( cBdPwd,25,"%s", "muebles" );
            mysnprintf( cUsr,30,"%s", "sysmuebles" );
			mysprintf( cPwd,"%s", "f3e335eee34db77cdbf6bd8d1ceb33fa" );
            //obtener(cPwd,CONECTA_CENTRAL_M);
            break;
        case CONECTA_CORREOS:
            mysnprintf( cBd,30,"%s", "correos" );
            mysnprintf( cBdPwd,25,"%s", "correos" );
            mysnprintf( cUsr,30,"%s", "systienda" );
			mysprintf( cPwd,"%s", "b403c0846e9541820fd15b6694fbd7a4" );
            //obtener(cPwd,CONECTA_CORREOS);
            break;
        /* CONECTA_SORTEO:
            mysnprintf( cBd,30,"%s", "sorteonavidad" );
            mysnprintf( cBdPwd,25,"%s", "sorteonavidad" );
            mysnprintf( cUsr,30,"%s", "sysprogs" );
            mysnprintf( cPwd,40,"%s", "f44909bdff601cba99be25f52a142502" );
            break;*/ //Se comenta por vulnerabilidad y no se utiliza
        case CONECTA_CONVENIOS:
            mysnprintf( cBd,30,"%s", "conveniosexternos" );
            mysnprintf( cBdPwd,25,"%s", "conveniosexternos" );
            mysnprintf( cUsr,30,"%s", "systienda" );
           // mysnprintf( cPwd,40,"%s", PWD_CONECTA__CONVENIOS );
            break; //Se comenta por vulnerabilidad y no se utiliza
        case 41: //este es el CONECTA_POSGATEWAY
            mysnprintf( cBd,30, "posgateway%04ld", numTienda );
            mysnprintf( cBdPwd,25, "posgateway%04ld", numTienda );
            mysnprintf( cUsr,30,"%s", "syshasar" );
			mysprintf( cPwd,"%s", "zdaQKO1ntZlj1pMG7DWfSSQKEYpBndNI" );
            bRegresa = false;                                   
            break;            
        default:
            bRegresa = false;
            break;
    }
	
	if ( bRegresa && numTienda != -1 )
	{
		generarPasswordDB( cUsr, cBdPwd, cPwd );
	}

	return bRegresa;
}

int consultarIpServidor( C_ODBC *odbc, short iTipoServidor , char *cIpServidor)
{
    int iRespuesta = 0;
	char cSql[256] = {0}, cLog[256] = {0};
	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar( "ipservidor", 256 );
	
	mysnprintf( cSql,sizeof(cSql), "SELECT TRIM(ipservidor) FROM sysServidores WHERE tiposervidor = %hd", iTipoServidor );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
            iRespuesta = _OK_;
			mysnprintf( cIpServidor,16, "%.32s", parametro.valorChar( "ipservidor" ) );
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "No se encontro el parametro: '%d'", iTipoServidor );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar IP. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);		
	}
    
    return iRespuesta;
}

bool consultarIpServidorggnml( C_ODBC *odbc, short iTipoServidor , char *cIpServidor)
{
	char cSql[256] = {0}, cLog[256] = {0};
    bool bResultado = false;

	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar( "ipservidor", 256 );
	
	mysnprintf( cSql,sizeof(cSql), "SELECT TRIM(ipservidor) FROM sysServidores WHERE tiposervidor = %hd", iTipoServidor );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			mysnprintf( cIpServidor,16, "%.32s", parametro.valorChar( "ipservidor" ) );
            bResultado = true;
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "No se encontro el parametro: '%d'", iTipoServidor );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);		
	}
    
    return bResultado;
}

bool crearTablaTemporal(C_ODBC *odbcDBTiendaNumero,int *iCaja,int *iSysNotaCobro, long lNumOrdenNUBE)
{
	 char cFlagNota[7] = {0}, cSql[256] = {0},mensajeError[256] = {0};
	 bool bContinuar = true;	 	

	if( *iSysNotaCobro == SYS_NOTA )
	{
		mysnprintf( cFlagNota,sizeof(cFlagNota),"%s", "TRUE" );
	}
	else
	{
		mysnprintf( cFlagNota,sizeof(cFlagNota),"%s", "FALSE" );		
	}

	CRegistro tablaTemp( odbcDBTiendaNumero );

	mysnprintf( cSql,sizeof(cSql), "SELECT rocreartemporalesnotaUn( '%.7s',%d, %ld )", cFlagNota,*iCaja, lNumOrdenNUBE );

	if( tablaTemp.Exec( cSql ) == FALSE)
	{		
		mysnprintf(mensajeError,sizeof(mensajeError),"%s", "Error en consultar " );			
		logx( mensajeError, _LOGINFO_);
		bContinuar = false;		
	}
	else
	{
		mysnprintf( mensajeError,sizeof(mensajeError),"%s", "Se Crearon Tablas Correctamente");			
		logx( mensajeError, _LOGINFO_);
	}	

	return bContinuar;
}

bool limpiarTabla( C_ODBC *odbcDBTiendaNumero,sSolicitudServicio *sSolicitud,int *iSysNotaCobro,int *iCaja )
{	
	char cSql[64] = {0},cMensaje[257] = {0};
	bool bContinuar = true;
	mysnprintf( cSql,sizeof(cSql), "SELECT roLimpiarTablasNotaVentasUn(%d,%d,%ld)",*iSysNotaCobro,*iCaja, sSolicitud->lNumOrdenNUBE );
	CRegistro limpiar(odbcDBTiendaNumero);
	if (limpiar.Exec(cSql) == FALSE)
	{
		crearTablaTemporal(odbcDBTiendaNumero, iCaja, iSysNotaCobro, sSolicitud->lNumOrdenNUBE);
	}
	else
	{
		bContinuar = false;
		mysnprintf(cMensaje,25,"%s", "Error en limpiarTabla()");
		logx( cMensaje, _LOGINFO_);
	}

	return bContinuar;
}

bool consultarFlag( C_ODBC *odbc, int iFlag, int iFlagDescripcion, int * iRespuesta)
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};
	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("gnConsultarFlag",DT_ENTERO);

	mysnprintf( cSql,sizeof(cSql), "select gnConsultarFlag from gnConsultarFlag ('%d','%d');", iFlag, iFlagDescripcion);
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "gnConsultarFlag" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar gnConsultarFlag : '");	
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarFlagSysflags( C_ODBC *odbc, int iFlag, char cArea, int * iRespuesta)
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc, false );
	parametro.agregarCampoEntero("flag",DT_ENTERO);

	mysnprintf( cSql,sizeof(cSql), "select flag from sysflags where tipoflag = '%ld' and area = '%c';", iFlag, cArea);
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "flag" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar sysflags : '");	
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarFlagPinPad( C_ODBC *odbc, int iCaja,int iCajaOriginal, char * cArea,int iSistema, int * iRespuesta)
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("flagPinPad",DT_ENTERO);

	
	if(iSistema == 0 )
	{
		mysnprintf( cSql,255, "SELECT flagPinPad FROM sysMicros WHERE area = '%.1s' AND caja = '%d';", cArea, iCaja );
	}
	else
	{
		switch( iSistema )
		{
			case 1: 
				mysnprintf( cSql,255, "SELECT flagPinPad FROM sysMicros WHERE area = 'M' AND caja = '%d';", iCaja );
				break;
			case 2: 
				mysnprintf( cSql,255, "SELECT flagPinPad FROM sysMicros WHERE area = 'R' AND caja = '%d';", iCaja );
				break;
			default:
				break;
		}
	}
	
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "flagPinPad" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar sysMicros : '");	
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarParidadDolar( C_ODBC *odbc, int * iRespuesta)
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("paridad",DT_ENTERO);

	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT paridad FROM gndominio");

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "paridad" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar la paridad de la gndominio : '");	
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarIpServidores( C_ODBC *odbc, char * cRespuesta, int iTipoServidor)
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar("ipservidor",20);
    
	mysnprintf( cSql,sizeof(cSql), "SELECT TRIM(ipservidor) FROM sysservidores where tiposervidor = %d", iTipoServidor);

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			mysnprintf( cRespuesta,16, "%.20s", parametro.valorChar( "ipservidor" ));
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar ipservidor de la sysservidres : ''"  );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarFlag(C_ODBC *xOdbc, char cArea, int iTipoFlag, short *iValorFlag)
{
    int iValorFlagTmp = 0;
    bool bRespuesta = false;

    bRespuesta = consultarFlagJC(xOdbc, cArea, iTipoFlag, &iValorFlagTmp);
    *iValorFlag = (short int)iValorFlagTmp;

    return bRespuesta;
}

bool consultarFlagJC(C_ODBC *xOdbc, char cArea, int iTipoFlag, int *iValorFlag)
{
    bool bContinuar = false;
    char cSql[256] ={0};
	char cLog[1024] = {0};

    CRegistro sysFlags( xOdbc );
    sysFlags.agregarCampoEntero( "gnconsultarflag", DT_ENTERO_CORTO );

    mysnprintf(cSql,sizeof(cSql),"SELECT gnConsultarFlag ('%c','%d') ",cArea,iTipoFlag);
    if( sysFlags.Exec( cSql ) )
	{
		sysFlags.activarCols();
		
		if( sysFlags.Leer() )
		{
            *iValorFlag =sysFlags.valorShort( "gnconsultarflag");
            bContinuar = true;
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "Error al consultar el flag '%d' en la tabla sysflags", iTipoFlag );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar el flag. [%.150s]", sysFlags.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bContinuar;
}

long incrementarFolio( int iFlagIncremento, char *cArea, int iCaja, int iTipoFolio, C_ODBC *xodbc, bool &bConsulta)
{
	long lFolio = 0L;
    char cSqlTxt[128] = {0}, cLog[512]={0};

	bConsulta = true;

    mysnprintf( cSqlTxt,sizeof(cSqlTxt), "SELECT gnincrementarfolio( '%.3s', '%d', '%d', '%d' )", cArea, iCaja, iTipoFolio, iFlagIncremento );

    CRegistro obtenerFolio( xodbc, false );

    obtenerFolio.agregarCampoEntero("gnincrementarfolio",DT_ENTERO);

	if ( obtenerFolio.Exec( cSqlTxt ) )
	{
		obtenerFolio.activarCols();
		if ( obtenerFolio.Leer() )
		{
            lFolio = obtenerFolio.valorLong("gnincrementarfolio");
		}
	}
	else
	{
        mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", obtenerFolio.error() );
		logx( cLog , _LOGINFO_);	
		bConsulta = false;
	}

	return lFolio;
}

bool crearTemporalesTiendaRopa( C_ODBC *odbcTiendaNumero, int iCaja, long lNumOrdenNUBE)
{
    char cLog[512] = {0}, cSql[512] = {0};
    bool bFlagIniciar = false;

	mysnprintf( cSql,sizeof(cSql), "SELECT  rocreartemporalesnotaUn('true','%d', %ld);", iCaja, lNumOrdenNUBE );

    CRegistro tdTemporales( odbcTiendaNumero );

	if( tdTemporales.Exec( cSql ) )
	{
		tdTemporales.activarCols();

		if( tdTemporales.Leer() )
		{
            bFlagIniciar = true;
		}else
		{
			mysnprintf( cLog,sizeof(cLog), "NO SE LOGRO CREAR LAS TABLAS TEMPORALES PARA LA CAJA : '%d'",iCaja );
			logx( cLog , _LOGINFO_);
		}
	}	
	else
	{
		mysnprintf( cLog,sizeof(cLog), "ERROR AL CREAR LAS TABLAS TEMPORALES PARA LA CAJA : '%d' ERROR=> [%.150s]",iCaja, tdTemporales.error() );
		logx( cLog , _LOGINFO_);			
	}

	return bFlagIniciar;
}

bool BorrarTablasTemporalesNube( C_ODBC *odbcTiendaNumero, int iCaja, long lNumOrdenNUBE)
{
    char cLog[512] = {0}, cSql[512] = {0};
    bool bFlagIniciar = false;

	mysnprintf( cSql,sizeof(cSql), "SELECT  gnBorrarTablasTmp('%d', %ld);", iCaja, lNumOrdenNUBE );
    CRegistro tdTemporales( odbcTiendaNumero );

	if( tdTemporales.Exec( cSql ) )
	{
		tdTemporales.activarCols();

		if( tdTemporales.Leer() )
		{
            bFlagIniciar = true;
		}else
		{
			mysnprintf( cLog,sizeof(cLog), "NO SE LOGRO BORRAR LAS TABLAS TEMPORALES PARA LA CAJA : '%d'",iCaja );
			logx( cLog , _LOGINFO_);
		}
	}	
	else
	{
		mysnprintf( cLog,sizeof(cLog), "ERROR AL BORRAR LAS TABLAS TEMPORALES PARA LA CAJA : '%d' ERROR=> [%.150s]",iCaja, tdTemporales.error() );
		logx( cLog , _LOGINFO_);			
	}

	return bFlagIniciar;
}

int esEmpleado( long lCliente )
{    
	int iFlag=0;
    if ( lCliente>=90000000L && lCliente<100000000L )    
	{        
		iFlag=1;    
	}    
	
	return iFlag;
}

void generarVentaCaida(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{		
	char cLog[256] = {0}, cSql[2048] = {0};
	int iRespuesta = 0;

		CRegistro parametro( odbcTiendaNumero );
		parametro.agregarCampoEntero("actualizarVentaCaida",DT_ENTERO);
		
		if( sSolicitud->VentaCaida.iFlagVentaCaida == 1 && sSolicitud->VentaCaida.iClienteEspecial == 0 )
		{
			switch( sSolicitud->VentaCaida.iFlagAccion )
			{
				case 1:
					sSolicitud->VentaCaida.iClaveCausa = 12;
					break;
				case 2:
					sSolicitud->VentaCaida.iClaveCausa = 3;
					break;
				case 3:
					sSolicitud->VentaCaida.iClaveCausa = 6;
					break;
				case 4:
					sSolicitud->VentaCaida.iClaveCausa = 1;
					break;
				case 5:
					sSolicitud->VentaCaida.iClaveCausa = 2;
					break;
				case 6:
					sSolicitud->VentaCaida.iClaveCausa = 7;
					break;
				case 7:
					sSolicitud->VentaCaida.iClaveCausa = 3;
					break;
				case 8:
					sSolicitud->VentaCaida.iClaveCausa = 9;
					break;
				case 10:
					sSolicitud->VentaCaida.iClaveCausa = 13;
					break;
				case 11:
					sSolicitud->VentaCaida.iClaveCausa = 5;
					break;
				case 12:
					sSolicitud->VentaCaida.iClaveCausa = 14;
					break;
				case 14:
					sSolicitud->VentaCaida.iClaveCausa = 11;
					break;
				case 15:
					sSolicitud->VentaCaida.iClaveCausa = 10;
					break;
				case 16:
					sSolicitud->VentaCaida.iClaveCausa = 4;
					break;
				case 17:
					sSolicitud->VentaCaida.iClaveCausa = 8;
				break;

				default:
					break;
			}

			mysnprintf( cSql,sizeof(cSql), "SELECT actualizarVentaCaida FROM actualizarVentaCaida('%d', '%d', '%d', %ld, %ld, %ld, '%d', %ld, %ld, %ld, %ld, '%c', '%d', '%c', %ld, '%c', '0', '%.16s', %ld, '%.80s', '%d', '%d', '%.20s', '%.20s', '%.20s', '%.20s', '%d', %ld, %ld, %ld, %ld)", sSolicitud->VentaCaida.iCaja, sSolicitud->VentaCaida.iArea, sSolicitud->VentaCaida.iTienda, sSolicitud->VentaCaida.lCliente, sSolicitud->VentaCaida.lEmpleado,
				sSolicitud->VentaCaida.lFolio, sSolicitud->VentaCaida.iClaveCausa, sSolicitud->VentaCaida.lPagoInicial, sSolicitud->VentaCaida.lPagoInicialCte, sSolicitud->VentaCaida.lPagoInicialCred, sSolicitud->VentaCaida.lSaldoCte, sSolicitud->VentaCaida.cSitEspecial, sSolicitud->VentaCaida.iCausaSitEsp, sSolicitud->VentaCaida.cPuntualidad, sSolicitud->VentaCaida.lVencido, sSolicitud->VentaCaida.cHuellaInvalida, sSolicitud->VentaCaida.cBancoTarjeta, sSolicitud->VentaCaida.lFolioTramite, sSolicitud->VentaCaida.cCondicionTramite, sSolicitud->VentaCaida.iRespuestaCred,
				sSolicitud->VentaCaida.iRespuestaCred2, sSolicitud->VentaCaida.cFechaIniciaVenta, sSolicitud->VentaCaida.cFechaTerminaVenta, sSolicitud->VentaCaida.cFechaIniciaTramite, sSolicitud->VentaCaida.cFechaTerminaTramite, sSolicitud->VentaCaida.iFlagAccion, sSolicitud->VentaCaida.lPuntajeFinalParam, sSolicitud->VentaCaida.lPorConsumoLinea, sSolicitud->VentaCaida.lImporteVenta, sSolicitud->VentaCaida.lFolioFactura);
		
			if( parametro.Exec( cSql ) )
			{
				parametro.activarCols();
				
				if( parametro.Leer() )
				{
					iRespuesta = parametro.valorLong( "actualizarVentaCaida" );
					if(iRespuesta == 1){
						sRespuesta->status = _MENSAJE_CORRECTO_;
					}
					else{
						mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL ACTUALIZARVENTACAIDA");
						mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");
						sRespuesta->status = _ERROR_EN_MENSAJE;
						sRespuesta->iDevStatus = E00001_ERROR_QUERY;
						mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
						logx( cLog , _LOGINFO_);
					}
				}
				else
				{
					mysnprintf( cLog,sizeof(cLog), "%s","Error al consultar sysflags : '"  );
					logx( cLog , _LOGINFO_);
				}
			}
			else
			{
				mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", parametro.error() );
				logx( cLog , _LOGINFO_);	
			}
		}
	/*}
	else{
		mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL ABRIR CONEXION");
		mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");
		sRespuesta->status = _ERROR_EN_MENSAJE;
		sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
		logx( "ERROR AL ABRIR CONEXION", _LOGINFO_);
	}*/
}

int obtenerTipoClienteLCC(C_ODBC *odbcCartera,sRespuestaServicio *sRespuesta,long *lCliente)
{
	logx( "entro a obtenerTipoClienteLCC()", _LOGINFO_);
	char cSql[255] = {0};
	char cMensaje[TAM_MAX_BUFF];
	mysnprintf( cSql,sizeof(cSql), "SELECT tipoorigencliente FROM crcliente WHERE cliente = %ld", *lCliente );
	////logx( csql, _LOGINFO_);
	
	CRegistro tpCliente( odbcCartera);
	tpCliente.agregarCampoEntero( "tipoorigencliente", DT_ENTERO_LARGO);  
	if( tpCliente.Exec( cSql ) )
	{
		tpCliente.activarCols();
		if( tpCliente.leer() )
		{			        	
			return tpCliente.valorLong( "tipoorigencliente" );
		}
	}
	else
	{
		mysnprintf(cMensaje,sizeof(cMensaje),"%s","ClienteLCC, obtenerTipoClienteLCC, Consultar tipo de origen del cliente LCC ");    
        logx( cMensaje, _LOGINFO_);							
		return -1;
	}
	return NULL;
}

void obtenerDatosClienteLCCRopa(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera,sRespuestaServicio *sRespuesta,int *iFlagDescuentoEspecial,int *iFlagClienteNunca,long *lCliente)
{
 	char cSql[255] = {0};
	 char cMensaje[TAM_MAX_BUFF];	
	 int iTipoCteLCC = 0;
 	if (*iFlagDescuentoEspecial!= 1 && *iFlagDescuentoEspecial != 2 && *iFlagClienteNunca == 0 && *lCliente!= 90001)
	{
		//Obtener Tipo Origen Cliente.
		iTipoCteLCC = obtenerTipoClienteLCC(odbcCartera,sRespuesta,lCliente);
		sRespuesta->sObtenerDatosClienteLCCRopa.iTipoCteLCC = iTipoCteLCC;
		 
		mysnprintf( cSql,sizeof(cSql), "SELECT flagcreditolcc, flaglccobligado, descuentolcc, msgdescuentolcc FROM tdIdentificaCteLCC ('%d') ", iTipoCteLCC );
		
		 CRegistro datosClienteLCC( odbcTiendaNumero );
		 datosClienteLCC.agregarCampoEntero( "flagcreditolcc", DT_ENTERO_CORTO);  
		 datosClienteLCC.agregarCampoEntero( "flaglccobligado", DT_ENTERO_CORTO);  
		 datosClienteLCC.agregarCampoEntero( "descuentolcc", DT_ENTERO_CORTO);  
		 datosClienteLCC.agregarCampoChar( "msgdescuentolcc", 52);		   
		if( datosClienteLCC.Exec( cSql ) )
		{
			datosClienteLCC.activarCols();
			if( datosClienteLCC.leer() )
			{
				if (datosClienteLCC.valorShort( "descuentolcc" ) > 0)
				{	
				    sRespuesta->sObtenerDatosClienteLCCRopa.flagcreditolcc = datosClienteLCC.valorShort( "flagcreditolcc" );
					sRespuesta->sObtenerDatosClienteLCCRopa.flaglccobligado = datosClienteLCC.valorShort( "flaglccobligado" );													
					sRespuesta->sObtenerDatosClienteLCCRopa.descuentolcc = datosClienteLCC.valorShort( "descuentolcc" );					
					mysnprintf(sRespuesta->sObtenerDatosClienteLCCRopa.msgdescuentolcc,52,"%s",datosClienteLCC.valorChar( "msgdescuentolcc" ));
					//DESACTIVAR Línea de Crédito Especial.
					sRespuesta->sObtenerDatosClienteLCCRopa.iFlagLineaCreditoEsp = 0;										
				}
			}
		}
		else
		{
			mysnprintf(cMensaje,sizeof(cMensaje),"%s","ClienteLCC, obtenerDatosClienteLCCRopa, Consultar los datos del cliente LCC ");    
        	logx( cMensaje, _LOGINFO_);		
			mysnprintf(sRespuesta->cMensaje,255,"%.255s",cMensaje);			
		}
	}
}
void grabarAutorizacionGerentes( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char cTipo, long lFolio, long lEmpleado,	 char *cIdentificacion, int iSistema, int iClave, bool &bContinuar, long lEmpleado2)
{
	int iConexion = 0;
	char cTablaTmp[50] = {0}, cSql[TAM_MIN_BUFF] = {0}, cLog[256] = {0};

	iConexion = crearTmp( "tdAutorizacionHuellas", bContinuar, odbcTiendaNumero, sRespuesta ); //conexión a tienda.nnnn

	if ( bContinuar && iConexion == -1 )
	{
		mysnprintf( cLog,sizeof(cSql),"%s" ,"Error #1331" );
		logx( cLog, _LOGINFO_);
		bContinuar = false;
	}

	if ( bContinuar )
	{
		mysnprintf( cTablaTmp,sizeof(cTablaTmp), "tmptdAutorizacionHuellas%d", iConexion );

		mysnprintf( cSql,sizeof(cSql), "SELECT tdAutorizacionHuellas02 FROM tdAutorizacionHuellas02( '%.50s', '%d', '%d', '%c', %ld, %ld, '%.20s', %ld, %ld );",
						cTablaTmp, iSistema, iClave, cTipo, sSolicitud->lCliente, lEmpleado, cIdentificacion, 
						lFolio, lEmpleado2 );

		CRegistro tdAutorizacionHuellas( odbcTiendaNumero );

		if ( !tdAutorizacionHuellas.Exec( cSql ) )
		{
			mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL ACTUALIZARVENTACAIDA");
			mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");
			sRespuesta->status = _ERROR_EN_MENSAJE;
			sRespuesta->iDevStatus = E00001_ERROR_QUERY;
			mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", tdAutorizacionHuellas.error() );
			bContinuar = false;
		}
	}
}
int crearTmp( char *cNombreTablaOrigen, bool &bContinuar, C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta)
{
	char cSql[64] = {0}, cLog[128] = {0};
	int iPID = 0;

	bContinuar = true;

	mysnprintf( cSql,sizeof(cSql), "SELECT gncreartablatmp('%.32s')", cNombreTablaOrigen );

	CRegistro crearTmpSQL( odbcTiendaNumero );
	crearTmpSQL.agregarCampoEntero( "pid", DT_ENTERO_CORTO);  

	if( crearTmpSQL.Exec( cSql ) )
	{
		crearTmpSQL.activarCols();
		if( crearTmpSQL.Leer() )
		{
			iPID = crearTmpSQL.valorShort("pid");
		}
	}
	else
	{
		mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL ACTUALIZARVENTACAIDA");
		mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");
		sRespuesta->status = _ERROR_EN_MENSAJE;
		sRespuesta->iDevStatus = E00001_ERROR_QUERY;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar parametro. [%.150s]", crearTmpSQL.error() );
		bContinuar = false;
	}

	return iPID;
}
bool crearTablatemporalMuebles(C_ODBC *odbcTiendaNumero, int *iCaja, long *lNumOrdenNUBE)
 {
	 logx( "Inicia crearTablatemporalMuebles()", _LOGINFO_);
	 	
	 char cSql[256] = {0},mensajeError[256] = {0};
	 bool bContinuar = true;	 	
	
	CRegistro CrearTablaTemporalMuebles( odbcTiendaNumero );

	mysnprintf( cSql,sizeof(cSql), "SELECT mucreartemporalesfacturaVentaUn( %d, %ld )", *iCaja, *lNumOrdenNUBE );
	////logx( csql, _LOGINFO_);

	if( CrearTablaTemporalMuebles.Exec( cSql ) == FALSE)
	{		
		mysnprintf(mensajeError,sizeof(mensajeError),"%s", "Error en ejecutar consulta "  );			
		logx( mensajeError, _LOGINFO_);
		bContinuar = false;		
	}
	else
	{
		mysnprintf( mensajeError,sizeof(mensajeError),"%s", "Se Crearon TablasMuebles Correctamente");			
		logx( mensajeError, _LOGINFO_);
	}	

	logx("Termina crearTablaTemporalMuebles()", _LOGINFO_);	
	return bContinuar;
 }
 bool obtenerValorConfiguracion( C_ODBC *odbcTiendaNumero, char *cValor, char *cElemento, char *cSql)
{
	bool bRegresa = false;

	mysnprintf( cSql,255, "SELECT valor FROM tdConfiguracion WHERE elemento = '%.30s'", cElemento );
    ////logx( csql, _LOGINFO_);

	CRegistro obtenerDatos( odbcTiendaNumero );
	 obtenerDatos.agregarCampoChar( "valor", 255);	

	if ( obtenerDatos.Exec( cSql ) )
	{
		obtenerDatos.activarCols();
		if ( obtenerDatos.leer() )
		{
			bRegresa = true;

			mysnprintf( cValor,255, "%.255s", obtenerDatos.valorChar("valor") );
			quitarBlancoNull( cValor, (int)mystrnlen( obtenerDatos.valorChar("valor") ) );
		}
	}
	else
	{
		logx( "error al obtener los datos de configuracion", _LOGINFO_);
	}

	return bRegresa;
}
void quitarBlancoNull( char *cCampo, int iTam )
{
	int i,k=0;
	char cTexto[80],iFlagBlanco=0;

		mymemset( cTexto,0,80 );

		for ( i=0;i<iTam;i++ )
		{
			if ( cCampo[i]!=' ' && cCampo[i]!=0  )
			{
				if(k < sizeof(cTexto))
                {
					if ( iFlagBlanco==1 )
					{
						iFlagBlanco=0;
						cTexto[k]=' ';
						k++;
					}
					cTexto[k]=cCampo[i];
					k++;
				}
			}
			if( cCampo[i]==' ' ) iFlagBlanco=1;
		}
		if(k < sizeof(cTexto))
        {
            cTexto[k]=0;
        }
		mymemset( cCampo,'\0',(unsigned int)iTam );
		mymemcpy( cCampo,cTexto,(unsigned int)k );
}

bool gnObtenerDatosCaja( C_ODBC *odbcTiendaNumero, DatosCajaSudamerica &datosCaja)
{
	bool bRegresa = false;
	char cIpProtheus[18] = {0}, cIpProtheusAlterno[18] = {0}, cSql[512] = {0}, cFilial[4] = {0}, cEmpresa[4] = {0}, cBDProtheus[27] = {0}, cLog[TAM_MIN_BUFF];
	long lFolioReferencia = 0L;
	int iRespuesta = 0;

	CRegistro xGenerales( odbcTiendaNumero );	//guia,tienda,caja,area,idproceso

	xGenerales.agregarCampoChar( "filial", 2);
	xGenerales.agregarCampoChar( "empresa", 2);	
	xGenerales.agregarCampoChar( "ipprotheus", 17);	
	xGenerales.agregarCampoChar( "ipalternoprotheus", 17);	
	xGenerales.agregarCampoChar( "ipwebservice", 17);	
	xGenerales.agregarCampoChar( "puerto", 12);	
	xGenerales.agregarCampoChar( "referencia", 15);	
	xGenerales.agregarCampoChar( "bdprotheus", 25);	
	xGenerales.agregarCampoChar( "pais", 2);		

	mysnprintf( cSql,sizeof(cSql),"SELECT filial, empresa, ipprotheus, ipalternoprotheus, ipwebservice, puerto, referencia, bdprotheus, pais "
					"FROM tdGeneraleMotorInterfaz( '%.15s', '%d', '%d', '%c', '%d' );",
					datosCaja.cParametros, datosCaja.iTienda, datosCaja.iCaja, datosCaja.cArea[0], datosCaja.iClaveMsj );
	////logx( csql, _LOGINFO_);

	if ( xGenerales.Exec( cSql ) == TRUE )
	{
		xGenerales.activarCols();
		if ( xGenerales.leer() )
		{

			mysnprintf( cIpProtheus,sizeof(cIpProtheus), "%.15s", xGenerales.valorChar( "ipprotheus" ) );
			mysnprintf( cLog,sizeof(cLog), "cIpProtheus [%.15s]", cIpProtheus );
			logx( cLog, _LOGINFO_);
			mysnprintf( cIpProtheusAlterno,sizeof(cIpProtheusAlterno), "%.15s", xGenerales.valorChar( "ipalternoprotheus" ) );
			mysnprintf( cLog,sizeof(cLog), "cIpProtheusAlterno [%.15s]", cIpProtheusAlterno );
			logx( cLog, _LOGINFO_);
			mysnprintf( cBDProtheus,sizeof(cBDProtheus), "%.25s", xGenerales.valorChar( "bdprotheus" ) );
			mysnprintf( cLog,sizeof(cLog), "cBDProtheus [%.25s]", cBDProtheus );
			logx( cLog, _LOGINFO_);

			mysnprintf(datosCaja.cReferenciaMsj,sizeof(datosCaja.cReferenciaMsj), "%.13s", xGenerales.valorChar( "referencia" ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cReferenciaMsj [%.13s]", datosCaja.cReferenciaMsj );
			logx( cLog, _LOGINFO_);
			mymemcpy( datosCaja.cEmpresa, xGenerales.valorChar( "empresa" ), sizeof( datosCaja.cEmpresa ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cEmpresa [%.2s]", datosCaja.cEmpresa );
			logx( cLog, _LOGINFO_);
			mymemcpy( datosCaja.cFilial, xGenerales.valorChar( "filial" ), sizeof( datosCaja.cFilial ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cFilial [%.2s]", datosCaja.cFilial );
			logx( cLog, _LOGINFO_);
			mysnprintf(datosCaja.cPuerto,sizeof(datosCaja.cPuerto), "%.10s", xGenerales.valorChar( "puerto" ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cPuerto [%.10s]", datosCaja.cPuerto );
			logx( cLog, _LOGINFO_);
			mysnprintf(datosCaja.cIpWebSrvice,sizeof(datosCaja.cIpWebSrvice), "%.15s", xGenerales.valorChar( "ipwebservice" ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cIpWebSrvice [%.15s]", datosCaja.cIpWebSrvice );
			logx( cLog, _LOGINFO_);
			// strncpy( datosCaja.cPais, xGenerales.valorChar( "pais" ), sizeof( datosCaja.cPais ));
			mysnprintf(datosCaja.cPais,sizeof(datosCaja.cPais), "%.15s", xGenerales.valorChar( "pais" ) );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cPais [%.2s]", datosCaja.cPais );
			logx( cLog, _LOGINFO_);

			mysnprintf(datosCaja.cIpProtheus,sizeof(datosCaja.cIpProtheus), "%.15s", cIpProtheus );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cIpProtheus [%.15s]", datosCaja.cIpProtheus );
			logx( cLog, _LOGINFO_);
			mysnprintf(datosCaja.cBDProtheus,sizeof(datosCaja.cBDProtheus), "%.25s", cBDProtheus );
			mysnprintf( cLog,sizeof(cLog), "datosCaja.cBDProtheus [%.25s]", datosCaja.cBDProtheus );
			logx( cLog, _LOGINFO_);
			bRegresa = true;

		}
	}
	else
	{

		logx("ERROR AL PREPARAR DATOS CAJA", _LOGINFO_);
	}

	return bRegresa;
}
bool obtenerFechaHora(C_ODBC *odbcTiendaNumero, char *cFecha, char *cHora)
{
	bool bRegresa = true;
	char cSql[256] = {0}, cLog [TAM_MIN_BUFF];
	long lFechaActual = 0;
	{
		mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT fecha, TRIM( TO_CHAR( date_part( 'hour', timenow() ), '09' ) ) || ':' || "
						"TRIM( TO_CHAR( date_part( 'minute', timenow() ), '09' ) ) || ':' || "
						"TRIM( TO_CHAR( date_part( 'second', timenow() ), '09' ) ) AS hora FROM gnDominio;" );

		CRegistro fechaHora( odbcTiendaNumero );

		fechaHora.agregarCampoFecha("fecha");
		fechaHora.agregarCampoChar( "hora", 8);

		if ( fechaHora.Exec( cSql ) )
		{
			fechaHora.activarCols();
			if ( fechaHora.leer() )
			{
				SqlTimeStamp *tFecha = fechaHora.valorFecha("fecha");
				mysnprintf( cFecha,10, "%04d%02d%02d", tFecha->ano(), tFecha->mes(), tFecha->dia() );
				logx( cFecha, _LOGINFO_);
				mysnprintf( cHora,10, "%.8s", fechaHora.valorChar("hora"));
				logx( cHora, _LOGINFO_);
				lFechaActual = longConverter(cFecha);
			}
		}
		else
		{
			logx("ERROR AL CONSULTAR FECHA Y HORA", _LOGINFO_);
		}
	}

	return bRegresa;
}
bool consultarColoniaCliente(C_ODBC *odbc_cartera, sSolicitudServicio *sSolicitud, int &iIdColonia )
{
	bool bContinuar = false;
	char cSql[256] = {0}, cTexto [256] ={0}, cLog[256] = {0};

	mysnprintf (cSql,sizeof(cSql), "select colonia from crloczona where ciudad = %d AND calle = %d AND desde <= %d AND hasta >= %d;", 
	sSolicitud->consultarDomicilio.idCiudad, sSolicitud->consultarDomicilio.idCalle, sSolicitud->consultarDomicilio.numCasa, sSolicitud->consultarDomicilio.numCasa );
	////logx( csql, _LOGINFO_);
	CRegistro colonia( odbc_cartera );

	colonia.agregarCampoEntero("colonia", DT_ENTERO);

	if( colonia.Exec( cSql ) )
	{
		colonia.activarCols();

		if( colonia.Leer() )
		{
			iIdColonia = colonia.valorLong("colonia");
			mysnprintf( cLog,sizeof(cLog), "iIdcolonia = [%d]",iIdColonia );
			logx( cLog, _LOGINFO_);
			bContinuar = true;
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog),"%s", "no se encontro colonia en base a la ciudad y numCasa proporcionado" );
			logx( cLog, _LOGINFO_);
			bContinuar = false;
		}		
	}
	else
	{
		logx("ERROR AL CONSULTAR LA COLONIA", _LOGINFO_);
	}
	return bContinuar;
}

bool obtenerCodigoPostal(C_ODBC *odbc_cartera, sSolicitudServicio *sSolicitud,int iIdColonia, long &lCodigoP )
{
	bool bContinuar = false;
	char cSql[256] = {0}, cLog[256] = {0};

	mysnprintf(cSql,sizeof(cSql), "SELECT codigopostal FROM crzonas WHERE ciudad=%d AND colonia=%d", sSolicitud->consultarDomicilio.idCiudad, iIdColonia);
	////logx( csql, _LOGINFO_);

	CRegistro obtenerCodPos( odbc_cartera );
	obtenerCodPos.agregarCampoEntero("codigopostal", DT_ENTERO);

    if ( !obtenerCodPos.Exec( cSql ) )
    {
		logx( "ERROR AL CONSULTAR CÓDIGO POSTAL", _LOGINFO_);
    }
    else
    {
        obtenerCodPos.activarCols();
        if ( obtenerCodPos.leer())
		{
			lCodigoP = obtenerCodPos.valorLong("codigopostal");
			mysnprintf( cLog,sizeof(cLog), "lCodigoP = [%ld]",lCodigoP );
			logx( cLog, _LOGINFO_);
			bContinuar = true;

		}
	}

	return bContinuar;
}
void obtenerProvincia(C_ODBC *odbcTiendaNumero, char *cProvincia, int iCiudad, int iModo, sRespuestaServicio *sRespuesta, int iTiendaLocal, int iTienda)

{
	char cSql[255] = {0}, cLog[255] = {0}, cIpServidor[17] = {0}, cUsuarioBD[20] = {0}, cPassBD[30], cNombreBD[20]={0};
	int i = 0;
	char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
	int iRespuesta = 0;
	C_ODBC conexionCartera;

	// if(consultarIpServidor( odbcTiendaNumero, IPCARTERA, cIpServidor ) == _OK_)
	// {
		//if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,(long)-1))
		iRespuesta = consultarSEC(_SEC_CARTERA, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
		if( iRespuesta == _OK_ )
		{
			//if(abrirConexion( &conexionCartera, cIpServidor,cNombreBD,cUsuarioBD ) > 0)
			iRespuesta = abrirConexion2( &conexionCartera, cDNS, cBd, cUser, cPss );
			if( iRespuesta == _OK_ )
			{
				mysnprintf( cSql,sizeof(cSql), "select provincia from crCiudadPercepcionIB where ciudad = %ld;", iCiudad);
				CRegistro consultaProvincia( &conexionCartera, false );
				consultaProvincia.agregarCampoChar( "provincia", 51 );
				if ( consultaProvincia.Exec( cSql ) )
				{
					cProvincia[50] = '\0';
					consultaProvincia.activarCols();
					if ( consultaProvincia.leer())
					{
						if(iModo == 1)
						{
							mysnprintf(cProvincia,3, "%.2s",consultaProvincia.valorChar( "provincia" ));
						}
						else
						{
							mysnprintf(cProvincia,25, "%.25s",&consultaProvincia.valorChar( "provincia" )[3]);
						}
					}
					else
					{
						mysnprintf(cProvincia,1,"%s", "");
						logx( "No se encontro la provincia favor de reportarlo a mesa de ayuda", _LOGINFO_);
					}
				}
				else
				{
					mysnprintf(cProvincia,1,"%s", "");
					mysnprintf( cLog,sizeof(cSql), "ERROR AL obtenerProvincia ERROR=> [%.150s]",consultaProvincia.error() );
					logx( cLog, _LOGINFO_);	
				}
			}
			else
			{
				mysnprintf(sRespuesta->cMensaje,255,"obtenerProvincia No fue posble abrir conexion  IpBD %.20s  BD %.30s   Usuario %.30s",cIpServidor,cNombreBD,cUsuarioBD);
				logx( sRespuesta->cMensaje, _LOGINFO_);
			}
		}
		else
		{
			logx("No se logro establecer conexión con el SEC - gnfunciones::obtenerProvincia", _LOGINFO_);
		}
	// }
	// else
	// {
	// 	mysnprintf( cLog,sizeof(cSql),"%s" ,"ERROR AL consultarIpServidor");
	// 	logx( cLog, _LOGINFO_);	
	// }
}
float ObtenerValorNeto(C_ODBC *odbcTiendaNumero, int iCodigo, int iPrecio, char cCausaUdi, char cQuienEntregaGlobal)
{
	float fValorNeto=0.000000;
	char cSql[255] = {0}, cLog[255] = {0};
	bool bBodega= false,bUdi = false;

	if(cCausaUdi == '2')
	{
		bUdi = true;
	}

	if(cQuienEntregaGlobal == 'B' || cQuienEntregaGlobal == 'S')
	{
		bBodega = true;
	}

	mysnprintf( cSql,sizeof(cSql), "SELECT tdobtenercostoneto(%ld,%ld,2,'%d','%d');", iCodigo, iPrecio, bUdi, bBodega);
	////logx( csql, _LOGINFO_);
	CRegistro obtenerNeto( odbcTiendaNumero, false );
	obtenerNeto.agregarCampoDecimal("tdobtenercostoneto",DT_FLOTANTE);	
	obtenerNeto.ClearResults(); 
	if ( obtenerNeto.Exec( cSql ))
	{
		obtenerNeto.activarCols();

		if( obtenerNeto.leer() )
		{
			fValorNeto = obtenerNeto.valorFloat("tdobtenercostoneto");
			mysnprintf(cLog,sizeof(cSql),"fValorNeto = %f",fValorNeto);
			logx( cLog, _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cSql), "ERROR AL OBTENER VALOR NETO CODIGO '%ld' ERROR=> [%.150s]",iCodigo, obtenerNeto.error() );
		logx( cLog, _LOGINFO_);	
	}
	return fValorNeto;
}


bool inicializarTablasTemporales(C_ODBC *odbcTiendaNumero,int iCaja, long lFactura, char *sPadStart)
{
	bool bContinuar = false;
	char cSql[256] = {0}, cLog[256] = {0} ;

	CRegistro actMuFacturaSQL( odbcTiendaNumero, false );
	
	mysnprintf (cSql,sizeof(cSql), "DELETE FROM tmpmufactura%02d%.11s;",iCaja, sPadStart);
	logx( "se limpia tmpmufactura", _LOGINFO_);

	if ( actMuFacturaSQL.Exec( cSql ) == TRUE )
	{
		mysnprintf (cSql,sizeof(cSql), "DELETE FROM tmpmufacturadetalle%02d%.11s;",iCaja, sPadStart);
		logx( "se limpia tmpmufacturadetalle", _LOGINFO_);

		if ( actMuFacturaSQL.Exec( cSql ) == TRUE )
		{
			mysnprintf (cSql,sizeof(cSql), "DELETE FROM tmpmufacturapendiente%02d%.11s;",iCaja, sPadStart);
			logx( "se limpia tmpmufacturapendiente", _LOGINFO_);

			if ( actMuFacturaSQL.Exec( cSql ) == TRUE )
			{
				mysnprintf (cSql,sizeof(cSql), "DELETE FROM tmpcacarmov%02d%.11s;",iCaja, sPadStart);
				logx( "se limpia tmpcacarmov", _LOGINFO_);

				if ( actMuFacturaSQL.Exec( cSql ) == TRUE )
				{
				bContinuar = true;
				logx("se ejecuto inicializarTablasTemporales correctamente", _LOGINFO_);
				}
			}
		}
	}

	if ( bContinuar == false )
	{
		mysnprintf( cLog,sizeof(cSql), "ERROR AL inicializarTablasTemporales ERROR=> [%.150s]",actMuFacturaSQL.error() );
		logx( cLog, _LOGINFO_);
		//sRespuesta->status = _ERROR_DE_SERVIDOR;
	}

	return bContinuar;
}

bool obtenerFechaDescuentoPrimerCompra(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta,long lCliente, int iTiendaLocal, int iTienda)
{
	char cSql[255] = {0}, cLog[255] = {0}, cIpServidor[17] = {0}, cUsuarioBD[20] = {0}, cPassBD[30], cNombreBD[20]={0};
	bool bRespuesta = false;	
	char cFechaPrimerCompra[12] = {0};
	mymemset(cFechaPrimerCompra, 0, sizeof(cFechaPrimerCompra));
	char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
	int iRespuesta = 0;
	//m_gridFactura.iFlagDescuentoPrimerCompra =0;
	//m_gridFactura.lClienteDescuentoPrimerCompra =0L;
	C_ODBC conexionCartera;

	// if(consultarIpServidor( odbcTiendaNumero, IPCARTERA, cIpServidor ) == _OK_)
	// {
	// 	if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,(long)-1))
		iRespuesta = consultarSEC(_SEC_CARTERA, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
		if( iRespuesta == _OK_ )
		{
			//if(abrirConexion( &conexionCartera, cIpServidor,cNombreBD,cUsuarioBD ) > 0)
			iRespuesta = abrirConexion2( &conexionCartera, cDNS, cBd, cUser, cPss );
			if( iRespuesta == _OK_ )
			{
				mysnprintf( cSql,sizeof(cSql), "SELECT fecha FROM crdescuentoprimercompra WHERE cliente = %ld", lCliente );
				////logx( csql, _LOGINFO_);
									
				CRegistro puntos( &conexionCartera, false );
				
				puntos.agregarCampoFecha( "fecha");
				
				if( puntos.Exec( cSql ) )
				{
					puntos.activarCols();
					if( puntos.leer() )
					{
						
						mysnprintf( cFechaPrimerCompra,sizeof(cFechaPrimerCompra), "%.08s",puntos.valorFecha( "fecha" ) );
						mysnprintf( cLog,sizeof(cSql), "Fecha de cliente consultado =  %.12s",cFechaPrimerCompra);
						logx( cLog, _LOGINFO_);
						if ( strncmp( cFechaPrimerCompra, "1900-01-01", 10 ) == 0)
						{	
							logx( "Cliente cuenta con fecha 1900-01-01", _LOGINFO_);
							//m_gridFactura.iFlagDescuentoPrimerCompra = 1;
							//m_gridFactura.lClienteDescuentoPrimerCompra =clienteMuebles.lCliente;
							bRespuesta = true;
							//bPrimerCompra = true;
						}
					}
					else
					{	  
						logx( "Cliente no cuenta con registro de fecha", _LOGINFO_);
						//m_gridFactura.iFlagDescuentoPrimerCompra = 2;
						//m_gridFactura.lClienteDescuentoPrimerCompra =clienteMuebles.lCliente;
						bRespuesta = false;
						//bPrimerCompra = false;
					}
				}
				else
				{
					logx( "Fallo la consulta de obtenerFechaDescuentoPrimerCompra()", _LOGINFO_);
					//m_gridFactura.iFlagDescuentoPrimerCompra =0;
					bRespuesta = false;
					//bPrimerCompra = false;
					mysnprintf(sRespuesta->sDatosCredMueblesRes.cMensaje,sizeof(sRespuesta->sDatosCredMueblesRes.cMensaje),"%s","error al Consultar la fecha de la primer compra del cliente. ");
					logx( sRespuesta->sDatosCredMueblesRes.cMensaje, _LOGINFO_);
				}
			}
			else
			{
				mysnprintf(sRespuesta->sDatosCredMueblesRes.cMensaje,sizeof(sRespuesta->sDatosCredMueblesRes.cMensaje),"obtenerFechaDescuentoPrimerCompra No fue posble abrir conexion  IpBD %.20s  BD %.30s   Usuario %.30s",cIpServidor,cNombreBD,cUsuarioBD);
				logx( sRespuesta->sDatosCredMueblesRes.cMensaje, _LOGINFO_);
			}
		}
		else
		{
			logx("No se logro establecer conexión con el SEC - gnfunciones::obtenerFechaDescuentoPrimerCompra", _LOGINFO_);
		}
	// }
	// else
	// {
	// 	mysnprintf( cLog,sizeof(cSql),"%s" ,"ERROR AL consultarIpServidor");
	// 	logx( cLog, _LOGINFO_);	
	// }

	return bRespuesta;
}
int checarCodigoJoyeria( long lCodigo)
{

	int iFlag = 0;
	logx( "checarCodigoJoyeria", _LOGINFO_);
    if( lCodigo >= 880000L && lCodigo <= 885999L ) 
	{
		iFlag = 1;
	}

    if( lCodigo >= 889000L && lCodigo <= 898999L ) 
	{
		iFlag = 1;
	}

    return iFlag;

}
int checarAgotadoCodigo( C_ODBC *odbcTiendaNumero, char cFlagApartado, char cAgotadoInvent)
{
	int iFlagAgotado = 0, iFlagSistApartado = 0;
	char cSqlTxt[1000] = {0};
	logx( "checarAgotadoCodigo", _LOGINFO_);
    if ( !checarSisApartadoNoMsg( iFlagSistApartado, odbcTiendaNumero, cSqlTxt ))     //gnwchapa.cpp
	{
	}

    if ( iFlagSistApartado == 1 )
    {
        if ( cFlagApartado == '1' || cAgotadoInvent == 'A' )
        {
            iFlagAgotado = 1;
        }
    }
    else
    {
        if ( cAgotadoInvent == 'A' ) iFlagAgotado = 1;
    }

    return iFlagAgotado;
}

bool checarSisApartadoNoMsg( int &iFlag, C_ODBC *odbcTiendaNumero, char *cSqlTxt)
{
	int iFlagApartado;
	bool bConsulta = true;
	logx( "checarSisApartadoNoMsg", _LOGINFO_);
	bConsulta = obtenerFlagApartadoMuebles( iFlagApartado, odbcTiendaNumero, cSqlTxt );
	if( bConsulta )
	{
		if( iFlagApartado == 1 )
		{	
			iFlag = 1;
			logx( "iFlagApartado = 1", _LOGINFO_);
		}
		else
		{
			iFlag = 0;
			logx( "iFlagApartado = 0", _LOGINFO_);		
		}
	}

    return bConsulta;
}

//Checar el flag del sistema de apartado en muebles
bool obtenerFlagApartadoMuebles( int &iFlagApartado, C_ODBC *odbcTiendaNumero, char *cSqlTxt)
{
	//CString sDatos;
	bool bConsultaOK = true;
	char cLog[255] = {0};

	mymemset(cSqlTxt,'\0',255);
	mysnprintf( cSqlTxt,40, "SELECT gnConsultarflag( 'M', '%d' )", FLAGM_SISTEMAAPARTADO );
	//logx( csqlTxt, _LOGINFO_);

	CRegistro consultaFolio( odbcTiendaNumero, false );
	consultaFolio.agregarCampoEntero( "flag", DT_ENTERO_CORTO );

	if( consultaFolio.Exec( cSqlTxt ) )
	{
		consultaFolio.activarCols();
		if( consultaFolio.Leer() )
		{
			iFlagApartado = consultaFolio.valorShort( "flag" );
		}
	}
	else
	{
		
		mysnprintf(cLog,255,"error al Consultar obtenerFlagApartadoMuebles: ERROR=> [%.150s]",consultaFolio.error());
		logx( cLog, _LOGINFO_);
		bConsultaOK = false;
	}

	return bConsultaOK;
}
void calcularDiaDePago( int &iMesPrimerPago, int &iDiaDePago, int iAnioActual, int iMesActual, int iDiaActual)
{
	int iDiaMax[] = { 0,
		27,
		30,
		29,
		30,
		29,
		30,
		30,
		29,
		30,
		29,
		30,
		30,
		27,
		30,
		29
	};

	if( iAnioActual == 1992 ||
		iAnioActual == 1996 ||
		iAnioActual == 2000 ||
		iAnioActual == 2004 ||
		iAnioActual == 2008 ||
		iAnioActual == 2012 ||
		iAnioActual == 2016 ||
		iAnioActual == 2020 ||
		iAnioActual == 2024 ||
		iAnioActual == 2028 ||
		iAnioActual == 92   ||
		iAnioActual == 96 )
	{
		iDiaMax[2] = 29;
	}
    iDiaDePago = iDiaActual + 1;
    iMesPrimerPago = iMesActual + 1;

    if( iDiaActual > iDiaMax[iMesActual] )
    {
        iDiaDePago = 1;
        iMesPrimerPago++;
        if( iMesPrimerPago > 12 ) iMesPrimerPago -= 12;
    }

    if( iDiaDePago > 28 && iMesPrimerPago == 2 )
    {
        iDiaDePago = 1;
        iMesPrimerPago = 3;
    }
}
void desplegarHoraEntrega( C_ODBC *odbcTiendaNumero,int iHoraIniEntMovto, int  iHoraFinEntMovto)
{
	char cSql[128] = {0};
	
	
	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT fechahorainicioentregamovto, fechahorafinalentregamovto FROM gnDominio;" );
	////logx( csql, _LOGINFO_);
						
	CRegistro TablaFecha( odbcTiendaNumero, false );
	
	TablaFecha.agregarCampoFecha( "fechahorainicioentregamovto");
	TablaFecha.agregarCampoFecha( "fechahorafinalentregamovto");
	
	if ( !TablaFecha.Exec( cSql ) )
	{
		iHoraIniEntMovto = 0;
		iHoraFinEntMovto = 0;
		logx( "ERROR AL CONSULTAR HORA DE ENTREGA", _LOGINFO_);
	}
	else
	{
		TablaFecha.activarCols();
		if ( TablaFecha.leer() )
		{
			mysnprintf( cSql,sizeof(cSql), "%.30s",TablaFecha.valorFecha( "fechahorainicioentregamovto" ) );
			iHoraIniEntMovto = (int)valor_campo( &cSql[11],2);
			mysnprintf( cSql,sizeof(cSql), "%.30s",TablaFecha.valorFecha( "fechahorafinalentregamovto" ) );
			iHoraFinEntMovto = (int)valor_campo( &cSql[11],2);
		}
	}
}
int determinarNumeroX( char cNumero )
{
	int iNumeroX = 0;

    iNumeroX = ( cNumero + 10 ) - 'A';

    if ( iNumeroX <= 9 )
    {    
        iNumeroX += 7;
    }

    return iNumeroX;
}
/* 
void grabarMovimientoFinanciera( sSolicitudFinanciera *sSolicitud, sRespuestaFinanciera *sRespuesta )
{
	char cTexto[300] = {0};
	char cArchivo[64] = {0}, cBuffer[4096] = {0};
	int iBufferTam = 0;
	
	time_t tTiempo;
	struct tm *tHora;
	tTiempo = time(NULL);
	tHora = localtime( &tTiempo );

	SqlTimeStamp tFecha;
	C_ODBC odbc;
	
	//int iRespuesta = abrirConexion( &odbc, sSolicitud->cIpSolicitudes );
	if(iRespuesta == _OK_)
	{
		CRegistro movtoFin( &odbc );
	
		movtoFin.agregarCampoEntero( "status", DT_ENTERO_CORTO );
		movtoFin.agregarCampoEntero( "tienda", DT_ENTERO_CORTO );
		movtoFin.agregarCampoChar( "area", 1 );
		movtoFin.agregarCampoEntero( "caja", DT_ENTERO_CORTO );
		movtoFin.agregarCampoChar( "fecha",12 );
		movtoFin.agregarCampoChar( "dni", 11 );	
		movtoFin.agregarCampoEntero( "codigoerrorid", DT_ENTERO);
		movtoFin.agregarCampoChar( "resultadotexto", 256 );	
		movtoFin.agregarCampoChar( "datosenviados", 4096 );
		movtoFin.agregarCampoChar( "datosenviadosfinanciera", 4096 );
		movtoFin.agregarCampoChar( "datosrecibidos", 4096 );
		movtoFin.agregarCampoChar( "datosrecibidosfinanciera", 4096 );
		movtoFin.agregarCampoEntero( "mensaje", DT_ENTERO_CORTO );
		movtoFin.agregarCampoChar( "financiera", 14 );
		movtoFin.agregarCampoChar( "sexo", 3 );
		movtoFin.agregarCampoEntero( "idsolicitud", DT_ENTERO );
		movtoFin.agregarCampoChar( "iptienda", 17 );
		movtoFin.agregarCampoChar( "ipsolicitudes", 17 );
		movtoFin.agregarCampoEntero( "diasueldo", DT_ENTERO_CORTO );
		movtoFin.agregarCampoChar( "areacelular", 6 );
		movtoFin.agregarCampoChar( "telefonocelular", 12 );
		movtoFin.agregarCampoEntero( "montoprestamo", DT_ENTERO );
		movtoFin.agregarCampoChar( "operadora", 10 );
		movtoFin.agregarCampoChar( "plan", 8 );
		movtoFin.agregarCampoChar( "token", 10 );
		movtoFin.agregarCampoEntero( "iddepartamento", DT_ENTERO_CORTO );
		movtoFin.agregarCampoChar( "errorinterno", 512 );
		
		
		movtoFin.activarCols();
		movtoFin.prepararInsert( "movimientosFinanciera" );
		
		movtoFin.valorShort( "status", sRespuesta->iRespuesta );
		movtoFin.valorShort( "tienda", sSolicitud->iTienda );
		movtoFin.valorChar( "area", sSolicitud->cArea );
		movtoFin.valorShort( "caja", sSolicitud->iCaja );
		movtoFin.valorChar( "fecha",  sSolicitud->cFecha );
		movtoFin.valorChar( "dni", sSolicitud->cDni );
		movtoFin.valorShort( "mensaje", sSolicitud->iMensaje );
		sSolicitud->iFinanciera == _CUOTAYA_ ? movtoFin.valorChar( "financiera", "CUOTAYA" ) : movtoFin.valorChar( "financiera", "TARJETAPLATA" );
		
		if(intConverter(sSolicitud->cSexo) != 0)
		{
			intConverter(sSolicitud->cSexo) == 1 ? movtoFin.valorChar( "sexo", "M" )  : movtoFin.valorChar( "sexo", "F" );			
		}
		
		movtoFin.valorLong( "idsolicitud", sSolicitud->iIDSolicitudPendiente );
		movtoFin.valorLong( "codigoerrorid", sRespuesta->iEstadoSoap );
		
		JSON de Entrada 
		
		mysnprintf( cArchivo,sizeof(cArchivo), "/sysx/progs/webservice/finansol/log/recv_%08ld.txt", (long)getpid() );
		{
			C_Archivo arcDatos( cArchivo, LEER_SOLAMENTE );
			iBufferTam = filelength(arcDatos.fp);

			if( iBufferTam > (int)sizeof( cBuffer ) -2 )
			{
				iBufferTam = (int)sizeof( cBuffer ) - 2;
			}
		
			arcDatos.leer( cBuffer, (unsigned int)iBufferTam );
			cBuffer[iBufferTam] = 0;
			arcDatos.cerrar();		
		}
		
		movtoFin.valorChar( "datosrecibidos", cBuffer );
		logx( cBuffer, _LOGINFO_);
		unlink( cArchivo );
		
		JSON de Salida 
		
		mysnprintf( cArchivo,sizeof(cArchivo), "/sysx/progs/webservice/finansol/log/send_%08ld.txt", (long)getpid() );
		{
			C_Archivo arcDatos( cArchivo, LEER_SOLAMENTE );
			iBufferTam = filelength(arcDatos.fp);

			if( iBufferTam > (int)sizeof( cBuffer ) -2 )
			{
				iBufferTam = (int)sizeof( cBuffer ) - 2;
			}
		
			arcDatos.leer( cBuffer, (unsigned int)iBufferTam );
			cBuffer[iBufferTam] = 0;
			arcDatos.cerrar();		
		}
		
		movtoFin.valorChar( "datosenviados", cBuffer );
		logx( cBuffer, _LOGINFO_);
		unlink( cArchivo );
		
		XML de Salida a Financiera 
		
		mysnprintf( cArchivo,sizeof(cArchivo), "/sysx/progs/webservice/finansol/log/send_xml_%08ld.txt", (long)getpid() );
		{
			C_Archivo arcDatos( cArchivo, LEER_SOLAMENTE );
			iBufferTam = filelength(arcDatos.fp);

			if( iBufferTam > (int)sizeof( cBuffer ) -2 )
			{
				iBufferTam = (int)sizeof( cBuffer ) - 2;
			}
		
			arcDatos.leer( cBuffer, (unsigned int)iBufferTam );
			cBuffer[iBufferTam] = 0;
			arcDatos.cerrar();		
		}
		
		movtoFin.valorChar( "datosenviadosfinanciera", cBuffer );
		logx( cBuffer, _LOGINFO_);
		unlink( cArchivo );
		
		XML de Salida a Financiera 
		
		mysnprintf( cArchivo,sizeof(cArchivo), "/sysx/progs/webservice/finansol/log/recv_xml_%08ld.txt", (long)getpid() );
		{
			C_Archivo arcDatos( cArchivo, LEER_SOLAMENTE );
			iBufferTam = filelength(arcDatos.fp);

			if( iBufferTam > (int)sizeof( cBuffer ) -2 )
			{
				iBufferTam = (int)sizeof( cBuffer ) - 2;
			}
		
			arcDatos.leer( cBuffer, (unsigned int)iBufferTam );
			cBuffer[iBufferTam] = 0;
			arcDatos.cerrar();		
		}
		
		movtoFin.valorChar( "datosrecibidosfinanciera", cBuffer );
		logx( cBuffer, _LOGINFO_);
		unlink( cArchivo );
		
		movtoFin.valorChar( "resultadotexto", sRespuesta->cMensaje );
		movtoFin.valorChar( "iptienda", sSolicitud->cIpTienda );
		movtoFin.valorChar( "ipsolicitudes", sSolicitud->cIpSolicitudes );
		movtoFin.valorShort( "diasueldo", sSolicitud->iDiaCobroSueldo );
		movtoFin.valorChar( "areacelular", sSolicitud->cAreaTelefono );
		movtoFin.valorChar( "telefonocelular", sSolicitud->cCelularOrigen );
		movtoFin.valorLong( "montoprestamo", sSolicitud->lMonto );
		movtoFin.valorChar( "operadora", sSolicitud->cOperadorCelular );
		movtoFin.valorChar( "plan", sSolicitud->cCodigoPlan );
		movtoFin.valorShort( "iddepartamento", sSolicitud->iIDProducto );
		movtoFin.valorChar( "errorinterno", sRespuesta->cMensajeInterno );
		
		if( movtoFin.Insert() )
		{
			movtoFin.Commit();
		}
		else
		{
				mysnprintf( cTexto,sizeof(cTexto), "Error al grabar el movimiento de Financiera. [%.150s]", movtoFin.error() );
				logx( cTexto , _LOGINFO_);
		}
	}else
	{
		
	}
}
 */
 bool consultarFechas(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
	char cSql[256] = {0};
	char cLog[TAM_MAX_BUFF] = {0};
	bool bRespuesta = false;
	int iTipoOrigenCliente = 0;

	CRegistro clienteSQL(odbcTiendaNumero, false);

	clienteSQL.agregarCampoEntero("Total", DT_ENTERO_LARGO);	

	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT COUNT(*) AS Total FROM gndominio ",
	"WHERE fecha >= (SELECT TRIM( valor ) FROM tdconfiguracion WHERE elemento = 'FECHA_INI_CTE_LCC')::DATE ",
	"AND fecha <= (SELECT TRIM( valor ) FROM tdconfiguracion WHERE elemento = 'FECHA_FIN_CTE_LCC')::DATE ");	

	if ( clienteSQL.Exec(cSql) )
	{		
		clienteSQL.activarCols();
		if ( clienteSQL.Leer() )
		{
			
			sRespuesta->bVigenciaLCC = clienteSQL.valorLong( "Total" ); 
			mysnprintf( cLog,sizeof(cLog), "se encontro el bVigenciaLCC: '%d'", sRespuesta->bVigenciaLCC );
			logx( cLog , _LOGINFO_);
			bRespuesta = true;
		}
	}
	if(bRespuesta)
	{
		bRespuesta = false;
		CRegistro clienteSQL(odbcTiendaNumero, false);

		clienteSQL.agregarCampoEntero("Total", DT_ENTERO_LARGO);

		mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(*) AS Total FROM tdconfiguracion WHERE elemento = 'STATUS_CTE_LCC' AND valor LIKE '%%-%ld%%';", iTipoOrigenCliente);	

		if ( clienteSQL.Exec(cSql) )
		{		
			clienteSQL.activarCols();
			if ( clienteSQL.Leer() )
			{
					
				sRespuesta->bStatusLCC = clienteSQL.valorLong( "Total" ); 
				mysnprintf( cLog,sizeof(cLog), "se encontro el bStatusLCC: '%d'", sRespuesta->bStatusLCC );
				logx( cLog , _LOGINFO_);
				bRespuesta = true;
			}
		}
	}
	if(bRespuesta)
	{
		bRespuesta = false;
		CRegistro clienteSQL(odbcTiendaNumero, false);

		clienteSQL.agregarCampoEntero("Total", DT_ENTERO_LARGO);
		mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(*) AS Total FROM tdconfiguracion WHERE elemento = 'TDA_DESC_ESP_CTE_LCC' AND valor LIKE '%%-%ld%%';", sSolicitud->iNumTienda );	

		if ( clienteSQL.Exec(cSql) )
		{		
			clienteSQL.activarCols();
			if ( clienteSQL.Leer() )
			{
				sRespuesta->bTiendaLCC = clienteSQL.valorLong( "Total" ); 
				mysnprintf( cLog,sizeof(cLog), "se encontro el bTiendaLCC: '%d'", sRespuesta->bTiendaLCC );
				logx( cLog  , _LOGINFO_);
				bRespuesta = true;
			}
		}
	}
	if (!bRespuesta)
	{
		logx( "Error en la funcion consultarFechas" , _LOGINFO_);	
	}
	return bRespuesta;
}
int esEmpleadoSinDig( long lCliente )
{
int iFlag=0;

    if ( lCliente>=9000000L && lCliente<10000000L )
    {
        iFlag=1;
    }
    return iFlag;
}


 long ObteneriSMC(long lSalarioMinimo)
 {
	long iSMC = 0;
	char sTexto[TAM_MIN_BUFF] = {0};

	mysnprintf(sTexto,sizeof(sTexto), "%.2d", lSalarioMinimo);
	//logx( sTexto, _LOGINFO_); //Dato sensible no debe ser mostrado en log

	if( sTexto != "00" )
	{
		iSMC = (long)(lSalarioMinimo / 100);
		iSMC = (long)(iSMC + 1);
		iSMC = (long)(iSMC * 100); // Redondeo del salario mínimo coppel.
	}
	else
	{
		iSMC = lSalarioMinimo;
	}

	mysnprintf(sTexto,sizeof(sTexto),"Valor iSMC = %d",iSMC);
	//logx( sTexto, _LOGINFO_); //Dato sensible no debe ser mostrado en log

	return iSMC;
 }



void gnGrabarSeguimiento( C_ODBC *odbcTiendaNumero, char cArea, int iCaja, int iProceso, char *cLog/*, bool bCommit*/ )
{
	char cSql[256] = {0};

	mysnprintf( cSql,sizeof(cSql), "SELECT gnSeguimiento( '%c', '%d', '%d', '%.128s' );", cArea, iCaja, iProceso, cLog );

	CRegistro borrarTabla( odbcTiendaNumero, false);
    borrarTabla.agregarCampoEntero("Total", DT_ENTERO);
	if ( borrarTabla.Exec( cSql ) == FALSE )
	{
        mysnprintf( cLog, 90, "Error al consultar parametro. [%.150s]", borrarTabla.error() );
		logx( cLog , _LOGINFO_);	
	}
}


//RQ624

int obtenerFactorLinea( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta )
{	
	char sTxt[256] = {0}, cLog[512] = {0};
	int lFactorLinea = 0;

	mysnprintf(sTxt,sizeof(sTxt),"%s","select factorlinea from gndominio;");
	CRegistro obtenerFactor(odbcTiendaNumero, false);

	obtenerFactor.agregarCampoEntero("factorlinea", DT_ENTERO);

	if ( obtenerFactor.Exec(sTxt) )
	{
		obtenerFactor.activarCols();
		obtenerFactor.leer();

		lFactorLinea = obtenerFactor.valorLong("factorlinea");
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar Tope de Credito. [%.285s]", obtenerFactor.error() );
       	logx( cLog , _LOGINFO_);
		sRespuesta->status = _ERROR_EN_MENSAJE;
		mysnprintf( sRespuesta->cMensaje,255,"%s", "Error al consultar Tope de Credito");
		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf( sRespuesta->cDevMensaje,255,"%s", "Error al consultar Tope de Credito");
	}

	return lFactorLinea;
}

bool leerParametricosCliente( C_ODBC *odbcCartera, S00028Envia &pCuentaEnvia, long lCliente)
{
	bool bRespuesta = false;
	char cSql[TAM_MED_BUFF] = {0}, cLog[TAM_MED_BUFF] = {0};

	mysnprintf( cSql,sizeof(cSql),"%s" ,"llegue a leerParametricosCliente()");
	////logx( csql, _LOGINFO_);

	CRegistro crConsCte( odbcCartera , false);
	crConsCte.agregarCampoEntero("mesesTranscurridos", DT_ENTERO);
	crConsCte.agregarCampoEntero("parRiesgoMuebles2", DT_ENTERO_LARGO);
	crConsCte.agregarCampoEntero("abonoPromedio", DT_ENTERO_LARGO);
	crConsCte.agregarCampoEntero("parPrestamo2", DT_ENTERO_LARGO);
	
	mysnprintf( cSql,sizeof(cSql), "SELECT mesesTranscurridos, parRiesgoMuebles2, abonoPromedio, parPrestamo2 FROM crCliente WHERE cliente = %ld;", lCliente );
	////logx( csql, _LOGINFO_);
			
	if ( crConsCte.Exec( cSql ) == TRUE )
	{
		crConsCte.activarCols();
		if ( crConsCte.Leer() )
		{
			bRespuesta = true;
			pCuentaEnvia.iEstado = _OK_;
			
			pCuentaEnvia.iMesesTranscurridos = crConsCte.valorLong( "mesesTranscurridos" );
			pCuentaEnvia.lParRiesgoMuebles2 = crConsCte.valorLong( "parRiesgoMuebles2" );
			pCuentaEnvia.lAbonoPromedio = crConsCte.valorLong( "abonoPromedio" );
			pCuentaEnvia.lParPrestamo2 = crConsCte.valorLong( "parPrestamo2" );
		}
		else
		{
			pCuentaEnvia.iEstado = E00028_ERROR_CLIENTE_NO_EXISTE;
		}
	}
	else 
	{
		pCuentaEnvia.iEstado = E00028_ERROR_CONSULTA;
		// crConsCte.odbc->GetLastError( crConsCte.GetHstmt() );
		// mysnprintf( cMensaje,sizeof(cMensaje), "Error al consultar los parametricos del cliente %ld. %d %s", lCliente, crConsCte.odbc->LastErrNum(), crConsCte.odbc->LastErrStr() );
		// logx( pCuentaEnvia.iEstado, cMensaje );

		mysnprintf( cLog,sizeof(cLog), "Error al leerParametricosCliente [%.150s]", crConsCte.error() );
		logx( cLog , _LOGINFO_);
	}
	
	return bRespuesta;
}

int consultarClienteTestigo( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, long lCliente)
{	
	char cTxt[TAM_MED_BUFF] = {0}, cLog[512] = {0};
	int iFlagTestigo = 0, iLongitud = 0;

	mysnprintf(cLog,sizeof(cLog),"%ld",lCliente);
	iLongitud = mystrnlen(cLog);
	mysnprintf(cLog,sizeof(cLog),"%c%c",cLog[iLongitud-3],cLog[iLongitud-2]);
	
	mysnprintf(cTxt,sizeof(cTxt),"SELECT COUNT(*) AS Total FROM tdconfiguracion WHERE elemento = 'GRUPO_TESTIGO_ALTORIESGO' AND valor LIKE '%%-%.20s-%%';",cLog);
	CRegistro consultaFlagTestigo(odbcTiendaNumero, false);
	//logx( cTxt, _LOGINFO_);
	consultaFlagTestigo.agregarCampoEntero("Total", DT_ENTERO);

	if ( consultaFlagTestigo.Exec(cTxt) )
	{
		consultaFlagTestigo.activarCols();
		if(consultaFlagTestigo.leer())
		{
			// iFlagTestigo = consultaFlagTestigo.valorLong("Total");
			if ( consultaFlagTestigo.valorLong("Total") > 0)
			{
				iFlagTestigo = 1;
			}
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar flag testigo. [%.285s]", consultaFlagTestigo.error() );
       	logx( cLog , _LOGINFO_);
		sRespuesta->status = _ERROR_EN_MENSAJE;
		mysnprintf( sRespuesta->cMensaje,255,"%s", "Error al consultar flagtestigo");
		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf( sRespuesta->cDevMensaje,255,"%s", "Error al consultar flag testigo");
	}

	return iFlagTestigo;
}

// gfmiML
short dcf( short iValorDcf )
{
    short iValor=0;

    iValor = iValorDcf;

    if ( iValor < 0 )
        iValor*=-1;
    return( iValor );
}

int meses_transcurridos( int dia,int mes,int anio ,int diaactual, int mesactual,int anioactual)
{
    int retorno=0;

    if(diaactual < dia ) mes++;

    //gn_coano.cpp
    retorno=(anioactual - anio)* 12 + mesactual - mes;

    if (diaactual == dia) retorno-=1;
    if (retorno < 0) retorno=0;
        
    return(retorno);
}

int checarJoyeriaCoppel( long lCodigo, int iAnio, int iMes, int iDia )
{


    int iFlag=0;
    char cTxt[20];

    mymemset(cTxt, 0, sizeof(cTxt));
    mysnprintf( cTxt,sizeof(cTxt),"%04d%02d%02d",iAnio, iMes, iDia );

    if ( checarCodigoJoyeria( lCodigo )==1 && valor_campo(cTxt,8)>20041226 )
    {
        //Coppel toma el control de la Joyer¡a
        iFlag = 1;
    }

    return( iFlag );
}

int ChecarFamTarjetasTiempoAire( long lFamilia )
{
    int iFlag=0;
    //Tiempo Aire....
    if ( lFamilia==22415 ) iFlag=1;

    return iFlag;
}


bool checarSisApartadoNoMsg( int &iFlag, C_ODBC *xodbc)
{
    int iFlagApartado;
    bool bConsulta = true;
    bConsulta = obtenerFlagApartadoMuebles( iFlagApartado, xodbc );
    if( bConsulta )
    {
        if( iFlagApartado == 1 )
        {	
            iFlag = 1;
        }
        else
        {
            iFlag = 0;
        }
    }
    return bConsulta;
}
bool obtenerFlagApartadoMuebles( int &iFlagApartado, C_ODBC *xodbc )
{
    //CString sDatos;
    bool bConsultaOK = true;
    char cSqlTxt[255] = {0}, cLog[512]={0};
    mymemset(cSqlTxt,' ',255);
    mysnprintf( cSqlTxt,sizeof(cSqlTxt), "SELECT gnConsultarflag( 'M', '%d' )", FLAGM_SISTEMAAPARTADO );
    //cSqlTxt[255]=0;
    CRegistro consultaFlag( xodbc, false );
    consultaFlag.agregarCampoEntero("gnConsultarflag",DT_ENTERO_CORTO);
    if( consultaFlag.Exec( cSqlTxt ) )
    {
        consultaFlag.activarCols();
        if( consultaFlag.Leer() )
        {
            //sDatos.Format( "%d", consultaFolio.flag );
            //sDatos.TrimLeft();
            //sDatos.TrimRight();
            iFlagApartado = (int)consultaFlag.valorShort("gnConsultarflag");
        }
    }
    else
    {
        mysnprintf(cLog,sizeof(cLog),"obtenerFlagApartadoMuebles [%.200s]", consultaFlag.error());
        bConsultaOK = false;
    }
    return bConsultaOK;
}
int checarSistemaCjs( char cAgotado, char cImportacion, char cQuienEntrega, short iFlagBodCjs, char *cMensaje )
{
    int iFlag = 0;
    if ( iFlagBodCjs == 1 )
    {
        if ( cImportacion == 'I' )
        {
            if ( cAgotado == 'A' && cQuienEntrega != 'T' && cQuienEntrega != 'S' )
            {
                //obtenerMensaje("GFIML.XML",MENSAJE_0017,cMensajeOut);
                mysnprintf( cMensaje,26, "%.25s"," !! VENDER POR T o S !! " );
                iFlag = 1;
            }
            else if ( cQuienEntrega != 'B' && cQuienEntrega != 'T' && cQuienEntrega != 'S' )
            {
                //obtenerMensaje("GFIML.XML",MENSAJE_0018,cMensajeOut);
                mysnprintf( cMensaje,26, "%.25s"," !! VENDER POR B, T o S," );
                iFlag = 1;
            }
        }
    }
    return( iFlag );
}
void sumarDia( int iSumarDia, int &iDia, int &iMes, int &iYear )
{
    int iDiaTmp, iMesTmp, iYearTmp;
    int iDiaMax[] = {0,31,28,31,30,31,30,31,31,30,31,30,31,31};
    if( iYear==1992 || iYear==1996 || iYear==2000 || iYear==2004 ||
        iYear==92   || iYear==96   || iYear==2008 || iYear==2012 || 
        iYear==2016 || iYear==2020 || iYear==2024 || iYear==2028 || 
        iYear==2032 || iYear==2036 || iYear==2040 || iYear==2044 )
    {
        iDiaMax[2]=29;
    }
    iDiaTmp = iDia;
    iMesTmp = iMes;
    iYearTmp = iYear;
    iDiaTmp += iSumarDia;
    if (iDiaTmp < 1 )
    {
        if( iMesTmp == 1 )
        {
            iMesTmp = 12;
            iYearTmp = iYearTmp - 1;
        }
        else
        {
            iMesTmp--;
        }
        iDiaTmp = iDiaMax[iMesTmp] + iDiaTmp;
        if ( iDiaTmp <= 0 )
            iDiaTmp=1;
    }
    if( iDiaTmp > iDiaMax[iMesTmp] )
    {
        iDiaTmp = iDiaTmp - iDiaMax[iMesTmp];
        iMesTmp++;
        if( iMesTmp > 12 )
        {
            iMesTmp = 1;
            iYearTmp++;
        }
    }
    iDia = iDiaTmp;
    iMes = iMesTmp;
    iYear = iYearTmp;
}
void miniFecha(char *fecha, int dia, int mes, int ano)
{
    char *m_corto[] = {"  ", "ENE", "FEB", "MAR", "ABR", "MAY", "JUN", "JUL", "AGO", "SEP", "OCT", "NOV", "DIC" };
    ano = ano_2000_2dig( ano );       //gn_coano.c
    if ( mes < 0 || mes > 12 ) mes = 0;
    if ( dia == 0 )
    {
        mysnprintf(fecha,20, "%.3s%02d", m_corto[mes], ano );
    }
    else
    {
        if ( ano == 0 )
        {
            mysnprintf(fecha,20, "%02d%.3.s", dia, m_corto[mes] );
        }
    }
    if ( dia > 0 && ano >= 0 )
    {
        mysnprintf(fecha,20, "%02d%.3s%02d", dia, m_corto[mes], ano );
    }
}
int ano_2000_2dig( int ano )
{
int aa=0;
    aa=ano;
    if ( ano<2000 )
    {
        if ( ano>1900 )
        {
            aa=ano-1900;
        }
        else if ( ano>99 )
        {
            aa=ano-100;
        }
    }
    else
    {
        aa=ano-2000;
    }
    return( aa );
}
bool checarAntiguedadCodigo( long lCodigo, C_ODBC *xOdbc, char *cSqlTxt, int &iDiaAntiguedad, int &iMesAntiguedad, int &iAnioAntiguedad )
{
    bool bContinuar = true;
    char cLog[512]={0};
    mysnprintf( cSqlTxt, 64,"SELECT muChecarAntiguedadCodigo('%ld'); ",lCodigo);
    //logx(cSqlTxt);
    CRegistro fechaAntiguedadSQL(xOdbc);
    fechaAntiguedadSQL.agregarCampoFecha("muchecarantiguedadcodigo");
    
    if (!fechaAntiguedadSQL.Exec(cSqlTxt))
    {
        mysnprintf(cLog,sizeof(cLog),"%.510s", fechaAntiguedadSQL.error());
        bContinuar = false;
    }
    else
    {
        fechaAntiguedadSQL.activarCols();
        while( fechaAntiguedadSQL.Leer() )
        {
            SqlTimeStamp *tFecha = fechaAntiguedadSQL.valorFecha("muchecarantiguedadcodigo");
            iDiaAntiguedad =    tFecha->dia();
            iMesAntiguedad =    tFecha->mes();
            iAnioAntiguedad =   tFecha->ano();
        }
    }
    return( bContinuar );
}


int diasTranscurridos(int iDia, int iMes, int iAnio,int iDiaActual, int iMesActual, int iAnioActual)
{
	int iDiasT, iMesesT;

    iMesesT = meses_transcurridos(iDia, iMes, iAnio,iDiaActual,iMesActual,iAnioActual); // gnwmeses.cpp
	if ( iMesesT == 0 )
	{
		iDiasT=iDiaActual - iDia;
	}
	else
	{
		if (iDiaActual < iDia || iDiaActual == iDia)
    	{
        	iDiasT =(int)((float)iMesesT*30.42 + (float)30.42 + (float)(iDiaActual - iDia));
    	}
    	else
    	{
        	iDiasT = (int)((float)iMesesT*30.42 + (float)(iDiaActual - iDia));
    	}
	}
    if (iDiasT<0) iDiasT=0;

    return(iDiasT);
}

long consultarFechaPrimerCompraRetorno( C_ODBC *conexionCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long lCliente ) //La que si regresa la fecha de la primer compra
{
	char cFechaPrimerCompra[11] = {0}, cFechaUltiCompra[11] = {0}, cSql[128] = {0}, cTexto[12] = {0};
	int iDiasTransPrimerCompra = 0, iDia = 0, iMes = 0, iYear = 0, iDiaPrimerCompra = 0, iMesPrimerCompra = 0, iYearPrimerCompra = 0;
	long lFechaPrimerCompra = 0;
	
	mysnprintf( cTexto,sizeof(cTexto), "%08ld", sSolicitud->ventaTramiteReq.lFecha );
	iYear = valorCampo( cTexto, 4 );
	iMes = valorCampo( &cTexto[4], 2 );
	iDia = valorCampo( &cTexto[6], 2 );

	mysnprintf( cSql,sizeof(cSql), "SELECT fechaprimercompra FROM crcliente WHERE cliente = %ld", lCliente );
	////logx( csql, _LOGINFO_);
	CRegistro primercompra( conexionCartera );
	primercompra.agregarCampoFecha("fechaprimercompra");
	
	if( primercompra.Exec( cSql ) )
	{
		primercompra.activarCols();
		if( primercompra.leer() )
		{
			mysnprintf( cFechaPrimerCompra,sizeof(cFechaPrimerCompra), "%.10s", primercompra.valorFecha("fechaprimercompra"));
			logx( cFechaPrimerCompra, _LOGINFO_);
			iYearPrimerCompra = valorCampo( cFechaPrimerCompra, 4 );
			iMesPrimerCompra = valorCampo( &cFechaPrimerCompra[5], 2 );
			iDiaPrimerCompra = valorCampo( &cFechaPrimerCompra[8], 2 );
			// mysnprintf(cTexto,sizeof(cTexto), "iYearPrimerCompra = %d, iMesPrimerCompra = %02d, iDiaPrimerCompra = %02d", iYearPrimerCompra, iMesPrimerCompra, iDiaPrimerCompra);
			mysnprintf(cFechaPrimerCompra,sizeof(cFechaPrimerCompra), "%d-%02d-%02d", iYearPrimerCompra, iMesPrimerCompra, iDiaPrimerCompra);
			if ( strncmp( cFechaPrimerCompra, "1900-01-01", 10 ) == 0)
			{
				//iFlagPrimerCompra = 1;
				iDiasTransPrimerCompra = 0;
			}
			else 
			{
				mysnprintf( cFechaUltiCompra,sizeof(cFechaUltiCompra), "%04d-%02d-%02d", iYear, iMes, iDia );
				if ( strncmp( cFechaPrimerCompra, cFechaUltiCompra, 10 ) == 0 )
				{	
                    iDiasTransPrimerCompra = 1;
				}
				else
				{
					iDiasTransPrimerCompra = diasTranscurridos( (int)iDiaPrimerCompra, (int)iMesPrimerCompra, (int)iYearPrimerCompra, 
														(int)iYear, (int)iMes, (int)iYear );
														
				}
			}
		}
	}
	else
	{
		sRespuesta->status = _ERROR_DE_SERVIDOR;                        
		mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");

		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf(sRespuesta->cDevMensaje,255,"ERROR AL EJECUTAR QUERY. [%.200s]", primercompra.error() );
		logx( sRespuesta->cDevMensaje, _LOGINFO_);
	}
	mysnprintf(cTexto,sizeof(cTexto), "%d%02d%02d", iYearPrimerCompra, iMesPrimerCompra, iDiaPrimerCompra);
	lFechaPrimerCompra = longConverter(cTexto);
	return lFechaPrimerCompra;
}



long calcularSaldoFactorizadoNuevaCompra(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta ,int iPlazo, long lSaldo, int iFlagLineaCreditoEsp, int iCteNEspecial, int iTipoCreditoCliente, int iTipoCtaRM, int iTiendaLocal, int iTienda)
{

	char cSqlTxt[128] = {0};
	long lSaldoFactorizado = 0;
	char cMensaje[255]={0}, cLog[512] = {0}, cIpServidor[17] = {0}, cUsuarioBD[20] = {0}, cPassBD[30], cNombreBD[20]={0};;
	char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
	int iRespuesta = 0;

	C_ODBC conexionCartera;

	mysnprintf (cMensaje,sizeof(cMensaje),"**-FactorizaSaldo iPlazo = %ld lSaldo = %ld",iPlazo,lSaldo) ;
	logx( cMensaje , _LOGINFO_);

	if(iTipoCtaRM !=0)
	{
		iTipoCtaRM = 1;
	}
	
	// if(consultarIpServidor( odbcTiendaNumero, IPCARTERA, cIpServidor ) == _OK_)
	// {
	// 	if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,(long)-1))
		iRespuesta = consultarSEC(_SEC_CARTERA, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
		if( iRespuesta == _OK_ )
		{
			//if(abrirConexion( &conexionCartera, cIpServidor,cNombreBD,cUsuarioBD ) < 0)
			iRespuesta = abrirConexion2( &conexionCartera, cDNS, cBd, cUser, cPss );
			if( iRespuesta != _OK_ )
			{
				sRespuesta->status = _ERROR_EN_MENSAJE;
				mysnprintf( sRespuesta->cMensaje,255,"%s", "Error al abrir de conexion");
				sRespuesta->iDevStatus = _ERROR_QUERY_;
				mysnprintf( sRespuesta->cDevMensaje,255,"%s", "Error al consultar flag abrirConexion [conexionCartera]");
			}
		}
		else
		{
			logx("No se logro establecer conexión con el SEC - gnfunciones::calcularSaldoFactorizadoNuevaCompra", _LOGINFO_);
		}
	//}

	CRegistro valorFactorizado( &conexionCartera, false );

	valorFactorizado.agregarCampoEntero("total", DT_ENTERO);

	mysnprintf( cSqlTxt,sizeof(cSqlTxt), "SELECT COALESCE(gnObtenerCuentaFactorizada02(%d,%d,%ld,%d),0) AS Total", iTipoCtaRM, iPlazo, lSaldo, iFlagLineaCreditoEsp );
	//logx( csqlTxt, _LOGINFO_);

	valorFactorizado.ClearResults();
	if( valorFactorizado.Exec(cSqlTxt))
	{
		valorFactorizado.activarCols();
		if( valorFactorizado.Leer() )
		{
			sRespuesta->iDevStatus = _OK_;
			logx("CONSULTO EL SALDO FACTORIZADO", _LOGINFO_);
			lSaldoFactorizado = valorFactorizado.valorLong("total");
			mysnprintf( cLog,sizeof(cLog), "lSaldoFactorizado [%d]", lSaldoFactorizado );
       		logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar calcularSaldoFactorizadoNuevaCompra. [%.250s]", valorFactorizado.error() );
       	logx( cLog , _LOGINFO_);
		sRespuesta->status = _ERROR_EN_MENSAJE;
		mysnprintf( sRespuesta->cMensaje,255,"%s", "Error al consultar Saldo Factorizado");
		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf( sRespuesta->cDevMensaje,255,"%s", "Error al consultar flag gnObtenerCuentaFactorizada02");
	}
	
	return lSaldoFactorizado;
}

bool consultarFechasGnDominio(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta)
{
	bool bVigencia=false;
	char cSql[256] = {0}, cLog[512] = {0};
	int iVigencia = 0; 
	
	logx( "ENTRO A CONSULTAR LA FECHA consultarFechasGnDominio()", _LOGINFO_);
	CRegistro clienteSQL(odbcTiendaNumero);

	mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(*) FROM gndominio WHERE fecha >= date('%.12s') AND fecha <= date('%.12s')", sRespuesta->cFechaIniCte, sRespuesta->cFechaFinCte) ;
	////logx( csql, _LOGINFO_);
	clienteSQL.agregarCampoEntero("Total",DT_ENTERO_CORTO);

	if ( clienteSQL.Exec(cSql) )
	{		
		clienteSQL.activarCols();
		if ( clienteSQL.Leer() )
		{
			logx( "CONSULTO LA FECHA DE LA GN DOMINIO", _LOGINFO_);
			bVigencia=true;
			sRespuesta->bVigenciaLCC = true;
			iVigencia = clienteSQL.valorShort("Total");

			if(iVigencia == 0)
			{
				bVigencia = false;
				sRespuesta->bVigenciaLCC = false;
			}	
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar consultarFechasGnDominio. [%.250s]", clienteSQL.error() );
       	logx( cLog , _LOGINFO_);
		sRespuesta->status = _ERROR_EN_MENSAJE;
		mysnprintf( sRespuesta->cMensaje,255,"%s", "Error al consultar Fecha de incio y fin");
		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf( sRespuesta->cDevMensaje,255,"%s", "Error al consultar flag consultarFechasGnDominio");
		bVigencia = false;
		sRespuesta->bVigenciaLCC = false;
	}

	return bVigencia;
}

/*bool obtenerFechaDescuentoPrimerCompra(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, long lCliente)
{
	char cSql[255] = {0};
	char cIpServidor[17] = {0}, cUsuarioBD[20] = {0}, cPassBD[30] = {0}, cNombreBD[20] = {0}, cLog[512] = {0};
	bool bRespuesta = false;	
	char cFechaPrimerCompra[12] = {0};
	sRespuesta->sDatosCredMueblesRes.bPrimerCompra = false;//MA
	mymemset(cFechaPrimerCompra, 0, sizeof(cFechaPrimerCompra));

	C_ODBC conexionCartera;
	
	sRespuesta->sDatosCredMueblesRes.iFlagDescuentoPrimerCompra =0;
	sRespuesta->sDatosCredMueblesRes.lClienteDescuentoPrimerCompra =0L;
	mysnprintf(sRespuesta->cMensaje,255,"%s", "OK");
	sRespuesta->status = _MENSAJE_CORRECTO_;

	logx( "Entro a consultar fecha primer compra", _LOGINFO_);

	mysnprintf( cSql,sizeof(cSql), "SELECT fecha FROM crdescuentoprimercompra WHERE cliente = %ld", lCliente );
	//extraerFechaActual(cFechaUpdate);
	////logx( csql, _LOGINFO_);

	if(consultarIpServidor( odbcTiendaNumero, IPCARTERA, cIpServidor ) == _OK_)
	{
		if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,(long)-1))
		{
			//if(abrirConexion( &conexionCartera, cIpServidor,cNombreBD,cUsuarioBD ) > 0)
			{
						
				CRegistro puntos( &conexionCartera );

				puntos.agregarCampoFecha("fecha");
				
				if( puntos.Exec( cSql ) )
				{
					puntos.activarCols();
					if( puntos.leer() )
					{
						mysnprintf( cFechaPrimerCompra,sizeof(cFechaPrimerCompra), "%s", puntos.valorFecha("fecha"));
						logx( "Fecha de cliente consultado", _LOGINFO_);
						logx( cFechaPrimerCompra, _LOGINFO_);

						if ( strncmp( cFechaPrimerCompra, "1900-01-01", 10 ) == 0)
						{	
							logx( "Cliente cuenta con fecha 1900-01-01", _LOGINFO_);
							sRespuesta->sDatosCredMueblesRes.iFlagDescuentoPrimerCompra = 1;
							sRespuesta->sDatosCredMueblesRes.lClienteDescuentoPrimerCompra = lCliente;
							bRespuesta = true;
							sRespuesta->sDatosCredMueblesRes.bPrimerCompra = true;
						}
					}
					else
					{	  
						logx( "Cliente no cuenta con registro de fecha", _LOGINFO_);
						sRespuesta->sDatosCredMueblesRes.iFlagDescuentoPrimerCompra = 2;
						sRespuesta->sDatosCredMueblesRes.lClienteDescuentoPrimerCompra = lCliente;
						bRespuesta = true;
						sRespuesta->sDatosCredMueblesRes.bPrimerCompra = false;
					}

					
				}
				else
				{
					logx( "Fallo la consulta de obtenerFechaDescuentoPrimerCompra()", _LOGINFO_);
					sRespuesta->sDatosCredMueblesRes.iFlagDescuentoPrimerCompra =0;
					bRespuesta = false;
					sRespuesta->sDatosCredMueblesRes.bPrimerCompra = false;

					sRespuesta->status = E00001_ERROR_QUERY;
         		  	mysnprintf(sRespuesta->cMensaje,255,"%s","ERROR AL CONSULTAR LA FECHA DE LA PRIMER COMPRA DEL CLIENTE");
					logx( sRespuesta->cMensaje, _LOGINFO_);  

					sRespuesta->iDevStatus = _ERROR_QUERY_;
           			mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL EJECUTAR obtenerFechaDescuentoPrimerCompra");
           			logx( sRespuesta->cDevMensaje, _LOGINFO_);

					mysnprintf( cLog,sizeof(cLog), "Error al consultar calcularSaldoFactorizadoNuevaCompra. [%.250s]", puntos.error() );
       				logx( cLog , _LOGINFO_);
				}
			}
		}
	}

	return bRespuesta;
}*/

void apagarFlagCteCero(sRespuestaServicio *sRespuesta, int iModo )
{
	char cLog[126] = {0};

	logx( "Entro a apagar los flag de Cliente Cero", _LOGINFO_);

	mysnprintf(cLog,sizeof(cLog),"Entro por el modo = [%d]", iModo);
	logx( cLog, _LOGINFO_);

	sRespuesta->bVigenciaLCC = false;
	sRespuesta->bFlagContadoCLCC = false; 
	sRespuesta->bCteCeroCredito = false;
	sRespuesta->bStatusLCC = false;
	sRespuesta->bAplicaCLCC = false;
	sRespuesta->bTiendaLCC = false;
	sRespuesta->bFlagDescuentoCero = false;
	sRespuesta->iDescuentoClienteCero = 0;
}

//Valida fecha inicio de la campaña línea de crédito cero, -Folio 144. 
bool obtenerFechaInicioFinTdConfiguracion( C_ODBC *xOdbcTiendaNumero, char *cElemento, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
	char cSql[256] = {0}, cLog[512] = {0};
	bool bRegresa = false;

	logx( "**- Entro obtenerValorTdConfiguracion LN-2763", _LOGINFO_);

	mysnprintf( cSql,sizeof(cSql), "SELECT TRIM( valor ) FROM tdconfiguracion WHERE elemento = '%.100s';", cElemento );

	CRegistro ConsultarTdConfiguracion( xOdbcTiendaNumero );

	ConsultarTdConfiguracion.agregarCampoChar("valor",256);

	if ( ConsultarTdConfiguracion.Exec( cSql ) == TRUE )
	{
		ConsultarTdConfiguracion.activarCols();
		if ( ConsultarTdConfiguracion.Leer() )
		{
			if(strncmp( cElemento, "FECHA_INI_CTE_LCC", 17 ) == 0)
			{
				logx( "**- Obtuvo datos obtenerValorTdConfiguracion LN-2774", _LOGINFO_);
				mysnprintf( sRespuesta->cFechaIniCte,sizeof(sRespuesta->cFechaIniCte), "%.11s", ConsultarTdConfiguracion.valorChar("valor") );
				bRegresa = true;
			}
			else
			{
				logx( "**- Obtuvo datos obtenerValorTdConfiguracion LN-2774", _LOGINFO_);
				mysnprintf( sRespuesta->cFechaFinCte,sizeof(sRespuesta->cFechaFinCte), "%.11s", ConsultarTdConfiguracion.valorChar("valor") );
				bRegresa = true;
			}

		}
	}
	else
	{
		bRegresa = false;
		sRespuesta->status = E00001_ERROR_QUERY;
		mysnprintf(sRespuesta->cMensaje,255,"%s","ERROR AL CONSULTAR FECHA DE CLIENTE CERO");
		logx( sRespuesta->cMensaje, _LOGINFO_);  

		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf(sRespuesta->cDevMensaje,255,"ERROR AL EJECUTAR obtenerFechaInicioFinTdConfiguracion, [%.100s]", cElemento);
		logx( sRespuesta->cDevMensaje, _LOGINFO_);
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar obtenerFechaInicioFinTdConfiguracion. [%.250s]", ConsultarTdConfiguracion.error() );
		logx( cLog , _LOGINFO_);

	}

	return bRegresa;
}

bool consultaTdaDctoCLCC(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
	bool bRespuesta = false;
	char cSql[300] = {0}, cLog[512] = {0};
	int iValor = 0;
	
	mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(*) AS Total FROM tdconfiguracion WHERE elemento = 'TDA_DESC_ESP_CTE_LCC' AND valor LIKE '%%-%ld%%';", sSolicitud->iNumTienda);

	CRegistro consultaTienda( odbcTiendaNumero );
	
	consultaTienda.agregarCampoEntero("Total",DT_ENTERO_CORTO);

	if( consultaTienda.Exec( cSql ) )
	{
		consultaTienda.activarCols();
		if( consultaTienda.Leer() )
		{
			iValor = consultaTienda.valorShort("Total"); 
			mysnprintf(cLog,sizeof(cLog),"tdconfiguracion Valor[%ld]", iValor);
			logx( cLog, _LOGINFO_);
			if( iValor > 0 )
			{
				bRespuesta = true;
				sRespuesta->bTiendaLCC = true;
				logx("consultaTdaDctoCLCC[bTiendaLCC = true]", _LOGINFO_);
			}
			else
			{
				sRespuesta->bTiendaLCC = false;
				logx("consultaTdaDctoCLCC[bTiendaLCC = false]", _LOGINFO_);
			}
		}
	}
	else
	{		
		sRespuesta->status = E00001_ERROR_QUERY;
		mysnprintf(sRespuesta->cMensaje,255,"%s","ERROR AL CONSULTAR FECHA DE CLIENTE CERO");
		logx( sRespuesta->cMensaje, _LOGINFO_);  

		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf(sRespuesta->cDevMensaje,255,"%s","ERROR AL EJECUTAR consultaTdaDctoCLCC");
		logx( sRespuesta->cDevMensaje, _LOGINFO_);
		
		mysnprintf( cLog,sizeof(cLog), "Error al consultar consultaTdaDctoCLCC. [%.250s]", consultaTienda.error() );
		logx( cLog , _LOGINFO_);
	}

	return bRespuesta;
}



bool obtenerFechaPrimerCompra(C_ODBC *odbcCartera, long lCliente, long lFecha, sDatosAltoRiesgoCR *datosAltoRiesgo)
{
	char cLog[TAM_MED_BUFF] = {0}, cSql[255] = {0}, cFechaUltCompra[11] = {0}, cFecha[10] = {0}, cTexto[10] = {0}, cAux[10] = {0};
	bool bRespuesta = false;
	int iAnio = 0, iMes = 0, iDia = 0;
	char cFechaPrimerCompra[15] = {0};

	mysnprintf( cSql,sizeof(cSql), "SELECT fechaprimercompra FROM crcliente WHERE cliente = %ld", lCliente );
	////logx( csql, _LOGINFO_);

	CRegistro puntos( odbcCartera, false);
    puntos.agregarCampoFecha("fechaprimercompra");

	if( puntos.Exec( cSql ) )
	{
		puntos.activarCols();
		if( puntos.leer() )
		{
			SqlTimeStamp *tFecha = puntos.valorFecha("fechaprimercompra");
			mysnprintf( cLog,sizeof(cLog), "fechaprimercompra [%04d%02d%02d]", tFecha->ano(), tFecha->mes(), tFecha->dia() );
			logx( cLog, _LOGINFO_);

			// esta funcion debe asignar la variable a cFechaPrimerCompra y no a cFechaPrimerCompraCR
			mysnprintf( cFechaPrimerCompra,sizeof(cFechaPrimerCompra), "%04d-%02d-%02d", tFecha->ano(), tFecha->mes(), tFecha->dia() );
			
			if ( strncmp( cFechaPrimerCompra, "1900-01-01", 10 ) == 0)
			{
				bRespuesta = true;
				datosAltoRiesgo->iDiasTransPrimerCompra = 0;
				datosAltoRiesgo->iFlagPrimerCompra = 1;
			}
			else
			{
				mysnprintf(cTexto,sizeof(cTexto),"%.8ld", lFecha );
				mysnprintf(cAux,sizeof(cAux),"%.4s",cTexto);
				iAnio = intConverter(cAux);
				mysnprintf(cAux,sizeof(cAux),"%c%c",cTexto[4],cTexto[5]);
				iMes = intConverter(cAux);
				mysnprintf(cAux,sizeof(cAux),"%c%c",cTexto[6],cTexto[7]);
				iDia = intConverter(cAux);
				mysnprintf( cFechaUltCompra,sizeof(cFechaUltCompra), "%04d-%02d-%02d", iAnio, iMes, iDia );

				mysnprintf( cLog,sizeof(cLog), "cFechaUltCompra [%.20s]", cFechaUltCompra );
				logx( cLog, _LOGINFO_);

				if ( strncmp( cFechaPrimerCompra, cFechaUltCompra, 10 ) == 0)
				{

					datosAltoRiesgo->iDiasTransPrimerCompra = 1;
				}
				else
				{
					datosAltoRiesgo->iDiasTransPrimerCompra = diasTranscurridos(tFecha->dia(), tFecha->mes(), tFecha->ano(), iDia, iMes, iAnio);
					mysnprintf( cLog,sizeof(cLog), "iDiasTransPrimerCompra [%d]", datosAltoRiesgo->iDiasTransPrimerCompra );
					logx( cLog, _LOGINFO_);
					// datosAltoRiesgo->iDiasTransPrimerCompra = diasTranscurridos( puntos.fecha.dia(), puntos.fecha.mes(), puntos.fecha.ano(), 
					// 							(int)sysRopa.iDiaSys, (int)sysRopa.iMesSys, (int)sysRopa.iYearSys );
				}
			}
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,sizeof(cLog), "Error al consultar fechaprimercompra [%.150s]", puntos.error() );
		logx( cLog  , _LOGINFO_);
		// puntos.odbc->GetLastError(puntos.GetHstmt());
		// grabarError( puntos.odbc, "CCapturarNC", "obtenerFechaPrimerCompra()", "Consultar la fecha de la primer compra del cliente.", cSql );
	}

	return bRespuesta;
}

int obtenerPuntosIniciales(C_ODBC *odbcTiendaNumero)
{
	char cSql[255] = {0}, cLog[255] = {0};
	int iRespuesta;

	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT puntosparametricoropa FROM gndominio" );
	////logx( csql, _LOGINFO_);

	CRegistro puntos( odbcTiendaNumero , false);
	puntos.agregarCampoEntero("puntosparametricoropa", DT_ENTERO);

	if( puntos.Exec( cSql ) )
	{
		puntos.activarCols();
		if( puntos.leer() ) {
			iRespuesta = puntos.valorLong( "puntosparametricoropa" );
		}
	}
	else
	{
		// puntos.odbc->GetLastError(puntos.GetHstmt());
		// grabarError( puntos.odbc, "PagoInicialNC", "calcularPI()", "Consultar los puntos iniciales de ropa.", cSql );
		mysnprintf( cLog,sizeof(cSql), "Error al consultar obtenerPuntosIniciales. [%.150s]", puntos.error() );
		////logx( cLog, _LOGINFO_);
	}

	return iRespuesta;
}

int consultaDatosGndominio(C_ODBC *odbcTiendaNumero)
{
	char cSql[300] = {0}, cLog[255] = {0};
	int iPuntosParIniciales = 0;

	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT puntospariniciales FROM gnDominio LIMIT 1");
	////logx( csql, _LOGINFO_);

	CRegistro consultaPuntosParIniciales( odbcTiendaNumero, false );
	consultaPuntosParIniciales.agregarCampoEntero( "puntospariniciales", DT_ENTERO );

	if( consultaPuntosParIniciales.Exec( cSql ) )
	{
		consultaPuntosParIniciales.activarCols();
		if( consultaPuntosParIniciales.Leer() )
		{
			iPuntosParIniciales = consultaPuntosParIniciales.valorLong( "puntospariniciales" );
			mysnprintf( cSql,sizeof(cSql), "iPuntosParIniciales [%d]", iPuntosParIniciales);
			////logx( csql, _LOGINFO_);
		}
	}
	else
	{
		// consultaPuntosParIniciales.odbc->GetLastError( consultaPuntosParIniciales.GetHstmt() );
		// grabarError( consultaPuntosParIniciales.odbc, "CGrabarNC", "consultaDatosGndominio", "Error al consultar Puntos Iniciales", cSql );
		mysnprintf( cLog,sizeof(cSql), "Error al consultar consultaPuntosParIniciales. [%.150s]", consultaPuntosParIniciales.error() );
		logx( cLog, _LOGINFO_);
	}

	return iPuntosParIniciales;
}

void consultarCrParametricoAR(C_ODBC *odbcTiendaNumero, int iDiasTransUltcompra, int iAntMeses, long lPtjCompra, int &iPtsSaturacion, int &iPtsAntiguedad, int &iPtsUltCompra, int iTipoVenta, char cPuntualidad, int iFlagTestigoAR)
{
	char cSql[300] = {0}, cLog[255] = {0};

	CRegistro ptosTienda( odbcTiendaNumero, false );
	ptosTienda.agregarCampoEntero( "iPtsUltCompra", DT_ENTERO );
	ptosTienda.agregarCampoEntero( "iPtsAntiguedad", DT_ENTERO );
	ptosTienda.agregarCampoEntero( "iPtsSaturacion", DT_ENTERO );

	mysnprintf(cSql,sizeof(cSql), "select iPtsUltCompra, iPtsAntiguedad, iPtsSaturacion from tdConsultarPtosGnDominio01('%d', '%d', '%d', '%d', '%c','%d')", iDiasTransUltcompra, iAntMeses, lPtjCompra, iTipoVenta, cPuntualidad, iFlagTestigoAR);
	////logx( csql, _LOGINFO_);

	if ( ptosTienda.Exec(cSql) )
	{
		ptosTienda.activarCols();
		if ( ptosTienda.Leer() )
		{
			iPtsUltCompra = ptosTienda.valorLong( "iPtsUltCompra" );
			iPtsAntiguedad = ptosTienda.valorLong( "iPtsAntiguedad" );
			iPtsSaturacion = ptosTienda.valorLong( "iPtsSaturacion" );
			mysnprintf( cSql,sizeof(cSql), "iPtsUltCompra [%d], iPtsAntiguedad [%d], iPtsSaturacion [%d]", iPtsUltCompra, iPtsAntiguedad, iPtsSaturacion);
			////logx( csql, _LOGINFO_);
		}
	}
	else
	{
		// ptosTienda.odbc->GetLastError( ptosTienda.GetHstmt() );
		// grabarError( ptosTienda.odbc, "CGrabarNC", "consultaDatosGndominio", "ERROR AL CONSULTAR PUNTAJES DE TDPARAMETRICOALTORIESGO", cSql );
		mysnprintf( cLog,sizeof(cSql), "Error al consultar ptosTienda. [%.150s]", ptosTienda.error() );
		logx( cLog, _LOGINFO_);
	}
}

void obtenerFechaPrimerCompraCR(C_ODBC *odbcCartera, int iNoCliente, char* cFechaPrimerCompraCR)
{
	char cSql[255] = {0}, cLog[255] = {0};

	mysnprintf( cSql,sizeof(cSql), "SELECT fecha FROM crDescuentoPrimerCompra WHERE cliente = %ld", iNoCliente);
	////logx( csql, _LOGINFO_);

	CRegistro fechaprim( odbcCartera, false );
	fechaprim.agregarCampoFecha("fecha");

	if( fechaprim.Exec( cSql ) )
	{
		fechaprim.activarCols();
		if( fechaprim.leer() )
		{
			SqlTimeStamp *tFecha = fechaprim.valorFecha("fecha");
			mysnprintf( cFechaPrimerCompraCR,11, "%04d%02d%02d", tFecha->ano(), tFecha->mes(), tFecha->dia() );
			logx( cFechaPrimerCompraCR, _LOGINFO_);

			mysnprintf( cSql,sizeof(cSql), "cFechaPrimerCompraCR [%04d%02d%02d]", tFecha->ano(), tFecha->mes(), tFecha->dia() );
			////logx( csql, _LOGINFO_);
		}
	}
	else
	{
		// sucesoLog("Error al consultar obtenerFechaPrimerCompraCR");
		// fechaprim.odbc->GetLastError(fechaprim.GetHstmt());
		// grabarError( fechaprim.odbc, "GrabarNC", "obtenerFechaPrimerCompraCR()", "Consultar la fecha de la primer compra del cliente.", cSql );
		mysnprintf( cLog,sizeof(cSql), "Error al consultar obtenerFechaPrimerCompraCR. [%.150s]", fechaprim.error() );
		logx( cLog, _LOGINFO_);
	}
}

void eliminarEspacioBlanco( char *cTexto, int iCantidad )
{
	for(int iPos = 0; iPos < iCantidad; iPos++)
	{
		if( cTexto[iPos] == 32 )
		{
			cTexto[iPos] = 0;
		}
	}
}

bool consultarFolio( C_ODBC *conexionLocal,int iTipoFolio,sRespuestaServicio *sRespuesta )
{
	bool bContinuar = false; 
	char cSql[128] = {0};
	char log[256] = {0};
	long lFolio = 0;
	int iModo = 2;
	
	logx( "Entro en consultarFolio", _LOGINFO_);
	if ( iTipoFolio == FOLIOM_CONTFACTURAPENDIENTE )
	{
		iModo = 0;
	}

	if ( iTipoFolio ==  FOLIO_PRESUPUESTO_PROTHEUS )
	{
		  lFolio = incrementarFolio( 0, "0", 0, iTipoFolio, conexionLocal, cSql, bContinuar );		 	
		
		
		if ( bContinuar )
		{
			logx( "entro dentro de bContinuar", _LOGINFO_);
			sRespuesta->sSysMuebles.lFolio = lFolio;
		}
		else
		{
			mysnprintf(log,sizeof(log), "consultarFolio %.128s Error al obtener los folios",cSql );
			logx( log, _LOGINFO_);			
		}
	}
	else
	{
		 lFolio = incrementarFolio( iModo, "M", 0, iTipoFolio, conexionLocal, cSql, bContinuar );
		mysnprintf( cSql,sizeof(cSql), "este es el ifolio bien %d",lFolio );
		////logx( csql, _LOGINFO_);
		if ( bContinuar )
		{
			if ( iTipoFolio == FOLIOM_CONTFACTURAPENDIENTE )
			{
				sRespuesta->sSysMuebles.iContFacturaPendiente = (short)lFolio;
			}
			else
			{
				sRespuesta->sSysMuebles.lFolioFacturaPendiente = lFolio;
			}
		}
		else
		{
			mysnprintf(log,sizeof(log), "consultarFolio %.128s Error al obtener los folios",cSql );
			 logx( log, _LOGINFO_);
		}
	}

	return bContinuar;
}

long incrementarFolio( int iFlagIncremento, char *cArea, int iCaja, int iTipoFolio, C_ODBC *xodbc, char *cSqlTxt, bool &bConsulta )
{
	logx( "entro a incrementarFolio()", _LOGINFO_);
	// iFlagIncremento   0=No Incrementar, 1=Incrementar
	long lFolio = 0L;
	char log[256] = {0};

	bConsulta = true;

    mysnprintf( cSqlTxt,80, "SELECT gnincrementarfolio( '%.3s', '%d', '%d', '%d' )", cArea, iCaja, iTipoFolio, iFlagIncremento );
	//logx( csqlTxt, _LOGINFO_);
	CRegistro obtenerFolio( xodbc, false );
	obtenerFolio.agregarCampoEntero( "folio", DT_ENTERO_LARGO );

	if ( obtenerFolio.Exec( cSqlTxt ) )
	{
		obtenerFolio.activarCols();
		if ( obtenerFolio.Leer() )
		{
			lFolio = obtenerFolio.valorLong( "folio" );
		}
	}
	else
	{
		mysnprintf(log,sizeof(log),"Error en la consulta %.128s",cSqlTxt );
		logx( log, _LOGINFO_);
		bConsulta = false;
	}

	return lFolio;
}

bool consultarFlagTdaVentaHuella( C_ODBC *xOdbcTda, int &iFlagTdaVentaHuella, char *cSql )
{	
	char log[256] = {0};
	bool bRespuesta = false;

	mysnprintf( cSql,50, "SELECT gnConsultarFlag( '0', '%d' )", FLAG_VENTACONHUELLA );
	////logx( csql, _LOGINFO_);

	CRegistro xFlagTdaVtaHue(xOdbcTda);
	xFlagTdaVtaHue.agregarCampoEntero( "iFlagVtaHuella", DT_ENTERO_CORTO );

	if ( xFlagTdaVtaHue.Exec(cSql) )
	{
		xFlagTdaVtaHue.activarCols();
		if ( xFlagTdaVtaHue.leer() )
		{
			bRespuesta = true;
			iFlagTdaVentaHuella = xFlagTdaVtaHue.valorShort("iFlagVtaHuella");
			mysnprintf(log,sizeof(log),"este es el valor: %ld",iFlagTdaVentaHuella );
			logx( log, _LOGINFO_);

		}
	}
	else
	{
		// Se obtiene el error
		mysnprintf(log,sizeof(log),"%s","Error DE CONEXION EN LA FUNCION consultarFlagTdaVentaHuella()");
		logx( log, _LOGINFO_);
		bRespuesta = false;
	}

	return bRespuesta;
}


long verificarUltimaNota( C_ODBC *odbcTiendaNumero, int iTipoFolio, int iCaja )
{	
	long lUltimaNota = -1;
    char cLog[512] = {0}, cSql[512] = {0};

	mysnprintf( cSql,512, "SELECT roVerificarUltimaNota( '%d', '%d')", iTipoFolio, iCaja );
	////logx( csql, _LOGINFO_);
    CRegistro nota( odbcTiendaNumero );

    nota.agregarCampoEntero("roVerificarUltimaNota",DT_ENTERO_LARGO);

	if( nota.Exec( cSql ) )
	{
		nota.activarCols();

		if( nota.Leer() )
		{            
			lUltimaNota = nota.valorLong("roVerificarUltimaNota");
		}
	}	
	else
	{		
		mysnprintf( cLog,sizeof(cLog),"%s", "Error al consultar " );
		logx( cLog , _LOGINFO_);			
	}

	return lUltimaNota;
}

double consultarFactorTasasDiferenciadas(C_ODBC *odbcCartera, sRespuestaServicio *sRespuesta, long lCliente)
{
	double fRegresa = 1;
	char cSql[256] = {0};				
	long iPorcentajePcTasasDiferenciadas = 0;
	
	CRegistro CObtenerFactorTasasDiferenciadas( odbcCartera );    

	mysnprintf(cSql,sizeof(cSql),"Select fvalorfactor,porcentajepc from fun_obtenerfactortasasdiferenciadas(%ld,'M')",lCliente);
	////logx( csql, _LOGINFO_);
	
	CObtenerFactorTasasDiferenciadas.agregarCampoDecimal("fvalorfactor",DT_DOBLE);
	CObtenerFactorTasasDiferenciadas.agregarCampoEntero("porcentajepc",DT_ENTERO_CORTO);	
	if(CObtenerFactorTasasDiferenciadas.Exec(cSql))
	{
		CObtenerFactorTasasDiferenciadas.activarCols();
		if(CObtenerFactorTasasDiferenciadas.leer())
		{
			 sRespuesta->iPorcentajeTasasDiferenciadas = (int)(CObtenerFactorTasasDiferenciadas.valorDouble("fvalorfactor") * 100);
			 iPorcentajePcTasasDiferenciadas = CObtenerFactorTasasDiferenciadas.valorShort( "porcentajepc" );
			 fRegresa = CObtenerFactorTasasDiferenciadas.valorDouble("fvalorfactor");
		}
	}
	else
	{
		logx( "ERROR EN  consultarFactorTasasDiferenciadas()", _LOGINFO_);
		mysnprintf(sRespuesta->cMensaje,255,"%s","ERROR EN  consultarFactorTasasDiferenciadas()"); 		
	}

	return fRegresa;
}

bool esCiudadQuePercibe(C_ODBC *conexionCartera, int iCiudad)
{	
	char cSql[128] = {0}, cLog[128] = {0};
	bool bRegresa = false;
	
	CRegistro consultaSQL( conexionCartera );
	consultaSQL.agregarCampoEntero("percibeib",DT_ENTERO);

	mysnprintf( cSql,sizeof(cSql), "SELECT percibeib FROM crCiudadPercepcionIB WHERE ciudad = %ld;", iCiudad);

	if ( consultaSQL.Exec( cSql ))
	{
		consultaSQL.activarCols();
		if ( consultaSQL.Leer() )
		{			
			if(consultaSQL.valorLong("percibeib") == 1)
			{
				bRegresa = true;
			}
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cSql), "ERROR AL BUSCAR LA CIUDAD DENTRO DEL IIBB. ERROR=> [%.150s]", consultaSQL.error() );
		logx( cLog, _LOGINFO_);
		bRegresa = false;
	}

	return bRegresa;	
}

bool obtenerImporteVtaSinImpuestosRopa(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud)
{
	bool bContinuar = true , bContinuarDescuento = true;
	char cLog[300] = {0};
	int iCodigo = 0 , iImporte = 0 , iCantidad = 0 , iValorDescuento = 0;
	long lIIBBPercepcionImpresion = 0L, lPercepcion = 0L, lIIBBPercepcionSum = 0L, lIIBBPercepcionACobrar = 0L;
	float fValorNetoCodigo = 0;

	logx( "Inicia obtenerImporteVtaSinImpuestosRopa()", _LOGINFO_);

	mysnprintf ( cLog,sizeof(cLog), "sSolicitud->iTotalArticulos %d,", sSolicitud->iTotalArticulos );
	logx( cLog, _LOGINFO_);

	for( int iCon = 0; iCon < sSolicitud->iTotalArticulos && bContinuar == true ; iCon++ )
	{
		logx("Entro a 1er for", _LOGINFO_);
		iCantidad		= 1;
		iCodigo 		= sSolicitud->lstProductos[iCon].iCodigo;
		iImporte 		= sSolicitud->lstProductos[iCon].lPrecio;
		iValorDescuento = sSolicitud->lstProductos[iCon+1].lImporteDescuento;

		mysnprintf ( cLog,sizeof(cLog), "iCodigo: %d, iImportee: %d, iValorDescuento: %d,", iCodigo, iImporte, iValorDescuento );
		logx( cLog, _LOGINFO_);

		bContinuarDescuento = true;
		for( int iContDesc = iCon+1 ; iContDesc < sSolicitud->iTotalArticulos && bContinuarDescuento == true ; iContDesc++ )
		{ // DESCUENTOS EN ROPA
			logx("Entro a 2do for", _LOGINFO_);
			iValorDescuento  = sSolicitud->lstProductos[iContDesc].lImporteDescuento;
			
			if(iValorDescuento > 0 )
			{						
				iImporte -= abs ( iValorDescuento ) ;
			}
			else
			{
				bContinuarDescuento = false;
			}
		}

		if ( iCantidad == 1 )
		{
			logx("Entro a iCantidad == 1", _LOGINFO_);

			mysnprintf( cLog,sizeof(cLog), "fValorNetoCodigo: %f", sRespuesta->fValorNetoCodigo );
			logx( cLog, _LOGINFO_);
			
			mysnprintf( cLog,sizeof(cLog), "lImporteVtaSinImpuestosRopa: %lld", sRespuesta->lImporteVtaSinImpuestosRopa );
			logx( cLog, _LOGINFO_);
			
			bContinuar = obtenerValorNetoArticulo( odbcTiendaNumero, sRespuesta, iCodigo, iImporte );
			
			lPercepcion =  (((sRespuesta->fValorNetoCodigo *  sRespuesta->sDatosCreditoRopaRes.fAlicuota) / 10000 ) + 0.005 ) * 100;
			lIIBBPercepcionSum += lPercepcion;
			mysnprintf( cLog,sizeof(cLog), "lPercepcion: %ld, lIIBBPercepcionSum: %ld", lPercepcion, lIIBBPercepcionSum );
			logx( cLog, _LOGINFO_);

			sRespuesta->lImporteVtaSinImpuestosRopa += (sRespuesta->fValorNetoCodigo * 1000000) ;// valor neto total
			
			mysnprintf( cLog,sizeof(cLog), "fValorNetoCodigo: %f", sRespuesta->fValorNetoCodigo );
			logx( cLog, _LOGINFO_);
			
			mysnprintf( cLog,sizeof(cLog), "lImporteVtaSinImpuestosRopa: %lld", sRespuesta->lImporteVtaSinImpuestosRopa );
			logx( cLog, _LOGINFO_);
			//NOTA.- Se multiplica por 1,000,000 para obtener el total de importe sin IVA mas proximo al que calcula la impresora				
		}
	}
	lIIBBPercepcionImpresion = (((double)(sRespuesta->lImporteVtaSinImpuestosRopa/10000) * sRespuesta->sDatosCreditoRopaRes.fAlicuota)/10000) + 0.5;// Se obtiene el valor lo mas exacto a la impresora para realizar el ajuste entre los articulos	

	/*while  (lIIBBPercepcionImpresion != lIIBBPercepcionSum )
	{// Ajustar percepcion en items
		mysnprintf( cLog,sizeof(cLog), "Son diferentes lIIBBPercepcionImpresion: %ld y lIIBBPercepcionSum: %ld", lIIBBPercepcionImpresion, lIIBBPercepcionSum );
		logx( cLog, _LOGINFO_);
		//ajustarImporteIIBBItems(lIIBBPercepcionImpresion, lIIBBPercepcionSum);				PENDIENTE NOAR		
	}*/

	lIIBBPercepcionACobrar = lIIBBPercepcionImpresion / 100;//Se cobra sin decimales, todo a favor del cliente.
	
	sRespuesta->lIIBBPercepcionImpresionRopa = lIIBBPercepcionImpresion;
	sRespuesta->lIIBBPercepcionACobrarRopa =lIIBBPercepcionACobrar;

	mysnprintf( cLog,sizeof(cLog), "Valores a regresar de lIIBBPercepcionImpresion: %ld y lIIBBPercepcionACobrar: %ld", lIIBBPercepcionImpresion, lIIBBPercepcionACobrar );
	logx( cLog, _LOGINFO_);

	logx("Termina obtenerImporteVtaSinImpuestosRopa()", _LOGINFO_);
	
	return bContinuar;
}

bool obtenerValorNetoArticulo( C_ODBC *odbcTiendaNumero,sRespuestaServicio *sRespuesta, int iCodigo, int iPrecio ) 
{
	char cSql[128] = {0};
	char cLog[128] = {0};
	bool bcontinuar = true;

	logx( "Inicia obtenerValorNetoArticulo()", _LOGINFO_);

	mysnprintf( cSql,sizeof(cSql), "SELECT tdObtenerCostoNeto( %d, %d, 1 , '0' , '0');", iCodigo, iPrecio) ;
	////logx( csql, _LOGINFO_);

	CRegistro costoNeto( odbcTiendaNumero );

    costoNeto.agregarCampoDecimal("roVerificarUltimaNota",DT_FLOTANTE);

	if ( costoNeto.Exec(cSql) )
	{		
		costoNeto.activarCols();

		if ( costoNeto.Leer() )
		{
			sRespuesta->fValorNetoCodigo = costoNeto.valorFloat("roVerificarUltimaNota");	
			bcontinuar = true ;
			
			mysnprintf( cLog,sizeof(cLog), "obtenerValorNetoArticulo.fValorNetoCodigo: %f", sRespuesta->fValorNetoCodigo );
			logx( cLog, _LOGINFO_);
		}
	}
	else
	{
		 bcontinuar = false;
		 mysnprintf( cLog,sizeof(cLog), "%s", "ERROR AL EJECTUAR EL QUERY "); 
		 logx( cLog, _LOGINFO_);
	}

	logx("Termina obtenerValorNetoArticulo()", _LOGINFO_);

	return bcontinuar;	
}

bool consultarIpServidores( C_ODBC *xOdbc, char *cIpServidor, char *cIpServidorAlterno, short iTipoServidor, char *cSql)
{
	char sDato[32] = {0},cLog[512]={0};
	bool bContinuar = false;

	mysnprintf( cSql,80, "SELECT ipservidor, ipalterno FROM sysservidores WHERE tiposervidor=%d", iTipoServidor );

	CRegistro xServidorSQL(xOdbc,false );

	xServidorSQL.agregarCampoChar( "ipservidor", 256 );
	xServidorSQL.agregarCampoChar( "ipalterno", 256 );

	if ( xServidorSQL.Exec(cSql) )
	{
		xServidorSQL.activarCols();

		if ( xServidorSQL.Leer() )
		{
			/*sDato.Format( "%.15s", xServidorSQL.ipservidor );
			sDato.Trim();
            mysnprintf( cIpServidor,sizeof(cIpServidor), "%s", sDato );

			sDato.Format( "%.15s", xServidorSQL.ipalterno );
			sDato.Trim();
            mysnprintf( cIpServidorAlterno,sizeof(cIpServidorAlterno), "%s", sDato );
			*/

			//iRespuesta = _OK_;
			mysnprintf( cIpServidor,17, "%.17s", xServidorSQL.valorChar( "ipservidor" ) );
			//iRespuesta = _OK_;
			mysnprintf( cIpServidorAlterno,17, "%.17s", xServidorSQL.valorChar( "ipalterno" ) );

			bContinuar = true;
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar IP. [%.150s]", xServidorSQL.error() );
		logx( cLog , _LOGINFO_);	
		bContinuar = false;
	}

	return bContinuar;
}

int ano_2000_4dig( int ano, int anioactual )
{
	int aa;

	aa=ano;

    if ( ano>999 )
    {
        //A¤o de 4  d¡gitos
    }
    else
    {
        if ( ano<((anioactual-2000)+10) )
        {
            aa=ano+2000;
        }
        else
        {
            aa=ano+1900;
        }
    }
    return( aa );
}

int obtenerNumCiudadApartado(C_ODBC *odbcTiendaNumero)
{
	char cSql[255] = {0}, cLog[255] = {0};
	int iRespuesta;

	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT numciudadapartado FROM gndominio" );
	////logx( csql, _LOGINFO_);

	CRegistro puntos( odbcTiendaNumero , false);
	puntos.agregarCampoEntero("numciudadapartado", DT_ENTERO);

	if( puntos.Exec( cSql ) )
	{
		puntos.activarCols();
		if( puntos.leer() ) {
			iRespuesta = puntos.valorLong( "numciudadapartado" );
		}
	}
	else
	{
		// puntos.odbc->GetLastError(puntos.GetHstmt());
		// grabarError( puntos.odbc, "PagoInicialNC", "calcularPI()", "Consultar los puntos iniciales de ropa.", cSql );
		mysnprintf( cLog,sizeof(cSql), "Error al consultar obtenerNumeroCiudadapartado. [%.150s]", puntos.error() );
		logx( cLog, _LOGINFO_);
	}

	return iRespuesta;
}

int verificarPrecioCodigo(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, long lCodigo, int iTalla, int iPrecio, int iCantidad, int iTienda, int iCaja, char cTipoMovto, bool bCommit)
{
	int iRespuesta = -1;
	char sSql [ TAM_MED_BUFF ] = {0};
	char sMovimiento;
	char sMensaje[250] = {0};
	long lEmpleado = 0; 
	int iTipo = 0; 
	bool bFlagHuella = false;
	sRespuesta->iPedirHuella = 0;
	sRespuesta->status = _MENSAJE_CORRECTO_;

	// fecha de la gndominio
    // obtenerFechaGnDominio( odbcTiendaNumero, cFecha, iDia, iMes, iAnio, cSql, TRUE );

	sMovimiento = cTipoMovto;

	/*
	INCREMENTAN							DISMINUYEN
	S-surtidos			 				U-Dif Surtido(-)
	D-Devolucion de venta -(V)			V-venta + (V)
	t-Transferencias Canceladas			T-Transferencia
	U-Dif surtido(+)
	v-Venta Canceladas 

	----------------------------------------------------------------------------------------------
	-- I-inventarios -No generan movimiento en la tabla romovimientosrebaja , pero si registro en
	-- la tabla tdautorizacionhuellaprecio.
	----------------------------------------------------------------------------------------------

	*/
	if ( iCantidad >= 0 )
	{
		iCantidad = 1;
	}
	else
	{
		iCantidad = -1;
	}

	if (sMovimiento == 'I' )
	{
		iTipo = 2; // Inventarios
	}
	else if (( sMovimiento == 'U' || sMovimiento == 'V' || sMovimiento == 'T') && iCantidad == 1)
	{
		iTipo = 0;
	}
	else if (( sMovimiento == 'S' || sMovimiento == 'D' || sMovimiento == 'V' || sMovimiento == 't' || sMovimiento == 't' || sMovimiento == 'U' || sMovimiento == 'v' )
		&& iCantidad == -1 )
	{
		 iTipo = 1 ; 
	}

	CRegistro verificar( odbcTiendaNumero , bCommit);
	verificar.agregarCampoEntero("roverificarprecio", DT_ENTERO);

	mysnprintf(sSql,sizeof(sSql), "SELECT roverificarprecio('%ld', '%d', '%d', '%d' , '%d', '%d')", lCodigo, iTalla, iPrecio, iTipo , iTienda , iCaja );
	logx( sSql , _LOGINFO_);

	if ( !verificar.Exec(sSql) )
	{
		sRespuesta->status = _ERROR_DE_SERVIDOR;
		mysnprintf(sRespuesta->cMensaje,255,"%s", "OCURRIO UN ERROR AL EJECUTAR roverificarprecio");
		logx( sRespuesta->cMensaje, _LOGINFO_);

		sRespuesta->iDevStatus = _ERROR_QUERY_;
		mysnprintf(sRespuesta->cDevMensaje,255,"ERROR AL EJECUTAR EL QUERY... '%.200s'", verificar.error() );
		logx( sRespuesta->cDevMensaje, _LOGINFO_);
	}
	else
	{
		verificar.activarCols();

		if( verificar.Leer() )
		{
			iRespuesta = verificar.valorLong( "roverificarprecio" );
		}
		mysnprintf(sMensaje,sizeof(sMensaje), "roverificarprecio: iRespuesta [%d]", iRespuesta);
		logx( sMensaje, _LOGINFO_);
		mysnprintf(sRespuesta->cMensajeHuella,sizeof(sRespuesta->cMensajeHuella), "%.128s", sMensaje);
		sRespuesta->iPedirHuella = iRespuesta;
		// if ( iRespuesta != -1 )
		// {
		// 	if( iRespuesta != 0 )
		// 	{
		// 		if ( iRespuesta == 1 )
		// 		{
		// 			if(	iTipo == 2 )// Inventarios
		// 			{// Se solicita huella de empleado ya que no hay gerentes en el inventarios (indica Maximimiano Soler)
		// 				mysnprintf(sMensaje,sizeof(sMensaje)," El precio capturado es mayor que el precio permitido se requiere autorizacion de Empleado para continuar ");
		// 			}
		// 			else
		// 			{
		// 				mysnprintf(sMensaje,sizeof(sMensaje)," El precio capturado es mayor que el precio permitido se requiere autorizacion de Gerente para continuar ");
		// 			}
		// 			logx( sMensaje , _LOGINFO_);
		// 			mysnprintf(sRespuesta->cMensajeHuella, "%s", sMensaje);
		// 			sRespuesta->iPedirHuella = 1;
		// 		}
		// 		else if ( iRespuesta == 2 )
		// 		{
		// 			if(	iTipo == 2 )// Inventarios 
		// 			{// Se solicita huella de empleado ya que no hay gerentes en el inventarios (indica Maximimiano Soler)
		// 				mysnprintf( sMensaje, " El precio capturado es menor que el precio permitido se requiere autorizacion de Empleado para continuar ");
		// 			}
		// 			else
		// 			{
		// 				mysnprintf( sMensaje, " El precio capturado es menor que el precio permitido se requiere autorizacion de Gerente para continuar ");
		// 			}
		// 			logx( sMensaje , _LOGINFO_);
		// 			mysnprintf(sRespuesta->cMensajeHuella, "%s", sMensaje);
		// 			sRespuesta->iPedirHuella = 1;
		// 		}
		// 		else if ( iRespuesta == 3 )
		// 		{
		// 			// verificarPrecioCodigoAgregarTMP( odbcTiendaNumero ,cTipoMovto, lCodigo, iTalla, iPrecio , iCantidad , 
		// 			// 	iTienda, iCaja, lEmpleado , 1, iAnio, iMes, iDia , cFolioMovimiento, lCodigoAnt, iTallaAnt,
		// 			// 	iPrecioAnt);

		// 			bFlagHuella = false;
		// 			iRespuesta = 0;
		// 		}

		// 		if ( bFlagHuella == true )
		// 		{
		// 			if(	iTipo == 2 )// Inventarios 
		// 			{// Se solicita huella de empleado ya que no hay gerentes en el inventarios (indica Maximimiano Soler)
		// 				// validarHuellaEmpleadoGte( odbcTiendaNumero, lEmpleado,3, MOVTO_GTERECAPTURAHUELLA ,0, iTienda , 2, iCaja);  //gnwvahue.cpp
		// 			}
		// 			else
		// 			{
		// 				// validarHuellaEmpleadoGte( odbcTiendaNumero, lEmpleado,1, MOVTO_GTERECAPTURAHUELLA ,0, iTienda , 2, iCaja);  //gnwvahue.cpp
		// 			}

		// 			if( lEmpleado > 90000000 )
		// 			{
		// 				// verificarPrecioCodigoAgregarTMP( odbcTiendaNumero ,cTipoMovto, lCodigo, iTalla, iPrecio , 1 , iTienda, 
		// 				// 			iCaja, lEmpleado , 1, iAnio, iMes, iDia , cFolioMovimiento, lCodigoAnt, iTallaAnt,
		// 				// 			iPrecioAnt);

		// 				iRespuesta = 0;

		// 			}
		// 			else
		// 			{
		// 				iRespuesta = -2;
		// 			}
		// 			bFlagHuella = false;
		// 		}
		// 	}
		// 	else if ( lCodigoAnt > 0 )
		// 	{
		// 		// verificarPrecioCodigoBorrarTMP( odbcTiendaNumero ,cTipoMovto, lCodigoAnt, iTallaAnt, iPrecioAnt, iTienda, 
		// 		// 			iCaja, cFolioMovimiento);
		// 	}
		// }
	}

	return iRespuesta;
}

bool roVerificarPrecioAgregaBorrarAutorizacion(C_ODBC *odbcTiendaNumero, char cMovimiento, long lCodigo, int iTalla, int iPrecio, int iCantidad, int iTienda, int iCaja, long lEmpleado, 
	int iFlagHuella, int iAnio, int iMes, int iDia, char *cFolioMovimiento, char cTipo, long lCodigoAnt, int iTallaAnt, int iPrecioAnt)
{
	bool bRespuesta;
	char cSql [ TAM_MED_BUFF ] = {0},cLog[ TAM_MIN_BUFF ] = {0};

	CRegistro roVerificarAutorizacion( odbcTiendaNumero);
	roVerificarAutorizacion.agregarCampoEntero("roverificarprecioagregaborrarautorizacion", DT_ENTERO);

	mysnprintf(cSql,sizeof(cSql), "SELECT roverificarprecioagregaborrarautorizacion( '%c', '%ld', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%.04d%.02d%.02d', '%.20s', '%c', '%d', '%d', '%d' );",
		cMovimiento, lCodigo, iTalla, iPrecio, iCantidad, iTienda, iCaja, lEmpleado, iFlagHuella, iAnio, iMes, iDia, cFolioMovimiento, cTipo, lCodigoAnt, iTallaAnt, iPrecioAnt);
	////logx( csql, _LOGINFO_);

	if( roVerificarAutorizacion.Exec( cSql ) )
	{
		bRespuesta = true;
	}
	else
	{
		mysnprintf( cLog,sizeof(cSql), "Error al consultar roVerificarPrecioAgregaBorrarAutorizacion. [%.150s]", roVerificarAutorizacion.error() );
		logx( cLog, _LOGINFO_);
	}

	return bRespuesta;
}

bool ActualizarPuntosCoppel( C_ODBC *xOdbcCartera, long lCliente, int iNuevosPuntos, bool bEsCancelacion, int iMesesVigencia, long lFactura, int iTienda)
{
	char cSql[256]={0},  cSql2[256] ={0};
	bool bRegresa = true;

	CRegistro ActualizaCliente( xOdbcCartera, false);
    
    if (iNuevosPuntos != 0)
	{
		mysnprintf( cSql2,sizeof(cSql2), "select verificacrdineroelectronico(%ld)", lCliente );
	}
	
    ActualizaCliente.Exec( cSql2 );

	if(bEsCancelacion == true || iNuevosPuntos <= 0)
	{ //No actualiza la fecha
		mysnprintf( cSql,sizeof(cSql), "SELECT actualizarmegapuntoscoppel(%ld, %ld)", iNuevosPuntos, lCliente);
	}
	else if(iNuevosPuntos > 0)
	{ //Actualiza la fecha
		mysnprintf( cSql,sizeof(cSql), "SELECT actdevolucionmegapuntos(%ld, %ld, %ld, %ld, %ld)", iNuevosPuntos, lCliente, iMesesVigencia, lFactura, iTienda);
	}

	CRegistro ActualizaSaldo( xOdbcCartera, false);
	
	if ( !ActualizaSaldo.Exec( cSql ) )
	{
		// bRegresa = false;
		// ActualizaSaldo.odbc->GetLastError( ActualizaSaldo.GetHstmt());
	}

	return bRegresa;
}

int ConsultarCuentaReestriccion(C_ODBC *odbcDBTiendaNumero, int iTienda, long lCliente, int iTiendaLocal)
{
	logx( "ConsultarCuentaReestriccion", _LOGINFO_);
	C_ODBC odbcCartera;
	char cMensajeReest[150] = {0};
	char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20]={0}, cIpBdServidor[20] = {0},cSqlTxt[256] = {0};
	long iRetorna = 0L;
	char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
	int iRespuesta = 0;

	logx( "Va a entrar a abrir conexiones", _LOGINFO_);	

	    	// if (consultarIpServidor( odbcDBTiendaNumero, SERV_CARTERA , cIpBdServidor ) == 1)
			// {
            //     if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,iTienda))
				iRespuesta = consultarSEC(_SEC_CARTERA, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
				if( iRespuesta == _OK_ )
                {
                    //iRespuesta = abrirConexion( &odbcCartera,cIpBdServidor,cNombreBD,cUsuarioBD );
					iRespuesta = abrirConexion2( &odbcCartera, cDNS, cBd, cUser, cPss );
                    if (iRespuesta == _OK_)
                    {
						
						logx( "Entro a abrir conexion", _LOGINFO_);
						CRegistro consultaSQL( &odbcCartera);												
				
						mysnprintf(cSqlTxt,sizeof(cSqlTxt),"SELECT clv_cuenta_reest FROM crcliente WHERE cliente = %ld", lCliente); 
						consultaSQL.agregarCampoEntero("clv_cuenta_reest", DT_ENTERO);
						if ( !consultaSQL.Exec(cSqlTxt) )
						{							
							mysnprintf(cMensajeReest,sizeof(cMensajeReest),"%s", "Fallo al ejecutar la consulta");
							logx( cMensajeReest, _LOGINFO_);
						}
						else 
						{
							consultaSQL.activarCols();
							if ( consultaSQL.Leer() )
							{									
								iRetorna = consultaSQL.valorLong("clv_cuenta_reest");
								mysnprintf(cMensajeReest,sizeof(cMensajeReest),"Hizo exitosamente la consulta - %ld",iRetorna);
								logx( cMensajeReest, _LOGINFO_);
							}
							else
							{
								mysnprintf(cMensajeReest,sizeof(cMensajeReest),"%s", "Fallo al ejecutar la consulta 2");
								logx( cMensajeReest, _LOGINFO_);
							}
						}
					}
					else
					{
							logx("Fallo al abrir conexion al servidor de cartera", _LOGINFO_);
					}
				}
				else
				{
					logx("No se logro establecer conexión con el SEC - gnfunciones::ConsultarCuentaReestriccion", _LOGINFO_);
				}
			// }
			// else
			// {
			// 		logx("Fallo al consultar al servidor de cartera");
			// }

	return iRetorna;

}
/*void padStart(sRespuestaServicio *sRespuesta,char *valor)
{
	short longitudValor = mystrnlen(valor);
	short longitudTiendaNube = 11;

	short MascaraDeCeros = longitudTiendaNube - longitudValor;
	char Regresa[15] = {'\0'};
	
	for (short i = 0; i < MascaraDeCeros;i++) Regresa[i] = '0';

	if (longitudValor > 1) {
		short x2 = 0;
		for (short x = MascaraDeCeros; x < longitudTiendaNube; x++)
		{
			Regresa[x] = valor[x2];
			x2++;
		}
	}
	mysnprintf(sRespuesta->padStart,15, "%.15s", Regresa);
}*/
void padStart(sRespuestaServicio *sRespuesta,char *valor)
{
    logx( valor, _LOGINFO_);
    int totalCaracteres = mystrnlen(valor );
    short cerosPoner = 0;
    char valorRegreso[15] = {0};    
    short iContador = 0;

    char test[256] = {0};
    mysprintf(test,"%d",totalCaracteres);    
	
    cerosPoner = 11 - totalCaracteres;

     for (short i = 0; i < cerosPoner; i++)
     {
         valorRegreso[i] = '0';
         
     }

     for (short x = cerosPoner; x < 11; x++)
     {
		if( x <= sizeof(valorRegreso))  
        {
            valorRegreso[x] = valor[iContador];
            iContador++;
        }
     }
     
   mysprintf(sRespuesta->padStart,"%s" , valorRegreso);
}


int confirmarTransaccionFE( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta )
{
    logx( "entro en la funcion confirmarTransaccionFE()", _LOGINFO_);
    char cTexto[128] = {0}, cURL[128] = {0};
    char cLog[512] = {0};
    int iJson = SOAP_ERR;
    int iRespuesta = _ERROR_QUERY_;    
    
    soap *soapFE = soap_new1( SOAP_C_UTFSTRING );
	value vSolicitudJson( soapFE );

    soapFE->double_format = "%.2lf";	 
    mysnprintf( cURL,sizeof(cURL), "http://%.17s:8078/api/comprobantes/ackcomprobante", sSolicitud->cIPwshasar );
    logx( cURL, _LOGINFO_);

    vSolicitudJson["nroCaja"] = sSolicitud->iCaja;
    vSolicitudJson["nroSucursal"] = sSolicitud->iNroSucursal;
    vSolicitudJson["ultimoNroTransaccion"] = sSolicitud->cUltimoNroTransaccion;

    displayJson( &vSolicitudJson );
    logx( "Conectando a WS de FE..." , _LOGINFO_);
    
    iJson = json_call( soapFE, cURL, &vSolicitudJson, NULL );
    
    mysnprintf( cTexto,sizeof(cTexto), "Respuesta de WS %d", iJson );
    logx( cTexto , _LOGINFO_);    

    if( iJson == 200 )  //HTTP Status 200 OK
    {
        iRespuesta = _OK_;
    }
    else
    {             
        sRespuesta->status = _ERROR_DE_SERVIDOR;                        
        mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA CONFIRMAR LA FACTURA ELECTRONICA");

        soapError( soapFE, cLog );

        sRespuesta->iDevStatus = _ERROR_HTTP_;
        mysnprintf(sRespuesta->cDevMensaje,255,"ERROR AL CONSUMIR EL WS PARA CONFIRMAR LA FE. [%.200s]", cLog );
        logx( sRespuesta->cDevMensaje, _LOGINFO_);
    }

    soap_destroy(soapFE);
    soap_end(soapFE);
    soap_free(soapFE);
    
    return iRespuesta;
}

void consultarFechaCaea( C_ODBC *odbc, char *cFecha, char *cFechaDelDia )
{
    logx( "entro en consultarFechaCaea()", _LOGINFO_);    
	char cSql[256] = {0}, cLog[256] = {0};
	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar( "fecha", 16 );
	
	mysnprintf( cSql,sizeof(cSql), "SELECT vigencia_hasta FROM caea WHERE '%.20s' BETWEEN vigencia_desde AND vigencia_hasta",cFechaDelDia );
	////logx( csql, _LOGINFO_);

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{            
			mysnprintf( cFecha,16, "%.16s", parametro.valorChar( "fecha" ) );
            logx( cFecha, _LOGINFO_);
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "No se encontro el parametro: '%.20s'", cFechaDelDia );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,sizeof(cLog), "Error al consultar la fecha. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);		
	}
}

void obtenerFecha(C_ODBC *odbcTiendaNumero, char *cFecha )
{	
	char cSql[256] = {0};	
	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT fecha FROM gndominio" );

	CRegistro fecha( odbcTiendaNumero, false );
	fecha.agregarCampoChar( "fecha", 11);

	if ( fecha.Exec( cSql ) )
	{
		fecha.activarCols();
		if ( fecha.leer() )
		{			 
			 mysnprintf( cFecha,11, "%.11s", fecha.valorFecha("fecha"));			
		}
	}
	else
	{
		logx( "ERROR AL CONSULTAR FECHA", _LOGINFO_);
	}
	
}

double consultarTasaInteres8XRopa(C_ODBC *odbcTiendaNumero )
{	
	char cSql[256] = {0};	
	mysnprintf( cSql,sizeof(cSql),"%s" ,"SELECT tasasobreprecio FROM rocatalogoplazoropa WHERE plazomeses = 8;");
    double tasaInteresRopa = 0L;
	CRegistro consulta( odbcTiendaNumero );	
    consulta.agregarCampoDecimal("tasaInteresRopa8x",DT_DOBLE);

	if ( consulta.Exec( cSql ) )
	{
		consulta.activarCols();
		if ( consulta.leer() )
		{			 
			tasaInteresRopa = consulta.valorDouble("tasaInteresRopa8x");
		}
	}
	else
	{
		logx( "ERROR AL CONSULTAR consultarTasaInteres8XRopa()", _LOGINFO_);
	}
    return  tasaInteresRopa;
	
}

int obtenerDiasPrimerCompra(C_ODBC *odbcCartera, long lCliente, int dia, int Mes, int Anio ) //847
{
	char cSql[TAM_MED_BUFF] = {0}, cLog[TAM_MED_BUFF] = {0};
	int iDiasTransPrimerCompra = 0;

	if (lCliente != 90001)
	{
		mysnprintf( cSql,sizeof(cSql), "SELECT idiastrans AS Total FROM crObtenerDiasTransPrimerCompra( '%ld', '%04ld%02ld%02ld' );", lCliente, Anio, Mes, dia);

		CRegistro ConsultarFechaPrimerCompra( odbcCartera, false );
		ConsultarFechaPrimerCompra.agregarCampoEntero("Total", DT_ENTERO);

		if ( ConsultarFechaPrimerCompra.Exec( cSql ) == TRUE )
		{
			ConsultarFechaPrimerCompra.activarCols();
			if ( ConsultarFechaPrimerCompra.leer() )
			{
				iDiasTransPrimerCompra = ConsultarFechaPrimerCompra.valorLong( "Total" );;

				mysnprintf( cLog,sizeof(cLog), "DiasTransPrimerCompra: '%d'", iDiasTransPrimerCompra );
				logx( cLog, _LOGINFO_);
			}
		}
		else
		{
			mysnprintf( cLog,sizeof(cLog), "Error al consultar la fecha. [%.150s]", ConsultarFechaPrimerCompra.error() );
			logx( cLog  , _LOGINFO_);
		}
	}
	return(iDiasTransPrimerCompra );
}

// separa la fecha "20210101" (numerica) a char
void separarFecha(long lFecha, char *cDia, char *cMes, char *cAnio )
{
	char cFechaActual[11] = {0};

	logx( "Va sacar fecha actual del sistema", _LOGINFO_);
	mysnprintf(cFechaActual,sizeof(cFechaActual), "%ld", lFecha);
	mysnprintf(cDia,3, "%c%c", cFechaActual[6], cFechaActual[7]);
	logx( cDia, _LOGINFO_);
	mysnprintf(cMes,3, "%c%c", cFechaActual[4], cFechaActual[5]);
	logx( cMes, _LOGINFO_);
	mysnprintf(cAnio,5, "%c%c%c%c", cFechaActual[0], cFechaActual[1], cFechaActual[2], cFechaActual[3]);
	logx( cAnio, _LOGINFO_);
}

bool exitenPlanes( C_ODBC *odbcTiendaNumero,  int iTipo, char *cTarjetaID )
{
    logx( "Entro dentro de la funcion exitenPlanes()", _LOGINFO_);
    
	bool bRegresa = false;
	char    cConsulta[150]={0};
    char    cSql[264]={0};
    mysnprintf( cSql,sizeof(cSql), "este es itipo: %d",iTipo);
	////logx( csql, _LOGINFO_);
	if (iTipo == 1){
		logx("Entro en iTipo == 1", _LOGINFO_);
        mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(cuotas) FROM tdplanpagopos WHERE tarjetaid ='%.3s' and status = 'true' ",cTarjetaID);
	}
	else{		
        logx( "Entro en else iTipo == 1", _LOGINFO_);
        mysnprintf( cSql,sizeof(cSql), "SELECT COUNT(cuotas) FROM tdplanpagopos WHERE tarjetaid ='%.4s' AND tasainteres = 1 and status = 'true'", cTarjetaID);
	}
	////logx( csql, _LOGINFO_);
	
	CRegistro  consultarPlanes( odbcTiendaNumero, false );
    consultarPlanes.agregarCampoEntero("cuotas",DT_ENTERO_LARGO);
	if( consultarPlanes.Exec( cSql ) )
	{
		consultarPlanes.activarCols();
		if( consultarPlanes.Leer())
		{
            
            if (consultarPlanes.valorLong("cuotas") > 0)
            {
                bRegresa=true;
                logx( "consultarPlanes bRegresa=true", _LOGINFO_);                
                mysnprintf( cSql,sizeof(cSql),"valor countCuotas %ld",consultarPlanes.valorLong("cuotas"));
                ////logx( csql, _LOGINFO_);
            }
            else
            {                
                logx("Error #999001 llenarComboNumCuotas", _LOGINFO_);
            }
			            
		}
	}
	else
	{		
        logx("Error #999001", _LOGINFO_);
	}
	return bRegresa;
}

long obtenerFinanciamiento( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta )
{
    logx( "Entro dentro de la funcion obtenerFinanciamiento()", _LOGINFO_);
    
	char cImporteMasInteres[10]={0},cNumeroCuotasFin[3]={0},cNumeroCuotasAhora[30]={0}, logg[256] = {0};
	int iValorInicial=0,iCantCaracteres=0,iCuotasAhora = 0;
	float fInteresReg = 0;
	long lInteresReg = 0,iTotalCaracteres = 0 , lImporte = 0;

    lImporte = sSolicitud->lImporteCostoFinanciero;
	iTotalCaracteres = mystrnlen(sSolicitud->cInfoCuotas);
	for (int i = 0; i<80; i++)
	{
		if (sSolicitud->cInfoCuotas[i]== 0)
		{
			i=80; // finalizar el ciclo
		}
		else if(sSolicitud->cInfoCuotas[i] == '(')
		{
			iValorInicial=i+2;// +2 por el ($
		}
		else if(sSolicitud->cInfoCuotas[i] == ')')
		{			
			iCantCaracteres = i - iValorInicial;
			iCuotasAhora = i + 2 ;
			i=80; // finalizar el ciclo
		}		
	}
	mymemcpy(cImporteMasInteres,&sSolicitud->cInfoCuotas[iValorInicial],iCantCaracteres);
	// mymemcpy(cNumeroCuotasFin,&sSolicitud->cInfoCuotas[0],2);
    mysnprintf( cNumeroCuotasFin,sizeof(cNumeroCuotasFin), "%.2s",&sSolicitud->cInfoCuotas[0]);        
	// mymemcpy(cNumeroCuotasAhora,&sSolicitud->cInfoCuotas[iCuotasAhora],( iTotalCaracteres - iCuotasAhora));
    mysnprintf( cNumeroCuotasAhora,sizeof(cNumeroCuotasAhora), "%.s%s",iTotalCaracteres - iCuotasAhora,&sSolicitud->cInfoCuotas[iCuotasAhora]);   
    if(iCantCaracteres < sizeof(cImporteMasInteres))
    {
        cImporteMasInteres[iCantCaracteres]=0;
    }
	infoCostoFinanciero(odbcTiendaNumero, sSolicitud, sRespuesta,cNumeroCuotasFin,cNumeroCuotasAhora);    
	//lInteresReg = longConverter(cImporteMasInteres)-lImporte;    
	fInteresReg = floatConverter(cImporteMasInteres)*100;
    
	//fInteresReg = ( fInteresReg * 100);	
	//lInteresReg = ((float) fInteresReg * (float)100 );

	//lInteresReg = floatConverter(cImporteMasInteres) *100;    
	lInteresReg = fInteresReg;	
	lInteresReg = ( lInteresReg - ( lImporte * 100) );
	if ( lInteresReg < 0 ) 
	{
		lInteresReg = 0;
	}
	return lInteresReg;
}

void infoCostoFinanciero( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char *cNumeroCuotasFin,  char *cNumeroCuotasAhora )
{
    logx( "Entro dentro de la funcion infoCostoFinanciero()", _LOGINFO_);
    char sSqlTxt [256] = {0};
	//bool bRegresa = false;
	char    cConsulta[150]={0};

	//sSqlTxt.Format("SELECT arancel,tasainteres FROM tdplanpagopos WHERE tarjetaid ='%.3s' AND cuotas ='%.2s' ",cTarjetaID, cNumeroCuotasFin);
	//mysnprintf( cConsulta,sizeof(cConsulta), "%.149s", sSqlTxt );
	//cConsulta[ sSqlTxt.GetLength() ] = 0;
    
	mysnprintf(sSqlTxt,sizeof(sSqlTxt),"SELECT arancel,tasainteres,cuotasgrabar FROM tdplanpagopos WHERE tarjetaid ='%.4s' AND cuotas ='%.2s' AND alias like '%%%.30s%%' ORDER BY tasainteres ASC LIMIT 1",
	sSolicitud->cTarjetaID, cNumeroCuotasFin,cNumeroCuotasAhora);
	//logx( sSqlTxt, _LOGINFO_);
	
	CRegistro consultarInfoTarjetas( odbcTiendaNumero, false );
    consultarInfoTarjetas.agregarCampoEntero("arancel", DT_ENTERO);
    // consultarInfoTarjetas.agregarCampoEntero("tasainteres", DT_ENTERO);
	consultarInfoTarjetas.agregarCampoDecimal("tasainteres",DT_DOBLE);
    consultarInfoTarjetas.agregarCampoEntero("cuotasgrabar", DT_ENTERO);	

	if( consultarInfoTarjetas.Exec( sSqlTxt ) )
	{
		consultarInfoTarjetas.activarCols();
		if( consultarInfoTarjetas.Leer())
		{
			sRespuesta->lArancel = consultarInfoTarjetas.valorLong("arancel");            
			sRespuesta->lInteresTarjeta = (consultarInfoTarjetas.valorDouble("tasainteres") * 10000 );
			sRespuesta->iCuotasGrabar = consultarInfoTarjetas.valorLong("cuotasgrabar");
			//bRegresa=true;
		}
	}
	else
	{
        logx( "Error #99900777 infoCostoFinanciero", _LOGINFO_);		
	}	
	
}

// separa la fecha "2021-01-01" a long 20210101
void quitarGuionesFechaGnDominio(char *cFecha, long &lFecha)
{
	char cFechaActual[11] = {0}, cDia[2] = {0}, cMes[2] = {0}, cAnio[10] = {0}, cFechaFormateada[11] = {0};

	logx( "Va sacar fecha actual del sistema", _LOGINFO_);
	mysnprintf(cFechaActual,sizeof(cFechaActual), "%.10s", cFecha);
	logx( cFechaActual, _LOGINFO_);
	mysnprintf(cAnio,sizeof(cAnio), "%.4s", cFechaActual);
	logx( cAnio, _LOGINFO_);
	mysnprintf(cMes,sizeof(cMes), "%c%c", cFechaActual[5], cFechaActual[6]);
	logx( cMes, _LOGINFO_);
	mysnprintf(cDia,sizeof(cDia), "%c%c", cFechaActual[8], cFechaActual[9]);
	logx( cDia, _LOGINFO_);	
	mysnprintf(cFechaFormateada,sizeof(cFechaFormateada), "%.4s%.2s%.2s", cAnio, cMes, cDia);
	logx( cFechaFormateada, _LOGINFO_);

	lFecha = longConverter(cFechaFormateada );
}

int ConsultarClienteCarteraVendida(C_ODBC *odbcDBTiendaNumero, int iTienda, long lCliente, sRespuestaServicio *sRespuesta, int iTiendaLocal)
{
	logx( "ConsultarClienteCarteraVendida", _LOGINFO_);
	C_ODBC odbcCartera;
	char cMensajeReest[150] = {0};
	char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20]={0}, cIpBdServidor[20] = {0},cSqlTxt[256] = {0}, cNumeroCliente[10] = {0};
	int iFlagClienteCarteraVendida = -1;
	char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
	int iRespuesta = 0;

	logx( "Va a entrar a abrir conexiones", _LOGINFO_);	

	    	// if (consultarIpServidor( odbcDBTiendaNumero, SERV_CARTERA , cIpBdServidor ) == 1)
			// {
            //     if(obtenerDatosConexionBD(CONECTA_CARTERA,cPassBD,cUsuarioBD,cNombreBD,iTienda))
				iRespuesta = consultarSEC(_SEC_CARTERA, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
				if( iRespuesta == _OK_ )
                {
                    //iRespuesta = abrirConexion( &odbcCartera,cIpBdServidor,cNombreBD,cUsuarioBD );
					iRespuesta = abrirConexion2( &odbcCartera, cDNS, cBd, cUser, cPss );
                    if (iRespuesta == _OK_)
                    {
						
						logx( "Entro a abrir conexion", _LOGINFO_);
						CRegistro consultaSQL( &odbcCartera);												
						
						mysnprintf(cNumeroCliente,sizeof(cNumeroCliente),"%ld",lCliente);
						//mysnprintf(cSqlTxt,sizeof(cSqlTxt),"SELECT clv_cuenta_reest FROM crcliente WHERE cliente = %ld", lCliente); 
						mysnprintf(cSqlTxt,sizeof(cSqlTxt),"SELECT cmensaje,iflagcarteravendida FROM crobtenerclientecarteravendida('%.10s',14)", cNumeroCliente);
						consultaSQL.agregarCampoChar("cmensaje",256);
						consultaSQL.agregarCampoEntero("iflagcarteravendida",DT_ENTERO);
						if ( !consultaSQL.Exec(cSqlTxt) )
						{							
							mysnprintf(cMensajeReest,sizeof(cMensajeReest),"Fallo al ejecutar la consulta  %.90s",cSqlTxt);
							logx( cMensajeReest, _LOGINFO_);
						}
						else 
						{
							consultaSQL.activarCols();
							if ( consultaSQL.Leer() )
							{		
								iFlagClienteCarteraVendida=consultaSQL.valorLong("iflagcarteravendida");
								sRespuesta->iFlagClienteCartera = iFlagClienteCarteraVendida;				
								mysnprintf(sRespuesta->cMensaje,255,"%.255s",consultaSQL.valorChar("cmensaje"));
								logx( sRespuesta->cMensaje, _LOGINFO_);

							}
							else
							{
								mysnprintf(cMensajeReest,sizeof(cMensajeReest),"Fallo al ejecutar la consulta 2 %.100s",cSqlTxt);
								logx( cMensajeReest, _LOGINFO_);
							}
						}
					}
					else
					{
							logx("Fallo al abrir conexion al servidor de cartera", _LOGINFO_);
					}
				}
				else
				{
					logx("No se logro establecer conexión con el SEC - gnfunciones::ConsultarClienteCarteraVendida", _LOGINFO_);
				}
			// }
			// else
			// {
			// 		logx("Fallo al consultar al servidor de cartera");
			// }

	return iFlagClienteCarteraVendida;
}

//Función General para obtener cualquier valor de la tdconfiguracón solo pasando el elemento deseado.
void consultarFechaGndominio(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
    logx( "Entro dentro de la funcion consultarFechaGndominio()", _LOGINFO_);
	char cMensaje[TAM_MAX_BUFF];
    char sSqlTxt [256] = {0};
    	
	mysnprintf(sSqlTxt,255,"%s","select fecha from gndominio");	

	//logx( sSqlTxt, _LOGINFO_);	

	CRegistro cConsulta( odbcTiendaNumero);
	cConsulta.agregarCampoFecha( "fecha" );
	if( cConsulta.Exec( sSqlTxt ) )
	{
		logx("Si entra a la funcion Ejecutar JUANCVI", _LOGINFO_);
		cConsulta.activarCols();
		if( cConsulta.Leer())
		{
			mysnprintf( sRespuesta->cFechaGndominio,12,"%.12s",cConsulta.valorFecha("fecha") );
		}
	}
	else
	{
		mysnprintf(cMensaje,200,"gnfunciones, consultarFechaGndominio, Error al consultar la función consultarFechaGndominio %s", sSqlTxt);    
        logx( cMensaje, _LOGINFO_);		
		mysnprintf(sRespuesta->cMensaje,255,"%s",cMensaje);
	}
}

int checarCodigoMuInvent(C_ODBC *xOdbc,long lCodigo,char *cSql, bool &bConsulta)
{
    logx( "Entro dentro de la funcion checarCodigoMuInvent()", _LOGINFO_);
    int iFlagEncontro = 0;
    bConsulta = false;
	char cLog[310] = {0};

    mymemset(cSql, 0 ,300);
    mysnprintf( cSql,300, "SELECT muChecarCodigoInvent('%ld');", lCodigo);
    logx( cSql, _LOGINFO_);

    CRegistro checarCodigoSQL(xOdbc,false);
    checarCodigoSQL.agregarCampoEntero( "muchecarcodigoinvent", DT_ENTERO_CORTO );
    if (!checarCodigoSQL.Exec(cSql))
    {            

            bConsulta = false;      
         
    }
    else
    {
            checarCodigoSQL.activarCols();
            if (checarCodigoSQL.leer())
            {        
                    iFlagEncontro =  checarCodigoSQL.valorShort( "muchecarcodigoinvent" );           
                    bConsulta = true;
            }
			else{
 				logx( "No leyo ningun registro de la funcion muChecarCodigoInvent", _LOGINFO_);
			}
    }

    return iFlagEncontro;
}

bool abrirConexionApartadoNoMsg(C_ODBC *odbcDBTiendaNumero,C_ODBC *conexionBodegaM, int iTiendaLocal, int iTienda)
{
 char cSql[255], cIpServidor[17], cIpServidorAlterno[17], cPasswordTda[40], cUsuarioTda[25], cBbTda[25];
 bool bRespuesta = false;
 int iRespuesta = 0;
 char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

	mymemset(cSql, 0, sizeof(cSql));
	mymemset(cBbTda, 0, sizeof(cBbTda));
	mymemset(cUsuarioTda, 0, sizeof(cUsuarioTda));
	mymemset(cIpServidor, 0, sizeof(cIpServidor));
	mymemset(cPasswordTda, 0, sizeof(cPasswordTda));
	mymemset(cIpServidorAlterno, 0, sizeof(cIpServidorAlterno));

	
    
	//if ( consultarIpServidores(odbcDBTiendaNumero, cIpServidor, cIpServidorAlterno, SERV_APARTADO, cSql) )
	iRespuesta = consultarSEC(_SEC_GLOBALBODEGAM, cDNS,  cUser,  cBd,  cPss, iTiendaLocal, iTienda);
    if( iRespuesta == _OK_ )
	{
		// mysnprintf( cBbTda,sizeof(cBbTda),"%s","globalbodegam" );
		// mysnprintf( cUsuarioTda,sizeof(cUsuarioTda),"%s","sysbodegam");
		// generarPasswordDB( cUsuarioTda,cBbTda,cPasswordTda );
        // mysnprintf( cSql,255,"globalbodegam %s, sysbodegam %s, cPasswordTda %s",cUsuarioTda,cBbTda,cPasswordTda);
        ////logx( csql, _LOGINFO_);
		cPasswordTda[32] = 0;
        // iRespuesta = abrirConexion( &odbcTiendaNumero, sSolicitud->cIpBD,sSolicitud->cBD,sSolicitud->cUsuario );
        // conexionBodegaM.Open("PostgreSQL",cIpServidor,cUsuarioTda,cPasswordTda,cBbTda) == TRUE
		//if(abrirConexion( conexionBodegaM, cIpServidor,cBbTda,cUsuarioTda ) )
		iRespuesta = abrirConexion2( conexionBodegaM, cDNS, cBd, cUser, cPss );
		if( iRespuesta == _OK_ )
		{
            logx( "conexion a bodega por cIpServidor", _LOGINFO_);
			bRespuesta=true;
		}
		else
		{
			//if ( strcmp(cIpServidor,cIpServidorAlterno) != 0 )
			iRespuesta = consultarSEC(_SEC_GLOBALBODEGAM, cDNS,  cUser,  cBd,  cPss, 1, iTienda);//Moodo Local
			if( iRespuesta == _OK_ )
			{
				// Establecer conexión con ip servidor alterno                
				//if (abrirConexion( conexionBodegaM, cIpServidorAlterno,cBbTda,cUsuarioTda))
				iRespuesta = abrirConexion2( conexionBodegaM, cDNS, cBd, cUser, cPss );
				if( iRespuesta == _OK_ )
				{
                    logx( "conexion a bodega por cIpServidorAlterno", _LOGINFO_);
					bRespuesta = true;
				}
			}
		}        
	} 
    return bRespuesta;   
}

bool consultarMinimoRetiroCashBack( C_ODBC *odbc, int * iRespuesta )
{
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("valor",DT_ENTERO);

	mysnprintf( cSql,255,"%s", "SELECT valor::int FROM tdconfiguracion WHERE elemento = 'MINIMO RETIRO CASHBACK'");
	////logx( csql, _LOGINFO_);
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "valor" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,255, "%s","Error al consultar la valor de la tdconfiguracion MINIMO RETIRO CASHBACK : ''" );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,255, "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

bool consultarMaximoRetiroCashBack( C_ODBC *odbc, int * iRespuesta )
{		
	bool bRespuesta = true;
	char cLog[256] = {0}, cSql[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("valor",DT_ENTERO);

	mysnprintf( cSql,255,"%s", "SELECT valor::int FROM tdconfiguracion WHERE elemento = 'MAXIMO RETIRO CASHBACK'");
	////logx( csql, _LOGINFO_);
	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "valor" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,255,"%s",  "Error al consultar la valor de la tdconfiguracion  MAXIMO RETIRO CASHBACK: ''" );
			logx( cLog , _LOGINFO_);
		}
	}
	else
	{
		bRespuesta = false;
		mysnprintf( cLog,255, "Error al consultar parametro. [%.150s]", parametro.error() );
		logx( cLog , _LOGINFO_);	
	}

	return bRespuesta;
}

void mymemset(void *ptr, int value, size_t num)
{
    char *cptr = (char *)ptr;

    for (int i = 0; i < num; i++)
    {
        cptr[i] = value;
    }
}
void mymemcpy(void *dst, const void *src, size_t n)
{
    char *cdst = (char *)dst;
    char *csrc = (char *)src;

    for (int i = 0; i < n; i++)
    {
        cdst[i] = csrc[i];
    }
}
void mystrncat(char* dest, const char* src, size_t n) {
    std::string str1 = dest;
    std::string str2 = src;
    str1.append(str2);
    char* c = const_cast<char*>(str1.c_str());
    mysnprintf(dest, 180, "%.190s", c);
}
void mystrcat(char * dst, const char * src) {
	int idst = 0;
	int isrc = 0;
	int j = 0;
	int n = 0;

	while(dst[idst] != '\0') idst++;
	while(src[isrc] != '\0') isrc++;
	n = idst + isrc;

	for(int i = 0; i < n; i++) {
		if(i >= idst && j <= isrc) {
			dst[i] = src[j];
			j++;
		}
		if(j > isrc) break;
	}
}

long longConverter(const char * numstr) 
{
  return strtol(numstr, NULL, 10);
}
int mystrnlen(const char *str)
{
    int c = 0;
    while (str[c] != '\0')
        c++;
    return c;
}
int intConverter(const char * numstr) 
{
    return (int)strtol(numstr, NULL, 10);
}
float floatConverter(const char * numstr) 
{
    return strtof(numstr, NULL);
}
void obtener(void *dst,int iOpcion)
{
    char *v1 = (char *)dst;
    char v2[40]={0};
    int iNum = 0,iAux = 0;
    switch(iOpcion)
    {
        case CONECTA_CORREOS:
        iNum = 1;
        mysnprintf( v2,40,"%s", PWD_CENTRAL_M );
        break;
        case CONECTA_CENTRAL_M:
        iNum = 2;
        mysnprintf( v2,40,"%s", PWD_CONECTA_CORREOS );
        break;
        case 41: //CONECTA_POSGATEWAY
        iNum = 4;
        mysnprintf( v2,40,"%s", PWD_CONECTA_POSGATEWAY );  
        break;
    }
    for (int i=0;i<mystrnlen(v2);i++)
    {   
        iAux = (int)v2[i]-iNum;
        v1[i] = (char)iAux;
    }
}

void encondeBase64( C_ODBC *odbc, char *cTexto )
{

	char cSql[150000] = {0}, cLog[256] = {0};
	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar( "textoBase64", 150000 );

	mysnprintf( cSql,150000, "SELECT (encode('%.149984s'::bytea, 'base64')) as textoBase64",cTexto );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		while( parametro.Leer() )
		{
			mysnprintf( cTexto,150000, "%s", parametro.valorChar( "textoBase64" ) );
			logx(cTexto, _LOGINFO_);
		}
	}
	else
	{
		mysnprintf( cLog,256, "%s","Error al consultar encondeBase64." );
		logx( cLog  , _LOGINFO_);
	}
}

void decondeBase64( C_ODBC *odbc, char *cTexto)
{
	char cSql[150000] = {0}, cLog[256] = {0};
	CRegistro parametro( odbc, false );
	parametro.agregarCampoChar( "textoBase64", 150000 );

	mysnprintf( cSql,150000, "SELECT convert_from((decode('%.149971s', 'base64')), 'UTF8')  as textoBase64",cTexto );

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		while( parametro.Leer() )
		{
			mysnprintf( cTexto,150000, "%s", parametro.valorChar( "textoBase64" ) );
		}
	}
	else
	{
		mysprintf( cLog,"%s", "Error al consultar encondeBase64." );
		logx( cLog , _LOGINFO_);
	}
}

/*void enconde( char *cTexto)
{
	int iCorte = 100;
	char cCorte[101] = {0},cod[101] = {0};
	int parte_entera;
	double parte_decimal, longitud = mystrnlen(cTexto) + 1;

	parte_entera = (longitud / iCorte)/1;
	parte_decimal = (longitud / iCorte)-parte_entera;

	for (int i=0; i <= parte_entera; i++)
	{
		if (i == parte_entera)
		{
			snprintf(cCorte,iCorte*parte_decimal, cTexto + (i*iCorte)); //prueba
			//strncpy(cCorte, cTexto + (i*iCorte), iCorte*parte_decimal);
		}
		else
		{
			snprintf(cCorte,iCorte, cTexto + (i*iCorte)); //prueba
			//strncpy(cCorte, cTexto + (i*iCorte), iCorte);
		}
		mysprintf( cod, "%.100s\0", cCorte );
		logxc(cod, _LOGINFO_);
		mymemset( &cCorte, 0, sizeof( cCorte ) );
	}
}*/

bool consultarSql( C_ODBC *odbc, int * iRespuesta, char* cSql, sRespuestaServicio *sRespuesta)
{		
	bool bRespuesta = true;
	char cLog[256] = {0};

	CRegistro parametro( odbc );
	parametro.agregarCampoEntero("Respuesta",DT_ENTERO);

	if( parametro.Exec( cSql ) )
	{
		parametro.activarCols();
		
		if( parametro.Leer() )
		{
			*iRespuesta = parametro.valorLong( "Respuesta" );
		}
		else
		{
			bRespuesta = false;
			mysnprintf( cLog,256,"%s", "Error al consultar la valor: ''" );
			logx( cLog  , _LOGINFO_);
		}
	}
	else
    {
		bRespuesta = false;
		////logx(csql, _LOGINFO_);
        sRespuesta->status = _ERROR_EN_MENSAJE;
        mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");
        sRespuesta->iDevStatus = _ERROR_QUERY_;
        mysnprintf(sRespuesta->cDevMensaje,255,"ERROR AL EJECUTAR QUERY.15 [%.200s]", parametro.error() );
        logx( sRespuesta->cDevMensaje, _LOGINFO_);
    }

	return bRespuesta;
}

bool encoding( C_ODBC *xOdbc, const char *cCmd, bool flagCommit )
{
    char cTexto[256] = {0};
    bool bCmd = true;

    CRegistro cmd( xOdbc, flagCommit );
    if( !cmd.Exec( cCmd ) )
    {
        bCmd = false;

        mysnprintf( cTexto,256, "ERROR EN EL SERVIDOR %s", cCmd);
        logx( cTexto, _LOGINFO_ );
    }
    return bCmd;
}

bool replaceWord(const char* s, const char* oldW, const char* newW, char *cWord)
{
    int i, cnt = 0, tam;
    int newWlen = mystrnlen(newW);
    int oldWlen = mystrnlen(oldW);
	char ccadena[TAM_MAX_BUFF]={0};
    for (i = 0; s[i] != '\0'; i++) 
	{
        if (strstr(&s[i], oldW) == &s[i]) 
		{
            cnt++;
            i += oldWlen - 1;
        }
    }
  
    //cWord = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) 
	{
        if (strstr(s, oldW) == s) 
		{
            //strcpy(&result[i], newW);
			mysprintf(&cWord[i], "%s",newW);
            i += newWlen;
            s += oldWlen;
        }
        else
		{
			cWord[i++] = *s++;
		}
    }
	tam = snprintf(ccadena,TAM_MAX_BUFF,"%s",cWord);
    if(i < tam)
    {
		cWord[i] = '\0';
	}

	return cWord;
}

//Metodo del SEC a implementar
int consultarSEC(char *cConexion, char *cDns, char *cUsuario, char *cBd, char *cPass, int iModoLocal, int iTienda) {

	int iRespuesta = E00001_ERROR_SEC;
	soap *soapwsprestamos = soap_new1( SOAP_C_UTFSTRING );		
	value vSolicitudJson( soapwsprestamos );
	value vRespuestaJson( soapwsprestamos );
	char cUrl[TAM_MIN_BUFF] = {0},cLog[TAM_MIN_BUFF] = {0};
	//logx("*** SEC LOCAL ***", _LOGINFO_);
	switch(iSecModo)
	{
		case 1:mysnprintf(cUrl,TAM_MIN_BUFF,"https://t%.4ld%s", iTienda, _SEC_PROD);		break;
		case 2:mysnprintf(cUrl,TAM_MIN_BUFF,"https://d%.4ld%s", iTienda, _SEC_DESARROLLO);	break;
		//case 3:mysnprintf(cUrl,TAM_MIN_BUFF,"%s",_SEC_TEST);		break;
		default: logx("No existe Url de conexion para este modo", _LOGINFO_);	break;
	}
	vSolicitudJson["clave"] = cConexion;
	mysnprintf(cLog,TAM_MIN_BUFF,"Clave a consultar el SEC Modo Local: %s",cConexion);	
	logx(cLog, _LOGINFO_);
	//displayJson( &vSolicitudJson );
	int iJson = json_call( soapwsprestamos, cUrl, &vSolicitudJson, &vRespuestaJson );
    //displayJson( &vRespuestaJson );
	if (iJson == SOAP_OK && vRespuestaJson["data"]["response"].has("des_dns")) {
		logx("Entro al SEC Modo Local", _LOGINFO_);
		if (iModoLocal == 1) {
			mysnprintf(cDns,	100,"%.100s","127.0.0.1");
		} else {
			mysnprintf(cDns,	100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_dns"]);
		}

		mysnprintf(cUsuario,100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_usuario"]);
		mysnprintf(cBd,		100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_bd"]);
		mysnprintf(cPass,	100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_pass"]);

		iRespuesta = _OK_;
	}
	else
	{
		logx("*** SEC APLICATIVO ***", _LOGINFO_);
		switch (iSecModo)
		{
			case 1:mysnprintf(cUrl, TAM_MIN_BUFF, "%s", _SEC_PRODAPLICATIVO);	break;
			case 2:mysnprintf(cUrl, TAM_MIN_BUFF, "%s", _SEC_DESAAPLICATIVO);	break;
			// case 3:mysnprintf(cUrl,TAM_MIN_BUFF,"%s",_SEC_TEST);		break;
			default:
			logx("No existe Url de conexion para este modo", _LOGINFO_);
			break;
		}
		vSolicitudJson["clave"] = cConexion;
		mysnprintf(cLog,TAM_MIN_BUFF,"Clave a consultar el SEC Modo Aplicativo: %s",cConexion);	
		logx(cLog, _LOGINFO_);
		int iJson = json_call( soapwsprestamos, cUrl, &vSolicitudJson, &vRespuestaJson );
		if (iJson == SOAP_OK && vRespuestaJson["data"]["response"].has("des_dns")) {
			logx("Entro al SEC Modo Aplicativo", _LOGINFO_);
			if (iModoLocal == 1) {
				mysnprintf(cDns,	100,"%.100s","127.0.0.1");
			} else {
				mysnprintf(cDns,	100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_dns"]);
			}
			mysnprintf(cUsuario,100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_usuario"]);
			mysnprintf(cBd,		100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_bd"]);
			mysnprintf(cPass,	100,"%.100s", (char *)vRespuestaJson["data"]["response"]["des_pass"]);
			iRespuesta = _OK_;
		}
		else
		{
			mysnprintf(cLog,TAM_MIN_BUFF,"Error(consultarSEC) cConexion: %s",cConexion);	
			logx(cLog, _LOGINFO_);
		}
	}

    return iRespuesta;
}

void obtenerClaveSEC(int iTienda, char *cTiendaNumero, int iOpcion)
{
    char cTienda[5] = {'\0'}, cLog[TAM_MIN_BUFF] = {0};

	if(iTienda >= 100 && iTienda < 1000){ mysnprintf(cTienda,5,"0%.3ld",iTienda); }
	else if (iTienda >= 10 && iTienda < 100){ mysnprintf(cTienda,5,"00%.2ld",iTienda);}
	else if (iTienda > 0 && iTienda < 10){ mysnprintf(cTienda,5,"000%.1ld",iTienda);}
	
	switch ( iOpcion )
    {       
        case _SEC_TIENDANUMERO:
            mysnprintf(cTiendaNumero,100,"systienda%s",cTienda);
            break;
        case _SEC_TIENDASN:
            mysnprintf(cTiendaNumero,100,"tienda%s",cTienda);
            break;
        case _SEC_HUELLAEMPLEADO:
            mysnprintf(cTiendaNumero,100,"huella%s",cTienda);
            break;
        default:
            break;
    }
}

bool aplicaDescuentoDiaNino(SysRopa sysRopa, int iOpcion, long lCliente, long lImporteDescuentoEmpleado)
{
	char cDll[64] = {0}, cArgvIN1[1024] = {0}, cArgvIN2[1024] = {0}, cArgvOUT1[1024] = {0}, cArgvOUT2[1024] = {0}, cSql[100] = {0};
	bool bFlag = false;
	int iRespuesta = 0, iRec = 0, iSend = 0, iBytes = 0;
	char sIPServer[17] = {0};
	char cLog[512] = {0};

	CSocketx skConexion;
	clock_t clkTiempoINI;
	clkTiempoINI = clock();

	S00029EnviaDescuentoNino estructurarespuesta;
	S00029RecibeDescuentoNino descuentoDiaNino;

	mymemset(&descuentoDiaNino, 0, sizeof(descuentoDiaNino));
	mymemset(&estructurarespuesta, 0, sizeof(estructurarespuesta));

	mysnprintf(sIPServer,17, "%.15s", sysRopa.cIpServidorCartera);

	// ---------------------------------------------------------------------------
	// datos que se nesesitan asignar valores antes
	long tmplImporteDescuentoEmpleado = lImporteDescuentoEmpleado;
	int iTiendaOrigNino = 0; // iTiendaOrigNino = xdlgDev.iTiendaOrig; (se obtiene de la devolucion)
	int iNotaorigNino = 0;	 // iNotaorigNino = xdlgDev.iNotaOrig; (se obtiene de la devolucion)
	int iCajaOrigNino = 0;	 // iCajaOrigNino = xdlgDev.iCajaOrig; (se obtiene de la devolucion)
	int iTiendaCompra = 0;	 // puede ser local o de otra tienda la devolucion
	long lNotaCoppel = 0;	 // lNotaCoppel = xdlgDev.lNotaCoppel; (devolucion)
	int iCajacompra = 0;	 // iCajacompra = 	xdlgDev.iCajaCompra; (devolucion)
	// ---------------------------------------------------------------------------

	descuentoDiaNino.iTipoMensaje = 29;
	descuentoDiaNino.iTipoOpcion = iOpcion;
	mysnprintf(descuentoDiaNino.IpServidor,15, "%.15s", sIPServer);
	descuentoDiaNino.lValorSeguridad = 0;
	descuentoDiaNino.lCliente = lCliente;
	descuentoDiaNino.iAnio = sysRopa.iYearSys;

	if (sysRopa.bEsCambio) //era griNota.sysRopa
	{
		descuentoDiaNino.iImportedescuento = 0;
	}

	if (iOpcion == 2) // Devolucion
	{
		if (!sysRopa.bEsCambio)
		{
			descuentoDiaNino.iImportedescuento = tmplImporteDescuentoEmpleado;

			if (iTiendaOrigNino > 0)
			{
				descuentoDiaNino.iTienda = (short)iTiendaOrigNino;
				descuentoDiaNino.iNota = iNotaorigNino;
				descuentoDiaNino.iCaja = (short)iCajaOrigNino;
			}
			else
			{

				descuentoDiaNino.iTienda = (short)iTiendaCompra;
				descuentoDiaNino.iNota = lNotaCoppel;
				descuentoDiaNino.iCaja = (short)iCajacompra;
			}
		}
	}
	else
	{
		descuentoDiaNino.iImportedescuento = tmplImporteDescuentoEmpleado;
		descuentoDiaNino.iTienda = (short)sysRopa.iTienda;
		descuentoDiaNino.iNota = sysRopa.lFolioNota;
		descuentoDiaNino.iCaja = (short)sysRopa.iCaja;
	}

	logx("Informando a Agente CMIP...", _LOGINFO_);

	mysnprintf(cLog,512, "sIPServer [%s], Puerto [%d]", sIPServer, PTO_INET_DIANINIO);
	logx(cLog, _LOGINFO_);

	while (!skConexion.estaConectado() && (clock() - clkTiempoINI) <= TIEMPO_ESPERA)
	{
		skConexion.conectarNormal(sIPServer, PTO_INET_DIANINIO);
		logx("conectando...", _LOGINFO_);
	}

	if (skConexion.estaConectado() == true)
	{
		logx("conectado", _LOGINFO_);
		iBytes = sizeof(descuentoDiaNino);
		iSend = skConexion.enviarDatos(&descuentoDiaNino, iBytes);

		if (iSend == iBytes)
		{
			iBytes = sizeof(S00029EnviaDescuentoNino);
			iRec = skConexion.recibirDatos(&estructurarespuesta, iBytes, 600);

			if (iRec == iBytes)
			{
				iRespuesta = 1;

				mysnprintf(cLog,512,"%s", "respuesta obtenida correctamente");
				logx(cLog, _LOGINFO_);
			}
			else
			{
				mysnprintf(cLog,512, "Error al recibir los datos [REC=%d,ESP=%d]", iRec, iBytes);
				logx(cLog, _LOGINFO_);
			}
		}
		else
		{
			mysnprintf(cLog,512, "Error al enviar los datos [ENV=%d,ESP=%d]", iSend, iBytes);
			logx(cLog, _LOGINFO_);
		}

		skConexion.desconectar();
	}
	else
	{
		iRespuesta = -3;
		mysnprintf(cLog,512, "Error de conexion con el servicio del dia del niño, sIPServer [%s]", sIPServer);
		logx(cLog, _LOGINFO_);
	}

	if (iRespuesta == 1)
	{
		// memcpy( &estructurarespuesta, cArgvOUT1, sizeof( estructurarespuesta ) );
		if (estructurarespuesta.iRespuesta == 1)
		{
			bFlag = true;
		}
	}

	mysnprintf(cLog,100,"%s", "termino aplicaDescuentoDiaNino()");
	logx(cLog, _LOGINFO_);

	return bFlag;
}

bool obtenerClaveEncriptado( char *cClaveEncriptado )
{
    char cLog[256] = {0};
    bool bResultado = false;

    mysnprintf( cLog,sizeof(cLog),"%s", "************************** INICIA [LEER ARCHIVO DE ENCRIPTADO] wsprestamos **************************" );
    logx( cLog, _LOGINFO_ );

    leerArchivo(cClaveEncriptado);    
     
    if (cClaveEncriptado != "")
    {
        bResultado = true;
    }

    mysnprintf( cLog,sizeof(cLog),"%s", "************************** TERMINA [LEER ARCHIVO DE ENCRIPTADO] wsprestamos **************************" );
    logx( cLog, _LOGINFO_ );

    return bResultado;
}

int abrirArchivo(char *cNombre)
{	
	int nFp = 0;
	char cLog[100] = {0};
	FILE * fp;

	if(access(cNombre,0) != 0)
	{
		mysnprintf( cLog,sizeof(cLog),"%s", "No existe el archivo de claveencriptado" );
    	logx( cLog, _LOGINFO_ );
		nFp = -1;
	}
	else
	{
		fp = freopen64(cNombre, "r", stdin);
		if(fp == NULL) {
			fclose(fp);
			nFp = -1;
		}

		if(nFp == -1)
		{
			mysnprintf( cLog,sizeof(cLog), "%s","No se pudo abrir el archivo de claveencriptado" );
    		logx( cLog, _LOGINFO_ );
		}
	}

	return nFp;
}

int leerArchivo( char *cClaveEncriptado )
{
	int  nFp,nLeido,nRegresa = FALSE;
	char cArchivoConfiguracion[500] = {0};
	char cLog[100] = {0};

	//nFp = abrirArchivo("/sysx/fpg/ipcontrol.dat");
	nFp = abrirArchivo("/sysx/progs/webservice/wsprestamos/claveencriptado.txt");

	
	if(nFp != -1)
	{
		if(ispermission(1)) {
		nLeido=read(nFp, &cArchivoConfiguracion, 500);
			if(nLeido > 0)
			{
				char linea[1024];
				FILE *fich;

				fich = fopen64("/sysx/progs/webservice/wsprestamos/claveencriptado.txt", "r");
				int iContador = 0;

				if(ispermission(1)) {
					while(fgets(linea, 1024, (FILE*) fich)) {
						switch (iContador)
						{
							case 0:
								mysnprintf (cClaveEncriptado,16,"%.18s",linea);
								quitaEspacio(cClaveEncriptado);
							break;
						}
						iContador++;
					}
				}

				nRegresa = TRUE;		
			}
			else
			{
				mysnprintf( cLog,sizeof(cLog),"%s", "El archivo claveencriptado se encuentra vacio" );
    			logx( cLog, _LOGINFO_ );
			}
		}
	}
	return nRegresa;
}

bool ispermission(int user) 
{
	return user == 1;
}

void quitaEspacio(char * cCadena)
{
	int nI;

	for(nI = 0; nI < 20; nI++)
	{
		if(!ispunct(cCadena[nI]) && !isdigit(cCadena[nI]) && !isalpha(cCadena[nI]))
		{
			cCadena[nI] = 0;
			nI = 20;
		}
	}
}

bool leerArchivoTienda90( )
{
	int  nFp,nLeido,nRegresa = FALSE;
	char cArchivoConfiguracion[500] = {0};
	char cLog[100] = {0};

	//nFp = abrirArchivo("/sysx/fpg/ipcontrol.dat");
	nFp = abrirArchivo90("/sysx/progs/webservice/wsprestamos/tienda90.txt");

	
	if(nFp != -1)
	{
		nRegresa = TRUE;		
	}
	return nRegresa;
}

int abrirArchivo90(char *cNombre)
{	
	int nFp = 0;
	char cLog[100] = {0};
	FILE * fp;

	if(access(cNombre,0) != 0)
	{
		mysnprintf( cLog,sizeof(cLog),"%s", "No existe el archivo de tienda90" );
    	logx( cLog, _LOGINFO_ );
		nFp = -1;
	}
	else
	{
		fp = freopen64(cNombre, "r", stdin);
		if(fp == NULL) {
			fclose(fp);
			nFp = -1;
		}

		if(nFp == -1)
		{
			mysnprintf( cLog,sizeof(cLog), "%s","No se pudo abrir el archivo de tienda90" );
    		logx( cLog, _LOGINFO_ );
		}
	}

	return nFp;
}

int obtenerSecModo(int *iSecModoRespuesta)
{
    char myIP[16] = {0}, cIptxt[16] = {0};
    int  nFp,nLeido, iRegresa = FALSE;
    char cArchivoIps[500] = {0};
    char cLog[100] = {0};

    nFp = abrirArchivomodoSEC();
    if(nFp != -1)
    {
        if(ispermission(1)) {
        	nLeido=read(nFp, &cArchivoIps, 500);
            if(nLeido > 0)
            {
                char linea[1024];
                FILE *fich;

                fich = fopen64(TXT_SEC, "r");

                if(ispermission(1)) {
                    while(fgets(linea, 1024, (FILE*) fich)) 
                    {
                        mysnprintf (cIptxt,10,"%.9s",linea);
                        quitaEspacio(cIptxt);
                        //logx(cIptxt, _LOGINFO_);
                        if( memcmp (cIptxt,"https://t",9) == 0)
                        {
                            iSecModo = 1; //Productivo 
							iRegresa = _OK_;
                        }
                        else if( memcmp (cIptxt,"https://d",9) == 0)
                        {
                            iSecModo = 2; //Desarrollo 
							iRegresa = _OK_;
                        }
						else
						{
							logx( "Informacion incorrecta en archivo modoSEC.txt", _LOGINFO_ );
						}
                    }
                }
            }
            else
            {
                logx( "El archivo modoSEC.txt se encuentra vacio", _LOGINFO_ );
            }
        }
    }
	*iSecModoRespuesta = iSecModo;
    if (iSecModo == 1){logx("Sec modo Productivo",_LOGINFO_);}
    if (iSecModo == 2){logx("Sec modo Desarrollo",_LOGINFO_);}
    return iRegresa;
}
  
int abrirArchivomodoSEC()
{   
    int nFp = 0;
    char cLog[100] = {0};
    FILE * fp;

    if(access(TXT_SEC,0) != 0)
    {
        logx( "No existe el archivo modoSEC.txt", _LOGINFO_ );
        nFp = -1;
    }
    else
    {
        fp = freopen64(TXT_SEC, "r", stdin);
        if(fp == NULL) {
            fclose(fp);
            nFp = -1;
        }

        if(nFp == -1)
        {
            logx( "No se pudo abrir el archivo modoSEC.txt", _LOGINFO_ );
        }
    }

    return nFp;
}
