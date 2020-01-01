/* $Id: mcimage.h,v 1.9 2006/02/28 07:49:12 michel Exp $ */
/* ============== */
/* prototypes for mcimage.c    */
/* ============== */

extern struct xvimage *allocimage(char * name, int rs, int cs, int d, int t);
extern void razimage(struct xvimage *f);
extern struct xvimage *allocheader(char * name, int rs, int cs, int d, int t);
extern int showheader(char * name);
extern void freeimage(struct xvimage *image);
extern struct xvimage *copyimage(struct xvimage *f);
extern int copy2image(struct xvimage *dest, struct xvimage *source);
extern int equalimages(struct xvimage *im1, struct xvimage *im2);
extern void list2image(struct xvimage * image, double *P, int n);
extern double * image2list(struct xvimage * image, int *n);

extern void writeimage(
  struct xvimage * image,
  char *filename
);

extern void writese(
  struct xvimage * image,
  char *filename,
  int x, int y, int z
);

extern void writelongimage(
  struct xvimage * image,
  char *filename
);

extern void writerawimage(
  struct xvimage * image,
  char *filename
);

extern void writeascimage(
  struct xvimage * image,
  char *filename
);

extern void printimage(
  struct xvimage * image
);

extern void writergbimage(
  struct xvimage * redimage,
  struct xvimage * greenimage,
  struct xvimage * blueimage,
  char *filename
);

extern struct xvimage * readimage(
  char *filename
);

extern struct xvimage * readheader(
  char *filename
);

extern struct xvimage * readse(char *filename, int *x, int *y, int*z);
extern void readSeList(char *esname, int **x, int **y, int *n);

extern struct xvimage * readlongimage(
  char *filename
);

extern int readrgbimage(
  char *filename,
  struct xvimage ** r,
  struct xvimage ** g,
  struct xvimage ** b
);

extern int readbmp(
  char *filename, 
  struct xvimage ** r, 
  struct xvimage ** g, 
  struct xvimage ** b
);

extern void writebmp(
  struct xvimage * redimage,
  struct xvimage * greenimage,
  struct xvimage * blueimage,
  char *filename
);

extern int readrgb(
  char *filename, 
  struct xvimage ** r, 
  struct xvimage ** g, 
  struct xvimage ** b
);

extern int convertgen(struct xvimage **f1, struct xvimage **f2);
extern int convertlong(struct xvimage **f1);
extern int convertfloat(struct xvimage **f1);
