#ifndef _S_wsprestamosDEF_
#define _S_wsprestamosDEF_

#define TAM_MAX_BUFF                    2048
#define TAM_MED_BUFF                    512
#define TAM_MIN_BUFF                    256

#define	_OK_					        1

#define STDIN  					        0
#define STDOUT 					        1

// Versionamiento Semantico 
#define _SEMVER_ "1.0"

// LOGS
#define _LOGINFO_ "INFO"
#define _LOGWARNING_ "WARNING"
#define _LOGERROR_ "ERROR"

// Clave Encrypt Decrypt
#define _CLAVECIFRADO_ "1234567890123456"

//Mensajes de la aplicacion
#define M00001_AUTENTIFICAHUELLA		 1
#define M00002_CONSULTARPRODUCTO		 2
#define M00003_CONSULTAARTICULOTIENDAS   3
#define M00004_CONSULTARDIRECCION		 4
#define M00005_BUSQUEDANOMBRE		     5
#define M00006_CAMBIARVENDEDOR           6
#define M00007_FORMASDEPAGO          	 7
#define M00008_COMPLEMENTARCCUENTA       8
#define M00009_GRABARVENTA               9
#define M00010_BUSQUEDACLIENTEDNI       10
#define M00011_VALIDARINICIODELDIA      11
#define M00012_VALIDARVENTASFUTURA      12
#define M00014_CAPTURADECORREOYTELEFONO 14
#define M00015_CAPTURADEEMI	        	15
#define M00016_CONSULTARPAGOINICIAL     16
#define M00017_CALCULAR_SOBREPRECIO		17
#define M00018_VERIFICAR_VENTA_TRAMITE  18
#define M00019_OBTENER_DESCUENTOS	    19
#define M00020_PROCEDIMIENTOSGENERALES  20
#define M00021_VALIDARCODIGOMUEBLES     21
#define M00023_GRABAR_FACTURA_TEMPORAL  23
#define M00024_VALIDARQUIENENTREGA      24
#define M00025_CONSULTARCLIENTECONTADO  25
#define M00026_GUARDARINFOMOTO          26
#define M00027_VALIDARPAGOMUEBLES       27
#define M00028_CONSULTARPRESTAMO        28
#define M00029_CONSULTARSORTEO          29
#define M00030_LOG_FRONT_END            30
#define M00031_CONSULTARPROMOCIONESTARJETAS 31
#define M00032_APARTADOPORTIENDA        32

#define _CONSULTA_CLIENTE_              1
#define _CONSULTA_EMPLEADO_             2


//Set de errores del mensaje
#define	E00001_ERROR_DEFAULT			-1
#define E00001_ERROR_CONEXION_DB		-3
#define E00001_ERROR_QUERY				-4
#define E00001_ERROR_XML_INVALIDO		-5
#define E00001_ERROR_SOAP_POST			-6
#define E00001_ERROR_SSL				-7
#define E00001_ERROR_PARAMETROS_MAL		-8

#define	E00001_ERROR_SEC    			-9


//Set de errores de los mensajes para desarrollo

#define _ERROR_DE_CONEXION_BD_          -1
#define _ERROR_HTTP_                    -2
#define _ERROR_QUERY_                   -3
#define _ERROR_DE_MOSTRAR_MSG_          -4

#define	TOKEN_ERROR_DEFAULT			-1
#define TOKEN_ERROR_SERVICIO		-2
#define TOKEN_NO_VALIDO  	    	-3
#define	LB_ERROR_DEFAULT		    -4
#define LB_ERROR_BD     		    -5
#define LB_NO_VALIDO  	    	    -6
#define ERROR_NO_DATOS		        -7

//Set de errores para para los mensajes con el front

#define _MENSAJE_CORRECTO_              200
#define _ERROR_EN_MENSAJE               400 // Bad Request
#define _ERROR_AUTORIZACION             401 // Authorization Required   Tok
#define _ERROR_FORBIDDEN                403 // Forbidden   LB
#define _ERROR_DE_SERVIDOR              500 // Internal Server Error

//PARA LA TABLA PAJ
#define PAJ_PRESTAMOS   				88
#define INSERTAR_PROTHEUS               '3'
#define MODIFICAR_PROTHEUS              '4'
#define ELIMINAR_PROTHEUS               '5'

