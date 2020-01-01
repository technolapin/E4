/*! \file graph_basic.c
    \brief fonctions de base pour la manipulation de graphes
*/
/*
      Michel Couprie, septembre 1999
      Derni�re mise � jour mars 2011
*/

#include "graphes.h"

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS SUR LES LISTES CHAINEES DE SOMMETS */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn pcell AlloueCell(pcell * plibre)
    \param plibre (entr�e) : pointeur sur une liste cha�nee de cellules libres.
    \return pointeur sur une cellule.
    \brief retire la premiere cellule de la liste point�e par plibre et retourne un pointeur sur cette cellule.
*/
pcell AlloueCell(pcell * plibre)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "AlloueCell"
{
  pcell p;
  if (*plibre == NULL) 
  {
    fprintf(stderr, "%s : plus de cellules libres\n", F_NAME);
    exit(0);
  }
  p = *plibre;
  *plibre = (*plibre)->next;
  return p;
} /* AlloueCell() */

/* ====================================================================== */
/*! \fn void LibereCell(pcell * plibre, pcell p)
    \param plibre (entr�e) : pointeur sur une liste cha�nee de cellules libres.
    \param p (entr�e) : pointeur sur une cellule.
    \brief ins�re la cellule p au d�but de la liste point�e par 'plibre'. 
*/
void LibereCell(pcell * plibre, pcell p)
/* ====================================================================== */
{
  p->next = *plibre;
  *plibre = p;
} /* LibereCell() */

/* ====================================================================== */
/*! \fn void RetireTete(pcell * plibre, pcell * pliste)
    \param plibre (entr�e) : pointeur sur une liste cha�nee de cellules libres.
    \param pliste (entr�e) : pointeur sur une liste.
    \brief retire la premi�re cellule de la liste 'pliste'. La cellule est cha�nee � la liste 'plibre'. 
*/
void RetireTete(pcell * plibre, pcell * pliste)
/* ====================================================================== */
{
  pcell p;
  p = (*pliste)->next;
  LibereCell(plibre, *pliste);
  *pliste = p;
} /* RetireTete() */

/* ====================================================================== */
/*! \fn void AjouteTete(pcell * plibre, pcell * pliste, int a, TYP_VARC v)
    \param plibre (entr�e) : pointeur sur une liste cha�nee de cellules libres.
    \param pliste (entr�e) : pointeur sur une liste.
    \param a (entr�e) : un sommet.
    \param v (entr�e) : une valeur.
    \brief ajoute une cellule contenant le sommet 'a' et la valeur 'v' en t�te de la liste 'pliste'. La cellule est prise dans la liste 'plibre'. 
*/
void AjouteTete(pcell * plibre, pcell * pliste, int a, TYP_VARC v)
/* ====================================================================== */
{
  pcell p;
  p = AlloueCell(plibre);
  p->next = *pliste;
  p->som = a;
  p->v_arc = v;
  *pliste = p;
} /* AjouteTete() */

/* ====================================================================== */
/*! \fn int EstDansListe(pcell p, int a) 
    \param p (entr�e) : une liste cha�nee de successeurs.
    \param a (entr�e) : un sommet.
    \return bool�en.
    \brief retourne 1 si le sommet 'a' se trouve dans la liste 'p', 0 sinon. 
*/
int EstDansListe(pcell p, int a) 
/* ====================================================================== */
{
  for (; p != NULL; p = p->next)
    if (p->som == a) return 1;
  return 0;
} /* EstDansListe() */

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS D'ALLOCATION / LIBERATION POUR UN GRAPHE */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn graphe * InitGraphe(int nsom, int nmaxarc)
    \param   nsom (entr�e) : nombre de sommets.
    \param nmaxarc (entr�e) : nombre maximum d'arcs.
    \return un graphe.
    \brief alloue la memoire n�cessaire pour repr�senter un graphe a 'nsom' sommets,
              poss�dant au maximum 'nmaxarc' arcs. 
              Retourne un pointeur sur la structure allou�e. 
