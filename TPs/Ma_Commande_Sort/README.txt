README : 

// Auteur : Djebien Tarik
// Date   : novembre 2010
// Objet  : Pratique Du C - Ma Commande Sort

Ci-Joint le TP numero 3 de PDC, tout est fonctionnel sauf msort (voir ci dessous) :

Arborescence de l'archive Tarik_Djebien_GROUPE2.tar.gz :
           |
           |_____README.txt + Algorithme_de_Tri_QuickSort.gif
           |
           |
           |_____________QuickSort_Generique/
           |                             |__ makefile
           |                             |__ msort.c
           |                             |__ readl.c readl.h
	   |                             |__ tools.c tools.h
           |                             |__ qs.c qs.h
           |                                      
           |
           |
           |_____________Tri_Tableau_Entiers/
                                          |__ makefile
                                          |__ qsint_tst.c
                                          |__ qsint.c qsint.h
 

Remarques :

 Quelle structure de données allez vous utiliser pour mémoriser l’ensemble des lignes d’un fichier ? 
 
 La structure de données utilisée pour mémoriser l’ensemble des lignes d’un fichier pourrait être un struct  :    
   1. struct fichier /* l'entrée standard */
   2. {
   3. char ligne[]; /* ou char * ligne; */
   4. int nbligne; /* contenant le nombre de ligne dans l'entrée standard */
   5. };
    /* On declare avec : fichier EntreeStandard;  
        On accede aux lignes differentes par : EntreeStandard.nbligne et EntreeStandard.ligne[i]; 
        L'avantage d'un struct est que la fonction generique quicksort necessite la meme taille en octet comme 3 eme parametre,
        le sizeof(fichier) donnera toujours la meme taille contrairement à un tableau de chaine de caractere de longueurs differentes 
    */

Pour les commentaires :

tarik.djebien@etudiant.univ-lille1.fr

Cordialement.
