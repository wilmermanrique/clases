#ifndef _Cwsprestamos00028_
#define _Cwsprestamos00028_

#include "estructuras.h"
#include "conecta.hpp"
#include "gnfunciones.h"
#include "CRegistro.h"
#include "definiciones.h"

class Cwsprestamos00028
{		
public:
	Cwsprestamos00028(void);
	~Cwsprestamos00028(void);	

    int wsconsultarParametricoPrestamo(sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);

private:

    S00028Respuesta estructuraSalida;


	bool consultarParametricoPrestamo(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    int obtenerFlag( C_ODBC *odbcTiendaNumero, char cArea, int iTipo, sRespuestaServicio *sRespuesta);
    bool obtenerCasoNuevoCliente( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
    bool obtenerIpCredito( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta );
    bool obtenFecha( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta );
    void checarFecha( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iEdadCliente );
    bool buscarClienteCCuenta(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    bool obtenerParametricoPrestamos(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iClienteTestigo);
    bool obtenerMinimoPrestamo(C_ODBC *odbcTiendaNumero, int &iMontoMinimoPrestamo, sRespuestaServicio *sRespuesta);
    bool checarCuentaReestructurada(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    void checarCondicionCliente( C_ODBC *odbcCartera, C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iClienteTestigo );
    int checarCondicionClienteLocalCC( C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);
    int calcularMesesTranscurridos(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta);
    bool consultarInfoPlazos(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, int &iTasainteresmoratorio8x);
    bool consultarClienteModificacionParametrico( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iGrupo);
    void obtenerMesesTransCC(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    bool obtenerMesesPorFecha( C_ODBC *odbcTiendaNumero, char *cFecha, int &iMeses );
    void obtenerMonto12y18MesesMuebles( C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long &lSaldo12, long &lSaldo18  );
    bool obtenerValorTdConfiguracion(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, char *cElemento, char *cValor, bool bCommit, int opcion );
    void consumirWebserviceParametrico(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta);
    void grabarPrestamoUN(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta); //PET1438
    long obtenerReciboCajas(C_ODBC *odbcTiendaNumero, int iFlag, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);
    long grabarEnCarteraPrestamos(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);//PET1438
    bool crearTablaTmpCrCancPrestamos(C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);//PET1438
    bool crearTablaTmpCrPrestamos(C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);//PET1438
    bool crearTablaTmpCacarmov(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);

    bool grabarLiquidacionPorNuevoPrest(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,long lRecibo,sRespuestaServicio *sRespuesta);//PET1438
    bool grabarPrestamo(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,long lRecibo,sRespuestaServicio *sRespuesta);//PET1438
    int transaccionDB( C_ODBC *odbc, char *cQuery, sRespuestaServicio *sRespuesta );
    bool ejecutarFuncionesPostgres( C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta,long lRecibo);
    bool obtenerCuponTicket(sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja);
    bool actualizarPrestamos(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja);
    void obtenerFolioPrestamo( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta);
    bool obtenerTasaInteres( C_ODBC *odbcTiendaNumero, int &iTasaInteresPrestamos, sRespuestaServicio *sRespuesta);
    void obtenerInfoEmpleados(  sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta );
    void obtenerInfoFinancieraPrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta);
    void consultarImportePrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta);
    void obtenerAbonoYTotalAnualPrestamo(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long &lImporte, double &dIntSobre);
    void errorGenericoPrestamo(sRespuestaServicio *sRespuesta, char *cDevMensaje, char *cMensaje);
    int obtenerDescripcionTdConfiguracionPrestamos(sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta, int &iNumeroMensaje );
    bool grabarCarteraServicio(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, long lRecibo); 
    bool verificarCantidadPrestamos( C_ODBC *odbcCartera, sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud);
    void ObtenerCajero( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iRespuesta);
    bool actualizarTdAutorizacionHuellas(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja);
    bool grabarAutorizacionGerentes(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char cTipo);
    bool grabarInformacionPrestamosCertificacion( C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iFlagAutorizoPrestamo );
    bool obtenerIVAPrestamo(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud , sRespuestaServicio *sRespuesta ,int iTipoComprobante);
    bool obtenerUltimoNroDocumento(C_ODBC *odbcTiendaNumero,InfoFE *infoFE,sSolicitudServicio *sSolicitud, int iTipoConsulta );// 0 consulta - 1 incrementa
    bool llenarEstructura(C_ODBC *odbcTiendaNumero,InfoFE *sRecibe,  sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud, int iTipoComprobante); // 6 "Factura B" -- 8: "Nota de credito B"
    bool obtenerIvaImpuestoInterno( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, sSolicitudServicio *sSolicitud );
    int generarFacturaElectronica( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta , DatosCajaSudamerica *datosCaja);
    int generarFacturaElectronicaNCC( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja );

    bool interfaceInsertarMovtoPAJLocal(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja);
    bool gnGenerarMovimientosReembolsoLocal02( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iProceso, bool bCommit, char cTipoProceso,DatosCajaSudamerica *datosCaja );
    bool crearTablaTmpPAJ(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud, char *cEmpresa);
    bool consultarCajaProtheus( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, char *cCajaProtheus, char *cAgencia, char *cCuenta, int iTipoRetiro, bool bCommit );
    bool grabarPAJLocal2(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    bool obtenerCuponTicket(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja);
    bool gnObtenerDatosCaja(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja);
    bool actualizarCrprestamosFE(C_ODBC *odbcCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
    bool actualizarInteresPrestamos( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, DatosCajaSudamerica *datosCaja);
    bool actualizarFECacarmov( C_ODBC *odbcTiendaNumero,InfoFE *infoFE, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta,DatosCajaSudamerica *datosCaja ,int iTipoComprobante);

};

#endif  //_Cwsprestamos00028_
