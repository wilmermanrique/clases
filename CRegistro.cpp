// =================================================================
//  Clase: CRegistro
//  Archivo: CRegistro.cpp
//
//  Descripcion: Clase generica que hereda de la CRecordSet, la estructura de la misma 
//       se define en tiempo de ejecuci?n lo que nos permite usarla para cualquier
//       query o inserci?n.
//
//  Autor        : David Pe?uelas Beltran
//  Fecha        : 15-JUN-11
// 
// =================================================================

#include "CRegistro.h"
#include "gnfunciones.h"
CRegistro::CRegistro( C_ODBC *odbc, bool bCommit, const char *cQuery ) : CRecordSet( odbc )
{
    this->odbc = NULL;
    this->odbc = odbc;    
    this->bCommit = bCommit;
    odbcRet = TRUE;
    flagInsertar = 0;
    mymemset( cBufferTemp, 0, sizeof( cBufferTemp ) );

    if( cQuery != NULL )
    {
        odbcRet = Exec( cQuery );
        activarCols();
    }
}

CRegistro::~CRegistro( void )
{
    if( this->bCommit )
    {
            Commit();
    }
}


BOOL CRegistro::agregarCampoEntero( const char *cNombre, short iTipo, int64_t *iValor )
{
    BOOL bRespuesta = TRUE;
    InfoCampo campo;
    mymemset( &campo, 0, sizeof( campo ) );
    campo.cFlgvDefault = '0';

    campo.iTipo = iTipo;
    mysnprintf( campo.cNombre, 35,"%s", cNombre );
    int64_t iPtrValor = 0;

    if( iValor != NULL ) {
        iPtrValor = *iValor;
        campo.cFlgvDefault = '1';
    }

    switch( iTipo )
    {
        case DT_ENTERO_CORTO:
            {   
                campo.nSqlTipo = SQL_SMALLINT;
                campo.nCTipo = SQL_C_SSHORT;
                campo.nLongitud = 3;    

                contenedor.agregarShort(campo.pVar, (short int)iPtrValor);          
                campos.agregar( &campo );
            }
            break;

        case DT_ENTERO:         
            {
                campo.nSqlTipo = SQL_INTEGER;
                campo.nCTipo = SQL_C_SLONG;
                campo.nLongitud = 5;
                
                contenedor.agregarLong(campo.pVar, (long)iPtrValor);
                campos.agregar( &campo );
            }
            break;

        case DT_ENTERO_LARGO:
            {   
                campo.nSqlTipo = SQL_BIGINT;
                campo.nCTipo = SQL_C_SBIGINT;
                campo.nLongitud = 9;
                
                contenedor.agregarInt64(campo.pVar, iPtrValor);
                campos.agregar( &campo );
            }
            break;

        default:
            bRespuesta = FALSE;
            break;
    }
    
	return bRespuesta;
}

BOOL CRegistro::agregarCampoDecimal( const char *cNombre, short iTipo, double *dValor )
{
    BOOL bRespuesta = TRUE;
    InfoCampo campo;
    mymemset( &campo, 0, sizeof( campo ) );
    campo.cFlgvDefault = '0';

    campo.iTipo = iTipo;
    mysnprintf( campo.cNombre, 34,"%s", cNombre );

    double dPtrValor = 0;
    if( dValor != NULL )
    {
        dPtrValor = *dValor;
        campo.cFlgvDefault = '1';
    }

    switch( iTipo )
    {
        case DT_FLOTANTE:
            {
                campo.nSqlTipo = SQL_REAL;
                campo.nCTipo = SQL_C_FLOAT;
                campo.nLongitud = 5;
                
                contenedor.agregarFloat(campo.pVar, (float)dPtrValor);
                campos.agregar( &campo );
            }
            break;

        case DT_DOBLE:
            {
                campo.nSqlTipo = SQL_FLOAT;
                campo.nCTipo = SQL_C_DOUBLE;
                campo.nLongitud = 5;
                
                contenedor.agregarDouble(campo.pVar, dPtrValor);
                campos.agregar( &campo );
            }
            break;

        default:
            bRespuesta = FALSE;
            break;
    }

	return bRespuesta;
}
    
