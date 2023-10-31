#include <C_archiv.hpp>
#include <C_ODBC.hpp>
#include "CListaCodigo.h"
#include "riwstruc.hpp"
#include "mustruc.hpp"

#ifndef ESTRUCTURAS_WSPRESTAMOS_
#define ESTRUCTURAS_WSPRESTAMOS_

struct S00012Respuesta
{
	char cMensajeSalidaM[128],
		cMensajeCodigos[512];

	int lFolioApartado;
	int iFlagApartadoBodegam; // Se agrega el Flag para saber cuales articulos afectaron el disponible del Bodegam -
	int iRespuesta;
};
struct GrabarPrestamoCartera03
{
	short iTipoMensaje;
	long lValorSeguridad;
	short iTipoOpcion;
	long lCliente;
	long lImportePrestamo;
	long lInteresFinanciamiento;
	long lImporteSeguroClub;
	long lFactura;
	long lFolioSeguro;
	long lEfectuo;
	long lRecibo;
	long lInteresAdicional;
	long lSaldoPrestamo;
	char cClave[3];
	char cTipoMovto[3];
	char cTipoGrabado[3];
	char cMovtoSeguro[3];
	char cFlagSeguroConyugal[3];
	char cIpServidor[17];
	int iVencidoInicial;
	int iImporteSaldaCon;
	int iAbonoBase;
	short iCiudad;
	short iTienda;
	short iCaja;
	short tFechaSaldaConDia;
	short tFechaSaldaConMes;
	short tFechaSaldaConAnio;
	short iCantSeguros;
	short iDiaActual;
 	short iMesActual;
	short iAnioActual;
	short iFlagNuevo;
	short tFechaVencimientoDia;
	short tFechaVencimientoMes;
	short tFechaVencimientoAnio;
	short iFlagTramite;
	long lSaldaCon;
	long lSaldoPrestAnt;
	long lFacturaPrestAnt;
	short tFechaNacDia;
	short tFechaNacMes;
	short tFechaNacAnio;
	long lComision;
	short tFecActNegocioDia;
	short tFecActNegocioMes;
	short tFecActNegocioAnio;
	char cCuponFiscal[12];
	char cSerieFiscal[3];
	char cCuponNcc[12];
	short iCuentaReest;
};
struct S00023Respuesta
{
	char cMensaje[256];
	int iFlagObligado;
	long lPorcentajeCompra;
	int iFlagMostrarDetalle;
	bool bContadoEspecial;
	int iAntiguedadMeses;
	int iPorcentajeDePagoInicialAR;
	int iPuntosPrecalificasionCN;
	int iSumaParametrico;
	long lTotalGEParametrico;
	long lLineaCredito;
	int iMensajeCteExcedido;
	int lLineaDeCredito;
	long long lImporteVtaSinImpuestos;
	float fAlicuota;
	char cMotivoPercepcionib[5];
	long lIIBBPercepcionImpresion;
	long lIIBBPercepcionACobrar;
	long lTotalConDescuento;
	long lTotalCredCB; // se renombra por vulnerabilidad
	char cPresupuesto[6];
	long lLineaRealCredito;
	long lEngancheRecibido;
	int iFlagPlazo18;
	int iFlagCteS50;
	long lPiSituacionS50;
	long lExcesoCompra;
	long iCteNEspecial;
	bool bFlagPuntualidadRiesgo;
	long iClienteExcedido;
	int iDiasTransPrimerCompra;
	long lExcesoTopeMaximo;
	int iPagos12Meses;
	int iNuevoSaldo;
	int iPagosVsSaldo;
	int inum_mesesconsaldo;
	long lFacturaPendiente;

	// Mensaje 27
	long iTopeMaximoSaldos;
	bool bTramitaLineaBlanca;
	bool bClieneContadoLCC;
	bool bFlagTramita;
	bool bReglaTopesActiva;
	int iTramiteCredito;
	int iFlagCteNRegistrado;
	int iFlagMensajeTramitar;
	bool bFlagClubPtoteccion;
	int iTotalAlicuota;
	long lImporteReembolso;
	int iFlagAbonoMensual;
	int iFlagLineaBlanca;
	bool bCumplePorcentTramite;
	int iTotalVentaLineaBca;
	long lFactorLinea;
	long lSaldoFactorizadoFinal;
	long lLimiteDeCred;
	int iFlagPrimerCompra;
	int iFlagNEspecial;
	int iFlagDescuentoPrimerCompra; // new
	int lClienteDescuentoPrimerCompra;
	bool bFlagDescuentoCero;
	bool bPrimerCompra;
	int iTipoComprador;

	long lCodigoOferta,
		lUltimoPrecio,
		lPrecioOferta,
		iFlagVtaMin,
		lPrecioOferta2,
		lCodigoOferta2,
		iDescuentoCalc,
		lDescuento,
		iPorcientoDescuentoEmpleado,
		lPrecioEspecial,
		iPorcientoClienteCero,
		iTipoDescuento,
		lCodigoDescm,
		iNumDesctos,
		iNumTiposDescto,
		ilCodigoOferta,
		lCodigoVtaMin;

	bool bFlagTipoDescuento;
	char cTasaCelular[3];
	char cTextoMsjError[256];
	long lReciboMovReembolso;
	char cAreaReembolso[2];
	long lNumFactReembolso;
	long lDevolucionFac;
	int iKeyxReembolso;

	char Sucursal[3],
		Prefixo[4],
		NumTitulo[13],
		Parcela[2],
		Tipo[4];
};

struct Enganche
{
	long lEngancheRecibido,
		lSobrePrecio,
		lEnganchePropuesto,
		lEngancheMinPropuesto,
		lEngancheNoTramitar,
		lMargenCreditoCliente,
		lTotalCredito,
		lSobrePrecio18,
		iPuntajeFinalParAltoRiesgo,
		iAntiguedadMeses,
		iPorcentajeDePagoInicialAR,
		iSumaParametrico,
		lTotalGEParametrico,
		iPorcentajePiDec27,
		lTotalVenta,
		lSobreprecioTotal,
		iPuntosPrecalificasionCN,
		lTotalNormalCLCC,
		iMensajeCteExcedido,
		iFlagObligado,
		iSeTramita,
		lEngancheTmp,
		iFlagEngancheCero,
		iSMCM,
		lTotalContado,
		iSMC;
	char cAutorizoMicroCredito;
	char cSiguientePago[12];
};
struct InfoVentaMoto
{

	long lCliente, lFactura, lCodigo;
	short iNumCaja, iNumTienda, iAnioModelo;

	char cNombre[16],
		cApellidoPaterno[16],
		cApellidoMaterno[16],
		cDni[16],
		cDireccion[45],
		cCuponFiscal[14],
		cDescripcion[44],
		cCuadro[25],
		cMotorSerie[25],
		cCertificado[25],
		cColorMoto[16],
		cCuadroCmp[25],
		cMotorSerieCmp[25],
		cCertificadoCmp[25];

	// char cStatus;
};

struct sDatosPagoInicial
{
	long lSaldo,
		lSaldoFactorizado,
		lCliente,
		lLineaCredPesos; // se renombra por vulnerabilidad

	int iFlagLineaCreditoEsp,
		iPuntosParCN,
		iParAltoRiesgo,
		iParRiesgoMuebles,
		iFlagCteNEspecial,
		iPlazoRopa,
		iPlazoMuebles,
		iTotalVentaRopa,
		iTotalVentaMuebles,
		iTotalVentaLineaBlanca,
		iIndice,
		iSistema;

	char cPuntualidad[3],
		cFechaAlta[12],
		cArea[3];
};

struct S00028Respuesta
{

	int lMargenCreditoDisponible,
		iPts_saturacion,
		iFlagCondicionClienteLocalCC,
		iNumeroMensaje,
		iCuentaReestructurada,
		lFactorLineaReal,
		cFechaAltaDia,
		cFechaAltaMes,
		iDiaActual,
		iMesActual,
		iGrupo,
		iAntiguedadMeses,
		iPuntosIniciales,
		iSumaPuntajeVariables,
		iPuntajeParametricoFinal,
		iFlagMensaje,
		iMostrarVencido,
		iFlagPrestamoEmpleado,
		ipuntajesaldoprestamoanterior;
	long lMontoMaximoPrestar,
		lSalarioMinimo,
		lLineaRealCred, // se renombra por vulnerabilidad
		lSaldaCon,
		lSaldoTotal,
		cFechaAltaAnio,
		iAnioActual,
		lParPrestamos;
	double ffactor;
	bool iFlagModifacionParametrico,
		bInicializar;
	char Mensaje[150],
		cNombreGerenteCajas[52],
		cValorInfo[500],
		cNombreCajero[100],
		cMontoMinimo[100];
};

struct S00029Respuesta
{
	char Mensaje[1024],
		sMensajeAlerta[1024],
		MensajeError[256],
		PremioTicket[50],
		SorteoTicket[50],
		cDni[30],
		cliente[30],
		cNombre[30],
		cTelefono[30],
		cTelefonocelular[30],
		cCasa[30],
		calle[30],
		cApellidos[31],
		cDireccion[50],
		sDomicilio[30],
		cEmail[30];
	long lCantOC1;
	int iTipo,
		Procedimiento,
		iRespuestaSort;
};
struct sDatosParametrico
{
	int iFlagCteSaturado,
		iFlagCteSaturadoNvaVenta,
		iFlagCteExcedido,
		iFlagCteExcedidoNvaVenta,
		iFactorTopeMaximo;
};

struct sRespuestaPagoInicial
{
	int iPorcentajePI,
		iPorcentajePIRopa,
		iPorcentajePIMuebles,
		iFlagTramitar,
		iMesesAntiguedad,
		iDiasTransUltCompra,
		iDiasTransPrimerCompra,
		iPagosVsSaldo,
		iFlagTestigoAR,
		iParRiesgoMuebles,
		iPuntosParCN;

	long lSaldoFactorizadoActual,
		lSaldoFactFinalMuebles,
		lSaldoFactFinalRopa,
		lEngancheRopa,
		lEngancheMuebles,
		lEngancheTotal,
		lEngancheMin,
		lCalculoFactorizado,
		lEngancheTmp;
};

struct sDatosempleado
{
	long lNumEmpleado;
	int iPermisos;
	int iAutorizar;
	int iCentro;
	char cNombre[22];
	char cApellidoPaterno[17];
	char cApellidoMaterno[17];
};
struct sDatosClaveempleado
{
	char cClaveEmpleado[17];
};

struct sSolicitudHuella
{
	char cTemplate64[2048];
	char cNumEmpleado[11];
	char cNivel[3];
	int iTipo;
};

struct sRespuestaHuella
{
	sDatosempleado sEmpleado;
	char cNumRespuesta[5];
	char cMensaje[256];
	int iTipo;
};

struct ValidarArticuloMuebles
{

	int64_t iCodigo;
	int iContadorMuebles;
	int iFlagEsMoto;
	int iFlagPaquete;
	int iFlagMotoEnFactura;
	int iFlagSoloPaquete;
	int iTipoComprador;
	bool bFlagCodigoGE;
	int iFlagCodEsp;
	int iFlagDescuentoEspecial;
	int iFlagTiendaZonaLibre;
	int iFlagArticulosM;
	int iCodigoGe;
	int iFlagCelularTN;
	char cImeiExcluir[256];

	int iAnioSys,
		iMesSys,
		iDiaSys;
};

struct Articulo
{
	int iCodigo;
	int iFormato;
	int iPrecio;
	int iTalla;
	long lPrecio;
	int iTotalCantidad;
	int iImporteDescuentoPC;
	int lImporteDescuento;
};

struct ArticuloMuebles // <- FacturaMovimientoCodigoGE01   fiwstruct
{
	long lCodigo;
	short i16Cantidad;
	char cQuienEntrega,
		cArticulo[11], // Se guarda el # de Vale en Vta. UDI.
		cMarca[11],
		cModelo[21]; // Vta. UDI=Causa del Prec. Especial y causa del UDI
	long lPrecioUnitario,
		lImporte;
	char cTipo,
		cAgotadoInvent; // Agotado del Invent.dat
	short i16Existencia;
	char cBodegaQueEntrega,
		cSemanaEntrega,
		cMesEntrega,
		cModoDeEntrega; // Vta. UDI=Causa del UDI.
	long lSobrePrecio;	// VR se guarda el # de Vale generado
	char cImportacion;
	short i16Stock;
	float fInteres12,
		fInteres18;
	char cNumeroSerieUdi[15],
		cCausaUdi,
		cDescripcionDano[45], // En los ultimos 5 caract. se graba la familia del udi para la VR
		cFlagApartado,		  // 0=No se busca en el apartado 1=Si
		cFlagCodigoEspecial,  // 1=Se comporta como el 999181 0=No
		cAgotado,
		cFlagTipoEntrada; // 0=Nuevo 1=Udi
	long lSobrePrecio18;  // A plazo 18
	char cFlagPlazo18,	  // 1=El cte. seleccion¢ plazo a 18 de lo contrario 12
		cCveImpuestoSuntuario;
	long lFamilia;
	int iStatus;			   // 0=sin movimiento  1=movto de factura
	char cFlagNoArmarArticulo, // 1=No se va a armar el art¡culo
		cFlagVtaChip,		   // 1=Celular, 2=Chip
		cNumSerieTel[18],
		cFlagSerieValida;
	short iFlagVtaMin,
		iTipoDescuento,
		iFlagVtaChip,
		iFlagCodigoOculto,
		iFlagCodigoGE,
		iAnioGE,
		iFlagCodigoArmado, // 664
		iCodidoArmadoSQL;  // 664
	long lCodigoOculto,	   // valor no visible en udis, descuentos...
		lTesTienda,
		lTesBodega,
		lCodigoGE;
	short iCelular,
		iDescEsp,
		iFlagRiesgo;
	long lDesPaquete,
		lSobrePrecioPaq,
		lSobrePrecioPaq18;
	char cFlagentregafuturo[5],
		cFlagta[5];
	short iBodega,
		iGarantia;
	char cSerieArtGE[20];
	int iFlagVentaPaquete;
};

