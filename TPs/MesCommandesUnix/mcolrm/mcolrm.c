#include <stdio.h>
#include "readl.h"
#include "tools.h"

int main(int argc, char** argv)
{
	if (argc == 1)
	fatal(0,"entrer au minimum un argument.\n",EXIT_FAILURE);
	else if (argc == 2){
		/* on recupere le premier argument */
		int argument1 = atoi(argv[1]);
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* recuperé pour chaque ligne */
		while (readl(ligneCourante) != EOF)
		{
		int i ;
		   for (i=0;i < argument1-1;i++){
		       putchar(ligneCourante[i]);
		   }
		putchar('\n');
		}
	}
	else if (argc == 3){
	/* on recupere le premier argument */
	int argument1 = atoi(argv[1]);
	/* on recupere le second  argument */
	int argument2 = atoi(argv[2]);
		/* la ligne courante */
		char ligneCourante[MAXLINE+1]="";
		/* recuperé pour chaque ligne */
		while (readl(ligneCourante) != EOF)
		{
		int i ;
		   for (i=0;i < argument1-1;i++){
		       putchar(ligneCourante[i]);
		   }
		   for (i=argument1-1;i<argument2;i++){
		       /* ne rien faire */
		   }
		   for (i=argument2;ligneCourante[i] != '\0';i++){
		       putchar(ligneCourante[i]);
		   }
		putchar('\n');
		}
	}
	else fatal(0,"entrer au maximum deux arguments.",EXIT_FAILURE);

	return 0;
}