*/
graphe * InitGraphe(int nsom, int nmaxarc)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "InitGraphe"
{
  graphe * g;
  int i;
  
  g = (graphe *)malloc(sizeof(graphe));
  if (g == NULL)
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->reserve = (cell *)malloc(nmaxarc * sizeof(cell));
  if (g->reserve == NULL)
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->gamma = (pcell *)calloc(nsom, sizeof(pcell)); /* calloc met a 0 la memoire allouee */
  if (g->gamma == NULL)
  {   fprintf(stderr, "%s : calloc failed\n", F_NAME);
      exit(0);
  }

  g->tete = (int *)malloc(nmaxarc * sizeof(int));
  g->queue = (int *)malloc(nmaxarc * sizeof(int));
  if ((g->tete == NULL) || (g->tete == NULL))
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->v_arcs = (TYP_VARC *)malloc(nmaxarc * sizeof(TYP_VARC));
  if (g->v_arcs == NULL)
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->v_sommets = (TYP_VSOM *)malloc(nsom * sizeof(TYP_VSOM));
  if (g->v_sommets == NULL)
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->x = (double *)malloc(nsom * sizeof(double));
  g->y = (double *)malloc(nsom * sizeof(double));
  g->z = (double *)malloc(nsom * sizeof(double));
  if ((g->x == NULL) || (g->y == NULL) || (g->z == NULL))
  {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
      exit(0);
  }

  g->nsom = nsom;
  g->nmaxarc = nmaxarc;
  g->narc = 0;

  /* construit la liste initiale de cellules libres */
  for (i = 0; i < nmaxarc - 1; i++)
    (g->reserve+i)->next = g->reserve+i+1;
  (g->reserve+i)->next = NULL;
  g->libre = g->reserve;  

  g->nomsommet = NULL;
  
  return g;
} /* InitGraphe() */

/* ====================================================================== */
/*! \fn void TermineGraphe(graphe * g)
    \param g (entr�e) : un graphe.
    \brief lib�re la memoire occup�e par le graphe g. 
*/
void TermineGraphe(graphe * g)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "TermineGraphe"
{
  int i, n = g->nsom;
  free(g->reserve);
  if (g->gamma) free(g->gamma);
  if (g->tete) { free(g->tete); free(g->queue); }
  if (g->v_arcs) free(g->v_arcs);
  if (g->v_sommets) free(g->v_sommets);
  if (g->nomsommet)
  {
    for (i = 0; i < n; i++) free(g->nomsommet[i]);
    free(g->nomsommet);
  }
  if (g->x) free(g->x);
  if (g->y) free(g->y);
  if (g->z) free(g->z);
  free(g);
} /* TermineGraphe() */

/* ====================================================================== */
/*! \fn void CopyXY(graphe * g1, graphe * g2)
    \param g1 (entr�e) : un graphe
    \param g2 (entr�e/sortie) : un graphe
    \brief copie les coordonn�es x, y des sommets du graphe 1 dans le graphe 2
*/
void CopyXY(graphe * g1, graphe * g2)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "CopyXY"
{
  int i, n = g1->nsom;
  if (g2->nsom != n)
  {   fprintf(stderr, "%s : graphs must have the same number of vertices\n", F_NAME);
      exit(0);
  }
  for (i = 0; i < n; i++) { g2->x[i] = g1->x[i]; g2->y[i] = g1->y[i]; }
} /* CopyXY() */

/* ====================================================================== */
/*! \fn void CopyVsom(graphe * g1, graphe * g2)
    \param g1 (entr�e) : un graphe
    \param g2 (entr�e/sortie) : un graphe
    \brief copie les valeurs associ�es aux sommets du graphe 1 dans le graphe 2
*/
void CopyVsom(graphe * g1, graphe * g2)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "CopyVsom"
{
  int i, n = g1->nsom;
  if (g2->nsom != n)
  {   fprintf(stderr, "%s : graphs must have the same number of vertices\n", F_NAME);
      exit(0);
  }
  for (i = 0; i < n; i++) g2->v_sommets[i] = g1->v_sommets[i];
} /* CopyVsom() */