struct sConsultarDomicilio
{
	int flagTipo;
	char idIdentificador[32];
	char cLocalidad[32];
	char cNombreCalle[32];
	int idCalle;
	int idCiudad;
	char cCiudad[32];
	long numCasa;
	long lCodigoPostal;
	int iNumDepartamento;
	int iIdColonia;
	char cNombreZona[32];
	char cNombreMunicipio[32];
	char casaunidadhabitacional[32];
	char calleunidadhabitacional[32];
	char flagunidadhabitacional[32];
	char cTelefono[15];
	char cComplemento[32];
	char cNumDepartamento[5];
	long clientecontado;
	int iPiso;
	int idZona;
};

struct sSolicitudFinanciera // Datos para la peticion 668
{
	int iMensaje;
	int iTienda;
	char cArea[3];
	int iCaja;
	char cFecha[12];
	char cIpServicio[20];
	char cDni[20];
	char cAreaTelefono[5];
	char cCelularOrigen[20];
	long lMonto;
	char cIpTienda[17];
	char cIpSolicitudes[17];
	int iFinanciera;
	char cSexo[3];
	int iDiaCobroSueldo;
	int iTipoTelefono;
	char cOperadora[16];
	int iIdArticulo;
	char cCodigo[5];
	int iDepartamento;
	char cComercio[8];
	char cMotivo[100];
	long lSolicitudPendienteID;
	int iIdCredito;
	char cToken[6];
};

struct sRespuestaFinanciera
{
	int iRespuesta;
	char cMensaje[256];
	char cDictamen[11];
	long lSolicitudPendienteID;
	long lImporteAprobado;
	char cCodigo[5];
	char cUrlPDF[256];
	int iCantidadPlanes;
	int iIdCredito;
	double dPrimerPago;
	bool mostrarDlgResumen;
	bool mostrarDlgToken;
};

struct sFormasDePago
{
	char cArea[2],
		cFechaActual[9],
		cCodAutorizacionBanco[9],
		cBanco[17],
		cLocalForaneo[2],
		cAdm[4],
		cDni[20],
		cCupon[11],
		cNcc[14],
		cFinancieraAdm[4],
		cCuponFiscal[17],
		cMotivo[51],
		cNumerotarjeta[14],
		cNumeroDetarjeta[18];

	int iSistemaOriginal,
		iCaja,
		iCajaOriginal,
		iCajaxArea,
		iSistema,
		iTarjetaArgenta,
		iAmex,
		iMonto,
		iPostFijoTarjeta,
		iTransaccionNumero,
		iLote,
		iCupon,
		iTiendaCupon,
		iMotivo,
		iHostTicketNumber,
		iMontoMuebles,
		iMontoRopa;

	short iMovimiento,
		iNumCuotas,
		iVentaUnificada;

	long lCliente,
		lFactura,
		lPagoPesos,
		lEmpleado,
		lPagoDlls,
		lReciboCaCarmov,
		iCuenta,
		lValor,
		lFolio,
		lNumOrdenNUBE,
		lFolioNota,
		lCostofinanciamiento,
		lCostofininteres,
		lArancel,
		lCostofinanciamientor,
		lCostofininteresr,
		lArancelr,
		lCostofinanciamientom,
		lCostofininteresm,
		lArancelm,
		lMontoCashBackMuebles,
		lMontoCashBackCajas,
		lMontoCashBackRopa;
	int64_t lIdPagoMp;
};

struct sComplementarCCuenta
{
	int iNumcliente;
	int idNumCalle;
	int idNumColonia;
	int idNumCiudad;
	int idIngresos;
};

struct sRespuestaComplementarCCuenta
{
	int iNumPuntosCoppel;
	int iNumEdad;
	char cNomCalle[32];
	char cNomColonia[32];
	char cNomCiudad[32];
};

struct sSc3Telefonos
{
	long lCliente;
	long lEmpleado;
	long iTipoCliente;
	long iOportunidad;
	long iArea;
	char cArea[3];
	long iCaja;
	long iEscenarios;
	long iFlagTelefono;
	int iFlagDescuentoEspecial;
	char cPuntualidad[3];
	char cNombre[40];
	char cApellidoPaterno[40];
	char cSexo[3];
	char cSituacionEspecial[3];
	int iCausaSitEsp;
	long iRespuesta;
	long iRegresa;
	long iTienda;
	char cMensaje[512];
	char cFuncion[128];
	char cApellidoCliente[40];
	int iMsg;
	char cMsg01[128];
	char cMsg02[128];
	char cMsg03[128];

	char cNombreCorreo[100];
	char cDni[20];
	char cMensajeValidarCorreo[200];

	long iFlagHuellaValor;
};
struct InfoFE
{
	long lComprobanteFecha;
	char cTipoComprobante[3];
	int64_t iNroTransaccion;
	int64_t iNroTransaccionConfirmado;
	long lNroOperacion;
	char cTipoDocumento[3];
	char cDocumentoNro[12];
	double dImporteTotal;
	double dImporteNetoNoGravado;
	double dImporteNeto;
	double dImporteExcento;
	double dImporteTributo;
	double dImporteIVA;
	double dAlicuotaIIBB;
	double dBaseImponibleIIBB;
	double dImporteIIBB;
	char cTipoTributoIIBB[3];
	double dAlicuotaII;
	double dBaseImponibleII;
	double dImporteII;
	char cTipoTributoII[3];
	double dBaseImponible3;
	double dImporte3;
	char cTipoIVA3[3];
	double dBaseImponible4;
	double dImporte4;
	char cTipoIVA4[3];
	double dBaseImponible5;
	double dImporte5;
	char cTipoIVA5[3];
	char cTipoComprobanteAs[3];
	long lPuntoVentaIdAs;
	long lNumeroComprobanteAs;
};

struct InfoFactura
{
	long lFolioFactura;
	bool bPercibeCABA;
	int iCantidadArticulos;
	long lTotalFactura;
	long lTotalFacturaGE;
	long lIIBBPercepcionACobrar;
	bool bPercibeCABAFin;
	int iAlicuotaIIBB;
	long lIIBBPercepcionImpresion;
	long lImporteVtaSinImpuestos;
	long lTotalImporteDescuento;
	long lImporteDescuentoCredito;
	long lPagoPC;
	long lPuntosCoppel;
	char cMotivoPercepcion[5];
	char cProvinciaPercepcion[5];
	char cAlicuotaIB[10];
	char cQuienEntregaGlobal;
	int iCiudadTienda;
	int iCiudadCapturada;
	long lZonaNumero;
	char cZonaNombre[20];
	char cCalleNombre[15];
	char cDepto[4];
	long lCalleNumero;
	long lCasaNumero;
	char cComplemento[30];
	int iFlaguhc;
	int iUhcmanzana;
	int iUhcotros;
	int iUhcandador;
	int iUhcetapa;
	int iUhclote;
	int iUhcedificio;
	int iUhcentrada;
	int64_t i64Telefono;
	long lLocalidad;
	int iFlagMismaCiudad;
	char cObservaciones[80];
	bool bCteCeroCred; // se renombra por vulnerabilidad
	bool bAplicaCLCC;
	long lPrecioUnitario;
	bool bDctoBienvenida;
	int iTomaReembolso;
	int iFlagPzo18;
	long lImporteDescuentoEmpleado;
	int iDiaEntrega;
	int iMesEntrega;
	int iAnioEntrega;
	int iNuevaTasaInteres;
	long lFolioPaquete;
	long lNumeroEmpleadoGerente;
	long lPorcentajeCompra;
	long lSobrePrecio18;

	long lVencidoMuebles;
	long lSaldoMuebles;
	long lFactura;
	long lFacturaPendiente;
	int iFlag; // temp

	long lPagoEfectivo;
	long lPagoTarjetaCredito;
	long lPagoTarjetaDebito;
	long lImporteCashBack;
	long lPagoReembolso;
	long lPagoPim;
	long lPagoFinanciera;
	long lNumeroDolar;
	double dPagoCheque;
	double dPagoDolaresPesos;
	double dPagoTarjetaPlata;
	double dCambio;
	char cFinanciera[24];
	char cCuponReembolso[26];
	long lCambio;
	char cCuponPosnet[14];
	long lMercadoPago;
	long lEnganche;
	long lPrecioConDescuento;
	bool bDctoOriginal;
	bool bbAplicaCLCC;
	long lEnganchePropuesto;

	char cMensaje[256];
	int iFlagObligado;
	int iFlagMostrarDetalle;
	bool bContadoEspecial;
	int iAntiguedadMeses;
	int iPorcentajeDePagoInicialAR;
	int iPuntosPrecalificasionCN;
	int iSumaParametrico;
	long lTotalGEParametrico;
	long lLineaCredito;
	int iMensajeCteExcedido;
	int lLineaDeCredito;
	float fAlicuota;
	char cMotivoPercepcionib[5];
	long lTotalConDescuento;
	long lTotalCredCB; // se renombra por vulnerabilidad
	char cPresupuesto[6];
	long lLineaRealCredito;
	long lEngancheRecibido;
	int iFlagPlazo18;
	int iFlagCteS50;
	long lPiSituacionS50;
	long lExcesoCompra;
	long iCteNEspecial;
	bool bFlagPuntualidadRiesgo;
	long iClienteExcedido;
	int iDiasTransPrimerCompra;
	long lExcesoTopeMaximo;
	int iPagos12Meses;
	int iNuevoSaldo;
	int iPagosVsSaldo;
	long lSobrePrecioTotal;
	long lEnganchePropuestotmp;
	int iPuntajeFinalParAltoRiesgo;
	int iUltimoDescuentoMuebles;


	//Mensaje 27
	long 	iTopeMaximoSaldos;
	bool	bTramitaLineaBlanca;
	bool 	bClieneContadoLCC;
	bool	bFlagTramita;
	bool	bReglaTopesActiva;
	int		iTramiteCred;
	int		iFlagCteNRegistrado;
	int 	iFlagMensajeTramitar;
	bool	bFlagClubPtoteccion;
	int 	iTotalAlicuota;
	long 	lImporteReembolso;
	int 	iFlagAbonoMensual;
	int 	iFlagLineaBlanca;
	bool	bCumplePorcentTramite;
	int		iTotalVentaLineaBca;
	long	lFactorLinea;
	int		iNumMensaje;

	//Mensjae 23 tramitadas
	bool bINit;
	char cDescripcionTramitado[35];
	int iNumero1;
	int iNumero2;
	int iNumero3;
	int iNumero4;
	int iNumero5;
	int iNumero6;
	int iNumero7;
	int iNumero8;
	int iNumero13;
	int iNumero14;
	int iNumero15;
	int iNumero17;
	int iFlagEsMoto;
	int iStatusTramitado;
	int iFlagFacturaPendiente;
	long lMinimoMuebles;
	long lCodigoTramitado;
	long lImporteTramitado;

	// variables para nuevo domicilio
	char descripcionCiudad[35];
	char descripcionZona[35];
	int idNumeroCasa;
	int idDepartamento;
	char descripcionCalle[35];
	char entreCalles[50];
	char telefonoCasa[10];
	int telefonoCel;
	int idzona;
	int idcalle;
	int flagcambiodomicilio;
	char cReferencia[80];
};

