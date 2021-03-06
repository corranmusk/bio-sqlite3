/* BioLIb for sqlite3
A library of bioinformatics functions for sqlite3

Corran C. Musk 2012

*/

#include <sqlite3ext.h>
#include <string.h>
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
	double 		result;
	unsigned char 	*z;
	
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			result=libcgContentFunc(z);
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
	double		result;
	unsigned char 	*z;
	
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			result=libMolWTFunc(z);
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

/* HammingDistFunc
 * Calculates the Hamming distance between two strings
 * Strings must be of same length otherwise returns -1
*/

static void HammingDistFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	int		result;
	unsigned char 	*z0, *z1;
	
	z0 = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
	strcpy((char*)z0,(char*)sqlite3_value_text(argv[0]));
	z1 = sqlite3_malloc(sqlite3_value_bytes(argv[1])+1);
	strcpy((char*)z1,(char*)sqlite3_value_text(argv[1]));
	result=libHammingDistFunc(z0,z1);
	if (result==-1){
		sqlite3_result_null(context);
	} else {
		sqlite3_result_int(context, result);
	}
	sqlite3_free(z0);
	sqlite3_free(z1);
}


static void LevenshteinDistFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	int		result;
	unsigned char 	*z0, *z1;
	
	z0 = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
	strcpy((char*)z0,(char*)sqlite3_value_text(argv[0]));
	z1 = sqlite3_malloc(sqlite3_value_bytes(argv[1])+1);
	strcpy((char*)z1,(char*)sqlite3_value_text(argv[1]));
	result=libLevenshteinDistFunc(z0,z1);
	sqlite3_result_int(context, result);
	sqlite3_free(z0);
	sqlite3_free(z1);
}

static void ReverseFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	unsigned char 	*z;
	
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			libReverseFunc(z);
			sqlite3_result_text(context, z,strlen(z),SQLITE_STATIC);
			sqlite3_free(z);
			break;
		}
		default: {
			sqlite3_result_null(context);
			break;
		}
	}
}

static void CompDNAFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	unsigned char 	*z;
	
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			libCompDNAFunc(z);
			sqlite3_result_text(context, z,strlen(z),SQLITE_STATIC);
			sqlite3_free(z);
			break;
		}
		default: {
			sqlite3_result_null(context);
			break;
		}
	}
}

static void CompRevFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	unsigned char 	*z;
	
	switch( sqlite3_value_type(argv[0]) ){
		case SQLITE_TEXT:{
			z = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
			strcpy((char*)z,(char*)sqlite3_value_text(argv[0]));
			libCompRevFunc(z);
			sqlite3_result_text(context, z,strlen(z),SQLITE_STATIC);
			sqlite3_free(z);
			break;
		}
		default: {
			sqlite3_result_null(context);
			break;
		}
	}
}

/* GlobalAlignScore func
 * Calculate the score of a global alignment opf two sequences
 */
 
static void GlobalAlignScoreFunc(
	sqlite3_context	*context,
	int 			argc,
	sqlite3_value 	**argv
){
	int		result;
	unsigned char 	*z0, *z1, *al;
	
	z0 = sqlite3_malloc(sqlite3_value_bytes(argv[0])+1);
	strcpy((char*)z0,(char*)sqlite3_value_text(argv[0]));
	z1 = sqlite3_malloc(sqlite3_value_bytes(argv[1])+1);
	strcpy((char*)z1,(char*)sqlite3_value_text(argv[1]));
	al =sqlite3_malloc(sqlite3_value_bytes(argv[0])+sqlite3_value_bytes(argv[1])+1);
	result=libGlobalAlign(z0,z1,al);
	sqlite3_result_int(context, result);
	sqlite3_free(z0);
	sqlite3_free(z1);
	sqlite3_free(al);
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
	// alias for cgcontent - gccontent
	sqlite3_create_function(db, "gccontent", 1, SQLITE_ANY, 0, cgContentFunc, 0, 0);
	sqlite3_create_function(db, "molwt", 1, SQLITE_ANY, 0, MolWTFunc, 0, 0);
	sqlite3_create_function(db, "hammingdist", 2, SQLITE_ANY, 0, HammingDistFunc, 0, 0);
	sqlite3_create_function(db, "levenshteindist", 2, SQLITE_ANY, 0, LevenshteinDistFunc, 0, 0);
	//alias for levensteindist - levdist
	sqlite3_create_function(db, "levdist", 2, SQLITE_ANY, 0, LevenshteinDistFunc, 0, 0);
	sqlite3_create_function(db, "revseq", 1, SQLITE_ANY, 0, ReverseFunc, 0, 0);
	sqlite3_create_function(db, "compDNA", 1, SQLITE_ANY, 0, CompDNAFunc, 0, 0);
	sqlite3_create_function(db, "comprev", 1, SQLITE_ANY, 0, CompRevFunc, 0, 0);
	sqlite3_create_function(db, "globalalignscore", 2, SQLITE_ANY, 0, GlobalAlignScoreFunc, 0, 0);
	
	return 0;
}