//Set de status para para los tipos de codigo que retorna el validar codigo de muebles al front

#define _CODIGO_MUEBLES_                200
#define _CODIGO_MOTO_                   201
#define _CODIGO_GE_                     202
#define _CODIGO_                        203
#define _CODIGO_PAQUETE                 204

//Tipos de inicio del sistema
#define SYS_NOTA				        0
#define SYS_CARGO				        1
#define SYS_DESCARGO			        2

//tipos de flag para consulta de domicilio
#define _CONSULTA_CIUDAD_               1
#define _CONSULTA_LOCALIDAD_            2
#define _CONSULTA_CALLE_                3
#define _CONSULTA_ZONA_                 4
#define _CONSULTA_MUFACTURAHISTORIAL_   10

#define CLIENTE_CONTADO                 90001

//Tabla de Tipo de Comprador
#define CLIENTE                         1
#define CONTADO                         2
#define EMPLEADO                        3
#define CLIENTELCCERO                   4


// Servidores

#define IPCARTERA                        1              //Ip para la consulta de domicilios y cuentas de clientes
#define IPCREDITO                        2              //Ip para la consulta de movimientos y cuentas de clientes
#define IPTRAMITES                       3              //Ip de tramites a cr�dito
#define IPENVIOSDINERO                   4              //Ip de env�os de dinero Nacional y MoneyGram
#define IPHUELLAS                        5
#define IPTIENDA                         6              //Ip de respuestas a tr�mites de cr�dito
#define IPCARTERA2                       7              //Ip para la consulta de domicilios y cuentas de clientes
#define IPCREDITO2                       8              //Ip para la consulta de movimientos y cuentas de clientes
#define IPTRAMITES2                      9              //Ip de tramites a cr�dito
#define IPENVIOSDINERO2                 10              //Ip de env�os de dinero Nacional y MoneyGram
#define IPHUELLAS2                      11
#define IPTIENDA2                       12              //Ip de respuestas a tr�mites de cr�dito
#define IPSORTEO                        13              //Ip de solicitud de boletos
#define IPCUPON                         14              //Ip de cupones
#define IPUNEFON                        15              //Ip tiempo aire unefon
#define IPMOVISTAR                      16              //Ip tiempo aire movistar
#define IPTELCEL                        17              //Ip tiempo aire telcel
#define IPIUSACELL                      18              //Ip tiempo aire iusacell
#define IPPSCFE                         19              //Ip pago de servicio cfe
#define IPPSTELMEX                      20              //Ip pago de servicio telmex
#define IPNUMSERIES                     21              //Ip n�meros de serie de celulares
#define IPHLLASPASSTDA                  22              //IP checar huellas empleados.(ventas, cancelaciones y respuestas de empleados)
#define IPCENTRALEMPS                   23              //IP2 checar huellas empleados.(Pagos de Nomina, reembolsos, gastos de viaje)
#define IPALTAHUEEMPRE                  24              //Ip para Alta, obtener, consultar importe de descuentos TEC u Otros    28/07/2005 10:20
#define IPATENCIONSERV                  25              //Ip para el m�dulo de atenci�n y servicios
#define IPCHEQUEBOTADOR                 26              //Ip para la verificacion de cheques
#define IPGRABARTIRAS                   27              //Ip para Grabar las tiras de ropa, muebles, cajas , tiempo aire, etc..., tambien los folios de os de cn
#define IPNVOAPARTADO                   28              //Ip para el Nuevo Sistema de Apartado    08/06/2005 10:23
#define IPCARTERACIUDAD                 29              //Ip para la consulta de domicilios en la red por ciudad                06/07/2005 16:48
#define IPSOLICITUDES                   30              //Ip para la actualizaci�n de la solicitudes de clientes nuevos         06/07/2005 16:48
#define IPTIENDALOCAL                   31              //Ip para consultar los datos generales de tienda                       06/07/2005 16:48
#define IPSALDOSYPEND                   32              //Ip para consultar los saldos y pendientes de entrega                  25/07/2005 09:40
#define IPPLANES_TA                     33              //Ip para planes de tiempo aire                                         15/08/2005 15:43
#define IPBURO                          34              //Ip para consultas al bur� de cr�dito                                  29/08/2005 15:43
#define IPTALLERAUT                     35              //Ip para consultas al taller autorizado                                02/09/2005 16:43
#define IPMENSAJERIA                    36              //Ip para env�o de mensajer�a o paqueter�a                              26/09/2005 10:03
#define IPEMPMENSAJERIA                 37              //Ip para env�o de mensajer�a o paqueter�a                              26/09/2005 10:03
#define IPAFORE                         38              //Ip para obtener y actualizar datos del servidor intermedio afore      12/10/2005 10:03
#define IPMENSAJERIA2                   39              //Ip para envio de mensajeria o paqueteria                              20/01/2006 17:33
#define IPIVRMOVTO                      40				//Ip para Los movimientos del IVR( Solicitud de mov de vta tpo aire tel)24/01/2006 12:35
#define IPHLLACENTRAL                   41              //Ip para Los movimientos de EMPLEADOS central                          02/03/2006 17:45
#define IPHLLAREGIONAL                  42              //Ip para Los movimientos del IVR( Solicitud de mov de vta tpo aire tel)02/03/2006 17:45
#define IPPASSTDAREGIO                  43              //IP checar huellas empleados.(ventas, cancelaciones y respuestas de empleados)
#define IPPASSTDACENTR                  44              //IP checar huellas empleados.(ventas, cancelaciones y respuestas de empleados)
#define IPDISCAJACHICA                  45              //IP para checar el centro de las caja chica de tiendas."10.15.240.216" 24/04/2006 10:56a
#define IPTAREVER                       46              //IP para reversos(Planes, Tiempo Aire, Servicios)                      05/05/2006 13:56
#define IPGTRANSITORIO                  48              //IP Para Obtener y grabar gastos de fondos transitorios  FONTRAN.EXE   15/07/2006 09:32
#define IPSERVIDORCOT	                49				//IP para realizar el tramite del COT.
#define SERV_CRED_VTASTRAMITADAS   		144             //Ip para la BD de Solicitudenlineasud //Se renombra por vulnerabilidad
#define SERV_CREDTO 					2               //Ip para la consulta de movimientos y cuentas de clientes