struct InfoNota
{
	long lNota;
	long lNotaPendiente;
	long lSaldoNuevoRopa;
	int iCantidadArticulos;
	int iCantidadArticulosDev;
	int iFlagCambio;
	bool bEsCambio;
	bool bEsEmpresa;
	long lEnganchePropuesto;
	long lTotalNota;
	long lIIBBPercepcionACobrar;
	bool bPercibeCABA;
	bool bPercibeCABAFin;
	bool bDevolucionIIBB;
	int iAlicuotaIIBB;
	int iTipoMsjDescuento;
	long lIIBBPercepcionImpresion;
	long lImporteVtaSinImpuestos;
	long lTotalImporteDescuento;
	long lImporteDescuentoCredito;
	long lTotalImporteDescuentoCambio;
	long lImporteDescuentoEmpleado;
	long lImporteDescuentoEmpleadoCambio;
	long lPagoPC;
	long lEngancheRecibido;
	long lSobrePrecioTotal;
	long lTotalNotaCambio;
	long lNuevoAbonoMensualRopa;
	long lNuevoMinimoRopa;
	long lTotalDescuentoDevPC;
	long lPuntosCoppel;
	int iTasaInteresRopa8x;
	bool bVtaDescUniformeEmp;
	bool bReglaTopesActiva;
	bool bDescuentoJugueteria;
	bool bAjustarMontoDescuentoNino;
	int iVtaDiaNino;
	int iTiendaOrigNino;
	long lNotaorigNino;
	int iCajaOrigNino;
	int iDescJuguetesCambio;
	int iTasaInteresRopaVtaOrig;
	bool bDevolucionContado;
	int iTipoDev;
	long lTotalCompensacion;
	char cMotivoPercepcion[5];
	char cProvinciaPercepcion[5];
	char cAlicuotaIB[10];
	long lPagoEfectivo;
	long lPagoTarjetaCredito;
	long lPagoTarjetaDebito;
	long lImporteCashBack;
	long lPagoReembolso;
	long lPagoPim;
	long lPagoFinanciera;
	long lNumeroDolar;
	double dPagoCheque;
	double dPagoDolaresPesos;
	double dPagoTarjetaPlata;
	double dCambio;
	char cFinanciera[24];
	char cCuponReembolso[21];
	long lCambio;
	char cCuponPosnet[14];
	long lMercadoPago;
	int iFalgCredito;
	long lFolioNotaPendiente;
	long lVencidoRopa;
	bool bDevolucionArgenta;
	int iNumero1;
	int iNumero2;
	int iNumero3;
	int iNumero4;
	int iNumero5;
	int iNumero6;
	int iNumero7;
	int iNumero8;
	int iNumero9;
	int iNumero13;
	int iNumero14;
	int iNumero15;
	int iNumero17;
	int iImpresion;
	long lImportePuntos;
	long lCargoCredito;
	int iCantidadArticulosPorCodigo;
	long iTotalCantidadDev;
	long lEnganchePropuestotmp;
	int iUltimoDescuentoRopa;
	char cTipoMovimientoRopa[3];
	int iNumCalle;
	char cCalleNombre[17];
	int iIdZona;
	char cZonaNombre[22];
	int iNumCasa;
	char cComplemento[32];
};

struct InfoCodigosInteres
{
	long lCodigo;
	short iCantidad;
	char cDescripcion[30];
	long lImporte;
	double dTasaIva;
};
struct InfoCodigosInterescf
{
	long lCodigo;
	short iCantidad;
	char cDescripcion[15];
	double dImporte,
		dTasaIva;
};
struct InfoDatosVenta
{
	int iFlagVentaRopa;
	int iFlagVentaMuebles;
	int iMesesPC;
};

struct InfoGrabarVentaReq
{
	int iOpcion;
	long lEmpleado;
	long lEmpleadoAutorizo;
	long lCajero;
	long lFecha;
	int iVentaHuella;
	long lClienteContado;
	int iPuntosParametrico;
	int iPuntosIniciales;
	int iPuntosPrecalificacion;
	long lSaldoParametrico;
	long lCliente;
	char cPuntualidad;
	int iFlagDescuentoEspecial;
	long lSaldoRopa;
	long lVencidoTotal;
	long lFechaUltimaCompraRopa;
	long lFechaUltimaCompraSysMuebles;
	char cIPwshasar[17];
	// char    cIPTienda           [17];
	// char    cDBTienda           [32];
	// char    cUsuarioDB          [32];
	char cNombreCliente[47];
	char cApellidopaterno[17];
	char cApellidomaterno[17];
	char cIPCarteraCliente[17];
	char cFEDevolucion[14];
	char cCupon[12];
	char cAutorizarMicroCredito[3];
	long lNumeroEmpleadoVendedor;
	int iNumeroVendedor;
	int iTipoComprador;
	bool bEsEmpresa;
	int iFlagPrimerCompra;
	int iDescuentoEspecial;
	int iTipoCteLCC;
	long lLineaCliente;
	char cDocumento[14];
	long lImporteBonificacionNueva[9];
	long lFechaBonificacionNueva[9];
	int iFlagHuella;
	int iDescuentoAplicado;
	int iNumeroEmpresa;
	long lColaborador;
	int iCampania;
	int iFlagGrabarAutorizacion;
	int iGerenteAdicional;
	int iFlagExterno;
	long lGerenteAutorizoEmpresaExterna;
	long lGerenteHuella;
	long lEmpleadoAutorizoHuellaCliente;
	int iGrabarAH;
	int iCuentasActivas;
	int iCuentasActivasMuebles;
	long lVencidoPrestamos;
	char cClienteAnexo;
	int iReposicionDeTarjeta;
	long lPuntosConsumoLinea;
	int iLimiteCredito;
	int iFlagCredito;
	long lClienteSDV;
	char cSituacionEspecial[3];
	int iCausaSituacionEspecial;
	int iUHCManzana;
	int iPuntajeParametricoRopa;
	long lSaldoMuebles;
	long lSaldoTiempoAire;
	long lSalarioMinimo;
	long lSaldoPrestamos;
	char sComentarios[128];
	int iReconocimiento;
	int iFlagPreguntas;
	int iDescuentoEspecialCliente;
	long lBaseTotal;
	long lIntAdicional;
	bool bFlagCalculos;
	int iFlagLineaCreditoEsp;
	int iFlagLineaCreditoReal;
	char cArea[3];
	int iPorcentajePiSistema;
	int iFlagGrabarTirasBD;
	int iContNotaPendiente;
	long lMinimoRopa;
	long lBaseRopa;
	int iIdCiudad;
	int iIdCalle;
	int iIdColonia;
	int iFlagCteForaneo;
	char cDni[10];
	int iTipoDescuento;
	long iTipoOrigenCliente;
	int iLimiteDeCred;	 // se renombra por vulnerabilidad
	long lLineaRealCred; // se renombra por vulnerabilidad
	long lPesoUnidadCred;
	long lSaldoFactorizadoFinal;
	long lSaldoFactorizadoTotal;
	int iFlagTiendaZonaLibre;
	int iFlagSobreStock;
	int iNumCaja;
	int iNumTienda;
	long lSaldoFactorizado;
	int iPlazoMuebles;
	int iPlazoRopa;
	int lLineaDeCredReal; // se renombra por vulnerabilidad
	long lFactorLinea;
	char cFechaAlta[10];
	bool bPaquetePromocion;
	int iPorcentajePiDec27;
	long lSaldoTotal;
	long lExcesoCompra;
	long lExcesoTopeMaximo;
	long lPagoPCRopa;
	long lPagoPCMuebles;
	int iPorcentajeCompraNvo;
	int iSumaParametrico;
	int iSMC;
	int iVSMCCte;
	// esta variable no se usa (iVSMCCteNvaVta), esta en el msn 23
	int iVSMCCteNvaVta;
	int iVSMCCteNvaVtaRopa;
	int iVSMCCteNvaVtaMuebles;
	int iSaturacionCte;
	int iSaturacionCteNvaVta;
	int iFactorTopeMaximo;
	long lMargenCreditoEmpleado;
	long lEngancheRecibido;
	int iVtaAccesorioCel;
	bool bContadoEspecial;
	int iDescuentoClienteCero;
	bool bFlagVentaEmpleado;
	int iFlagCapturarDescripcion;
	int iFlagPagoSugerido;
	int iCuentasSaldoMuebles;
	int iCuentasActivas30;

	int iFlagBodegaRemates;
	long lEnganchePropuesto;
	bool bCuentas30Dias3000;
	int iSeTramita;
	int iFlagFuturo;
	long lLineaCreditoPesos;
	int iFlagVentaPaquete;
	long lPuntosParIniciales;
	int iDiasTransUltimaCompra;

	bool bVigenciaLCC;
	bool bStatusLCC;
	bool bTiendaLCC;
	int iFlagVentaCaida;
	int iClienteEspecial;
	long lPorConsumoLinea;
	long lAbonoPromedio;
	long lParRiesgoMuebles;
	long lParRiesgoMuebles2;
	long lFechaAlta;
	int iCiudad;
	/// Reemboslo
	long lNumFactReembolso;
	long lImporteReembolso;
	long lDevolucionFac;
	int iKeyxReembolso;
	bool bClienteForaneo;
	int iTiendaReembolso;
	int iTiendaCupon;
	long lEmpleadoValida;
	int iClvStatusReembolso;
	bool bReactivado;
	char cPresupuesto[7];
	long lValorReembolso;
	long lFacturaReembolso;
	long lEmpleadoReactivo;
	char cCuponPosnet[14];

	long lMinimoMuebles;
	long lVencidoMuebles;
	long lImporteDoctoxCobrar;

	int iPorcentajePiDec27Muebles;
	int iPorcentajeDePagoInicialAR;
	int iSaturacionCteNvaVtaMuebles;
	long lExcesoCompraMuebles;
	int iPorcentajeCompraNvoMuebles;
	int iAntiguedadMeses;
	long lExcesoTopeMaximoMuebles;
	bool bEsMixta;
	bool bDescuentoDiaNinio;
	int		iFlagEsExento;

	InfoFactura factura;
	InfoNota nota;
};

struct InfoGrabarPrestamo
{
	long lNota;
	long lNotaPendiente;
	long lFactura;
	double dImporteIVA;
	int64_t iNroTransaccion;
	char cPresupuestoRopa[8];
	char cPresupuestoMuebles[8];
	char cTipoComprobante[3];
	char cResultado[3];
	char cCertificado[15];
	char cModo[5];
	char cCaeFechaVto[11];
	char cFechaProceso[50];
	char cCuponFiscal[14];
	char cSerieFiscal[3];
	char cPDV[6];
	char cGrupoTransaccion[16];
	char cParcelaTitulo[3];
	char cTipoTitulo[5];
	char NumTituloRopa[9];
	char NumTituloMuebles[9];
	short iCantidadCodigos;
	InfoCodigosInteres codigoInteres[6];
};

struct sRegalo
{
	int flagagotarexist;
	char cAgotadoInvent[1],
		cQuienEntrega[1],
		cFlagApartado[1];
};

struct ventaCaida
{
	int iCaja,
		iArea,
		iTienda,
		iClaveCausa,
		iCausaSitEsp,
		iRespuestaCred,
		iRespuestaCred2,
		iFlagAccion,
		iFlagVentaCaida,
		iClienteEspecial;
	long lCliente,
		lFolio,
		lPagoInicial,
		lPagoInicialCte,
		lPagoInicialCred,
		lSaldoCte,
		lVencido,
		lFolioTramite,
		lFolioFactura,
		lPorConsumoLinea,
		lPuntajeFinalParam,
		lEmpleado,
		lImporteVenta;
	char cSitEspecial[3],
		cPuntualidad[3],
		cHuellaInvalida[3],
		cBancoTarjeta[16],
		cCondicionTramite[80],
		cFechaIniciaVenta[20],
		cFechaTerminaVenta[20],
		cFechaIniciaTramite[20],
		cFechaTerminaTramite[20];
};

struct ReconocimientoCompra
{
	char cCuponFiscal[14];
	char cArea[2];
	long lImporteVenta;
};

struct SSorteo
{
	int iFlagSorteoLc,
		lMontoDeCompra,
		iFlagSorteoRc,
		iFlagSorteoDm,
		iPremioSorteo,
		iFlagctecontado,
		lTotalNotaMuebles,
		lTotalNotaRopa,
		iSobrePrecioMuebles,
		iSobrePrecioRopa,
		iFlagDescuentoEspecial,
		lFolioNota,
		iFolioFactura,
		mensajesTicket,
		Procedimiento,
		iRespuestaSort,
		iTipoCte;
	char cMunicipio[18],
		cNombreCalle[18],
		cCasa[18],
		cCuponFiscal[18],
		cNombreCiudad[20],
		cEmail[25],
		sNombre[25],
		cDireccion[30],
		nomLocalidad[20],
		cSexo[2];
	long lSaldoFactorizadoTotal,
		lCantOC1,
		lOrdenCompra;
	int64_t iCelular,
		iTelefono;
};

struct SPrestamo
{
	int SaldaCon,
		FechaNacimiento,
		lVencidoTiempoAire,
		lVencidoPrestamos,
		lVencidoRopa,
		lVencidoMuebles,
		iCausaSituacionEspecial,
		VencidoTotal;
	bool CuentaReestructurada;
	char cSituacionEspecial[2];
	char cPuntualidad[2];
	long lSaldoFactorizadoTotal;
};

struct VentaUdis
{
	long lVale;
	int iFlagCapturaVentaUdi;
	short iFlagTiendaZonaLibre;
	short iFlagNoMarcarUdiGenXVr;
	char cSituacionEspecial[2];
	char cQuienEntregaVale[2];
	char cQuienEntregaGlobal[2];
	short iCiudad;
	short iColonia;
	short iCausaSituacionEspecial;
	char cCausaUdi[2];
	int iTotalGrid;
	short iFlagReconstruido;
};

