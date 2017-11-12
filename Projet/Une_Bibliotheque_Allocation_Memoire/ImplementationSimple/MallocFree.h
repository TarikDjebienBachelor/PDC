#include <stdio.h>
#include <stdlib.h>


/* Macro pour la taille maximale de l'espace disponible dans le tas */
#define TAILLE_DU_TAS 40

/* Malloc Simple :
 * retourne un pointeur sur n "cases" memoires si le malloc a fonctionné
 * sinon retourne NULL
 */
  char* mallocSimple (int n);


/* Free Simple :
 * libère l'espace memoire pointé par le parametre zoneOccupe
 */
  void freeSimple (char *zoneOccupe);

  unsigned int getAdresseTasMemoire(void);
  unsigned int getAdresseEstDisponible(void);

  void afficheAdresseTasMemoire (void);
  void afficheAdresseEstDisponible (void);
