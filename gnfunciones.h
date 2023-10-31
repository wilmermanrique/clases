#ifndef _wsprestamos_PROTO_GRAL
#define _wsprestamos_PROTO_GRAL

#include <C_ODBC.hpp>
#include "definiciones.h"
#include "estructuras.h"
#include "CRegistro.h"
#include "CListaCodigo.h"
#include "flags.hpp"
#include <sys/socket.h>
#include "CSocketx.hpp"
#include "folios.hpp"

// void abrirLog( void );
int abrirConexion( C_ODBC *xOdbc, char *cIP, char *cBD , char *cUsuario );
int abrirConexion2( C_ODBC *xOdbc, char *cIP, char *cBD , char *cUsuario,char *cClave );
void strtrim(char* str, int size);
bool consultarParametro( C_ODBC *odbc, const char *cParametro, char *cValor );
bool consultarDescripcion( C_ODBC *odbc, long lCodigo, int iTalla, char *cDescripcion, int iFormato, char *cSql );
int consultarIpServidor( C_ODBC *odbc,char *cSql);
bool consultarIpServidorggnml( C_ODBC *odbc, short iTipoServidor , char *cIpServidor );
bool obtenerDatosEmpleado(C_ODBC *odbc, long lNumEmpleado,sDatosempleado *sEmpleado);
bool obtenerClaveEmpleado(C_ODBC *odbc, long lNumEmpleado,sDatosClaveempleado *sEmpleado);
bool obtenerDatosConexionBD( int iControl, char *cPwd, char *cUsr, char *cBd, long numTienda );
int abrirConexionCartera( C_ODBC *xOdbcCartera, char *cIpBDCartera,char *cBDCartera ,char *cUsuarioCartera  );
int consultarIpServidor( C_ODBC *odbc, short iTipoServidor , char *cIpServidor );
bool realizarConsulta( C_ODBC *odbc, char *cSql, char *cNombreCampo, char *cValor );
bool crearTablaTemporal( C_ODBC *odbcDBTiendaNumero,int *iCaja,int *iSysNotaCobro, long lNumOrdenNUBE);
bool limpiarTabla(C_ODBC *odbcDBTiendaNumero, sSolicitudServicio *sSolicitud,int *iSysNotaCobro,int *iCaja);
bool consultarFlag( C_ODBC *odbc, int iFlag, int iFlagDescripcion, int * iRespuesta );
bool consultarFlagJC(C_ODBC *xOdbc, char cArea, int iTipoFlag, int *iValorFlag);
bool consultarFlag(C_ODBC *xOdbc, char cArea, int iTipoFlag, short *iValorFlag);
bool consultarFlagSysflags( C_ODBC *odbc, int iFlag, char cArea, int * iRespuesta );
bool consultarFlagPinPad( C_ODBC *odbc, int iCaja,int iCajaOriginal, char * cArea,int iSistema, int * iRespuesta );
bool consultarParidadDolar( C_ODBC *odbc, int * iRespuesta );
bool consultarIpServidores( C_ODBC *odbc, char * cRespuesta, int iTipoServidor );
int abrirConexionCorreos( C_ODBC *odbcCorreos, char *cIpBDCorreos,char *cBDCorreos ,char *cUsuarioCorreos  );
long incrementarFolio( int iFlagIncremento, char *cArea, int iCaja, int iTipoFolio, C_ODBC *xodbc, bool &bConsulta );
bool crearTemporalesTiendaRopa( C_ODBC *odbcTiendaNumero, int iCaja, long lNumOrdenNUBE );
bool BorrarTablasTemporalesNube( C_ODBC *odbcTiendaNumero, int iCaja, long lNumOrdenNUBE );
int esEmpleado( long lCliente );
int esEmpleadoSinDig( long lCliente );
void generarVentaCaida(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
int obtenerTipoClienteLCC(C_ODBC *odbcCartera, sRespuestaServicio *sRespuesta, long *lCliente);
void obtenerDatosClienteLCCRopa(C_ODBC *odbcTiendaNumero,C_ODBC *odbcCartera,sRespuestaServicio *sRespuesta,int *iFlagDescuentoEspecial,int *iFlagClienteNunca,long *lCliente);
void grabarAutorizacionGerentes( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char cTipo, long lFolio, long lEmpleado, char *cIdentificacion, int iSistema, int iClave, bool &bContinuar, long lEmpleado2);
int crearTmp( char *cNombreTablaOrigen, bool &bContinuar, C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta );
bool crearTablatemporalMuebles(C_ODBC *odbcTiendaNumero, int *iCaja, long *lNumOrdenNUBE);
bool obtenerValorConfiguracion( C_ODBC *odbcTiendaNumero, char *cValor, char *cElemento, char *cSql );
void quitarBlancoNull( char *cCampo, int iTam );
bool gnObtenerDatosCaja( C_ODBC *odbcTiendaNumero, DatosCajaSudamerica &datosCaja );
bool obtenerFechaHora(C_ODBC *odbcTiendaNumero, char *cFecha, char *cHora );
bool consultarColoniaCliente(C_ODBC *odbc_cartera, sSolicitudServicio *sSolicitud, int &iIdColonia );
bool obtenerCodigoPostal(C_ODBC *odbc_cartera, sSolicitudServicio *sSolicitud,int iIdColonia, long &lCodigoP );
void obtenerProvincia(C_ODBC *odbcTiendaNumero, char *cProvincia, int iCiudad, int iModo, sRespuestaServicio *sRespuesta, int iTiendaLocal, int iTienda);
float ObtenerValorNeto(C_ODBC *odbcTiendaNumero, int iCodigo, int iPrecio, char cCausaUdi, char cQuienEntregaGlobal);
bool inicializarTablasTemporales(C_ODBC *odbcTiendaNumero,int iCaja, long lFactura, char *sPadStart);
long totalFactura(C_ODBC *odbcTiendaNumero,sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta);
bool obtenerFechaDescuentoPrimerCompra(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta,long lCliente, int iTiendaLocal, int iTienda);
int checarCodigoJoyeria( long lCodigo );
int checarAgotadoCodigo( C_ODBC *odbcTiendaNumero, char cFlagApartado, char cAgotadoInvent );
bool checarSisApartadoNoMsg( int &iFlag, C_ODBC *odbcTiendaNumero, char *cSqlTxt );
bool obtenerFlagApartadoMuebles( int &iFlagApartado, C_ODBC *odbcTiendaNumero, char *cSqlTxt );
void calcularDiaDePago( int &iMesPrimerPago, int &iDiaDePago, int iAnioActual, int iMesActual, int iDiaActual );
void desplegarHoraEntrega( C_ODBC *odbcTiendaNumero,int iHoraIniEntMovto, int  iHoraFinEntMovto);
int determinarNumeroX( char cNumero );
bool consultarFechas(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
bool validarReglaTopesActiva(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud);

int obtenerPuntosPrecalificasionCN(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
int obtenerFechaUltCompraRM( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char *cFechaUltCompra, int iSegundaConsulta);
bool calcularTotales (C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iFlagPrimerCalculo);
void gnGrabarSeguimiento( C_ODBC *odbcTiendaNumero, char cArea, int iCaja, int iProceso, char *cLog/*, bool bCommit*/ );
bool ponerTopeVentaCredito( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
////mensaje 27


bool descuentoEmpleadoMovistar( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud );
bool consultaStatusCLCC( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
//void asignarDesctoAut( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iRen );
bool aplicaDescuentoDeEmpleado( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
void identificarTopeCredito( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
int obtenerFactorLinea( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta  );
bool leerParametricosCliente( C_ODBC *odbcCartera, S00028Envia &pCuentaEnvia, long lCliente );
int consultarClienteTestigo( C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, long lCliente );
void obtenerPagosHistorial(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int iSistema);

int diasTranscurridos(int iDia, int iMes, int iAnio,int iDiaActual, int iMesActual, int iAnioActual);
long consultarFechaPrimerCompraRetorno( C_ODBC *conexionCartera, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long lCliente );

int obtenerFechaAltaCliente( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char *cFechaAlta );
long calcularSaldoFactorizadoNuevaCompra(C_ODBC *odbcTiendaNumero,sRespuestaServicio *sRespuesta, int iPlazo, long lSaldo, int iFlagLineaCreditoEsp, int iCteNEspecial, int iTipoCreditoCliente, int iTipoCtaRM, int iTiendaLocal, int iTienda);
bool consultarFechasGnDominio(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta);
bool obtenerFechaInicioFinTdConfiguracion( C_ODBC *xOdbcTiendaNumero, char *cElemento, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
bool consultaTdaDctoCLCC(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
void apagarFlagCteCero(sRespuestaServicio *sRespuesta, int iModo);


bool obtenerTipoOrigenCliente(C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
bool consultarFolio( C_ODBC *conexionLocal,int iTipoFolio,sRespuestaServicio *sRespuesta );
long incrementarFolio( int iFlagIncremento, char *cArea, int iCaja, int iTipoFolio, C_ODBC *xodbc, char *cSqlTxt, bool &bConsulta );
bool consultarFlagTdaVentaHuella( C_ODBC *xOdbcTda, int &iFlagTdaVentaHuella, char *cSql );
long verificarUltimaNota( C_ODBC *odbcTiendaNumero, int iTipoFolio, int iCaja );
double consultarFactorTasasDiferenciadas(C_ODBC *odbc, sRespuestaServicio *sRespuesta, long lCliente);

bool esCiudadQuePercibe(C_ODBC *conexionCartera,int iCiudad);
bool obtenerImporteVtaSinImpuestosRopa(C_ODBC *odbcTiendaNumero,sRespuestaServicio *sRespuesta,sSolicitudServicio *sSolicitud);
bool obtenerValorNetoArticulo( C_ODBC *odbcTiendaNumero,sRespuestaServicio *sRespuesta, int iCodigo, int iPrecio );
long ObteneriSMC(long lSalarioMinimo);

//gfiML
short dcf( short iValorDcf );
int meses_transcurridos( int dia,int mes,int anio ,int diaactual, int mesactual,int anioactual);

int checarJoyeriaCoppel( long lCodigo, int iAnio, int iMes, int iDia );
int ChecarFamTarjetasTiempoAire( long lFamilia );
bool obtenerFlagApartadoMuebles( int &iFlagApartado, C_ODBC *xodbc );
bool checarSisApartadoNoMsg( int &iFlag, C_ODBC *xodbc);
int checarSistemaCjs( char cAgotado, char cImportacion, char cQuienEntrega, short iFlagBodCjs, char *cMensaje );

void sumarDia( int iSumarDia, int &iDia, int &iMes, int &iYear );
void miniFecha(char *fecha, int dia, int mes, int ano);
int ano_2000_2dig( int ano );
bool checarAntiguedadCodigo( long lCodigo, C_ODBC *xOdbc, char *cSqlTxt, int &iDiaAntiguedad, int &iMesAntiguedad, int &iAnioAntiguedad );

bool obtenerFechaPrimerCompra(C_ODBC *odbcCartera, long lCliente, long lFecha, sDatosAltoRiesgoCR *datosAltoRiesgo);
int consultaDatosGndominio(C_ODBC *odbcTiendaNumero);
void consultarCrParametricoAR(C_ODBC *odbcTiendaNumero, int iDiasTransUltcompra, int iAntMeses, long lPtjCompra, int &iPtsSaturacion, int &iPtsAntiguedad, int &iPtsUltCompra, int iTipoVenta, char cPuntualidad, int iFlagTestigoAR);
void obtenerFechaPrimerCompraCR(C_ODBC *odbcCartera, int iNoCliente, char* cFechaPrimerCompraCR);
int obtenerPorcentajePIParametrico(C_ODBC *odbcTiendaNumero, C_ODBC *odbcCartera, S00028Envia &pCuentaEnvia, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, int &iDiasTransUltimaCompra, int iFlagNEspecial, int iPagosVsSaldo, int iFlagTestigoAR, int iCteNEspecial);
int obtenerPuntosIniciales(C_ODBC *odbcTiendaNumero);
void eliminarEspacioBlanco( char *cTexto, int iCantidad );


bool consultarIpServidores( C_ODBC *xOdbc, char *cIpServidor, char *cIpServidorAlterno, short iTipoServidor, char *cSql);
int ano_2000_4dig( int ano, int anioactual );
int obtenerNumCiudadApartado(C_ODBC *odbcTiendaNumero);

int verificarPrecioCodigo(C_ODBC *odbcTiendaNumero, sRespuestaServicio *sRespuesta, long lCodigo, int iTalla, int iPrecio, int iCantidad, int iTienda, int iCaja, char cTipoMovto, bool bCommit);
bool roVerificarPrecioAgregaBorrarAutorizacion(C_ODBC *odbcTiendaNumero, char cMovimiento, long lCodigo, int iTalla, int iPrecio, int iCantidad, int iTienda, int iCaja, long lEmpleado, int iFlagHuella, int iAnio, int iMes, int iDia, char *cFolioMovimiento, char cTipo, long lCodigoAnt, int iTallaAnt, int iPrecioAnt);
bool ActualizarPuntosCoppel( C_ODBC *xOdbcCartera, long lCliente, int iNuevosPuntos, bool bEsCancelacion, int iMesesVigencia, long lFactura, int iTienda);

void ponerTopeVentaCreditoVentaUn( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, long lTotalConDesc );
int ConsultarCuentaReestriccion( C_ODBC *odbcDBTiendaNumero, int iTienda, long lCliente, int iTiendaLocal );
void padStart(sRespuestaServicio *sRespuesta,char *valor);
int confirmarTransaccionFE( sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
void consultarFechaCaea( C_ODBC *odbc,char *cFecha, char *cFechaDelDia );
void obtenerFecha(C_ODBC *odbcTiendaNumero, char *cFecha );
double consultarTasaInteres8XRopa(C_ODBC *odbcTiendaNumero );
int obtenerDiasPrimerCompra(C_ODBC *odbcCartera, long lCliente, int dia, int Mes, int Anio );
void separarFecha(long lFecha, char *cDia, char *cMes, char *cAnio);
bool exitenPlanes( C_ODBC *odbcTiendaNumero,  int iTipo, char *cTarjetaID );
long obtenerFinanciamiento( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta );
void infoCostoFinanciero( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta, char *cNumeroCuotasFin,  char *cNumeroCuotasAhora );
void quitarGuionesFechaGnDominio(char *cFecha, long &lFecha);
//803
int ConsultarClienteCarteraVendida(C_ODBC *odbcDBTiendaNumero, int iTienda, long lCliente, sRespuestaServicio *sRespuesta, int iTiendaLocal);
bool actualizarMovimientosTramitadas( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud, sRespuestaServicio *sRespuesta);
void consultarFechaGndominio( C_ODBC *odbcTiendaNumero, sSolicitudServicio *sSolicitud,sRespuestaServicio *sRespuesta );

int checarCodigoMuInvent(C_ODBC *xOdbc,long lCodigo,char *cSql, bool &bConsulta);
bool abrirConexionApartadoNoMsg( C_ODBC *odbcDBTiendaNumero,C_ODBC *conexionBodegaM, int iModoLocal, int iTienda);
bool consultarMinimoRetiroCashBack( C_ODBC *odbc, int * iRespuesta );
bool consultarMaximoRetiroCashBack( C_ODBC *odbc, int * iRespuesta );
void encondeBase64( C_ODBC *odbc, char *cTexto );
//void enconde( char *cTexto );
bool consultarSql( C_ODBC *odbc, int * iRespuesta, char* cSql, sRespuestaServicio *sRespuesta );
//char* replaceWord(const char* s, const char* oldW, const char* newW);
bool encoding( C_ODBC *xOdbc, const char *cCmd, bool flagCommit );
bool aplicaDescuentoDiaNino(SysRopa sysRopa, int iOpcion, long lCliente, long lImporteDescuentoEmpleado);
bool consultarSql( C_ODBC *odbc, int * iRespuesta, char* cSql, sRespuestaServicio *sRespuesta );
//char* replaceWord(const char* s, const char* oldW, const char* newW);
bool replaceWord(const char* s, const char* oldW, const char* newW, char *cWord);
void mymemset(void *ptr, int value, size_t num);
void mymemcpy(void *dst, const void *src, size_t n);
void mystrcat(char * dst, const char * src);
void mystrncat(char* dest, const char* src, size_t n);
long longConverter(const char * numstr);
int mystrnlen(const char *str);
int intConverter(const char * numstr);
float floatConverter(const char * numstr);
void obtener(void *dst,int iOpcion);

bool aplicaDescuentoDiaNino(SysRopa sysRopa, int iOpcion, long lCliente, long lImporteDescuentoEmpleado);
int consultarSEC(char *cConexion, char *cDns, char *cUsuario, char *cBd, char *cPass, int iModoLocal, int iTienda);
void obtenerClaveSEC(int iTienda, char *cTiendaNumero, int iOpcion);
bool encoding( C_ODBC *xOdbc, const char *cCmd, bool flagCommit );
bool obtenerClaveEncriptado( char *cClaveEncriptado );
int abrirArchivo( char *cNombre );
int leerArchivo( char *cClaveEncriptado );
bool leerArchivoTienda90( );
int abrirArchivo90(char *cNombre);
int obtenerSecModo(int *iSecModoRespuesta);
int abrirArchivomodoSEC();
// Se coloca una condicion donde marca la vulnerabilidad (if(ispermission(1), siempre va a regresar true)), soluciona:
// Improper Resource Access Authorization
bool ispermission(int user);

void quitaEspacio(char * cCadena);

#define mysprintf(_s, _f, ...) {\
    int s = 0;\
    char buf[MAX_BUFFER_CHAR] = {0};\
    mysnprintf(buf, MAX_BUFFER_CHAR, _f, __VA_ARGS__);\
    s = mystrnlen(buf);\
    mymemcpy(_s, buf, s);\
}

#define mysnprintf(_s, _l, _f, ...) {\
    int status = 0;\
    status = snprintf(_s, _l, _f, __VA_ARGS__);\
    if(status == -1){}\
}
#endif //_wsprestamos_PROTO_GRAL