/* ====================================================================== */
/*! \fn graphe * CopyGraphe(graphe * g1)
    \param g1 (entr�e) : un graphe
    \return un graphe
    \brief retourne un clone du graphe g1
*/
graphe * CopyGraphe(graphe * g1)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "CopyGraphe"
{
  graphe * g;
  int i, j;
  TYP_VARC v;
  int nsom = g1->nsom;
  int nmaxarc = g1->nmaxarc;
  pcell p;

  g = InitGraphe(nsom, nmaxarc);

  if (g1->v_sommets)
    for (i = 0; i < nsom; i++) 
      g->v_sommets[i] = g1->v_sommets[i];

  if (g1->x)
    for (i = 0; i < nsom; i++) 
    {
      g->x[i] = g1->x[i];
      g->y[i] = g1->y[i];
      g->z[i] = g1->z[i];
    }

  for (i = 0; i < nsom; i++) 
    for (p = g1->gamma[i]; p != NULL; p = p->next)
    {
      j = p->som;
      v = p->v_arc;
      AjouteArcValue(g, i, j, (TYP_VARC)v);
    }
  
  return g;
} /* CopyGraphe() */

/* ====================================================================== */
/*! \fn void UnionGraphes(graphe * g1, graphe * g2)
    \param g1 (entr�e) : un graphe
    \param g2 (entr�e) : un graphe
    \brief calcule l'union des graphes g1 et g2, le r�sultat est stock� dans g1.
    Le champ v_sommet de l'union est le max des champs v_sommets des deux graphes.
*/
void UnionGraphes(graphe * g1, graphe * g2)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "UnionGraphes"
{
  int i, j, n = g1->nsom, m1 = g1->narc, m2 = g2->narc;
  TYP_VARC v;
  pcell p;

  if (g2->nsom != n)
  {   fprintf(stderr, "%s: graphs must have the same number of vertices\n", F_NAME);
      exit(0);
  }
  if (m1 + m2 > g1->nmaxarc)
  {   fprintf(stderr, "%s: two many arcs in union\n", F_NAME);
      exit(0);
  }

  for (i = 0; i < n; i++) 
    for (p = g2->gamma[i]; p != NULL; p = p->next)
    {
      j = p->som;
      v = p->v_arc;
      AjouteArcValue(g1, i, j, v);
    }

  for (i = 0; i < n; i++) 
    if (g2->v_sommets[i] > g1->v_sommets[i])
      g1->v_sommets[i] = g2->v_sommets[i];
  
} /* UnionGraphes() */

/* ====================================================================== */
/*! \fn void UnitLength(graphe * g) 
    \param g (entr�e) : un graphe.
    \brief met � 1 les longueurs de tous les arcs (repr�sentation gamma seulement).
*/
void UnitLength(graphe * g) 
/* ====================================================================== */
#undef F_NAME
#define F_NAME "UnitLength"
{
  int i, n = g->nsom;
  pcell p;
  for (i = 0; i < n; i++) 
    for (p = g->gamma[i]; p != NULL; p = p->next)
      p->v_arc = (TYP_VARC)1;
} /* UnitLength() */

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS D'ENTREE / SORTIE FICHIER POUR UN GRAPHE */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn graphe * ReadGraphe(char * filename)
    \param   filename (entr�e) : nom du fichier graphe.
    \return un graphe.
    \brief Lit les donn�es d'un graphe dans le fichier filename, retourne un pointeur sur la structure graphe construite. 
