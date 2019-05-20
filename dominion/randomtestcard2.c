/* Savannah Loberger
 * File: randomtestcard1.c
 * A random test of the village card 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "village"
#define MAX_TEST 100000

// Reference: http://www.dillonbhuff.com/?p=439
#define MY_ASSERT(x) if (!(x)) { printf("My custom assertion failed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__);} else{ printf("My custom assertion passed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__); }


void test_village()
{
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int deckSize, handSize;
    int player = 0;
    struct gameState G, test;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                        sea_hag, tribute, smithy, council_room};

    int test1Passed = 0, test2Passed = 0, test3Passed = 0;

    // Test the playing of village card with different deck sizes and different hand sizes 
    for(i = 0; i < MAX_TEST; i++){
        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);
	
	// Setup random deck size and hand size, keeping within the game max constraints
	deckSize = (rand() % (MAX_DECK + 1));
	//handSize = (rand() % (deckSize + 1)); //hand has to be smaller than the deck
	if(deckSize > 50){
	    handSize = (rand() % (20 + 1));
	}else{
	    handSize = (rand() % (deckSize + 1)); //hand has to be smaller than the deck
	}

	G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
	//handpos = (rand() % handSize + 1);


        printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

        // ----------- TEST 1: Check that the card was added to the hand --------------
        printf("TEST 1: \n");

        // copy the game state to a test case
        memcpy(&test, &G, sizeof(struct gameState));
        player = whoseTurn(&test);

        //run the refractored code for the adventurer card
        village_card(player, &G, handpos);

        //test should be one less card than the state
        MY_ASSERT((test.handCount[player]-1) == (G.handCount[player]));

	if((test.handCount[player]-1) == (G.handCount[player])){
	    test1Passed++;
	}

	// ----------- TEST 2: Check that the card was played --------------
        printf("TEST 2: \n");

        //test should be one less card than the state as the reference
        MY_ASSERT((test.playedCardCount+1) == (G.playedCardCount));

	if((test.playedCardCount+1) == (G.playedCardCount)){
            test2Passed++;
        }

	// ----------- TEST 3: Check that the number of cards stayed --------------
	printf("TEST 3: \n");

	//test should be two more cards in the hand (-1 for played village + 1 new) than the state
        MY_ASSERT((test.handCount[player]) == (G.handCount[player]));
	
	if((test.handCount[player]) == (G.handCount[player])){
            test3Passed++;
        }

        //printf("----------End Testing %s Card----------\n", TESTCARD);

    }

    // Results from testing    
    printf("TEST 1: Passed %d / %d tests\n", test1Passed, MAX_TEST);
    printf("TEST 2: Passed %d / %d tests\n", test2Passed, MAX_TEST);
    printf("TEST 3: Passed %d / %d tests\n", test3Passed, MAX_TEST);


}


// Using the setup for testing from the example test code provided (with some modifications) 
int main() {
    
    srand(time(NULL));
    test_village();
    return 0;
} 

/* for referrence
void village_card(int currentPlayer, struct gameState *state, int handPos){
      //+1 Card
      drawCard(currentPlayer, state);

      //+2 Actions
      state->numActions = state->numActions + 2;

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
}*/
