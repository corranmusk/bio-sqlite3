/* BioLIb
A library of bioinformatic functions

Corran C. Musk 2012

Functions to be implemented:
	reverse
	compliment
	revcomp (reverse and compliment)
	translateDNAtoProtein(frame) (if neg uses reverse)
	dist
	align
*/


/* cgcontent function
  calculate the proportion of C+G of a given dna sequence
	 requires a string
	 returns a double
*/

#include <string.h>


double libcgContentFunc(unsigned char *z)
{
	int 			cg_count, ct, i;
	double 			result;
	char 			t;
	
	cg_count=0;
	ct=0;
	for(i=0; z[i]; i++){
		ct++;
		t=toupper(z[i]);
		if(t=='C') ++cg_count;
		if(t=='G') ++cg_count;
	}
	result=(double) cg_count/(double) ct;
	return result;
}

/* Molwt Function
  Calculates the Molecular Weight in Daltons of the specified DNA sequence
	requires a string
	returns a double
*/
double libMolWTFunc(unsigned char *sequence)
{
	int 			i;
	double			result;
	char 			t;
	
	result=0.0;
	for(i=0; sequence[i]; i++){
		t=toupper(sequence[i]);
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
	return result;
}

int libHammingDistFunc(unsigned char *seq1, unsigned char *seq2)
{
	// Calculates Hamming distance, returns -1 if strings are different lengths
	// Requires 2 strings for comparison, ignores case

	int 	result,i;

	// Check string lengths
	if (strlen(seq1)!=strlen(seq2)){
		// Different so result is -1 
		result=-1;
	} else {
		result=0;
		for(i=0; i<strlen(seq1); i++){
			if (toupper(seq1[i])==toupper(seq2[i])) ++result;
		}
	}
	return result;
}

int libLevenshteinDistFunc (char *seq1, char *seq2) {
// Calculates Levenshtein Distance between two sequences
// Note that it ignores case

	// Function to calculate minimum between two integers
	int min( int a, int b ){ return ( a < b ) ? a : b;}
	// Calculate length of strings;
	int la = strlen ( seq1 );
	int lb = strlen ( seq2 );
	// Check that strings aren't empty...
	if( la == 0 ) return lb;
	if( lb == 0 ) return la;
	// ...and that seq1 is longer than seq2
	if( la > lb ) {
		return libLevenshteinDistFunc ( seq2, seq1 );
	}else{
		// set up vars
		int current[ la + 1 ];
		int previous[ la + 1 ];
		int i,j;
		// set-up initial state
		for( i = 0; i < ( la + 1 ); i++ ) {
			current[ i ]= i;
		}
		// Main calculation loop
		int x, y, z;
		for ( j = 1;  j < ( lb + 1 ); j++ ) {
			// Move down a row at a time
			previous[ 0 ] = current[ 0 ];
			current[ 0 ] = j;
			for ( i = 1; i < ( la + 1 ); i++ ) {
				previous[ i ] = current[ i ];
				x = current[ i ] + 1;
				y = current[ i - 1 ] + 1;
				z = previous[ i - 1 ] + ( (toupper(seq1[i-1]) == toupper(seq2[j-1]) ) ? 0 : 1 );
				current[ i ] = min ( x , min ( y , z ) );
			}
		}
		return current[ la ];
	}
}

