#include <stdio.h>
#include <string.h>
#include "readl.h"
#include "tools.h"

int main(int argc, char** argv)
{
	if (argc == 1 )
	fatal(0,"entrer au minimum un argument. \nUsage : mlook string \n",EXIT_FAILURE);
	else if (argc == 2){
		/* word */
		char* argument1 = argv[1];
		/* succés de mlook */
		int OK = EXIT_FAILURE;
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* et sa longueur */
		int longeurLigneCourante = 0;
		/* recuperé pour chaque ligne */
	    while ( (longeurLigneCourante = readl(ligneCourante)) != EOF)
		{
			/*le premier mot de notre ligne */
			char* premierMot;
			/* la copie de notre ligne */
			char* maLigneLu;
			/* On recopie la ligneCourante pour ne pas la modifier */
			maLigneLu = strcpy(maLigneLu,ligneCourante);
			/* On recupere le premier mot de la ligneCourante (remarque: strtok modifie maLigneLu en parametre). */
			premierMot = strtok (maLigneLu," ,.-");
			/* Si la ligneCourante commence par le parametre de mlook */
			if (strcmp(argument1, premierMot) == 0){
			 /* On affiche la ligne courante */
			 fprintf(stdout,"%s",ligneCourante);
			 /* et on passe à la ligne */
			 putchar('\n');
			 /* La commande mlook est donc un succés */
			 OK = EXIT_SUCCESS;
			}
		}
		/* On a lu tout le fichier sur StdIn */
		/* On termine la commande sur un échec : */
		fatal(OK == EXIT_SUCCESS,"Aucune ligne ne debute par ce mot.\n",EXIT_FAILURE);
		/* Ou un succés : */
		exit(OK);
	}
	else fatal(0,"entrer au maximum un argument. \nUsage : mlook string \n",EXIT_FAILURE);

	return 0;
}