struct Parametrico
{
	long lAbonoPromedio;
	long lEstado;
	int iMesesTranscurridos;
	long lParPrestamo;
	long lParRiesgoMuebles;
	int iPorcentajeCompraNvo;
	int iPorcentajeCompra;
};
struct sVentaTramiteReq
{
	bool bEsCambio;
	bool bCuentas30Dias3000;
	char cHuellaInvalida;
	char cPuntualidad[3];
	char cAutorizarMicroCredito[3];
	char cSituacionEspecial[3];
	int iOpcion;
	int iNumero9;
	int iTipoComprador;
	int iFlagCambio;
	int iVentaHuella;
	int iFlagExterno;
	int iFlagCredito;
	int iTramitar;
	int iReconocimiento;
	int iYearSys;
	int iMesSys;
	int iDiaSys;
	int iCiudad;
	int iTipoDescuento;
	int iFlagLineaCreditoEsp;
	int iCausaSituacionEspecial;
	int iPlazoMuebles;
	int iNumCaja;
	int iNumTienda;
	long lIntAdicTotal;
	long lBaseTotal;
	long lVencidoTotal;
	long lImporteDescuentoCredito;
	long lNumeroEmpleado;
	long lCliente;
	long lTotalNota;
	long lEngancheRecibido;
	long lEnganchePropuesto;
	long lTotalImporteDescuento;
	long lNota;
	long lFolioNotaPendiente;
	long lSaldoRopa;
	long lSaldoMuebles;
	long lSaldoTiempoAire;
	long lSalarioMinimo;
	long iCuentasActivas;
	long lSobrePrecioTotal;
	long lFecha;

	long lFechaAlta;
	long lFechaPrimerCompra;
	long lSaldoFactorizadoMuebles;
	long lSaldoFactorizadoRopa;
	long lLimiteCredito;
	long lLineaRealCredito;
	long lTotalFactura;

	InfoFactura factura;
	InfoNota nota;
};
struct sVentaTramitadaRes
{
	char cAutorizarMicroCredito[3];
	int iTramitar;
	int iNumero1;
	int iNumero2;
	int iNumero3;
	int iNumero4;
	int iNumero5;
	int iNumero6;
	int iNumero7;
	int iNumero8;
	int iNumero9;
	int iNumero13;
	int iNumero14;
	int iNumero15;
	int iNumero17;
	int iFlagCredito;
	int iCreditoVerificar;
	int iFlagFacturaPendiente;
	int iFlagPresupuestoPendiente;
	long lCliente;
	long lEngancheRopa;
	long lEngancheTiendaRopa;
	char cMensajeR[64];
	long lContadoRopa;
	long lContadoMuebles;
	long lFactura;
	long lNotaPendiente;
	long lEngancheMuebles;
	long lEngancheTiendaMuebles;
	char cMensajeM[64];
};
struct sRegistrarProtheus
{
	char cFecha[10];
	char cHora[10];
	char cNombreTabla[10];
	char cTexto[45];
	char cValor[256];
	char cSql[256];
	char cCodigoPais[7];
	char cCuentaContable[22];
	char cCodigoEstado[4];
	char cCodigoMunicipio[7];
	char cNombreCiudadCliente[17];
	char cTexto1[15];
	char cTexto2[15];
	char cTexto3[15];
	char cDatos[15];
	int iPid;
	long lCodigoPostal;
};
struct DatosCajaSudamerica
{
	int iTienda;
	char cArea[3];
	int iCaja;
	char cIp[17];
	long lEmpleado;
	int iMostrarError;
	int iClaveMsj;
	char cEsperarMotor[3];
	char cReferenciaMsj[15];
	char cEmpresa[2];
	char cFilial[2];
	char cParametros[100];
	char cIpWebSrvice[17];
	char cPuerto[12];
	char cPais[2];
	char cNFOriginal[13];
	char cSerieOriginal[4];
	char cIpProtheus[17];
	char cBDProtheus[27];
};
struct RecibeFEPrestamos
{
	int		iOpcion;
	int 	iTienda;
	char	cComprobanteFecha[15];
	int		iTipoComprobante;
	long	i64NroTransaccion;
	long	i64NroTransaccionConfirmado;
	int		iNroOperacion;
	int		iTipoDocumento;
	long	i64DocumentoNro;
	long	lImporteTotal;
	long	lImporteNetoNoGravado;
	long	lImporteNeto;
	long	lImporteExcento;
	long	lImporteTributo;
	long	lImporteIVA;
	short	iSucursal;
	short	iCaja;
	long	lAlicuotaBaseImponible;
	long	lAlicuotaimporte;
	int		iAlicuotaTipoIVA;
	long	lAlicuotaBaseImponible105;
	long	lAlicuotaimporte105;
	int		iAlicuotaTipoIVA105;
	long	lAlicuotaBaseImponible21;
	long	lAlicuotaimporte21;
	int		iAlicuotaTipoIVA21;
	char	cIpImpresoraHassar[17];
};
struct EnviaFEPrestamos
{
	int 	iCodigo;
	char 	cMensaje[512];
	int 	iPuntoVenta;
    int		iTipoComprobante;
    long 	lNumeroComprobante;
    char 	cResultado[4];
    char 	cCae[16];
    char 	cCaeFechaVto[15];
    char 	cCaea[16];
    long	i64NroTransaccion;
    char 	cFechaProceso[27];
	char	cCuponAsociado[14];
};


struct InformarCamposPa9
{
	char Pa9_filial[4];
	char Pa9_cod[10];
	char Pa9_loja[4];
	char Pa9_pessoa[3];
	char Pa9_nome[42];
	char Pa9_nreduz[22];
	char Pa9_end[42];
	char Pa9_tipo[3];
	char Pa9_est[4];
	char Pa9_mun[17];
	char Pa9_bairro[32];
	char Pa9_cep[10];
	char Pa9_tel[17];
	char Pa9_pais[5];
	char Pa9_conta[22];
	char Pa9_perciv[3];
	char Pa9_agenpe[3];
	char Pa9_rg1415[3];
	char Pa9_dtgrv[10];
	char Pa9_hrgrv[10];
	char Pa9_tipope[3];
	char Pa9_grptra[17];
	char Pa9_rg[17];
};
struct CCrClienteContado
{
	long clientecontado;
	char nombre[17];
	char apellidopaterno[17];
	char apellidomaterno[17];
	char sexo[3];
	// SqlTimeStamp        fechanacimiento;
	char estadocivil[3];
	short int ciudad;
	short int colonia;
	long calle;
	long casa;
	char rumbo[3];
	char complemento[32];
	short int flaguhc;
	short int uhcmanzana;
	short int uhcotros;
	short int uhcandador;
	short int uhcetapa;
	short int uhclote;
	short int uhcedificio;
	short int uhcentrada;
	char numdeptoointerior[6];
	int64_t telefono;
	int64_t telefonocelular;
	char dni[10];
};

struct xInfoCliente
{
	char cSituacionEspecial,
		cPuntualidad;
	int iCausaSituacionEspecial,
		iCiudad;
	long lCliente;
};
struct globalEnviroment
{
	bool bAplicaCLCC,
		bCteCeroCred, // se renombra por vulnerabilidad
		bFlagMostrarMsgOftaUnica,
		bReglaTopesActiva;

	int iTipoComprador,
		iTipoOrigenCliente,
		iFlagOFtaUnica,
		iCodigoDobleDesGE,
		iTipoDescuento,
		iSMC;
	short iFlagMismaCiudad,
		iPorcientoDescuentoEmpleado;
	long lTotalConDesc;
};

struct OfertaUnica
{
	long lCodigo,
		lImporte,		   // Futuro
		lFechaInicio,	   // aaaammdd  Futuro
		lFechaTerminacion; // aaaammdd  Futuro
	short iTienda,
		iPorcentaje;
	char cFlagMovto,	   // 1=Se hizo movto de entrada o salida no se aplica el descto.
		cFlagEtiqueta;	   // 1=Ya se imprimió Etiqueta
	long lFechaAntiguedad; // aaaammdd
};



struct sRespuesta24_QuienEntrega
{
	InfoCodigoMuebles facturaMovimiento;
	globalEnviroment sEnviroment;
	char cQuienEntregaGlobal;
	SysMuebles sSysMuebles;
	char cFlagApartado;
};

struct sSolicitudPim // Datos para la peticion PIM
{
	int iMensaje;
	int iOperacion;
	int iTienda;
	char cArea[3];
	int iCaja;
	long lFolio;
	long lCliente;
	long lFecha;
	char cIpPim[20];
	char cDocumento[20];
	char cCelularOrigen[20];
	long lMonto;
	char cIpTienda[17];
	char cIdTransaccion[62];
	int iClavePim;
};

struct sRespuestaPim
{
	char cStatusPim[64];
	int iCodigoResultado;
	char cCodigoErrorId[64];
	char cResultadoTexto[255];
	char cIdTransaccion[255];
};
struct sRespuestaBuy
{
	int iResultCode,
		iHostResultCode,
		iSession,
		iHostTicketNumber,
		iAccountType,
		iTransactionInstallments,
		iHostIdentification,
		iHostBatchNumber,
		iTransactionAmount,
		iTransactionCashbackAmount,
		iIssuerEntity,
		iInserted,
		iUpdated,
		iTienda,
		iCaja,
		iSistema,
		iMontoCashRopa,
		iMontoCashMuebles,
		iMontoCashCajas;

	long lCliente,
		lImporte;

	char cCuponFiscal[14],
		cDigitos[7],
		cFecha[12],
		cTarjetanombre[32],
		cResultMessage[101],
		cDeviceType[41],
		cTransactionResolutionMode[8],
		cTransactionCurrencyCode[4],
		cDeviceIntegratorVersion[9],
		cWorkstationInfo[101],
		cHostResultMessage[51],
		cTransactionRequestType[19],
		cTransactionResponseType[19],
		cTransactionDate[11],
		cTransactionTime[9],
		cCardType[2],
		cCardTypeDescription[9],
		cPaymentMethodDescription[13],
		cMerchantPaymentMethodID[5],
		cMerchantPaymentMethodType[5],
		cMerchantPaymentMethodSupportsCashback[2],
		cCardNumber[21],
		cCardInputMode[2],
		cCardInputModeDescription[15],
		cHostAuthorizationCode[7],
		cTransactionCurrencySymbol[4],
		cAccountTypeDescription[30],
		cTransactionFacilitiesType[2],
		cHostMerchantIdentification[16],
		cHostTerminalIdentification[9],
		cReceiptNumber[13],
		cLastContractVersionAvailable[12],
		cContractVersion[12],
		cResponseActions[51],
		cCuponPosnet[14];
};

struct sRespuestaVoid
{
	int iResultCode,
		iHostResultCode,
		iSession,
		iHostTicketNumber,
		iAccountType,
		iTransactionInstallments,
		iHostIdentification,
		iHostBatchNumber,
		iCustomerPhone,
		iOperationCode,
		iOriginalTicketNumber,
		iIssuerEntity,
		iTransactionAmount,
		iTransactionCashbackAmount,
		iInserted,
		iUpdated,
		iTienda,
		iCaja,
		iSistema;

	long lCliente,
		lImporte;

	char cCuponFiscal[14],
		cDigitos[7],
		cFecha[12],
		cTarjetanombre[32],
		cResultMessage[101],
		cHostResultMessage[51],
		cTransactionResponseType[19],
		cTransactionDate[11],
		cTransactionTime[9],
		cCardType[2],
		cCardTypeDescription[9],
		cPaymentMethodDescription[13],
		cMerchantPaymentMethodID[5],
		cMerchantPaymentMethodType[5],
		cMerchantPaymentMethodSupportsCashback[2],
		cCardNumber[21],
		cCardInputMode[2],
		cCardInputModeDescription[15],
		cHostAuthorizationCode[7],
		cTransactionCurrencySymbol[4],
		cAccountTypeDescription[30],
		cTransactionFacilitiesType[2],
		cHostMerchantIdentification[16],
		cHostTerminalIdentification[9],
		cOriginalDate[11],
		cReceiptNumber[13],
		cPhoneCompanyIdentification[4],
		cPhoneCompanyDescription[10],
		cLastContractVersionAvailable[12],
		cContractVersion[12],
		cResponseActions[51],
		cTerminalIdentification[9];

	char cCuponPosnet[14];
};

struct sSolicitudGuardarPos
{
	int iSistema,
		iCajaTMP,
		iMovimiento,
		i64Cuenta,
		iTransaccionNumero,
		iNumCuotas,
		i16Manual,
		iMontoMuebles,
		iMontoRopa;

	long lCliente,
		lImporte,
		lEmpleado,
		lPostfijoTarjeta,
		lFactura,
		lLote,
		lCupon,
		lLotDefinition,
		lImporteCashBack;

	char cMarca[34],
		cCodigoAutoriza[22],
		cAdm[6],
		cCuponFiscal[14],
		cCuponPosnet[14];
	short iVentaUnificada;

	float dMontoMuebles,
		dMontoRopa;
};

struct sRespuestaReturn
{
	int iResultCode,
		iHostResultCode,
		iSession,
		iHostTicketNumber,
		iAccountType,
		iTransactionInstallments,
		iHostIdentification,
		iHostBatchNumber,
		iCustomerPhone,
		iOperationCode,
		iOriginalTicketNumber,
		iIssuerEntity,
		iTransactionAmount,
		iTransactionCashbackAmount,
		iInserted,
		iUpdated,
		iTienda,
		iCaja,
		iSistema;

	long lCliente,
		lImporte;

