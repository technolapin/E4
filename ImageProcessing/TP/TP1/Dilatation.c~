#include<stdlib.h>
#include<stdio.h>
#include "graphes.h"
#include "mcimage.h"
#include "mccodimage.h"


struct graphe *initImageGraph(struct xvimage *image, 
			      int *tab_es_i, int *tab_es_j, 
			      /* list of successeurs points (coordinates) of the point (0,0) */
			      int n_es){
  
  struct graphe * G;

  int rs = rowsize(image);     /* row size */
  int cs = colsize(image);     /* column size */
  int n = rs * cs;             /* image size = |E| */
  int m = n * (n_es);          /* |\Gamma| without taking into account the borders */
  
  int x, y;                    /* two points */
  int x_i, x_j, y_i, y_j;      /* coordinates of x and y */

  int k;                       /* an index */
  
  G = InitGraphe(n, m);
  
  for(x_j = 0; x_j < cs; x_j++ )
    for(x_i = 0; x_i < rs; x_i++ ){ /* for any vertex (x_i, x_j) de E */
      for(k = 0; k < n_es; k++) { /* for any successor (y_i,y_j) according to the se */
	y_i = x_i + tab_es_i[k];
	y_j = x_j + tab_es_j[k];
	
	/***************************************************/
	/*                    To complete                  */
	/***************************************************/

	/* Some help : Arcs can be added to a graph with the procedure */
	/*    AjouteArc whose prototype is : */ 
	
	/* /\* void AjouteArc 	( 	graphe *  	g, *\/ */
	/* /\* 	int  	i, *\/ */
	/* /\* 	int  	s  *\/ */
	/* /\* ) 		 *\/ */

	/* and which adds the arc (i,s) to the graph g (work only on */
	/*      the successor map gamma (array of linked lists of */
	/*      successors)).  */

	}
      }
  
  return G;
}

#define INSET 255
#define OUTSET 0

unsigned char *dilat(unsigned char *X, struct graphe *G){
  unsigned char *Y;
  int x, y;         /* two vertices */
  pcell p;
  int n = G->nsom;  /* number of elements of the space E */

  Y = calloc(1, n * sizeof(unsigned char));
  if(Y == NULL){
    fprintf(stderr, "Erreur d'allocation mémoire dans la fonction dilat\n");
    exit(0);
  }
    
  memset(Y, OUTSET ,G->nsom * sizeof(unsigned char)); /* Y is initialized to the emptyset */
    
  for(x = 0; x < n; x++){
    if(X[x] == INSET){ /* the vertex x belongs to X */
      for(p = G->gamma[x]; p != NULL; p = p->next){
	y = p->som;
	Y[y] = INSET;
      }
    }
  }

  return Y;
}


int main(int argc, char ** argv){
  struct xvimage * image;

  int *tab_es_i;               /* list of the first coordinates of the points in the s.e. */
  int *tab_es_j;               /* list of the second coordinates of the points in the s.e. */
  int n;                       /* Number of vertices in the structuring element */
  
  unsigned char *X;                      /* the subset of the space (the image domain) that we want to dilate */
  unsigned char *Y;                      /* the dilation of X */

  struct graphe * G;                     /* the s.e. represented as a graph */

  if (argc != 4)
  {
    fprintf(stderr, "usage: %s im.pgm el.pgm out.pgm \n", argv[0]);
    exit(1);
  }

  image = readimage(argv[1]); /* reading of the image */
  if (image == NULL)
  {
    fprintf(stderr, "%s: readimage failed\n", argv[0]);
    exit(1);
  }

  readSeList(argv[2], &tab_es_i, &tab_es_j, &n); /* reading of the structuring element */

  printf("L'e.s. contient %d points \n",n);

  G = initImageGraph(image, tab_es_i, tab_es_j, n); /* Building of the graph */
  
  printf("Le graphe G contient %d sommets et %d arcs \n", G->nsom, G->narc);
  
  X = UCHARDATA(image); 
  
  Y = dilat(X, G); /* Dilation of the subset X (set of white image pixels) */

  memcpy(X, Y, G->nsom*sizeof(unsigned char));
  writeimage(image, argv[argc-1]);

  freeimage(image);
  free(Y);
  free(tab_es_i);
  free(tab_es_j);
  TermineGraphe(G);
  
  return 0;
}
