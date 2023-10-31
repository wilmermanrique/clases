#include <unistd.h>
#include "gnlog.h"
#include "Aes.hpp"
#include "definiciones.h"
#include "gnfunciones.h"

long lNumEmpleadoLog;
char cTipoEventoLog[64];
char cIpMicroLog[17];
char cLogDir[64] = {0};

void soapError( struct soap *pSoap, char *cError );
void logx( char *cLog, const char *cStatus)
{   char cMensaje[5000] = {0};
    time_t tTiempo;
    struct tm *tHora;

    tTiempo = time(NULL);
    tHora = localtime( &tTiempo );
    mysnprintf(cMensaje,4999,"%d/%02d/%02d %02d:%02d:%02d %06d %08ld %.63s %.16s %.17s: %s\n",
    tHora->tm_year + 1900,
    tHora->tm_mon + 1,
    tHora->tm_mday,
    tHora->tm_hour,
    tHora->tm_min,
    tHora->tm_sec,
    getpid(),
    lNumEmpleadoLog,
	cTipoEventoLog,
	cIpMicroLog,
	cStatus,
	cLog );

    C_Archivo arch( cLogDir, &cMensaje, sizeof( cMensaje ) );
    arch.posicionar( (long)0, BASE_FINAL);
    arch.grabar( cMensaje, (unsigned int) mystrnlen(cMensaje) );
}



/*void logxd( char *cLog, const char *cStatus)
{
	char nuevo[TAM_MAX_BUFF] = {0};
	Aes Aes;
	Aes.decrypt( cLog, _CLAVECIFRADO_, nuevo );

	time_t tTiempo;
	struct tm *tHora;

	tTiempo = time(NULL);
	tHora = localtime( &tTiempo );

	fprintf( stderr, "%d/%02d/%02d %02d:%02d:%02d %06d %08ld %.63s %.16s %.17s: %.2047s\n",
	tHora->tm_year + 1900,
	tHora->tm_mon + 1,
	tHora->tm_mday,
	tHora->tm_hour,
	tHora->tm_min,
	tHora->tm_sec,
	getpid(),
	lNumEmpleadoLog,
	cTipoEventoLog,
	cIpMicroLog,
	cStatus,
	cLog );

	fflush(stderr);
}*/

void abrirLog( int iCaja,int iTipo )
{
    time_t tTiempo;
    struct tm *tHora;
     
    tTiempo = time(NULL);
    tHora = localtime( &tTiempo );
    switch(iTipo)
    {
        case 1:
        mysnprintf( cLogDir, sizeof(cLogDir)-1, "/sysx/progs/webservice/wsprestamos/log/%d_%02d%02d.txt",iCaja, tHora->tm_mon + 1, tHora->tm_mday );
        break;
        case 2:
        mysnprintf( cLogDir, sizeof(cLogDir)-1, "/sysx/progs/webservice/wsprestamos/log/%d_%02d%02d_front.txt",iCaja, tHora->tm_mon + 1, tHora->tm_mday );
        break;
    }
}

/*void logx( char *cLog)
{
	time_t tTiempo;
	struct tm *tHora;
	      
	tTiempo = time(NULL);
	tHora = localtime( &tTiempo );
		
	fprintf( stderr, "%d/%02d/%02d %02d:%02d:%02d %06d %s\n",
	tHora->tm_year + 1900,
	tHora->tm_mon + 1,
	tHora->tm_mday,
	tHora->tm_hour,
	tHora->tm_min,
	tHora->tm_sec,
	getpid(),
	cLog );
	
	fflush(stderr);
}*/


