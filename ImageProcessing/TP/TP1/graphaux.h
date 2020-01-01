/*! \file graphaux.h
    \brief structures auxiliaires
*/
#include <stdio.h>
#include <string.h>
/* 
#include <errno.h> 
#include <sys/types.h>
#include <unistd.h> 
*/
#include <stdlib.h>
#include <sys/time.h>

#define _graphaux_h

typedef char boolean;

#define TRUE 1
#define FALSE 0

/* ===================================== */
/* GESTION DE FILE */
/* ===================================== */

typedef struct {
  int Max;          /* taille max de la fifo */
  int In;           /* index ou ranger le prochain arrivant */
  int Out;          /* index d'ou retirer le prochain sortant */
  int Pts[1];
} Fifo;

/* prototypes     */

extern Fifo * CreeFifoVide(int taillemax);
extern void FifoFlush(Fifo * L);
extern int FifoVide(Fifo * L);
extern int FifoPop(Fifo * L);
extern void FifoPush(Fifo * L, int V);
extern void FifoPushFirst(Fifo * L, int V);
extern int FifoTaille(Fifo * L);
extern void FifoPrint(Fifo * L);
extern void FifoTermine(Fifo * L);


/* ===================================== */
/* GESTION DE PILE */
/* ===================================== */

/*! \struct Lifo
    \brief structure de pile (Last In, First Out).
*/
typedef struct Lifo {
//! taille max de la Lifo
  int Max;
//! index de pile (pointe la 1ere case libre)
  int Sp;
//! tableau pour la pile (re-dimensionné dynamiquement)
  int Pts[1];
} Lifo;

/* prototypes     */
Lifo * CreeLifoVide( int taillemax );
void LifoFlush( Lifo * L );
boolean LifoVide( Lifo * L );
int LifoPop( Lifo * L );
void LifoPush( Lifo * L, int V );
void LifoPrint( Lifo * L );
void LifoPrintLine( Lifo * L );
void LifoTermine( Lifo * L );

/* ===================================== */
/* TRI */
/* ===================================== */

#define TypeCle long

/* prototypes     */
void TriRapideStochastique (int * A, TypeCle *T, int p, int r);

/* ===================================== */
/* MESURE DE TEMPS */
/* ===================================== */

#ifdef DEFTIMEVAL
struct timeval {
  unsigned long	tv_sec;		/* seconds */
  long		tv_usec;	/* and microseconds */
};

struct timezone {
  int	tz_minuteswest;	/* minutes west of Greenwich */
  int	tz_dsttime;	/* type of dst correction */
};
#endif

/*! \var chrono
    \brief strucure pour la mesure du temps
*/
typedef struct timeval chrono;

/* prototypes     */
void start_chrono( chrono *tp );
int read_chrono( chrono *tp );

/* ===================================== */
/* GENERATION DE POSTSCRIPT */
/* ===================================== */

/* prototypes     */

void PSHeader(FILE *fd, double figure_width, double figure_height, double line_width, int font_size );
void EPSHeader(FILE *fd, double figure_width, double figure_height, double line_width, int font_size );
void PSMove (FILE *fd, double x, double y);
void PSDraw (FILE *fd, double x, double y);
void PSLine (FILE *fd, double xd, double yd, double xf, double yf);
void PSDrawcircle (FILE *fd, double x, double y, double r);
void PSDrawdisc (FILE *fd, double x, double y, double r);
void PSDrawdiscCol (FILE *fd, double x, double y, double r, int col);
void PSString (FILE *fd, double x, double y, char *s);
void PSFooter(FILE *fd);

/* ===================================== */
/* ENSEMBLES */
/* ===================================== */

boolean * EnsembleVide(int n);

/* ===================================== */
/* LISTES */
/* ===================================== */

int * ListeVide(int n);
