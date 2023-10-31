#include "jsonUtils.h"

void displayJson(struct value *v)
{
    char cJson[35000] = {0};
    
    displayJson( v, cJson );    
    logx( cJson ,_LOGINFO_);
}

void displayJson2(struct value *v,C_ODBC *odbcDBTiendaNumero)
{
    char cJson[150000] = {0};
    
    displayJson( v, cJson );
    encondeBase64(odbcDBTiendaNumero,cJson);//no esta permitido por riesgos
}

void displayJson3(struct value *v)
{
    char cJson[150000] = {0};

    displayJson( v, cJson );
    //enconde(cJson);
}

void displayJson(struct value *v, char *cJson)
{
    char cTexto[1024] = {0};
    
    if (v->is_bool())
    {
        mysnprintf( cTexto,1024, "%s", v->is_true() ? "true" : "false" );
        mystrcat( cJson, cTexto );
    }
    else if (v->is_int())
    {
        mysnprintf( cTexto,1024, "%lld", (long long int)*v );
        mystrcat( cJson, cTexto );
    }    
    else if (v->is_double())
    {
        mysnprintf( cTexto,1024, "%lG", (double)*v );
        mystrcat( cJson, cTexto );
    }
    else if (v->is_string())
    {
//        mysnprintf( cTexto,1024, "\"%s\"", (char *)*v );
		mysnprintf( cTexto,1024, "\"%s\"", (char *)*v );
        mystrcat( cJson, cTexto );
    }    
    else if (v->is_array())
    {
        mystrcat( cJson, "[" );
        _array& vec = *v;  // cast to _array
        int array_index = 0;
        int j = 0;

        for(_array::iterator i = vec.begin(); i != vec.end(); ++i, j++ )
        {
            if (j) mystrcat( cJson, "," );
            array_index = i.index();
            value& array_value = *i;
            displayJson( &array_value, cJson );
        }

        mystrcat( cJson, "]" );
        
    }
    else if (v->is_struct())
    {        
        mystrcat( cJson, "{" );
        _struct& rec = *v;  // cast to _struct
        int j = 0;

        for (_struct::iterator i = rec.begin(); i != rec.end(); ++i, j++)
        {
            if (j) mystrcat( cJson, "," );
            const char *member_name = i.name();
            value& val = *i;

            mysnprintf( cTexto,1024, "\"%s\": ", member_name );
            mystrcat( cJson, cTexto );
            displayJson( &val, cJson );
        } 
      
        mystrcat( cJson, "}" );
    }
}
