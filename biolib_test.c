/* BioLIb for sqlite3

Corran C. Musk 2012

*/

#include <string.h>
#include <stdio.h>
#include "biolib.h"

int main() {
	unsigned char *seq1, *seq2;
	int int_result;
	double dbl_result;

	seq1="AAAAATCATGCATGCTA";
	seq2="CTAGCTAGGCATGATCC";

	dbl_result=libcgContentFunc(seq1);
	printf("C+G Content : %f\n",dbl_result);
	int_result=libLevenshteinDistFunc(seq1,seq2);
	printf("Levenshtein distance : %d\n",int_result);

	return 0;
}
