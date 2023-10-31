// =================================================================
//  Clases: CListaCampo y CNodoCampo
//  Archivo: CListaCampo.h
//
//  Descripcion: Clases para manejar una lista enlazada, 
//		 la cual tendra la informaci�n de los campos creados.
//
//  Autor        : David Pe�uelas Beltran
//  Fecha        : 15-JUN-11
// 
// =================================================================

#ifndef _LISTA_CAMPOS_
#define	_LISTA_CAMPOS_
#include <RecordSet.hpp>

struct InfoCampo
{
	int nSqlTipo;
	int nCTipo;
	long nLongitud;
	long nLongResp;
	void *pVar;
	char cNombre[35];
	short iTipo;
	char cFlgvDefault;
};
template <typename T>
class CContenedor {
    public:
        CContenedor() {
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
        T lista[256];
        int tamanio;
};

class CGranContenedor {
	public:
		CGranContenedor(void);
		void agregarShort(void * &p, short num);
		void agregarLong(void * &p, long num);
		void agregarInt64(void * &p, int64_t num);
		void agregarFloat(void *&p, float num);
		void agregarDouble(void *&p, double num);
		void agregarChar(void *&p, char *c);
		void agregarFecha(void *&p, SqlTimeStamp fecha);
	private:
		CContenedor<short> contenedorShort;
		CContenedor<long> contenedorLong;
		CContenedor<int64_t> contenedorInt64;
		CContenedor<float> contenedorFloat;
		CContenedor<double> contenedorDouble;
		CContenedor<SqlTimeStamp> contenedorFecha;
		char arrChar[100][2048];
		int indiceChar;
};

class CNodoCampo
{
public:
	CNodoCampo( InfoCampo *campo= NULL, CNodoCampo *pSig = NULL, CNodoCampo *pAnt = NULL );
	~CNodoCampo( void );

private:
		
	InfoCampo campo;
	CNodoCampo *pNodoSiguiente;
	CNodoCampo *pNodoAnterior;
        
   	friend class CListaCampo;
};

typedef CNodoCampo *pNodoCampo;

class CListaCampo
{
public:
		
	CListaCampo(void);
	~CListaCampo(void);
    
	void agregar( InfoCampo *campo );
	//void borrar( int iIndice );
	bool listaVacia( void );
	bool siguiente( void );
	bool anterior( void );
	void primero( void );
	void ultimo( void );    
	InfoCampo *nodo( void );
	void borrar( void );
	int totalNodos( void );
	
    
private:
	pNodoCampo pLista;
	CContenedor<CNodoCampo> contenedor;
	int iNodos;
};

#endif	//_LISTA_CAMPOS_