//MENSAJES DE LA APLICACION DE BODEGAM : 20801
//----------------------------------------------
#define M00001_APARTADO                  1			//Cosulta y apartado de los codigos
#define M00002_SERVICIOSYGARANTIAS       2			//consulta de historial de las facturas
#define M00003_ENRUTADO                  3			//ejecucion de un programa del enrutado
#define M00017_GARANTIASEXTENDIDAS       17			//consulta de las facturas con GE
#define M00001_APARTADO_ELIMINAR_REGISTROS_ADICIONALES                  11			//Elimina los registros extras y actualiza por cada registro el unico registro que queda para aumentar el campo cantidad

//----------------------------------------------
//SUBMENSAJES DEL MENSAJE M00001_APARTADO : 20801
//----------------------------------------------
#define M001_APARTADO_BUSQUEDA                  1
#define M002_APARTADO_CONFIRMACION              2
#define M004_APARTADO_ELIMINAR                  4
#define M005_ELIMINAR_REGISTROS_ADICIONALES     5
#define M006_APARTADO_CANCELACION               6
//Elimina o restaura el disponible de los articulos que se eliminaron o no se concreto la venta - JUANCVI

//flag para tabla temporal
#define SYS_NOTA	                0
#define FALSE	                    0
#define TRUE	                    1

//ESCENARIOS 
#define SOLOCORREO						0
#define SOLOTELEFONOS					1
#define CORREOYTELEFONOS				2
//Tipo de Descuentos de ropa
#define DESCUENTO_NULO					0
#define DESCUENTO_DESPERFECTO			1
#define DESCUENTO_GERENTE				2
#define DESCUENTO_EMPLEADO				3
#define DESCUENTO_DEVOLUCION_PORCNTJ	4
#define DESCUENTO_CREDITO_CFE			5
#define DESCUENTO_ESPECIAL				7
#define DESCUENTO_CRED	    			8   //Se renombra por vulnerabilidad
//#define DESCUENTO_VALE_DORADOS		9
#define DESCUENTO_ESPECIAL_EMPLEADO		10
#define DESCUENTO_CUPON_PROMOCION		15
#define DESCUENTO_EMPRESA_EXTERNA		16
#define DESCUENTO_DINERO_COPPEL         17
#define DESCUENTO_PAQUETE				18
#define DESCUENTO_COCACOLA				19
#define DESCUENTO_BIENVENIDA			20
#define DESCUENTO_CTECERO               22			//El 21 ya esta en uso en el sistema de Nota Ropa
#define DESCUENTO_ARGENTA				43
#define DESCUENTO_CLIENTECERO			45
#define DESCUENTO_PUNTOS_COPPEL         51
#define DESCUENTO_ESPECIAL_VARIOS		52

