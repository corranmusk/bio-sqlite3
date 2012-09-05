/* BioLIb
A library of bioinformatics functions

Corran C. Musk 2012

Functions to be implemented (among others):
	translateDNAtoProtein(frame) (if neg uses reverse)
	dist
	align
*/

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/* defaults */
const int GAP_PENALTY=-1;
const int DIFF_PENALTY=1;
const int MATCH_SCORE=2;
const unsigned int DOWN=1;
const unsigned int RIGHT=2;
const unsigned int DIAG=3;


/* ReverseFunc : reverses a string
**	requires pointer to string
*/

void libReverseFunc(char *str)
{
	// Bit clunky but it works, certainly room for improvement!
	char *tmp_str;
	int i,str_len;

	// create a temporary space for string
	tmp_str=malloc(strlen(str));
	// copy original into temp
	strcpy(tmp_str,str);
	// get length of string
	str_len=strlen(tmp_str)-1;
	// for each character in the temp put in opposite position in original
	for (i=0; i<=str_len; ++i){
		str[i]=tmp_str[str_len-i];
	}
	// tidy up
	free(tmp_str);
}

/* ComplimentDNAFunc : Compliments DNA, preserves case
**	requires pointer to str to be complimented
*/

void libCompDNAFunc(char *str)
{
	char *tmp_str;
	int i,str_len;

	tmp_str=malloc(strlen(str));
	strcpy(tmp_str,str);
	str_len=strlen(tmp_str);
	for (i=0; i<str_len; ++i){
		switch (tmp_str[i]){
			case 'a':
				str[i]='t';
				break;
			case 'A':
				str[i]='T';
				break;
			case 'g':
				str[i]='c';
				break;
			case 'G':
				str[i]='C';
				break;
			case 'c':
				str[i]='g';
				break;
			case 'C':
				str[i]='G';
				break;
			case 't':
				str[i]='a';
				break;
			case 'T':
				str[i]='A';
				break;
			default:
				str[i]=tmp_str[i];
		}
	}
	free(tmp_str);
}

/* comprev : reverses and compliments a DNA sequence
	requires pointer to string
*/

void libCompRevFunc(char *seq)
{
	libReverseFunc(seq);
	libCompDNAFunc(seq);
}


/* cgcontentFunc : calculate the proportion of C+G of a given dna sequence
	 requires a string
	 returns a double
*/

double libcgContentFunc(unsigned char *z)
{
	int 	cg_count, ct, i;
	double 	result;
	char 	t;
	
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

/* MolWTFunc : Calculates the Molecular Weight in Daltons of the specified DNA sequence
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

/* HammingDistFunc : Calculates Hamming distance 
	Requires 2 strings for comparison, ignores case
	returns -1 if strings are different lengths otherwise calculates Hamming distance
*/

int libHammingDistFunc(char *seq1, char *seq2)
{

	int 	result,i;

	// Check string lengths
	if (strlen(seq1)!=strlen(seq2)){
		// Different so result is -1 
		result=-1;
	} else {
		result=0;
		for(i=0; i<strlen(seq1); i++){
			if (toupper(seq1[i])!=toupper(seq2[i])) ++result;
		}
	}
	return result;
}

/* LevenshteinDistFunc : Calculates Levenshtein distance 
	Requires 2 strings for comparison, ignores case
	returns calculated Levenshtein distance
*/

int libLevenshteinDistFunc (char *seq1, char *seq2) {

	// Function to return the minimum of two integers
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

int global_align_score (char *seq1 , char *seq2, char *alignseq)
{
	int seq1len,seq2len;
	int i,j;
	int a,b,c;
	int result;
	
	seq1len=strlen(seq1);
	seq2len=strlen(seq2);
	
	int scores[seq1len+1][seq2len+1];
	scores[0][0]=0;
	unsigned int dirs[seq1len+1][seq2len+1];
	for(i=0;i<=seq1len;i++){
		for(j=0; j<=seq2len;j++){
			if(i==0){
				scores[0][j]=j * GAP_PENALTY;
				dirs[0][j]=DOWN;
			}
			if (j==0){
				scores[i][0]=i * GAP_PENALTY;
				dirs[i][0]=RIGHT;
			}  
			if((j!=0) && (i!=0)){
				a=scores[i-1][j-1];
				if (toupper(seq1[i])==toupper(seq2[j])) {
					a+=MATCH_SCORE;
				} else {
					a+=DIFF_PENALTY;
				}
				b=scores[i-1][j] + GAP_PENALTY;
				c=scores[i][j-1] + GAP_PENALTY;
				if ((a>b) && (a>c)){
					scores[i][j]=a;
					dirs[i][j]=DIAG;
				} else {
					if ((b>c) && (b>a)){
						scores[i][j]=b;
						dirs[i][j]=RIGHT;
					} else {
						scores[i][j]=c;
						dirs[i][j]=DOWN;
					}
				}
			}
		}
	}
	dirs[0][0]=0;
	i--;
	j--;
	result=scores[i][j];
	/*char retseq1[i+j];
	char retseq2[i+j];*/
	//unsigned char alignseq[i+j];
	int seqpos=0;
	do
	{
		switch (dirs[i][j]){
			case 1:		//DOWN
				j--;
				alignseq[seqpos]=tolower(seq2[j]);
				break;
			case 2:		//RIGHT
				i--;
				alignseq[seqpos]=tolower(seq2[i]);
				break;
			case 3:		//DIAG
				i--;
				j--;
				if (seq1[i]==seq2[j]){
					//match
					alignseq[seqpos]=toupper(seq2[j]);					
				} else {
					//mismatch
					alignseq[seqpos]='*';
				}
				break;
		}
		seqpos++;
	} while (i>0 && j>0);
	libReverseFunc(alignseq);
	return result;
}
