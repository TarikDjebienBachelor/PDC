#include <stdio.h>
#include <stdlib.h>

#define swap(p1,p2,sz)          {                               \
                                    size_t j;                   \
                                    for (j=0; j<sz; j++)        \
                                    {                           \
                                        char ptmp = *(p1+j);    \
                                        *(p1+j) = *(p2+j);      \
                                        *(p2+j) = ptmp;         \
                                    }                           \
                                }

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
(void *base, int nmemb, int size, int (*compar)(const void *, const void *)){

 char *debut, *fin, *gauche, *droite, *pivot;

 debut = base;
 fin = debut+(size*nmemb)-size;
 while (debut < fin){
     gauche = debut;
     droite = fin;
     /* on choisit un pivot au milieu du tableau,
       (et on le place au début pour le partitionnement) */
     swap (debut, debut+(((fin-debut)/(size*2))*size), size);
     pivot = debut;
     /* Partitionnement */
        do
        {
            while (gauche < droite && compar(droite, pivot) > 0)
                droite -= size;
            swap (gauche, droite, size);
            pivot = droite;

            while (gauche < droite && compar(gauche, pivot) <= 0)
                gauche += size;
            swap (droite, gauche, size);
            pivot = gauche;
        }
        while (gauche < droite);

        /* Pour minimiser les appels récursifs */
        if (gauche-debut < fin-gauche)
        {
            my_quicksort(debut, (gauche-debut)/size, size, compar);
            debut = gauche+size;
        }
        else
        {
            my_quicksort(gauche+size, (fin-gauche)/size, size, compar);
            fin = gauche-size;
        }
    }
}
