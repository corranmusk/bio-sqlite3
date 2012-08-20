/* BioLIb for sqlite3
A library of bioinformatics functions for sqlite3

Corran C. Musk 2012

Functions to be implemented:
	reverse
	compliment
	revcomp (reverse and compliment)
	translateDNAtoProtein(frame) (if neg uses reverse)
	dist
	align
*/

#include <sqlite3ext.h>
#include <assert.h>
#include "biolib.h"

SQLITE_EXTENSION_INIT1

/* cgcontent function
  calculate the proportion of C+G of a given dna sequence
*/
static void cgContentFunc(
		sqlite3_context *context,
		int argc,
		sqlite3_value **argv
){
	int 			cg_count, ct, i;
	double 			result;
	unsigned char 	*z;
	char 			t;
	
/* still need to deal with empty string */
	assert (argc==1);
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			cg_count=0;
			ct=0;
			for(i=0; z[i]; i++){
				ct++;
				t=toupper(z[i]);
				if(t=='C') cg_count++;
				if(t=='G') cg_count++;
			}
			result=(double) cg_count/(double) ct;
			sqlite3_result_double(context, result);
			sqlite3_free(z);
			break;
		}
		default: {
			sqlite3_result_null(context);
			break;
		}
	}
}

/* Molwt Function
  Calculates the Molecular Weight in Daltons of the specified DNA sequence
*/
static void MolWTFunc(
		sqlite3_context	*context,
		int 			argc,
		sqlite3_value 	**argv
){
	int 			i;
	double			result;
	unsigned char 	*z;
	char 			t;
	
	assert (argc==1);
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			result=0.0;
			for(i=0; z[i]; i++){
				t=toupper(z[i]);
				switch (t) {
					case 'C':{
						result+=289.2;
						break;
					}
					case 'A':{
						result+=313.2;
						break;
					}
					case 'G':{
						result+=329.2;
						break;
					}
					case 'T':{
						result+=304.2;
						break;
					}
				}
			}
			sqlite3_result_double(context, result);
			sqlite3_free(z);
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
		char 	**pzErrMsg,
		const 	sqlite3_api_routines *pApi
){
		SQLITE_EXTENSION_INIT2(pApi)
		sqlite3_create_function(db, "cgcontent", 1, SQLITE_ANY, 0, cgContentFunc, 0, 0);
		/* alias for cgcontent - gccontent */
		sqlite3_create_function(db, "gccontent", 1, SQLITE_ANY, 0, cgContentFunc, 0, 0);
		sqlite3_create_function(db, "molwt", 1, SQLITE_ANY, 0, MolWTFunc, 0, 0);
		return 0;
}
