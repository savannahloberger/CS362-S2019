# Savannah Loberger 
# CS362 
# MAKEFILE for testme - random quiz 

CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc  -o testme -g testme.c $(CFLAGS)

runtests: testme
	./testme &> randomtestresult.out
	gcov testme.c >> randomtestresult.out
	cat testme.c.gcov >> randomtestresult.out

all: testme

clean: 
	rm -rf *.o *.gcov *.gcda *.gcno *.so *.out testme


