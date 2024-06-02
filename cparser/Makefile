CC := gcc
CFLAGS4LIB := -Wall -O3 -c -DIS_LIB

test: ParseInt.c common.h
	${CC} -Wall -O3 -o ParseInt.out ParseInt.c
	./ParseInt.out
	${CC} -Wall -O3 -o ParseFloat.out ParseFloat.c
	./ParseFloat.out

lib: ParseInt.c ParseFloat.c common.h
	${CC} ${CFLAGS4LIB} ParseInt.c
	${CC} ${CFLAGS4LIB} ParseFloat.c

clear:
	rm *.out *.o
