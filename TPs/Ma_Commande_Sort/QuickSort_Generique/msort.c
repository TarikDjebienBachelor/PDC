#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readl.h"
#include "tools.h"
#include "qs.h"
#define MAXFILE 100

static int
cmpstringp
(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
    pointers to char", but strcmp(3) arguments are "pointers
    to char", hence the following cast plus dereference */
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}


int
main(int argc, char *argv[])
{
	if (argc == 1){
		int i;
        int j;
		/* le fichier lu */
		char fichierCourant[MAXFILE][MAXLINE+1];
		/* sa taille */
		int nbLigneFichier = 0;
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* On recupere chaque ligne */
	    for (i=0 ; readl(ligneCourante) != EOF ; i++){
		/* que l'on stocke dans notre fichierCourant */
		strcpy (fichierCourant[i],ligneCourante);
        /* et on incremente le nombre de ligne dans le fichier */
		nbLigneFichier++;
		}

		/* On applique notre QuickSort Generique */
		my_quicksort(&fichierCourant[0], nbLigneFichier , sizeof(fichierCourant[1]) , cmpstringp);

		/* Remarque :
		 * Ici le probleme vient du fait que le 3eme parametre de my_quicksort
		 * representant la taille en octet d'un élement du tableau varie selon la case du tableau
		 * car la taille d'une chaine de caractere varie en fonction du nombre de caractere contenu
		 * dans la chaine, ceci est genant car on ne peut pas appliquer notre quicksort generique.
		 * Une solution est proposé dans le README.txt proposant une autre structure de donnée.
		 * /

		/* On parcours chaque ligne du fichier trié par le quicksort */
		for (j = 0; j < nbLigneFichier; j++){
		/* On affiche la ligne courante sur la sortie standard : */
		fprintf(stdout,"%s",fichierCourant[j]);
		/* et on passe à la ligne */
		putchar('\n');
		}
		exit(EXIT_SUCCESS);

	}
	else fatal(0,"Usage: msort < fileStdIn ...\n",EXIT_FAILURE);

	return 0;
}

