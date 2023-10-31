// =================================================================
//  Clase: CRegistro
//  Archivo: CRegistro.h
//
//  Descripcion: Clase generica que hereda de la CRecordSet, la estructura de la misma 
//		 se define en tiempo de ejecuci�n lo que nos permite usarla para cualquier
//		 query o inserci�n.
//
//  Autor        : David Pe�uelas Beltran
//  Fecha        : 15-JUN-11
// 
// =================================================================


#ifndef HPP_CREGISTRO
#define HPP_CREGISTRO

#include <RecordSet.hpp>
#include "CListaCampo.h"

//Tabla de campos
#define	DT_ENTERO_CORTO		1
#define	DT_ENTERO			2
#define	DT_ENTERO_LARGO		3
#define	DT_FLOTANTE			4
#define	DT_DOBLE			5
#define	DT_FECHA			6
#define	DT_CHAR				7

#define	MAX_BUFFER_CHAR			150000


class CRegistro : public CRecordSet 
{

public:

	CRegistro( C_ODBC *odbc, bool bCommit = true, const char *cQuery = NULL );
	~CRegistro( void );
    
	void activarCols( void );
	BOOL prepararInsert( const char *cNombreTabla );	
	
	BOOL agregarCampoEntero( const char *cNombre, short iTipo, int64_t *iValor = NULL );
	BOOL agregarCampoDecimal( const char *cNombre, short iTipo, double *dValor = NULL );
	BOOL agregarCampoChar( const char *cNombre, int iLongitud, const char *cValor = NULL );
	BOOL agregarCampoFecha( const char *cNombre, SqlTimeStamp *tFecha = NULL );
	
	int totalCampos( void );

	//Obtener/poner valores de los campos por nombre
	char *valorChar( const char *cNombre );
	void valorChar( const char *cNombre, const char *cValor, int iLongitud = 0 );
	
	short valorShort( const char *cNombre );
	void valorShort( const char *cNombre, short iValor );

	long valorLong( const char *cNombre );
	void valorLong( const char *cNombre, long lValor );

	int64_t valorInt64( const char *cNombre );
	void valorInt64( const char *cNombre, int64_t iValor );

	float valorFloat( const char *cNombre );
	void valorFloat( const char *cNombre, float fValor );

	double valorDouble( const char *cNombre );
	void valorDouble( const char *cNombre, double dValor );

	SqlTimeStamp *valorFecha( const char *cNombre );
	void valorFecha( const char *cNombre, SqlTimeStamp *tValor );

	//Obtener/poner valores de los campos por indice de las columnas
	char *valorChar( int iCol );
	void valorChar( int iCol, const char *cValor, int iLongitud = 0 );

	short valorShort( int iCol );
	void valorShort( int iCol, short iValor );

	long valorLong( int iCol );
	void valorLong( int iCol, long lValor );

	int64_t valorInt64( int iCol );
	void valorInt64( int iCol, int64_t iValor );

	float valorFloat( int iCol );
	void valorFloat( int iCol, float fValor );

	double valorDouble( int iCol );
	void valorDouble( int iCol, double dValor );

	SqlTimeStamp *valorFecha( int iCol );
	void valorFecha( int iCol, SqlTimeStamp *tValor );	
	
	int obtenerTipoDato( int iCol );
	int obtenerTipoDato( const char *cNombre );
	int obtenerTamanio( int iCol );
	int obtenerTamanio( const char *cNombre );
	bool tieneValorDefault( int iCol );
	bool tieneValorDefault( const char *cNombre );
	const char *error( void );

	C_ODBC *odbc1;//encoding

private:
    
	CListaCampo campos;
	C_ODBC *odbc;
	int odbcRet;
	int flagInsertar;
	bool bCommit;
	char cBufferTemp[MAX_BUFFER_CHAR];

	bool buscarCampo( const char *cNombre );
	bool buscarCampo( int iCol );

	CGranContenedor contenedor;
};

#endif //HPP_CREGISTRO


