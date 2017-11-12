README : 

// Auteur : Djebien Tarik
// Date   : octobre 2010
// Objet  : Pratique Du C - Mes Commandes Unix

Ci-Joint le TP numero 2 de PDC, tout est fonctionnel :

Arborescence de l'archive Tarik_Djebien_GROUPE2.tar.gz :
           |
           |_____README.txt
           |
           |
           |_____________mcolrm/
           |                             |__ makefile
           |                             |__ mcolrm.c
           |                             |__ readl.c readl.h
	   |                             |__ tools.c tools.h
           |                             |__ Test
           |                                      |__ Alphabet  HistoireDuC
           |
           |
           |_____________mcut/
           |                             |__ makefile
           |                             |__ mcut.c
           |                             |__ readl.c readl.h
	   |                             |__ tools.c tools.h
           |                             |__ Test
           |                                      |__ PlusBelleLaVie
           |
           |
           |_____________mlook/
           |                             |__ makefile
           |                             |__ mlook.c
           |                             |__ readl.c readl.h
	   |                             |__ tools.c tools.h
           |                             |__ Test
           |                                      |__ LookAtMe  GameOver
           |
           |
           |_____________mgrep/
                                         |__ makefile
                                         |__ mgrep.c
                                         |__ readl.c readl.h
	                                 |__ tools.c tools.h
                                         |__ Test
                                                  |__ C++

Remarques :

Chacunes des quatres commandes implémentées sont exactement similaires 
à l'effet produites de celles existantes dans le Shell des systèmes Unix.

Usage de chaque commande :                                      Leur equivalent dans le Shell Unix :

$ ./mcolrm 8 < HistoireDuC                                         $ colrm 8 < HistoireDuC 
$ ./mcolrm 8 12 < Test/Alphabet                                  $ colrm 8 10 < Alphabet 
 
$ ./mcut e 3 5 < Test/PlusBelleLaVie                            $ cut -d"e" -f3-5 Test/PlusBelleLaVie 

$ ./mlook Mais < Test/LookAtMe                                  $ look Mais Test/LookAtMe 
$ ./mlook Try < Test/GameOver                                   $ look Try Test/GameOver

$ ./mgrep X < Test/C++                                              $ grep X < Test/C++ 

Chaque fichier test traite des cas particuliers engendré par chaque commandes excepté le dernier "C++". 

Pour les commentaires :

tarik.djebien@etudiant.univ-lille1.fr

Cordialement.