//Tipos de ventas
#define VENTA_PENDIENTE				    0
#define VENTA_NORMAL					1
#define VENTA_AUTORIZADA				2

//Tipos de facturas
#define FACTURA_PENDIENTE		 0
#define FACTURA_NORMAL			 1
#define FACTURA_AUTORIZADA		 2
#define FACTURA_RECHAZADA		 3
#define FACTURA_CONDICIONADA	 4

//Máximo de items para el recorrido de las bonificaciones de ropa
#define MAX_ITEM_BONIFICACION_ROPA      9

#define FLAG_TIENDALOCAL                30
#define FLAG_DOLARESFRONTERA			53
#define FLAG_TARJETA_VTOL				62
#define FLAG_VENTA_CAIDA				69
#define FLAG_USAR_FINACIERA				82
#define FLAG_PERMITE_CASHBACK			79 // Flag para controlar si se permite cashback en tarjetas de débito
#define PTO_INET_BODEGAMTDAV1           50326
#define PTO_INET_BODEGAM                20801
#define PTO_INET_SORTEO                 20616
#define FLAG_COSTO_FINANCIERO			90


#define FOLIOC_RECIBO					7

#define TIEMPO_ESPERA		5000
#define PTO_CLIENTECARTERA	20521

#define	NO_AMEX					0
#define	ES_AMEX					1

#define TIEMPO_ESPERA		            5000
#define PTO_CLIENTECARTERA	            20521

//Tipos de status para las huellas de gerentes
#define HUELLA_ERROR			  0
#define HUELLA_CORRECTA			  1
#define HUELLA_INCORRECTA		  2

#define	NO_AMEX					        0
#define	ES_AMEX					        1

// definiciones para inet (consultarCodigoBodega)
#define CONSULTAR_INFO_CODIGOC			102

//------------------------DEFINICION DE PUERTOS CONFIGURADOS EN LOS SERVIDORES LINUX---------------------------------
#define PTO_INET_BODEGAR                 20850 //Procesa Movimientos de Bodega Ropa
#define PTO_INET_DIANINIO                20506 //consulta inet del dia del niño
#define PTO_INET_PERCEPCIONIB			 20506 //consulta de PERCEPCION IB 
#define PTO_INET_DESCUENTO_ESPECIAL      20410 //consulta inet para saber si tiene descuentos especiales

//Definiciones para la obtencion del valores del grid
#define VALOR_NUMERO_ARTICULO			-1
#define VALOR_CODIGO					0
#define VALOR_TALLA						1
#define VALOR_PRECIO					2
#define VALOR_CANTIDAD					3
#define VALOR_DESCRIPCION				4
#define VALOR_IMPORTE					5
#define VALOR_CONIVA					6
#define VALOR_LOTE						7
#define VALOR_SOBREPRECIO				8
#define VALOR_DESCUENTO					9
#define VALOR_NOTAMANUAL				10
#define VALOR_CODIGO_DESCUENTO			11
#define VALOR_TALLA_DESCUENTO			12
#define VALOR_DESCONTINUADO				13
#define VALOR_PAQUETEPROMOCION			14
#define VALOR_ITEMORI					15
#define VALOR_KEYX						16
#define VALOR_PERCEPCION				17
#define VALOR_DESCUENTOPC				18
#define VALOR_DESCUENTOSESP				19

//PROCEDIMIENTOSGENERALES
#define LIMPIARTABLATEMPORALES          1
#define OBTENERDATOSCLIENTELCCROPA      2
#define GRABARRECONOCIMIENTO	        3
#define GRABARTDAUTORIZACION	        4
#define CONSULTARFLAGDESCUENTOESPECIAL	5
#define COLSULTARPROVINCIA              11
// #define OBTENERDATOSPAGOINICIAL         12
#define OBTENERDATOSPAGOINICIAL         12
#define SALDOFACTORIZADONUEVACOMPRA     13
#define VENTAUDI                        15
#define CONSULTARENCABEZADOTICKET       16
#define QUIENENTREGAUDI                 17

