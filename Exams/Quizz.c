#include <stdio.h>
#include <stdlib.h>



/* 2.1 */
int cherche_et_incremente (int tab[], int size)
{
int valeurMin = tab[0];
int valeurMax = tab[0];
int i;
for (i=1;i<size;i++)
valeurMin = valeurMin > tab[i] ? tab[i] : valeurMin;
for (i=1;i<size;i++)
valeurMax = valeurMax < tab[i] ? tab[i] : valeurMax;
for (i=1;i<size;i++)
tab[i] = (valeurMax == tab[i]) ? tab[i]+= 1 : tab[i];
return valeurMin;
}

/* 2.2 */
/* affiche 45678910 */

/* 3.1 */
char
ComplementBase
(char c)
{
switch (c){
case 'A' : return 'T';break;
case 'T' : return 'A';break;
case 'C' : return 'G';break;
case 'G' : return 'C';break;
default : return 0;
}
}

/* 3.2 */
char*
ComplementBrin
(char* s){
int i;
int longueur;
char* res ;

/* Validité*/
longueur = 0;
for (i=0;s[i]!='\0';i++){
 switch (s[i]){
 case 'A' : ;break;
 case 'T' : ;break;
 case 'C' : ;break;
 case 'G' : ;break;
 default : return 0;
 }
 longueur++;
}

/* Allocation */
res = (char*)malloc(sizeof(char)*longueur++);
/* Complément ADN */
for (i=0;s[i]!='\0';i++)
res[i]=ComplementBase(s[i]);
return res;
}

int
main
(int argc, char** argv)
{

return 0;
}
