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
double libcgContentFunc(unsigned char *z)
{
	int 			cg_count, ct, i;
	double 			result;
	char 			t;
	
/* still need to deal with empty string */
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