BOOL CRegistro::agregarCampoChar( const char *cNombre, int iLongitud, const char *cValor )
{
    BOOL bRespuesta = TRUE;
    InfoCampo campo;
    mymemset( &campo, 0, sizeof( campo ) );

    mysnprintf( campo.cNombre, 35,"%s", cNombre );
    campo.cFlgvDefault = '0';   
    campo.iTipo = DT_CHAR;  
    campo.nSqlTipo = SQL_CHAR;
    campo.nCTipo = SQL_C_CHAR;
    campo.nLongitud = iLongitud + 2;

    char cVar[campo.nLongitud];
    mymemset(cVar, 0, campo.nLongitud);

    if( cValor != NULL )
    {
        campo.cFlgvDefault = '1';
        mymemcpy( cVar, cValor, mystrnlen( cValor ) );
    }
    contenedor.agregarChar(campo.pVar, cVar);
    campos.agregar( &campo );

	return bRespuesta;
}

BOOL CRegistro::agregarCampoFecha( const char *cNombre, SqlTimeStamp *tFecha )
{
    BOOL bRespuesta = TRUE;
    SqlTimeStamp tFechaLoc;
    InfoCampo campo;
    mymemset( &campo, 0, sizeof( campo ) );
    campo.cFlgvDefault = '0';

    campo.iTipo = DT_FECHA;
    mysnprintf( campo.cNombre, 34,"%s", cNombre );
    campo.nSqlTipo = SQL_VARCHAR;
    campo.nCTipo = SQL_C_CHAR;
    campo.nLongitud = 107;  
    
    tFechaLoc.ponerFecha( 1, 1, 1900 );
    
    if( tFecha != NULL )
    {
        campo.cFlgvDefault = '1';
        tFechaLoc.ponerFecha( tFecha->dia(), tFecha->mes(), tFecha->ano() );
    }
    
    contenedor.agregarFecha(campo.pVar, tFechaLoc);
    campos.agregar( &campo );

	return bRespuesta;
}

char *CRegistro::valorChar( const char *cNombre )
{
    bool bRespuesta = false;
    int iLen = 0;
    mymemset( cBufferTemp, '\0', sizeof( cBufferTemp ) );

    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {       
        if(campos.nodo()->nLongitud > ( sizeof( cBufferTemp )) || campos.nodo()->nLongitud == ( sizeof( cBufferTemp )))
        {
            iLen = sizeof( cBufferTemp ) - 1;
        }
        else if (campos.nodo()->nLongitud < ( sizeof( cBufferTemp )))
        {
            iLen = campos.nodo()->nLongitud ;       
        }
        mymemcpy( cBufferTemp, campos.nodo()->pVar, iLen);                      
    }
    return cBufferTemp;

}

void CRegistro::valorChar( const char *cNombre, const char *cValor, int iLongitud )
{
    int iLen = 0;
    bool bRespuesta = false;
    int iLongitudLoc = 0;

    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        iLongitudLoc = iLongitud;
                
        if( iLongitudLoc == 0 )
        {
            iLongitudLoc = mystrnlen( cValor );
        }
        
        iLen = iLongitudLoc > (int)campos.nodo()->nLongitud - 2 ? (int)campos.nodo()->nLongitud - 2 : iLongitudLoc;
        mymemcpy( campos.nodo()->pVar, cValor, iLen );
    }
}

short CRegistro::valorShort( const char *cNombre )
{
    short iValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( &iValor, campos.nodo()->pVar, sizeof( iValor ) );
    }

    return iValor;
}

void CRegistro::valorShort( const char *cNombre, short iValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &iValor, sizeof( iValor ) );
    }
}

long CRegistro::valorLong( const char *cNombre )
{
    long lValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( &lValor, campos.nodo()->pVar, sizeof( lValor ) );
    }

    return lValor;
}

void CRegistro::valorLong( const char *cNombre, long lValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &lValor, sizeof( lValor ) );
    }   
}

int64_t CRegistro::valorInt64( const char *cNombre )
{
    int64_t iValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( &iValor, campos.nodo()->pVar, sizeof( iValor ) );
    }

    return iValor;
}

void CRegistro::valorInt64( const char *cNombre, int64_t iValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &iValor, sizeof( iValor ) );
    }
}

float CRegistro::valorFloat( const char *cNombre )
{
    float fValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( &fValor, campos.nodo()->pVar, sizeof( fValor ) );
    }

    return fValor;
}

void CRegistro::valorFloat( const char *cNombre, float fValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &fValor, sizeof( fValor ) );
    }
}

double CRegistro::valorDouble( const char *cNombre )
{
    double dValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( &dValor, campos.nodo()->pVar, sizeof( dValor ) );
    }

    return dValor;
}

void CRegistro::valorDouble( const char *cNombre, double dValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &dValor, sizeof( dValor ) );
    }
}

