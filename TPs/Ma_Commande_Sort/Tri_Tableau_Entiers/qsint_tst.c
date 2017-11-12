#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qsint.h"
#define MAX_ELEMENTS 20



int
main()
{
   int i = 0;
   /* An array of integers */
   int array[MAX_ELEMENTS];

   /* initialize random seed: */
	srand ( time(NULL) );

   /* generate random numbers between 1 and 100 and fill them to the array of integer */

   for(i = 0; i < MAX_ELEMENTS; i++ ){
	   array[i] = rand()% 100 + 1;
   }

   printf("The array before sorting is:\n");
   printArray(array,MAX_ELEMENTS);

   /* sort the array using quicksort algorithm */
   quicksort(array,0,MAX_ELEMENTS-1);

   /* print the array result after sorting */
   printf("The array after sorting using quicksort algorithm:\n");
   printArray(array,MAX_ELEMENTS);

   return 0;
}
