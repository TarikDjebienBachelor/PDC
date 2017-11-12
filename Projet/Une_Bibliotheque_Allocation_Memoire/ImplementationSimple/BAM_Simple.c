#include <stdio.h>
#include <stdlib.h>
#include "MallocFree.h"

/* procedure d'affichage sur la sortie standard du tas memoire
 * sous la forme :
 *
 *      XXXXXXXXXXXXXXXXXXX
 *      1234..............n=TAILLE_DU_TAS
 *
 * X représantant une case memoire dans le tas memoire
 * avec X = O si la case est occupée (allouée)
 *      X = L si la case est libre   (désallouée)
 */
void
visualiserMemoire
(unsigned int adresseTas,unsigned int adresseEstDisponible)
{
  int nbOccupe,nbLibre;
  int espaceOccupe,espaceLibre;

espaceOccupe = adresseEstDisponible - adresseTas;

printf("\n VISUALISATION DU TAS MEMOIRE : \n Legende : \n O = Espace Memoire Occupé \n L = Espace Memoire Libre \n\n");

for (nbOccupe=0;nbOccupe<espaceOccupe;nbOccupe++)
printf(" ");
printf("estDisponible\n");
for (nbOccupe=0;nbOccupe<espaceOccupe;nbOccupe++)
printf(" ");
printf("v\n");

for (nbOccupe=0;nbOccupe<espaceOccupe;nbOccupe++)
printf("O");

espaceLibre = TAILLE_DU_TAS - espaceOccupe;
for (nbLibre=0;nbLibre<espaceLibre;nbLibre++)
printf("L");



printf("\n\n");
}

/* Procedure d'affichage du menu pour l'intercation OS et utilisateur
 * retourne 1 si l'utilisateur choisit de faire un malloc
 * retourne 2 si l'utilisateur choisit de faire un free
 * retourne 3 sinon
 */
int
afficheMenu
(void)
{
 int choixMenu;

  printf("=== Menu Interaction avec le systeme d'exploitation ===\n\n");
  printf("1. Faire un Malloc()\n");
  printf("2. Faire un Free()\n");
  printf("\nVotre choix ? ");
  scanf("%d", &choixMenu);

  printf("\n");

  switch (choixMenu)
  {
    case 1:
       printf("Vous avez choisi de faire un Malloc. Bon choix !\n");
       return 1;
       break;
    case 2:
       printf("Vous avez choisi de faire un Free! \n");
       return 2;
       break;
    default:
       printf("Vous n'avez pas rentre un nombre correct!\n");
       return 3;
       break;
  }

  printf("\n\n");


}

/*
 * Fonction main principal
 */
int
main
(int argc, char *argv[])
{

  /* L'objet a alloué */
  char *monObjet = NULL;
  /* la taille en octets que l'on souhaite allouer dans le tas */
  int nbOctets;
  /* Reponse de l'utilisateur */
  int choix,menu;
  /* les adresses décimales du tas memoire et du pointeur sur la premiere case libre disponible */
  unsigned int adresseTas,adressePointeurDisponible;
  printf("***************************************************\n");
  printf("** UNE BIBLIOTHEQUE D'ALLOCATION MEMOIRE SIMPLE ***\n");
  printf("***************************************************\n");
  printf(" \nImplementation :\n  Le tas memoire est implementé avec un tableau analogue à une pile FIFO.\n");
  printf("\n  Cette version permet d'introduire le projet en analysant l'importance du choix \n  ");
  printf("de la structure de donnée adapté a sa resolution.\n\n\n");




  printf("Au lancement du programme on a initialement : \n");
  afficheAdresseTasMemoire();
  afficheAdresseEstDisponible();
  printf("- taille du tas memoire : %d\n\n",TAILLE_DU_TAS);
  adresseTas = getAdresseTasMemoire();
  adressePointeurDisponible = getAdresseEstDisponible();
  visualiserMemoire(adresseTas,adressePointeurDisponible);

  printf("\n\n");

  do
  {
  menu = afficheMenu();
  if (menu==1){
  printf("Entrer le nombre d'octets que vous souhaitez allouer dans le tas memoire : \n");
  scanf("%d",&nbOctets);
  monObjet = mallocSimple(nbOctets);
  if (monObjet){
  printf("\n\nadresse du bloc qui vient d'etre alloué dans le tas memoire :  %u \n",(unsigned int) monObjet);
  afficheAdresseTasMemoire();
  afficheAdresseEstDisponible();
  adresseTas = getAdresseTasMemoire();
  adressePointeurDisponible = getAdresseEstDisponible();
  visualiserMemoire(adresseTas,adressePointeurDisponible);
  }
  else
  printf("ERREUR :  ESPACE MEMOIRE DANS LE TAS INSUFFISANT .\n");
  }
  else if (menu==2){
  freeSimple(monObjet);
  printf("adresse du bloc qui vient d'etre desalloué dans le tas memoire :  %u \n",(unsigned int) monObjet);
  afficheAdresseTasMemoire();
  afficheAdresseEstDisponible();
  adresseTas = getAdresseTasMemoire();
  adressePointeurDisponible = getAdresseEstDisponible();
  visualiserMemoire(adresseTas,adressePointeurDisponible);
  }else if (menu==3)
  printf("Respectez les consignes.\n");

  printf("Souhaitez vous interagir une nouvelle fois avec le systeme d'exploitation ? (oui:1 / non:0)\n");scanf("%d",&choix);
  }while(choix==1);

  printf("\nCONCLUSION:\n  La Structure de donnée FIFO implementer en tableau est mal adaptée pour memoriser\n  la taille d'un bloc alloué entre 2 appels consecutifs de malloc au systeme.\n");
  printf("  De plus, les tableaux sont des structures de donnees statiques fermés à toutes eventuelle expansion\n  Ce principe reste non conforme à la dimension dynamique de la vrai bibliotheque d'allocation de memoire du systeme dans la pratique.\n");
  printf("\n SOLUTION : cf BAM_Evolution");
  printf("\n AUTEUR : DJEBIEN TARIK \n");
  return 0;
}
