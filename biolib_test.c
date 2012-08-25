/* BioLIb for sqlite3

Corran C. Musk 2012

*/

#include <string.h>
#include <stdio.h>
#include "biolib.h"

int main() {
	unsigned char *z;
	int int_result;
	double dbl_result;

	z="AAAAATCATGCATGCTA";

	dbl_result=libcgContentFunc(z);
	printf("C+G Content : %f\n",dbl_result);
	return 0;
}
