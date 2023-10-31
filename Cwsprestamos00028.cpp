#include "wsprestamos.h"
#include "jsonUtils.h"
#include "Cwsprestamos00028.h"
#include "gnlog.h"
#include "folios.hpp"
void soapError( struct soap *pSoap, char *cError );
Cwsprestamos00028::Cwsprestamos00028( void )
{
}

Cwsprestamos00028::~Cwsprestamos00028( void )
{
}
int Cwsprestamos00028::wsconsultarParametricoPrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
	logx("Empieza wsconsultarParametricoPrestamo ***************************************************",_LOGINFO_);

    int iRespuesta = 0;
    sRespuesta ->iNumeroProcedimiento = sSolicitud->opcion;
    if (sSolicitud->opcion == 2)
    {

        consumirWebserviceParametrico(sSolicitud, sRespuesta, iRespuesta);
    }
    else if(sSolicitud->opcion == 3)
    {
        grabarPrestamoUN(sSolicitud, sRespuesta, iRespuesta);
    }
    else if(sSolicitud->opcion == 4)
    {
        obtenerFolioPrestamo(sSolicitud, sRespuesta, iRespuesta);
        obtenerInfoEmpleados( sSolicitud, sRespuesta, iRespuesta );
        obtenerInfoFinancieraPrestamo( sSolicitud, sRespuesta, iRespuesta );
        ObtenerCajero( sSolicitud, sRespuesta, iRespuesta);
    }
    else if(sSolicitud->opcion == 5)
    {
        consultarImportePrestamo(sSolicitud, sRespuesta, iRespuesta);
    }
    else if(sSolicitud->opcion == 6)
    {
        C_ODBC odbcTiendaNumero;
        char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
        char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

        obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
        iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
        if (iRespuesta == _OK_)
        {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
        }
        else
        {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
        }
        sRespuesta->iDevStatus = iRespuesta;
        if (iRespuesta != _OK_)
        {
            sRespuesta->status = _ERROR_DE_SERVIDOR;
            mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje) - 1, "%s", "OCURRRIO UN ERROR EN EL SERVIDOR");

            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }

        if (consultarFlagSysflags(&odbcTiendaNumero, FLAGC_PRESTAMOS, 'C', &sRespuesta->flagPrestamos) && 
        consultarFlagSysflags(&odbcTiendaNumero, FLAGC_ENCUESTAS_AUTOMATICAS, 'C', &sRespuesta->flagEncuesta) &&
        consultarFlagSysflags(&odbcTiendaNumero, FLAG_SERV_ISVR, 'C', &sRespuesta->sRespPrestamo.iFlagPrestamoEmpleado))
        {
            sRespuesta->status = _MENSAJE_CORRECTO_;
        }
        else{
            sRespuesta->status = _ERROR_DE_SERVIDOR;
            mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje) - 1, "%s", "OCURRRIO UN ERROR EN EL SERVIDOR");
            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }

    }
    else if(sSolicitud->opcion == 1)
    {
        C_ODBC odbcTiendaNumero, odbcCartera, odbcTienda;
        char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0}, Monto[100] = {0};
        char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

        obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
        iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
        sRespuesta -> Prestamo = 0;
        if (iRespuesta == _OK_)
        {
            iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
        }
        else
        {
            logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
        }
        sRespuesta->iDevStatus = iRespuesta;
        if (iRespuesta != _OK_)
        {
            sRespuesta->status = _ERROR_DE_SERVIDOR;
            mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje) - 1, "%s", "OCURRRIO UN ERROR EN EL SERVIDOR");

            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }
        iRespuesta = consultarSEC(_SEC_CARTERA, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
        if (iRespuesta == _OK_)
        {
            iRespuesta = abrirConexion2(&odbcCartera, cDNS, cBd, cUser, cPss);
        }
        else
        {
            logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
        }
        if (iRespuesta != _OK_)
        {
            sRespuesta->status = _ERROR_DE_SERVIDOR;
            mysnprintf(sRespuesta->cMensaje, 255, "%s", "OCURRRIO UN ERROR EN EL SERVIDOR");

            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }

        iRespuesta = E00001_ERROR_DEFAULT;
        if (consultarFlagSysflags(&odbcTiendaNumero, FLAGR_MENSAJE_PRESTAMO_DISPONIBLE, 'R', &sRespuesta->sSysRopa.iFlagMensajePrestamoR) ||
            consultarFlagSysflags(&odbcTiendaNumero, FLAGM_MENSAJE_PRESTAMO_DISPONIBLE, 'M', &sRespuesta->sSysMuebles.iFlagMensajePrestamoM))
        {
            if (sRespuesta->sSysRopa.iFlagMensajePrestamoR == 1 || sRespuesta->sSysMuebles.iFlagMensajePrestamoM == 1)
            {
                if (sSolicitud->infoGrabarVentaReq.iFlagDescuentoEspecial != 1 && sSolicitud->infoGrabarVentaReq.iFlagDescuentoEspecial != 2)
                {
                    if (consultarParametricoPrestamo(&odbcTiendaNumero, &odbcCartera, sSolicitud, sRespuesta))
                    {
                        if (sSolicitud->infoGrabarVentaReq.nota.bEsCambio == false)
                        {
                            if (obtenerValorTdConfiguracion(&odbcTiendaNumero, sRespuesta, "MENSAJE_PRESTAMO_DISPONIBLE_RM", Mensaje, false, 0))
                            {
                                mysnprintf(sRespuesta->sRespPrestamo.Mensaje, sizeof(sRespuesta->sRespPrestamo.Mensaje) - 1, "%s", Mensaje);
                                logx(sRespuesta->sRespPrestamo.Mensaje, _LOGINFO_);
                            }
                            if (obtenerValorTdConfiguracion(&odbcTiendaNumero, sRespuesta, "CANTIDAD_MONTO_MINIMO", Monto, false, 0))
                            {
                                mysnprintf(sRespuesta->sRespPrestamo.cMontoMinimo, sizeof(sRespuesta->sRespPrestamo.cMontoMinimo) - 1, "%s", Monto);
                                logx(sRespuesta->sRespPrestamo.cMontoMinimo, _LOGINFO_);
                            }
                            mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "El cliente [%d] Si es candidato a prestamo", sSolicitud->sCCuenta.iNumcliente);
                            iRespuesta = _OK_;
                        }
                    }
                    else
                    {
                        mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "El cliente [%d] NO es apto para un préstamo", sSolicitud->sCCuenta.iNumcliente);
                    }
                }
                else
                {
                    mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "Tipo cliente [%d] no aplica para prestamo disponible", sSolicitud->infoGrabarVentaReq.iFlagDescuentoEspecial);
                }
            }
            else
            {
                mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "%s", "MENSAJE_PRESTAMO_DISPONIBLE_RM apagado");
            }
        }
        else
        {
            mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "%s", "Error al consultar consultarFlag( &odbcDBTiendaNumero, cSql, 'R', FLAGR_MENSAJE_PRESTAMO_DISPONIBLE, iFlagMensajePrestamo");
        }
        if (iRespuesta == _OK_)
        {
            sRespuesta->iDevStatus = _MENSAJE_CORRECTO_;
            mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje) - 1, "%s", "OK");
            sRespuesta->status = _MENSAJE_CORRECTO_;
        }
    }
	return iRespuesta;
}
void Cwsprestamos00028::grabarPrestamoUN(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta) {
	char cURL_[128] = {0}, cTexto[128] = {0}, cLog[512] = {0},Mensaje[150] = {0},cMensaje[300]={0};
	int iJson_ = SOAP_ERR,lRecibo=0;
    bool bContinuar=true;
    
    long lFacturaAntCentral=0,lSaldoAntCentral=0,lSaldoFecha=0;
	iRespuesta = _ERROR_QUERY_;

    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
    C_ODBC odbcTiendaNumero, odbcCartera;

    iRespuesta = consultarSEC(_SEC_CARTERA, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    iRespuesta = abrirConexion2( &odbcCartera, cDNS, cBd, cUser, cPss );
    if (iRespuesta != _OK_)
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::consumirWebserviceParametrico", _LOGINFO_);
        bContinuar=false;
    }
    if(bContinuar)
    {
            if (sSolicitud -> lImporte > 99L )
            {
                obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
                iRespuesta = consultarSEC(cTiendaNumero, cDNS,  cUser,  cBd,  cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
                if( iRespuesta == _OK_ )
                {
                    iRespuesta = abrirConexion2( &odbcTiendaNumero, cDNS, cBd, cUser, cPss );
                }
                else
                {
                    logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::WSPRESTAMOS", _LOGINFO_ );
                }
                sRespuesta->iDevStatus = iRespuesta;
                if( iRespuesta == _OK_ )
                {
                    if( crearTablaTmpCrCancPrestamos(&odbcCartera,sSolicitud,sRespuesta) && crearTablaTmpCrPrestamos(&odbcCartera,sSolicitud,sRespuesta) && crearTablaTmpCacarmov(&odbcTiendaNumero,sSolicitud,sRespuesta) )
	                {
                        lRecibo = obtenerReciboCajas(&odbcTiendaNumero ,0,sSolicitud,sRespuesta );
                        lRecibo = lRecibo + 1;
                        lSaldoFecha = grabarEnCarteraPrestamos(&odbcTiendaNumero ,&odbcCartera,sSolicitud,sRespuesta);
                        if( lSaldoFecha < 0 )
                        {
                            bContinuar = false;
                        }
                        if(bContinuar)
                        {
                            if( sSolicitud-> iFlagNuevo == 0 )
                            {
                                lFacturaAntCentral = sSolicitud ->lFacturaAnt;
                                lSaldoAntCentral = lSaldoFecha;

                                bContinuar = grabarLiquidacionPorNuevoPrest( &odbcTiendaNumero, sSolicitud, lRecibo ,sRespuesta);
                            }
                            else
                            {
                                bContinuar = true;
                            }

                        }
                    }
                    else{
                        bContinuar = false;
                    }
                }
                else
                {
                    bContinuar=false;

                }
                if( bContinuar )
                {


                    if( grabarPrestamo(&odbcTiendaNumero,sSolicitud,lRecibo,sRespuesta) )
                    {
                       // sRespuesta -> status = _MENSAJE_CORRECTO_;
            
                        if(ejecutarFuncionesPostgres(&odbcTiendaNumero,&odbcCartera,sSolicitud,sRespuesta,lRecibo))//373
                        {


                        }

                    }
                }
                else
                {
                    sRespuesta -> status = _ERROR_EN_MENSAJE;
                    mysnprintf(cMensaje,254,"No se logro abrir conexion a la base de datos: %.32s en el servidor: %.16s con el usuario: %.32s",sSolicitud->cBD, sSolicitud->cIpBD, sSolicitud->cUsuario );
                    logx( cMensaje, _LOGINFO_ );
                    sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
                    mysnprintf( sRespuesta->cDevMensaje,254,"%s", cMensaje );
                }
            }
            else
            {
                sRespuesta -> status = _ERROR_EN_MENSAJE;
                mysnprintf(cMensaje,254,"Error: EL IMPORTE DEBE SER MAYOR A 99L, IMPORTE : %d",sSolicitud->lImporte);
                logx( cMensaje, _LOGINFO_ );
                sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
                mysnprintf( sRespuesta->cDevMensaje,254,"%s", cMensaje );
            }
        }    
        else
        {
            sRespuesta -> status = _ERROR_EN_MENSAJE;
            mysnprintf(cMensaje,254,"No se logro abrir conexion a la base de datos: %.32s en el servidor: %.16s con el usuario: %.32s",sSolicitud->cBD, sSolicitud->cIpBD, sSolicitud->cUsuario );
            logx( cMensaje, _LOGINFO_ );
            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
            mysnprintf( sRespuesta->cDevMensaje,254,"%s", cMensaje );
        }
    
}
long Cwsprestamos00028::grabarEnCarteraPrestamos( C_ODBC *odbcTiendaNumero ,C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta)
{
	int iFlagSaldo=0,i=0,iFlag=0;
    long lInteresFinanciamiento=0,lAuxiliar=0,lSaldoPrestamoAnterior=0,lComision=0,lImportePrestamo=0,lSaldoActual=0,lSaldoFecha=0;
	char cMensaje[90]={0}, cTexto[500]={0};
	double dIntSobre=0;
	
		if( sSolicitud ->lSaldoPrestamo >0 )
		{
			iFlagSaldo=2;
		}
		else
		{
			iFlagSaldo=1;
		}
		
		if( iFlagSaldo > 1 )
		{
			lAuxiliar= sSolicitud ->lSaldoPrestamo-(sSolicitud ->lSaldoPrestamo - sSolicitud ->lSaldaCon)+ sSolicitud -> lInteresAdicional;
			dIntSobre=( (double)((double)sSolicitud -> iTasaInteresPrestamos/(double)10000) );
			lInteresFinanciamiento=(long)( (double)(sSolicitud ->lImporte + lAuxiliar)*dIntSobre);
			lSaldoPrestamoAnterior= sSolicitud ->lSaldaCon;
			lImportePrestamo= sSolicitud ->lImporte+ lComision +  sSolicitud ->lSaldaCon;
		}
		else
		{
			lAuxiliar=0L;
			dIntSobre=( (double)( (double)sSolicitud->iTasaInteresPrestamos/(double)10000) );
			lInteresFinanciamiento=(long)( (double)(sSolicitud->lImporte)*dIntSobre );
			lSaldoPrestamoAnterior=0L;
			sRespuesta ->lImportePrestamo = sSolicitud->lImporte+lComision+ sSolicitud -> lImporteSeguroClub;
		}

		lSaldoFecha= sSolicitud ->lSaldoPrestamo;
	
	return lSaldoFecha;
}


long Cwsprestamos00028::obtenerReciboCajas(C_ODBC *odbcTiendaNumero, int iFlag, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta)
{
	long lNumFolio=0L;
    char sSqlTxt[128] = {0}, cLog[250]={0};
    
    mysnprintf(sSqlTxt, sizeof(sSqlTxt)-1,"select gnincrementarfolio('C', '%d', '%d', '%d' ) ",sSolicitud -> iCaja, FOLIOC_RECIBO, iFlag);

    CRegistro FolioCoppel( odbcTiendaNumero,true );

    FolioCoppel.agregarCampoEntero("gnincrementarfolio",DT_ENTERO_LARGO);

    if( !FolioCoppel.Exec( sSqlTxt ) )
    {
		sRespuesta->status = E00001_ERROR_QUERY;	   
    }
	else
	{
		FolioCoppel.activarCols();
		if( FolioCoppel.Leer() )
		{
			lNumFolio = FolioCoppel.valorLong( "gnincrementarfolio" );	
		}
	}

	return lNumFolio;
}
bool Cwsprestamos00028::crearTablaTmpCrCancPrestamos(C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
	char sSqlTxt[256] = {0},cLog[250]={0};
	bool bRegresa=false;

	CRegistro crearTablaTmpCrCancPrestamos1( odbcCartera, false );
    mysnprintf(sSqlTxt, 256,"CREATE TABLE IF NOT EXISTS tmpcrcancelacionprestamos ( LIKE crcancelacionprestamos INCLUDING DEFAULTS ) WITHOUT OIDS;"
    "DELETE FROM tmpcrcancelacionprestamos WHERE cliente='%d';",sSolicitud ->lCliente);
  

	if( !crearTablaTmpCrCancPrestamos1.Exec(sSqlTxt) )
	{	
		sRespuesta->status = E00001_ERROR_QUERY;	
    }
	else
	{
		bRegresa=true;
	}

	return bRegresa;
}

bool Cwsprestamos00028::crearTablaTmpCrPrestamos(C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta)
{
	char sSqlTxt[265] = {0},cLog[250]={0};
	bool bRegresa=false;

	CRegistro crearTablaTmpCrPrestamos1( odbcCartera,false );
    mysnprintf(sSqlTxt, 256,"CREATE TABLE IF NOT EXISTS tmpcrprestamos ( LIKE crprestamos INCLUDING DEFAULTS ) WITHOUT OIDS;"
    "DELETE FROM tmpcrprestamos WHERE cliente=%d;",sSolicitud ->lCliente);

	if( !crearTablaTmpCrPrestamos1.Exec( sSqlTxt ) )
	{		
		sRespuesta->status = E00001_ERROR_QUERY;	
    }
	else
	{
		bRegresa=true;
	}

	return bRegresa;
}
bool Cwsprestamos00028::crearTablaTmpCacarmov(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta)
{
	char sSqlTxt[265] = {0},cLog[250]={0};
	bool bRegresa=false;

	CRegistro ccrearTablaTmpCacarmov1( odbcTiendaNumero,false );
    mysnprintf(sSqlTxt, 256,"CREATE TEMPORARY TABLE IF NOT EXISTS tmpcacarmov( LIKE cacarmov INCLUDING DEFAULTS ) WITHOUT OIDS; "
    "DELETE FROM tmpcacarmov WHERE caja=%d;",sSolicitud ->iCaja);
	if( !ccrearTablaTmpCacarmov1.Exec( sSqlTxt ) )
	{
		sRespuesta->status = E00001_ERROR_QUERY;	
    }
	else
	{
		bRegresa=true;
	}

	return bRegresa;
}
bool Cwsprestamos00028::grabarLiquidacionPorNuevoPrest(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, long lRecibo,sRespuestaServicio *sRespuesta)
{
	char cNombreTabla[50]={0}, cTexto[64] = { 0 }, cLog[500] = {0};
	bool bRespuesta = false;
    int iFlagBonificacion =0,iDia = 1, iMes = 1, iYear = 1900;
    long lcomisionNeg =0,lTotalBonificacion=0;
    CRegistro inTmpCaCarmov( odbcTiendaNumero, false);
    SqlTimeStamp tFecha;

    inTmpCaCarmov.agregarCampoChar( "clave", 3 );
    inTmpCaCarmov.agregarCampoChar( "tipomovimiento", 3 );
    inTmpCaCarmov.agregarCampoEntero( "caja", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "ciudad", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "factura", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "importe", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "cliente", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "importesaldacon", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "bonificacion", DT_ENTERO );
    sRespuesta ->lTotalBonificacion = sSolicitud ->lSaldoAnt- sSolicitud ->lSaldaCon;
    if(sRespuesta ->lTotalBonificacion >0){sSolicitud -> iFlagBonificacion=1;}
    inTmpCaCarmov.agregarCampoEntero( "saldocuenta", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "efectuo", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "tienda", DT_ENTERO );
    inTmpCaCarmov.agregarCampoFecha( "fecha" );
    inTmpCaCarmov.agregarCampoEntero( "recibo", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "saldoinicial", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "saldofinal", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "vencidoinicial", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "minimoinicial", DT_ENTERO );
    inTmpCaCarmov.agregarCampoChar( "tipoconvenio", 2 );
    inTmpCaCarmov.agregarCampoChar( "subtipoconvenio", 2 );
    inTmpCaCarmov.agregarCampoChar( "ejercicio", 12 );
    inTmpCaCarmov.agregarCampoEntero( "base", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "cantidadmeses", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "cantidadseguros", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "cantidadsegurosanterior", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "causabaja", DT_ENTERO );
    inTmpCaCarmov.agregarCampoFecha( "fechasaldacon" );
    inTmpCaCarmov.agregarCampoEntero( "interes", DT_ENTERO );
    inTmpCaCarmov.agregarCampoEntero( "comision", DT_ENTERO );
    inTmpCaCarmov.agregarCampoChar( "ipcarteracliente", 15 );
    inTmpCaCarmov.activarCols();
    inTmpCaCarmov.prepararInsert("tmpcacarmov");

    inTmpCaCarmov.valorChar( "clave", "S" );
    inTmpCaCarmov.valorChar( "tipomovimiento", "S" );
    inTmpCaCarmov.valorShort( "caja", (short)sSolicitud ->iCaja );
    inTmpCaCarmov.valorShort( "ciudad", (short)sSolicitud -> iCiudad );
    inTmpCaCarmov.valorLong( "factura", sSolicitud -> lFactura );
    inTmpCaCarmov.valorLong( "importe", (long)sSolicitud -> lSaldo*100 );
    inTmpCaCarmov.valorLong( "cliente", sSolicitud ->lCliente );
    inTmpCaCarmov.valorLong( "importesaldacon", sSolicitud ->importesaldacon );
    inTmpCaCarmov.valorLong( "bonificacion", sRespuesta ->lTotalBonificacion );
    inTmpCaCarmov.valorLong( "saldocuenta", 0 );
    tFecha.ponerFecha( iDia, iMes, iYear );
    inTmpCaCarmov.valorFecha( "fechasaldacon",&tFecha );
    inTmpCaCarmov.valorLong( "efectuo", sSolicitud ->lEmpleado );
    inTmpCaCarmov.valorLong( "tienda", sSolicitud ->iNumTienda );
    mysnprintf( cTexto, 100, "%.17s", sSolicitud->lFecha );
    iYear = valorCampo( cTexto, 4 );
    iMes= valorCampo( &cTexto[5], 2 );
    iDia= valorCampo( &cTexto[8], 2 );
    tFecha.ponerFecha( iDia, iMes, iYear );
    inTmpCaCarmov.valorFecha( "fecha",&tFecha );
    inTmpCaCarmov.valorLong( "recibo", lRecibo) ;
    inTmpCaCarmov.valorLong( "saldoinicial", 0 );
    inTmpCaCarmov.valorLong( "saldofinal", 0 );
    inTmpCaCarmov.valorLong( "vencidoinicial", 0 );
    inTmpCaCarmov.valorLong( "minimoinicial", 0 );
    inTmpCaCarmov.valorChar( "tipoconvenio", "" );
    inTmpCaCarmov.valorChar( "subtipoconvenio", "" );
    inTmpCaCarmov.valorChar( "ejercicio", "" );
    inTmpCaCarmov.valorLong( "base", sSolicitud->abonoMensual );
    inTmpCaCarmov.valorLong( "cantidadmeses", 0 );
    inTmpCaCarmov.valorLong( "cantidadseguros", 0 );
    inTmpCaCarmov.valorLong( "cantidadsegurosanterior", 0 );
    inTmpCaCarmov.valorLong( "causabaja", 0 );
    inTmpCaCarmov.valorLong( "interes",  sSolicitud -> lInteresFinanciamiento );
    inTmpCaCarmov.valorLong( "comision", 0 );
    inTmpCaCarmov.valorChar( "ipcarteracliente", sSolicitud->cIpCarteraCliente );



    if (inTmpCaCarmov.Insert())
    {
        if (inTmpCaCarmov.Commit())
        {
            bRespuesta = true;
        }
        else
        {
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
            mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
            sRespuesta->status = _ERROR_EN_MENSAJE;
            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }
    }
    else
    {
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
        mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
        sRespuesta->status = _ERROR_EN_MENSAJE;
        sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
    }

	return bRespuesta;
}

bool Cwsprestamos00028::grabarPrestamo(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,long lRecibo,sRespuestaServicio *sRespuesta)
{
	
	char cNombreTabla[50]={0}, cTexto[64] = { 0 }, cLog[500] = {0};
	long lComision=0, lIntFinanciamiento = 0L,lAuxiliar=0,lInteresFinanciamiento=0;
	bool bContinuar=true;
    int iFlagBonificacion =0,iDia = 1, iMes = 1, iYear = 1900;
	double dIntSobre=0;
	bool bRespuesta = false;
	long lFolioClubVencido=0;
	int iMostrarError = 0;

	div_t div_result;
    SqlTimeStamp tFecha;
	mymemset(cNombreTabla,0,sizeof(cNombreTabla));

    CRegistro inTmpCaCarmov( odbcTiendaNumero, true);
	lComision=0L;
    inTmpCaCarmov.agregarCampoChar( "clave", 3 );//
    inTmpCaCarmov.agregarCampoChar( "tipomovimiento", 3 );//
    inTmpCaCarmov.agregarCampoEntero( "caja", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "ciudad", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "factura", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "importe", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "cliente", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "importesaldacon", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "bonificacion", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "saldocuenta", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "efectuo", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "tienda", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoFecha( "fecha" );//
    inTmpCaCarmov.agregarCampoEntero( "recibo", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "saldoinicial", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "saldofinal", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "vencidoinicial", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "minimoinicial", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoChar( "tipoconvenio", 2 );//
    inTmpCaCarmov.agregarCampoChar( "subtipoconvenio", 2 );//
    inTmpCaCarmov.agregarCampoChar( "ejercicio", 12 );//
    inTmpCaCarmov.agregarCampoEntero( "base", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "cantidadmeses", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "cantidadseguros", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "cantidadsegurosanterior", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "causabaja", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoFecha( "fechasaldacon" );//
    inTmpCaCarmov.agregarCampoEntero( "interes", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "comision", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoChar( "ipcarteracliente", 15 );//
    inTmpCaCarmov.agregarCampoEntero( "numerosubcuenta", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "importeclub", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "parametricocte", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoChar( "puntualidadcte", 3 );//
    inTmpCaCarmov.agregarCampoEntero( "parametricotda", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "puntajefinal", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoEntero( "factorprestamo", DT_ENTERO );//
    inTmpCaCarmov.agregarCampoChar( "docfiscal", 15 );//
    inTmpCaCarmov.agregarCampoChar( "serieintbnf", 15 );//
    inTmpCaCarmov.agregarCampoEntero( "tasainteres", DT_ENTERO );//
    

    inTmpCaCarmov.activarCols();
    inTmpCaCarmov.prepararInsert("tmpcacarmov");

    inTmpCaCarmov.valorChar( "clave", "S" );
    inTmpCaCarmov.valorChar( "tipomovimiento", "A" );
    inTmpCaCarmov.valorShort( "caja", (short)sSolicitud ->iCaja );
    inTmpCaCarmov.valorShort( "ciudad", (short)sSolicitud -> iCiudad );
    inTmpCaCarmov.valorLong( "factura", (int)sSolicitud -> lFactura );
    inTmpCaCarmov.valorLong( "importe", (int)(sSolicitud -> lImporte + sSolicitud ->lImporteSeguroClub)*100 );
    inTmpCaCarmov.valorLong( "cliente", (int)(sSolicitud ->lCliente ));
    inTmpCaCarmov.valorLong( "importesaldacon", 0 );
    inTmpCaCarmov.valorLong( "bonificacion", 0 );
    inTmpCaCarmov.valorLong( "saldocuenta", sSolicitud ->importetotalAnual );
    tFecha.ponerFecha( iDia, iMes, iYear );
    inTmpCaCarmov.valorFecha( "fechasaldacon",&tFecha );
    inTmpCaCarmov.valorLong( "efectuo", sSolicitud ->lEmpleado );
    inTmpCaCarmov.valorLong( "tienda", sSolicitud ->iNumTienda );
    mysnprintf( cTexto, 100, "%.17s", sSolicitud->lFecha );
    iYear = valorCampo( cTexto, 4 );
    iMes= valorCampo( &cTexto[5], 2 );
    iDia= valorCampo( &cTexto[8], 2 );
    tFecha.ponerFecha( iDia, iMes, iYear );
    mysnprintf( cLog,sizeof(cLog), "fechaprimercompra [%.17s]", &tFecha );
    inTmpCaCarmov.valorFecha( "fecha",&tFecha );
    inTmpCaCarmov.valorLong( "recibo", (long)lRecibo);
    inTmpCaCarmov.valorLong( "saldoinicial", 0 );
    inTmpCaCarmov.valorLong( "saldofinal", 0 );
    inTmpCaCarmov.valorLong( "vencidoinicial", sSolicitud ->lSaldaCon );
    inTmpCaCarmov.valorLong( "minimoinicial", 0 );
    inTmpCaCarmov.valorChar( "tipoconvenio", "1" );
    inTmpCaCarmov.valorChar( "subtipoconvenio", "2" );
    inTmpCaCarmov.valorChar( "ejercicio", "" );
    div_result = div( sSolicitud ->lSaldoActual, 12 );
    if ( (div_result.rem)!=0 )
    {
        inTmpCaCarmov.valorLong( "base", sSolicitud->abonoMensual ); //Abono Mensual
    }
    else
    {
        inTmpCaCarmov.valorLong( "base", sSolicitud->abonoMensual ); //Abono Mensual
    }
    inTmpCaCarmov.valorLong( "numerosubcuenta", sSolicitud ->lEmpleado);
    inTmpCaCarmov.valorLong( "importeclub", 0);
    inTmpCaCarmov.valorLong( "cantidadmeses", 0 );
    inTmpCaCarmov.valorLong( "cantidadseguros", 0 );
    inTmpCaCarmov.valorLong( "cantidadsegurosanterior", 0 );
    inTmpCaCarmov.valorLong( "causabaja", 0 );

    dIntSobre = ( (double)((double)(sSolicitud ->iTasaInteresPrestamos)/(double)10000) );
    lAuxiliar= sSolicitud ->lSaldoPrestamo-(sSolicitud ->lSaldoPrestamo-sSolicitud ->lSaldaCon)+sSolicitud ->lInteresAdicional;
    lInteresFinanciamiento = (long)( (double)(sSolicitud ->lImporte+ lAuxiliar)*dIntSobre );
    inTmpCaCarmov.valorLong( "interes",  sSolicitud -> lInteresFinanciamiento );

    inTmpCaCarmov.valorLong( "comision", 0 );
    inTmpCaCarmov.valorChar( "ipcarteracliente", sSolicitud->cIpCarteraCliente );
    inTmpCaCarmov.valorLong( "parametricocte", sSolicitud ->lParPrestamos );// ParPrestamo de la crCliente
    inTmpCaCarmov.valorLong( "parametricotda", sSolicitud->parametricotda );//// ParametroPrestamos de la gnDominio
    inTmpCaCarmov.valorChar( "puntualidadcte", sSolicitud->cPuntualidad );// Puntualidad de la crCliente
    inTmpCaCarmov.valorLong( "puntajefinal", sSolicitud->iPuntajeParametricoFinal );
    inTmpCaCarmov.valorLong( "factorprestamo", sSolicitud ->factorprestamo );
    inTmpCaCarmov.valorChar( "docfiscal", "");
    inTmpCaCarmov.valorChar( "serieintbnf",  sSolicitud ->cTipoDoc);
    inTmpCaCarmov.valorLong( "tasainteres", sSolicitud ->tasainteres );

	
    if (inTmpCaCarmov.Insert())
    {
        if (inTmpCaCarmov.Commit())
        {
            bRespuesta = true;
        }
        else
        {
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
            mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
            sRespuesta->status = _ERROR_EN_MENSAJE;
            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }
    }
    else
    {
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
        mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
        sRespuesta->status = _ERROR_EN_MENSAJE;
        sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        mysnprintf(cLog, sizeof(cLog)-1, "Error al consultar parametro en Insert. [%.150s]", inTmpCaCarmov.error()); 
        logx( cLog, _LOGINFO_ );
    }

	return bRespuesta;
}
int Cwsprestamos00028::transaccionDB( C_ODBC *odbc, char *cQuery, sRespuestaServicio *sRespuesta )
{
    int iRespuesta = _ERROR_QUERY_; 

    CRegistro comandoDB( odbc); 

    if( comandoDB.Exec( cQuery ) )
    {
        iRespuesta = _OK_;
    }
    else
    {
        sRespuesta->status = _ERROR_DE_SERVIDOR;                        
        mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");

        sRespuesta->iDevStatus = _ERROR_QUERY_;
        mysnprintf(sRespuesta->cDevMensaje, 255,"ERROR AL EJECUTAR QUERY.1 [%.200s]", comandoDB.error() );
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
    }
    return iRespuesta;
}

bool Cwsprestamos00028::actualizarPrestamos(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja )
{
	char sSqlTxt[500]={0};
	bool bRegresa=true;
	short iCapturoSeguro=0, iCapturoTransferencia=0;
	
	if ( sRespuesta ->lTotalBonificacion > 0 ){
        mysnprintf( sSqlTxt,255, "SELECT foliorecibo, factura FROM caactualizarprestamos24('%d','%d','%d','%d','%s','%ld', '%s', '%d');", 0,sSolicitud->iCaja, iCapturoSeguro, iCapturoTransferencia,"", sSolicitud->lSaldoTotal,
		datosCaja ->cReferenciaMsj,sRespuesta->lTotalBonificacion );
	}
	else
	{
        mysnprintf( sSqlTxt,255, "SELECT foliorecibo, factura FROM caactualizarprestamos24('%d','%d','%d','%d','%s','%ld', '%s', '%d');", 0,sSolicitud->iCaja, iCapturoSeguro, iCapturoTransferencia,"", sSolicitud->lSaldoTotal,
		datosCaja ->cReferenciaMsj,sRespuesta->lTotalBonificacion );
	}
    CRegistro actualizarTablasPrestamos( odbcTiendaNumero, false );
    actualizarTablasPrestamos.agregarCampoEntero( "foliorecibo", DT_ENTERO );
    actualizarTablasPrestamos.agregarCampoEntero( "factura", DT_ENTERO );

	if( !actualizarTablasPrestamos.Exec( sSqlTxt ) )
	{
        sRespuesta->iDevStatus = _ERROR_QUERY_;
        mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY caactualizarprestamos24 [%.200s]", actualizarTablasPrestamos.error() );
        logx(sRespuesta->cDevMensaje,_LOGINFO_ );
        transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
        bRegresa=false;
	}
	else
	{
		actualizarTablasPrestamos.activarCols();
		if(actualizarTablasPrestamos.leer())
		{
            //sRespuesta -> Prestamo = 1;
            sRespuesta-> lRecibo = actualizarTablasPrestamos.valorLong("foliorecibo");//folio de notas pendientes
            sRespuesta-> lFacturaPrestamos = actualizarTablasPrestamos.valorLong("factura");//folio de notas pendientes

             //mysprintf(sRespuesta->cDevMensaje,"Si ejecuto bien la funcion caactualizarprestamos24 %s", sSqlTxt);
             //logx(sRespuesta->cDevMensaje,_LOGINFO_ );
           // transaccionDB( odbcTiendaNumero, "COMMIT" ,sRespuesta);
		}
		else
		{
            sRespuesta->iDevStatus = _ERROR_QUERY_;
            mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY actualizarTablasPrestamos [%.200s]", actualizarTablasPrestamos.error() );
            logx(sRespuesta->cDevMensaje,_LOGINFO_ );
            transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
			bRegresa = false;
		}
	}
	return bRegresa;
}

bool Cwsprestamos00028::grabarInformacionPrestamosCertificacion( C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iFlagAutorizoPrestamo )
{
	
	char cSql[2000] = {0}, cTexto[1025] = {0};
	bool bRegresa=false, bEjecutaCommit=false;
    int iFlagTestigo = 0;
	long lSaturacion = 0L, lPrestamo = 0L, lBaseTotal = 0L, lLineaDeCreditoReal = 0L, lFactorLineaReal = 0L;
	int iRespuesta	 = 0;
	char cFechaAlta[15] = { 0 }, cFechaNac[15] = { 0 }, cSituacionEspecial[2] = {0}, cSexo[2] = {0}, cEstadoCivil[2] = {0};
    int iCausaSitEsp = 0, iParRiesgoMuebles = 0, ipuntajesaldoprestamoanterior = 0;
    int iSaldo_ropa5x = 0, iSaldo_prestamos18x = 0, iSaldo_prestamos24x = 0, iSaldo_muebles24x = 0, iClienteEspecial = 0, iFLagModificacionParametrico = 0, iAntiguedadMeses = 0, iPtsAntiguedad = 0;

    logx("::::::::::::::::ENTRO A grabarInformacionPrestamosCertificacion::::::::::::::::::",_LOGINFO_ );

    iFLagModificacionParametrico = obtenerFlag( odbcTiendaNumero,'C', FLAGC_MODIFICACION_PARAMETRICO_PRESTAMOS, sRespuesta);
    mysnprintf( cTexto,40, "EL iFLagModificacionParametrico:: %d", iFLagModificacionParametrico);
    logx(cTexto,_LOGINFO_ );

	if ( iFlagAutorizoPrestamo == 0  )
	{
		bEjecutaCommit= true;
	}
	else 
	{
		lPrestamo = sSolicitud->lImporte;
	}

    CRegistro consultaCrCliente( odbcCartera, false );

    mysnprintf( cSql,500, "SELECT situacionespecial, causasitesp, abonopromedio, lineadecreditoreal, sexo, fechanacimiento, estadocivil, fechaalta, parriesgomuebles, mesesTranscurridos FROM crcliente where cliente = %d ", sSolicitud->lCliente );
    logx(cSql,_LOGINFO_ );
    logx("qUERY DE CRCLIENTE",_LOGINFO_ );
    consultaCrCliente.agregarCampoChar("situacionespecial", 2);
    consultaCrCliente.agregarCampoEntero("causasitesp", 2);
    consultaCrCliente.agregarCampoEntero("abonopromedio", DT_ENTERO_LARGO);
    consultaCrCliente.agregarCampoEntero("lineadecreditoreal", DT_ENTERO_LARGO);
    consultaCrCliente.agregarCampoChar("sexo", 2);
    consultaCrCliente.agregarCampoChar("fechanacimiento", 15);
    consultaCrCliente.agregarCampoChar("estadocivil", 2);
    consultaCrCliente.agregarCampoChar("fechaalta", 15);
    consultaCrCliente.agregarCampoEntero("parriesgomuebles", DT_ENTERO_LARGO);
    consultaCrCliente.agregarCampoEntero("mesesTranscurridos", DT_ENTERO);

	if(!consultaCrCliente.Exec(cSql))
	{
        mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY select crcliente [%.200s]", consultaCrCliente.error() );
        logx(sRespuesta->cDevMensaje,_LOGINFO_ );
	}
	else
    {
        consultaCrCliente.activarCols();
        consultaCrCliente.Leer();
        
        mysnprintf(cSituacionEspecial, 4, "%s", consultaCrCliente.valorChar("situacionespecial") );
        iCausaSitEsp = consultaCrCliente.valorShort("causasitesp");
        lBaseTotal = consultaCrCliente.valorLong("abonopromedio");
        lLineaDeCreditoReal = consultaCrCliente.valorLong("lineadecreditoreal");
        mysnprintf(cSexo, 2, "%s", consultaCrCliente.valorChar("sexo") );
        mysnprintf(cFechaNac, 15, "%s", consultaCrCliente.valorChar("fechanacimiento") );
        mysnprintf(cEstadoCivil, 2, "%s", consultaCrCliente.valorChar("estadocivil") );
        mysnprintf(cFechaAlta, 15, "%s", consultaCrCliente.valorChar("fechaalta") );
        iParRiesgoMuebles = consultaCrCliente.valorLong("parriesgomuebles");
        iAntiguedadMeses = consultaCrCliente.valorLong("mesesTranscurridos");

    }

    CRegistro CuatroPrestamos( odbcCartera ,false );

    CuatroPrestamos.agregarCampoEntero("crnumerodeprestamos",DT_ENTERO_LARGO);
    CuatroPrestamos.valorLong("cliente",sSolicitud->lCliente );

	mysnprintf(cSql,1024,"SELECT crnumerodeprestamos from crnumerodeprestamos(%ld)", sSolicitud->lCliente);
    logx(cSql, _LOGINFO_);

	if( !CuatroPrestamos.Exec( cSql ) )
	{
        iRespuesta = CuatroPrestamos.valorLong("crnumerodeprestamos");
		logx("NO JALO LA crnumerodeprestamos", _LOGINFO_);
        bRegresa = false;
	}
	else
	{
		CuatroPrestamos.activarCols();
        logx("SI JALO crnumerodeprestamos", _LOGINFO_);
        logx(cSql, _LOGINFO_);

		while (CuatroPrestamos.Leer() )
		{
            iRespuesta = CuatroPrestamos.valorLong("crnumerodeprestamos");
            logx("SI JALO a leer", _LOGINFO_);

			if( iFlagAutorizoPrestamo == 0 )
			{
				iRespuesta;
			}
			else
			{
				iRespuesta += 1;
			}
		}
	}

    CRegistro obtenerFactor( odbcTiendaNumero );

    mysnprintf(cSql, 80, "select factorlinea from gndominio", ' ');

    obtenerFactor.valorLong("factorlinea");

	if ( obtenerFactor.Exec(cSql) )
	{
		obtenerFactor.activarCols();
		obtenerFactor.leer();
        {
            lFactorLineaReal = obtenerFactor.valorLong("factorlinea");
        }
	}
    else
    {
		sRespuesta->status = E00001_ERROR_QUERY;
        logx("NO JALO LA GNDOMINIO FACTOR", _LOGINFO_);
    }

	if ( obtenerCasoNuevoCliente( odbcTiendaNumero, sSolicitud, sRespuesta) ) 
    {
        iFlagTestigo = 1; 
    }
    logx("SI JALO a obtenerCasoNuevoCliente", _LOGINFO_);
	if(iFLagModificacionParametrico == 1)
	{   
        logx(" iFLagModificacionParametrico = 1", _LOGINFO_);
		if(sSolicitud->iGrupo == 1)
		{
			mysnprintf(cSql,1024, "	SELECT puntaje FROM tdParametricoAltoRiesgoNuevo WHERE tipoVariable = 201 AND %ld BETWEEN valorMinimo and valorMaximo ", iAntiguedadMeses);
		}
		else
		{
			mysnprintf(cSql,1024, "SELECT puntaje FROM cat_puntajesprestamos WHERE nom_variable = 'ANTIGUEDAD EN MESES' AND %ld BETWEEN num_valorminimo AND num_valormaximo", iAntiguedadMeses);
		}

		CRegistro ptsAntiguedadNuevo(odbcTiendaNumero, false);

        //ptsAntiguedadNuevo.valorShort("puntaje");
        ptsAntiguedadNuevo.agregarCampoEntero("crnumerodeprestamos",DT_ENTERO_CORTO);

		logx(cSql, _LOGINFO_);

		if ( !ptsAntiguedadNuevo.Exec( cSql ))
		{
            sRespuesta->iDevStatus = E00001_ERROR_QUERY;
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA primera validacion flagmodificacionparametrico");
            mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gnconsultarflag, ERROR:[%.150s]", ptsAntiguedadNuevo.error() );
            sRespuesta->status = _ERROR_DE_SERVIDOR;
        }
		else
		{
			ptsAntiguedadNuevo.activarCols();
			while ( ptsAntiguedadNuevo.Leer() )
			{
				iPtsAntiguedad =  ptsAntiguedadNuevo.valorShort("puntaje");
			}
		}
	}
	else
	{
            logx(" iFLagModificacionParametrico :0", _LOGINFO_);

		if(iFlagTestigo == 0)
		{
			CRegistro ptsAntiguedadNuevo(odbcTiendaNumero, false);
	
			mysnprintf(cSql,1024, "	SELECT puntaje FROM tdParametricoAltoRiesgoNuevo WHERE tipoVariable = 201 AND %ld BETWEEN valorMinimo and valorMaximo ", iAntiguedadMeses);
			
			if ( !ptsAntiguedadNuevo.Exec( cSql ) )
			{
                sRespuesta->iDevStatus = E00001_ERROR_QUERY;
                mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN el else validacion flagtestigo");
                mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gnconsultarflag, ERROR:[%.150s]", ptsAntiguedadNuevo.error() );
                sRespuesta->status = _ERROR_DE_SERVIDOR;
			}
			else
			{
				ptsAntiguedadNuevo.activarCols();
				while ( ptsAntiguedadNuevo.Leer() )
				{
					iPtsAntiguedad =  ptsAntiguedadNuevo.valorShort("puntaje");
				}
			}
		}
		else
		{
			CRegistro ptsAntiguedad(odbcTiendaNumero, false);
	
			mysnprintf(cSql,1024, "SELECT puntaje FROM tdParametricoAltoRiesgo WHERE tipoVariable = 101 AND %ld BETWEEN valorMinimo and valorMaximo ", iAntiguedadMeses);
			
			if (!ptsAntiguedad.Exec( cSql ))
			{
                sRespuesta->iDevStatus = E00001_ERROR_QUERY;
                mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA primera validacion flagmodificacionparametrico");
                mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gnconsultarflag, ERROR:[%.150s]", ptsAntiguedad.error() );
                sRespuesta->status = _ERROR_DE_SERVIDOR;
			}
			else
			{
				ptsAntiguedad.activarCols();
				while ( ptsAntiguedad.Leer() )
				{
					iPtsAntiguedad =  ptsAntiguedad.valorShort("puntaje");
				}
			}
		}
	} 
    if(sSolicitud ->iGrupo ==0 ||sSolicitud ->iGrupo ==2 || sSolicitud ->iGrupo ==3  )
    {
		mysnprintf(cSql,1024, "	SELECT puntaje  FROM cat_puntajesprestamos WHERE nom_variable = 'PUNTOS INICIALES';", "");
    }
    else
    {
		mysnprintf(cSql,1024, "	SELECT valor as puntaje FROM tdconfiguracion WHERE elemento = 'PUNTOS_INICIALES_1175';", "");
    }
    CRegistro puntaje(odbcTiendaNumero, false);
        puntaje.agregarCampoEntero("puntaje",DT_ENTERO_CORTO);

    if ( puntaje.Exec(cSql) )
	{
		puntaje.activarCols();
		puntaje.leer();
        {
            sSolicitud ->iPuntosIniciales = puntaje.valorShort("puntaje");
        }
	}
    else
    {
		sRespuesta->status = E00001_ERROR_QUERY;
        logx("Error en consultar Puntaje", _LOGINFO_);
    }

    long iSaldoPrestamos12x = sSolicitud->lSaldoTotal;
    if (sSolicitud->lLineaRealCredPesos > 0){
       lSaturacion = sSolicitud->SaldoFactorizadoTotalP / sSolicitud->lLineaRealCredPesos * 100;
    }else{
        lSaturacion = 0;
    }
    //lSaturacion = sSolicitud->SaldoFactorizadoTotalP / sSolicitud->lLineaRealCredPesos * 100;
   // int iSaldo_ropa8x = 0, iSaldo_muebles12x = 0, iSaldo_muebles18x = 0;
    logx("cSql", _LOGINFO_);
	mysnprintf(cSql, 1500, "SELECT cagrabarinformacionprestamos02('%d','%d','%s','%d','%ld','%ld','%ld','%ld','%d','%ld','%ld','%ld','%s','%s','%s','%s','%ld','%s', '%d','%d','%ld', '%ld','%d','%ld','%f','%ld','%s','%d', '%d', '%d','%d','%d','%d','%d','%d','%d','%ld','%d','%ld','%d','%ld','%d','%d','%ld','%d')", sSolicitud->iCaja, iFlagTestigo, cSituacionEspecial, iCausaSitEsp, sSolicitud->SaldoCertificado,sSolicitud->SaldoCertificado, sSolicitud->VencidoTotal, sSolicitud->abonosCertificado, iClienteEspecial, lLineaDeCreditoReal,sSolicitud->lLineaRealCredPesos, sSolicitud->margenCreditoReal, cSexo, cFechaNac, cEstadoCivil,cFechaAlta, lSaturacion , "C", sSolicitud->iPuntajeParametricoFinal, iFlagAutorizoPrestamo,sSolicitud->lCliente, lPrestamo, sSolicitud->iNumTienda, sSolicitud->lNumEmpleado, sSolicitud -> ffactor,sSolicitud->iSumaPuntajeVariables, sSolicitud->cPuntualidad, iParRiesgoMuebles, iSaldo_ropa5x, sSolicitud->iSaldoRopa8x,sSolicitud->iSaldoMuebles12x, sSolicitud->iSaldoMuebles18x, iSaldo_muebles24x, iSaldoPrestamos12x, iSaldo_prestamos18x,iSaldo_prestamos24x, sSolicitud->lMontoMaximoPrestar,sSolicitud->iPuntosIniciales, iPtsAntiguedad, sSolicitud->iSaturacionCte,sSolicitud->lParPrestamos, iRespuesta, sSolicitud -> ipuntajesaldoprestamoanterior, sSolicitud->lSaldaCon, sSolicitud->iGrupo);
    logx(cSql, _LOGINFO_);

		CRegistro infoPrestamo( odbcCartera, bEjecutaCommit );
    
		if( !infoPrestamo.Exec( cSql ) ) 
		{
            mysnprintf(cTexto,1000,"NO FUNCIONO LA EJECUCION DEL QUERY ::  %s ", cSql);
            logx(cTexto, _LOGINFO_);
		    sRespuesta->status = E00001_ERROR_QUERY;
        }
		else
		{
             logx("Si funciono la ejecuicion del certificado", _LOGINFO_);
			infoPrestamo.activarCols();
			if( infoPrestamo.Leer() )
			{
				bRegresa = true;
			}
		}

	return bRegresa;
}
bool Cwsprestamos00028::interfaceInsertarMovtoPAJLocal(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja )
{
	bool bRegresa = false;
   // char cParametros1[101] = {0};
	// `int iPid = 0;
	// char cTipoRetiro;
	// long lValor = 0L,lPrestamoPAJ=0;
	// CString sDato;
	// HRESULT hr = 0;

	// datosCaja ->iTienda = iTienda;
	// datosCaja ->cArea = 'C';
	// datosCaja ->iCaja = iCaja; 
	// hr = StringCchPrintf( datosCaja ->cIp,17, "%s", (LPTSTR)(LPCTSTR) sServer ); 
	// datosCaja ->lEmpleado = lEmpleado;
	// datosCaja ->iMostrarError = iMuestraMsg;
	// datosCaja ->iClaveMsj = MOTOR_MOVIMIENTOS_BANCARIOS;					// Motor que se Iniciara en el protheus esto indica que tabla se grabara.

	// mymemset( datosCaja ->cReferenciaMsj, 0, sizeof( datosCaja ->cReferenciaMsj ) );
	// mymemset( datosCaja ->cParametros, 0, sizeof( datosCaja ->cParametros ) );

	// hr = StringCchPrintf( datosCaja ->cReferenciaMsj ,15, "%.13s", cGpoTransaccion  );
	
	// cTipoRetiro = 'P';

	// mysnprintf( cParametros1,100, "%08ld%08ld%06ld%02d",sSolicitud->lImporte, sSolicitud->lCliente, sRespuesta->lFactura, sSolicitud->iCaja );
    logx("ENTRO AL METODO PARA ENTRAR A gnGenerarMovimientosReembolsoLocal02", _LOGINFO_);
   // logx(cParametros1, _LOGINFO_);
	// datosCaja ->cEsperarMotor = 'N';										// indica si va esperar el motor a que termine de procesar protheus.
	if ( gnGenerarMovimientosReembolsoLocal02( odbcTiendaNumero, sSolicitud, sRespuesta, PAJ_PRESTAMOS, false, INSERTAR_PROTHEUS,datosCaja) )
	{
        bRegresa = true;
	// 	if ( gnInsertarDatosTablasLocales( &odbcTiendaNumero, datosCaja -> iPid, false ) )//datosCaja ->iClaveMsj
	// 	{
	 		
	// 	}
	}

	return bRegresa;
}

bool Cwsprestamos00028::gnGenerarMovimientosReembolsoLocal02( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, int iProceso, bool bCommit, char cTipoProceso,DatosCajaSudamerica *datosCaja )
{
	bool bRegresa = true, bContinuar =  false;
	char cSql[1024] = {0}, cFecha[10] = {0}, cHora[10] = {0}, cError[100] = {0}, cNombreTabla[17] = {0}, cCajaProtheus[5] = {0}, cNombreTablaPAJ[10] = {0};
	char cAgencia[6] = {0}, cCuenta[11] = {0}, cParametros[18] = {0}, cFlagCancelacion [ 2 ]= { 0 }, cEmpresa[5] = {0};
	int iContador = 0, iTipoRetiro = 1;
    char cParametros1[202] = {0},cTexto[64] = {0}, cTexto2[64] = {0}, cLog[500] = {0};
    const char *cTexto3 = NULL;
    int iFlagBonificacion = 0, iDia = 1, iMes = 1, iYear = 1900;
    bool bRespuesta = false;

    mysnprintf( cSql, 200," SELECT TRIM( valor ) AS valor FROM tdConfiguracion WHERE UPPER( TRIM( elemento ) ) = 'NUMERO_DE_EMPRESA' ", ' ');
    
    CRegistro consultarNE(odbcTiendaNumero, bCommit);
    
    consultarNE.agregarCampoChar("valor", 5);

    if( consultarNE.Exec(cSql) )
    {
        consultarNE.activarCols();
	    if ( consultarNE.Leer() )
        {
            mysnprintf( cEmpresa, 5, "%s", consultarNE.valorChar("valor") );
            bRespuesta= true;

        }else
        {
             bRespuesta= false;
        }
    }
    else
    {
        logx("NO SE PUDO CONSULTAR EL NUMERO DE EMPRESA", _LOGINFO_);
        logx(cSql, _LOGINFO_);
         bRespuesta= false;
    }

	mysnprintf( cNombreTablaPAJ, 15, "tmppaj%.2s0", cEmpresa );

	/*if( crearTablaTmpPAJ( odbcTiendaNumero, sSolicitud, cEmpresa) )
    {
        logx("PASO crearTablaTmpPAJ", _LOGINFO_);
        bRespuesta = true;
        bContinuar = true;
    }*/

	if ( bRespuesta ==  true )
	{
        logx("PASA A CONSULTAR CAJA PROTHEUS", _LOGINFO_);

		if ( consultarCajaProtheus( odbcTiendaNumero, sSolicitud, cCajaProtheus, cAgencia, cCuenta, 1, bCommit) )
		{
            mysnprintf( cParametros1,100, "%08ld%08ld%06ld%02d",sSolicitud->lImporte, sSolicitud->lCliente, sRespuesta-> lRecibo, sSolicitud->iCaja );
			mysnprintf(cParametros,18, "%.3s%.5s%.10s", cCajaProtheus, cAgencia, cCuenta );
            mystrncat(cParametros1, cParametros, 121);
			mysnprintf( cSql, 1023,"SELECT filial, moneda, valor, naturez, banco, agencia, cuenta, documento, reciboopago, beneficiario, historial, tipodoc, txmoneda, prorrateo, filialorig, numerocheque, debito, credito, centrocostodebito, centrocostocredito, tipoope FROM gnGenerarMovimietnosBancariosLocal03( %d::smallint,'%.100s')", iProceso,cParametros1);
            logx(cSql, _LOGINFO_);

			CRegistro datosMovtosReembolso( odbcTiendaNumero );
            datosMovtosReembolso.agregarCampoChar("filial", 2);
            datosMovtosReembolso.agregarCampoEntero("moneda", 2);
            datosMovtosReembolso.agregarCampoEntero("valor", DT_ENTERO);
            datosMovtosReembolso.agregarCampoChar("naturez", 10);
            datosMovtosReembolso.agregarCampoChar("banco", 3);
            datosMovtosReembolso.agregarCampoChar("agencia", 5);
            datosMovtosReembolso.agregarCampoChar("cuenta", 11);
            datosMovtosReembolso.agregarCampoChar("documento", 50);
            datosMovtosReembolso.agregarCampoChar("reciboopago", 1);
            datosMovtosReembolso.agregarCampoChar("beneficiario", 30);
            datosMovtosReembolso.agregarCampoChar("historial", 40);
            datosMovtosReembolso.agregarCampoChar("tipodoc", 2);
            datosMovtosReembolso.agregarCampoEntero("txmoneda", DT_ENTERO);
            datosMovtosReembolso.agregarCampoChar("prorrateo", 1);
            datosMovtosReembolso.agregarCampoChar("filialorig", 2);
            datosMovtosReembolso.agregarCampoChar("numerocheque", 15);
            datosMovtosReembolso.agregarCampoChar("debito", 20);
            datosMovtosReembolso.agregarCampoChar("credito", 20);
            datosMovtosReembolso.agregarCampoChar("centrocostodebito", 9);
            datosMovtosReembolso.agregarCampoChar("centrocostocredito", 9);
            datosMovtosReembolso.agregarCampoChar("tipoope", 1);

           /* datosMovtosReembolso.agregarCampoFecha("PAJ_DATA");
            datosMovtosReembolso.agregarCampoChar("PAJ_DTGRV", DT_CHAR);
            datosMovtosReembolso.agregarCampoChar("PAJ_HRGRV", DT_CHAR);
            datosMovtosReembolso.agregarCampoChar("PAJ_GRPTRA", DT_CHAR);*/

			if (datosMovtosReembolso.Exec( cSql ))
			{
                // CRegistro insertarPajLocal( odbcTiendaNumero, bCommit );
				// //if ( iProceso == PAJ_PAGO_REEMBOLSOS )
				// //{
				datosMovtosReembolso.activarCols();
				if ( datosMovtosReembolso.Leer() )
				{
                    //CString sTexto;   
                    CRegistro inTmpPaj( odbcTiendaNumero, false);
                    SqlTimeStamp tFecha;
                    logx("EJECUTO BIEN LEERdatosMovtosReembolso ", _LOGINFO_);
                    
                    inTmpPaj.agregarCampoChar("PAJ_FILIAL", 2);
                    inTmpPaj.agregarCampoChar("PAJ_DATA",8);
                    inTmpPaj.agregarCampoEntero("PAJ_MOEDA", 2);
                    inTmpPaj.agregarCampoChar("PAJ_NATURE", 10);
                    inTmpPaj.agregarCampoEntero("PAJ_VALOR", DT_ENTERO);
                    
                    inTmpPaj.agregarCampoChar("PAJ_BANCO", 3);
                    inTmpPaj.agregarCampoChar("PAJ_AGENCI", 3);
                    inTmpPaj.agregarCampoChar("PAJ_CONTA", 11);
                    inTmpPaj.agregarCampoChar("PAJ_DOCUME", 50);
                    inTmpPaj.agregarCampoChar("PAJ_RECPAG", 1);
                    inTmpPaj.agregarCampoChar("PAJ_BENEF", 30);
                    inTmpPaj.agregarCampoChar("PAJ_HISTOR", 40);
                    inTmpPaj.agregarCampoChar("PAJ_TIPODO", 2);
                    inTmpPaj.agregarCampoEntero("PAJ_TXMOED", DT_ENTERO);
                    inTmpPaj.agregarCampoChar("PAJ_RATEIO", 1);
                    inTmpPaj.agregarCampoChar("PAJ_FILORI", 2);
                    inTmpPaj.agregarCampoChar("PAJ_NUMCHE", 15);
                    inTmpPaj.agregarCampoChar("PAJ_DEBITO", 20);
                    inTmpPaj.agregarCampoChar("PAJ_CCD", 9);
                    inTmpPaj.agregarCampoChar("PAJ_CCC", 9);
                    inTmpPaj.agregarCampoChar("PAJ_CREDIT", 20);
                    inTmpPaj.agregarCampoChar("PAJ_DTGRV", 8);
                    inTmpPaj.agregarCampoChar("PAJ_HRGRV", 8);
                    inTmpPaj.agregarCampoChar("PAJ_TIPOPE", 1);
                    inTmpPaj.agregarCampoChar("PAJ_GRPTRA", 15);
                    mysnprintf(cNombreTabla, 100, "PAJ%.2s0", cEmpresa);
                    logx(cNombreTabla, _LOGINFO_);
                    inTmpPaj.activarCols();
                    inTmpPaj.prepararInsert(cNombreTabla);
                    logx("Despues de activar COLS PAJ", _LOGINFO_);
                    
                    inTmpPaj.valorChar( "PAJ_FILIAL", datosMovtosReembolso.valorChar("filial"));

                    //mysnprintf(cTexto, 100, "%.17s", datosMovtosReembolso.valorChar("filial"));
                    //mysnprintf(cTexto, 100, "%.12s", sSolicitud->lFecha);
                   // iYear = valorCampo( cTexto, 4 );
                    //iMes = valorCampo( &cTexto[5], 2 );
                    //iDia = valorCampo( &cTexto[8], 2 );
                    //tFecha.ponerFecha( iDia, iMes, iYear );
                    mysnprintf(cTexto, 100, "%.8s", sSolicitud->fechaSinFormato);
                    inTmpPaj.valorChar("PAJ_DATA",cTexto);
                    logx("Despues de FECHA", _LOGINFO_);

                    inTmpPaj.valorShort("PAJ_MOEDA", (short)datosMovtosReembolso.valorLong("moneda"));
                    inTmpPaj.valorShort("PAJ_VALOR", (short)datosMovtosReembolso.valorLong("valor"));
                    inTmpPaj.valorChar("PAJ_NATURE", datosMovtosReembolso.valorChar("naturez"));
                    inTmpPaj.valorChar("PAJ_BANCO", datosMovtosReembolso.valorChar("banco"));
                    inTmpPaj.valorChar("PAJ_AGENCI", datosMovtosReembolso.valorChar("agencia"));
                    inTmpPaj.valorChar("PAJ_CONTA", datosMovtosReembolso.valorChar("cuenta"));
                    inTmpPaj.valorChar("PAJ_DOCUME", datosMovtosReembolso.valorChar("documento"));
                    inTmpPaj.valorChar("PAJ_RECPAG", datosMovtosReembolso.valorChar("reciboopago"));
                    inTmpPaj.valorChar("PAJ_BENEF", datosMovtosReembolso.valorChar("beneficiario"));
                    cTexto3 = datosMovtosReembolso.valorChar("historial");
                    std::string str(cTexto3);
                    str.substr(2, 8);
                    char* c = const_cast<char*>(str.c_str());
                    mysnprintf(cTexto, 100, "%s", c);
                    inTmpPaj.valorChar("PAJ_HISTOR", cTexto);
                    logx("Despues de PAJ_HISTOR", _LOGINFO_);

                    inTmpPaj.valorChar("PAJ_TIPODO", datosMovtosReembolso.valorChar("tipodoc"));
                    inTmpPaj.valorDouble("PAJ_TXMOED", (double)datosMovtosReembolso.valorLong("txmoneda"));
                    inTmpPaj.valorChar("PAJ_RATEIO", datosMovtosReembolso.valorChar("prorrateo"));
                    inTmpPaj.valorChar("PAJ_FILORI", datosMovtosReembolso.valorChar("filialorig"));
                    inTmpPaj.valorChar("PAJ_NUMCHE", datosMovtosReembolso.valorChar("numerocheque"));
                    inTmpPaj.valorChar("PAJ_DEBITO", datosMovtosReembolso.valorChar("debito"));
                    inTmpPaj.valorChar("PAJ_CREDIT", datosMovtosReembolso.valorChar("credito"));
                    inTmpPaj.valorChar("PAJ_CCD", datosMovtosReembolso.valorChar("centrocostodebito"));
                    inTmpPaj.valorChar("PAJ_CCC", datosMovtosReembolso.valorChar("centrocostocredito"));

                    inTmpPaj.valorChar("PAJ_TIPOPE", datosMovtosReembolso.valorChar("tipoope"));
                    mysnprintf(cTexto, 100, "%.8s", sSolicitud->fechaSinFormato);
                    inTmpPaj.valorChar("PAJ_DTGRV", cTexto);
                    mysnprintf(cTexto, 100, "%.8s", sSolicitud->lHora);
                    inTmpPaj.valorChar("PAJ_HRGRV", cTexto);
                    mysnprintf(cTexto, 100, "%.15s", datosCaja ->cReferenciaMsj);
                    inTmpPaj.valorChar("PAJ_GRPTRA",  cTexto);
                    logx("Despues de PAJ_GRPTRA", _LOGINFO_);


                    if (inTmpPaj.Insert())
                    {
                        if (inTmpPaj.Commit())
                        {
                            logx("Despues de COMMIT", _LOGINFO_);
                            bRespuesta = true;
                        }
                        else
                        {
                            mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
                            mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
                            sRespuesta->status = _ERROR_EN_MENSAJE;
                            bRespuesta = false;
                            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
                        }
                    }
                    else
                    {
                        mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY select datosMovtosReembolso [%.200s]", datosMovtosReembolso.error() );
                        logx(sRespuesta->cDevMensaje,_LOGINFO_ );
                       // mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
                        mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
                        sRespuesta->status = _ERROR_EN_MENSAJE;
                        bRespuesta = false;
                        sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
                    }

					//if ( !grabarPAJLocal2( codbc cFecha, cHora, iContador, datosCaja -> cTipoProceso, cCajaProtheus, cAgencia, cCuenta, iProceso )  )

                    /*if ( !grabarPAJLocal2(odbcTiendaNumero, sSolicitud, sRespuesta)  )
					{
						bRegresa = false;
						logx("ERROR AL INSERTAR PAGO DE REEMBOLSO LOCAL", _LOGINFO_);
						break;
					}*/
				}
                else {
                    bRespuesta = false;
                    logx("error  LEERdatosMovtosReembolso ", _LOGINFO_);
                    sRespuesta->status = _ERROR_EN_MENSAJE;
                    sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
                    mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY select datosMovtosReembolso [%.200s]", datosMovtosReembolso.error() );
                    logx(sRespuesta->cDevMensaje,_LOGINFO_ );
                }
			}
			else
			{
				bRespuesta = false;
				//logx("ERROR AL GENERAR MOVIMIENTO DE REEMBOLSO LOCAL",_LOGINFO_);
                logx(cSql, _LOGINFO_);
                logx("ERROR AL HACER EJECUTAR LA FUNCION gnGenerarMovimietnosBancariosLocal03",_LOGINFO_);
			}
		}
		else
		{
            logx("ERROR AL HACER EJECUTAR LA FUNCION de consultarcaja",_LOGINFO_);
			bRespuesta = false;
		}
	}
    else
	{
        logx("ERROR AL HACER EJECUTAR LA FUNCION de consultarcaja 1",_LOGINFO_);
    }
	return bRespuesta;
}
bool Cwsprestamos00028::crearTablaTmpPAJ(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud, char *cEmpresa)
{
	char sSqlTxt[265] = {0},cLog[250]={0};
	bool bRegresa=false;
	CRegistro ccrearTablaTmpPaj010( odbcTiendaNumero,false );
    mysnprintf(sSqlTxt, 256,"CREATE TEMPORARY TABLE IF NOT EXISTS tmppaj%.2s0( LIKE paj010 INCLUDING DEFAULTS ) WITHOUT OIDS;",cEmpresa,cEmpresa);
	
    if( !ccrearTablaTmpPaj010.Exec( sSqlTxt ) )
	{
        logx(sSqlTxt, _LOGINFO_);
        logx("ERROR AL CREAR TABLA TEMPORAL PAJ", _LOGINFO_);	
    }
	else
	{
        logx("SI JALO AL CREAR TABLA TEMPORAL PAJ", _LOGINFO_);
		bRegresa=true;
	}
	return bRegresa;
}

bool Cwsprestamos00028::consultarCajaProtheus( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, char *cCajaProtheus, char *cAgencia, char *cCuenta, int iTipoRetiro, bool bCommit )
{
	bool bRespuesta = false;
	char cSql[300] = {0};

    logx("asdiohfsikuflhailufjahdsliokfahj", _LOGINFO_);

	if (iTipoRetiro == 1)
	{
		mysnprintf( cSql, 300, "SELECT cajaprotheus,agencia,cuenta FROM tdEstacion WHERE area = 'C' AND caja = %d", sSolicitud->iCaja );
        logx(cSql, _LOGINFO_);
	}
	else if (iTipoRetiro == 2)
	{
		mysnprintf( cSql, 300, "SELECT cajaprotheus,agenciaus,cuentaus FROM tdEstacion WHERE area = 'C' AND caja = %d", sSolicitud->iCaja );
        logx(cSql, _LOGINFO_);
	}

	CRegistro consultarCaja( odbcTiendaNumero, bCommit );

    consultarCaja.agregarCampoChar("cajaprotheus", 5);
    consultarCaja.agregarCampoChar("agenciaus", 5);
    consultarCaja.agregarCampoChar("cuentaus", 11);
    
	if ( !consultarCaja.Exec( cSql ) )
	{
        logx("ERROR AL CONSULTAR CAJA PROTHEUS",_LOGINFO_ );
        logx(cSql, _LOGINFO_ );
	}
	else
	{
        logx("si ejecuto",_LOGINFO_ );
		consultarCaja.activarCols();

        if(consultarCaja.Leer())
        {
            logx("SI CONSULTO LA LA TDESTACION",_LOGINFO_ );
		    bRespuesta = true;
            if(iTipoRetiro == 2)
            {
		        mysnprintf( cCajaProtheus,5, "%s", consultarCaja.valorChar("cajaprotheus") );
		        mysnprintf( cAgencia,5, "%s", consultarCaja.valorChar("agenciaus") );
		        mysnprintf( cCuenta,11, "%.10s", consultarCaja.valorChar("cuentaus") );
                logx("jalo la primera validacion",_LOGINFO_ );
            }
            else if(iTipoRetiro == 1)
            {
		        mysnprintf( cCajaProtheus,5, "%s", consultarCaja.valorChar("cajaprotheus") );
		        mysnprintf( cAgencia,5, "%s", consultarCaja.valorChar("agencia") );
		        mysnprintf( cCuenta,11, "%.10s", consultarCaja.valorChar("cuenta") );
                logx("jalo la segunda validacion",_LOGINFO_ );
            }

        }
	}

	return bRespuesta;
}

bool Cwsprestamos00028::ejecutarFuncionesPostgres( C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta,long lRecibo)
{
	char cSqlTxt[500]={0},cSql[256]={0}, cIpTmp[22]={0},cLog[80]={};
	int iTipoImpresora=0,iCasa=0,iFlagSiguele=1,i64FolioBancoppel=0,i64CuentaTarjeta=0;
	bool bConsultaOK = true;
	bool bContinuar = false;
	bool bReversar = false;
	int i64FolioTransBancoppel = 0;    
	short int iFlagFalloConexion = 0;
	long lEmpleado2 = 0L;
	char cIdentificacion[20]={0}, cNombreSucursal[25]= {0}, cDomicilio[25]= {0}, cNombreGerente[25]= {0},
		cNombreZona[40]= {0},cPoblacion[30]= {0},cMunicipio[30]= {0},cNombreCalle[25]= {0},cMensajeOut[100]= {0}, cCodigoPostal[15]= {0},cTelefono[15] = {0};
	bool bActivar = false;

	i64FolioBancoppel = 0;
	i64CuentaTarjeta = 0;
    InfoFE infoFE;
    DatosCajaSudamerica datosCaja;
    mymemset( &infoFE, 0, sizeof( infoFE ) );
    mymemset( &datosCaja , 0, sizeof( datosCaja ) );	
	


    if( transaccionDB( odbcTiendaNumero, "BEGIN" ,sRespuesta) )
    { 		
        if(obtenerCuponTicket(odbcTiendaNumero, sSolicitud, sRespuesta,  &datosCaja ))
        {
            if( actualizarPrestamos(odbcTiendaNumero,odbcCartera,sSolicitud,sRespuesta,&datosCaja ) )
            {
                if(grabarInformacionPrestamosCertificacion(odbcTiendaNumero, odbcCartera, sSolicitud, sRespuesta, 1 ) )
                {
                    if (sSolicitud->iFlagHuella == 3 || sSolicitud->iFlagHuella == 2) 
                    {
                        if (sSolicitud->iFlagHuella == 3) 
                        {
                            logx("Entro con iFlagHuella = 3", _LOGINFO_);
                            bContinuar = grabarAutorizacionGerentes(odbcTiendaNumero, sSolicitud, sRespuesta, '1');    //gnwaugte.cpp
                        } 
                        else if (sSolicitud->iFlagHuella == 2) 
                        {
                            logx("Entro con iFlagHuella = 2", _LOGINFO_);
                            bContinuar = grabarAutorizacionGerentes(odbcTiendaNumero, sSolicitud, sRespuesta, 'G');    //gnwaugte.cpp
                        }
                        actualizarTdAutorizacionHuellas(odbcTiendaNumero, sSolicitud,sRespuesta,&datosCaja );
                    }	       
                    if( bContinuar && transaccionDB( odbcCartera, "BEGIN" ,sRespuesta) )
                    { 
                        if ( interfaceInsertarMovtoPAJLocal( odbcTiendaNumero, sSolicitud, sRespuesta,&datosCaja) )	
                        {
                            if(  grabarCarteraServicio(odbcTiendaNumero,odbcCartera,sSolicitud,sRespuesta,lRecibo))
                            {
                                if( transaccionDB( odbcTiendaNumero, "COMMIT" ,sRespuesta) )
                                {
                                    if( generarFacturaElectronicaNCC(odbcTiendaNumero,&infoFE, sSolicitud, sRespuesta, &datosCaja ) == 1 )
                                    {
                                        bContinuar =actualizarFECacarmov(odbcTiendaNumero,&infoFE, sSolicitud, sRespuesta, &datosCaja, 8);
                                        if(bContinuar && generarFacturaElectronica(odbcTiendaNumero,&infoFE, sSolicitud, sRespuesta, &datosCaja ) == 1 )
                                        {
                                            bContinuar = actualizarFECacarmov(odbcTiendaNumero,&infoFE, sSolicitud, sRespuesta, &datosCaja,6);
                                            if(bContinuar && actualizarCrprestamosFE(odbcCartera, sSolicitud, sRespuesta) ) 
                                            {
                                                sRespuesta->status = _MENSAJE_CORRECTO_;
                                                bConsultaOK = true;
                                                logx("SI JALO EL actualizarCrprestamosFE ", _LOGINFO_);
                                            } 
                                            else
                                            {
                                                logx("NO JALO EL actualizarCrprestamosFE ", _LOGINFO_); 
                                                transaccionDB(odbcTiendaNumero, "ROLLBACK", sRespuesta);
                                                transaccionDB(odbcCartera, "ROLLBACK", sRespuesta);
                                                sRespuesta->status = _ERROR_DE_SERVIDOR;
                                                bConsultaOK = false;
                                            }
                                        }
                                        else
                                        {
                                            logx("NO JALO EL generarFacturaElectronica ", _LOGINFO_); 
                                            transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                                            transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                                            sRespuesta->status = _ERROR_DE_SERVIDOR;
                                            bConsultaOK = false;
                                        }
                                    }
                                    else
                                    {
                                        transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                                        transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                                    }
                                             //  logx('ya funca generarFacturaElectronica');
                                }
                                else 
                                {
                                    transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                                    transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                            //     logx('fallo generarFacturaElectronica');
                                }
                            } 
                            else 
                            {
                                transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                                transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                                 //     logx('fallo generarFacturaElectronica');
                            }
                        }
                        else
                        {
                            transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                            transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                            sRespuesta->status = _ERROR_DE_SERVIDOR;
                            bConsultaOK = false;
                        }

                    }	 
                    else
                    {
                        transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                        transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                        
                    }
                }    
                else
                {
                    transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                    transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                    bConsultaOK = false;
                }      
                                  				
            }
            else
            {
                transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
                transaccionDB( odbcCartera, "ROLLBACK" ,sRespuesta);
                sRespuesta->status = _ERROR_DE_SERVIDOR;
                bConsultaOK = false;
            }
        } 
        else
        {
            transaccionDB( odbcTiendaNumero, "ROLLBACK" ,sRespuesta);
            bConsultaOK = false;
        }     				
    }
    else
    {
        bConsultaOK = false;
    }      		
	return bConsultaOK;
}

bool Cwsprestamos00028::grabarCarteraServicio(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta,long lRecibo)
{
	bool bRegresa=false;
	char cDll[64] = {0};
    char cArgvIN1[1024] = {0}, cArgvIN2[1024] = {0},cTexto[128] = {0};
    char cArgvOUT1[1024] = {0}, cArgvOUT2[1024] = {0},cIpServidorCartera[47]={0},cCuponTicket[47]={0};
	char cSql[2500] = {0};
	long iLongitud=0;
    long lImporteSeguroClub =0,iCuentaReest=0,iPlazoReconocimiento=0,iFlagTramitar=0,iTieneNegPropio=0;
    char tempString[2];
	char cTablaConsulta[18]={0},sTexto[30] = {0};;
	char cMensajePrestamo[500] = {0};//830
    char sSqlTxt[500]={0};
    int  iDia = 1, iMes = 1, iYear = 1900;
    GrabarPrestamoCartera03 grabarEnCartera;
    SqlTimeStamp tFecha;

    CRegistro grabarPrestamo( odbcCartera, false );

	CRegistro consultarCaCarmov( odbcTiendaNumero, false );

    consultarCaCarmov.agregarCampoChar("clave", 1);
    consultarCaCarmov.agregarCampoChar("tipomovimiento", 1);
    consultarCaCarmov.agregarCampoEntero("tienda", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("ciudad", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("cliente", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("clienteetp", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("caja", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("recibo", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("factura", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("importe", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("saldoinicial", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("saldofinal", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("saldocuenta", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("vencidoinicial", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("minimoinicial", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("base", DT_ENTERO);
    consultarCaCarmov.agregarCampoFecha("fechasaldacon");
    consultarCaCarmov.agregarCampoEntero("importesaldacon", DT_ENTERO);
    consultarCaCarmov.agregarCampoChar("tipoconvenio", 1);
    consultarCaCarmov.agregarCampoChar("subtipoconvenio", 1);
    consultarCaCarmov.agregarCampoEntero("plazoconvenio", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoChar("ejercicio", 1);
    consultarCaCarmov.agregarCampoChar("clavetdaocob", 1);
    consultarCaCarmov.agregarCampoChar("grabacartera", 1);
    consultarCaCarmov.agregarCampoChar("anexo", 1);
    consultarCaCarmov.agregarCampoChar("clavelocal", 1);
    consultarCaCarmov.agregarCampoChar("clientelocalizar", 1);
    consultarCaCarmov.agregarCampoChar("tiposeguro", 1);
    consultarCaCarmov.agregarCampoChar("flagseguroconyugal", 1);
    consultarCaCarmov.agregarCampoChar("movtoseguro", 1);
    consultarCaCarmov.agregarCampoChar("flagmontoseguro", 1);
    consultarCaCarmov.agregarCampoChar("statusseguro", 1);
    consultarCaCarmov.agregarCampoEntero("causabaja", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("cantidadseguros", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("cantidadsegurosanterior", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("cantidadmeses", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("bonificacion", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("mesesvencidos", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoFecha("fechanacimiento");
    consultarCaCarmov.agregarCampoEntero("edad", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoChar("sexo", 1);
    consultarCaCarmov.agregarCampoChar("areaajuste", 1);
    consultarCaCarmov.agregarCampoFecha("fechaabonoajuste");
    consultarCaCarmov.agregarCampoChar("claveajuste", 2);
    consultarCaCarmov.agregarCampoChar("ajuste", 2);
    consultarCaCarmov.agregarCampoEntero("tiendaorigen", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("numerocontrol", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("comision", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("clienteremitente", DT_ENTERO);
    consultarCaCarmov.agregarCampoChar("tipogastoviaje", 1);
    consultarCaCarmov.agregarCampoEntero("centro", DT_ENTERO);
    consultarCaCarmov.agregarCampoChar("flagincluyerecibo", 1);
    consultarCaCarmov.agregarCampoEntero("ruta", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("folio", DT_ENTERO);
    consultarCaCarmov.agregarCampoChar("cuenta", 20);
    consultarCaCarmov.agregarCampoEntero("iva", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("telefono", DT_ENTERO_LARGO);  //Cambio de bigint a entero largo
    consultarCaCarmov.agregarCampoChar("compania", 1);
    consultarCaCarmov.agregarCampoChar("contrato", 22);
    consultarCaCarmov.agregarCampoChar("credito", 15);
    consultarCaCarmov.agregarCampoFecha("fechavencimiento");
    consultarCaCarmov.agregarCampoFecha("fechavencimientoanterior");
    consultarCaCarmov.agregarCampoFecha("fecha");
    consultarCaCarmov.agregarCampoEntero("efectuo", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("cajaoriginal", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoEntero("foliotienda", DT_ENTERO_LARGO);
    consultarCaCarmov.agregarCampoChar("rpu", 12);
    consultarCaCarmov.agregarCampoChar("flagmovtosupervisor", 1);
    consultarCaCarmov.agregarCampoEntero("interes", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("importeventa", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("folioanterior", DT_ENTERO);
    consultarCaCarmov.agregarCampoEntero("digito", DT_ENTERO_CORTO);
    consultarCaCarmov.agregarCampoChar("sac", 9);
    consultarCaCarmov.agregarCampoChar("ipcarteracliente", 47);
    consultarCaCarmov.agregarCampoFecha("fechadocumento");
    consultarCaCarmov.agregarCampoChar("docfiscal", 12);
    consultarCaCarmov.agregarCampoChar("serieintbnf", 3);

    mysnprintf( cSql,2500, "SELECT clave, tipomovimiento, tienda, ciudad, cliente, clienteetp, caja, recibo, factura, importe, saldoinicial, saldofinal, saldocuenta,"
        "vencidoinicial, minimoinicial, base, fechasaldacon, importesaldacon, tipoconvenio, subtipoconvenio, plazoconvenio, ejercicio, clavetdaocob,"
        "grabacartera, anexo, clavelocal, clientelocalizar, tiposeguro, flagseguroconyugal, movtoseguro, flagmontoseguro, statusseguro, causabaja,"
        "cantidadseguros, cantidadsegurosanterior, cantidadmeses, bonificacion, mesesvencidos, fechanacimiento, edad, sexo, areaajuste,"
        "fechaabonoajuste, claveajuste, ajuste, tiendaorigen, numerocontrol, comision, clienteremitente, tipogastoviaje, centro, flagincluyerecibo,"
        "ruta, folio, cuenta, iva, telefono, compania, contrato, credito, fechavencimiento, fechavencimientoanterior, fecha, efectuo, cajaoriginal,"
        "foliotienda, rpu, flagmovtosupervisor, interes, importeventa, folioanterior, digito, sac, ipcarteracliente, docfiscal, serieintbnf "
        "FROM cacarmov WHERE recibo = %ld AND caja = %d ORDER BY tipomovimiento DESC", sRespuesta-> lRecibo, sSolicitud ->iCaja);
    logx(cSql,_LOGINFO_);
    mysnprintf(sTexto, sizeof(sTexto)-1,"%d", sSolicitud->sCCuenta.iNumcliente);
    iLongitud = mystrnlen(sTexto);
    mysnprintf(sTexto, sizeof(sTexto)-1,"%c%c",sTexto[iLongitud-3],sTexto[iLongitud-2]);

	if(!consultarCaCarmov.Exec(cSql))
	{
        mysprintf(sRespuesta->cDevMensaje,"ERROR AL EJECUTAR QUERY select cacarmov [%.200s]", consultarCaCarmov.error() );
        logx(sRespuesta->cDevMensaje,_LOGINFO_ );
	}
	else
	{
		mymemset( &grabarEnCartera, 0, sizeof( grabarEnCartera) );

		consultarCaCarmov.activarCols();
		while( consultarCaCarmov.leer() )
		{
            if( consultarCaCarmov.valorChar("cve")[0] == 'G' ) 
            {
                grabarEnCartera.lImporteSeguroClub =  consultarCaCarmov.valorLong("importe") / 100;
                grabarEnCartera.lFolioSeguro =  consultarCaCarmov.valorLong("folio");
                grabarEnCartera.iCantSeguros =  consultarCaCarmov.valorLong("cantidadseguros");
                mysnprintf( cTexto, 16, "%.17s", consultarCaCarmov.valorFecha("fechanacimiento") );
                iYear = valorCampo( cTexto, 4 );
                iMes = valorCampo( &cTexto[5], 2 );
                iDia = valorCampo( &cTexto[8], 2 );
                tFecha.ponerFecha( iDia, iMes, iYear );
                grabarEnCartera.tFechaNacDia =iDia;
                grabarEnCartera.tFechaNacMes = iMes;
                grabarEnCartera.tFechaNacAnio = iYear;
            }
            else
            {
                if( lImporteSeguroClub == 0)
                {
                    grabarEnCartera.tFechaNacDia = 1;
                    grabarEnCartera.tFechaNacMes = 1;
                    grabarEnCartera.tFechaNacAnio = 1900;
                }

                grabarEnCartera.lCliente = sSolicitud -> lCliente;
                grabarEnCartera.lImportePrestamo = consultarCaCarmov.valorLong("importe") / 100;

                grabarEnCartera.lInteresFinanciamiento = sSolicitud -> lInteresFinanciamiento;

                grabarEnCartera.lFactura =  consultarCaCarmov.valorLong("factura");
                grabarEnCartera.lEfectuo =  consultarCaCarmov.valorLong("efectuo");

                if( iFlagTramitar == 0)
                {
                    grabarEnCartera.lRecibo =  consultarCaCarmov.valorLong("recibo");
                }
                else
                {
                    grabarEnCartera.lRecibo = lRecibo;
                }
                grabarEnCartera.lInteresAdicional = sSolicitud ->lInteresAdicional;
                grabarEnCartera.lSaldoPrestamo = consultarCaCarmov.valorLong("saldocuenta");//  # PENDIENTE
                
                grabarEnCartera.cClave[0] =consultarCaCarmov.valorChar("cve")[0];
                grabarEnCartera.cClave[1] = 0;
                grabarEnCartera.cTipoMovto[0] = consultarCaCarmov.valorChar("tipomovimiento")[0];
                grabarEnCartera.cTipoMovto[1] = 0;


                if (memcmp(consultarCaCarmov.valorChar("ipcarteracliente"), cIpServidorCartera, iLongitud) == 0)
                {
                   
                    grabarEnCartera.cTipoGrabado[0] = 'T';
                }
                else
                {
                    grabarEnCartera.cTipoGrabado[0] = 'F';
                }
               
                grabarEnCartera.cTipoGrabado[1] = 0;
                grabarEnCartera.cMovtoSeguro[0] = 'C';
                grabarEnCartera.cMovtoSeguro[1] = 0;
                grabarEnCartera.cFlagSeguroConyugal[0] = ' ';
                grabarEnCartera.cFlagSeguroConyugal[0] = 0;

                mysnprintf(grabarEnCartera.cIpServidor, 17, "%s", consultarCaCarmov.valorChar("ipcarteracliente")); 
                grabarEnCartera.iVencidoInicial = consultarCaCarmov.valorShort("vencidoinicial");
                grabarEnCartera.iImporteSaldaCon = consultarCaCarmov.valorShort("importesaldacon");
                grabarEnCartera.iAbonoBase = consultarCaCarmov.valorLong("base");
                grabarEnCartera.iCiudad = consultarCaCarmov.valorShort("ciudad");
                grabarEnCartera.iTienda = consultarCaCarmov.valorShort("tienda");
                grabarEnCartera.iCaja = consultarCaCarmov.valorShort("caja");
                 mysnprintf( cTexto, 16, "%.17s", consultarCaCarmov.valorFecha("fechasaldacon") );
                iYear = valorCampo( cTexto, 4 );
                iMes = valorCampo( &cTexto[5], 2 );
                iDia = valorCampo( &cTexto[8], 2 );
                grabarEnCartera.tFechaSaldaConDia = iDia;
                grabarEnCartera.tFechaSaldaConMes = iMes;
                grabarEnCartera.tFechaSaldaConAnio = iYear;
                mysnprintf( cTexto, 16, "%.17s", consultarCaCarmov.valorFecha("fecha") );
                iYear = valorCampo( cTexto, 4 );
                iMes = valorCampo( &cTexto[5], 2 );
                iDia = valorCampo( &cTexto[8], 2 );
                grabarEnCartera.iDiaActual =iDia;
                grabarEnCartera.iMesActual = iMes;
                grabarEnCartera.iAnioActual =iYear;
                grabarEnCartera.iFlagNuevo = sSolicitud ->iFlagNuevo;
                 mysnprintf( cTexto, 16, "%.17s", consultarCaCarmov.valorFecha("fechavencimiento"));
                iYear = valorCampo( cTexto, 4 );
                iMes = valorCampo( &cTexto[5], 2 );
                iDia = valorCampo( &cTexto[8], 2 );
                grabarEnCartera.tFechaVencimientoDia = iDia;
                grabarEnCartera.tFechaVencimientoMes = iMes;
                grabarEnCartera.tFechaVencimientoAnio = iYear;
                grabarEnCartera.iFlagTramite = consultarCaCarmov.valorShort("lSaldoPrestAnt");
                grabarEnCartera.lSaldaCon = sSolicitud ->lSaldoAnt;
                grabarEnCartera.lSaldoPrestAnt = sSolicitud ->lSaldoActual;
                grabarEnCartera.lFacturaPrestAnt = sSolicitud ->lFacturaAnt;
                grabarEnCartera.lComision = 0;
                iPlazoReconocimiento = consultarCaCarmov.valorLong("plazoconvenio");
                if (iTieneNegPropio == 1)
                {
                    grabarEnCartera.tFecActNegocioDia = consultarCaCarmov.valorShort("fechavencimiento");
                    grabarEnCartera.tFecActNegocioMes = consultarCaCarmov.valorShort("fechavencimiento");
                    grabarEnCartera.tFecActNegocioAnio = consultarCaCarmov.valorShort("fechavencimiento");
                }
                else
                {
                    grabarEnCartera.tFecActNegocioDia = 1;
                    grabarEnCartera.tFecActNegocioMes = 1;
                    grabarEnCartera.tFecActNegocioAnio = 1900;
                }
                bRegresa = true;
            }	
        }
	}


    mysnprintf(grabarEnCartera.cIpServidor, 17, "%s", consultarCaCarmov.valorChar("ipcarteracliente"));
    mysnprintf(grabarEnCartera.cCuponFiscal, 12, "%d", cCuponTicket);
    grabarEnCartera.iCuentaReest = iCuentaReest;

	if( bRegresa )
	{
            mysnprintf(cSql, 1000, "SELECT crgrabarMovtoPrestamo03(cast(('%ld','%ld','%ld','%ld','%ld','%ld','%ld','%ld','%ld','%ld','%s','%s','%s','%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d-%d-%d','%d','%d','%d','%d','%d','%ld','%ld','%ld','%d-%d-%d','%d-%d-%d','%ld','%d-%d-%d','%.12s', '%.12s', '%ld') AS crgrabamovtoprestamo03 ))",
                grabarEnCartera.lCliente, grabarEnCartera.lImportePrestamo, grabarEnCartera.lInteresFinanciamiento, grabarEnCartera.lImporteSeguroClub,
                grabarEnCartera.lFactura, grabarEnCartera.lFolioSeguro, grabarEnCartera.lEfectuo, grabarEnCartera.lRecibo,
                grabarEnCartera.lInteresAdicional, grabarEnCartera.lSaldoPrestamo, grabarEnCartera.cClave,
                grabarEnCartera.cTipoMovto, grabarEnCartera.cTipoGrabado, grabarEnCartera.cMovtoSeguro, grabarEnCartera.cFlagSeguroConyugal,
                grabarEnCartera.cIpServidor, grabarEnCartera.iVencidoInicial, grabarEnCartera.iImporteSaldaCon,
                grabarEnCartera.iAbonoBase, grabarEnCartera.iCiudad, grabarEnCartera.iTienda, grabarEnCartera.iCaja,
                grabarEnCartera.tFechaSaldaConDia, grabarEnCartera.tFechaSaldaConMes, grabarEnCartera.tFechaSaldaConAnio,
                grabarEnCartera.iCantSeguros, grabarEnCartera.iAnioActual, grabarEnCartera.iMesActual, grabarEnCartera.iDiaActual,
                grabarEnCartera.iFlagNuevo, grabarEnCartera.tFechaVencimientoDia, grabarEnCartera.tFechaVencimientoMes,
                grabarEnCartera.tFechaVencimientoAnio, grabarEnCartera.iFlagTramite, grabarEnCartera.lSaldaCon,
                grabarEnCartera.lSaldoPrestAnt, grabarEnCartera.lFacturaPrestAnt,
                grabarEnCartera.tFechaNacAnio, grabarEnCartera.tFechaNacMes, grabarEnCartera.tFechaNacDia,
                grabarEnCartera.iAnioActual + 1, 0, 0, grabarEnCartera.lComision,
                grabarEnCartera.tFecActNegocioAnio, grabarEnCartera.tFecActNegocioMes, grabarEnCartera.tFecActNegocioDia, grabarEnCartera.cCuponFiscal, grabarEnCartera.cCuponNcc,
                grabarEnCartera.iCuentaReest);
		if( grabarPrestamo.Exec( cSql ) )
		{
			grabarPrestamo.activarCols();
			if(grabarPrestamo.leer())
			{
				bRegresa = true;
			}
			else
			{
				bRegresa = false;
			}
		}
		else
		{
			bRegresa = false;			
		}
	}
	return bRegresa;
}

void Cwsprestamos00028::consumirWebserviceParametrico(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta) {
	char cURL_[128] = {0}, cTexto[128] = {0},cLog[512] = {0};
	int iJson_ = SOAP_ERR;
	iRespuesta = _ERROR_QUERY_;
     int iRegresaMsg = 0;
    long lVencido = 0L;
    bool bRegresa= true;
    bool bPrestamos = true,bContinuar =true;
    char cTexto1[10] = { 0 }, cEdadMax[10] = { 0 }, cSql[512] = { 0 };
    int iNumeroMensaje = 0, iPuntos = 0;
    int iEdadCliente = 0;
    char cWord[400] = {0}, cVencido[20] = {0};
	soap *soapParametricoPrestamo = soap_new1( SOAP_C_UTFSTRING );
	value vSolicitudJson( soapParametricoPrestamo ), vRespuestaJson( soapParametricoPrestamo );
    C_ODBC  odbcCartera;
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    if (iRespuesta != _OK_)
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::consumirWebserviceParametrico", _LOGINFO_);
    }
    
    mysnprintf( cURL_, sizeof(cURL_)-1, "10.44.160.58:50112", "" );

	vSolicitudJson["mensaje"]  = 1;
	vSolicitudJson["tienda"]   = 14;
	vSolicitudJson["cliente"]  = sSolicitud->sCCuenta.iNumcliente;
    vSolicitudJson["iptienda"] = "10.44.160.58";

	logx("Conectando al paramétrico préstamo", _LOGINFO_);
	displayJson( &vSolicitudJson );

	iJson_ = json_call(soapParametricoPrestamo, cURL_, &vSolicitudJson, &vRespuestaJson);
	displayJson( &vRespuestaJson );

	if (iJson_ != SOAP_OK){
		sRespuesta->status = _ERROR_DE_SERVIDOR;                        
        mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje)-1, "%s", "OCURRRIO UN ERROR EN EL SERVIDOR.");
        sRespuesta->iDevStatus = _ERROR_HTTP_;
        mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje)-1, "ERROR AL CONSUMIR EL WEBSERVICE PARAMETRICO PRESTAMO. [%.200s]", cLog );
        logx(sRespuesta->cDevMensaje, _LOGINFO_);
        return;
	}
	
	iRespuesta = _OK_;
    sRespuesta -> Prestamo = 0;
	if (!vRespuestaJson.has("bAprobo")){
		sRespuesta->status = _ERROR_DE_SERVIDOR;                        
        mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje)-1, "%s", "OCURRRIO UN ERROR AL CONSUMIR WEBSERVICE PARAMETRICO PRESTAMO");
        sRespuesta->iDevStatus = _ERROR_HTTP_;
        mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje)-1, "NO SE ENCUENTRA EL CAMPO bAprobo EN LA RESPUESTA. [%.200s]", cLog );
		return;
	}

	sRespuesta->iDevStatus = _MENSAJE_CORRECTO_;
	if (vRespuestaJson["bAprobo"]){
		sRespuesta->status = _MENSAJE_CORRECTO_;
        sRespuesta->sRespPrestamo.iGrupo = (int)vRespuestaJson["iGrupo"];;
        sRespuesta->sRespPrestamo.iPuntajeParametricoFinal =(long long int)vRespuestaJson["iPuntajeParametricoFinal"];
        sRespuesta->sRespPrestamo.ffactor = (double)vRespuestaJson["ffactor"];
        sRespuesta->sRespPrestamo.ipuntajesaldoprestamoanterior = (int)vRespuestaJson["ipuntajesaldoprestamoanterior"];
        sRespuesta->sRespPrestamo.iSumaPuntajeVariables = (int)vRespuestaJson["iSumaPuntajeVariables"];
        sRespuesta->sRespPrestamo.iNumeroMensaje = (int)vRespuestaJson["iNumeroMensaje"];
        iNumeroMensaje = (int)vRespuestaJson["iNumeroMensaje"];
       
		sRespuesta->sRespPrestamo.lMontoMaximoPrestar = (long long int)vRespuestaJson["lMontoMaximoPrestar"];
        mysnprintf(sRespuesta->sRespPrestamo.cMontoMinimo, sizeof(sRespuesta->sRespPrestamo.cMontoMinimo) - 1, "%s", (char *) vRespuestaJson["MontoMinimoPrestamo"]);
		mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje)-1, "El cliente [%d] Si es candidato a prestamo", sSolicitud->sCCuenta.iNumcliente);
		mysnprintf(sRespuesta->sRespPrestamo.Mensaje, sizeof(sRespuesta->sRespPrestamo.Mensaje)-1, "%s",(char *) vRespuestaJson["bAprobo"]);
	} else {
		sRespuesta->status = _ERROR_EN_MENSAJE;
		sRespuesta->sRespPrestamo.lMontoMaximoPrestar = (long long int)vRespuestaJson["lMontoMaximoPrestar"];
		mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje)-1, "El cliente [%d] NO es apto para un prestamo", sSolicitud->sCCuenta.iNumcliente);
		mysnprintf(sRespuesta->sRespPrestamo.Mensaje, sizeof(sRespuesta->sRespPrestamo.Mensaje)-1, "%s",(char *) vRespuestaJson["bAprobo"]);
         sRespuesta->sRespPrestamo.iNumeroMensaje = (int)vRespuestaJson["iNumeroMensaje"];
        iNumeroMensaje = (int)vRespuestaJson["iNumeroMensaje"];
	}

    iRespuesta = consultarSEC(_SEC_CARTERA, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    iRespuesta = abrirConexion2( &odbcCartera, cDNS, cBd, cUser, cPss );
    if (iRespuesta != _OK_)
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::consumirWebserviceParametrico", _LOGINFO_);
        bContinuar=false;
    }

    if(bContinuar){
        bPrestamos = verificarCantidadPrestamos(&odbcCartera, sRespuesta, sSolicitud);
    }
	mysnprintf(cLog, sizeof(sRespuesta->sRespPrestamo.iNumeroMensaje)-1, "%ld",sRespuesta->sRespPrestamo.iNumeroMensaje);
    logx(cLog,_LOGINFO_);
    if (!bPrestamos) {

       iNumeroMensaje = 49;

    } else {
        
    }
   /// mysnprintf(iNumeroMensaje, sizeof(iNumeroMensaje)-1, "%ld",(int) vRespuestaJson["iNumeroMensaje"]);
    mysnprintf(cLog, sizeof(cLog)-1, "%ld",iNumeroMensaje);

    logx(cLog,_LOGINFO_); 
    //iNumeroMensaje =sRespuesta->sRespPrestamo.iNumeroMensaje ;
    if(iNumeroMensaje > 0) {

        obtenerDescripcionTdConfiguracionPrestamos( sSolicitud, sRespuesta, iRespuesta, iNumeroMensaje );
        
        if (sSolicitud->cDescMensaje[0] != '\0'){

        replaceWord(sRespuesta->cDescMensaje, "__", sSolicitud->cDescMensaje, cWord);
        mysnprintf(sRespuesta->cDescMensaje,400, "%s", cWord);

        }
    }else {
        obtenerDescripcionTdConfiguracionPrestamos( sSolicitud, sRespuesta, iRespuesta, iNumeroMensaje );
    }
	
	soap_destroy(soapParametricoPrestamo);
    soap_end(soapParametricoPrestamo);
    soap_free(soapParametricoPrestamo);
}
bool Cwsprestamos00028::consultarParametricoPrestamo(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
    bool bAprobo = false;
    int iClienteTestigo = 0;
    char cLog[512] = {0};
    int iMontoMinimoPrestamo = 0;
    
    sRespuesta->sRespPrestamo.lFactorLineaReal = obtenerFactorLinea(odbcTiendaNumero, sSolicitud, sRespuesta);
    sRespuesta->sRespPrestamo.iFlagModifacionParametrico = obtenerFlag( odbcTiendaNumero,'C', FLAGC_MODIFICACION_PARAMETRICO_PRESTAMOS, sRespuesta);
    sRespuesta->sRespPrestamo.iFlagPrestamoEmpleado = obtenerFlag( odbcTiendaNumero,'C', FLAG_SERV_ISVR, sRespuesta);
    if ( obtenerCasoNuevoCliente( odbcTiendaNumero, sSolicitud, sRespuesta) ) { iClienteTestigo = 1; } //parametrico Actual
    if ( obtenerIpCredito( odbcTiendaNumero, sRespuesta)                                           && 
         obtenFecha( odbcTiendaNumero, sRespuesta)                                                 && 
         buscarClienteCCuenta(odbcTiendaNumero, odbcCartera, sSolicitud, sRespuesta)               && 
         obtenerParametricoPrestamos(odbcTiendaNumero,sSolicitud, sRespuesta, iClienteTestigo)     && 
         obtenerMinimoPrestamo(odbcTiendaNumero, iMontoMinimoPrestamo, sRespuesta)) {
            
        if ( !checarCuentaReestructurada(sSolicitud, sRespuesta) ) {

            checarCondicionCliente(odbcCartera, odbcTiendaNumero,sSolicitud, sRespuesta, iClienteTestigo);
            
            if ( sRespuesta->sRespPrestamo.iNumeroMensaje <= 0) {
                checarCondicionClienteLocalCC(odbcTiendaNumero, odbcCartera, sSolicitud, sRespuesta);

                if ( sRespuesta->sRespPrestamo.iFlagCondicionClienteLocalCC == 1 ) {
                    if ( sRespuesta->sRespPrestamo.lMontoMaximoPrestar >= iMontoMinimoPrestamo ) {
                        bAprobo = true;
                    } else {
                        sRespuesta->sRespPrestamo.iNumeroMensaje = 48;
                    }
                }                               
            }	                          
        }
    }
    if ( obtenerCasoNuevoCliente( odbcTiendaNumero, sSolicitud, sRespuesta ) ) {
        iClienteTestigo=1;
    }
    return bAprobo;
}
int Cwsprestamos00028::obtenerFlag( C_ODBC *odbcTiendaNumero, char cArea, int iTipo, sRespuestaServicio *sRespuesta ) {
    int iFlag=0;
    char sSqlTxt[128] = {0}, cLog[200] = {0};
    logx("OBTENER FLAAAGS!!!", _LOGINFO_);
    mysnprintf(sSqlTxt, sizeof(sSqlTxt)-1,"select gnconsultarflag( '%c','%d') ", cArea, iTipo );
    CRegistro  FlagCoppel(odbcTiendaNumero );
    logx("ENTRO A CHECAR FLAGS!!!!", _LOGINFO_);
    logx(sSqlTxt, _LOGINFO_);
    FlagCoppel.agregarCampoEntero("flag", DT_ENTERO);

    if( FlagCoppel.Exec( sSqlTxt ) ) {
        FlagCoppel.activarCols();
        if( FlagCoppel.Leer() ) {
            iFlag = FlagCoppel.valorLong("flag");
        }
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA gnconsultarflag");
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gnconsultarflag, ERROR:[%.150s]", FlagCoppel.error() );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    mysnprintf(cLog, 100,"ESTE ES EL FLAG SOLICITADO == %d", iFlag);
    logx(cLog, _LOGINFO_);
    return iFlag;
}
bool Cwsprestamos00028::obtenerCasoNuevoCliente( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta ) {
    char cSql[256] = {0}, cLog[512] = {0}, cTex[15] = {0};
    int iLongitud = 0;
    bool bClienteV = false;

    mysnprintf(cTex, sizeof(cTex)-1,"%d", sSolicitud->sCCuenta.iNumcliente);
    iLongitud = mystrnlen(cTex);
    mysnprintf(cTex, sizeof(cTex)-1,"%c%c",cTex[iLongitud-3],cTex[iLongitud-2]);

    mysnprintf(cSql, sizeof(cSql)-1,"SELECT COUNT(*) AS Total FROM tdconfiguracion WHERE elemento = 'GRUPO_TESTIGOS_PRESTAMOS' AND valor LIKE '%%-%s-%%';",cTex);
    CRegistro objClientesNvoTestigo(odbcTiendaNumero, false);
    objClientesNvoTestigo.agregarCampoEntero("Total", DT_ENTERO);
     logx("SI JALO a obtenerCasoNuevoCliente", _LOGINFO_);
    if ( objClientesNvoTestigo.Exec(cSql) ) {
        objClientesNvoTestigo.activarCols();
        if(objClientesNvoTestigo.leer()) {
            if ( objClientesNvoTestigo.valorLong("Total") > 0) {
                bClienteV = true;
            }
        }
    } else {
        sRespuesta->status = _ERROR_EN_MENSAJE;
        mysnprintf(sRespuesta->cMensaje, 255,"%s", "Error al consultar objClientesNvoTestigo");
        sRespuesta->iDevStatus = _ERROR_QUERY_;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "Error al consultar objClientesNvoTestigo");
    }
    return bClienteV;
}
bool Cwsprestamos00028::obtenerIpCredito( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta ) {
    bool bConsulta = false;
    
    char cLog[256] = {0}; 
    if( consultarIpServidorggnml( odbcTiendaNumero, (short)2, sRespuesta->sSysRopa.cIpServidorCarteraCentral ) == true &&           
        consultarIpServidorggnml( odbcTiendaNumero, SERV_CARTERA, sRespuesta->sSysRopa.cIpServidorCartera ) == true ) {
            bConsulta = true;
    }
    return bConsulta;
}
bool Cwsprestamos00028::obtenFecha( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta ) {
    char cSql[TAM_MED_BUFF] = {0}, cLog[512] = {0};
    bool bContinuar = false;
	int iCiudad;	
	int iTasaInteresPrestamos;
	int iInteresMoratorioPrestamos;
	int iMontoMinimoBoleto;
	int iMontoBoleto;
	int iTasaInteresBancoppel;
	int iInteresMoratorioBancoppel;
	char cNombreCiudad[22];
	char cDomicilio[22];
	char cTelefono[12];
	char cfecha[14];
	char ifecha[14];
	char iDiaActual[3] = {0};
    char iMesActual[3] = {0};
    char iAnioActual[8] = {0};

    mysnprintf(cSql, sizeof(cSql)-1,"%s","SELECT ciudad,nombreciudad,domicilio,telefono,fecha::char(10),pesosunidadcredito,tasainteresprestamos,interesmoratorioprestamos,"
                  "montominimoboletos,"
                  "montoboletos,tasainteresbancoppel,interesmoratoriobancoppel, salariominimo FROM gndominio ");

    CRegistro Fecha( odbcTiendaNumero );
    Fecha.agregarCampoEntero("ciudad",DT_ENTERO_CORTO);
    Fecha.agregarCampoChar("nombreciudad",20);
    Fecha.agregarCampoChar("domicilio",20);
    Fecha.agregarCampoChar("telefono",10);
    Fecha.agregarCampoChar("fecha", 10);
    Fecha.agregarCampoEntero("pesosunidadcredito",DT_ENTERO);
    Fecha.agregarCampoEntero("tasainteresprestamos",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("interesmoratorioprestamos",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("montominimoboletos",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("montoboletos",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("tasainteresbancoppel",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("interesmoratoriobancoppel",DT_ENTERO_CORTO);
    Fecha.agregarCampoEntero("salariominimo",DT_ENTERO);

    if( Fecha.Exec( cSql ) ) {
        Fecha.activarCols();
        if( Fecha.Leer() ) {
            mysnprintf( cNombreCiudad,21, "%s", Fecha.valorChar( "nombreciudad" ));
            mysnprintf( cDomicilio   ,21, "%s", Fecha.valorChar( "domicilio" ));
            mysnprintf( cTelefono    ,11, "%s", Fecha.valorChar( "telefono" ));
            mysnprintf( cfecha       ,11, "%s", Fecha.valorChar( "fecha" ));

            iCiudad                     = Fecha.valorShort("ciudad");
            iTasaInteresPrestamos       = Fecha.valorShort("tasainteresprestamos");
            iInteresMoratorioPrestamos  = Fecha.valorShort("interesmoratorioprestamos");
            iMontoMinimoBoleto          = Fecha.valorShort("montominimoboletos");
            iMontoBoleto                = Fecha.valorShort("montoboletos");
            sRespuesta->sRespPrestamo.lSalarioMinimo                = Fecha.valorLong("salariominimo");
            iTasaInteresBancoppel       = Fecha.valorShort("tasainteresbancoppel");
            iInteresMoratorioBancoppel  = Fecha.valorShort("interesmoratoriobancoppel");
            bContinuar = true;

            mysnprintf(ifecha,14,"%s",cfecha);
            mysnprintf(iDiaActual,3,"%c%c",ifecha[8],ifecha[9]);
            sRespuesta->sRespPrestamo.iDiaActual = intConverter(iDiaActual);
            mysnprintf(iMesActual,3,"%c%c",ifecha[5],ifecha[6]);
            sRespuesta->sRespPrestamo.iMesActual = intConverter(iMesActual);
            mysnprintf(iAnioActual,8,"%c%c%c%c",cfecha[0],cfecha[1],cfecha[2],cfecha[3]);
            sRespuesta->sRespPrestamo.iAnioActual = intConverter(iAnioActual);
        }

    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA gndominio obtenerFecha");
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gndominio, ERROR:[%.150s]", Fecha.error() );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }   
    return bContinuar;
}
void Cwsprestamos00028::obtenerInfoEmpleados(  sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta ) {
    char cSql[TAM_MED_BUFF] = {0}, cLog[512] = {0};
    C_ODBC odbcTiendaNumero;
    char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);

    if (iRespuesta == _OK_)
    {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
    }
    else
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
    }

    mysnprintf(cSql, sizeof(cSql)-1,"%s","SELECT nombregerentecajas FROM gndominio ");

    CRegistro infoEmpleados( &odbcTiendaNumero );

    infoEmpleados.agregarCampoChar("nombregerentecajas", 50);

    if( infoEmpleados.Exec( cSql ) ) {
        infoEmpleados.activarCols();

        if( infoEmpleados.Leer() ) {
            mysnprintf( sRespuesta->sRespPrestamo.cNombreGerenteCajas, 51, "%s",infoEmpleados.valorChar( "nombregerentecajas" ) );
            sRespuesta->status = _MENSAJE_CORRECTO_;

        }

    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA gndominio obtenerInfoEmpleados");
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gndominio, ERROR:[%.150s]", infoEmpleados.error() );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }

}

bool Cwsprestamos00028::buscarClienteCCuenta(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
    bool bEncontro = false;
    long lSaldo12=0,lSaldo18=0;
    int iTasainteresmoratorio8x = 0;
    int lLineaDeCreditoReal;
    char cSql[250] = {0}, cFechaAlta[14], iFechaAlta[14], cLog[512] = {0};
    int lAbonoBasePromedio = 0;
    sRespuesta->iDevStatus = _MENSAJE_CORRECTO_;
    char iFechaAltaDia[3] = {0};
    char iFechaAltaMes[3] = {0};
    char iFechaAltaAnio[8] = {0};
    
    if(consultarInfoPlazos(odbcTiendaNumero, sRespuesta, iTasainteresmoratorio8x)) {

        mysnprintf(cSql, sizeof(cSql)-1, "SELECT fechaalta FROM crcliente WHERE cliente = %d",  sSolicitud->sCCuenta.iNumcliente);
        CRegistro fechaalta( odbcCartera );
        fechaalta.agregarCampoFecha("fechaalta");
		      
        if ( fechaalta.Exec( cSql ) ) {
            fechaalta.activarCols();
            if ( fechaalta.leer() ) {
                mysnprintf( cFechaAlta,14, "%s", fechaalta.valorFecha( "fechaalta" ));
                mysnprintf(iFechaAlta,14,"%s",cFechaAlta);
                mysnprintf(iFechaAltaDia,3,"%c%c",iFechaAlta[8],iFechaAlta[9]);
                sRespuesta->sRespPrestamo.cFechaAltaDia = intConverter(iFechaAltaDia);
                mysnprintf(iFechaAltaMes,3,"%c%c",iFechaAlta[5],iFechaAlta[6]);
                sRespuesta->sRespPrestamo.cFechaAltaMes = intConverter(iFechaAltaMes);
                mysnprintf(iFechaAltaAnio,8,"%c%c%c%c",cFechaAlta[0],cFechaAlta[1],cFechaAlta[2],cFechaAlta[3]);
                sRespuesta->sRespPrestamo.cFechaAltaAnio = intConverter(iFechaAltaAnio);
            }
        } else {
            sRespuesta->iDevStatus = E00001_ERROR_QUERY;
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA crCliente");
            mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA crCliente, ERROR:[%.150s]", fechaalta.error() );
            sRespuesta->status = _ERROR_DE_SERVIDOR;
        }

        obtenerMonto12y18MesesMuebles( odbcCartera, sSolicitud, sRespuesta, lSaldo12, lSaldo18 );
        sRespuesta->sRespPrestamo.lSaldoTotal =  sSolicitud->DatosPrestamo.lSaldoFactorizadoTotal / 100;
		      
		      
        mysnprintf(cSql, sizeof(cSql)-1,"SELECT mesesTranscurridos, abonoPromedio, num_parprestamo3, parPrestamo2, LineaDeCreditoReal FROM crCliente WHERE cliente = %d ", sSolicitud->sCCuenta.iNumcliente);

        CRegistro parametrico( odbcCartera );
        parametrico.agregarCampoEntero("mesesTranscurridos", DT_ENTERO);
        parametrico.agregarCampoEntero("abonoPromedio", DT_ENTERO);
        parametrico.agregarCampoEntero("num_parprestamo3", DT_ENTERO);
        parametrico.agregarCampoEntero("parPrestamo2", DT_ENTERO);
        parametrico.agregarCampoEntero("lLineaDeCreditoReal", DT_ENTERO);

        if ( parametrico.Exec(cSql) ) {
            parametrico.activarCols();
            if(parametrico.leer()) {
                sRespuesta->sRespPrestamo.iAntiguedadMeses = parametrico.valorLong("mesesTranscurridos");
                lAbonoBasePromedio = parametrico.valorLong("abonoPromedio");
                if(sRespuesta->sRespPrestamo.iFlagModifacionParametrico == 1) {
                    sRespuesta->sRespPrestamo.lParPrestamos = parametrico.valorLong("num_parprestamo3");
                } else {
                    sRespuesta->sRespPrestamo.lParPrestamos = parametrico.valorLong("parPrestamo2");
                }
                lLineaDeCreditoReal = parametrico.valorLong("lLineaDeCreditoReal");
            }
        } else {
            sRespuesta->iDevStatus = E00001_ERROR_QUERY;
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA crCliente");
            mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA crCliente, ERROR:[%.150s]", parametrico.error() );
            sRespuesta->status = _ERROR_DE_SERVIDOR;
        }
	   
        if ( lLineaDeCreditoReal > 0 ) {
            sRespuesta->sRespPrestamo.lLineaRealCred  = (long)(( (double) lLineaDeCreditoReal / sRespuesta->sRespPrestamo.lFactorLineaReal ) * sRespuesta->sRespPrestamo.lSalarioMinimo + .5 );
        } else {
            sRespuesta->sRespPrestamo.lLineaRealCred  = sRespuesta->sRespPrestamo.lSalarioMinimo;
        }
    
        sRespuesta->sRespPrestamo.lMargenCreditoDisponible = sRespuesta->sRespPrestamo.lLineaRealCred  - sRespuesta->sRespPrestamo.lSaldoTotal;
        if (sRespuesta->sRespPrestamo.lMargenCreditoDisponible < 0 ) sRespuesta->sRespPrestamo.lMargenCreditoDisponible = 0;

        if( sRespuesta->iDevStatus == _MENSAJE_CORRECTO_ ) {
            bEncontro = true;
        } else {
            logx(sRespuesta->cDevMensaje, _LOGINFO_ );
        }

    }
    return bEncontro;
}

bool Cwsprestamos00028::verificarCantidadPrestamos( C_ODBC *odbcCartera, sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud )
{
	bool bRegresa = false;
    bool bCuatroPrestamos = false;
    char sSqlTxt[1000] = {0}, cLog[1000] = {0};
    int iRespuesta = 0;

    CRegistro CuatroPrestamos( odbcCartera ,false );

    CuatroPrestamos.agregarCampoEntero("crnumerodeprestamos",DT_ENTERO_LARGO);
    CuatroPrestamos.valorLong("cliente",sSolicitud->sCCuenta.iNumcliente );

    mysnprintf(sSqlTxt, 400,"SELECT crnumerodeprestamos from crnumerodeprestamos('%d'); ", sSolicitud->sCCuenta.iNumcliente);

    if( !CuatroPrestamos.Exec( sSqlTxt ) )
	{
        iRespuesta = CuatroPrestamos.valorLong("crnumerodeprestamos");
		sRespuesta->status = E00001_ERROR_QUERY;
        bRegresa = false;
	}
	else
	{
        CuatroPrestamos.activarCols();
		if( CuatroPrestamos.Leer() )
		{
            iRespuesta = CuatroPrestamos.valorLong("crnumerodeprestamos");

            if(iRespuesta >= 4)
            {
                bRegresa = false;  
                bCuatroPrestamos = true;
            }
            else
            {
                bRegresa = true;
                bCuatroPrestamos = false;
            }

		}

	}

    return bRegresa;
}

bool Cwsprestamos00028::consultarInfoPlazos(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, int &iTasainteresmoratorio8x) {
    bool bContinuar = false;
    char cSql[350] = {0}, cLog[100] = {0}; 
    
    mysnprintf(cSql, sizeof(cSql)-1,"%s", " SELECT plazomeses, tasasobreprecio, tasainteresmoratorio,compraminima, flagplazo "
                   " FROM rocatalogoplazoropa WHERE plazomeses = 8;" );
    CRegistro xInfoPlazos(odbcTiendaNumero, false);
    xInfoPlazos.agregarCampoEntero("tasainteresmoratorio", DT_ENTERO);

    if( xInfoPlazos.Exec( cSql ) ) {
        xInfoPlazos.activarCols();

        if( xInfoPlazos.Leer() ) {
            iTasainteresmoratorio8x = xInfoPlazos.valorLong("tasainteresmoratorio");
            bContinuar = true;
        }
    } else {    
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA rocatalogoplazoropa");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA rocatalogoplazoropa, ERROR:[%.150s]", xInfoPlazos.error() );
        logx( sRespuesta->cMensaje , _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bContinuar;
}
void Cwsprestamos00028::obtenerMonto12y18MesesMuebles( C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long &lSaldo12, long &lSaldo18  ) {
    char cSql[350] = {0};
    int plazo = 0;
    mysnprintf(cSql, sizeof(cSql)-1, "select plazo,saldo from crcmuebles WHERE cliente = %d ", sSolicitud->sCCuenta.iNumcliente );
    CRegistro saldoPlazo12y18( odbcCartera );
    saldoPlazo12y18.agregarCampoEntero("plazo", DT_ENTERO);
    saldoPlazo12y18.agregarCampoEntero("saldo", DT_ENTERO);

    if( saldoPlazo12y18.Exec( cSql ) )
    {
        saldoPlazo12y18.activarCols();
        while( saldoPlazo12y18.Leer() )
        {
            plazo = saldoPlazo12y18.valorLong("plazo");
            if ( plazo == 12) {
                lSaldo12 += saldoPlazo12y18.valorLong("saldo");
            } else if ( plazo == 18) {
                lSaldo18 += saldoPlazo12y18.valorLong("saldo");
            }           
        }
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA CrCMuebles PlazoCartera");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA CrCMuebles, ERROR:[%.150s]", saldoPlazo12y18.error() );
        logx( sRespuesta->cMensaje , _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    
}
bool Cwsprestamos00028::obtenerParametricoPrestamos(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iClienteTestigo) {
    char cSql[512] = {0}, cLog[212] = {0};
    bool bRegresa = false;
    int iGrupo = 0;
    long lSaldaCon = 0L;
    sRespuesta->sRespPrestamo.iAntiguedadMeses = meses_transcurridos( sRespuesta->sRespPrestamo.cFechaAltaDia, sRespuesta->sRespPrestamo.cFechaAltaMes, sRespuesta->sRespPrestamo.cFechaAltaAnio, sRespuesta->sRespPrestamo.iDiaActual, sRespuesta->sRespPrestamo.iMesActual, sRespuesta->sRespPrestamo.iAnioActual);

    if(sRespuesta->sRespPrestamo.iFlagModifacionParametrico == 1) {
        if(consultarClienteModificacionParametrico(odbcTiendaNumero, sSolicitud, sRespuesta, iGrupo)) {
            lSaldaCon = sSolicitud->DatosPrestamo.SaldaCon;

            switch(iGrupo) {
            case 0:
                iGrupo = 3;
                mysnprintf(cSql, sizeof(cSql)-1, "SELECT ipuntajefinal,imontomaximoprestar,fFactorParametrico,ipuntosiniciales,ipuntosvariables,ipuntajesaturacion,puntossaldoprestamoanterior FROM caobtenerparametricoprestamos05( '%d', '%ld','%ld', '%ld', '%ld','%d')", sRespuesta->sRespPrestamo.iAntiguedadMeses,sRespuesta->sRespPrestamo.lParPrestamos,sRespuesta->sRespPrestamo.lLineaRealCred ,sRespuesta->sRespPrestamo.lSaldoTotal,lSaldaCon,iGrupo);
                break;
            case 1:
                mysnprintf(cSql, sizeof(cSql)-1, "SELECT ipuntajefinal,imontomaximoprestar,fFactorParametrico,ipuntosiniciales,ipuntosvariables,ipuntajesaturacion,0 as puntossaldoprestamoanterior FROM caobtenerparametricoprestamosnuevo02( '%d', '%ld','%ld', '%ld')", sRespuesta->sRespPrestamo.iAntiguedadMeses,sRespuesta->sRespPrestamo.lParPrestamos,sRespuesta->sRespPrestamo.lLineaRealCred ,sRespuesta->sRespPrestamo.lSaldoTotal );
                break;
            case 2:
                mysnprintf(cSql, sizeof(cSql)-1, "SELECT ipuntajefinal,imontomaximoprestar,fFactorParametrico,ipuntosiniciales,ipuntosvariables,ipuntajesaturacion,puntossaldoprestamoanterior FROM caobtenerparametricoprestamos05( '%d', '%ld','%ld', '%ld', '%ld','%d')", sRespuesta->sRespPrestamo.iAntiguedadMeses,sRespuesta->sRespPrestamo.lParPrestamos,sRespuesta->sRespPrestamo.lLineaRealCred ,sRespuesta->sRespPrestamo.lSaldoTotal,lSaldaCon,iGrupo);
                break;
            }
        }
    } else {
        if( iClienteTestigo == 1) {
            mysnprintf(cSql, sizeof(cSql)-1, "SELECT ipuntajefinal,imontomaximoprestar,fFactorParametrico,ipuntosiniciales,ipuntosvariables,ipuntajesaturacion,0 as puntossaldoprestamoanterior  FROM caobtenerparametricoprestamos04( '%d', '%ld','%ld', '%ld' )", sRespuesta->sRespPrestamo.iAntiguedadMeses,sRespuesta->sRespPrestamo.lParPrestamos,sRespuesta->sRespPrestamo.lLineaRealCred ,sRespuesta->sRespPrestamo.lSaldoTotal );
        } else {
            mysnprintf(cSql, sizeof(cSql)-1, "SELECT ipuntajefinal,imontomaximoprestar,fFactorParametrico,ipuntosiniciales,ipuntosvariables,ipuntajesaturacion,0 as puntossaldoprestamoanterior  FROM caobtenerparametricoprestamosnuevo02( '%d', '%ld','%ld', '%ld')", sRespuesta->sRespPrestamo.iAntiguedadMeses,sRespuesta->sRespPrestamo.lParPrestamos,sRespuesta->sRespPrestamo.lLineaRealCred ,sRespuesta->sRespPrestamo.lSaldoTotal );
        }
    }
    
    CRegistro parametricoPrestamos( odbcTiendaNumero );
    parametricoPrestamos.agregarCampoEntero("ipuntajefinal", DT_ENTERO);
    parametricoPrestamos.agregarCampoEntero("imontomaximoprestar", DT_ENTERO);
    parametricoPrestamos.agregarCampoEntero("ffactorparametrico", DT_ENTERO);
    parametricoPrestamos.agregarCampoEntero("ipuntosiniciales", DT_ENTERO);
    parametricoPrestamos.agregarCampoEntero("ipuntosvariables", DT_ENTERO);
    parametricoPrestamos.agregarCampoEntero("ipuntajesaturacion", DT_ENTERO);

    if( parametricoPrestamos.Exec( cSql ) ) {
        parametricoPrestamos.activarCols();
        if( parametricoPrestamos.leer() ) {
            int iPuntajeParametricoFinal = parametricoPrestamos.valorLong("ipuntajefinal");
            int iSumaPuntajeVariables = parametricoPrestamos.valorLong("ipuntosvariables");
            sRespuesta->sRespPrestamo.lMontoMaximoPrestar = parametricoPrestamos.valorLong("imontomaximoprestar");
            int iPuntajeSaturacion = parametricoPrestamos.valorLong("ipuntajesaturacion");
            if ( sRespuesta->sRespPrestamo.lMontoMaximoPrestar < 0  ) {
                sRespuesta->sRespPrestamo.lMontoMaximoPrestar = 0;
            }
            int iFactorPrestamo = parametricoPrestamos.valorLong("ffactorparametrico");
            sRespuesta->sRespPrestamo.iPuntosIniciales = parametricoPrestamos.valorLong("ipuntosiniciales");

 
            sRespuesta->sRespPrestamo.iPuntajeParametricoFinal = iPuntajeParametricoFinal;
            sRespuesta->sRespPrestamo.iSumaPuntajeVariables = iSumaPuntajeVariables; //suma de los puntos de las Variables parprestamos,ant, satu y p. iniciales /100
            sRespuesta->sRespPrestamo.ffactor = iFactorPrestamo; //suma de los puntos de las Variables parprestamos,ant, satu y p. iniciales /100
            sRespuesta->sRespPrestamo.iPts_saturacion = iPuntajeSaturacion;//Puntos de saturacion
            ///sRespuesta->sRespPrestamo.ipuntajesaldoprestamoanterior = parametricoPrestamos.ipuntajesaldoprestamoanterior;
            sRespuesta->sRespPrestamo.lSaldaCon = lSaldaCon;
            sRespuesta->sRespPrestamo.iGrupo = iGrupo;
            bRegresa = true;
        }
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA parametricoPrestamos");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA parametricoPrestamos, ERROR:[%.150s]", parametricoPrestamos.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bRegresa;
}
bool Cwsprestamos00028::consultarClienteModificacionParametrico( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iGrupo) {
	bool bClienteV = false;
	int iRangoV = 0;
	char cSql[512] = {0}, cText[200] = {0}, cLog[212] = {0};
    int iLongitud = 0;

    mysnprintf(cText, sizeof(cText)-1,"%s", sSolicitud->cDni);
    strtrim(cText,sizeof(cText));
    iLongitud = mystrnlen(cText);
    mysnprintf(cText, sizeof(cText)-1,"%c%c",cText[iLongitud-2],cText[iLongitud-1]);

    CRegistro objClientesNvoTestigo (odbcTiendaNumero, false);

    mysnprintf(cSql, sizeof(cSql)-1, "select num_grupo from cat_gruposparametricoprestamos where opc_activo = 1 and num_terminaciondni = '%s'",cText);

    objClientesNvoTestigo.agregarCampoEntero("num_grupo", DT_ENTERO);


    if(objClientesNvoTestigo.Exec( cSql ))
    {
        objClientesNvoTestigo.activarCols();
        bClienteV = true;
        while( objClientesNvoTestigo.Leer() ) {
            iGrupo = objClientesNvoTestigo.valorLong("num_grupo");
        }
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA consultarClienteModificacionParametrico");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA consultarClienteModificacionParametrico, ERROR:[%.150s]", objClientesNvoTestigo.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bClienteV;

}
bool Cwsprestamos00028::obtenerMinimoPrestamo(C_ODBC *odbcTiendaNumero, int &iMontoMinimoPrestamo, sRespuestaServicio *sRespuesta) { 
    bool bContinuar = true;
    char sSqlTxt[128] = {0}, cLog[128] = {0};

    mysnprintf(sSqlTxt, sizeof(sSqlTxt)-1,"%s","select topeminimo from tdgruposplazostasasprestamos where plazo = 12 and grupo = 1 ");
    CRegistro topeMinimoPrestamo( odbcTiendaNumero );
    topeMinimoPrestamo.agregarCampoEntero("topeminimo", DT_ENTERO);

    if( topeMinimoPrestamo.Exec( sSqlTxt ) ) {
        topeMinimoPrestamo.activarCols();
        if( topeMinimoPrestamo.Leer() ) {
            iMontoMinimoPrestamo = (int) topeMinimoPrestamo.valorLong("topeminimo");
        }
    } else {
        bContinuar = false;
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA tdgruposplazostasasprestamos");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA tdgruposplazostasasprestamos, ERROR:[%.150s]", topeMinimoPrestamo.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bContinuar;
}
bool Cwsprestamos00028::checarCuentaReestructurada(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
    bool bRegresa = false;
    char cMensaje [150] = {0};

    mysnprintf(cMensaje, sizeof(cMensaje)-1,"%s","  Cliente Indice TipoCta Descrip. SaldaCon Saldo");

    if (sSolicitud->DatosPrestamo.CuentaReestructurada == true) {
        bRegresa = true;
    }
    /*for( int i = 0; i < pCuentaCliente.iIndice; i++ ) {
        if( pCuentaCliente.pCuenta[i].iTipoDeCuenta == 5 )//Cuenta de muebles {
            lAbonado = pCuentaCliente.pCuenta[i].lImporteDeVenta - pCuentaCliente.pCuenta[i].lSaldo;
            if( lAbonado < ( pCuentaCliente.pCuenta[i].lImporteDeVenta * 50 / 100) ) {
                bRegresa = true;
                break;
            }
        }
        mysnprintf(cMensaje, sizeof(cMensaje)-1,"9 %ld   %d       %d    %.11s      %ld      %ld", sSolicitud->sCCuenta.iNumcliente,
            pCuentaCliente.iIndice,
            pCuentaCliente.pCuenta[i].iTipoDeCuenta,
            pCuentaCliente.pCuenta[i].sDescripcion,
            pCuentaCliente.pCuenta[i].lSaldaCon,
            pCuentaCliente.pCuenta[i].lSaldo);
        guardarLog( cMensaje );
    }*/
    if ( bRegresa == true ) {
        sRespuesta->sRespPrestamo.iCuentaReestructurada = 1;
    } else {
        sRespuesta->sRespPrestamo.iCuentaReestructurada = 0;
    }
    return bRegresa;
}
void Cwsprestamos00028::checarCondicionCliente( C_ODBC *odbcCartera, C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iClienteTestigo ) { 
    int iRegresaMsg = 0, iRespuesta = 0;
    long lVencido = 0L;
    bool bRegresa= true;
    bool bPrestamos = true;
    char cTexto[500] = { 0 }, cTexto1[10] = { 0 }, cEdadMax[10] = { 0 }, cSql[512] = { 0 };
    int iNumeroMensaje = 0, iPuntos = 0;
    int iEdadCliente = 0;
    char cWord[400] = {0}, cLog[300] = {0}, cVencido[20] = {0};

    checarFecha(sSolicitud, sRespuesta, iEdadCliente );
    sRespuesta->sRespPrestamo.iAntiguedadMeses = calcularMesesTranscurridos(odbcTiendaNumero, sRespuesta);

    if(sRespuesta->sRespPrestamo.iFlagModifacionParametrico == 1)
    {
        mysnprintf(cSql, sizeof(cSql)-1, "select fun_obtenerpuntajeparametricodeprestamos('%d');", sRespuesta->sRespPrestamo.iGrupo);
    }
    else
    {
        if( iClienteTestigo == 1 ) //Elias Parametrico Actual
        {
            //iPuntos = 72;
            mysnprintf(cSql, sizeof(cSql)-1,"%s", "SELECT puntaje FROM tdParametricoAltoRiesgoNuevo WHERE tipoVariable = 205");
        }
        else
        {
            //iPuntos = 75;
            mysnprintf(cSql, sizeof(cSql)-1,"%s", "SELECT puntaje FROM tdParametricoAltoRiesgoNuevo WHERE tipoVariable = 206");
        }
    }
    
    CRegistro obtenerPuntajeCorte( odbcTiendaNumero );
    obtenerPuntajeCorte.agregarCampoEntero("puntaje", DT_ENTERO);
    if( obtenerPuntajeCorte.Exec( cSql ) ) 
    {
        obtenerPuntajeCorte.activarCols();
        if( obtenerPuntajeCorte.leer() )
        {
            iPuntos = obtenerPuntajeCorte.valorLong("puntaje");
        }
    }
    else
    {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA checarCondicionCliente");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA checarCondicionCliente, ERROR:[%.150s]", obtenerPuntajeCorte.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }

    bPrestamos = verificarCantidadPrestamos(odbcCartera, sRespuesta, sSolicitud);

    if (!bPrestamos) {

        iNumeroMensaje = 49;

    } else {
    }

    lVencido = sSolicitud->DatosPrestamo.lVencidoMuebles + sSolicitud->DatosPrestamo.lVencidoRopa + sSolicitud->DatosPrestamo.lVencidoPrestamos + sSolicitud->DatosPrestamo.lVencidoTiempoAire ;
    obtenerValorTdConfiguracion(odbcTiendaNumero, sRespuesta, "EDAD_MAXIMA_PRESTAMO", cEdadMax, false, 1);
    if( sSolicitud->DatosPrestamo.cSituacionEspecial[0] == ' ' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'G' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'g' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'H' ||
        sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'h' || (sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'S' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 's' &&
        (sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 50 ||
         sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 52 ||
         sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 57 ||
         sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 70   )) ) 
    {
        if ( sSolicitud->DatosPrestamo.cPuntualidad[0] == 'A' || sSolicitud->DatosPrestamo.cPuntualidad[0] == 'a' ) 
        {
            if(sRespuesta->sRespPrestamo.iAntiguedadMeses >= 6)
            {
                if( iEdadCliente <= intConverter(cEdadMax) )
                {  
                    if ( sRespuesta->sRespPrestamo.iPuntajeParametricoFinal >= iPuntos )
                    {
                        if( lVencido == 0L ) 
                        {
                            if(sRespuesta->sRespPrestamo.iFlagModifacionParametrico == 1)
                            {                                
                                if(sRespuesta->sRespPrestamo.iGrupo == 1)
                                {
                                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                                    {
                                        //
                                    }
                                    else
                                    {
                                        iNumeroMensaje=1;
                                
                                    }
                                }
                            }
                            else
                            {
                                if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                                {
                                //
                                }
                                else
                                {
                                    iNumeroMensaje=1;
                                
                                }
                            }
                        }
                        else  
                        {
                            //cliente tiene vencido.
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                            {
                                iNumeroMensaje=2;
                            }
                            else
                            {
                                iNumeroMensaje=3;
                            }
                        }
                    }
                    else
                    {
                        //no paso parametrico
                        //cliente no tiene vencido.
                        if( lVencido == 0L ) 
                        {                   
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                            {
                                //
                                iNumeroMensaje=8;
                            }
                            else
                            {
                                iNumeroMensaje=9;
                            }
                        }
                        else  
                        {
                            //cliente tiene vencido.
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) ////se cambia de 100 a 500 
                            {
                                iNumeroMensaje=10;
                            }
                            else
                            {
                                iNumeroMensaje=11;
                            }
                        }
                    }
                }
                else 
                {
                    //cliente mayor a 65 años.
                    //no paso parametrico
                    //cliente no tiene vencido.
                    if( lVencido == 0L ) 
                    {                   
                        if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                        {
                            //
                            iNumeroMensaje=16;
                        }
                        else
                        {
                            iNumeroMensaje=17;
                        }
                    }
                    else  
                    {
                        //cliente tiene vencido.
                        if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                        {
                            iNumeroMensaje=18;
                        }
                        else
                        {
                            iNumeroMensaje=19;
                        }
                    }
                }
            }

            else
            {
                //la antigüedad es menor a 6
                //no paso parametrico
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                    {
                        //
                        iNumeroMensaje=40; 
                    }
                    else
                    {
                        iNumeroMensaje=41; 
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=42; 
                    }
                    else
                    {
                        iNumeroMensaje=43; 
                    }
                }
            }
        }
        else
        {
            //no tiene puntualidad A
            if( sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'P' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'p' || sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 45)
            {
                if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )
                {
                    iNumeroMensaje=29;
                }
            }

            if( iEdadCliente <= intConverter(cEdadMax) )
            {
                //cliente no tiene vencido.
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                    {
                        iNumeroMensaje=24;
                    }
                    else
                    {
                        iNumeroMensaje=25;
                    
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=26;
                    }
                    else
                    {
                        iNumeroMensaje=27;
                    }
                }
            }
            else
            {
                //cliente >= 65 años
                //cliente no tiene vencido.
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=32;
                    }
                    else
                    {
                        iNumeroMensaje=33;
                    
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                    {
                        iNumeroMensaje=34;
                    }
                    else
                    {
                        iNumeroMensaje=35;
                    }
                }
            }
        }
    }
    else
    {
        //es otra situacion o causa
        if ( sSolicitud->DatosPrestamo.cPuntualidad[0] == 'A' || sSolicitud->DatosPrestamo.cPuntualidad[0] == 'a'  ) 
        {
            if(sRespuesta->sRespPrestamo.iAntiguedadMeses >= 6)
            {
                if( iEdadCliente <= intConverter(cEdadMax) )
                {
                    if ( sRespuesta->sRespPrestamo.iPuntajeParametricoFinal >= iPuntos )//se modifica de 75 a 72 ->Re-calibracion del modelo parametrico de alto reisgo.
                    {
                        //cliente no tiene vencido.
                        if( lVencido == 0L ) 
                        {                   
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                            {
                                //
                                iNumeroMensaje=4; 
                            }
                            else
                            {
                                iNumeroMensaje=5;
                            
                            }
                        }
                        else  
                        {
                            //cliente tiene vencido.
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                            {
                                iNumeroMensaje=6;
                            }
                            else
                            {
                                iNumeroMensaje=7;
                            }
                        }
                    }
                    else
                    {
                        //NO PASO PARAMETRICO
                        //cliente no tiene vencido.
                        if( lVencido == 0L ) 
                        {                   
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                            {
                                //
                                iNumeroMensaje=12;
                            }
                            else
                            {
                                iNumeroMensaje=13;
                            
                            }
                        }
                        else  
                        {
                            //cliente tiene vencido.
                            if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                            {
                                iNumeroMensaje=14;
                            }
                            else
                            {
                                iNumeroMensaje=15;
                            }
                        }
                    }
                }
                else
                {
                    //cliente >= 65 años
                    //no paso parametrico
                    //cliente no tiene vencido.
                    if( lVencido == 0L ) 
                    {                   
                        if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                        {
                            //
                            iNumeroMensaje=20;
                        }
                        else
                        {
                            iNumeroMensaje=21;
                        }
                    }
                    else  
                    {
                        //cliente tiene vencido.
                        if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                        {
                            iNumeroMensaje=22;
                        }
                        else
                        {
                            iNumeroMensaje=23;
                        }
                    }
                }
            }
            else
            {
                //la antigüedad es menor a 6
                //no paso parametrico
                //cliente no tiene vencido.
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        //
                        iNumeroMensaje=44;
                    }
                    else
                    {
                        iNumeroMensaje=45;
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=46;
                    }
                    else
                    {
                        iNumeroMensaje=47;
                    }
                }
            }
        }
        else
        {
            if( sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'P' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'p' || sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 45)
            {
                if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )
                {
                    iNumeroMensaje=29;
                }
            }

            //no tiene puntualidad A
            if( iEdadCliente <= intConverter(cEdadMax) )
            {
                //cliente no tiene vencido.
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                    {
                        
                        iNumeroMensaje=28;
                    }
                    else
                    {
                        iNumeroMensaje=29;
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=30;
                    }
                    else
                    {
                        iNumeroMensaje=31;
                    }
                }
            }
            else
            {
                //cliente >= 65 años
                //cliente no tiene vencido.
                if( lVencido == 0L ) 
                {                   
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )//se cambia de 100 a 500 
                    {
                        //
                        iNumeroMensaje=36;
                    }
                    else
                    {
                        iNumeroMensaje=37;
                    }
                }
                else  
                {
                    //cliente tiene vencido.
                    if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 ) //se cambia de 100 a 500 
                    {
                        iNumeroMensaje=38;
                    }
                    else
                    {
                        iNumeroMensaje=39;
                    }
                }
            }
        }
    }
    if( sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'P' || sSolicitud->DatosPrestamo.cSituacionEspecial[0] == 'p' || sSolicitud->DatosPrestamo.iCausaSituacionEspecial == 45)
    {
        if ( sRespuesta->sRespPrestamo.lMargenCreditoDisponible >= 500 )
        {
            iNumeroMensaje=29;
        }

    }

    sRespuesta->sRespPrestamo.iNumeroMensaje = iNumeroMensaje;

    if(sRespuesta->sRespPrestamo.iNumeroMensaje > 0) {

        obtenerDescripcionTdConfiguracionPrestamos( sSolicitud, sRespuesta, iRespuesta, iNumeroMensaje );
        
        if (sSolicitud->cDescMensaje[0] != '\0'){

        replaceWord(sRespuesta->cDescMensaje, "__", sSolicitud->cDescMensaje, cWord);
        mysnprintf(sRespuesta->cDescMensaje,400, "%s", cWord);

        }

    } else {
        obtenerDescripcionTdConfiguracionPrestamos( sSolicitud, sRespuesta, iRespuesta, iNumeroMensaje );
    }

}
void Cwsprestamos00028::ObtenerCajero( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta){
	
	bool bRegresa = false;
    int iSistema = 0,iCaja = 0,iSistema2 = 0;
    char cTexto[200]={0}, cLog[500]={0}, cSql[1000] = {0};
    char cAreaLocal [3] = {0}, cCaja [3] = {0}, cAreaTienda [3] = {0};
    C_ODBC odbcTiendaNumero;
    char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    
    if (iRespuesta == _OK_)
    {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
    }
    else
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
    }

    iSistema = 1;

    mysnprintf(cSql,500, "select nombre from tdcajaactiva where sistema='%d' and caja='%d'", iSistema, sSolicitud->iCaja);

	CRegistro obtenerCajero( &odbcTiendaNumero );

    obtenerCajero.agregarCampoChar("nombre", 100);

    if ( obtenerCajero.Exec(cSql))
	{
        obtenerCajero.activarCols();

         if( obtenerCajero.Leer() ) {
            mysnprintf( sRespuesta->sRespPrestamo.cNombreCajero, 100, "%s",obtenerCajero.valorChar( "nombre" ) );
            sRespuesta->status = _MENSAJE_CORRECTO_;
        }
	}
	else
    {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA obtenerCajero");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA obtenerCajero, ERROR:[%.150s]", obtenerCajero.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
}

void Cwsprestamos00028::checarFecha( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iEdadCliente ) {
    char cTexto[20],cTexto2[20];
    int iAnioNacimiento = 0;
    int iMesNacimiento = 0;

    iAnioNacimiento = trunc(sSolicitud->DatosPrestamo.FechaNacimiento / 10000);
    iMesNacimiento = trunc((sSolicitud->DatosPrestamo.FechaNacimiento - (iAnioNacimiento * 10000))/100);
    mymemset(cTexto,' ',10);mymemset(cTexto2,' ',10);
    mysnprintf( cTexto, sizeof(cTexto)-1,"%04ld%02d",sRespuesta->sRespPrestamo.iAnioActual,sRespuesta->sRespPrestamo.iMesActual );
    mysnprintf( cTexto2, sizeof(cTexto2)-1,"%04d%02d",ano_2000_4dig(iAnioNacimiento,sRespuesta->sRespPrestamo.iAnioActual),iMesNacimiento );
    iEdadCliente=(valor_campo(cTexto,6)-valor_campo(cTexto2,6))/100L;

    return;
}
void Cwsprestamos00028::obtenerInfoFinancieraPrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta ) {
    char cSql[500] = {0}, cLog[512] = {0};
    C_ODBC odbcTiendaNumero;
    char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    
    if (iRespuesta == _OK_)
    {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
    }
    else
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
    }

    mysnprintf(cSql, 500, "SELECT valor FROM tdconfiguracion WHERE elemento = 'INFORMACION_FINANCIERA_PRESTAMOS';", "asdf" );

    CRegistro ConsultarTdConfiguracion( &odbcTiendaNumero );
     
    ConsultarTdConfiguracion.agregarCampoChar("valor", 499);

    if ( ConsultarTdConfiguracion.Exec( cSql ))
    {
        ConsultarTdConfiguracion.activarCols();
        if ( ConsultarTdConfiguracion.Leer() )
        {
            mysnprintf( sRespuesta->sRespPrestamo.cValorInfo, 499, "%s",ConsultarTdConfiguracion.valorChar( "valor" ) );
            sRespuesta->status = _MENSAJE_CORRECTO_;
        }
    }
    else
    {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA obtenerInfoFinancieraPrestamo");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA obtenerInfoFinancieraPrestamo, ERROR:[%.150s]", ConsultarTdConfiguracion.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
}
bool Cwsprestamos00028::obtenerValorTdConfiguracion(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, char *cElemento, char *cValor, bool bCommit, int opcion ) {  
    char cSql[256] = {0};
    bool bRegresa = false;

    mysnprintf(cSql, sizeof(cSql)-1, "SELECT TRIM( valor ) FROM tdconfiguracion WHERE elemento = '%s';", cElemento );

    CRegistro ConsultarTdConfiguracion( odbcTiendaNumero, bCommit );
    if ( opcion == 1) {
        ConsultarTdConfiguracion.agregarCampoEntero("btrim", DT_ENTERO);
    } else {
        ConsultarTdConfiguracion.agregarCampoChar("ctrim", 250);
    }

    if ( ConsultarTdConfiguracion.Exec( cSql ))
    {
        ConsultarTdConfiguracion.activarCols();
        if ( ConsultarTdConfiguracion.Leer() )
        {
            if ( opcion == 1) {
                mysnprintf( cValor,10, "%ld", ConsultarTdConfiguracion.valorLong("btrim"));
            } else {
                mysnprintf( cValor,150,"%s", ConsultarTdConfiguracion.valorChar("ctrim"));
            }
            bRegresa = true;
        }
    }       
    else
    {
        bRegresa = false;
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA obtenerValorTdConfiguracion");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA obtenerValorTdConfiguracion, ERROR:[%.150s]", ConsultarTdConfiguracion.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bRegresa;
}

int Cwsprestamos00028::obtenerDescripcionTdConfiguracionPrestamos(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta, int &iNumeroMensaje ) { 

    char cSql[500] = {0};
    C_ODBC odbcTiendaNumero;
    char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
    char cWord[400] = {0}, cDescMensaje[400] = { 0 }, cLog[300] = {0}, cVencido[20] = {0};
    long lVencido;

    lVencido = sSolicitud->DatosPrestamo.lVencidoMuebles + sSolicitud->DatosPrestamo.lVencidoRopa + sSolicitud->DatosPrestamo.lVencidoPrestamos + sSolicitud->DatosPrestamo.lVencidoTiempoAire ;
    mysnprintf(cVencido,16,"%ld", lVencido);

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);

    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);

    if (iRespuesta == _OK_)
    {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
    }
    else
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
    }

    mysnprintf(cSql, 500, "SELECT TRIM( descripcion ) FROM tdconfiguracionprestamos WHERE mensaje = '%d' ;", iNumeroMensaje );

    CRegistro ConsultarTdConfiguracionPrestamos( &odbcTiendaNumero );
    ConsultarTdConfiguracionPrestamos.agregarCampoChar("descripcion", 400);

    if ( ConsultarTdConfiguracionPrestamos.Exec( cSql ))
    {
        ConsultarTdConfiguracionPrestamos.activarCols();
        if ( ConsultarTdConfiguracionPrestamos.Leer() )
        {
            mysnprintf(sRespuesta->cDescMensaje, sizeof(sRespuesta->cDescMensaje)-1, "%s", ConsultarTdConfiguracionPrestamos.valorChar("descripcion"));
            sRespuesta->status = _MENSAJE_CORRECTO_;
            replaceWord(sRespuesta->cDescMensaje, "__", cVencido, cWord);
            mysnprintf(sRespuesta->cDescMensaje,400, "%s", cWord);
            mysnprintf(cSql, 400,"NUMERO MENSAJE =  %d y Descripcion: %s", iNumeroMensaje, sRespuesta->cDescMensaje);
            logx(cSql,_LOGINFO_);
        }
    }        
    else
    {
        logx(":::::::::NO SE PUDO EJECUTAR EL QUERY PARA obtenerDescripcionTdConfiguracionPrestamos::::::::::", _LOGINFO_);
    }
}
int Cwsprestamos00028::calcularMesesTranscurridos(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta) {
    int iMeses = 0;
    char cSql[1024] = {0};

    mysnprintf(cSql, sizeof(cSql)-1, "SELECT tdcalcularmesestranscurridos( '%04ld-%02d-%02d' , '%04ld-%02d-%02d' )",sRespuesta->sRespPrestamo.cFechaAltaAnio, sRespuesta->sRespPrestamo.cFechaAltaMes, sRespuesta->sRespPrestamo.cFechaAltaDia, sRespuesta->sRespPrestamo.iAnioActual, sRespuesta->sRespPrestamo.iMesActual, sRespuesta->sRespPrestamo.iDiaActual);

    CRegistro objMesesAnt (odbcTiendaNumero, false);
    objMesesAnt.agregarCampoEntero("tdcalcularmesestranscurridos", DT_ENTERO);

    if(objMesesAnt.Exec( cSql )) {
        objMesesAnt.activarCols();
        while ( objMesesAnt.Leer() ) {
            iMeses = objMesesAnt.valorLong("tdcalcularmesestranscurridos");
        }   
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA calcularMesesTranscurridos");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA calcularMesesTranscurridos, ERROR:[%.150s]", objMesesAnt.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return iMeses;
}
int Cwsprestamos00028::checarCondicionClienteLocalCC( C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
    int  iFlag = 0, iMesesPrimerCompra = 0;
    char cFechaPrimerCompra[11] = {0}, cSql[210] = {0};
    int iFlagMensaje = 0;

	   
    mysnprintf(cSql, sizeof(cSql)-1, "SELECT fechaprimercompra FROM crcliente WHERE cliente = %d",  sSolicitud->sCCuenta.iNumcliente);
    CRegistro fechaprimercompra( odbcCartera );
    fechaprimercompra.agregarCampoFecha("fechaprimercompra");
	   
    if ( fechaprimercompra.Exec( cSql ) ) {
        fechaprimercompra.activarCols();
        if ( fechaprimercompra.leer() ) {
            mysnprintf( cFechaPrimerCompra,11, "%s", fechaprimercompra.valorFecha( "fechaprimercompra" ));
        }
    } else {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA crCliente");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA crCliente, ERROR:[%.150s]", fechaprimercompra.error() );
        logx( sRespuesta->cMensaje , _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }

    obtenerMesesTransCC(odbcTiendaNumero, odbcCartera, sSolicitud, sRespuesta);

    if( sSolicitud->DatosPrestamo.cPuntualidad[0] == 'N' && strncmp( cFechaPrimerCompra, "1900-01-01", 10 ) != 0  )
    {
         obtenerMesesPorFecha( odbcTiendaNumero, cFechaPrimerCompra, iMesesPrimerCompra );
    }

    iFlag = 1;

    if( sSolicitud->DatosPrestamo.VencidoTotal > 0 )
    {
        int lVencido = sSolicitud->DatosPrestamo.lVencidoMuebles + sSolicitud->DatosPrestamo.lVencidoRopa + sSolicitud->DatosPrestamo.lVencidoPrestamos + sSolicitud->DatosPrestamo.lVencidoTiempoAire ;
        
        mysnprintf(cSql, sizeof(cSql)-1,"Pagar vencido de $%d", lVencido );
        sRespuesta->sRespPrestamo.iMostrarVencido = 1;
        sRespuesta->sRespPrestamo.bInicializar = true;
        iFlag = 0;
    }

    sRespuesta->sRespPrestamo.iFlagCondicionClienteLocalCC = iFlag;
    sRespuesta->sRespPrestamo.iFlagMensaje = iFlagMensaje;
    return iFlag;
} 
void Cwsprestamos00028::obtenerMesesTransCC(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
    char cSql[250] = {0};

    mysnprintf(cSql, sizeof(cSql)-1, "SELECT mesestranscurridos FROM crcliente WHERE cliente = %d LIMIT 1 ", sSolicitud->sCCuenta.iNumcliente );
    CRegistro mesesTranscurridos( odbcCartera );
    mesesTranscurridos.agregarCampoEntero("mesestranscurridos", DT_ENTERO);

    if( !mesesTranscurridos.Exec( cSql ) )
    {
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA obtenerMesesTransCC");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA obtenerMesesTransCC, ERROR:[%.150s]", mesesTranscurridos.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    else
    {
        mesesTranscurridos.activarCols();
        if( mesesTranscurridos.Leer() )
        {
            // 
        }
    }
}
bool Cwsprestamos00028::obtenerMesesPorFecha( C_ODBC *odbcTiendaNumero, char *cFecha, int &iMeses ) {
    bool bContinuar = true;
    char cSql[254] = { 0 }; 
    iMeses = 0;
    
    mysnprintf(cSql, sizeof(cSql)-1, "SELECT ( INT2( date_part( 'year',  age( fecha, '%s' ) ) ) * 12 ) + INT2( date_part( 'month', age( fecha, '%s' ) ) ) FROM gndominio;", cFecha, cFecha );
    CRegistro obtenerMeses( odbcTiendaNumero );
    obtenerMeses.agregarCampoEntero("Total",DT_ENTERO);
    if( obtenerMeses.Exec( cSql ) )
    { 
        obtenerMeses.activarCols();
        if( obtenerMeses.leer() ) {
            iMeses = obtenerMeses.valorLong( "Total" );
        }
    }
    else
    {
        bContinuar = false;
    }
    return bContinuar;
}

void Cwsprestamos00028::obtenerFolioPrestamo( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta )
{
	long lRetFolio = 0;
    char cSql[1000] = {0}, cLog[1000] = {0};
    C_ODBC odbcTiendaNumero;
    char cUsuarioBD[20] = {0}, cPassBD[36] = {0}, cNombreBD[20] = {0}, cIpBdServidor[20] = {0}, Mensaje[150] = {0};
    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};

    obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
    iRespuesta = consultarSEC(cTiendaNumero, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    
    if (iRespuesta == _OK_)
    {
        iRespuesta = abrirConexion2(&odbcTiendaNumero, cDNS, cBd, cUser, cPss);
    }
    else
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::wsconsultarParametricoPrestamo", _LOGINFO_);
    }

    mysnprintf(cSql, 1000, "SELECT gnincrementarfolio('C','0','%d','%01d')", FOLIOC_PRESTAMO, 0 );
    
	CRegistro obtenerFolio( &odbcTiendaNumero );
    obtenerFolio.agregarCampoEntero("gnincrementarfolio",DT_ENTERO_LARGO);
	if( !obtenerFolio.Exec( cSql ) )
	{
        logx("NO SE PUDO OBTENER EL FOLIO DEL PRESTAMO", _LOGINFO_);
	}
	else
	{
		obtenerFolio.activarCols();
		if( obtenerFolio.Leer() )
		{
			sRespuesta->lRetFolio = obtenerFolio.valorLong("gnincrementarfolio");
            sRespuesta->status = _MENSAJE_CORRECTO_;
		}
	}
}

bool Cwsprestamos00028::obtenerTasaInteres(C_ODBC *odbcTiendaNumero, int &iTasaInteresPrestamos, sRespuestaServicio *sRespuesta) { 
    bool bContinuar = true;
    char sSqlTxt[128] = {0}, cLog[128] = {0};

    mysnprintf(sSqlTxt, sizeof(sSqlTxt)-1,"%s","select tasainteresprestamos, parametroprestamos from gndominio"); //
    CRegistro tasaInteresPrestamos( odbcTiendaNumero );
    tasaInteresPrestamos.agregarCampoEntero("tasainteresprestamos", DT_ENTERO);
    tasaInteresPrestamos.agregarCampoEntero("parametroprestamos", DT_ENTERO); //

    if( tasaInteresPrestamos.Exec( sSqlTxt ) ) {
        tasaInteresPrestamos.activarCols();
        if( tasaInteresPrestamos.Leer() ) {
            iTasaInteresPrestamos = (int) tasaInteresPrestamos.valorLong("tasainteresprestamos");
            sRespuesta->iTasaInteresPrestamos = iTasaInteresPrestamos;
            sRespuesta->iParametricoTda = (int) tasaInteresPrestamos.valorLong("parametroprestamos");
        }
    } else {
        bContinuar = false;
        sRespuesta->iDevStatus = E00001_ERROR_QUERY;
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","ERROR AL EJECUTAR EL QUERY EN LA gndominio");
        logx( sRespuesta->cDevMensaje, _LOGINFO_ );
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL CONSULTAR LA gndominio, ERROR:[%.150s]", tasaInteresPrestamos.error() );
        logx( sRespuesta->cMensaje, _LOGINFO_ );
        sRespuesta->status = _ERROR_DE_SERVIDOR;
    }
    return bContinuar;
}

void Cwsprestamos00028::consultarImportePrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta) {
    char cURL_[128] = {0}, cTexto[128] = {0}, cLog[512] = {0},Mensaje[150] = {0},cMensaje[300]={0};
    int iJson_ = SOAP_ERR, lRecibo=0, iMontoMinimoPrestamo=0, iTasaInteresPrestamos=0, iRespuestaExample = 0, lMontoMaximoPrestar = 0;
    bool bContinuar=true;
    double dIntSobre = 0; 
    long lFacturaAntCentral = 0, lSaldoAntCentral = 0, lSaldoFecha = 0, lImporte = 0;
    iRespuesta = _ERROR_QUERY_;

    char cDNS[100] = {'\0'}, cUser[100] = {'\0'}, cBd[100] = {'\0'}, cPss[200] = {'\0'}, cTiendaNumero[100] = {'\0'};
    C_ODBC odbcTiendaNumero, odbcCartera;

    iRespuesta = consultarSEC(_SEC_CARTERA, cDNS, cUser, cBd, cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
    iRespuesta = abrirConexion2( &odbcCartera, cDNS, cBd, cUser, cPss );
    if (iRespuesta != _OK_)
    {
        logx("No se logro establecer conexión con el SEC - Cwsprestamos00028::consumirWebserviceParametrico", _LOGINFO_);
        bContinuar=false;
    }

    if(bContinuar) {
        obtenerClaveSEC(sSolicitud->iNumTienda, cTiendaNumero, _SEC_TIENDANUMERO);
        iRespuesta = consultarSEC(cTiendaNumero, cDNS,  cUser,  cBd,  cPss, sSolicitud->iTiendaLocal, sSolicitud->iNumTienda);
        lImporte = sSolicitud->lImporte;

        if( iRespuesta == _OK_ )
        {
            iRespuesta = abrirConexion2( &odbcTiendaNumero, cDNS, cBd, cUser, cPss );
        }
        else
        {
            logx("No se logro establecer conexión con el SEC - Cwsprestamos00001::wsAutentificaHuella", _LOGINFO_ );
        }
        sRespuesta->iDevStatus = iRespuesta;
        if( iRespuesta == _OK_ )
        {
            if(lImporte <= 0L){
                errorGenericoPrestamo(sRespuesta, cTexto, "Debe capturar el importe del préstamo");
            }else{
                if(obtenerMinimoPrestamo(&odbcTiendaNumero, iMontoMinimoPrestamo, sRespuesta) &&
                    obtenerTasaInteres(&odbcTiendaNumero, iTasaInteresPrestamos, sRespuesta) ) {
                    if(lImporte < iMontoMinimoPrestamo){
                        mysnprintf(cTexto, sizeof(cTexto)-1, "Importe incorrecto. Favor de Capturar una cantidad mayor o igual a %ld", iMontoMinimoPrestamo);
                        errorGenericoPrestamo(sRespuesta, cTexto, cTexto);
                    }else{
                        if((lImporte % 100) != 0){
                            mysnprintf(cTexto, sizeof(cTexto)-1, "Es necesario que el importe %ld capturado sea múltiplo de 100", lImporte);
                            errorGenericoPrestamo(sRespuesta, cTexto, cTexto);
                        }else {
                            dIntSobre = (double)iTasaInteresPrestamos / (double)10000;
                            obtenerAbonoYTotalAnualPrestamo(sSolicitud, sRespuesta, lImporte, dIntSobre);
                        }
                    }
                }
            }
        }
    } else {
        sRespuesta -> status = _ERROR_EN_MENSAJE;
        mysnprintf(cMensaje,254,"No se logro abrir conexion a la base de datos: %.32s en el servidor: %.16s con el usuario: %.32s", sSolicitud->cBD, sSolicitud->cIpBD, sSolicitud->cUsuario );
        sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        mysnprintf( sRespuesta->cDevMensaje,254,"%s", cMensaje );
    }
}

void Cwsprestamos00028::obtenerAbonoYTotalAnualPrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long  &lImporte, double &dIntSobre){
    char cURL_[128] = {0}, cTexto[128] = {0}, cLog[512] = {0},Mensaje[150] = {0},cMensaje[250]={0};
    int lInteresAdicionalAnt = 0, lAuxiliar = 0, lInteresFinanciamiento = 0, lMontoMaximoPrestar = 0, lImporteSeguroClub= 0, lAbonoMensual = 0, lImporteTotalFinanciado = 0;
    int lSaldoPrestamoAnt = 0, lSaldaConAnt = 0;

    lSaldoPrestamoAnt = sSolicitud->lSaldoPrestamo ? sSolicitud->lSaldoPrestamo : 0;
    lSaldaConAnt = sSolicitud->lSaldo ? sSolicitud->lSaldo : 0;
    lInteresAdicionalAnt = sSolicitud->lInteresAdicional ? sSolicitud->lInteresAdicional : 0;
    lMontoMaximoPrestar = sSolicitud->lMontoMaximoPrestar ? sSolicitud->lMontoMaximoPrestar : 0;
    lImporteSeguroClub = sSolicitud->lImporteSeguroClub ? sSolicitud->lImporteSeguroClub : 0;

    lAuxiliar = lSaldoPrestamoAnt - ( lSaldoPrestamoAnt - lSaldaConAnt ) + lInteresAdicionalAnt;
    lInteresFinanciamiento = (long)( (double)(lImporte + lAuxiliar) * dIntSobre);

    if(lImporte > lMontoMaximoPrestar){
        if(lMontoMaximoPrestar > 99){
            mysnprintf(cTexto, sizeof(cTexto)-1, "Monto máximo autorizado es de $%ld pesos", lMontoMaximoPrestar);
            errorGenericoPrestamo(sRespuesta, cTexto, cTexto);
        }else{
            mysnprintf(cTexto, sizeof(cTexto)-1, "El Monto Maximo a prestar es menor a 99 por eso se rechazo, lMontoMaximoPrestar: %ld", lMontoMaximoPrestar);
            errorGenericoPrestamo(sRespuesta, cTexto, cTexto);
        }
    }else {
        if(lImporte > 99){
            lImporteTotalFinanciado = lImporte + lInteresFinanciamiento + lAuxiliar + lImporteSeguroClub;

            if( ( ( lImporte + lAuxiliar + lInteresFinanciamiento + lImporteSeguroClub + lImporteSeguroClub )%12 ) != 0 )
            {
                lAbonoMensual = ( (lImporteTotalFinanciado/12)+1 );
            }
            else
            {
                lAbonoMensual = ( (lImporteTotalFinanciado/12)+1 );
            }
            sRespuesta->status = _MENSAJE_CORRECTO_;
            mysnprintf(sRespuesta->cMensaje, sizeof(sRespuesta->cMensaje) - 1, "%s", "Success");
            mysnprintf(sRespuesta->cDevMensaje, sizeof(sRespuesta->cDevMensaje) - 1, "%s", "Success Dev");
            sRespuesta->lAbonoMensual = lAbonoMensual;
            sRespuesta->lImporteTotalFinanciado = lImporteTotalFinanciado;
            sRespuesta->lInteresFinanciamiento = lInteresFinanciamiento;
        }

    }
}

void Cwsprestamos00028::errorGenericoPrestamo(sRespuestaServicio *sRespuesta, char *cDevMensaje, char *cMensaje){
    sRespuesta->iDevStatus = _ERROR_EN_MENSAJE;
    mysnprintf(sRespuesta->cDevMensaje, 255,"%s", cDevMensaje);
    logx( sRespuesta->cDevMensaje, _LOGINFO_ );
    mysnprintf(sRespuesta->cMensaje, 255, "%s",  cMensaje);
    logx( sRespuesta->cMensaje, _LOGINFO_ );
    sRespuesta->status = _ERROR_EN_MENSAJE;
}

bool Cwsprestamos00028::actualizarTdAutorizacionHuellas(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja ){
    char cSql[256] = {0}, cTexto[256] = {0};
	bool bConsulta = true;
	int iActualizo = 0;

	CRegistro xPasarTmpTdAutorizacionHuellas(odbcTiendaNumero);
    xPasarTmpTdAutorizacionHuellas.agregarCampoEntero("cngrabartdautorizacionhuellaspendientes", DT_ENTERO_LARGO);

    mysnprintf(cSql, sizeof(cSql)-1, "SELECT cngrabartdautorizacionhuellaspendientes(%d::smallint, %d::smallint);", sSolicitud->iCaja, 3);
    logx(cSql, _LOGINFO_);
	
    if(!xPasarTmpTdAutorizacionHuellas.Exec(cSql)) {
        mysnprintf(cTexto, 256, "OCURRRIO UN ERROR AL EJECUTAR LA FUNCION cngrabartdautorizacionhuellaspendientes, ERROR:[%.150s]", xPasarTmpTdAutorizacionHuellas.error());
        logx(cTexto, _LOGINFO_);
		bConsulta = false;
	} else {
		xPasarTmpTdAutorizacionHuellas.activarCols();
		if (xPasarTmpTdAutorizacionHuellas.Leer()) {
			iActualizo = (int)xPasarTmpTdAutorizacionHuellas.valorLong("cngrabartdautorizacionhuellaspendientes");
		}
    }

    //hr = StringCchPrintf( cSqlTxt,256, "SELECT grabarreconocimiento(%ld, '%s', '%.12s', %ld, '%s', %ld)", lCliente, sDni , cCuponTicket , iTotalRec , "C", iCaja  );
    mysnprintf(cSql, sizeof(cSql)-1, "SELECT grabarreconocimiento(%ld, '%s', '%.12s', %ld, '%s', %ld);",sSolicitud -> lCliente, sSolicitud -> sDni , datosCaja ->cReferenciaMsj , sSolicitud -> importetotalAnual , "C", sSolicitud ->iCaja );
    CRegistro reconocio( odbcTiendaNumero );
    reconocio.agregarCampoEntero("grabarreconocimiento", DT_ENTERO_LARGO);

    if( reconocio.Exec( cSql ) )
    {
        reconocio.activarCols();
        if( reconocio.Leer() )
        {
            bConsulta = true;
            sRespuesta -> iNumReconocimiento = reconocio.valorLong("grabarreconocimiento");
        }
    }
    else
    {
        mysnprintf(cTexto, 256, "OCURRRIO UN ERROR AL EJECUTAR LA FUNCION reconocio, ERROR:[%.150s]", reconocio.error());
        logx(cTexto, _LOGINFO_);
		bConsulta = false;
    }

	return bConsulta;
}

bool Cwsprestamos00028::grabarAutorizacionGerentes(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char cTipo) 
{   
    bool bContinuar = true;
    char cSql[400] = {0};
    int iActualizo = 0;
    logx("entro a grabarAutorizacionGerentes", _LOGINFO_);
    mysnprintf(cSql, sizeof(cSql)-1,"SELECT tdautorizacionhuellas(%d::smallint, %d::smallint, %d::smallint, '%c'::character, %d, %d,'%c'::character, %d, %d);",sSolicitud->iCaja, 3, 0, cTipo, sSolicitud->lCliente, sSolicitud->lEmpleado, '0', sRespuesta->lRecibo, 0);
    logx(cSql, _LOGINFO_);
    CRegistro tdAutorizacionHuellas(odbcTiendaNumero);
    tdAutorizacionHuellas.agregarCampoEntero("tdautorizacionhuellas", DT_ENTERO_LARGO);

    if (!tdAutorizacionHuellas.Exec(cSql)) {
        mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL EJECUTAR LA FUNCION tdautorizacionhuellas, ERROR:[%.150s]", tdAutorizacionHuellas.error() );
        logx(sRespuesta->cMensaje, _LOGINFO_);
        bContinuar = false;
    } else {
		tdAutorizacionHuellas.activarCols();
		if (tdAutorizacionHuellas.Leer()) {
			iActualizo = (int)tdAutorizacionHuellas.valorLong("tdautorizacionhuellas");
		}
    }
	return bContinuar;
}

/*bool Cwsprestamos00028::grabarPAJLocal2(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta)
{
    char cNombreTabla[50]={0}, cTexto[64] = {0}, cTexto2[64] = {0}, cLog[500] = {0};
    const char *cTexto3 = NULL;
    int iFlagBonificacion = 0, iDia = 1, iMes = 1, iYear = 1900;
    bool bRespuesta = false;
    bool bRegresa = false;
    //CString sTexto;
    
    CRegistro inTmpPaj( odbcTiendaNumero, false);
    SqlTimeStamp tFecha;
    
    inTmpPaj.agregarCampoChar("PAJ_FILIAL", DT_CHAR);
    inTmpPaj.agregarCampoFecha("PAJ_DATA");
    inTmpPaj.agregarCampoEntero("PAJ_MOEDA", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_NATURE", DT_CHAR);
    inTmpPaj.agregarCampoEntero("PAJ_VALOR", DT_ENTERO);
    
    inTmpPaj.agregarCampoChar("PAJ_BANCO", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_AGENCI", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_CONTA", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_DOCUME", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_RECPAG", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_BENEF", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_HISTOR", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_TIPODO", DT_CHAR);
    inTmpPaj.agregarCampoEntero("PAJ_TXMOED", DT_ENTERO);
    inTmpPaj.agregarCampoChar("PAJ_RATEIO", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_FILORI", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_NUMCHE", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_DEBITO", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_CCD", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_CCC", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_CREDIT", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_DTGRV", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_HRGRV", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_TIPOPE", DT_CHAR);
    inTmpPaj.agregarCampoChar("PAJ_GRPTRA", DT_CHAR);

    mysnprintf(cNombreTabla, 100, "PAJ%.2s0", sSolicitud->cEmpresa);
    inTmpPaj.activarCols();
    inTmpPaj.prepararInsert(cNombreTabla);
    
    inTmpPaj.valorChar( "PAJ_FILIAL", sSolicitud->cFilial);

    mysnprintf(cTexto, 100, "%.17s", sSolicitud->cData);
    iYear = valorCampo( cTexto, 4 );
    iMes = valorCampo( &cTexto[5], 2 );
    iDia = valorCampo( &cTexto[8], 2 );
    tFecha.ponerFecha( iDia, iMes, iYear );
    inTmpPaj.valorFecha("PAJ_DATA", sSolicitud->fechaSinFormato);

    inTmpPaj.valorShort("PAJ_MOEDA", (short)sSolicitud->sMoneda);
    inTmpPaj.valorShort("PAJ_VALOR", (short)sSolicitud->sValor);
    inTmpPaj.valorChar("PAJ_NATURE", sSolicitud->cNaturez);
    inTmpPaj.valorChar("PAJ_BANCO", sSolicitud->cBanco);
    inTmpPaj.valorChar("PAJ_AGENCI", sSolicitud->cAgencia);
    inTmpPaj.valorChar("PAJ_CONTA", sSolicitud->cCuenta);
    inTmpPaj.valorChar("PAJ_DOCUME", sSolicitud->cDocumento);

    const char PAJ_RECPAG[];
    PAJ_RECPAG[0] = sSolicitud->cRecPag;
    PAJ_RECPAG[1] = 0;
    inTmpPaj.valorChar("PAJ_RECPAG", sSolicitud->cRecPag);

    inTmpPaj.valorChar("PAJ_BENEF", sSolicitud->cBeneficiario);
    //sTexto.Format( "%s", sSolicitud->cParametros );
    //mysnprintf(sTexto, 100, "%s", sSolicitud->cParametros);
    //const char sTexto[60]
    cTexto3 = sSolicitud->cParametros;
    std::string str(cTexto3);
    str.substr(2, 8);
    char* c = const_cast<char*>(str.c_str());
    //const char* char_array = str.c_str();
    //str::string sTexto = sSolicitud->cParametros;
    //sTexto.Format("%s", sSolicitud->cHistor);
    mysnprintf(cTexto, 100, "Reembolso a %s", c);
    inTmpPaj.valorChar("PAJ_HISTOR", cTexto);
    
    inTmpPaj.valorChar("PAJ_TIPODO", sSolicitud->cTipodoc);
    inTmpPaj.valorDouble("PAJ_TXMOED", (double)sSolicitud->cTxmoneda);

    /*const char *PAJ_RATEIO[];
    PAJ_RATEIO[0] = sSolicitud->cRateio;
    PAJ_RATEIO[1] = 0;
    inTmpPaj.valorChar("PAJ_RATEIO", sSolicitud->cRateio);

    inTmpPaj.valorChar("PAJ_FILORI", sSolicitud->cFilori);
    inTmpPaj.valorChar("PAJ_NUMCHE", sSolicitud->cNumche);
    inTmpPaj.valorChar("PAJ_DEBITO", sSolicitud->cDebito);
    inTmpPaj.valorChar("PAJ_CREDIT", sSolicitud->cCredit);
    inTmpPaj.valorChar("PAJ_CCD", sSolicitud->cCd);
    inTmpPaj.valorChar("PAJ_CCC", sSolicitud->cCc);
    inTmpPaj.valorChar("PAJ_DTGRV", sSolicitud->cDtgrv);
    inTmpPaj.valorChar("PAJ_HRGRV", sSolicitud->cHrgrv);

    /*const char *PAJ_TIPOPE[] = NULL;
    PAJ_TIPOPE[0] = sSolicitud->cTipope;
    PAJ_TIPOPE[1] = 0;
    inTmpPaj.valorChar("PAJ_TIPOPE", sSolicitud->cTipope);

    inTmpPaj.valorChar("PAJ_GRPTRA",  sSolicitud->cGrptra);

    if (inTmpPaj.Insert())
    {
        if (inTmpPaj.Commit())
        {
            bRespuesta = true;
        }
        else
        {
            mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
            mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
            sRespuesta->status = _ERROR_EN_MENSAJE;
            sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
        }
    }
    else
    {
        mysnprintf(sRespuesta->cDevMensaje, 255,"%s", "ERROR AL GUARDAR EL MOVIMIENTO EN LA TABLA tmpcacarmov"); 
        mysnprintf(sRespuesta->cMensaje, 255,"%s", "OCURRRIO UN ERROR EN EL SERVIDOR"); 
        sRespuesta->status = _ERROR_EN_MENSAJE;
        sRespuesta->iDevStatus = _ERROR_DE_CONEXION_BD_;
    }

    return bRespuesta;
}
*/
bool Cwsprestamos00028::llenarEstructura(C_ODBC *odbcTiendaNumero,InfoFE *infoFE,  sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud, int iTipoComprobante)
{
	char cLog[80]={0};
	bool bRegresa = false;
	int iTipoID = -1, iAnio=-1;
    //int iTipoComprobante = 6;
	//HRESULT hr = 0;
	
		//infoFE->iOpcion = 1;
	//	infoFE->iTienda = sSolicitud ->iNumTienda;
		//consultarFechaFE( infoFE->cComprobanteFecha );
      //  mysnprintf(infoFE->cComprobanteFecha, 16, "%s", sSolicitud ->lFecha);
		//sprintf( infoFE->cComprobanteFecha, "%04d-%02d-%02d", iAnio, tFecha.GetMonth(), tFecha.GetDay() );
		//consultarFlagHasar( ); ES PARA SABER SI ES IMPRESORA HASAR
        //mysnprintf(infoFE->cIpImpresoraHassar, 17, "%s", sSolicitud -> cIPwshasar);
		//hr = StringCchPrintf( infoFE->cIpImpresoraHassar,17, "%.17s",sSolicitud -> cIpImpresoraHasar );
	//	hr = StringCchPrintf(cLog ,80,"Ip Envia FE:: %s", infoFE->cIpImpresoraHassar );
      //  mysnprintf(cLog ,80,"Ip Envia FE:: %s", infoFE->cIPwshasar);

		logx(cLog,_LOGINFO_);
        mysnprintf(infoFE->cTipoComprobante, 17, "%ld", iTipoComprobante);
		//infoFE->cTipoComprobante = iTipoComprobante; //6 "Factura B" -- 8: "Nota de credito B"
		bRegresa = obtenerUltimoNroDocumento( odbcTiendaNumero,infoFE,sSolicitud, 1 );
		bRegresa = obtenerUltimoNroDocumento( odbcTiendaNumero,infoFE,sSolicitud, 0 );

		
		//infoFE->i64NroTransaccion = sSolicitud -> i64NroDocumentoFE;
		//infoFE->i64NroTransaccionConfirmado = sSolicitud -> i64NroDocumentoFEAnterior;


		infoFE->lNroOperacion = 0 ; // default

		//bRegresa = obtenerTipoIdentificacion( infoFE->iTipoDocumento );
		
		infoFE->dImporteNetoNoGravado = 0; // fijo

         mysnprintf(infoFE->cDocumentoNro, 17, "%s", sSolicitud -> sDni);
		//infoFE->cDocumentoNro =  sSolicitud -> sDni; // Nro DNI
		
		if( iTipoComprobante == 6 )
		{
			infoFE->dImporteTotal = (double)(sSolicitud -> lInteresFinanciamiento );
			bRegresa = obtenerIVAPrestamo( odbcTiendaNumero,sSolicitud ,sRespuesta,iTipoComprobante );
			
			/*infoFE->lImporteTotal = lTotalBonificacion * 100;
			bRegresa = obtenerIVAPrestamo(odbcTiendaNumero,sSolicitud  );*/
			
		}
		else if( iTipoComprobante == 8 )
		{
			infoFE->dImporteTotal =(double)(sRespuesta ->lTotalBonificacion );
			bRegresa = obtenerIVAPrestamo(odbcTiendaNumero,sSolicitud ,sRespuesta,iTipoComprobante );
		}
		 mysnprintf(cLog, 256, "lImportePrestamoSinIva :%ld, lIvaPrestamo:%ld ", sRespuesta -> lImportePrestamoSinIva, sRespuesta ->lIvaPrestamo);
        logx(cLog,_LOGINFO_);
		infoFE->dImporteNeto = (double) sRespuesta -> lImportePrestamoSinIva /100;
		infoFE->dImporteExcento = 0;
		infoFE->dImporteTributo = 0;
		infoFE->dImporteIVA =(double) sRespuesta ->lIvaPrestamo/100;
        mysnprintf(cLog, 256, "lImportePrestamoSinIva :%f, lIvaPrestamo:%f", infoFE->dImporteNeto, infoFE->dImporteIVA);
        logx(cLog,_LOGINFO_);
	//	infoFE->iSucursal = sSolicitud -> iNumTienda;
		//infoFE->iCaja = sSolicitud ->iCaja;

		if( sSolicitud -> lPorcentajeIva == 0 )
		{
			infoFE->dBaseImponible3 = (double)sSolicitud -> lImporte; // el iva del 0 y 5% va fijo en 0 por que los prestamos son con iva del 21
			infoFE->dImporte3 = 0;
            mysnprintf(infoFE->cTipoIVA3, 2, "%ld", 3);

			//infoFE->cTipoIVA3 = 3;// indica que es el iva del 0%
		}
		else if ( sSolicitud -> lPorcentajeIva == 105 )
		{		
			infoFE->dBaseImponible3 =(double) sRespuesta -> lImportePrestamoSinIva/100;
			infoFE->dImporte3 = (double)sRespuesta ->lIvaPrestamo/100;
            mysnprintf(infoFE->cTipoIVA3, 2, "%ld", 4);

			//infoFE->cTipoIVA3 = 4;// indica que es el iva del 10.5%
		}
		else if ( sSolicitud -> lPorcentajeIva == 2100 )
		{		
			infoFE->dBaseImponible3 = (double)sRespuesta -> lImportePrestamoSinIva/100;
			infoFE->dImporte3 =(double) sRespuesta ->lIvaPrestamo/100;
            mysnprintf(infoFE->cTipoIVA3, 2, "%ld", 5);

		//	infoFE->cTipoIVA3 = 5; // indica que es el iva del 21%
		}

	return bRegresa;
}
bool Cwsprestamos00028::obtenerUltimoNroDocumento(C_ODBC *odbcTiendaNumero,InfoFE *infoFE,sSolicitudServicio *sSolicitud, int iTipoConsulta )// 0 consulta - 1 incrementa
{
	bool bRegresa = false;
	char cSql[180]={0};
	//HRESULT hr = 0;

	CRegistro consultaNumero( odbcTiendaNumero );
	//hr = StringCchPrintf(cSql,180,"select gnverificarultimatransaccionfe  as total from gnverificarultimatransaccionfe('%d', '3','%d', '%d')", iTienda,iCaja, iTipoConsulta );
    mysnprintf(cSql, 180, "select gnverificarultimatransaccionfe  from gnverificarultimatransaccionfe('%d', '3','%d', '%d')", sSolicitud ->iNumTienda,sSolicitud -> iCaja,iTipoConsulta);
    consultaNumero.agregarCampoEntero("gnverificarultimatransaccionfe",DT_ENTERO_LARGO);
    //.agregarCampoEntero( "nroTransaccion", DT_ENTERO_LARGO );
    logx(cSql,_LOGINFO_);
	if( consultaNumero.Exec(cSql))
	{
		consultaNumero.activarCols();
		if(consultaNumero.Leer())
		{
			if( iTipoConsulta == 1 )
			{
				infoFE->iNroTransaccion = consultaNumero.valorInt64("gnverificarultimatransaccionfe");
			}
			else if( iTipoConsulta == 0 )
			{
				infoFE->iNroTransaccionConfirmado = consultaNumero.valorInt64("gnverificarultimatransaccionfe");
			}
			mysnprintf(cSql, 180, "iNroTransaccion :'%d',iNroTransaccionConfirmado'%d'", infoFE->iNroTransaccion,infoFE->iNroTransaccionConfirmado );
            logx(cSql,_LOGINFO_);

			bRegresa = true;
		}
	}
	else
	{
        logx("error al sacar ultimatrasnaccionFE",_LOGINFO_);
		//consultaNumero.odbc->GetLastError( consultaNumero.GetHstmt() );
		//grabarMensajeError( 'C', iCaja, (LPTSTR)(LPCTSTR)sServer, "CA0052.DLL", "CDlgCapturarPrestamos", "obtenerUltimoNroDocumento" ,cSql,lEmpleado ,"ERROR #2021", consultaNumero.odbc, iMuestraMsg );
	}
	return bRegresa ;
}

bool Cwsprestamos00028::obtenerIVAPrestamo(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, int iTipoComprobante )
{
	char cSql[180] = {0};
	bool bRespuesta = false;
	//HRESULT hr = 0;
	CRegistro obtenerIvaPrestamo( odbcTiendaNumero );
    //CRegistro obtenerlPorcentajeIva( odbcTiendaNumero );

    //mysnprintf(cSql, 180, "select lIvaPrestamo, lImportePrestamoSinIva from caObtenerIVAPrestamo( %ld, %ld );", sSolicitud ->lImportePrestamo,sSolicitud -> lPorcentajeIva);
    if(obtenerIvaImpuestoInterno( odbcTiendaNumero, sRespuesta, sSolicitud )) {
            //hr = StringCchPrintf(cSql,180,"select lIvaPrestamo, lImportePrestamoSinIva from caObtenerIVAPrestamo( %ld, %ld ) ", lImportePrestamo, lPorcentajeIva );
        if(iTipoComprobante ==  6)
        {
            mysnprintf(cSql, 180, "select lIvaPrestamo, lImportePrestamoSinIva from caObtenerIVAPrestamo( %ld, %ld );",sSolicitud -> lInteresFinanciamiento, sSolicitud -> lPorcentajeIva);
        }
        else if (iTipoComprobante == 8)
        {
            mysnprintf(cSql, 180, "select lIvaPrestamo, lImportePrestamoSinIva from caObtenerIVAPrestamo( %ld, %ld );",  sRespuesta ->lTotalBonificacion,sSolicitud -> lPorcentajeIva);
        }
        obtenerIvaPrestamo.agregarCampoEntero("lIvaPrestamo",DT_ENTERO_LARGO);
        obtenerIvaPrestamo.agregarCampoEntero("lImportePrestamoSinIva",DT_ENTERO_LARGO);
        logx(cSql,_LOGINFO_);
        if( obtenerIvaPrestamo.Exec(cSql))
        {
            obtenerIvaPrestamo.activarCols();
            if(obtenerIvaPrestamo.Leer())
            {
                sRespuesta -> lImportePrestamoSinIva = obtenerIvaPrestamo.valorLong("lImportePrestamoSinIva");
                sRespuesta -> lIvaPrestamo = obtenerIvaPrestamo.valorLong("lIvaPrestamo");
                bRespuesta = true;
            }
        }
        else
        {
            //obtenerIvaPrestamo.odbc->GetLastError( obtenerIvaPrestamo.GetHstmt() );
          //  grabarMensajeError( 'C', iCaja, (LPTSTR)(LPCTSTR)sServer, "CA0052.DLL", "CDlgCapturarPrestamos", "obtenerIVAPrestamo" ,cSql,lEmpleado ,"ERROR #2023", obtenerIvaPrestamo.odbc, iMuestraMsg );
        }
    }
	return bRespuesta;
}
bool Cwsprestamos00028::obtenerIvaImpuestoInterno( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud)
{
	char cSql[512] = {0};
	bool bRegresa = false;
	//HRESULT hr = 0;


	CRegistro consultarivaimpuesto( odbcTiendaNumero,false );
	//hr = StringCchPrintf( cSql,512, "SELECT ivaRegresa,impuestoInternoRegresa FROM caobtenerivaimpuestointerno()"  );
    mysnprintf(cSql, 180, "SELECT ivaRegresa,impuestoInternoRegresa FROM caobtenerivaimpuestointerno()","");
    consultarivaimpuesto.agregarCampoEntero("ivaRegresa",DT_ENTERO_LARGO);
    consultarivaimpuesto.agregarCampoEntero("impuestoInternoRegresa",DT_ENTERO_LARGO);

	if( consultarivaimpuesto.Exec( cSql ) )
	{
		consultarivaimpuesto.activarCols();
		if( consultarivaimpuesto.leer() )
		{
			sSolicitud -> lPorcentajeIva = consultarivaimpuesto.valorLong("ivaRegresa");
			sSolicitud -> lmpuestointerno = consultarivaimpuesto.valorLong("impuestoInternoRegresa");
			bRegresa = true;
		}
	}
	else
	{
		bRegresa = false;
		//consultarivaimpuesto.odbc->GetLastError( consultarivaimpuesto.GetHstmt() );
		//grabarMensajeError( 'c', 0, "0", "CAOO52", "obtenerIvaImpuestoInterno", "obtenerIvaImpuestoInterno", (LPTSTR)(LPCTSTR)cSql, 0, "Error #7001 obtenerIvaImpuestoInterno", consultarivaimpuesto.odbc, 1 );
	}
	return bRegresa;
}
int Cwsprestamos00028::generarFacturaElectronica( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja )
{    
    char cTexto[128] = {0}, cTextoTmp[128] = {0}, cURL[128] = {0};
    char cLog[512] = {0};
    int iJson = SOAP_ERR,iYear=1900,iMes=1,iDia=1;
    int iRespuesta = _ERROR_QUERY_;
    int  iContIva = 0;
    char cUsuarioBD[20] = {0}, cPassBD[60] = {0}, cNombreBD[20] = {0}, cIpServidor[20] = {0}, cFecha[16] = {0};
    
    if(llenarEstructura( odbcTiendaNumero,infoFE, sRespuesta, sSolicitud,6) && actualizarInteresPrestamos(odbcTiendaNumero,  sSolicitud,  sRespuesta,  datosCaja)){

        soap *soapFE = soap_new1( SOAP_C_UTFSTRING );
        value vSolicitudJson( soapFE );
        value vRespuestaJson( soapFE );

        soapFE->double_format = "%.2lf";     
        mysnprintf( cURL,128, "http://%.16s:8078/api/comprobantes/creaComprobante",  sSolicitud -> cIPwshasar );
        //logx( cURL );
        mysnprintf( cTexto,128, "%.16s",  sSolicitud -> cIPwshasar );
        //logx( cTexto, _LOGINFO_  );
        //logx( "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*", _LOGINFO_ );

        mysnprintf( cTexto, 128, "%.15s",sSolicitud ->fechaSinFormato );
        iYear = valorCampo(cTexto, 4);
        iMes= valorCampo(&cTexto[4], 2);
        iDia= valorCampo(&cTexto[6], 2);
        mysnprintf(cTextoTmp, 14, "%04d-%02d-%02d", iYear, iMes, iDia);
       // logx(cFecha, _LOGINFO_);
       /// mysnprintf( cTextoTmp, 128, "%04ld-%02ld-%02ld", valorCampo( cTexto, 4 ), valorCampo( &cTexto[4], 2 ), valorCampo( &cTexto[6], 2 ) );
        logx(cTextoTmp,_LOGINFO_);
        vSolicitudJson["comprobanteFecha"]          = cTextoTmp;
        vSolicitudJson["tipoComprobante"]           = infoFE->cTipoComprobante;
        vSolicitudJson["nroTransaccion"]            =  infoFE->iNroTransaccion;
        vSolicitudJson["nroTransaccionConfirmado"]  =  infoFE->iNroTransaccionConfirmado;
        vSolicitudJson["nroOperacion"]              = (long long int)(0);
        vSolicitudJson["tipoDocumento"]             = sSolicitud -> iTipoID;
        vSolicitudJson["documentoNro"]              = sSolicitud -> sDni;
        mysnprintf( cTexto, 128, "El dni de fe %s", sSolicitud -> sDni);
        logx( cTexto , _LOGINFO_ );
        vSolicitudJson["importeTotal"]              = infoFE->dImporteTotal;
        vSolicitudJson["importeNetoNoGravado"]      = infoFE->dImporteNetoNoGravado;
        vSolicitudJson["importeNeto"]               = infoFE->dImporteNeto ;
        vSolicitudJson["importeExcento"]            = 0;
        vSolicitudJson["importeTributo"]            = 0;
        vSolicitudJson["importeIVA"]                = infoFE->dImporteIVA ;
        vSolicitudJson["sucursal"]               	= (int)sSolicitud->iNumTienda;
        //vSolicitudJson["sucursal"]               	= (int)1;
        vSolicitudJson["caja"]               		= (int)sSolicitud->iNumCaja;

        if (sSolicitud->iSecModo == 2)
        {
            vSolicitudJson["sucursal"]              = (int)1;
        }                     		                          
        vSolicitudJson["alicuotas"][0]["baseImponible"]   = infoFE->dBaseImponible3;
        vSolicitudJson["alicuotas"][0]["importe"]         = infoFE->dImporte3;
        vSolicitudJson["alicuotas"][0]["tipoIVA"]         = infoFE->cTipoIVA3;        
        logx( "----------------------------------------3", _LOGINFO_  );
      

        
        if( infoFE->lNumeroComprobanteAs > 0 )
        {
            vSolicitudJson["comprobantesAsociados"][0]["numeroComprobante"]     = infoFE->cTipoComprobanteAs;
            vSolicitudJson["comprobantesAsociados"][0]["puntoVentaId"]          = (long long int)infoFE->lPuntoVentaIdAs;
            vSolicitudJson["comprobantesAsociados"][0]["numeroComprobante"]     = (long long int)infoFE->lNumeroComprobanteAs;
            logx( "----------------------------------------6", _LOGINFO_  );
        }
        mysnprintf( cTexto, 128, "El tipo de fe %s", infoFE->cTipoDocumento );
        logx( cTexto , _LOGINFO_ );
        mysnprintf( cTexto, 128, "El dni de fe %d", infoFE->cDocumentoNro);
        logx( cTexto , _LOGINFO_ );
        logx( "Conectando a WS de FE....", _LOGINFO_  );
        displayJson( &vSolicitudJson );

        if (sSolicitud->iSecModo == 1) //productivo
        {
            iJson = json_call( soapFE, cURL, &vSolicitudJson, &vRespuestaJson );
        
            mysnprintf( cTexto, 128, "Respuesta de WS %d", iJson );
            logx( cTexto , _LOGINFO_ );
            displayJson( &vRespuestaJson );      

            if( iJson == SOAP_OK )
            {
                if( vRespuestaJson.has("resultado") )
                {
                    if( strcmp( (char *)vRespuestaJson["resultado"], "A" ) == 0 )
                    {
                        iRespuesta = _OK_;

                        sRespuesta->infoGrabarPrestamo.iNroTransaccion = vRespuestaJson["nroTransaccion"];
                        mysnprintf( sRespuesta->infoGrabarPrestamo.cTipoComprobante,3, "%.2s", (char *)vRespuestaJson["tipoComprobante"] );
                        mysnprintf( sRespuesta->infoGrabarPrestamo.cResultado,3, "%.2s", (char *)vRespuestaJson["resultado"] );
                        
                        if( mystrnlen( (char *)vRespuestaJson["cae"] ) > 0 ) 
                        {
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%s", "CAE" );                    
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", (char *)vRespuestaJson["cae"] );
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cCaeFechaVto,11, "%.10s", (char *)vRespuestaJson["caeFechaVto"] );
                        }
                        else
                        {
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", (char *)vRespuestaJson["caea"] );
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%s", "CAEA" );
                        }

                        mysnprintf( sRespuesta->infoGrabarPrestamo.cFechaProceso,50, "%.25s", (char *)vRespuestaJson["fechaProceso"] );  

                        mysnprintf( cTexto,128, "%04d%08ld", (int)vRespuestaJson["puntoVenta"], (long)(long long int)vRespuestaJson["numeroComprobante"] );
                        mysnprintf( sRespuesta->infoGrabarPrestamo.cCuponFiscal,14, "%.13s", cTexto );
                        mysnprintf( sRespuesta->infoGrabarPrestamo.cPDV,6, "%04d", (int)vRespuestaJson["puntoVenta"] );
                    }
                    else
                    {
                        sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                        mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");
                        sRespuesta->iErrorDirectorio = 96000035;

                        sRespuesta->iDevStatus = _ERROR_HTTP_;
                        mysnprintf(sRespuesta->cDevMensaje,255,"LA RESPUESTA DEL WS PARA LA FE NO ES LA ESPERADA: %.200s", (char *)vRespuestaJson["resultado"] );
                        logx(sRespuesta->cDevMensaje, _LOGINFO_ ); 
                    }
                }
                else
                {
                    sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                    mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");
                    sRespuesta->iErrorDirectorio = 96000033;

                    sRespuesta->iDevStatus = _ERROR_HTTP_;
                    mysnprintf(sRespuesta->cDevMensaje, 255,"%s","LA RESPUESTA DEL WS NO TRAE EL CAMPO resultado" );
                    logx(sRespuesta->cDevMensaje, _LOGINFO_ ); 
                }
            }
            else
            {             
                sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");

                soapError( soapFE, cLog );
                sRespuesta->iErrorDirectorio = 96000034;

                sRespuesta->iDevStatus = _ERROR_HTTP_;
                mysnprintf(sRespuesta->cDevMensaje, 255,"ERROR AL CONSUMIR EL WEBSERVICE DE FE. [%.200s]", cLog );
                logx(sRespuesta->cDevMensaje, _LOGINFO_ );
                
                //soap_print_fault( soapFE, stderr );        
            }

            soap_destroy(soapFE);
            soap_end(soapFE);
            soap_free(soapFE);
        }
        else //desarrollo
        {
            iRespuesta = _OK_;
            sRespuesta->infoGrabarPrestamo.iNroTransaccion = infoFE->iNroTransaccion;
            mysnprintf( sRespuesta->infoGrabarPrestamo.cTipoComprobante,3, "%.2s", "06");
            mysnprintf( sRespuesta->infoGrabarPrestamo.cResultado,3, "%.2s", "0A" );
            mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", "3045219873706" );
            mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%.4s" , "CAEA" );
            mysnprintf( sRespuesta->infoGrabarPrestamo.cFechaProceso,50, "%.48s", "2020-11-10T15:30:17.976-07:00[America/Chihuahua]" ); 
            mysnprintf( cTexto,127, "%04d%08lld", 8102, infoFE->iNroTransaccion );
            mysnprintf( sRespuesta->infoGrabarPrestamo.cCuponFiscal,14, "%s", cTexto );
            // sprintf( sRespuesta->infoGrabarPrestamo.cPDV, "%04d", (int)vRespuestaJson["puntoVenta"] );
            mysnprintf( sRespuesta->infoGrabarPrestamo.cPDV,6, "0000" ,0);
            logx("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",_LOGINFO_);
            logx(sRespuesta->infoGrabarPrestamo.cFechaProceso,_LOGINFO_);
            if (strcmp(sRespuesta->infoGrabarPrestamo.cFechaProceso, "2020-11-10T15:30:17.976-07:00[America/Chihuahua]") == 0)
            {
                sRespuesta->iFeActiva = 0;
            }
            else
            {
                sRespuesta->iFeActiva = 1;
            }
        }
    }
    
    return iRespuesta;
}

bool Cwsprestamos00028::actualizarCrprestamosFE(C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta) {
	char cSql[128] = {0}, cFecha[14] = {0};
    bool bContinuar = true;
    int iActualizo = 0, iDia = 1, iMes = 1, iYear = 1900;
    SqlTimeStamp tFecha;
	CRegistro actualizarFE(odbcCartera);

    mysnprintf(cFecha, 14, "%.12s", sSolicitud->fechaSinFormato);
    iYear = valorCampo(cFecha, 4);
    iMes= valorCampo(&cFecha[4], 2);
    iDia= valorCampo(&cFecha[6], 2);
    tFecha.ponerFecha(iDia, iMes, iYear);

    mysnprintf(cFecha, 14, "%04d-%02d-%02d", iYear, iMes, iDia);
    logx(cFecha, _LOGINFO_);
	mysnprintf(cSql, 128, "select tdActualizarCuponFE(%d,'%.12s','%.12s',%d)", sSolicitud->lCliente, &tFecha, sRespuesta->infoGrabarPrestamo.cCuponFiscal, sRespuesta->lRecibo);
	logx(cSql, _LOGINFO_);

    actualizarFE.agregarCampoEntero("tdActualizarCuponFE", DT_ENTERO_LARGO);
	if(!actualizarFE.Exec(cSql)) {
		mysnprintf(sRespuesta->cMensaje, 255, "OCURRRIO UN ERROR AL EJECUTAR LA FUNCION tdActualizarCuponFE, ERROR:[%.150s]", actualizarFE.error() );
        logx(sRespuesta->cMensaje, _LOGINFO_);
        bContinuar = false;
	} else {
        actualizarFE.activarCols();
		if (actualizarFE.Leer()) {
			iActualizo = (int)actualizarFE.valorLong("tdActualizarCuponFE");
		}
    }
	return bContinuar;
}

void soapError( struct soap *pSoap, char *cError )
{
    if (soap_check_state(pSoap ))
    {
        mysnprintf( cError,35, "%.35s", "Error: soap struct not initialized" );
    }
    else
    {
        if (pSoap->error)
        { 
            const char *pFaultCode = NULL, *pFaultSubCode = NULL, *pFalutString = NULL, **iFaultCode = NULL;
            iFaultCode = soap_faultcode(pSoap );
            if (!*iFaultCode)
                soap_set_fault(pSoap );
            pFaultCode = *iFaultCode;
            if (pSoap->version == 2)
                pFaultSubCode = *soap_faultsubcode(pSoap );
            pFalutString = *soap_faultstring(pSoap );
            iFaultCode = soap_faultdetail(pSoap );

            mysnprintf( cError,255, "%.8s%d fault: %.64s [%.64s]%.64s Detail: %.64s", pSoap->version ? "SOAP 1." : "Error ", pSoap->version ? (int)pSoap->version : pSoap->error, 
            pFaultCode, pFaultSubCode ? pFaultSubCode : "no subcode", pFalutString ? pFalutString : "[no reason]", iFaultCode && *iFaultCode ? *iFaultCode : "[no detail]" );
    }   
        }
}

bool Cwsprestamos00028::obtenerCuponTicket(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja ){
	char cSql[200] = {0},cBufferMensaje[256] = {0} ;
	bool bRegresa = true;
	int iCupon = -1;
	//HRESULT hr = 0;

	//mymemset( &datosCaja ,0, sizeof( datosCaja ) );
	//mymemset( &cCuponRePrestamoNcc, 0, sizeof( cCuponRePrestamoNcc ) );
    //mymemset( cCuponTicket, 0, sizeof(cCuponTicket) );
    //mymemset( cCuponNcc, 0, sizeof(cCuponNcc) );

    datosCaja ->iTienda = sSolicitud -> iNumTienda;
    mysnprintf( datosCaja ->cArea,3, "%.3s", "C" );
    datosCaja ->iCaja =sSolicitud-> iCaja;
    mysnprintf( datosCaja ->cIp,17, "%.15s", sSolicitud->cIpCarteraCliente );
    datosCaja ->lEmpleado = sSolicitud -> lEmpleado;
    datosCaja ->iMostrarError = 1;
    mysnprintf( datosCaja ->cEsperarMotor,17, "%.15s", "N" );
    datosCaja ->iClaveMsj = 38;//MOTOR_FACTURA_MANUAL

    if( gnObtenerDatosCaja( odbcTiendaNumero,sSolicitud,sRespuesta,datosCaja))
    {
        //hr = StringCchPrintf( cGpoTransaccion,15, "%.13s", datosCaja ->cReferenciaMsj );
        bRegresa = true;
    }
    else
    {
        bRegresa= false;
    }		
	
	return bRegresa;
}
bool Cwsprestamos00028::gnObtenerDatosCaja( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja)
{
	bool bRegresa = false;
	char cIpProtheus[18] = {0}, cIpProtheusAlterno[18] = {0}, cSql[512] = {0}, cFilial[4] = {0}, cEmpresa[4] = {0}, cBDProtheus[27] = {0};
	long lFolioReferencia = 0L;
	int iRespuesta = 0;

	CRegistro xGenerales( odbcTiendaNumero, false );
    xGenerales.agregarCampoChar("filial", 2);
    xGenerales.agregarCampoChar("empresa",2);
    xGenerales.agregarCampoChar("ipprotheus", 17);
    xGenerales.agregarCampoChar("ipalternoprotheus", 17);
    xGenerales.agregarCampoChar("ipwebservice", 17);
    
    xGenerales.agregarCampoChar("puerto", 12);
    xGenerales.agregarCampoChar("referencia", 15);
    xGenerales.agregarCampoChar("bdprotheus", 25);
    xGenerales.agregarCampoChar("pais", 2);
															//guia,tienda,caja,area,idproceso

    mysnprintf(cSql,512, "SELECT filial, empresa, ipprotheus, ipalternoprotheus, ipwebservice, puerto, referencia, bdprotheus, pais "
    "FROM tdGeneraleMotorInterfaz( '%.15s', '%d', '%d', '%s', '%d' );", datosCaja ->cParametros, sSolicitud ->iNumTienda, sSolicitud ->iCaja, "C", datosCaja ->iClaveMsj );
    logx(cSql, _LOGINFO_);
	if ( xGenerales.Exec( cSql ) == TRUE )
	{
		xGenerales.activarCols();
		if ( xGenerales.leer() )
		{
			//sprintf( cIpProtheus, "%.15s", xGenerales.ipprotheus );
           // mysnprintf( sRespuesta->infoGrabarPrestamo.cCuponFiscal,14, "%s", cTexto );
			//sprintf( cIpProtheusAlterno, "%.15s", xGenerales.ipalternoprotheus );
			//sprintf( cBDProtheus, "%.25s", xGenerales.bdprotheus );
            mysnprintf(datosCaja ->cReferenciaMsj,14, "%.13s", xGenerales.valorChar("referencia") );

			//sprintf( datosCaja ->cReferenciaMsj, "%.13s", xGenerales.referencia );
            mysnprintf(datosCaja ->cPuerto,14, "%.10s", xGenerales.valorChar("puerto") );
			//memcpy( datosCaja ->cEmpresa, xGenerales.empresa, sizeof( datosCaja ->cEmpresa ) );
			//memcpy( datosCaja ->cFilial, xGenerales.filial, sizeof( datosCaja ->cFilial ) );
			//sprintf( datosCaja ->cPuerto, "%.10s", xGenerales.puerto );
            mysnprintf(datosCaja ->cIpWebSrvice,14, "%.15s", xGenerales.valorChar("ipwebservice") );
//			sprintf( datosCaja ->cIpWebSrvice, "%.15s", xGenerales.ipwebservice );
            mystrncat(datosCaja ->cPais,  xGenerales.valorChar("pais"), sizeof( datosCaja->cPais ) - 1);

//			strncpy( datosCaja ->cPais, xGenerales.pais, sizeof( datosCaja ->cPais ) );

            mysnprintf(datosCaja ->cIpProtheus,14, "%.15s", xGenerales.valorChar("cIpProtheus") );
            mysnprintf(datosCaja ->cBDProtheus,14, "%.25s", xGenerales.valorChar("cBDProtheus") );
			//sprintf( datosCaja ->cIpProtheus, "%.15s", cIpProtheus );
			//sprintf( datosCaja ->cBDProtheus, "%.25s", cBDProtheus );
			bRegresa = true;
		}
	}
	else
	{
	//	xGenerales.odbc->GetLastError( xGenerales.GetHstmt() );
	//	grabarMensajeError( datosCaja ->cArea, datosCaja ->iCaja, datosCaja ->cIp, "ProcesosDeMotor", "gnObtenerDatosCaja", "gnObtenerDatosCaja", 
	//						cSql, datosCaja ->lEmpleado, "ERROR AL PREPARAR DATOS CAJA", xOdbcTiendaNumero, datosCaja ->iMostrarError );
	}

	return bRegresa;
}
bool Cwsprestamos00028::actualizarInteresPrestamos( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja)
{
	//CString sSqlTxt;
    char  cSql[512] = {0},log[512] = {0};
	bool bRegresa=true;
	short iCapturoSeguro=0, iCapturoTransferencia=0;

    mysnprintf(log,512, "lTotalBonificacion: %ld);",  sRespuesta ->lTotalBonificacion );
    logx(log,_LOGINFO_);

	if( sRespuesta ->lTotalBonificacion > 0 )
	{
		//sSqlTxt.Format("SELECT caActualizarDocFiscalInteresPrestamos('%.12s','%.15s', '%d')", cCuponTicket, cGpoTransaccion, 1 );
        mysnprintf(cSql,512, "SELECT caActualizarDocFiscalInteresPrestamos('%.12s','%.15s', '%d');", sRespuesta->infoGrabarPrestamo.cCuponFiscal, datosCaja ->cReferenciaMsj ,1);

		CRegistro actualizarTablasPrestamos( odbcTiendaNumero );
        actualizarTablasPrestamos.agregarCampoEntero("caActualizarDocFiscalInteresPrestamos", DT_ENTERO);

		if( !actualizarTablasPrestamos.Exec( cSql ) )
		{
			//guardarLogPrestamos( "Error al actualizar Interes de prestamo en cacarmov" );
			//actualizarTablasPrestamos.odbc->GetLastError(actualizarTablasPrestamos.GetHstmt());
			//grabarMensajeError( 'C', iCaja, (LPTSTR)(LPCTSTR)sServer, "CA0052.DLL", "CDlgCapturarPrestamos", "actualizarPrestamos", (LPTSTR)(LPCTSTR)sSqlTxt, lEmpleado, "ERROR #7857", actualizarTablasPrestamos.odbc, iMuestraMsg );
			bRegresa=false;
		}
		else
		{
            actualizarTablasPrestamos.activarCols();
            if ( actualizarTablasPrestamos.leer() )
            {
                iCapturoTransferencia= actualizarTablasPrestamos.valorLong("caActualizarDocFiscalInteresPrestamos");
            }
	    }
    }
	return bRegresa;
}
int Cwsprestamos00028::generarFacturaElectronicaNCC( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja )
{    
    char cTexto[128] = {0}, cTextoTmp[128] = {0}, cURL[128] = {0},cFechaDesdeLocal[30] = {0}, cFechaHastaLocal[30] = {0};;
    char cLog[512] = {0};
    int iJson = SOAP_ERR,iYear=1900,iMes=1,iDia=1;
    int iRespuesta = _ERROR_QUERY_;
    int  iContIva = 0;
    char cUsuarioBD[20] = {0}, cPassBD[60] = {0}, cNombreBD[20] = {0}, cIpServidor[20] = {0}, cFecha[16] = {0};
        if(sSolicitud -> iFlagBonificacion ==1){
            if(llenarEstructura( odbcTiendaNumero,infoFE, sRespuesta, sSolicitud,8)){
            soap *soapFE = soap_new1( SOAP_C_UTFSTRING );
            value vSolicitudJson( soapFE );
            value vRespuestaJson( soapFE );

            soapFE->double_format = "%.2lf";     
            mysnprintf( cURL,128, "http://%.16s:8078/api/comprobantes/creaComprobante",  sSolicitud -> cIPwshasar );
            //logx( cURL );
            mysnprintf( cTexto,128, "%.16s",  sSolicitud -> cIPwshasar );
            //logx( cTexto, _LOGINFO_  );
            //logx( "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*", _LOGINFO_ );

            mysnprintf( cTexto, 128, "%.15s",sSolicitud ->fechaSinFormato );
            iYear = valorCampo(cTexto, 4);
            iMes= valorCampo(&cTexto[4], 2);
            iDia= valorCampo(&cTexto[6], 2);
            mysnprintf(cTextoTmp, 14, "%04d-%02d-%02d", iYear, iMes, iDia);
        // logx(cFecha, _LOGINFO_);
        /// mysnprintf( cTextoTmp, 128, "%04ld-%02ld-%02ld", valorCampo( cTexto, 4 ), valorCampo( &cTexto[4], 2 ), valorCampo( &cTexto[6], 2 ) );
            logx(cTextoTmp,_LOGINFO_);
            vSolicitudJson["comprobanteFecha"]          = cTextoTmp;
            vSolicitudJson["tipoComprobante"]           = infoFE->cTipoComprobante;
            vSolicitudJson["nroTransaccion"]            =  infoFE->iNroTransaccion;
            vSolicitudJson["nroTransaccionConfirmado"]  =  infoFE->iNroTransaccionConfirmado;
            vSolicitudJson["nroOperacion"]              = (long long int)(0);
            vSolicitudJson["tipoDocumento"]             = sSolicitud -> iTipoID;
            vSolicitudJson["documentoNro"]              = sSolicitud -> sDni;
            mysnprintf( cTexto, 128, "El dni de fe %s", sSolicitud -> sDni);
            logx( cTexto , _LOGINFO_ );
            vSolicitudJson["importeTotal"]              = infoFE->dImporteTotal;
            vSolicitudJson["importeNetoNoGravado"]      = infoFE->dImporteNetoNoGravado;
            vSolicitudJson["importeNeto"]               = infoFE->dImporteNeto ;
            vSolicitudJson["importeExcento"]            = 0;
            vSolicitudJson["importeTributo"]            = 0;
            vSolicitudJson["importeIVA"]                = infoFE->dImporteIVA ;
            vSolicitudJson["sucursal"]               	= (int)sSolicitud->iNumTienda;
            //vSolicitudJson["sucursal"]               	= (int)1;
            vSolicitudJson["caja"]               		= (int)sSolicitud->iNumCaja;

            if (sSolicitud->iSecModo == 2)
            {
                vSolicitudJson["sucursal"]              = (int)1;
            }                     		                          
            vSolicitudJson["alicuotas"][0]["baseImponible"]   = infoFE->dBaseImponible3;
            vSolicitudJson["alicuotas"][0]["importe"]         = infoFE->dImporte3;
            vSolicitudJson["alicuotas"][0]["tipoIVA"]         = infoFE->cTipoIVA3;        
            logx( "----------------------------------------3", _LOGINFO_  );
        

            
            if( infoFE->lNumeroComprobanteAs > 0 )
            {
                vSolicitudJson["comprobantesAsociados"][0]["numeroComprobante"]     = infoFE->cTipoComprobanteAs;
                vSolicitudJson["comprobantesAsociados"][0]["puntoVentaId"]          = (long long int)infoFE->lPuntoVentaIdAs;
                vSolicitudJson["comprobantesAsociados"][0]["numeroComprobante"]     = (long long int)infoFE->lNumeroComprobanteAs;
                logx( "----------------------------------------6", _LOGINFO_  );
            }
            mysnprintf( cFechaDesdeLocal, 128, "%.10sT01:00:00.000Z" ,cTextoTmp);
            mysnprintf( cFechaHastaLocal, 128, "%.10sT23:54:07.870Z" ,cTextoTmp);
            vSolicitudJson["periodoAsoc"]["fechaDesde"]	=	 cFechaDesdeLocal;
            vSolicitudJson["periodoAsoc"]["fechaHasta"]	=	 cFechaHastaLocal;

            mysnprintf( cTexto, 128, "El tipo de fe %s", infoFE->cTipoDocumento );
            logx( cTexto , _LOGINFO_ );
            mysnprintf( cTexto, 128, "El dni de fe %d", infoFE->cDocumentoNro);
            logx( cTexto , _LOGINFO_ );
            logx( "Conectando a WS de FE....", _LOGINFO_  );
            displayJson( &vSolicitudJson );

            if (sSolicitud->iSecModo == 1) //productivo
            {
                iJson = json_call( soapFE, cURL, &vSolicitudJson, &vRespuestaJson );
            
                mysnprintf( cTexto, 128, "Respuesta de WS %d", iJson );
                logx( cTexto , _LOGINFO_ );
                displayJson( &vRespuestaJson );      

                if( iJson == SOAP_OK )
                {
                    if( vRespuestaJson.has("resultado") )
                    {
                        if( strcmp( (char *)vRespuestaJson["resultado"], "A" ) == 0 )
                        {
                            iRespuesta = _OK_;

                            sRespuesta->infoGrabarPrestamo.iNroTransaccion = vRespuestaJson["nroTransaccion"];
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cTipoComprobante,3, "%.2s", (char *)vRespuestaJson["tipoComprobante"] );
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cResultado,3, "%.2s", (char *)vRespuestaJson["resultado"] );
                            
                            if( mystrnlen( (char *)vRespuestaJson["cae"] ) > 0 ) 
                            {
                                mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%s", "CAE" );                    
                                mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", (char *)vRespuestaJson["cae"] );
                                mysnprintf( sRespuesta->infoGrabarPrestamo.cCaeFechaVto,11, "%.10s", (char *)vRespuestaJson["caeFechaVto"] );
                            }
                            else
                            {
                                mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", (char *)vRespuestaJson["caea"] );
                                mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%s", "CAEA" );
                            }

                            mysnprintf( sRespuesta->infoGrabarPrestamo.cFechaProceso,50, "%.25s", (char *)vRespuestaJson["fechaProceso"] );  

                            mysnprintf( cTexto,128, "%04d%08ld", (int)vRespuestaJson["puntoVenta"], (long)(long long int)vRespuestaJson["numeroComprobante"] );
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cCuponFiscal,14, "%.13s", cTexto );
                            mysnprintf( sRespuesta->infoGrabarPrestamo.cPDV,6, "%04d", (int)vRespuestaJson["puntoVenta"] );
                        }
                        else
                        {
                            sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                            mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");
                            sRespuesta->iErrorDirectorio = 96000035;

                            sRespuesta->iDevStatus = _ERROR_HTTP_;
                            mysnprintf(sRespuesta->cDevMensaje,255,"LA RESPUESTA DEL WS PARA LA FE NO ES LA ESPERADA: %.200s", (char *)vRespuestaJson["resultado"] );
                            logx(sRespuesta->cDevMensaje, _LOGINFO_ ); 
                        }
                    }
                    else
                    {
                        sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                        mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");
                        sRespuesta->iErrorDirectorio = 96000033;

                        sRespuesta->iDevStatus = _ERROR_HTTP_;
                        mysnprintf(sRespuesta->cDevMensaje, 255,"%s","LA RESPUESTA DEL WS NO TRAE EL CAMPO resultado" );
                        logx(sRespuesta->cDevMensaje, _LOGINFO_ ); 
                    }
                }
                else
                {             
                    sRespuesta->status = _ERROR_DE_SERVIDOR;                        
                    mysnprintf(sRespuesta->cMensaje, 255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR PARA GENERAR FACTURA ELECTRONICA");

                    soapError( soapFE, cLog );
                    sRespuesta->iErrorDirectorio = 96000034;

                    sRespuesta->iDevStatus = _ERROR_HTTP_;
                    mysnprintf(sRespuesta->cDevMensaje, 255,"ERROR AL CONSUMIR EL WEBSERVICE DE FE. [%.200s]", cLog );
                    logx(sRespuesta->cDevMensaje, _LOGINFO_ );
                    
                    //soap_print_fault( soapFE, stderr );        
                }

                soap_destroy(soapFE);
                soap_end(soapFE);
                soap_free(soapFE);
            }
            else //desarrollo
            {
                iRespuesta = _OK_;
                sRespuesta->infoGrabarPrestamo.iNroTransaccion = infoFE->iNroTransaccion;
                mysnprintf( sRespuesta->infoGrabarPrestamo.cTipoComprobante,3, "%.2s", "06");
                mysnprintf( sRespuesta->infoGrabarPrestamo.cResultado,3, "%.2s", "0A" );
                mysnprintf( sRespuesta->infoGrabarPrestamo.cCertificado,15, "%.14s", "3045219873706" );
                mysnprintf( sRespuesta->infoGrabarPrestamo.cModo,5,"%.4s" , "CAEA" );
                mysnprintf( sRespuesta->infoGrabarPrestamo.cFechaProceso,50, "%.48s", "2020-11-10T15:30:17.976-07:00[America/Chihuahua]" ); 
                mysnprintf( cTexto,127, "%04d%08lld",0022, infoFE->iNroTransaccion );
                mysnprintf( sRespuesta->infoGrabarPrestamo.cCuponFiscal,14, "%s", cTexto );
                // sprintf( sRespuesta->infoGrabarPrestamo.cPDV, "%04d", (int)vRespuestaJson["puntoVenta"] );
                mysnprintf( sRespuesta->infoGrabarPrestamo.cPDV,6, "0000" ,0);
                logx("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",_LOGINFO_);
                logx(sRespuesta->infoGrabarPrestamo.cFechaProceso,_LOGINFO_);
                if (strcmp(sRespuesta->infoGrabarPrestamo.cFechaProceso, "2020-11-10T15:30:17.976-07:00[America/Chihuahua]") == 0)
                {
                    sRespuesta->iFeActiva = 0;
                }
                else
                {
                    sRespuesta->iFeActiva = 1;
                }
            }
        }

    }
    else{
        iRespuesta = _OK_;
    }

    return iRespuesta;
}
bool Cwsprestamos00028::actualizarFECacarmov( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja ,int iTipoComprobante)
{
	bool bRespuesta = true;
	char cSql[360] = {0}, cFechaFE[25] = {0}, cCadena[50] = {0},cLog[256] = {0};
    mysnprintf( cLog,256,"%d",iTipoComprobante );
    logx(cLog,_LOGINFO_);
    
	if( iTipoComprobante == 6 )
	{
        mysnprintf(cCadena,50, " and clave||tipomovimiento = 'SA' " ,"");
	}
	else if( iTipoComprobante == 8 )
	{
        mysnprintf(cCadena,50, " and clave||tipomovimiento = 'SE' " ,"");
	}

	CRegistro actualizaCacarmov( odbcTiendaNumero,false );
    //actualizaCacarmov.agregarCampoEntero("caActualizarDocFiscalInteresPrestamos", DT_ENTERO);
	mysnprintf( cSql,256,"%d",iTipoComprobante );
    logx(cLog,_LOGINFO_);
   // mysnprintf( cSql,256,"Update cacarmov set docfiscal='%s', nrotransaccionfe=%ld, certificadofe='%s', modofe='%s' where cliente =%ld and caja=%d and recibo = %ld %s", sRespuesta->infoGrabarPrestamo.cCuponFiscal,  (long long int)infoFE->iNroTransaccion, sRespuesta->infoGrabarPrestamo.cCertificado,  sRespuesta->infoGrabarPrestamo.cModo, sSolicitud ->lCliente, sSolicitud ->iCaja, sRespuesta ->lRecibo, cCadena  );
    if( iTipoComprobante == 6 )
    {
        mysnprintf( cSql,360,"Update cacarmov set docfiscal='%0.12s', nrotransaccionfe=%lld, certificadofe='%s', modofe='%s' where cliente =%ld and caja=%d and recibo = %ld %s", sRespuesta->infoGrabarPrestamo.cCuponFiscal,  infoFE->iNroTransaccion, sRespuesta->infoGrabarPrestamo.cCertificado,  sRespuesta->infoGrabarPrestamo.cModo, sSolicitud ->lCliente, sSolicitud ->iCaja, sRespuesta ->lRecibo, cCadena);
    }
    else if( iTipoComprobante == 8 )
    {
        mysnprintf( cLog,256,"docfiscal='%0.12s', ivacuponncc=%ld, nrotransaccionfe=%lld, certificadofe='%s', modofe='%s' where cliente =%ld and caja=%d and recibo = %ld %s", sRespuesta->infoGrabarPrestamo.cCuponFiscal , sRespuesta ->lIvaPrestamo,  infoFE->iNroTransaccion, sRespuesta->infoGrabarPrestamo.cCertificado,  sRespuesta->infoGrabarPrestamo.cModo, sSolicitud ->lCliente, sSolicitud ->iCaja, sRespuesta ->lRecibo, cCadena);
        logx(cLog,_LOGINFO_);
        mysnprintf( cSql,360,"Update cacarmov set docfiscal='%0.12s', ivacuponncc=%ld, nrotransaccionfe=%lld, certificadofe='%s', modofe='%s' where cliente =%ld and caja=%d and recibo = %ld %s", sRespuesta->infoGrabarPrestamo.cCuponFiscal , sRespuesta ->lIvaPrestamo,  infoFE->iNroTransaccion, sRespuesta->infoGrabarPrestamo.cCertificado,  sRespuesta->infoGrabarPrestamo.cModo, sSolicitud ->lCliente, sSolicitud ->iCaja, sRespuesta ->lRecibo, cCadena);
       // hr = StringCchPrintf(cSql,256, "Update cacarmov set docfiscal='%s', ivacuponncc=%ld, nrotransaccionfe=%I64d, certificadofe='%s', modofe='%s' where cliente =%ld and caja=%d and recibo = %ld %s", cCuponNcc, lIvaPrestamo, i64NroDocumentoFE, cCertificadoFE, cModoFe, lCliente, iCaja, lRecibo, cCadena ); 
    }
    logx(cSql,_LOGINFO_);
    //guardarLogPrestamos(cSql);
    if(sSolicitud -> iFlagBonificacion ==1 || iTipoComprobante ==6) {
        if( !actualizaCacarmov.Exec(cSql))
        {
            sRespuesta->status = _ERROR_DE_SERVIDOR;
            mysnprintf(sRespuesta->cMensaje,255,"%s","OCURRRIO UN ERROR EN EL SERVIDOR");

            sRespuesta->iDevStatus = _ERROR_QUERY_;
            mysnprintf(sRespuesta->cDevMensaje,255,"ACTUALIZAR cacarmov- ERROR AL EJECUTAR QUERY. [%.200s]", actualizaCacarmov.error() );
            logx( sRespuesta->cDevMensaje, _LOGINFO_ );        
            bRespuesta = false;
        }
    }


	return bRespuesta;
}