#define CONSULTARMINIMOCOMPRAMEGAPUNTOS     8
#define CONSULTARPORCENTAJEGASTOMEGAPUNTOS  9
#define ACTUALIZARCTEVTO 19
#define CONSULTARTDCONFIGURACIONTICKETGARANTIAEXT 21
#define CONSULTAFECHAPRIMERACOMPRALCCMUEBLES 22
#define OBTENERFECHAFINVIGENCIA 23
#define CONSULTARFLAGMERCADOPAGO 		24
#define CONSULTARFOLIO 26
#define CONSULTARMISMACIUDAD 28
#define CONSULTARFLAGTDAVENTAHUELLA 29
#define VALIDARCONTROL 30
#define GRABARENCABEZADOTICKETS 31 

#define ALICUOTAPERCEPCIONIB 32
#define OBTENERICTENESPECIAL 33
#define CONSULTARPUNTOSINICIALESROPA 34
#define CONSULTARFECHAPRIMERACOMPRA 35
#define VERIFICARULTIMANOTA 37
#define CONSULTARNOMBREZONA 38
#define OBTENERALICUOTAIBROPA 39
#define CONSULTARFACTORTASADIFERENCIADA 40
#define CONSULTARCOLONIA 41
#define VERIFICARPRECIOCODIGO 42
#define VERIFICARPRECIOCODIGOAGREGARTMP 43
#define VERIFICARPRECIOCODIGOBORRARTMP 44
#define GRABARVENTACAIDA 45
#define CONSULTARINFORMACIONFINANCIERA 46
#define CONSULTARTOPEVENTACREDITO 47
#define CONSULTARSERVICIOPAGOMINIMO 48
#define CONSULTARSERVICIOREESTRUCTURA 49
#define CONSULTARFLAGREGALO 50
#define CONSULTARVALORNETO 51
#define BORRARTABLASTEMPORALESNUBE 52
#define CONFIRMARTRANSACCIONFE 53
#define VERIFICARTDESTACION 54
#define CALCULARDESICION27PARAMETRICO 55
#define CHECARCODREGALO 56
#define BORRARTMPTDCHEQUES 57
#define COMBONUMCUOTAS 58
#define OBTENERFINANCIAMIENTO 59
#define ONOFFAUTOMATIZACION 60
#define CONSULTACLIENTECARTERAVENDIDA 61
#define CONSULTARLEYENDAMONOTRIBUTO 62
#define OBTENERCOSTOFINANCIERO 63
#define GRABARCAMOVDINEROELECTRONICO 64//762
#define CONSULTARFECHAGNDOMINIO 65
#define GNCONSULTARTDCONFIGURACION 66
#define VERIFICA_CACARMOV 67
#define GNCONSULTARTDCAJAACTIVA 68
#define GNCONSULTARDATOSM3 69
#define GNCONSULTACLIENTE 70   //1053
#define GNLEVANTARDIALOGO 71   //1053
#define MANDARTRAMITE 72  //1053
#define OBTENERIVA_TICKETMUEBLES 73
#define VERIFICARCAJAACTIVA 74
#define OBTENERTRASPASOSPENDIENTES 75
#define REGISTRARTRASPASOCAN 76
#define ACTUALIZARMOTIVOTRASPASOCAN 77
#define DESCONEXIONTRASPASOSCAN 78
#define REMOVERTRASPASOCAN 79
#define FLAGYTIEMPOSTRASPASO 80

#define SISTEMA_MUEBLES    1
#define SISTEMA_ROPA       2
//#define SISTEMA_CAJAS      3

//Valores de temporizadores
#define TIEMPO_CHECK_NP				1
//#define TIEMPO_INICIAR_REPINS		2
#define TIEMPO_VERIFICAR_ENTER		3
//#define TIEMPO_MARCAR_INVENTARIO	4

#define COMPROBAR_VENTA     1
#define CONSULTAR_TRAMITE   2
#define CONSULTAR_VENTA_PENDIENTE 3
#define BORRAR_VENTAS_PENDIENTE 4
#define CONSULTAR_VENTAS_PENDIENTE 5