SqlTimeStamp *CRegistro::valorFecha( const char *cNombre )
{
    SqlTimeStamp *tValor = NULL;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        tValor = (SqlTimeStamp *)campos.nodo()->pVar;
    }

    return tValor;
}

void CRegistro::valorFecha( const char *cNombre, SqlTimeStamp *tValor )
{
    bool bRespuesta = false;
    SqlTimeStamp *tValorLoc = NULL;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        tValorLoc = (SqlTimeStamp *)campos.nodo()->pVar;
        tValorLoc->ponerFecha( tValor->dia(), tValor->mes(), tValor->ano() );
    }
}

char *CRegistro::valorChar( int iCol )
{
    bool bRespuesta = false;
    int iLen = 0;
    mymemset( cBufferTemp, '\0', sizeof( cBufferTemp ) );

    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {   
        if(campos.nodo()->nLongitud > ( sizeof( cBufferTemp )) || campos.nodo()->nLongitud == ( sizeof( cBufferTemp )))
        {
            iLen = sizeof( cBufferTemp ) - 1;
        }
        else if (campos.nodo()->nLongitud < ( sizeof( cBufferTemp )))
        {
            iLen = campos.nodo()->nLongitud ;       
        }
        mymemcpy( cBufferTemp, campos.nodo()->pVar, iLen);  
    }

    return cBufferTemp;

}

void CRegistro::valorChar( int iCol, const char *cValor, int iLongitud )
{
    int iLen = 0;
    bool bRespuesta = false;
    int iLongitudLoc = 0;

    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        iLongitudLoc = iLongitud;
                
        if( iLongitudLoc == 0 )
        {
            iLongitudLoc = mystrnlen( cValor );
        }
        
        iLen = iLongitudLoc > (int)campos.nodo()->nLongitud - 2 ? (int)campos.nodo()->nLongitud - 2 : iLongitudLoc;
        mymemcpy( campos.nodo()->pVar, cValor, iLen );
    }
}

short CRegistro::valorShort( int iCol )
{
    short iValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( &iValor, campos.nodo()->pVar, sizeof( iValor ) );
    }

    return iValor;
}

void CRegistro::valorShort( int iCol, short iValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &iValor, sizeof( iValor ) );
    }
}

long CRegistro::valorLong( int iCol )
{
    long lValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( &lValor, campos.nodo()->pVar, sizeof( lValor ) );
    }

    return lValor;
}

void CRegistro::valorLong( int iCol, long lValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &lValor, sizeof( lValor ) );
    }
}

int64_t CRegistro::valorInt64( int iCol )
{
    int64_t iValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( &iValor, campos.nodo()->pVar, sizeof( iValor ) );
    }

    return iValor;
}

void CRegistro::valorInt64( int iCol, int64_t iValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &iValor, sizeof( iValor ) );
    }
}

float CRegistro::valorFloat( int iCol )
{
    float fValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( &fValor, campos.nodo()->pVar, sizeof( fValor ) );
    }

    return fValor;
}

void CRegistro::valorFloat( int iCol, float fValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &fValor, sizeof( fValor ) );
    }
}

double CRegistro::valorDouble( int iCol )
{
    double dValor = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( &dValor, campos.nodo()->pVar, sizeof( dValor ) );
    }
    
    return dValor;
}

void CRegistro::valorDouble( int iCol, double dValor )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        mymemcpy( campos.nodo()->pVar, &dValor, sizeof( dValor ) );
    }
}

SqlTimeStamp *CRegistro::valorFecha( int iCol )
{
    SqlTimeStamp *tValor = NULL;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        tValor = (SqlTimeStamp *)campos.nodo()->pVar;
    }

    return tValor;
}

void CRegistro::valorFecha( int iCol, SqlTimeStamp *tValor )
{
    bool bRespuesta = false;
    SqlTimeStamp *tValorLoc = NULL;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        tValorLoc = (SqlTimeStamp *)campos.nodo()->pVar;
        tValorLoc->ponerFecha( tValor->dia(), tValor->mes(), tValor->ano() );
    }
}

bool CRegistro::buscarCampo( const char *cNombre )
{
    bool bRespuesta = false;
    int nCols = campos.totalNodos();

    if( nCols > 0 )
    {
        campos.primero();

        do
        {
            if( strcmp( campos.nodo()->cNombre, cNombre ) == 0 )
            {
                bRespuesta = true;
            }

        }   while( !bRespuesta && campos.siguiente() );
    }

    return bRespuesta;
}