*/
graphe * ReadGraphe(char * filename)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "ReadGraphe"
{
#define TAILLEBUF 4096
  graphe * g;
  int i, n, m, t, q;
  char buf[TAILLEBUF];
  char *ret;

  FILE *fd = NULL;

  fd = fopen(filename,"r");
  if (!fd)
  {
    fprintf(stderr, "%s: file not found: %s\n", F_NAME, filename);
    return NULL;
  }

  fscanf(fd, "%d %d\n", &n, &m);
  g = InitGraphe(n, m);
  do
  {
    ret = fgets(buf, TAILLEBUF, fd);
    if ((ret != NULL) && (strncmp(buf, "noms sommets", 12) == 0))
    {
      g->nomsommet = (char **)malloc(n * sizeof(char *));
      if (g->nomsommet == NULL)
      {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
          exit(0);
      }
      for (i = 0; i < n; i++)
      {
        fscanf(fd, "%d\n", &t);
        fgets(buf, TAILLEBUF, fd);
        g->nomsommet[t] = (char *)malloc((strlen(buf)+1) * sizeof(char));
        if (g->nomsommet[t] == NULL)
        {   fprintf(stderr, "%s : malloc failed\n", F_NAME);
            exit(0);
        }
        strcpy(g->nomsommet[t], buf);
      } /* for (i = 0; i < n; i++) */
    } /* if ((ret != NULL) && (strcmp(buf, "noms sommets") == 0)) */
    else if ((ret != NULL) && (strncmp(buf, "val sommets", 11) == 0))
    {
      double v;
      for (i = 0; i < n; i++)  
      {
        fscanf(fd, "%d %lf\n", &t, &v);
        g->v_sommets[t] = (TYP_VSOM)v; 
      }
    } /*  if ((ret != NULL) && (strncmp(buf, "val sommets", 11) == 0)) */
    else if ((ret != NULL) && (strncmp(buf, "coord sommets", 13) == 0))
    {
      double x, y;
      for (i = 0; i < n; i++)  
      {
        fscanf(fd, "%d %lf %lf\n", &t, &x, &y);
        g->x[t] = x; 
        g->y[t] = y; 
      }
    } /*  if ((ret != NULL) && (strncmp(buf, "coord sommets", 13) == 0)) */
    else if ((ret != NULL) && (strncmp(buf, "arcs values", 11) == 0))
    {
      double v;
      for (i = 0; i < m; i++)  
      {
        fscanf(fd, "%d %d %lf\n", &t, &q, &v);
        AjouteArcValue(g, t, q, (TYP_VARC)v);
      }
    } /*  if ((ret != NULL) && (strncmp(buf, "arcs values", 11) == 0)) */
    else if ((ret != NULL) && (strncmp(buf, "arcs", 4) == 0))
    {
      for (i = 0; i < m; i++)  
      {
        fscanf(fd, "%d %d\n", &t, &q);
        AjouteArc(g, t, q);
      }
    } /*  if ((ret != NULL) && (strncmp(buf, "arcs", 4) == 0)) */
  } while (ret != NULL);

  return g;
} /* ReadGraphe() */

