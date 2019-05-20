/* Savannah Loberger
 * File: randomtestadventurer.c
 * A random test of the adventurer card 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

#define TESTCARD "adventurer"
#define MAX_TEST 100000

// Reference: http://www.dillonbhuff.com/?p=439
#define MY_ASSERT(x) if (!(x)) { printf("My custom assertion failed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__);} else{ printf("My custom assertion passed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__); }


void test_adventurer()
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

    int test1Passed = 0, test2Passed = 0; //, test3Passed;

    // Test the playing of adventurer card with different deck sizes and different hand sizes 
    for(i = 0; i < MAX_TEST; i++){
        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);

	// Setup random deck size and hand size, keeping within the game max constraints
	deckSize = (rand() % (MAX_DECK + 1));
	if(deckSize > 50){
	    handSize = (rand() % (10 + 1));
	}else{
	    handSize = (rand() % (deckSize + 1)); //hand has to be smaller than the deck
	}

	G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
	

	printf("Deck Size: %d 	Hand Size: %d \n", deckSize, handSize);

        printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

        // ----------- TEST 1: Check that the card was added to the hand --------------
        printf("TEST 1: \n");

        // copy the game state to a test case
        memcpy(&test, &G, sizeof(struct gameState));
        player = whoseTurn(&test);

        //run the refractored code for the adventurer card
        adventurer_card(player, &G);

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

        printf("----------End Testing %s Card----------\n", TESTCARD);

    }

    // Results from testing 
    printf("TEST 1: Passed %d / %d tests\n", test1Passed, MAX_TEST);
    printf("TEST 2: Passed %d / %d tests\n", test2Passed, MAX_TEST);
    

}


// Using the setup for testing from the example test code provided (with some modifications) 
int main() {
    
    srand(time(NULL));
    test_adventurer();
    return 0;
} 

/* for referrence
void adventurer_card(int currentPlayer, struct gameState *state){
  int drawntreasure = 1; //BUG: should be 0 instead of 1
  int z = 0;
  int cardDrawn;
  int temphand[MAX_HAND];
  while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
          shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
          drawntreasure++;
        else{
          temphand[z]=cardDrawn;
          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
          z++;
        }
      }
      while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
      }
}
*/
