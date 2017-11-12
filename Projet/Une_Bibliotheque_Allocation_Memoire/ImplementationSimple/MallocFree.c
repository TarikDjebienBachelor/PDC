#include <stdio.h>
#include <stdlib.h>
#include "MallocFree.h"

/**
 *                  AVANT L'APPEL DE MALLOC :
 *
 *           estDisponible
 *                v_______________________________________
 *   tasMemoire : |_______________________________________|
 *                <--------------------------------------->
 *                              MEMOIRE LIBRE
 *
 *
 *                  APRES LE PREMIER APPEL DE MALLOC :
 *
 *                      estDisponible
 *                 __________v_____________________________
 *   tasMemoire : |__________|_____________________________|
 *                <----------><---------------------------->
 *                   OCCUPE           MEMOIRE LIBRE
 *
 *
 *
 *                  APRES LE N-IEME APPEL DE MALLOC :
 *
 *                                            estDisponible
 *                 _________________________________v______
 *   tasMemoire : |__________|___|______|___|_______|______|
 *                <---------------------------------><----->
 *                            MEMOIRE OCCUPE          LIBRE
 *
 *
 *   La méthode la plus simple est de considerer que MallocSimple retourne
 *   des morceaux d'un grand tableau de caractères representant le tas memoire.
 */


/* espace mémoire où le malloc est autorisé à écrire,
 * lui seul à l'autorisation de le faire */
static char tasMemoire[TAILLE_DU_TAS];

/* prochain emplacement disponible directement dans le tas,
 * seul malloc et free peuvent modifier sa position */
static char *estDisponible = tasMemoire;
/** Initialement lorsque le programme commence,
 * on fait pointer l'emplacement libre au debut du tas */





/* Malloc Simple :
 * retourne un pointeur sur n "cases" memoires
 * (ici les n cases memoires sont en fait un pointeur qui pointe sur le début d'une chaine de caractères)
 * Retourne NULL si l'allocation memoire a échoué.
 */
  char*
  mallocSimple
  (int n)
  {
	/** ALGORITHME:
	 *  Lorsque l'on appelle mallocSimple pour demander n caractères dans le tableau
	 *  la fonction regarde dans un premier temps, s'il reste suffisamment de place
	 *  disponible dans le tas Memoire.
	 *
	 *  Si la condition est respectée, mallocSimple retourne la valeur courante du
	 *  pointeur estDisponible, est ensuite l'incremente de n pour qu'il pointe sur l'espace
	 *  memoire disponible suivant.
	 *
	 *  Sinon, il n'y a plus assez de place dans le tas memoire, on renvoie la valeur 0 pour
	 *  pouvoir tester par la suite si le Malloc s'est bien deroulé.
	 */
	/* SI il y a encore de la place dans le tas pour les n octets que l'on souhaite allouer */
    if (tasMemoire + TAILLE_DU_TAS - estDisponible >= n){
	/* ALORS on décale la position de l'emplacement libre des n cases contigue suivantes */
	   estDisponible = estDisponible + n;
	/* On retourne l'adresse du bloc ajouter dans le tas*/
	   return estDisponible - n;

	} else
	/* SINON il n'y a plus assez de place */
	return NULL;
  }

/* Free Simple :
 * libère l'espace memoire pointé par le parametre zoneOccupe
 */
  void
  freeSimple
  (char *zoneOccupe)
  {
	/** ALGORITHME:
	 *  Le freeSimple affecte zoneOccupe a estDisponible si
	 *  zoneOccupe se situe à dans le tasMemoire.
	 */
	/* SI la zone Occupe se trouve bien dans les bornes du tableau representant le tas memoire */
	if ((zoneOccupe >= tasMemoire)&&(zoneOccupe < tasMemoire+TAILLE_DU_TAS))
	/* On libere la zoneOccupe */
       estDisponible = zoneOccupe;
  }

  unsigned int
  getAdresseTasMemoire
  (void)
  {
	return (unsigned int) tasMemoire;
  }
  unsigned int
  getAdresseEstDisponible
  (void)
  {
	return (unsigned int) estDisponible;
  }

  void
  afficheAdresseTasMemoire
  (void)
  {
	printf("- adresse du tas memoire : %u \n",(unsigned int) tasMemoire);
  }
  void
  afficheAdresseEstDisponible
  (void)
  {
	printf("- adresse du pointeur de zone libre : %u \n",(unsigned int) estDisponible);
  }