/* ====================================================================== */
/*! \fn void SaveGraphe(graphe * g, char *filename) 
    \param g (entr�e) : un graphe.
    \param filename (entr�e) : nom du fichier � g�n�rer.
    \brief sauve le graphe g dans le fichier filename. 
*/
void SaveGraphe(graphe * g, char *filename) 
/* ====================================================================== */
#undef F_NAME
#define F_NAME "SaveGraphe"
{
  int i, j, n = g->nsom, m = g->narc;
  pcell p;
  FILE * fd = NULL;
  TYP_VARC v;

  fd = fopen(filename,"w");
  if (!fd)
  {
    fprintf(stderr, "%s: cannot open file: %s\n", F_NAME, filename);
    return;
  }
  
  fprintf(fd, "%d %d\n", n, m);

  if (g->v_sommets)
  {
    fprintf(fd, "val sommets\n");
    for (i = 0; i < n; i++) 
      fprintf(fd, "%d %d\n", i, g->v_sommets[i]);
  }

  if (g->x)
  {
    fprintf(fd, "coord sommets\n");
    for (i = 0; i < n; i++) 
      fprintf(fd, "%d %g %g\n", i, g->x[i], g->y[i]);
  }

  fprintf(fd, "arcs values\n");
  for (i = 0; i < n; i++) 
    for (p = g->gamma[i]; p != NULL; p = p->next)
    {
      j = p->som;
      v = p->v_arc;
      fprintf(fd, "%d %d %ld\n", i, j, v);
    }
  
  fclose(fd);
} /* SaveGraphe() */

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS DE MANIPULATION DES ARCS (APPLICATION GAMMA UNIQUEMENT) */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn void AjouteArc(graphe * g, int i, int s)
    \param g (entr�e/sortie) : un graphe.
    \param i (entr�e) : extr�mit� initiale de l'arc.
    \param s (entr�e) : extr�mit� finale de l'arc.
    \brief ajoute l'arc (i,s) au graphe g (application gamma seulement). 
*/
void AjouteArc(graphe * g, int i, int s)
/* ====================================================================== */
{
  AjouteTete(&(g->libre), &(g->gamma[i]), s, 0);
  g->narc++;
} /* AjouteArc() */

/* ====================================================================== */
/*! \fn void AjouteArcValue(graphe * g, int i, int s, TYP_VARC v)
    \param g (entr�e/sortie) : un graphe.
    \param i (entr�e) : extr�mit� initiale de l'arc.
    \param s (entr�e) : extr�mit� finale de l'arc.
    \param v (entr�e) : une valeur pour l'arc.
    \brief ajoute l'arc (i,s) au graphe g (application gamma seulement). 
*/
void AjouteArcValue(graphe * g, int i, int s, TYP_VARC v)
/* ====================================================================== */
{
  AjouteTete(&(g->libre), &(g->gamma[i]), s, v);
  g->narc++;
} /* AjouteArcValue() */

/* ====================================================================== */
/*! \fn void RetireArc(graphe * g, int i, int s)
    \param g (entr�e/sortie) : un graphe.
    \param i (entr�e) : un sommet de g.
    \param s (entr�e) : un sommet de g.
    \brief retire l'arc (i,s) du graphe g (application gamma seulement),
              si celui-ci etait pr�sent. Sinon, pas d'action. 
*/
void RetireArc(graphe * g, int i, int s)
/* ====================================================================== */
{
  pcell * pliste;
  pliste = g->gamma + i;
  while ((*pliste != NULL) && (((*pliste)->som) != s))
    pliste = &((*pliste)->next);
  if (*pliste != NULL) RetireTete(&(g->libre), pliste);
  g->narc--;
} /* RetireArc() */

/* ====================================================================== */
/*! \fn int PopSuccesseur(graphe * g, int i)
    \param g (entr�e/sortie) : un graphe.
    \param i (entr�e) : un sommet de g.
    \brief retire un arc (i,s) du graphe g (application gamma seulement),
           et retourne le sommet s
    \warning le sommet i doit avoir au moins un successeur (pas de v�rification)
*/
int PopSuccesseur(graphe * g, int i)
/* ====================================================================== */
{
  int s = g->gamma[i]->som;
  RetireTete(&(g->libre), &(g->gamma[i]));
  return s;
} /* PopSuccesseur() */

