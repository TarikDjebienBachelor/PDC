#include <stdio.h>
#include <stdlib.h>

/* ENSEMBLE DES ETATS DE L'AUTOMATE */

    enum Etat
    {
       ETAT_DEBUT_LIGNE,
       ETAT_DIRECTIVE,
       ETAT_CHAINE,
       ETAT_CHAR,
       ETAT_CARAC1,
       ETAT_CARAC2,
       ETAT_CARAC3,
       ETAT_CARAC4,
       ETAT_CARAC5,
       ETAT_DEBUT_COMM,
       ETAT_COMMENTAIRE,
       ETAT_DEBUT_FIN_COMM,
       ETAT_FIN_COMM
    };

/* ETAT INITIAL DE L'AUTOMATE */
enum Etat etat = ETAT_DEBUT_LIGNE ;
/* Le nombre de blancs pour l'indentation courante */
int nbBlanc = 0;
int nbAccoladesOuvrantes = 0;
int nbAccoladesFermantes = 0;

/* Procedure d'indentation courante */
void
indentationCourante
(int nombreDeBlanc )
{
  int i;
    for ( i = 0 ; i < nombreDeBlanc ; i++ )
    {
        putchar(' ');
    }/* endFor */
}/* Fin de indentationCourante */



int
main
()
{
    /* Le char sur le flux de stdIn */
    int c;

    /* LECTURE DU FICHIER SUR StdIn */
    while ( (c=getchar()) != EOF ) {

       switch (etat) {
            case ETAT_DEBUT_LIGNE:
                switch (c) {
                    case ' ' :
                           /* ne rien faire */;
                           break;
                    case '\t':
                           /* ne rien faire */;
                           break;
                    case '#' :
                           putchar('#');
                           etat = ETAT_DIRECTIVE;
                           break;
                    case '\n':
                           putchar('\n');
                           indentationCourante(nbBlanc);
                           break;
                    case '/' :
                           etat = ETAT_DEBUT_COMM;
                           break;
                    case '{' :
					       nbAccoladesOuvrantes++;
				           putchar('\n');
				           putchar('{');
				           putchar('\n');
				           nbBlanc= nbBlanc + 4;
				           indentationCourante(nbBlanc);
				           etat = ETAT_CARAC3;
				           break;
                    default:
                           putchar(c);
                           etat = ETAT_CARAC1;
                           break;
                }
            break; /* ETAT_DEBUT_LIGNE */

            case ETAT_DIRECTIVE:
                putchar(c);
                etat = ETAT_CARAC2;
            break; /* ETAT_DIRECTIVE */

            case ETAT_CHAINE:
                switch (c) {
					case '"' :
				       putchar('"');
				       etat = ETAT_CARAC1;
				       break;
				     default:
				       putchar(c);
				       break;
                }
            break; /* ETAT_CHAINE */

            case ETAT_CHAR:
                switch (c) {
                    case '\'' :
				       putchar('\'');
				       etat = ETAT_CARAC1;
				       break;
				     default:
				       putchar(c);
				       break;
                }
            break; /* ETAT_CHAR */

            case ETAT_CARAC1:
                switch (c) {
					case ';' :
					   putchar(';');
					   putchar('\n');
					   etat = ETAT_DEBUT_LIGNE;
					   break;
				    case '/' :
				       etat = ETAT_DEBUT_COMM;
				       break;
				    case '"' :
				       putchar('"');
				       etat = ETAT_CHAINE;
				       break;
				    case '\'' :
				       putchar('\'');
				       etat = ETAT_CHAR;
				       break;
				    case '{'  :
				       nbAccoladesOuvrantes++;
				       putchar('\n');
				       putchar('{');
				       putchar('\n');
				       nbBlanc= nbBlanc + 4;
				       indentationCourante(nbBlanc);
				       etat = ETAT_CARAC3;
				       break;
				    default:
				       putchar(c);
				       break;
                }
            break; /* ETAT_CARAC1 */

            case ETAT_CARAC2:
                switch (c) {
					case '\n' :
					    putchar('\n');
					    etat = ETAT_DEBUT_LIGNE;
					    break;
					default:
					    putchar(c);
					    break;

                }
            break; /* ETAT_CARAC2 */

            case ETAT_CARAC3:
                switch (c) {
					case ' ' :
                           /* ne rien faire */;
                           break;
                    case '\t':
                           /* ne rien faire */;
                           break;
					case '{'  :
				       nbAccoladesOuvrantes++;
				       putchar('\n');
				       putchar('{');
				       putchar('\n');
				       nbBlanc= nbBlanc + 4;
				       indentationCourante(nbBlanc);
				       break;
				    case '/' :
				       etat = ETAT_DEBUT_COMM;
				       break;
				    case '\n':
				       putchar('\n');
				       indentationCourante(nbBlanc);
				       break;

				    case '}'  :
				       nbAccoladesFermantes++;
				       putchar('\n');
				       nbBlanc= nbBlanc - 4;
				       indentationCourante(nbBlanc);
				       putchar('}');
				       putchar('\n');
				       break;
				    default:
				       putchar(c);
				       etat = ETAT_CARAC5;
				       break;
                }
            break; /* ETAT_CARAC3 */

            case ETAT_CARAC4:
                switch (c) {
					case '\n' :
				       putchar('*');
				       putchar('/');
				       putchar('\n');
				       indentationCourante(nbBlanc);
				       putchar('/');
				       putchar('*');
				       break;
				    case '*'  :
				       putchar('*');
				       etat = ETAT_DEBUT_FIN_COMM;
				       break;
				    default:
				       putchar(c);
				       break;
                }
            break; /* ETAT_CARAC4 */

            case ETAT_CARAC5:
                switch (c) {
				    case ';' :
				       putchar(';');
				       putchar('\n');
				       indentationCourante(nbBlanc);
				       etat = ETAT_CARAC3;
				       break;
				    default:
				       putchar(c);
				       break;
                }
            break; /* ETAT_CARAC5 */

            case ETAT_DEBUT_COMM:
                switch (c) {
                     case '*' :
                        /*indentationCourante(nbBlanc);*/
                        putchar('/');
                        putchar('*');
                        etat = ETAT_COMMENTAIRE;
                        break;
                     default:
                        putchar(c);
                        etat = ETAT_CARAC3;
                        break;
                }
            break; /* ETAT_DEBUT_COMM */

            case ETAT_COMMENTAIRE:
                putchar(c);
                etat = ETAT_CARAC4;
            break; /* ETAT_COMMENTAIRE */

            case ETAT_DEBUT_FIN_COMM:
                switch (c) {
					case '*' :
					   putchar('*');
					   etat = ETAT_DEBUT_FIN_COMM;
					   break;
					case '/' :
					   putchar('/');
					   etat = ETAT_FIN_COMM;
					   break;
					default:
					   putchar(c);
					   etat = ETAT_CARAC4;
					   break;
                }
            break; /* ETAT_DEBUT_FIN_COMM */

            case ETAT_FIN_COMM:
                putchar('\n');
                indentationCourante(nbBlanc);
                etat = ETAT_DEBUT_LIGNE;
            break; /* ETAT_FIN_COMM */


       }/* switch etat */

    }/* endWhile */

 if (nbAccoladesOuvrantes != nbAccoladesFermantes) {
    printf("\n\nATTENTION :\n\nLe nombre d'accolades ouvrantes et fermantes ne semblent pas correspondre !");
    exit(EXIT_FAILURE);
  };
  exit(EXIT_SUCCESS);
}

