#ifndef _LISTA_CODIGOS_
#define	_LISTA_CODIGOS_

struct InfoCodigoRopa
{
    long    lCodigo;
    int     iTalla;
    long    lPrecio;
    int     iCantidad;
    long    lImporte;
    long    lSobrePrecio;        
    int     iTipoDescuento;    
    int     iPorcientoDescuentoCodigo;
    long    lImporteDescuento;
    long    lImporteDescuentoPC;
    long    lSobrePrecioDescto;
    int     iDescontinuado;
    int     iItemOriginal;    
    long    lPercepcionIIBB;
    long    lPrecioNetoDevolucion;        
    char    cNotaManual;
    char    cDescripcion    [45];
	int     iTipoDescuentoOrig;   
};
template <typename T>
class CContenedorCodigo {
    public:
        CContenedorCodigo() {
            tamanio = 0;
        }

        void agregar(void * &p, T * t) {
            if(tamanio > -1) {
                lista[tamanio] = *t;
                p = &lista[tamanio];
                tamanio++;
            }
        }

        void agregar(T * &p, T * t) {
            if(tamanio > -1) {
                lista[tamanio] = *t;
                p = &lista[tamanio];
                tamanio++;
            }
        }
    private:
        T lista[100];
        int tamanio;
};

class CNodoCodigoRopa
{
public:
	CNodoCodigoRopa( InfoCodigoRopa *codigo = NULL, CNodoCodigoRopa *pSig = NULL, CNodoCodigoRopa *pAnt = NULL );
	~CNodoCodigoRopa( void );

private:
		
	InfoCodigoRopa codigo;
	CNodoCodigoRopa *pNodoSiguiente;
	CNodoCodigoRopa *pNodoAnterior;
        
   	friend class CListaCodigoRopa;
};

typedef CNodoCodigoRopa *pNodoCodigoRopa;

class CListaCodigoRopa
{
public:
		
	CListaCodigoRopa(void);
	~CListaCodigoRopa(void);
    
	void agregar( InfoCodigoRopa *codigo );
	bool listaVacia( void );
	bool siguiente( void );
	bool anterior( void );
	void primero( void );
	void ultimo( void );    
	InfoCodigoRopa *nodo( void );	
	void borrar( void );
	int totalNodos( void );
	
    
private:
	pNodoCodigoRopa pLista;
	CContenedorCodigo<CNodoCodigoRopa> contenedorRopa;
	int iNodos;	
};

struct InfoCodigoMuebles
{
	long  	lCodigo; 				
	short 	i16Cantidad;			
	char  	cQuienEntrega,			
			cArticulo[11],     		
			cMarca[11],				
			cModelo[21];       		
	long  	lPrecioUnitario,		
			lImporte;				
	char  	cTipo,					
			cAgotadoInvent;    		
	short 	i16Existencia;			
	char  	cBodegaQueEntrega,		
			cSemanaEntrega,			
			cMesEntrega,			
			cModoDeEntrega;    		
	long  	lSobrePrecio;    		
	char  	cImportacion;			
	short 	i16Stock;				
	double 	fInteres12,				
			fInteres18;				
	char  	cNumeroSerieUdi[15],	
			cCausaUdi,				
			cDescripcionDano[45],   
			cFlagApartado,          
			cFlagCodigoEspecial,    
			cAgotado,				
			cFlagTipoEntrada;       
	long  	lSobrePrecio18;        	
	char  	cFlagPlazo18,          	
			cCveImpuestoSuntuario;	
	long  	lFamilia;				
	int   	iStatus,
	        iValorErrorChip;      			
	char  	cFlagNoArmarArticulo,   
			cFlagVtaChip,           
			cNumSerieTel[18],		
			cFlagSerieValida;		
	short 	iFlagVtaMin,			
			iTipoDescuento,			
			iFlagVtaChip,			
			iFlagCodigoOculto,		
			iFlagCodigoGE,			
			iAnioGE,				
			iFlagCodigoArmado,		
			iCodidoArmadoSQL;		
	long  	lCodigoOculto,			
			lTesTienda,				
			lTesBodega,				
			lCodigoGE;				
	short 	iCelular,				
			iDescEsp,				
			iFlagRiesgo;			
	long  	lDesPaquete,			
			lSobrePrecioPaq,		
			lSobrePrecioPaq18;		
	char  	cFlagentregafuturo[5],	
			cFlagta[5];				
	short 	iBodega,				
			iGarantia;				
	char  	cSerieArtGE[20];		
	long 	lPercepcionIIBB;
	long 	lIIBBPercepcionSum;
	long 	lPagoPC;
    int     iFlag;//temp
    int     totalIva;
	int     ivaTienda;
    int     ivaBodega;
    int     iNuevaTasaInteres;
	int 	iImpuestointernoTienda;
	int 	iImpuestointernoBodega;

};

class CNodoCodigoMuebles
{
public:
	CNodoCodigoMuebles( InfoCodigoMuebles *codigo = NULL, CNodoCodigoMuebles *pSig = NULL, CNodoCodigoMuebles *pAnt = NULL );
	~CNodoCodigoMuebles( void );

private:
		
	InfoCodigoMuebles codigo;
	CNodoCodigoMuebles *pNodoSiguiente;
	CNodoCodigoMuebles *pNodoAnterior;
        
   	friend class CListaCodigoMuebles;
};

typedef CNodoCodigoMuebles *pNodoCodigoMuebles;

class CListaCodigoMuebles
{
public:
		
	CListaCodigoMuebles(void);
	~CListaCodigoMuebles(void);
    
	void agregar( InfoCodigoMuebles *codigo );
	bool listaVacia( void );
	bool siguiente( void );
	bool anterior( void );
	void primero( void );
	void ultimo( void );    
	InfoCodigoMuebles *nodo( void );
	void borrar( void );
	int totalNodos( void );
	
    
private:
	pNodoCodigoMuebles pLista;
	CContenedorCodigo<CNodoCodigoMuebles> contenedorMuebles;
	int iNodos;
};

#endif	//_LISTA_CODIGOS_
