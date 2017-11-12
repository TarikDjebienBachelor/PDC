/**
 * Ma bibliotheque d'allocation mémoire
 *
 * Djebien Tarik, Decembre 2010
 *
 */

#include <stdio.h>
#include <stdlib.h>


#define NALLOUE 1024 /* nombre d'unités demandées au minimum au systeme */
#define MAXOCTETS (unsigned) 10240 /* nombre d'octets maximales demandés */

typedef long Alignement; /* Cadrage des blocs de la liste sur un long */

union en_tete{
	struct{
	    union en_tete *ptr; /* pointeur sur le bloc libre suivant */
	    unsigned taille; /* taille d'un bloc strictement positive */
	}s;

    Alignement x; /* force les blocs du tas memoire à s'aligner correctement */
};

typedef union en_tete En_tete;

/* malloc() replacement */
void *my_malloc(unsigned noctets);

/* free() replacement */
void my_free(void *pa);

/* plusmem : demande plus de mémoire au système */
static En_tete *plusmem(unsigned nu);

/**
 * Explication :
 *
 * Le champ Alignement n'est jamais réellement utilisé,
 * il permet seulement de forcer l'alignement de chaque
 * en tete sur une limite en memoire correspondant au cas
 * le plus défavorable, ici on choisit comme type le plus
 * contraignant le type long, on aurait pu prendre un double
 * au choix selon la machine.
 *
 * Dans malloc, la taille demandée en nombre de caractères est arrondie
 * au nombre convenable d'unités de taille d'en tête.
 * Le bloc que l'on allouera contiendra une unité de plus, correspondant
 * à l'en tête elle même, et c'est cette valeur que l'on stocke dans
 * le champ taille de l'en tête.
 *
 * Le pointeur retourné par malloc pointe sur l'espace libre, pas sur
 * l'en tête elle même. L'utilisateur peut faire ce qu'il veut de l'espace
 * qu'il a demandé, mais s'il écrit quelque chose en dehors de l'espace alloué
 * ,la liste risque d'être bouleversée.
 *
 * Le champ taille est nécessaire parce que les blocs contrôlés par malloc
 * peuvent ne pas être contigus et on ne peut pas calculer des tailles de blocs
 * par l'intermediaire de l'arithmétique des pointeurs.
 */

static unsigned maxalloue; /* contrainte : nbre max d'unités allouées */

static En_tete base; /* liste vide pour débuter */
static En_tete *plibre = NULL; /* le debut de la liste est libre */

/* my_malloc : mon allocateur de mémoire à usage général */
void *
my_malloc
(unsigned noctets)
{
    En_tete *p, *pprec;
    En_tete *plusmem(unsigned);
    unsigned nunites;

    /* La fonction malloc compare le nombre d'octets demandés
     * à une constante arbitraire MAXOCTETS pour limiter
     * les actions de l'utilisateur.
     */
    if (noctets > MAXOCTETS){ /*ne depasse pas MAXOCTETS */
       fprintf(stderr,"malloc: impossible d'allouer plus de %u octets\n",MAXOCTETS);
       return NULL;
	}


    nunites = (noctets + sizeof(En_tete) - 1) / sizeof(En_tete) + 1;

    /* Si il n'existe pas encore de liste */
    if ((pprec = plibre) == NULL){

      base.s.ptr = plibre = pprec = &base;
      base.s.taille = 0;
	}

    for (p = pprec-> s.ptr; ; pprec = p, p = p->s.ptr){

	   /* Si la taille du bloc est assez grande */
	   if (p->s.taille >= nunites){
		  /* Dans le cas ou la taille est exacte, tout juste */
		  if (p->s.taille == nunites)
		      pprec->s.ptr = p->s.ptr;
	      else {
			  p->s.taille -= nunites;
			  p += p->s.taille;
			  p->s.taille = nunites;
		  }
		  plibre = pprec;
		  return (void *) (p+1);
		}
		if (p == plibre) /* liste libre rebouclée */
			if((p = plusmem(nunites)) == NULL )
			   return NULL; /* il n'en reste plus */

	 }
}

/**
 * Explication de l'Algorithme:
 * La variable base designe l'en tete au debut du lancement du programme.
 * Si plibre vaut NULL, comme au premier appel de malloc,
 * on crée une liste dégénérée de blocs libres.
 * Elle contient un bloc de taille zéro et pointe sur elle même.
 * Ensuite, dans tout les cas, on explore la liste de blocs libres.
 * La recherche d'un bloc libre de taille adéquate commence à l'endroit
 * (plibre) où le dernier bloc a été trouvé.
 * Cette stratégie permet de conserver l'homogénéité de la liste.
 * Si l'on a trouvé un bloc trop gros, on retourne à l'utilisateur
 * la fin de ce bloc, ainsi, il suffit de modifier la taille de l'en tete
 * du bloc original.
 * Dans tous les cas, le pointeur retourné à l'utilisateur pointe sur l'espace
 * libre à l'intérieur du bloc qui commence une unité derrière l'en tête.
 *
 * Optimisation réalisé:
 * Débordement memoire pour un segment alloué par malloc().
 */



