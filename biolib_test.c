/* BioLIb test program

Corran C. Musk 2012

*/

#include <string.h>
#include <stdio.h>
#include "biolib.h"

int main() {
	unsigned char *seq1, *seq2, *align;
	int int_result;
	double dbl_result;

	seq1="AAAAATCATGCATGCTA";
	seq2="CAAGCTAGGCATGATCC";

	printf("Sequence 1: %s\n",seq1);
	dbl_result=libcgContentFunc(seq1);
	printf("C+G Content : %f\n",dbl_result);
	printf("Sequence 2: %s\n",seq2);
	int_result=libLevenshteinDistFunc(seq1,seq2);
	printf("Levenshtein distance : %d\n",int_result);
	int_result=global_align_score(seq1,seq2,align);
	printf("Global align score : %d\n",int_result);
	printf("Alignment %s\n",align);

	return 0;
}
