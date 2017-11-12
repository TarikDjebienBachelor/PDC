#include<stdio.h>
#define SIZE 65000
char memoire[SIZE] ;

struct cellule_m{
  unsigned int contenu ;
  struct cellule_m *next ;
} ;

typedef struct cellule_m cellule_t ;

/* pour compenser l'absence de fonction free, on utilise */
cellule_t *ListeDesCellulesLibres = NULL ;  

/* on peut ensuite avoir autant de listes que n\'ecessaire */

cellule_t *maliste = NULL ;  

int estvide(cellule_t *liste){
  return !liste ;
}

void inserer(cellule_t *cell,cellule_t **liste){

  cellule_t *tmp=NULL, *ptr = *liste ;

  while(ptr && ptr->contenu < cell->contenu){
    tmp = ptr ;
    ptr = ptr->next ;
  }

  cell->next = ptr ;
  if(tmp)
    tmp->next = cell ;
  else *liste = cell  ;
}

void extraire(cellule_t *cell, cellule_t **liste){

  cellule_t *tmp=NULL, *ptr = *liste ;

  while(ptr && ptr != cell){
    tmp = ptr ;
    ptr = ptr->next ;
  }

  if(tmp)
    tmp->next = cell ->next ;
  else *liste = NULL ;
}

char *sommet = memoire ;

void supprimerCellule(cellule_t *cell){

  inserer( cell, &ListeDesCellulesLibres ) ;

} 

cellule_t *creerCellule(unsigned int stuff){

  cellule_t *tmp = ListeDesCellulesLibres ;
  if( tmp ){
    extraire( tmp, &ListeDesCellulesLibres ) ;
    tmp->contenu = stuff ; 
    return tmp ; 
  }
  
  if(SIZE-(sommet-memoire)<sizeof(cellule_t))
     return NULL ;

  tmp = (cellule_t *) sommet ;

  tmp->contenu = stuff ; 
  
  sommet = (char *) ((cellule_t *) sommet +1)  ;
  
  return tmp;
}

int main(void){

  cellule_t *tmp, *ptr ;

  inserer(creerCellule(1),&maliste) ;
  inserer(creerCellule(2),&maliste) ;
  ptr = creerCellule(3) ;
  inserer(ptr,&maliste) ;
  inserer(creerCellule(4),&maliste) ;

  for(tmp=maliste;tmp!=NULL;tmp=tmp->next) 
    printf("%d ",tmp->contenu) ;

  putchar('\n') ;
  
  extraire(ptr,&maliste) ;
  supprimerCellule(ptr) ;

  for(tmp=maliste;tmp!=NULL;tmp=tmp->next) 
    printf("%d ",tmp->contenu) ;

  putchar('\n') ;

  inserer(creerCellule(5),&maliste) ;

  return 0 ;
}
