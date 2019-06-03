/* Savannah Loberger
 * File: unittest-smithy.c
 * test the smithy function 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "smithy"

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

        // ----------- TEST 1: Check that the card was played and cards were discarded --------------
        printf("TEST 1: \n");

        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        choice1 = 1;
        
        player = whoseTurn(&testG);

		printf("Before hand count: %d \n", testG.handCount[player]);

		//run the refractored code for the smithy card
		smithyCard(handpos, &testG, player);

        //test should be two more card than the state
        MY_ASSERT((testG.handCount[player]) == (G.handCount[player]+2));
		printf("After hand count: %d \n", testG.handCount[player]);


        printf("----------End Testing %s Card----------\n", TESTCARD);

    return 0;

} 


/* For referrence:
void smithyCard(int handPos, struct gameState* state, int currentPlayer)
{
	//+3 Cards
	for (int i = 1; i < 3; i++)
	{
		drawCard(currentPlayer, state);
	}

	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);

}
*/

