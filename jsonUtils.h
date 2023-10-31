#ifndef _wsprestamos_PROTO_JSON_
#define _wsprestamos_PROTO_JSON_

#include <C_ODBC.hpp>
#include "estructuras.h"
#include "definiciones.h"
#include "gnfunciones.h"
#include "gnlog.h"

#include "json.h"

void displayJson(struct value *v);
void displayJson(struct value *v, char *cJson);
void displayJson2(struct value *v,C_ODBC *odbcDBTiendaNumero);
void displayJson3(struct value *v);


#endif //_wsprestamos_PROTO_JSON_
