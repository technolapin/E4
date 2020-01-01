/* $Id: mccodimage.h,v 1.13 2007/07/10 08:49:29 michel Exp $ */
#define SHRT_MIN -32767 
#define SHRT_MAX +32767 
#define USHRT_MAX 65535 
#define INT_MIN -32767 
#define INT_MAX +32767 
#define UINT_MAX 65535 
#define LONG_MIN -2147483647 
#define LONG_MAX +2147483647
#define ULONG_MAX 4294967295
#define NDG_MAX 255            /* niveau de gris max */
#define NDG_MIN 0              /* niveau de gris min */

#define VRAI 255
#define FAUX 0



/* definitions for data storage type,
   unsigned int data_storage_type; */
#define	VFF_TYP_BIT		0	/* pixels are on or off (binary image)*/
                                        /* Note: This is an X11 XBitmap 
					   with bits packed into a byte and
					   padded to a byte */
#define	VFF_TYP_1_BYTE		1	/* pixels are byte (uint8_t) */
#define	VFF_TYP_2_BYTE		2	/* pixels are two byte (int16_t) */
#define	VFF_TYP_4_BYTE		4	/* pixels are four byte (integer) */
#define	VFF_TYP_FLOAT		5	/* pixels are float (single precision)*/
#define VFF_TYP_DOUBLE		9	/* pixels are float (double precision)*/

struct xvimage {
  char *name;
  unsigned int row_size;                    /* Size of a row (number of columns) */
  unsigned int col_size;                    /* Size of a column (number of rows) */
  unsigned int depth_size;                  /* Number of planes (for 3d images) */
  unsigned int time_size;                   /* Number of (2d or 3d) images */
  unsigned int num_data_bands;	        /* Number of bands per data pixel,
					   or number of bands per image, or
					   dimension of vector data, or
					   number of elements in a vector */
  unsigned int data_storage_type;           /* storage type for disk data */
  double xdim, ydim, zdim;              /* voxel dimensions in real world */
  void * image_data;                    /* pointer on raw data */
};

#define UCHARDATA(I)  ((unsigned char*)((I)->image_data))
#define USHORTDATA(I) ((uint16_t*)((I)->image_data))
#define ULONGDATA(I)  ((unsigned int*)((I)->image_data))
#define FLOATDATA(I)  ((float*)((I)->image_data))
#define DOUBLEDATA(I) ((double*)((I)->image_data))
#define colsize(I)    ((I)->col_size)
#define rowsize(I)    ((I)->row_size)
#define depth(I)      ((I)->depth_size)
#define tsize(I)      ((I)->time_size)
#define nbands(I)     ((I)->num_data_bands)
#define datatype(I)   ((I)->data_storage_type)