#define CLIENTE_VENTA_PENDIENTE 2

//Identificadores de procesos que realiza el motor de interfaz
#define MOTOR_CLIENTES					3	//000003  MANT. AL MAESTRO DE CLIENTES  PA9

//Tipos de elementos en la tabla tdConfiguracion
#define CONFIG_CODIGO_PAIS              "CODIGO_PAIS"
#define CONFIG_CUENTA_CONTABLE_CLIENTES "CUENTA_CONTABLE_CLIENTES"
#define CONFIG_PROVINCIA_ESTADO	        "PROVINCIA_ESTADO"

//Maximo numero de codigos de interes
#define MAX_ITEM_INTERES            6

//Operaciones del mensaje M00001_PIM
#define M0000101_PREPARACION_CARGA_DINERO_ELECTRONICO		1
#define M0000102_CONFIRMACION_CARGA_DINERO_ELECTRONICO		2
#define M0000103_PREPARACION_DESCARGA_DINERO_ELECTRONICO	3
#define M0000104_CONFIRMACION_DESCARGA_DINERO_ELECTRONICO	4
#define M0000105_REVERSION_TRANSACCION_AGENTE			5
#define M0000106_REVERSION_TRANSACCION_AGENTE_UTFI		6
#define M0000107_PREPARACION_COBRO				7
#define M0000108_CONFIRMACION_COBRO				8
//Estatus del grabado de movimientos PIM
#define _CARGADO	0
#define _CANCELADO	1
#define _RECHAZADO	2

//Set de errores del mensaje

#define E00001_ERROR_PIM				-2
#define E00001_ERROR_GRABADO_MOVIMIENTO -9

#define FOLIOC_RETIROPARCIAL     39
#define FOLIOR_RETIROPARCIAL     40
#define FOLIOM_RETIROPARCIAL     41
#define FOLION_RETIROPARCIAL     55
#define FOLIOM_CONTADOR_GE       74
#define FLAGC_INCLUIRRECIBOAGUA     15
#define FLAG_NUEVACARTERATIEMPOAIRE 33
#define SISTEMA_MUEBLES 1
#define SISTEMA_ROPA 2
#define SISTEMA_CAJAS 3
#define SISTEMA_CLIENTES_NUEVOS 4

#define SERV_SERVICIO_FIN				137				//Ip del webservice FINANSOL
#define SERV_DB_FIN						138				//Ip para la DB del servicio FINANSOL

//Mensajes del servicio FINANSOL CUOTA YA
#define M00001_MULTIOFERTA					1
#define M00002_PLANFINANCIERO				2
#define M00003_PREPARACION					3
#define M00004_CONFIRMACION					4
#define M00005_REENVIARSMS					5
#define M00006_ENVIARARCHIVOSFINANCIERA		6

//Mensajes del servicio FINANSOL TARJETA PLATA
#define M00001_EVALUARTP					1
#define M00002_CALCULARTP					2
#define M00004_REGISTRARTP					4
#define	M00008_ANULARTP						8
#define _APROBADO							200

//Definiciones para procesos de muebles en tabla gnSeguimiento
#define PROCESO_M_FACTURAS			1

//Definiciones para procesos de ropa en tabla gnSeguimiento
#define PROCESO_R_NOTAS				1

//Definiciones para procesos de cajas en tabla gnSeguimiento
#define PROCESO_C_ABONOS			1

//Definiciones para procesos de clientes nuevos en tabla gnSeguimiento
#define PROCESO_N_ALTA_CLIENTES		1

//Definiciones para el proceso de validar pago de muebles
/* Identificadores Familias */
#define FAMILIA_MOTOS            369

//Tipos de captura de descripción para códigos especiales
#define CAPTURAR_DESCRIPCION_999181		 1
#define CAPTURAR_DESCRIPCION_199941		 2
#define CAPTURAR_DESCRIPCION_999644		 3


// sysMuebles.h
#define T4A0B   " NO HAY EN BODEGA,SE ENTREGARA PARA %.43s "

//Definiciones para leerParametricosCliente
#define E00028_ERROR_CONSULTA           -2
#define E00028_ERROR_CLIENTE_NO_EXISTE	-3

