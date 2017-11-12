#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* procedure d'affichage d'un tableau d'entiers */
void
afficherTableau
(int tab[], int lengthTab)
{   int i = 0;
    printf("[%d",tab[i]);
	for (i = 1 ; i < lengthTab ; i++)
		printf(", %d",tab[i]);
    printf("] \n");
}
/* procedure d'echange de deux élements d'indices a et b dans un tableau[0...a...b...n] d'éléments */
void
echanger
(int tab[], int a, int b)
{   int temp;

    /*printf("On échange les élements %d et %d .\n",tab[a],tab[b]);*/
	temp = tab[a];
	tab[a] = tab[b];
	tab[b] = temp;
}

/* procedure de partionnement d'un tableau d'entiers */
void
partitionner
(int tab[], const int v, const int g, const int d , int m)
{
	int i;
    for(i=g+1; i < d ; i++){
		if (tab[i] < v ){
			m++;
			echanger(tab,m,i);
		}
	}
	echanger(tab,m,g);
}

/* procedure de Tri QuickSort sur un tableau d'entiers */
void
QuickSort
(int tab[], const int g, const int d)
{
  int m; /* Position du pivot */
  int v; /* Valeur du pivot */

  if (g < d) {
	  v = tab[g];
	  m = g;
	  partitionner(tab,v,g,d,m);
      QuickSort(tab, g, m-1);
	  QuickSort(tab, m+1, d);
  }

}

/* procedure d'initialisation d'un tableau d'entiers de taille n
   avec des entiers choisis aléatoirement entre 1 et 100
*/
void
genereTableau
(int t[], const int n){
int i;
/* initialize random seed: */
srand ( time(NULL) );
for (i=0;i<n;i++)
	t[i]= rand() % 100 + 1;
}

int main(int argc, char** argv)
{

    int tableau[5];
    genereTableau(tableau,5);
    afficherTableau(tableau,5);
    QuickSort(tableau,0,5);
    afficherTableau(tableau,5);
	return 0;
}