bool CRegistro::buscarCampo( int iCol )
{
    bool bRespuesta = false;
    int nCols = campos.totalNodos();
    int iCont = 0;

    if( nCols > 0 )
    {
        campos.primero();

        do
        {
            if( iCont != iCol )
            {
                iCont++;                
            }
            else
            {
                bRespuesta = true;
            }

        }   while( !bRespuesta && campos.siguiente() );
    }

    return bRespuesta;
}

void CRegistro::activarCols( void )
{
    int i = 0, nCols = campos.totalNodos();

    if( nCols > 0 )
    {
        flagInsertar = 1;
        campos.primero();

        do
        {
            Activar(i++, campos.nodo()->nCTipo, campos.nodo()->pVar, campos.nodo()->nLongitud, &(campos.nodo()->nLongResp) );

        }   while( campos.siguiente() );
    }
}
 
BOOL CRegistro::prepararInsert( const char *cNombreTabla )
{
    BOOL bRespuesta = FALSE;
    int i = 0, nCols = 0, iLen = 0, iV = 0, iC = 0;
    char cSqlTxtInsert[5000] = {0};
    char cSqlValues[2024] = {0};
    char cSqlCampos[2024] = {0}; 
                                                                  
    nCols = campos.totalNodos();

    if( nCols > 0 )
    {
        if( flagInsertar == 0 ) activarCols();

        campos.primero();
        iV += snprintf( cSqlValues,10,"%s", "VALUES (" );
        iC += snprintf( cSqlCampos,2,"%s", "(" );

        do
        {
            iV += snprintf(cSqlValues+iV,3,"%s","?,");
            iC += snprintf(cSqlCampos+iC,30,"%s",campos.nodo()->cNombre);
            iC += snprintf(cSqlCampos+iC,2,"%s",",");

        }   while( campos.siguiente() );

        iLen = (int)mystrnlen( cSqlValues );
        cSqlValues[ iLen - 1 ] = 0;

        iLen = (int)mystrnlen( cSqlCampos );
        cSqlCampos[ iLen - 1 ] = 0;

        iLen = snprintf( cSqlTxtInsert,4999, "INSERT INTO %.50s %.2023s) %.2023s)", cNombreTabla, cSqlCampos, cSqlValues );
        bRespuesta = CRecordSet::PrepararInsert(cSqlTxtInsert); 
        
        campos.primero();

        do
        {
            ActivarInsert(i++, campos.nodo()->nCTipo, campos.nodo()->nSqlTipo, campos.nodo()->pVar, campos.nodo()->nLongitud, &(campos.nodo()->nLongResp) );

        }   while( campos.siguiente() );
    }
    if(iV ==0 || iC == 0 || iLen == 0)
	{
		return false;
	}
	else
	{
		return bRespuesta;
	} 
}

int CRegistro::totalCampos( void )
{
    return campos.totalNodos();
}

int CRegistro::obtenerTipoDato( int iCol )
{
    int iTipo = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        iTipo = campos.nodo()->iTipo;
    }
    
    return iTipo;
}

int CRegistro::obtenerTipoDato( const char *cNombre )
{
    int iTipo = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        iTipo = campos.nodo()->iTipo;
    }
    
    return iTipo;
}

int CRegistro::obtenerTamanio( int iCol )
{
    int iTamanio = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        iTamanio = campos.nodo()->nLongitud;
    }
    
    return iTamanio;
}

int CRegistro::obtenerTamanio( const char *cNombre )
{
    int iTamanio = 0;
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        iTamanio = campos.nodo()->nLongitud;
    }
    
    return iTamanio;
}

bool CRegistro::tieneValorDefault( int iCol )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( iCol );

    if( bRespuesta )
    {
        bRespuesta = campos.nodo()->cFlgvDefault == '1' ? true : false;
    }
    
    return bRespuesta;
}

bool CRegistro::tieneValorDefault( const char *cNombre )
{
    bool bRespuesta = false;
    
    bRespuesta = buscarCampo( cNombre );

    if( bRespuesta )
    {
        bRespuesta = campos.nodo()->cFlgvDefault == '1' ? true : false;
    }
    
    return bRespuesta;
}

const char *CRegistro::error( void )
{
    this->odbc->GetLastError( GetHstmt() );
    mysnprintf( cBufferTemp,2047, "%d-%.256s", this->odbc->LastErrNum(), this->odbc->LastErrStr() );
    
	return cBufferTemp;
}
