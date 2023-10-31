#include <stdio.h>
#include <C_archiv.hpp>
#include "CListaCodigo.h"
#include "estructuras.h"
#include "CRegistro.h"
#include "gnfunciones.h"
//Nodo
CNodoCodigoRopa::CNodoCodigoRopa( InfoCodigoRopa *codigo, CNodoCodigoRopa *pSig, CNodoCodigoRopa *pAnt )
{	
	if(codigo)
	{
		mymemcpy( &(this->codigo), codigo, sizeof( this->codigo ) );
	}
	pNodoSiguiente = pSig;
	pNodoAnterior = pAnt;
}

CNodoCodigoRopa::~CNodoCodigoRopa(void)
{
}

CNodoCodigoMuebles::CNodoCodigoMuebles( InfoCodigoMuebles *codigo, CNodoCodigoMuebles *pSig, CNodoCodigoMuebles *pAnt )
{
	if(codigo)
	{
		mymemcpy( &(this->codigo), codigo, sizeof( this->codigo ) );
	}
	pNodoSiguiente = pSig;
	pNodoAnterior = pAnt;
}

CNodoCodigoMuebles::~CNodoCodigoMuebles(void)
{
}

//Lista
CListaCodigoRopa::CListaCodigoRopa(void) 
{
	 pLista = NULL;
	 iNodos = 0;     
}

CListaCodigoRopa::~CListaCodigoRopa(void) 
{
	//borrar();
}

void CListaCodigoRopa::agregar( InfoCodigoRopa *codigo ) 
{   
	pNodoCodigoRopa nuevo = NULL;
	ultimo();	
		
	if( !pLista ) 
	{
		nuevo = new CNodoCodigoRopa( codigo, pLista );	
		contenedorRopa.agregar(pLista,nuevo);
	}
	else 
	{
		nuevo = new CNodoCodigoRopa( codigo, pLista->pNodoSiguiente, pLista );
		contenedorRopa.agregar(pLista->pNodoSiguiente,nuevo);
	}
	delete nuevo;
	iNodos++;  
}

bool CListaCodigoRopa::siguiente( void ) 
{
	bool bSiguiente = false; 

	if( pLista && pLista->pNodoSiguiente ) 
	{
		bSiguiente = true;
		pLista = pLista->pNodoSiguiente;        
	}

	return bSiguiente;
}

bool CListaCodigoRopa::anterior( void ) 
{
	bool bAnterior = false;

	if( pLista && pLista->pNodoAnterior ) 
	{
		bAnterior = true;
		pLista = pLista->pNodoAnterior;        
	}

	return bAnterior;
}

void CListaCodigoRopa::primero( void ) 
{
	while( pLista && pLista->pNodoAnterior ) 
	{
	   	pLista = pLista->pNodoAnterior;        
	}
}

void CListaCodigoRopa::ultimo( void ) 
{
	while( pLista && pLista->pNodoSiguiente )
	{
		pLista = pLista->pNodoSiguiente;        
	}
}

bool CListaCodigoRopa::listaVacia( void )
{
	return pLista == NULL ? true : false; 
}

InfoCodigoRopa *CListaCodigoRopa::nodo( void ) 
{
	return &(pLista->codigo);
}

void CListaCodigoRopa::borrar( void )
{
	pNodoCodigoRopa aux = NULL;
	primero();

	while( pLista ) 
	{
		aux = pLista;
		pLista = pLista->pNodoSiguiente;
		//delete aux;
		aux = NULL;
	}

	iNodos = 0;
}

int CListaCodigoRopa::totalNodos( void )
{
	return( iNodos );
}

CListaCodigoMuebles::CListaCodigoMuebles(void) 
{
	 pLista = NULL;
	 iNodos = 0;
}

CListaCodigoMuebles::~CListaCodigoMuebles(void) 
{
	//borrar();
}

void CListaCodigoMuebles::agregar( InfoCodigoMuebles *codigo ) 
{   
	pNodoCodigoMuebles nuevo = NULL;
	ultimo();	
		
	if( !pLista ) 
	{
		nuevo = new CNodoCodigoMuebles( codigo, pLista );
		contenedorMuebles.agregar(pLista,nuevo);
	}
	else 
	{
		nuevo = new CNodoCodigoMuebles( codigo, pLista->pNodoSiguiente, pLista );
		contenedorMuebles.agregar(pLista->pNodoSiguiente,nuevo);
	}
	delete nuevo;
	iNodos++;
}

bool CListaCodigoMuebles::siguiente( void ) 
{
	bool bSiguiente = false; 

	if( pLista && pLista->pNodoSiguiente ) 
	{
		bSiguiente = true;
		pLista = pLista->pNodoSiguiente;
	}

	return bSiguiente;
}

bool CListaCodigoMuebles::anterior( void ) 
{
	bool bAnterior = false;

	if( pLista && pLista->pNodoAnterior ) 
	{
		bAnterior = true;
		pLista = pLista->pNodoAnterior;
	}

	return bAnterior;
}

void CListaCodigoMuebles::primero( void ) 
{
	while( pLista && pLista->pNodoAnterior ) 
	{
	   	pLista = pLista->pNodoAnterior;
	}
}

void CListaCodigoMuebles::ultimo( void ) 
{
	while( pLista && pLista->pNodoSiguiente )
	{
		pLista = pLista->pNodoSiguiente;
	}
}

bool CListaCodigoMuebles::listaVacia( void )
{
	return pLista == NULL ? true : false; 
}

InfoCodigoMuebles *CListaCodigoMuebles::nodo( void ) 
{
	return &(pLista->codigo);
}

void CListaCodigoMuebles::borrar( void )
{
	pNodoCodigoMuebles aux = NULL;
	primero();

	while( pLista ) 
	{
		aux = pLista;
		pLista = pLista->pNodoSiguiente;
		//delete aux;
		aux = NULL;
	}

	iNodos = 0;
}

int CListaCodigoMuebles::totalNodos( void )
{
	return( iNodos );
}

