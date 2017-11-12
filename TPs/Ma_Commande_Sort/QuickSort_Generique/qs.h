#include <stdio.h>
#include <stdlib.h>

/* Trier des tableaux de type quelconque.

   -base  : une reference sur le premier élément du tableau à trier.
   -nmemb : le nombre d'éléments du tableau à trier.
   -size  : la taille en octets, d'un élément du tableau.
   -compar: un pointeur sur la fonction de comparaison.
            Cette fonction accepte deux références sur les éléments
            à comparer et retourne la valeur de la comparaison selon
            le principe de la fonction.
*/
extern
void
my_quicksort
(void *base, int nmemb, int size, int (*compar)(const void *, const void *));