	char cCuponFiscal[14],
		cDigitos[7],
		cFecha[12],
		cTarjetanombre[32],
		cResultMessage[101],
		cHostResultMessage[51],
		cTransactionResponseType[19],
		cTransactionDate[11],
		cTransactionTime[9],
		cCardType[2],
		cCardTypeDescription[9],
		cPaymentMethodDescription[13],
		cMerchantPaymentMethodID[5],
		cMerchantPaymentMethodType[5],
		cMerchantPaymentMethodSupportsCashback[2],
		cCardNumber[21],
		cCardInputMode[2],
		cCardInputModeDescription[15],
		cHostAuthorizationCode[7],
		cTransactionCurrencySymbol[4],
		cAccountTypeDescription[30],
		cTransactionFacilitiesType[2],
		cHostMerchantIdentification[16],
		cHostTerminalIdentification[9],
		cOriginalDate[11],
		cReceiptNumber[13],
		cPhoneCompanyIdentification[4],
		cPhoneCompanyDescription[10],
		cLastContractVersionAvailable[12],
		cContractVersion[12],
		cResponseActions[51],
		cTerminalIdentification[9];
};

struct sSolicitudAnulacion
{
	char cCantidadLeida[40],
		sFechaTrx[10];
	int iPrimerosDigitos,
		iUltimoDigitos;
};

struct sconsultaTdConfiguracion
{
	char cRegresa[15],
		cValor[256],
		cPregunta[256],
		cMensaje[256];
	int iContadorTicketge;
	int iContinuarVenta;
};

struct sconsultaTdConfiguracionPrestamos
{
	char cDescMensaje[400];
	int iNumeroMensaje;	
};

struct sRespuestaVentCaida
{
	int lFolio;
	char cFechaIniciaVenta[20];
};

struct sconsultarFlagMercadoPago
{
	char cRegresa[15],
		cValor[256];
	int iContadorTicketge;
};

struct infoCodigo
{
	char cQuienEntrega[2];
	char cImportacion[2];
	int i16Cantidad;
	int iFlagApartado;
	long lCodigo;
	int iStatus;
};

struct CancelarTramitada
{
	int iSistema;
	int iTienda;
	long lCliente;
	long lNota;
	long lNotaPendiente;
	long lFactura;
	long lEngancheF;
	long lEngancheN;
	long lConvDevolucion;
	int iCondicioncr1F;
	int iCondicioncr2F;
	int iCondicioncr1N;
	int iCondicioncr2N;
	char cArea[3];
	int iFlagVtaCaida;
	int iFlagAccion;
};

struct DineroElectronico
{
	long lNota;
	long lFactura;
	long lFecha;
	int iFlagCambio;
	int iMegaPuntosMuebles;
	int iMegaPuntosRopa;
	int iEnganchePropuestoMuebles;
	int iEnganchePropuestoRopa;
	int iEngancheMuebles;
	int iEngancheRopa;
	int iTotalMuebles;
	int iTotalRopa;
	int iTotalCreditoMuebles;
	int iTotalCreditoRopa;
	int iTasaInteresMuebles;
	int iTasaInteresRopa;
	int iTotalPuntosMuebles;
	int iTotalPuntosRopa;
	int PorcentajeGastoMPMuebles;
	int PorcentajeGastoMPRopa;
	int MinimoCompraMPMuebles;
	int MinimoCompraMPRopa;
};

/*1195 INICIO*/
// REIMPRESIÓN FACTURAS
struct formaFacturas
{
	char cuponfiscal[13];
	int num_factura;
	int num_nota;
	char presupuestomueble[7];
	char presupuestoropa[7];
	int num_cliente;
	char nom_cliente[21];
	char ape_cliente[21];
	char num_dni[18];
	char des_articulo[41];
	int num_importe;
	int num_pagoinicial;
	char ticket[8192];
	short int num_tipoticket;
	char fec_impresion[17];
	char fec_factura[17];
	short int tienda;
};

// NOTAS ROPA
struct infoNotasRopa
{
	char presupuestoArticuloRopa[6];
	int clienteArticuloRopa;
	int importeArticuloRopa;
	int engancheArticuloRopa;
	int empleadoArticuloRopa;
	char nombreclienteArticuloRopa[60];
	char marcaArticuloRopa[50];
	int codigoArticuloRopa;
	short int cantidadArticuloRopa;
	int preciounitarioArticuloRopa;
	short int tallaArticuloRopa;
	int ivaArticuloRopa;
	int totalArticuloRopa;
	char fec_factura[17];
};

struct sInfoCodigoVentaFuturo
{
	long lCodigo;
	int iCantidad;
	char cQuienEntrega[3];
	char cImportacion[3];
	int iFlagApartado;
	int iStatus;
};

struct sVentaFutura
{
	int iModo;
	// int iTamStruc;

	int iElementos,
		iStatus,
		iTiendaApa,
		iConsultaCancela,
		iFlagDesplegarPant,
		iDiaActual,
		iMesActual,
		iAnioActual,
		iCiudad,
		iNumCiudadApartado,
		iVentaCredito,
		iCantidad,
		iFlagApartadoBodegam; // Se agrega el Flag para saber cuales articulos afectaron el disponible del Bodegam -

	long lCliente,
		lCodigo,
		lFolioApartado,
		lFactura,
		iFlagTiendaZonaLibre;

	bool bFuturo;

	////////////////////////////////////
	int iFlagApartado,
		iBodega,
		iColoniaZona,
		iTotalCodigos,
		iFamilia;

	long lZonaNumero;
	infoCodigo infoCodigoF;

	char cQuienentrega[3],
		cFlagentregafuturo[3];
};

struct sDatosGarex
{
	char 	tipocertificado [3],
			numsolicitud [20],
			vendedor [30],
			tienda [25],
			dni [9],
			nombre [50],
			direccion [50],
			ciudad [50],
			codigopostal [25],
			provincia [50],
			telefono [20],
			moneda [1],
			fechagarex  [9],
			marca [50],
			modelo [30],
			serie [30],
			expuesta  [3],
			sujetoobligado  [3],
			registro [3],
			estadocivil  [3],
			fechanacimiento  [9],
			genero  [2],
			nacionalidad [3],
			cuit_cuil [12],
			correo [50],
			ocupacion [50];
	
	long	importe,
		 	precio;

	int		garantia,
			mesesgarex,
			factura,
			tipopago,
			numeromensualidad,
			mensualidad,
			monedapago,
			valorfinanciado,
			numautorizacion,
			iSku,
			iCodigoassurant;
	short	iGarantiaprov;
};
struct sGabadoR
{
    int num_tienda ,
    num_factura ,
    num_cliente ,
	num_sku ;
	char des_presupuesto [7],
	des_nombre_autoriza [21],
	des_nombre_apellido [21],
	des_descripcion [61] ;

};
//Siempre el campo infoGrabarVentaReq de la estructura sSolicitudServicio debe de ser el ultimo para que el memset a las
//variables de éste tipo de dato funcione correctamente
struct  sSolicitudServicio
{
	int iMensaje;
	char cIpBDCartera[17];
	char cBDCartera[32];
	char cUsuarioCartera[32];
	/*  DATOS DE LA TIENDA */
	char cIpBD[17];
	char cBD[32];
	char cUsuario[32];
	char cIpServidorCred[17]; // se renombra por vulnerabilidad
	char cIpServidorCartera[17];
	char cFechaInicioVenta[19];
	int iYearSys,
		iMesSys,
		iDiaSys;
	char cTipoEvento[64];
	long lNumEmpleado;
	char cIpMicro[17];
	int iNumTienda;
	int iNumCaja;
	int iNumeroProcedimiento;
	int iSysNotaCobro;
	int iCaja;
	int iFlagClienteNunca;
	int opcion;
	int 	liberar;
	/* Tienda Nube ID identificador */
	long lNumOrdenNUBE;
	/* Tienda Nube ID identificador */
	/*  DATOS DEL CLIENTE */
	long lCliente;
	char cDni[23];
	char cApellidoM[40];

	/*  DATOS DEL EMPLEADO */
	long lEmpleado;

	/*  DATOS PARAMETRICOAR */
	int iSaturacionCteNvaVta;
	int iSaturacionCte;
	int iVSMCCte;
	int iVSMCCteNvaVta;
	char cPuntualidad[1];

	//DATO TDCONFIGURACIONPRESTAMO
	char cDescMensaje[400];

	/*DATOS TDCONFIGURACION */
	char cElemento[35];
	char cValor[260];
	bool bCommit;
	int iCiudad;
	int iCalle;
	int iCasa;

	short iCantidadCodigos;

	/* Datos REPEX 1195*/
	int iTipoRepex;
	char cPresupuestoArticuloRopa[6];
	char cPresupuestoArticuloMueble[6];
	int iSku;
	int iCliente;

	/*  ESTRUCTURAS DE ENTRADA */

	/* Facturas reimpresión inicio 1195*/
	int iOpcionReimpresion;
	int iTiendaBusqueda;
	char cCuponFiscal[13];
	char cPresupuestoMuebles[7];
	char cPresupuestoRopa[7];
	char cArticulo[41];
	int iTipoTicket;
	char cTicket[16384];
	char cFechaInicial[17];
	char cFechaFinal[17];
	int iImporte;
	int iPagoInicial;
	bool bContarTickets;
	char iOffsetTickets[5];
	int lSku;
	char lClienteDni[18];
	char cCuponPresupuesto[13];
	int iRopaMueble;
	int iEsUdi;
	int iBuscarCentral;
	formaFacturas sFormaFacturas;
	/* Facturas reimpresión fin 1195*/

	/*Notas ropa 1195 inicio*/
	char presupuestoArticuloRopa[6];
	int clienteArticuloRopa;
	int importeArticuloRopa;
	int engancheArticuloRopa;
	int empleadoArticuloRopa;
	char nombreclienteArticuloRopa[60];
	char marcaArticuloRopa[50];
	int codigoArticuloRopa;
	short int cantidadArticuloRopa;
	int preciounitarioArticuloRopa;
	short int tallaArticuloRopa;
	int ivaArticuloRopa;
	int totalArticuloRopa;
	infoNotasRopa sArticulosRopa;
	/*Notas ropa 1195 fin*/

	/*  ESTRUCTURAS DE ENTRADA */

	/*  ESTRUCTURAS DE ENTRADA */
	sSolicitudHuella sHuellas;
	sComplementarCCuenta sCCuenta;
	Articulo aProducto;
	Articulo lstProductos[50];
	sConsultarDomicilio consultarDomicilio;
	sFormasDePago formasDePago;
	sSc3Telefonos sc3Telefonos;
	sGabadoR		sGabadoRs;
	char cNombre[40];
	char cApellido[40];
	char cSerieTel1[20];
	char cSerieTel2[20];
	int iFoco;
	int iCodigo;
	int iCodigoGE;
	int iAnio;
	int iMes;
	int iDia;
	long lSaldoRopa;
	long lSaldoMuebles;
	long lSaldo;
	int iPlazo;
	int iFlagLineaCreditoEsp;
	int iCteNEspecial;
	int iTipoCreditoCliente;
	int iTipoCtaRM;
	int fecha;
	int folio;
	int iFlagTasasDiferenciadas;
	int iColonia;
	int iFlagRopa;
	int iTotalArticulos;
	char cDiaDeEntrega[3];
	char cMesDeEntrega[3];
	int iNroSucursal;
	char cUltimoNroTransaccion[256];
	char cIPwshasar[17];
	int lImporte;
	int lTotalCompraCF;
	char cTarjetaID[4];
	int lPagoCliente;
	SSorteo DatosSorteo;
	int iTipomovimiento;
	char cArea[1];
	char cInfoCuotas[80];
	long lImporteCostoFinanciero;
	char version_Sistema[32];
	long lFolioApartado;
	long factura;
	char cIpPc[17];
	int iFlagOpcionCaja;
	int 	iTiendaLocal;
	int 	iSecModo;
		/////////1438/////////////
	int iTasaInteresPrestamos;
	int lFacturaAnt;
	int lInteresAdicional;
	char cIpCarteraCliente[32];
	int lSaldoPrestamo;
	char cTipoDoc[4];
	int lInteresFinanciamiento;
	char lFecha[15];
	int importesaldacon;
	int abonoMensual;
	int importetotalAnual;
	int lParPrestamos;
	int iPuntajeParametricoFinal;
	int factorprestamo;
	int tasainteres;
	int iFlagNuevo;
	int lSaldaCon;
	int lFactura;
	int parametricotda;
	int lSaldoAnt;
	int lSaldoActual;
	int lImporteSeguroClub;
	int lSaldoTotal;
	long lMontoMaximoPrestar;
	long abonosCertificado;
	long SaldoCertificado;
	int iFlagHuella;
	long VencidoTotal;
	long SaldoFactorizadoTotalP;
	long margenCreditoReal;
	long lLineaRealCredPesos;
	int iPuntosIniciales;
	int iGrupo;   
	long iSaldo_prestamos12x;
	long iSaldoRopa8x;
	long iSaldoMuebles12x;
	long iSaldoMuebles18x;
	int iSumaPuntajeVariables;
	char iTipoID[3];
	char sDni[11];
	long lPorcentajeIva;
	long lmpuestointerno;
	char lHora[10];
	char fechaSinFormato[15];
	int ipuntajesaldoprestamoanterior;
	double ffactor;
	int iFlagBonificacion;
	//paj
	char cEmpresa[32];
	char cParametros[32];
	char cFilial[32];
	char cData[32]; //tFecha
	short int sMoneda;
	short int sValor; 
	char cNaturez[32];
	char cBanco[32]; //cCajaProtheus
	char cAgencia[32];
	char cCuenta[32];
	char cDocumento[32];
	char cRecPag[32]; //reciboopago
	char cBeneficiario[32];
	char cHistor[32]; //cParametros
	char cTipodoc[32];
	double cTxmoneda;
	char cRateio[32]; //prorrateo
	char cFilori[32]; //filialorig
	char cNumche[32]; //numerocheque
	char cDebito[32]; //debito
	char cCredit[32]; //credito
	char cCd[32]; //centrocostodebito
	char cCc[32]; //centrocostocredito
	char cDtgrv[32]; //tFecha
	char cHrgrv[32]; //lFecha
	char cTipope[32]; //PAJ_TIPOPE
	char cGrptra[32]; //cReferenciaMsj
	//////////////////////////
	sRegalo        DescuentoRegalo;
	SPrestamo         DatosPrestamo;
    ventaCaida		VentaCaida;
    ValidarArticuloMuebles  muArticulo;
    ReconocimientoCompra	reconocimiento;
    Parametrico  parametrico;
    DatosCajaSudamerica datosCaja;
	sSolicitudPim	solicitudPim;
	sRespuestaBuy	respuestaBuy;
	sRespuestaVoid	respuestaVoid;
	sRespuestaReturn respuestaReturn;
	sSolicitudGuardarPos guardarPos;
	sSolicitudFinanciera solicitudFinanciera;
	sSolicitudAnulacion anulacionCliente;
	InfoVentaMoto InfoMoto;
	S00023Respuesta sDatosValidarPagos;
	sVentaFutura sVentaFuturas;
	sInfoCodigoVentaFuturo sInfoCodigoFuturo;
	// Enganche enganche;
	/* 		ESTRUCTURA PAGOS INICIALES		*/
	sDatosPagoInicial datosPagoInicial;
	sVentaTramiteReq ventaTramiteReq;
	VentaUdis ventaudi; /*Muebles*/
	CancelarTramitada sCancelarTramitada;
	DineroElectronico sDineroElectronico;
	sDatosGarex	DatosGarex;
    InfoGrabarVentaReq  infoGrabarVentaReq;		//->>> SIEMPRE DEBE SER EL ULTIMO ELEMENTO DE LA ESTRUCTURA DE sSolicitudServicio EVITA DESBORDES DE MEMORIA
};

