#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* procedure d'affichage d'un tableau de char */
void
afficherTableau
(char tab[], int lengthTab)
{   int i = 0;
    printf("[%c",tab[i]);
	for (i = 1 ; i < lengthTab ; i++)
		printf(", %c",tab[i]);
    printf("] \n");
}
/* procedure d'echange de deux élements d'indices a et b dans un tableau[0...a...b...n] d'éléments */
void
echanger
(char tab[], int a, int b)
{   char temp;

    /*printf("On échange les élements %d et %d .\n",tab[a],tab[b]);*/
	temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

/* procedure de Tri QuickSort sur un tableau d'entiers */
void
TriBulle
(char tab[], const int size)
{
int i,j;
for (i=size;i>0;i--)
  for(j=0;j<i-1;j++)
     if (tab[j]>tab[j+1])
       echanger(tab,j,j+1);
}

/* procedure d'initialisation d'un tableau de char de taille n
   avec des char choisis aléatoirement entre A et Z.
*/
void
genereTableau
(char t[], const int n){
int i;
int MAX = 90;
int MIN = 65;
/* initialize random seed: */
srand ( time(NULL) );
for (i=0;i<n;i++)
	t[i]= (rand() % (MAX - MIN + 1)) + MIN;
}

int main(int argc, char** argv)
{

    char tableau[5];
    genereTableau(tableau,5);
    afficherTableau(tableau,5);
    TriBulle(tableau,5);
    afficherTableau(tableau,5);
	return 0;
}