//Tipos de inicio del sistema
#define NOTA_PENDIENTE			        0
#define NOTA_NORMAL				        1

//Operaciones del mensaje M00012_VENTAFUTURA
#define M0001201_NO_EXISTENCIAS_EN_BODEGA		201
#define M0001202_BORRAR_ARTICULO		202

#define	NO_AMEX					0
#define	ES_AMEX					1

//Tipos de Venta
#define CLIENTE_COPPEL_MUEBLES   1
#define CLIENTE_COPPEL_ROPA      2
#define CLIENTE_COPPEL_MIXTA     3
#define CLIENTE_CONTADO_MUEBLES  4
#define CLIENTE_CONTADO_ROPA     5
#define CLIENTE_CONTADO_MIXTA    6


#define PWD_CONECTA_CORREOS "c514d1957f:652931ge26c77:5gce8b5" //+1
#define PWD_CENTRAL_M "h5g557ggg56fd99efdh8df:f3egd55hc" //+2
#define PWD_CONECTA_POSGATEWAY "~heUOS5rx^pn5tQK;H[jWWUOI]tFrhRM" //+3

// ** IMPLEMENTACION DEL SEC ** //
//#define _SEC_DESARROLLO         "https://serviciocredenciales-dev.coppel.io/api/conexionesBD"
//#define _SEC_TEST               "https://serviciocredenciales-test.coppel.io/api/conexionesBD"
//#define _SEC_PROD               "https://serviciocredenciales.coppel.io/api/conexionesBD"

//#define _SEC_DESARROLLO         "https://d0001.coppel.io:81/sec/api/conexionesBD"
//#define _SEC_PROD               "https://t0001.coppel.io:81/sec/api/conexionesBD"

//#define _SEC_DESARROLLO         ".coppel.io:81/sec/api/conexionesBD"

//UTILIZAR EL SEC MODO PRODUCTIVO
#define _SEC_PROD               ".coppel.io:50335/api/conexionesBD"
#define _SEC_PRODAPLICATIVO     "https://serviciocredenciales.coppel.io/api/conexionesBD"
//UTILIZAR EL SEC MODO DESARROLLO
#define _SEC_DESARROLLO         ".coppel.io:50335/api/conexionesBD"
#define _SEC_DESAAPLICATIVO     "https://serviciocredenciales-dev.coppel.io/api/conexionesBD"

// -- Descomentar y comentar dependiendo donde se utilice el SEC -- //
//#define _SEC_MODO               1 //Productivo
//#define _SEC_MODO               2 //Desarrollo 
//#define _SEC_MODO               3 //Tester


#define _SEC_TIENDANUMERO          1 //"TiendaNumero" //Tienda Numero
#define _SEC_TIENDASN              2 //"Tienda" //CONECTA_TIENDA <-- Neumonico Original
#define _SEC_HUELLAEMPLEADO        3 //"HuellaEmpleados" // CONECTA_HUELLASEMPLEADOS <-- Neumonico Original
#define _SEC_CARTERA               "Cartera" //CONECTA_CARTERA <-- Neumonico Original
#define _SEC_CENTRAL_M             "CentralMuebles" //CONECTA_CENTRAL_M <-- Neumonico Original
#define _SEC_SOLICITUDES           "Solicitudes" //CONECTA_SOLICITUDES <-- Neumonico Original
#define _SEC_TRAMITES              "Tramites" //CONECTA_TRAMITES <-- Neumonico Original
#define _SEC_CORREOS               "Correos" //CONECTA_CORREOS <-- Neumonico Original
#define _SEC_GLOBALBODEGAM         "GlobalBodegam" //CONECTA_GLOBALBODEGAM <-- Neumonico Original
#define _SEC_GLOBALTIENDAS         "GlobalTiendas" //SERV_GLOBALTIENDAS <-- Neumonico Original
#define _SEC_CUENTASPERDIDAS       "CuentasPerdidas" //- <-- Neumonico Original
#define _SEC_SERVICIOPIM           "ServicioPim" //SERV_SERVICIO_PIM <-- Neumonico Original
#define _SEC_SERVICIOFIN           "ServicioFin" //SERV_SERVICIO_FIN <-- Neumonico Original

#define TXT_SEC                    "/sysx/progs/webservice/wsprestamos/modoSEC.txt"

#endif //_S_wsprestamosDEF_