struct sConsultarCodigoCiudad
{
	int iNumeroTienda;
	int iExistencia;
	char cArticulo[60];
	char cNombreTienda[30];
	char cDomicilio[30];
	char cTelefono[15];
	long lZona;
};
struct sMueblesinfoTienda
{
	int izona;
	int icalle;
	int icasa;
	char		cZonaNombre [21];
	char		cCalleNombre [16];
};
struct sBusquedaPorNombre
{
	int iCliente;
	char cDni[30];
	char cNombre[30];
	char cApellidoPaterno[30];
	char cApellidoMaterno[30];
};
struct sCambiarVendedor
{
	int iNumeroEmpleado;
	char cNombreEmpleado[60];
	int iNumeroVendedor;
};

struct sDomicilios
{
	int iDomicilio;
	char cDomicilio[60];
};

struct sbusquedaClientePorDni
{
	long lCliente;
	char cDni[35];
};

struct sRespMegaPuntosCoppel
{
	int MINIMO_COMPRA_MP;
	int PORCENTAJE_GASTO_MP;
};

struct sFormaDePagoTarjetas
{
	// int iCodigo;
	char cNombre[41],
		cCodigo[4],
		cTarjetaId[5];
};

struct sFormaDePagoEmisoras
{
	char cCodigo[4];
	char cNombre[41];
};

struct S00225Recibe
{
	short int iClave;
	long lValorSeguridad;
	long lTipoOpcion;
	int nTienda;
	long lCliente;
	long lConvenio;
};

struct S00225Envia
{
	int iEstado;
	int iResultado;

	int iCancelo;
};

struct sRespFormaPagoPrecarga
{
	int flagVentaCaida;
	int flagFinanciera;
	int flagPinPad;
	int iFlagDolares;
	int iFlagTiendaLocal;
	int iFlagTarjetaVtol;
	int iParidadDolar;
	long lDolares;
	long foliocarmov;
	int iFlagCostoFinancieroRopa;
	int iFlagCostoFinancieroMuebles;
	int iMaximoReritoCashBack;
	int iMinimoRetiroCashBack;
};

struct S00019Respuesta
{
	int id;
	char nombre[32];
	char clave[32];
	int dia1;
	int dia2;
	int dia3;
	int dia4;
	int dia5;
	int dia6;
	int dia7;
	int valor;
	int activo;
	int numerotecla;
	int numero_dia;
	int tipodesc;
	int pidedatos;
	int pidehuella;
	int sistema;
};

struct CodigosPaquete
{
	int iPaquete;
	long lCodigo;
	long lPrecio;
	long lDescuento;
	char lf_cr[2];
};

struct DescuentoMuebles
{
	int codigo;
	int preciocontado;
	int preciocredito;
	int codigooferta;
	int preciooferta;
	char fechainicial[12],
		fechafinal[12];
	short flagagotarexist;
	short flagventaminima;
	bool Procedimiento2;
	int lUltimoPrecio;
	int lCodigoOferta2;
	int lPrecioOferta2;
};

struct sDescNinio
{
	long iDescuentoEspecial;
	long iMontoDescuentoNino;
	bool bDescuentoJugueteria;
	bool bDescuentoDiaNinio;
};

struct DescuentoRopa
{
	int iPorcientoDescuento;
	int iPaquetePorcientoDescuento;
	int iTipodescuento;
	bool bPromocion;
	bool bPaquetePromocion;
	sDescNinio DescuentoDiaNinio;
};

struct FacturaPaquete
{
	long lPaquete;
	char cNombrePaquete[30],
		cComplemento1[40],
		cComplemento2[40],
		cComplemento3[40],
		cComplemento4[40];
	long lPrecioInterior,
		lPrecioFrontera,
		lFechaInicial,
		lFechaFinal;
	char lf_cr[2];
	CodigosPaquete sPaquetes[10];
	int totalCodigos;
};

struct MovimientoUdi // DENNIS STRUCTURA DE RESPUESTA DE VALES UDIS
{
	char cStatus[3];
	long lVale;
	short i16Causa;
	long lDcf;
	long lCodigoNuevo;
	char cArticulo[11],
		cMarca[11],
		cModelo[21];
	char cDescripcionDano[45];
	long lPrecioVtaUdi;
	short iDiaReferencia,
		iMesReferencia,
		iAnioReferencia;
	char cNumeroSerieUdi[15];
	short i16FlagMarcaTS;
	long lTes;
	float fTasa12,
		fTasa18;
	short iFlagRiesgo;
	char cQuienEntrega[2];
	int iFlagCapturaVentaUdi;
	char cCveImpuestoSuntuario[5];
	int iIva;
	short garantiaenmeses;
};

struct sRespuestaGarantiaExtendida
{
	long lCodigo,
		lCodigoge,
		lPrecio,
		lDcf;

	char cArticulo[12],
		cMarca[12],
		cModelo[22],
		cModoentrega[3],
		cImportacion[3],
		cAgotado[3],
		iFlagincrementartasa[3];

	int iResp,
		iMessurtir,
		iStock,
		iTasa12,
		iTasa18,
		iExistencia,
		iFlagarmado,
		iTestienda,
		iTesbodega,
		iCelular,
		iDescesp,
		iFlagriesgo,
		iTipo,
		iAnioge;
};

struct sRespuestaArmado
{
	int iCodigo,
		iPrecio;
	char cModelo[22];
};

struct S00027Respuesta
{
	long lCodigoOferta,
		lUltimoPrecio,
		lPrecioOferta,
		iFlagVtaMin,
		lPrecioOferta2,
		lCodigoOferta2,
		iDescuentoCalc,
		lDescuento,
		iPorcientoDescuentoEmpleado,
		lPrecioEspecial,
		iPorcientoClienteCero,
		iTipoDescuento,
		lCodigoDescm,
		iNumDesctos,
		iNumTiposDescto,
		ilCodigoOferta,
		lCodigoVtaMin;

	bool bFlagTipoDescuento;
	char cTasaCelular[3];
	char cTextoMsjError[256];
};

struct VentaCredito
{
	char cFecha[7];
	long lAbono10,
		lAbono2u,
		lAhorre,
		lTotal3,
		lAbono3;
};
struct S00031RecibePercepcionIB
{
	int iRespuesta;
	long lPorcAlicCABA;
	char cMotivo[4];
	short int iStatus;
	char cDescStatus[102];
};

struct S00031EnviaPercepcionIB
{
	short int iTipoMensaje;
	long lValorSeguridad;
	int iTipoOpcion;
	char cIpServidor[15];
	long lCliente;
	bool bEntregaEnCABA;
	long lImporteVtaSinImpuestos;
	char cFecha[10];
};

struct S00035RecibePagoMinimo
{
	int iRespuesta;
	int iPagoMinimo;
};

struct S00035EnviaPagoMinimo
{
	short int iTipoMsj;
	long lValorSeguridad;
	int iTipoOpcion;
	int iTienda;
	int iCliente;
	int lNotaFactura;
	int iTipoCuenta;
	int iTipoMovimiento;
};

struct sRespuestaGEOpcion2
{
	long lCodigo,
		lCodigoge,
		lPrecio;
	int iAnioge,
		iDcf;
	char cArticulo[12],
		cMarca[12],
		cModelo[22],
		cFechaVig[12],
		cModoentrega[1],
		cImportacion[1],
		cAgotado[1],
		cFlagincrementartasa[1];
	short iMesesGarantia,
		iFlagRiesgo,
		Tipo,
		iMessurtir,
		iStock,
		iTasa12,
		iTasa18,
		iExistencia,
		iFlagarmado,
		iTestienda,
		iTesbodega,
		iCelular,
		iDescesp;
};

struct obtenerDatosClienteLCCRopa
{
	short flagcreditolcc;
	short flaglccobligado;
	short descuentolcc;
	char msgdescuentolcc[52];
	short iFlagLineaCreditoEsp;
	int iTipoCteLCC;
	char cVigenciaMegaPuntosCoppel[50];
};

struct MSGDesctoCredtoEnvia
{
	short int iTipoMensaje;
	long lValorSeguridad;
	short int iTienda;
	long lCliente;
};

struct MSGDesctoCredtoRecibe
{
	short int iStatus;
	int iDescuentoRopa,
		iDescuentoMuebles;
};
struct sRespSc3Telefono
{
	/*int	 iFlagDescuentoEspecial;
	char cPuntualidad       [3];
	char cNombre            [40];
	char cApellidoPaterno   [40];
	char cSexo              [3];
	char cSituacionEspecial [3];
	int  iCausaSitEsp;*/
};
struct RespSc3DatosIniciales
{
	int iInicio;
	char cDesCripcioUno[257];
	char cDesCripcioDos[257];
	char cDesCripcioTres[257];
	char cSubDominioUno[17];
	char cSubDominioDos[17];
	char cDominioUno[17];
	char cDominioDos[17];
	char cDominioTres[17];
	char cDominioCuatro[17];
};
struct sBotonesSc3Telefonos
{
	int iNoTelefono;
	int iNoCorreo;
	int iNoTelefonoCorreo;
	/*char cDesCripcioUno         [257];
	char cDesCripcioDos         [257];
	char cDesCripcioTres        [257];
	char cSubDominioUno         [17];
	char cSubDominioDos         [17];
	char cDominioUno            [17];
	char cDominioDos            [17];
	char cDominioTres           [17];
	char cDominioCuatro         [17];*/
};
/*
Estructura de respuesta para captura Imei
*/
struct CapturaImei
{
	char cSerieTel[20];
	char cSerieTel1[20];
};
struct sTarjetaPosNet
{
	short iSist,
		iNoCaja;

	int iTicket,
		iCuotas,
		iSession;

	long lCliente;

	char cTarjeta[14],
		cImporte[18],
		cCodigoAutoriza[10],
		cCuponFiscal[17],
		cCodigoSeguridad[23],
		cDigitos[10],
		cLastTransaction[14],
		cMontoCashBack[22],
		cFecha[12];
};

struct ventasPendientes
{
	long cliente;
	long factura;
	int caja;
	long enganche;
	char presupuesto[8];
	int sistema;
};

struct sRespRembolso
{
	long lDevolucion,
		lFacturaReembolso;
	char cArea[2],
		cSexo[2],
		cNombre[17],
		cApellidoPaterno[17],
		cApellidoMaterno[17],
		cDni[20];
	int iNoEncontroReembolso,
		iValidaHuellaCliente,
		iCiudad;
};

struct sRespLeerTarjetaPreCarga
{
	char cDomicilio[21],
		cNombreCiudad[21],
		cNombreSucursal[21],
		cFecha[11];
	int iFlagCashBack;
	int iFlagPinPad;
};

struct CObtenerCostoFinanciero
{
	char sTexto[264];
};

struct S00031Respuesta
{
	char cTarjeta[20];
	char cPlan[32];
};