/* ====================================================================== */
/*! \fn int EstSuccesseur(graphe *g, int i, int s) 
    \param g (entr�e) : un graphe.
    \param i (entr�e) : un sommet de g.
    \param s (entr�e) : un sommet de g.
    \return bool�en.
    \brief retourne 1 si le sommet 's' est un successeur du sommet 'i', 0 sinon.
*/
int EstSuccesseur(graphe *g, int i, int s) 
/* ====================================================================== */
{
  return EstDansListe(g->gamma[i], s);
} /* EstSuccesseur() */

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS DE MANIPULATION DES ARCS (LISTE D'ARCS) */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn void Gamma2ListArcs(graphe *g) 
    \param g (entr�e) : un graphe.
    \brief g�n�re la repr�sentation "liste d'arcs" du graphe g.
*/
void Gamma2ListArcs(graphe *g) 
/* ====================================================================== */
{
  int i, a, n = g->nsom, m = g->narc;
  pcell p;

  a = 0;
  for (i = 0; i < n; i++) 
    for (p = g->gamma[i]; p != NULL; p = p->next)
    {
      g->tete[a] = i;
      g->queue[a] = p->som;
      g->v_arcs[a] = p->v_arc;
      a++;
    }
} /* Gamma2ListArcs() */

/* ====================================================================== */
/* ====================================================================== */
/* FONCTIONS DE GENERATION DE GRAPHES */
/* ====================================================================== */
/* ====================================================================== */

/* ====================================================================== */
/*! \fn graphe * GrapheAleatoire(int nsom, int narc)
    \param nsom (entr�e) : nombre de sommets.
    \param narc (entr�e) : nombre d'arcs.
    \return un graphe.
    \brief retourne un graphe al�atoire � 'nsom' sommets et 'narc' arcs. 
              Le graphe est antisym�trique et sans boucle.
              Le nombre d'arcs doit �tre <= nsom (nsom - 1) / 2.
              Les arcs sont pond�r�s (valeur al�atoire entre 0.0 et 1.0).
    \warning la m�thode employ�e ici est na�ve, tres inefficace du point de vue
              temps de calcul et ne garantit aucune propri�t� statistique. 
*/
graphe * GrapheAleatoire(int nsom, int narc)
/* ====================================================================== */
#undef F_NAME
#define F_NAME "GrapheAleatoire"
{
  graphe * g;
  int i, j, m;
  double mmax = ((double)nsom * ((double)nsom - 1)) / 2;

  if (narc > mmax)
  {
    fprintf(stderr, "%s : pas plus de %g arcs pour %d sommets\n", 
                     mmax, nsom, F_NAME);
    exit(0);
  }

  if ((mmax >= (1<<31)) || (narc <= ((int)mmax) / 2))
  {
    g = InitGraphe(nsom, narc);
    while (narc > 0)
    {
      narc--;
      do
      {
        i = rand() % nsom;
        j = rand() % nsom;
      } while ((i == j) || EstSuccesseur(g, i, j) || EstSuccesseur(g, j, i));
      AjouteArc(g, i, j);
      g->tete[narc] = i;
      g->queue[narc] = j;
      if (g->v_arcs) g->v_arcs[narc] = (TYP_VARC)(rand()*100.0);
    }
  }
  else /* on part du graphe complet et on retire des arcs au hasard */
  {
    /* construit un graphe complet antisymetrique sans boucle */
    g = InitGraphe(nsom, (int)mmax);
    for (i = 0; i < nsom ; i++)
      for (j = i+1; j < nsom; j++)
        AjouteArc(g, i, j);         

    /* retire mmax - narc arcs */
    m = (int)mmax;
    while (m > narc)
    {
      m--;
      do
      {
        i = rand() % nsom;
        j = rand() % nsom;
      } while ((i == j) || !EstSuccesseur(g, min(i,j), max(i,j)));
      RetireArc(g, min(i,j), max(i,j));
    }

    /* rajoute la liste des arcs et les poids */
    m = 0;
    for (i = 0; i < nsom ; i++)
      for (j = i+1; j < nsom; j++)
        if (EstSuccesseur(g, i, j))
	{
          g->tete[m] = i;
          g->queue[m] = j;
          if (g->v_arcs) g->v_arcs[narc] = (TYP_VARC)(rand()*100.0);
          m++;
	}
  }

  return g;
} /* GrapheAleatoire() */
