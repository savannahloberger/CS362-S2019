/* Savannah Loberger
 * File: unittest2.c
 * test the council_room function 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "council_room"

// Reference: http://www.dillonbhuff.com/?p=439
//#define MY_ASSERT(x) if (!(x)) { printf("My custom assertion failed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); abort(); }
#define MY_ASSERT(x) if (!(x)) { printf("My custom assertion failed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__);} else{ printf("My custom assertion passed: (%d), function %s, file %s, line %d.\n", x, __PRETTY_FUNCTION__, __FILE__, __LINE__); }

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
        struct gameState G, testG;
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                        sea_hag, tribute, smithy, council_room};

        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &G);


        printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

        // ----------- TEST 1: Check that the card was added to the hand --------------
        printf("TEST 1: \n");

        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        choice1 = 1;
        
        //cardEffect(TESTCARD, choice1, choice2, choice3, &testG, handpos, &bonus);
	

        player = whoseTurn(&testG);

        //test should be one less card than the state
        MY_ASSERT((testG.handCount[player]-1) == (G.handCount[player]));


        printf("----------End Testing %s Card----------\n", TESTCARD);

    return 0;

} 


/* For referrence:
void council_room_card(int currentPlayer, struct gameState *state, int handPos){
  int i;
  //+4 Cards
  for (i = 0; i < 4; i++)
   {
       drawCard(currentPlayer, state);
    }

  //+1 Buy
  state->numBuys++;

   //Each other player draws a card
   for (i = 0; i < state->numPlayers; i++)
      {
        if ( i != currentPlayer )
            {
              drawCard(i, state);
            }
        i++; //BUG: skips over every other player for drawing cards
        }

      //put played card in played card pile
      discardCard(handPos, currentPlayer, state, 0);
}
*/