// Siempre el campo sRespuestaSobreprecio de la estructura sRespuestaServicio debe de ser el ultimo para que el memset a las
// variables de éste tipo de dato funcione correctamente
struct sRespuestaServicio
{
	int status;
	int iNumeroProcedimiento;
	/*1195*/
	int iOpcionReimpresion;
	bool bContarTickets;
	int iContadorTicketsLocal;
	int iContadorTicketsCentral;
	char cFechaInicialReimpresion[17];
	/*1195*/
	int iContadorStruct;
	int iContadorStructRopa;
	int iDevStatus;
	int iErrorDirectorio;
	int iva;
	int iToken;
	int iListasBlancas;
	int iRespuesta;
	char cMensaje[256];
	char cDevMensaje[256];
	char cMensajeHuella[256];
	char cDescripcion[42]; // Dato nesesario para la validacion del codigo y obtencion de la descripcion del mismo
	bool bVigenciaLCC;
	bool bStatusLCC;
	bool bTiendaLCC;
	bool bFlagContadoCLCC;
	bool bCteCeroCredito;
	bool bAplicaCLCC;
	bool bFlagDescuentoCero;
	int iDescuentoClienteCero;
	char cFechaIniCte[14];
	char cFechaFinCte[14];
	char cProvincia[50];
	char cValorEncabezado[260];
	char cRfc[25];
	char cFechaFinVig[30];
	short iFlagMismaCiudad;
	int iReconocimiento;
	int iReconocimientoRopa;
	int iReconocimientoMuebles;
	int iTipoOrigenCliente;
	int iFlagTdaVentaHuella;
	int iFlagClienteNunca;
	bool bDctoBienvenida;
	bool bAlicuotaPercepcionIB;
	long lSaldoFactorizado;
	int impuestointerno;
	char cFolioPosnet[14];
	int iFlagPrimerCompra;
	long lUltimaNota;
	long iPorcentajeTasasDiferenciadas;
	int iDescuentoTasasDiferenciadas;
	long lImporteVtaSinImpuestos;
	float fValorNetoCodigo;
	long long lImporteVtaSinImpuestosRopa;
	bool bPercibeCABAFin;
	long lIIBBPercepcionImpresionRopa;
	long lIIBBPercepcionACobrarRopa;
	int iColonia;
	int iPedirHuella;
	char fechaInicioPagarCliente[40];
	char cInformacionFinancieraRopa[256];
	char cInformacionFinancieraMuebles[256];
	int iClv_cuenta_reest;
	char padStart[15];
	int iFlagClienteCartera;
	bool fEsMoto;
	short iFeActiva;
	double dTasaInteresRopa8x;
	bool bPlanCuotas;
	bool bPlanCuotasValidacion;
	bool bFlagCostoFinanciero;
	char cFechaConsultaSaldos[30];
	char cIpPcLocal[20];
	long lEmpleado;
	int cajaApartado;
	int iFlagSamsung;
	long lRetFolio;
	char cNombreGerenteCajas[52];
	char cNombreCajero[100];
	char cDescMensaje[400];
		//////////////////////PET1438//////////////
	long lTotalBonificacion;
	int lRecibo;
	int lFacturaPrestamos;
	int lFactura;
	int Prestamo;
	int lImportePrestamo;
	int lAbonoMensual;
	int lImporteTotalFinanciado;
	int lInteresFinanciamiento;
	int iTasaInteresPrestamos;
	int iParametricoTda;
	long lImportePrestamoSinIva;
	long lIvaPrestamo;
	long iNumReconocimiento;
	int flagPrestamos;
	int flagEncuesta;
	//////////////////////////////////////////
    DescuentoMuebles                desmu;
	DescuentoRopa	                desro;
    sRespuestaVentCaida             sRespVentaCaida;
	sconsultaTdConfiguracion        sConsultaTdConfiguracion;
	sconsultaTdConfiguracionPrestamos        sConsultaTdConfiguracionPrestamos;
	sconsultarFlagMercadoPago       sConsultarFlagMercadoPago;
	MSGDesctoCredtoRecibe			desctoCredtoRecibe;
	sRespuestaHuella				sHuellas;
	sDatosClaveempleado				sClaveEmp;
    sRespFormaPagoPrecarga			sRespFormaPagoPre;
    sConsultarCodigoCiudad			sConsultarCodigo[40];
    sCambiarVendedor				sCambioVendedor[40];
    sDomicilios						sDomiciliosR[60];
    sBusquedaPorNombre				sBuscarClientes[500];
    sConsultarDomicilio				sConsultaDom;
    sFormaDePagoTarjetas			sTarjetas[40];
    sRespMegaPuntosCoppel			sRMegaPuntos[2];
    sRespuestaComplementarCCuenta	sComCCuenta;
    sbusquedaClientePorDni			sBusquedaPorDni;
	sRespSc3Telefono 				sRespuestaSc3;
    sBotonesSc3Telefonos 			sRespuestaBotones;
  	RespSc3DatosIniciales 			sRespSc3DatosIniciales;
	CapturaImei  					sCapturaImei;
    InfoGrabarPrestamo				infoGrabarPrestamo;
    SysRopa							sSysRopa;
    SysMuebles						sSysMuebles;
    SysMicros                       sSysMicros;
	S00019Respuesta					sRespDesc[25];
    InfoCodigoMuebles               articuloMuebles;
	FacturaPaquete					sInfoPaquetes;
    sRespuestaGarantiaExtendida		sRespuestaGE;//839
	sRespuestaGEOpcion2				sRespGE2[10];//839
	sRespuestaGEOpcion2 			sRespGE2Temporal;
	sRespuestaArmado                sResArmado;
    obtenerDatosClienteLCCRopa		sObtenerDatosClienteLCCRopa;
    S00031RecibePercepcionIB skInfoPercepcionIB;
	int 	liberar;
	S00035RecibePagoMinimo sRecibePagoMinimo;
	S00035RecibePagoMinimo sReestructuraRopa;
	S00023Respuesta sDatosCredMueblesRes; // Se renombra por vulnerabilidad
	S00023Respuesta sDatosCreditoRopaRes;
	Enganche enganche;
	sVentaTramitadaRes ventaTramiteRes;
	sVentaTramitadaRes sVentaTramiteRes[256];
	sRespuesta24_QuienEntrega sQuienEntrega;
	sRespuestaPagoInicial sRespuestaPI;
	sDatosParametrico tdDatosParametricosAr;
	sFormaDePagoEmisoras sEmisoras[100];
	VentaCredito ventaDeCredito;
	S00027Respuesta sValidaPagoMuebles;
	S00012Respuesta sRespVentaFutura;
	S00028Respuesta sRespPrestamo;
	sMueblesinfoTienda sMueblesinfoTiendas[40];
	S00029Respuesta sRespSorteo;

	sTarjetaPosNet sTarjetasPosNet[40];
	bool bChecarCliente;
	sRespRembolso resprembolso;
	sRespuestaPim respuestaPim;
	sRespLeerTarjetaPreCarga respuestaLeerTarjetaPre;
	bool bExistesolicitud;
	long lCliente;
	int iTipoTarjeta;
	char cAdmFinanciera[5];
	int DisponibleCajaMuebles;
	int DisponibleCajaRopa;
	int DisponibleCaja;
	MovimientoUdi movimientoUdi;
	int iPuntosInicialesRopa;
	char nombreZona[256];
	double fFactorTasasDiferenciadas;
	float lArancel;
	float lInteresTarjeta;
	long iCuotasGrabar;
	long lCostoFinanciero;
	sRespuestaFinanciera respuestaFinanciera;
	Articulo sArticuloMegaPuntusUtilizado[99];
	CObtenerCostoFinanciero sConsultarFinanciacion[50];
	CObtenerCostoFinanciero sConsultarFinanciacionCompare[50];
	int iFlagCredDesctoEmpleadoUnificadoRM;
	ventasPendientes sventasPendientes[256];
	char cValorMonotributo[256];
	InfoCodigosInterescf interesfinanciero[50];
	long lCostoFinancieroR;
	long lCostoFinancieroM;
	char cFechaGndominio[12];
	char cIpPcBd[17];
	char cFechaVencimiento[12];
	int iFlagCajaActiva;
	int iFlagModoEntregaR;
	sVentaFutura sVentaFuturasCodigos[200];
	sVentaFutura sVentaCodigosRopaVtex[200];
	formaFacturas sFormaFacturas[256];
	infoNotasRopa sArticuloRopas[256];	   // 1195 notas ropa

	int iMontoCashBackRopa,
		iEmpleado,
		iEmpleadoRopa,
		iMontoCashBackCaja,
		iMontoCashBackMuebles;
	sDatosGarex	DatosGarex;
	S00031Respuesta sRespuestaPromociones[50];
};

struct sRespuestaServicioinicio
{
	int iToken;
	int iListasBlancas;
};

/*
***** Estructuras para la facturacion electronica *********
*/

struct sTributosFactura
{
	double dAlicuota;
	double dBaseImponible;
	double dImporte;
	char sAlicuota[512];
};

struct sAlicuotasFactura
{
	double dBaseImponible;
	double dImporte;
	char sTipoIva[54];
};

struct sComprobantesAsociadosFactura
{
	char sTipoComprobante[128];
	int iPuntoVentaId;
	int iNumeroComprobante;
};

struct sFacturacionElectronica
{
	char sTipoComprobante[128];
	int iNroTransaccion;
	char sTipoDocumento[128];
	char sDocumentoNro[128];
	char sComprobanteFecha[128]; // yyyy-MM-dd
	double dImporteTotal;
	double dImporteNetoNoGravado;
	double dImporteNeto;
	double dImporteExcento;
	double dImporteTributo;
	double dImporteIVA;
	sTributosFactura sTributos[15];
	sAlicuotasFactura sAlicuotas[15];
	// sFacturacionElectronica sComprobantesAsociados   [ 15 ];
};

struct FormaPagoCoppel05
{
	short iRespuesta; // 1 pago.  0 No pago

	long lPagoEfectivo,
		lPagoTarjetaCredito,
		lPagoTarjetaDebito,
		lMontoGlobal,
		lNumEmpleadoHuella,
		lImporteCashBack,
		lPagoReembolso,
		lPagoPim,
		lPagoFinanciera;

	double dPagoCheque,
		dPagoDolaresPesos,
		dCambio,
		dPagoTarjetaPlata,
		dParidad;

	int iNumeroDolar;

	int64_t lNumCheque;

	char cFinanciera[24],
		cDni[10];
};

struct DatosReembolso
{
	short iTiendaReembolso,
		iNoEncontroReembolso;

	char cPresupuesto[7],
		cNcc[13];
	long lCliente,
		lFactura,
		lValorReembolso,
		lGerenteAutoriza,
		lEmpleado;
};

struct S00016Enviar
{
	short iTipoMensaje;
	long lValorSeguridad;
	short iTipoOpcion;
	long lCliente;
	int iFecha;
	int iTipoCambio;
	long lDolares;
};

struct S00016Respuesta
{
	int iRespuesta;
	long lDolares;
};

/*
***** Estructuras para la facturacion electronica *********
*/
// Estructura de ventas tramitadas
struct GridNota
{
	char m_cantidad[32];
	char sPrecio[32];
	char m_Precio[32];
	int iTipoMsjDescuento;
	int VALOR_CANTIDAD1;
	long VALOR_PRECIO1;
	long VALOR_PRECIO2;
	int VALOR_LOTE1;
	int VALOR_CANTIDAD2;
	int iFlagNuevoCodigoTalla;
	int iFlagDescuentoArgenta;
	bool bPaquetePromocion;
	int iPorcientoDescuento;
	int iPaquetePorcientoDescuento;
	int iDescJuguetesCambio;
	int bEsCambio;
	int iVtaDiaNino;
};

struct S00029RecibeDescuentoNino
{
	short int iTipoMensaje;
	long lValorSeguridad;
	int iTipoOpcion;
	char IpServidor[15];
	long lCliente;
	int iImportedescuento;
	short int iTienda;
	int iNota;
	short int iCaja;
	int iAnio;
};

struct S00029EnviaDescuentoNino
{
	int iRespuesta;
};

struct SorteoOCEnvia
{
	int iRespuesta;
	long lOrdenCompra,
		lCantOC1,
		lCantOC2,
		lCantOC3,
		lValorOC1,
		lValorOC2,
		lValorOC3;
	char cTelefonoOC[16],
		cFechaInicialCanje[12],
		cFechaFinalCanje[12],
		cCuponFiscalOC[15],
		cFechaInicialPremio[12],
		cFechaFinalPremio[12];
};
struct SorteoOCRecibe
{
	short int iClave;
	long lValorSeguridad;
	short int iTienda;
	char cArea[1];
	short int iCaja;
	long lFolio;
	long lFecha;
	long lCliente;
	char cDNI[11];
	char cNombre[45];
	char cDomicilio[50];
	char cEmail[45];
	int64_t iTelefonoCelular;
	int64_t iTelefonoParticular;
	long lImporte;
	char cIPServidorTda[20];
	char cFlagEmpleado[3];
};
struct TramitarCredto
{
	long lCliente,
		lFactura;
	int iTienda;
	char cArea;
	int iCaja;
	char cPuntualidadTienda;
	int iCuentasActivas,
		iLimite;
	long lSaldoRopa,
		lVencidoRopa,
		lSaldoMuebles,
		lVencidoMuebles,
		lSaldoPrestamo,
		lVencidoPrestamo,
		lVentaContado,
		lEngancheCliente,
		lInteres,
		lVentaCredito,
		lEnganchePropuesto,
		lCodigo1,
		lCodigo2,
		lCodigo3;
	int iCantidadArticulosCodigo1,
		iCantidadArticulosCodigo2,
		iCantidadArticulosCodigo3;
	char cTipoEntregaCodigo1,
		cTipoEntregaCodigo2,
		cTipoEntregaCodigo3,
		cCondicionesTienda[30];
	int iPlazoVentaMuebles;
	char cClienteAnexo,
		cComentarioTienda[80],
		cFechaTienda[8],
		cIpTienda[15],
		cIpServidorTienda[15];
	int iPuntosPrecalificasion,
		iPuntosConsumoLinea,
		iPuntajeParametricoRopa;
};
struct TramitarCreditoDetalleMuebles
{
	long lCliente,
		lFactura,
		lFolio;
	int iTienda;
	char cArea;
	int iCaja;
	long lCodigo;
	char cDescripcion[40];
	int iTipoArticulo;
	long lImporte,
		lPiSistema;
	int iPorPiSistema;
	long lPiCliente;
	int iPorPiCliente,
		iCantidadArtPorCodigo;
	char cFormasDeEntrega,
		cFechaTienda[9];
	int iFila;
};

