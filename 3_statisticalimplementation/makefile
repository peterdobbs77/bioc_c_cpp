#makefile
all: preproc.exe cluster.exe

preproc.exe: vector_ops.o stats.o preproc.o
	gcc -g -o preproc.exe vector_ops.o stats.o preproc.o -lm

cluster.exe: cluster.o vector_ops.o stats.o
	gcc -g -o cluster.exe vector_ops.o stats.o cluster.o -lm

clean:
	rm *.o