void parametrosLog( int iMensaje, int iNumeroProcedimiento, long lNumEmpleado, char *cIpMicro )
{
    char cLog[ 256 ] = {0};
    mysprintf(cLog, "%d, %d, %ld, %s", iMensaje, iNumeroProcedimiento , lNumEmpleado , cIpMicro);
    //logx(cLog);


    lNumEmpleadoLog = lNumEmpleado;
    mysprintf(cIpMicroLog, "%s", cIpMicro);

    switch (iMensaje)
    {
        case M00001_AUTENTIFICAHUELLA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00001_AUTENTIFICAHUELLA");
        }
        break;
        case M00002_CONSULTARPRODUCTO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00002_CONSULTARPRODUCTO");
        }
        break;
        case M00003_CONSULTAARTICULOTIENDAS:
        {
            mysprintf(cTipoEventoLog,"%s", "M00003_CONSULTAARTICULOTIENDAS");
        }
        break;
        case M00004_CONSULTARDIRECCION:
        {
            mysprintf(cTipoEventoLog,"%s", "M00004_CONSULTARDIRECCION");
        }
        break;
        case M00005_BUSQUEDANOMBRE:
        {
            mysprintf(cTipoEventoLog,"%s", "M00005_BUSQUEDANOMBRE");
        }
        break;
        case M00006_CAMBIARVENDEDOR:
        {
            mysprintf(cTipoEventoLog,"%s", "M00006_CAMBIARVENDEDOR");
        }
        break;
        case M00007_FORMASDEPAGO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00007_FORMASDEPAGO");
        }
        break;
        case M00008_COMPLEMENTARCCUENTA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00008_COMPLEMENTARCCUENTA");
        }
        break;
        case M00009_GRABARVENTA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00009_GRABARVENTA");
        }
        break;
        case M00010_BUSQUEDACLIENTEDNI:
        {
            mysprintf(cTipoEventoLog,"%s", "M00010_BUSQUEDACLIENTEDNI");
        }
        break;
        case M00011_VALIDARINICIODELDIA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00011_VALIDARINICIODELDIA");
        }
        break;
        case M00012_VALIDARVENTASFUTURA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00012_VALIDARVENTASFUTURA");
        }
        break;
        case M00014_CAPTURADECORREOYTELEFONO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00014_CAPTURADECORREOYTELEFONO");
        }
        break;
        case M00015_CAPTURADEEMI:
        {
            mysprintf(cTipoEventoLog,"%s", "M00015_CAPTURADEEMI");
        }
        break;
        case M00016_CONSULTARPAGOINICIAL:
        {
            mysprintf(cTipoEventoLog,"%s", "M00016_CONSULTARPAGOINICIAL");
        }
        break;
        case M00017_CALCULAR_SOBREPRECIO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00017_CALCULAR_SOBREPRECIO");
        }
        break;
        case M00018_VERIFICAR_VENTA_TRAMITE:
        {
            mysprintf(cTipoEventoLog,"%s", "M00018_VERIFICAR_VENTA_TRAMITE");
        }
        break;
        case M00019_OBTENER_DESCUENTOS:
        {
            mysprintf(cTipoEventoLog,"%s", "M00019_OBTENER_DESCUENTOS");
        }
        break;
        case M00020_PROCEDIMIENTOSGENERALES:
        {
            // PROCEDIMIENTOSGENERALES
            switch (iNumeroProcedimiento)
            {
                case LIMPIARTABLATEMPORALES:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_LIMPIARTABLATEMPORALES");
                }
                break;
                case OBTENERDATOSCLIENTELCCROPA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERDATOSCLIENTELCCROPA");
                }
                break;
                case GRABARRECONOCIMIENTO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GRABARRECONOCIMIENTO");
                }
                break;
                case GRABARTDAUTORIZACION:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GRABARTDAUTORIZACION");
                }
                break;
                case CONSULTARFLAGDESCUENTOESPECIAL:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFLAGDESCUENTOESPECIAL");
                }
                break;
                case CONSULTARMINIMOCOMPRAMEGAPUNTOS:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARMINIMOCOMPRAMEGAPUNTOS");
                }
                break;
                case CONSULTARPORCENTAJEGASTOMEGAPUNTOS:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARPORCENTAJEGASTOMEGAPUNTOS");
                }
                break;
                case COLSULTARPROVINCIA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_COLSULTARPROVINCIA");
                }
                break;
                /*case OBTENERDATOSPAGOINICIAL:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERDATOSPAGOINICIAL");
                }
                break;*/
                case OBTENERDATOSPAGOINICIAL:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERDATOSPAGOINICIAL");
                }
                break;
              
                case VENTAUDI:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VENTAUDI");
                }
                break;
                case CONSULTARENCABEZADOTICKET:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARENCABEZADOTICKET");
                }
                break;
                case QUIENENTREGAUDI:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_QUIENENTREGAUDI");
                }
                break;
                case ACTUALIZARCTEVTO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_ACTUALIZARCTEVTO");
                }
                break;
                case CONSULTARTDCONFIGURACIONTICKETGARANTIAEXT:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARTDCONFIGURACIONTICKETGARANTIAEXT");
                }
                break;
                case CONSULTAFECHAPRIMERACOMPRALCCMUEBLES:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTAFECHAPRIMERACOMPRALCCMUEBLES");
                }
                break;
                case OBTENERFECHAFINVIGENCIA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERFECHAFINVIGENCIA");
                }
                break;
                case CONSULTARFLAGMERCADOPAGO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFLAGMERCADOPAGO");
                }
                break;
                case CONSULTARFOLIO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFOLIO");
                }
                break;
                case CONSULTARMISMACIUDAD:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARMISMACIUDAD");
                }
                break;
                case CONSULTARFLAGTDAVENTAHUELLA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFLAGTDAVENTAHUELLA");
                }
                break;
                case VALIDARCONTROL:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VALIDARCONTROL");
                }
                break;
                case GRABARENCABEZADOTICKETS:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GRABARENCABEZADOTICKETS");
                }
                break;
              
              
                case CONSULTARPUNTOSINICIALESROPA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARPUNTOSINICIALESROPA");
                }
                break;
              
                case VERIFICARULTIMANOTA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VERIFICARULTIMANOTA");
                }
                break;
                case CONSULTARNOMBREZONA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARNOMBREZONA");
                }
                break;
               
                case CONSULTARFACTORTASADIFERENCIADA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFACTORTASADIFERENCIADA");
                }
                break;
                case CONSULTARCOLONIA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARCOLONIA");
                }
                break;
                case VERIFICARPRECIOCODIGO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VERIFICARPRECIOCODIGO");
                }
                break;
             
              
                case GRABARVENTACAIDA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GRABARVENTACAIDA");
                }
                break;
                case CONSULTARINFORMACIONFINANCIERA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARINFORMACIONFINANCIERA");
                }
                break;
                
                case CONSULTARSERVICIOPAGOMINIMO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARSERVICIOPAGOMINIMO");
                }
                break;
                case CONSULTARSERVICIOREESTRUCTURA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARSERVICIOREESTRUCTURA");
                }
                break;
                case CONSULTARFLAGREGALO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFLAGREGALO");
                }
                break;
                case CONSULTARVALORNETO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARVALORNETO");
                }
                break;
                case BORRARTABLASTEMPORALESNUBE:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_BORRARTABLASTEMPORALESNUBE");
                }
                break;
                case CONFIRMARTRANSACCIONFE:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONFIRMARTRANSACCIONFE");
                }
                break;
                case VERIFICARTDESTACION:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VERIFICARTDESTACION");
                }
                break;
               
                case CHECARCODREGALO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CHECARCODREGALO");
                }
                break;
                case BORRARTMPTDCHEQUES:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_BORRARTMPTDCHEQUES");
                }
                break;
                case COMBONUMCUOTAS:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_COMBONUMCUOTAS");
                }
                break;
                case OBTENERFINANCIAMIENTO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERFINANCIAMIENTO");
                }
                break;
                case ONOFFAUTOMATIZACION:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_ONOFFAUTOMATIZACION");
                }
                break;
                case CONSULTACLIENTECARTERAVENDIDA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTACLIENTECARTERAVENDIDA");
                }
                break;
                case CONSULTARLEYENDAMONOTRIBUTO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARLEYENDAMONOTRIBUTO");
                }
                break;
                case OBTENERCOSTOFINANCIERO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_OBTENERCOSTOFINANCIERO");
                }
                break;
                case GRABARCAMOVDINEROELECTRONICO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GRABARCAMOVDINEROELECTRONICO");
                }
                break;
                case CONSULTARFECHAGNDOMINIO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_CONSULTARFECHAGNDOMINIO");
                }
                break;
                case GNCONSULTARTDCONFIGURACION:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GNCONSULTARTDCONFIGURACION");
                }
                break;
                case VERIFICA_CACARMOV:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_VERIFICA_CACARMOV");
                }
                break;
                case GNCONSULTARTDCAJAACTIVA:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GNCONSULTARTDCAJAACTIVA");
                }
                break;
                case GNCONSULTACLIENTE:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GNCONSULTACLIENTE");
                }
                break;
                case GNLEVANTARDIALOGO:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_GNLEVANTARDIALOGO");
                }
                break;
                case MANDARTRAMITE:
                {
                    mysprintf(cTipoEventoLog,"%s", "M00020_PG_MANDARTRAMITE");
                }
                break;
                default:
                    mysprintf(cTipoEventoLog,"%s", "NORECONOCIDA");
                break;
            }
        }
        break;
        case M00021_VALIDARCODIGOMUEBLES:
        {
            mysprintf(cTipoEventoLog,"%s", "M00021_VALIDARCODIGOMUEBLES");
        }
        break;
        case M00023_GRABAR_FACTURA_TEMPORAL:
        {
            mysprintf(cTipoEventoLog,"%s", "M00023_GRABAR_FACTURA_TEMPORAL");
        }
        break;
        case M00024_VALIDARQUIENENTREGA:
        {
            mysprintf(cTipoEventoLog,"%s", "M00024_VALIDARQUIENENTREGA");
        }
        break;
        case M00025_CONSULTARCLIENTECONTADO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00025_CONSULTARCLIENTECONTADO");
        }
        break;
        case M00026_GUARDARINFOMOTO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00026_GUARDARINFOMOTO");
        }
        break;
        case M00027_VALIDARPAGOMUEBLES:
        {
            mysprintf(cTipoEventoLog,"%s", "M00027_VALIDARPAGOMUEBLES");
        }
        break;
        case M00028_CONSULTARPRESTAMO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00028_CONSULTARPRESTAMO");
        }
        break;
        case M00029_CONSULTARSORTEO:
        {
            mysprintf(cTipoEventoLog,"%s", "M00029_CONSULTARSORTEO");
        }
        break;
        case M00030_LOG_FRONT_END:
        {
            mysprintf(cTipoEventoLog,"%s", "M00030_LOG_FRONT_END");
        }
        break;
        default:
            mysprintf(cTipoEventoLog,"%s", "NORECONOCIDO");
        break;
    }
}