struct CorteCarteras
{
	long TotalMicro,
		PesosBonificacionMuebles,
		PesosBonificacionRopa,
		PesosEtp,
		PesosAgua,
		PesosLuz,
		PesosTelefono,
		PesosGas1,
		PesosGas2,
		PesosCablevision,
		PesosAbonoRopa,
		PesosAbonoMuebles,
		PesosInteresRopa,
		PesosInteresMuebles,
		ImporteCorreccionRopa,
		ImporteCorreccionMuebles,
		PesosCorrecVentaRopa,
		PesosCorrecAbonoRopa,
		PesosCorrecCancInteAdRopa,
		PesosCorrecBonifRopa,
		PesosCorrecCancInteAdMueb,
		PesosCorrecAbonoMuebles,
		PesosCorrecBonifMuebles,
		PesosCorrecDevolMuebles,
		PesosPagosSeguros,
		PesosComprasSeguros,
		PesosLiquidacionTramite,
		PesosLiquidacionPago,
		PesosInteresesRopa,
		PesosInteresesMuebles,
		AbonosEnMiles,
		AbonosEnMilesExtra,
		InteresEnMiles,
		InteresEnMilesExtra;
	short NumeroEtp,
		NumeroBonificacionMuebles,
		NumeroBonificacionRopa,
		ConveniosRopa,
		ConveniosMuebles,
		NumeroAgua,
		NumeroLuz,
		NumeroTelefono,
		NumeroGas1,
		NumeroGas2,
		NumeroCablevision,
		CorreccionesVentaRopa,
		CorreccionesAbonoRopa,
		CorreccionesCancInteAdRopa,
		CorreccionesBonifRopa,
		CorreccionesCancInteAdMueb,
		CorreccionesAbonoMuebles,
		CorreccionesBonifMuebles,
		CorreccionesDevolMuebles,
		DificilCobroRopa,
		DificilCobroMuebles,
		InteresAdicionalRopa,
		InteresAdicionalMuebles,
		PagosSeguros,
		ComprasSeguros,
		LiquidacionTramite,
		LiquidacionPago;
	long PesosAsofol;
	short NumeroAsofol;
	long PesosPagoNomina;
	short NumeroPagoNomina;
	long PesosPagoUniteller;
	short NumeroPagoUniteller;
	long PesosPagosSegurosClub;
	short PagosSegurosClub;
	long PesosNextel;
	short NumeroNextel;
	long PesosPrestamos;
	short NumeroPrestamos;
	long PesosAbonosPrestamos;
	short NumeroAbonosPrestamos;
	long PesosBonificacionPrestamos;
	short NumeroBonificacionPrestamos;
	long PesosLiquidacionPrestamos;
	short NumeroLiquidacionPrestamos;
	long PesosInteresesPrestamos;
	short NumeroInteresesPrestamos;
	long PesosConveniosPrestamos;
	short NumeroConveniosPrestamos;
	long PesosAlestra;
	short NumeroAlestra;
	long ComisionPrestamos;
	long PesosCfe;
	short NumeroCfe;
	long PesosAxtel;
	short NumeroAxtel;
	long PesosTA;
	short NumeroTA;
	long PesosRP;
	short NumeroDeRP;
	long PesosGasNat;
	short NumeroGasNat;
	long PesosOIngresos;
	short NumeroDeOIngresos;
	long PesosRetirosAfore,
		PesosAportacionesAfore;
	short NumeroRetirosAfore,
		NumeroAportacionesAfore;
	long PesosCorrecBonifPrestamo,
		PesosCorrecAbonoPrestamo,
		PesosCorreCancInteAdPrest,
		PesosCorreVencidoPrestamo;
	short CorreccionesBonifPrestamo,
		CorreccionesAbonoPrestamo,
		CorreccionesCancIntePrest,
		CorreccionesVencidoPrestamo;
	long PesosAbonoTiempoAire,
		PesosInteresTiempoAire,
		PesosBonificacionTiempoAire;
	short NumeroBonificacionTiempoAire,
		ConveniosTiempoAire,
		InteresAdicionalTiempoAire;
	long PesosAbonoBancoppel;
	short NumeroBonificacionBancoppel,
		NumeroConveniosBancoppel,
		NumeroInteresesBancoppel;
	long PesosConveniosBancoppel,
		PesosBonificacionesBancoppel,
		PesosInteresesBancoppel;
};

struct Corte
{
	short Nb100,
		Nb50,
		Nb20,
		NbMil, // Nb10,
		Nb5,
		Nb2,
		Nb1;
	long Efectivo100,
		Efectivo50,
		Efectivo20,
		EfectivoMil,	   // Efectivo10,
		EfectivoEnDolares, // Efectivo5,
		RetParcialPesos,   // Efectivo2,
		RetParcialDls,	   // Efectivo1,
		Moneda,
		DocumentosCheques,
		DocumentosTarjetas,
		DolaresBillete,
		DolaresCheque,
		DolaresGiro,
		BilleteEnDolar,
		ChequeEnDolar,
		GiroEnDolar,
		Comision;
	short Nb500,
		Nb200;
	long Efectivo500,
		Efectivo200;
	int Nb1000,
		Nb2000,
		Nb5000,
		Nb10000,
		Nb20000,
		Nb50000,
		Nb100000,
		Nb200000,
		Nb500000;
	long Efectivo1000, // cfe
		ComisionPrestamo,
		Efectivo5000,	  // alestra
		EfectivoPrestamo, // efectivo_10000,
		Efectivo20000,
		Efectivo50000, // nextel
		lRetirosAfore,
		CantEnDolar, // antes -> Efectivo100000,  //megacable
		// Efectivo200000,
		EfectivoAgua,
		EfectivoTelmex,
		ValeCoppel,
		Vale1,
		Vale2,
		Vale3,
		EfectivoSofol, // Antes era vale4
		Vale5,
		PagosNomina,
		PagosUniteller,
		ImporteAxtel,
		lRPagos,
		lAportacionAfore,
		lOtrosIngresos,
		DocumentosxCobrar,
		lRetirosFaltante,
		lRetiroSobrante,
		lDolaresComprados,
		lDolaresVendidos,
		BilleteEnDolarCompra,
		BilleteEnDolarVenta,
		lRetirosFaltanteCheques,
		lRetiroSobranteCheques,
		lRetiroParcialExtraCash;
	short Nb10;
	long Efectivo10,
		Efectivo5,
		Efectivo2,
		Pim,
		Tarjetaplata,
		Cuotaya;
};

struct Parametricos02
{
	short int iEstado;
	int iMesesTranscurridos;
	long lParRiesgoMuebles2;
	long lAbonoPromedio;
	long lParPrestamo2;
};

struct TramitarCreditoMuebles
{
	long lCliente,
		lFactura;
	int iTienda;
	char cArea;
	int iCaja;
	char cPuntualidadTienda;
	int iCuentasActivas,
		iLimite;
	long lSaldoRopa,
		lVencidoRopa,
		lSaldoMuebles,
		lVencidoMuebles,
		lSaldoPrestamo,
		lVencidoPrestamo,
		lVentaContado,
		lEngancheCliente,
		lInteres,
		lVentaCredito,
		lEnganchePropuesto,
		lCodigo1,
		lCodigo2,
		lCodigo3,
		iPorConsumoLinea;
	int iCantidadArticulosCodigo1,
		iCantidadArticulosCodigo2,
		iCantidadArticulosCodigo3;
	char cTipoEntregaCodigo1,
		cTipoEntregaCodigo2,
		cTipoEntregaCodigo3,
		cCondicionesTienda[32];
	int iPlazoVentaMuebles;
	char cClienteAnexo,
		cComentarioTienda[80],
		cFechaTienda[9],
		cIpTienda[15],
		cIpServidorTienda[15];
	int iPuntajeParAltoRiesgo;
};

struct sDatosAltoRiesgoCR
{
	long lCliente,
		lNota,
		lSaldoTotal,
		lSaldoFactorizadoTotal,
		lVencidoTotal,
		lTotalVenta,
		lLineaRealCreditoPesos,
		lLineaDeCredReal, // se renombra por vulnerabilidad
		lParRiesgoMuebles2,
		lEnganche,
		lExcesoCompra,
		lTotalGE, // 0 en ropa, Total de GE, GE: solo se venden en muebles.
		lFolioTramite,
		lEngancheProp,
		lSaldoMuebles,
		lExcesoTopeMaximo,
		lPagoPC,
		lEngancheTmp;

	char cArea,
		cPuntualidad,
		cFechaActual[15],
		cFechaPrimerCompraCR[11],
		cFechaAlta[15],
		cFechaUltimaCompra[11];

	int iPlazoVta,
		iFlagLineaCreditoEsp,
		iAntiguedadMeses,
		iPorcentajeCompraNvo,
		iPorcPI,
		iSumaParametrico,
		iPtosParametrico,
		iCaja,
		iPtosPrecalificacionCN,
		iStatus,
		iDiasTransUltimaCompra,
		iFlagLineaBlanca,	 // 0 en ropa, iFlagLineaBlanca:se llena solo en muebles. 538
		iTotalVentaLineaBca, // 0 en ropa, iTotalVentaLineaBca:se llena solo en muebles. 538
		iFlagVentaTramitada,
		iFlagVentaCambio, // 0 en ropa
		iFlagVentaEmpleado,
		iTienda,
		iPuntosParIniciales,
		iPtsUltCompra,
		iPtsAntiguedad,
		iPtsSaturacion,
		iFlagVentaPaquete,
		iCuentasActivas,
		iSMC,
		iVSMCCte,
		iVSMCCteNvaVta,
		iSaturacionCte,
		iSaturacionCteNvaVta,
		iFactorTopeMaximo,
		iDescuentoCert,
		iPiDescuento,
		iDescuentoAplicado,
		iflagCambio,
		iFlagPrimerCompra,
		iDiasTransPrimerCompra,
		iPagos12Meses,
		iPagosVsSaldo,
		iPuntajePagos,
		iPuntajeTienda,
		iFlagEmpresa,
		iNuevoSaldo,
		iFlagTestigoAR;
	int64_t iNroTransaccion;
};

struct S00028Envia
{
	short int iEstado;

	int iMesesTranscurridos;
	int iPuntosIniciales;
	int iPuntosPrecalificasion;
	int iPuntosPrecalificasionCN;
	int iPuntos;
	int iPuntosParametrico;
	int iAntiguedadMeses;
	int iSumaParametrico;
	int iPuntosConsumoLinea;

	long lParRiesgoMuebles2;
	long lAbonoPromedio;
	long lParPrestamo2;
	long lAbonoBaseTotal;
	long lAbonoBasePromedio;
};

struct TituloVenta
{
	char cNCC[14],
		cPresupuesto[8],
		cCuponFiscal[14],
		cSerieFiscal[5],
		cSucursalTitulo[4],
		cPrefixoTitulo[5],
		cNumTitulo[11],
		cParcelaTitulo[3],
		cTipoTitulo[5];
};

struct ClienteMuebles
{
	long lCliente,
		lCalleNumero,
		lCasaNumero,
		lZonaNumero,
		lVendedorNumero,
		lVendedorEmpleado,
		lLocalidad;
	char cNombre[15],
		cApellidoPaterno[15],
		cApellidoMaterno[15],
		cCalleNombre[20],
		cRumbo,
		cZonaNombre[20],
		cComplemento[30],
		cVendedorNombre[20],
		cObservaciones[80],
		cDiaDeEntrega,
		cMesDeEntrega,
		cFlagCteForaneo, // 0=Local  1=For neo
		cFlagUnidadHab,	 // 1=Si es unidad hab.
		cCoordenadasDomic[62],
		cDepto[6];
	int iCiudadNumero;
	short iUHCManzana,
		iUHCOtros,
		iUHCAndador,
		iUHCEtapa,
		iUHCLote,
		iUHCEdificio,
		iUHCEntrada;
	int16_t i64Telefono;
	char cDNICliente[12];
	long lClienteContado;
};

#endif	//ESTRUCTURAS_WSPRESTAMOS_
