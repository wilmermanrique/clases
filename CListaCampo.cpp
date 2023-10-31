// =================================================================
//  Clases: CListaCampo y CNodoCampo
//  Archivo: CListaCampo.cpp
//
//  Descripcion: Clases para manejar una lista enlazada, 
//		 la cual tendra la informacion de los campos creados.
//
//  Autor        : David Penuelas Beltran
//  Fecha        : 15-JUN-11
// 
// =================================================================
#include <stdio.h>
#include "CListaCampo.h"
#include "CRegistro.h"
#include "gnfunciones.h"
//Nodo
CGranContenedor::CGranContenedor(void) {
	indiceChar = 0;

	for(int i = 0; i < 100; i++) {
		mymemset(&arrChar[i], 0, 100);
	}
}

void CGranContenedor::agregarShort(void * &p, short num) {
	contenedorShort.agregar(p, &num);
}

void CGranContenedor::agregarLong(void * &p, long num) {
	contenedorLong.agregar(p, &num);
}

void CGranContenedor::agregarInt64(void * &p, int64_t num) {
	contenedorInt64.agregar(p, &num);
}

void CGranContenedor::agregarFloat(void * &p, float num) {
	contenedorFloat.agregar(p, &num);
}

void CGranContenedor::agregarDouble(void * &p, double num) {
	contenedorDouble.agregar(p, &num);
}

void CGranContenedor::agregarFecha(void * &p, SqlTimeStamp fecha) {
	contenedorFecha.agregar(p, &fecha);
}

void CGranContenedor::agregarChar(void * &p, char * c) {
	mysprintf(arrChar[indiceChar], "%s", c);
	p = &arrChar[indiceChar];
	indiceChar++;
}

CNodoCampo::CNodoCampo( InfoCampo *campo, CNodoCampo *pSig, CNodoCampo *pAnt )
{
	if(campo) {
		mymemcpy( &(this->campo), campo, sizeof( this->campo ) );
	}
	pNodoSiguiente = pSig;
	pNodoAnterior = pAnt;
}

CNodoCampo::~CNodoCampo(void)
{
}

//Lista
CListaCampo::CListaCampo(void) 
{
	 pLista = NULL;
	 iNodos = 0;
}

CListaCampo::~CListaCampo(void) 
{
	//borrar();
}

void CListaCampo::agregar( InfoCampo *campo ) 
{   
	pNodoCampo nuevo = NULL;
	ultimo();	
		
	if( !pLista ) 
	{
		nuevo = new CNodoCampo( campo, pLista );
		contenedor.agregar( pLista, nuevo );
	}
	else 
	{
		nuevo = new CNodoCampo( campo, pLista->pNodoSiguiente, pLista );
		contenedor.agregar( pLista->pNodoSiguiente, nuevo );
	}
	delete nuevo;
	iNodos++;
}


/*void CListaCampo::borrar( int iIndice )
{
}*/

bool CListaCampo::siguiente( void ) 
{
	bool bSiguiente = false; 

	if( pLista && pLista->pNodoSiguiente ) 
	{
		bSiguiente = true;
		pLista = pLista->pNodoSiguiente;
	}

	return bSiguiente;
}

bool CListaCampo::anterior( void ) 
{
	bool bAnterior = false;

	if( pLista && pLista->pNodoAnterior ) 
	{
		bAnterior = true;
		pLista = pLista->pNodoAnterior;
	}

	return bAnterior;
}

void CListaCampo::primero( void ) 
{
	while( pLista && pLista->pNodoAnterior ) 
	{
	   	pLista = pLista->pNodoAnterior;
	}
}

void CListaCampo::ultimo( void ) 
{
	while( pLista && pLista->pNodoSiguiente )
	{
		pLista = pLista->pNodoSiguiente;
	}
}

bool CListaCampo::listaVacia( void )
{
	return pLista == NULL ? true : false; 
}

InfoCampo *CListaCampo::nodo( void ) 
{
	return &(pLista->campo);
}

void CListaCampo::borrar( void )
{
	short int *iValor = NULL;
	long *lValor = NULL;
	int64_t *i64Valor = NULL;
	float *fValor = NULL;
	double *dValor = NULL;
	SqlTimeStamp *tValor = NULL;
	char *cValor = NULL;
	//char cLog[512] = {0};
			
	pNodoCampo aux = NULL;
	primero();

	while( pLista ) 
	{
		aux = pLista;
		pLista = pLista->pNodoSiguiente;
		
		switch( aux->campo.iTipo )
		{
			case DT_ENTERO_CORTO:			
			iValor = (short int *)aux->campo.pVar;
			delete iValor;			
			break;			
			
			case DT_ENTERO:			
			lValor = (long *)aux->campo.pVar;
			delete lValor;			
			break;
			
			case DT_ENTERO_LARGO:
			i64Valor = (int64_t *)aux->campo.pVar;
			delete i64Valor;
			break;
			
			case DT_FLOTANTE:
			fValor = (float *)aux->campo.pVar;
			delete fValor;
			break;
			
			case DT_DOBLE:
			dValor = (double *)aux->campo.pVar;
			delete dValor;
			break;
			
			case DT_FECHA:					
			tValor = (SqlTimeStamp *)aux->campo.pVar;
			delete tValor;
			break;
			
			case DT_CHAR:			
			cValor = (char *)aux->campo.pVar;
			delete []cValor;			
			break;
			
			default:
			//sprintf( cLog, "No se puede liberar el buffer, tipo de dato no definido [%d]", aux->campo.iTipo );
			//logx( cLog  , _LOGINFO_ );			
			break;
		}
		
		aux->campo.pVar = NULL;		
		//delete aux;
		aux = NULL;
	}

	iNodos = 0;
}

int CListaCampo::totalNodos( void )
{
	return( iNodos );
}
