#include <stdio.h>
#include <stdlib.h>
#include "qsint.h"

void
swap
(int *x, int *y)
{
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

int
choose_pivot_median
(int i, int j )
{
   return((i+j) /2);
}

int
choose_pivot_inf
(int i, int j )
{
   return i;
}

int
choose_pivot_sup
(int i, int j )
{
   return j;
}

void
quicksort
(int tab[], int g, int d)
{
   int key,i,j,k;
   if( g < d)
   {
      k = choose_pivot_inf(g,d);
      swap(&tab[g],&tab[k]);
      key = tab[g];
      i = g+1;
      j = d;
      while(i <= j)
      {
         while((i <= d) && (tab[i] <= key))
                i++;
         while((j >= g) && (tab[j] > key))
                j--;
         if( i < j)
                swap(&tab[i],&tab[j]);
      }
	  /* swap two elements */
      swap(&tab[g],&tab[j]);
	  /* recursively sort the lesser array */
      quicksort(tab,g,j-1);
      quicksort(tab,j+1,d);
   }
}

/* print an array of integers */
void
printArray
(int tab[], int lengthTab)
{   int i = 0;
    printf("[%d",tab[i]);
	for (i = 1 ; i < lengthTab ; i++)
		printf(", %d",tab[i]);
    printf("] \n");
}