/* plusmem : demande plus de mémoire au système */
static En_tete *plusmem(unsigned nu)
{
     char *pc, *sbrk(int);
     En_tete *pu;

     /* Demander de la mémoire au système est une opération
      * coûteuse, pour eviter de le faire à chaque appel
      * de malloc, on recupere au minimum NALLOUE unités.*/
     if (nu < NALLOUE)
		 nu = NALLOUE;

     /*L'appel système UNIX sbrk(n) retourne un pointeur sur n octets de
      * mémoire supplémentaires, sbrk retourne -1 s'il n'y a pas de place
      * disponible
      */
	 pc = sbrk(nu * sizeof(En_tete));
	 /* On doit convertir par un cast la valeur -1 en char*, de façon à
      * pouvoir la comparer à la valeur de retour.
      */
	 if (pc == (char*) -1) /* si il n'y a pas d'espace du tout */
		 return NULL;
	 pu = (En_tete *) pc;
	 pu->s.taille = nu;

	 /* Quand plusmem alloue un nouveau bloc,
	  * la variable statique maxalloue conserve
	  * la taille du plus gros bloc utilisé jusqu'à présent
	  * Ainsi la fonction free peut verifier la valeur de size:
	  * elle ne doit pas être nulle ni supérieure à la taille
	  * du plus gros bloc alloué.
	  */
	 maxalloue = (pu->s.taille > maxalloue)? pu->s.taille : maxalloue;

	 my_free((void *)(pu+1));
	 return plibre;
}
/**
 *Explication :
 *   La fonction plusmem demande de la mémoire au système d'exploitation.
 * Les détails de son fonctionnement varient d'un système à un autre.
 * Puisque le fait de demander de la mémoire au système est une opération
 * relativement coûteuse, nous ne voulons pas l'effectuer à chaque appel
 * de malloc, c'est pourquoi plusmem demande au minimum NALLOUE unités.
 * On coupera ce grand bloc en morceaux selon les besoins. Aprés
 * l'affectation du champ taille, plusmem introduit la mémoire
 * supplémentaire dans la liste en appelant free.
 *
 *   L'appel système UNIX sbrk(n) retourne un pointeur sur n octets de
 * mémoire supplémentaires, sbrk retourne -1 s'il n'y a pas de place
 * disponible, meme si NULL serait plus approprié.
 * On doit convertir par un cast la valeur -1 en char*, de façon à
 * pouvoir la comparer à la valeur de retour.
 */


/* my_free : met le bloc pa dans la liste des blocs libres */
void
my_free
(void *pa)
{
	En_tete *pb, *p;

	pb = (En_tete *)pa -1; /*pb pointe sur l'en tête de pa */

    /* Quand plusmem alloue un nouveau bloc,
	  * la variable statique maxalloue conserve
	  * la taille du plus gros bloc utilisé jusqu'à présent
	  * Ainsi la fonction free peut verifier la valeur de size:
	  * elle ne doit pas être nulle ni supérieure à la taille
	  * du plus gros bloc alloué.
	  */
    if (pb->s.taille == 0 || pb->s.taille > maxalloue){
		fprintf(stderr,"free: impossible de libérer plus de %u unités\n",pb->s.taille);
		return;
	}

	for(p=plibre; !(pb>p && pb < p->s.ptr); p=p->s.ptr)

		if (p >= p->s.ptr && (pb>p || pb< p->s.ptr))
		  break; /* bloc libéré au début ou la fin */

	if (pb + pb->s.taille == p->s.ptr){ /*jointure par le haut */

		pb->s.taille += p->s.ptr->s.taille;
		pb->s.ptr = p->s.ptr->s.ptr;
	} else
		pb->s.ptr = p->s.ptr;

    if (p + p->s.taille == pb){ /* jointure par le bas */
		p->s.taille += pb->s.taille;
		p->s.ptr = pb->s.ptr;
	} else
	    p->s.ptr = pb;

	plibre = p;
}

/**
 *Explication :
 * La fonction my_free explore la liste des blocs libres, en commençant
 * à plibre, de façon à trouver un endroit où inserer le bloc à libérer.
 * Cet endroit se trouve soit entre deux blocs existants, soit en fin de liste.
 * Dans tout les cas, si le bloc à libérer est adjacent à un autre,
 * on rassemble les blocs.
 */

int
main
(int argc, char* argv[]){
  /* mymalloc myfree example: string generator*/
  int i,n;
  char * buffer;

  printf ("How long do you want the string? ");
  scanf ("%d", &i);

  buffer = (char*) my_malloc (i+1);
  if (buffer==NULL) exit (1);

  for (n=0; n<i; n++)
    buffer[n]=rand()%26+'a';
  buffer[i]='\0';

  printf ("Random string: %s\n",buffer);
  my_free (buffer);
  return 0;
}
