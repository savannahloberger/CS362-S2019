CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

#########
#make each test created 
unittest-adventurer: unittest-adventurer.c dominion.o rngs.o
	gcc -o unittest-adventurer -g  unittest-adventurer.c dominion.o rngs.o $(CFLAGS)

unittest-minion: unittest-minion.c dominion.o rngs.o
	gcc -o unittest-minion -g  unittest-minion.c dominion.o rngs.o $(CFLAGS)

unittest-smithy: unittest-smithy.c dominion.o rngs.o
	gcc -o unittest-smithy -g  unittest-smithy.c dominion.o rngs.o $(CFLAGS)

unittest-steward: unittest-steward.c dominion.o rngs.o
	gcc -o unittest-steward -g  unittest-steward.c dominion.o rngs.o $(CFLAGS)

testresults: unittest-adventurer unittest-minion unittest-smithy unittest-steward 
	./unittest-adventurer &> testresult.out
	gcov unittest-adventurer.c >> testresult.out
	cat unittest-adventurer.c.gcov >> testresult.out
	./unittest-minion >> testresult.out
	gcov unittest-minion.c >> testresult.out
	cat unittest-minion.c.gcov >> testresult.out
	./unittest-smithy >> testresult.out
	gcov unittest-smithy.c >> testresult.out
	cat unittest-smithy.c.gcov >> testresult.out
	./unittest-steward >> testresult.out
	gcov unittest-steward.c >> testresult.out
	cat unittest-steward.c.gcov >> testresult.out	

#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 
