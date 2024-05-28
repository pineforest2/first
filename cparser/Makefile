CC := gcc
CFLAGS4LIB := -Wall -c -DIS_LIB

test: ParseInt.c
	${CC} -Wall -O3 -o ParseInt.out ParseInt.c
	./ParseInt.out

lib: ParseInt.c
	${CC} ${CFLAGS4LIB} ParseInt.c

clear:
	rm *.out *.o
