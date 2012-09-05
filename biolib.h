/* BioLIb
A library of bioinformatic functions

Corran C. Musk 2012
*/

// function defs
extern void libReverseFunc (char *str);
extern void libCompDNAFunc (char *str);
extern void libCompRevFunc (char *str);
extern double libcgContentFunc (unsigned char *sequence);
extern double libMolWTFunc (unsigned char *sequence);
extern int libHammingDistFunc (unsigned char *seq1, unsigned char *seq2);
extern int libLevenshteinDistFunc (char *seq1, char *seq2);
extern int global_align_score (char *seq1 , char *seq2, char *alignseq);

