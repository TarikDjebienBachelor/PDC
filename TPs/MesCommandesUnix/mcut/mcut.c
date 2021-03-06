#include <stdio.h>
#include "readl.h"
#include "tools.h"

int main(int argc, char** argv)
{
	if (argc == 1 || argc == 2)
	fatal(0,"entrer au minimum deux argument. \n Usage : mcut delim fieldno [fieldno] \n",EXIT_FAILURE);
	else if (argc == 3){
		/* delimiteur represente une seule lettre */
		char delimiteur = argv[1][0];
		/* Fieldno */
		int argument1 = atoi(argv[2]);
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* et sa longueur */
		int longeurLigneCourante = 0;
		/* le nombre de fieldno */
		int nbColonnes = 1;
		/* recuperé pour chaque ligne */
	    while ( (longeurLigneCourante = readl(ligneCourante)) != EOF)
		{
			int i ;
			nbColonnes = 1;
			for (i=0 ; i < longeurLigneCourante ; i++){
			  if (ligneCourante[i] == delimiteur) {
				nbColonnes++;
				if (nbColonnes >= argument1){
					while(ligneCourante[++i] != '\0')
					putchar(ligneCourante[i]);
				}
			  }
			}/*endfor*/
		putchar('\n');
		}
	}
	else if (argc == 4){
		/* delimiteur represente une seule lettre */
		char delimiteur = argv[1][0];

		/* Fieldno */
		int argument1 = atoi(argv[2]);

		/* [Fieldno] */
		int argument2 = atoi(argv[3]);

		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";

		/* et sa longueur */
		int longeurLigneCourante = 0;

		/* le nombre de fieldno */
		int nbColonnes = 1;

		/* recuperé pour chaque ligne */
	    while ( (longeurLigneCourante = readl(ligneCourante)) != EOF)
		{
			int i ;
			nbColonnes = 1;

			for (i=0 ; i < longeurLigneCourante ; i++){

			  if (ligneCourante[i] == delimiteur) {
				nbColonnes++;
				if (nbColonnes >= argument1 && nbColonnes <= argument2){
					while(ligneCourante[++i] != delimiteur ){
					putchar(ligneCourante[i]);
					}
				i--;
				if (nbColonnes >= argument1 && nbColonnes < argument2)
				putchar(delimiteur);
				}
			  }
			}/*endfor*/
		putchar('\n');
		}

	}
	else fatal(0,"entrer au maximum trois arguments. \n Usage : mcut delim fieldno [fieldno] \n",EXIT_FAILURE);

	return 0;
}
