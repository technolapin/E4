
all:	Dilatation


clean:
	rm *.o Dilatation *~

mcimage.o:	mcimage.c mcimage.h mcutil.h mccodimage.h
	gcc -c mcimage.c

graph_basic.o:	graphes.h graph_basic.c
	gcc -c graph_basic.c

Dilatation:	Dilatation.c mcimage.h mccodimage.h graphes.h mcimage.o graph_basic.o
	gcc Dilatation.c mcimage.o graph_basic.o -o Dilatation
