/* Savannah Loberger
 * File: unittest1.c
 * A negative test against the adventurer card 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
//#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "adventurer"

// Reference: http://www.dillonbhuff.com/?p=439
#define MY_ASSERT(x) if (!(x)) { printf("My custom assertion failed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__);} else{ printf("My custom assertion passed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }


// Using the setup for testing from the example test code provided (with some modifications) 
int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int player = 0;
	struct gameState G, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);


	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Check that the card was added to the hand --------------
	printf("TEST 1: \n");

	// copy the game state to a test case
	memcpy(&test, &G, sizeof(struct gameState));
	
	//cardEffect(TESTCARD, choice1, choice2, choice3, &testG, handpos, &bonus);	

	player = whoseTurn(&test);

	//run the refractored code for the adventurer card 
	adventurer_card(player, &G);

	//test should be one less card than the state
	MY_ASSERT((test.handCount[player]-1) == (G.handCount[player]));

	// ----------- TEST 2: Check that the card was played --------------
        printf("TEST 2: \n");

	//test should be one less card than the state as the reference
        MY_ASSERT((test.playedCardCount+1) == (G.playedCardCount));


 	// ----------- TEST 3: Check that the actions were added --------------
        printf("TEST 3: \n");

	//test should have 2 less actions than the state
        MY_ASSERT((test.numActions+2) == (G.numActions));


	printf("----------End Testing %s Card----------\n", TESTCARD);

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

