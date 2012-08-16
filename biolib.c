#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

static void cgContentFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int gc_count;
  int i;
  int ct;
  double result;

  gc_count=100;
  ct=2000;
  result=(double) gc_count/(double) ct;
  
/*sqlite3_value_text(argv[0])*/
  sqlite3_result_double(context, result);
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
