//Patrisia Kaplun            id:314631474
//Lior Hai                   id:207134990
//Date: 24/08/2021
//The Game Of Sudoku
#include "Func.h"
int main()
{
    playerList lst;
    WinList winners;
    playerNode** pArr;
    int numPlayers;
    char space;
    playerNode* a, * b, * curr;
    Tree players;

    makeEmptyListp(&lst);

    printf("Welcome!\n");

    printf("How many players?\n");

    scanf("%d", &numPlayers);

    printf("please enter the names of the players\n");

    scanf("%c", &space);

    for (int i = 0; i < numPlayers; i++)
    {
        insertDataToEndListp(&lst);
    }

    pArr = makePArr(lst, &numPlayers);

    players = BuildTreeFromArray(pArr, numPlayers);

    freeArr(pArr, numPlayers);

    playGame(players, &lst, &winners);

    freeTree(&players);

    printWinners(&winners);
}