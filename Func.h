#ifndef DEBUG__H
#define DEBUG__H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <time.h>

#define BS 9
#define NOT_FINISH 0
#define FINISH_SUCCESS 1
#define FINISH_FAILURE -1
#define FILLED 2
#define FAIL -2
#define MAX 100

//possibile
typedef struct _Array
{
    short* arr;
    unsigned short size;
} Array;

//player Node
typedef struct playerNode {
    char name[MAX];
    short board[9][9];
    Array*** possib;
    struct playerNode* next;
} playerNode;

//players List
typedef struct playerList {
    playerNode* head;
    playerNode* tail;
} playerList;

//board list Node
typedef struct _listNode
{
    int row;
    int col;
    struct _listNode* next;
}listNode;

//board list
typedef struct _list
{
    struct _listNode* head;
    struct _listNode* tail;
}list;

//win player list
typedef struct winList {
    playerNode* head;
    playerNode* tail;
} WinList;

//tree node
typedef struct  treeNode
{
    playerNode* player;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

//players tree
typedef struct tree
{
    TreeNode* root;
} Tree;

//active player list functions
void makeEmptyListp(playerList* lst);//empty the list of players
void insertDataToEndListp(playerList* lst);//create and add a new player to the list
playerNode* createNewListNodep(playerNode* next);//creates new player
void insertNodeToEndListp(playerList* lst, playerNode* tail);//insert player to the end of the player's list
bool isEmptyListp(playerList* lst);//is the list empty?
void playGame(Tree tr, playerList* lst, WinList* win);//function to start the game
void playTree(TreeNode* root, playerList* lst, WinList* winnerList);//run on the player's tree to play the game

//make players arr from list ,merge arr
playerNode** makePArr(playerList lst, int* size);//make a new player's array
playerNode** merge(playerNode** a1, int size1, playerNode** a2, int size2);//merge between 2 arrays of players
void copy(playerNode** des, playerNode** src, int size);// copies source to destination
void mergeSort(playerNode** arr, int size);// sorting an array of players
int upDateArr(playerNode*** arr, int size);// updates size of array
int findNewSize(int size);//finds the new size of array
int checkFull(short board[9][9]);//checking if the board is full

//random board functions
Array*** randomBoard(short sudokuBoard[9][9]);//random's the values of the board
void deleteNode(listNode* after);//delete's a node from the list
listNode* createNewListNode(int row, int col, listNode* next);//creates nodes for list to random board
void insertNodeToEndList(list* lst, listNode* tail);//insert the node to the end of the list
bool isEmptyList(list* lst);// is the list empty?

//board functions
Array*** makeMat();//creates array of possibilities for the board
void upDate(Array*** possibilities, short board[][9], int row, int col, int num, int* found);// updates the possibilities of the board after isert of a number to the board
void sudokoPrintBoard(short sudokuBoard[9][9]);//print's the board to the screen
int removeNum(short* arr, int num, int size);//removes the number from the array of possibilities of a certain spot in the board
short* checkOptions(int row, int col, short sudokuBoard[][9], unsigned short* size);//returns an array of possible numbers for the spot in the board
Array*** PossibleDigits(short sudokuBoard[][9]);//checks the possible digits for the board
int OneStage(short board[][9], Array*** possibilities, int* x, int* y);//updates all the places in the board with only one possible number to put in
void resetArray(short* arr);// resets the possiblities for a certain spot in the board
int FillBoard(short board[][9], Array*** possibilities);//fills the board by the scanned numbers from the player
bool checkLigalboard(short sudokuBoard[][9]);//checks if the board is legal
bool checkLigalrow(short sudokuBoard[][9], int row);//checks for the row if it's legal
bool checkLigalcol(short sudokuBoard[][9], int col);//checks for the collum if it's legal
bool checkLigalSquare(short sudokuBoard[][9], int row, int col);//checks for the square if it's legal

//win list
void insertNodeToEndListw(WinList* lst, playerNode* tail);//inserts a player to the end of the winner's list
bool isEmptyListw(WinList* lst);//checks if the winner list is empty
void printWinners(WinList* win);//print's the winner's boards and names
void removeListNode(playerList* lst, TreeNode* root);//removes a player from the active players list
void freePlayer(playerNode* node);//free the values of a player

//build tree of players with new size
Tree BuildTreeFromArray(playerNode** arr, int  size);// builds a tree from a given array of players
TreeNode* BuildTreeFromArrayHelper(playerNode** arr, int size);//helps BuildTreeFromArray to complete its mission
TreeNode* createNewTNode(playerNode* data, TreeNode* left, TreeNode* right);//creates a new root for the tree for a player
void freeTree(Tree* tr);//frees the tree
void freeTreeHelper(TreeNode* root);//helps to free the tree
void freeArr(playerNode** arr, int size);//frees the array of players


#endif
