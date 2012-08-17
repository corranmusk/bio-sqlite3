#include <sqlite3ext.h>
#include <assert.h>

SQLITE_EXTENSION_INIT1

static void cgContentFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int cg_count, ct, i;
  double result;
  unsigned char *z;

  assert (argc==1);
  switch( sqlite3_value_type(argv[0]) ){
    case SQLITE_TEXT:{
      z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
      strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
      cg_count=0;
      ct=0;
      for(i=0; z[i]; i++){
        ct++;
        if(toupper(z[i])=='C') cg_count++;
        if(toupper(z[i])=='G') cg_count++;
      }
      result=(double) cg_count/(double) ct;
      sqlite3_result_double(context, result);
      break;
    }
    default: {
      sqlite3_result_null(context);
      break;
    }
  }
}

/* SQLite invokes this routine once when it loads the extension.
** Create new functions, collating sequences, and virtual table
** modules here.  This is usually the only exported symbol in
** the shared library.
*/
int sqlite3_extension_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
){
  SQLITE_EXTENSION_INIT2(pApi)
  sqlite3_create_function(db, "cgcontent", 1, SQLITE_ANY, 0, cgContentFunc, 0, 0);
  return 0;
}
