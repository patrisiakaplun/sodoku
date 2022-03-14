#include "Func.h"
void freeArr(playerNode** arr, int size)
{
    free(arr);
}

void printWinners(WinList* win)///////may need to change to print to file
{
    playerNode* curr = win->head;
    playerNode* saver;

    if (isEmptyListw(win))//there are no winners
    {
        printf("That's a shame, no one won this round.. better luck next time :)\n");
    }

    else
    {
        printf("And the Winners are: \n");

        while (curr != NULL)
        {
            printf("%s !\n", curr->name);
            sudokoPrintBoard(curr->board);
            printf("\n");
            saver = curr;
            curr = curr->next;
            freePlayer(saver);
        }
    }
}

void playGame(Tree tr, playerList* lst, WinList* win)
{
    win->head = win->tail = NULL;

    playTree(tr.root, lst, win);
}

void freePlayer(playerNode* node)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            free(node->possib[i][j]);
        }
        free(node->possib[i]);
    }
    free(node->possib);
    free(node);
}

void playTree(TreeNode* root, playerList* lst, WinList* winnerList)
{
    int res;
    playerNode* win, * saver, * curr, * prev;

    if (isEmptyListp(lst))
        return;

    if (root == NULL)
        return;

    else //there is a player
    {
        playTree(root->left, lst, winnerList);

        if (root->player != NULL)
        {
            printf("it's time for %s to play!\n", root->player->name);
            res = FillBoard(root->player->board, root->player->possib);//or one stage

            if (res == FILLED)
            {
                printf("%s finished his game.\n", root->player->name);
                removeListNode(lst, root);
                insertNodeToEndListw(winnerList, root->player);
            }

            else
            {
                removeListNode(lst, root);
                freePlayer(root->player);
            }

        }
        playTree(root->right, lst, winnerList);
        root->player = NULL;
    }
}

void removeListNode(playerList* lst, TreeNode* root)
{
    playerNode* saver, * curr, * prev;

    if (lst->head == root->player)
    {
        if (lst->tail == root->player)
        {
            lst->head = lst->tail = NULL;
        }

        else
        {
            saver = lst->head->next;
            lst->head = saver;
        }
    }

    else
    {
        prev = lst->head;
        curr = lst->head->next;

        while (curr != NULL)
        {
            if (curr == root->player)
            {
                if (curr == lst->tail)
                {
                    lst->tail = prev;
                    lst->tail->next = NULL;
                }

                else
                {
                    saver = curr->next;
                    prev->next = saver;
                }
            }

            prev = curr;
            curr = curr->next;
        }
    }
}

void makeEmptyListp(playerList* lst)
{
    lst->head = lst->tail = NULL;
}

void insertDataToEndListp(playerList* lst)
{
    playerNode* newTail;
    newTail = createNewListNodep(NULL);
    insertNodeToEndListp(lst, newTail);
}

playerNode* createNewListNodep(playerNode* next)
{
    playerNode* res = (playerNode*)malloc(sizeof(playerNode));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            res->board[i][j] = -1;
        }
    }

    gets(res->name);

    res->possib = randomBoard(res->board);

    res->next = next;

    return res;
}

Array*** makeMat()
{
    Array*** res = (Array***)malloc(9 * sizeof(Array**));

    for (int i = 0; i < 9; i++)
    {
        res[i] = (Array**)malloc(9 * sizeof(Array*));

        for (int j = 0; j < 9; j++)
            res[i][j] = (Array*)malloc(sizeof(Array));
    }

    return res;
}

void insertNodeToEndListp(playerList* lst, playerNode* tail)
{
    if (isEmptyListp(lst) == true)
        lst->head = lst->tail = tail;

    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }

    tail->next = NULL;
}

void insertNodeToEndListw(WinList* lst, playerNode* tail)
{
    if (isEmptyListw(lst) == true)
        lst->head = lst->tail = tail;

    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }

    tail->next = NULL;
}

bool isEmptyListw(WinList* lst)
{
    if (lst->head == NULL)
        return true;

    else
        return false;
}

bool isEmptyListp(playerList* lst)
{
    if (lst->head == NULL)
        return true;

    else
        return false;
}

playerNode** makePArr(playerList lst, int* size)
{
    playerNode** res = (playerNode**)malloc(*size * sizeof(playerNode*));

    playerNode* curr;
    int index = 0;
    int newsize;

    curr = lst.head;

    while (curr != NULL)
    {
        //printf("name on list: %s\n", curr->name);
        res[index] = curr;
        curr = curr->next;
        index++;
    }

    mergeSort(res, *size);

    (*size) = upDateArr(&res, *size);

    return res;
}

void upDate(Array*** possibilities, short board[][9], int row, int col, int num, int* found)
{
    int rowPart, colPart;
    *found = 0;

    if (possibilities[row][col]->size == 1 && possibilities[row][col]->arr[0] == num)
    {
        free(possibilities[row][col]->arr);
        possibilities[row][col]->arr = NULL;
        possibilities[row][col]->size = 0;
    }

    for (int i = 0; i < 9; i++)
    {
        if (removeNum(possibilities[row][i]->arr, num, possibilities[row][i]->size) > 0)
        {
            (possibilities[row][i]->size)--;
            possibilities[row][i]->arr = (short*)realloc(possibilities[row][i]->arr, (possibilities[row][i]->size) * sizeof(short));

            if (possibilities[row][i]->size == 1 && i < col)
                *found = 1;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (removeNum(possibilities[i][col]->arr, num, possibilities[i][col]->size) > 0)
        {
            (possibilities[i][col]->size)--;
            possibilities[i][col]->arr = (short*)realloc(possibilities[i][col]->arr, (possibilities[i][col]->size) * sizeof(short));

            if (possibilities[i][col]->size == 1 && i < row)
                *found = 1;
        }
    }

    rowPart = (row / 3) * 3;
    colPart = (col / 3) * 3;

    for (int i = rowPart; i < (rowPart + 3); i++)
    {
        for (int j = colPart; j < (colPart + 3); j++)
        {
            if (removeNum(possibilities[i][j]->arr, num, possibilities[i][j]->size) > 0)
            {
                (possibilities[i][j]->size)--;
                possibilities[i][j]->arr = (short*)realloc(possibilities[i][j]->arr, (possibilities[i][j]->size) * sizeof(short));

                if (possibilities[i][j]->size == 1 && &(board[i][j]) < &(board[row][col]))
                    *found = 1;
            }
        }
    }
}

Array*** randomBoard(short sudokuBoard[9][9])
{
    Array*** possibilities;
    int startNums, randomPlace, cubeSize, found, removeIndex, options = 81;
    list lst;
    listNode* curr, * saver;

    possibilities = PossibleDigits(sudokuBoard);

    lst.head = lst.tail = NULL;

    for (int i = 0; i < 81; i++)
    {
        curr = createNewListNode((i / 9), (i % 9), NULL);
        insertNodeToEndList(&lst, curr);
    }

    srand(time(0));

    startNums = fmod(rand(), (20)) + 1;

    for (int i = 1; i <= startNums; i++)
    {
        randomPlace = fmod(rand(), (options));

        curr = lst.head;
        saver = lst.head;

        for (int j = 1; j <= randomPlace; j++)
        {
            saver = curr;
            curr = curr->next;
        }

        cubeSize = possibilities[curr->row][curr->col]->size;
        removeIndex = fmod(rand(), (cubeSize));
        sudokuBoard[curr->row][curr->col] = possibilities[curr->row][curr->col]->arr[removeIndex];
        possibilities[curr->row][curr->col]->arr[0] = sudokuBoard[curr->row][curr->col];
        possibilities[curr->row][curr->col]->size = 1;
        upDate(possibilities, sudokuBoard, curr->row, curr->col, sudokuBoard[curr->row][curr->col], &found);


        if (curr == lst.head)
        {
            lst.head = curr->next;
            free(curr);
        }
        else
            deleteNode(saver);

        options--;
    }

    curr = lst.head;

    while (curr != NULL)
    {
        saver = curr->next;
        free(curr);
        curr = saver;
    }

    return possibilities;
}

void deleteNode(listNode* after)
{
    listNode* temp = after->next;
    after->next = temp->next;
    free(temp);
}

listNode* createNewListNode(int row, int col, listNode* next)
{
    listNode* res;
    res = (listNode*)malloc(sizeof(listNode));
    res->row = row;
    res->col = col;
    res->next = next;
    return res;
}

void insertNodeToEndList(list* lst, listNode* tail)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

bool isEmptyList(list* lst)
{
    return (lst->head == NULL);
}

void sudokoPrintBoard(short sudokuBoard[9][9])
{
    int i, j;

    printf(" |");

    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i > 0) printf("| %d", i);
        else printf(" %d", i);
    }
    printf("\n");
    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0) printf("----------------------\n");
        printf("%d", i);
        for (j = 0; j < 9; j++)
        {
            if (j % 3 == 0) printf("|");
            if (sudokuBoard[i][j] != -1) printf("% hi", sudokuBoard[i][j]);
            else printf("  ");
        }
        printf("\n");
    }
    printf("----------------------\n");
    printf("\n");
}

int removeNum(short* arr, int num, int size)
{
    int i, j, count = 0;

    for (i = 0, j = 0; i < size; i++)
    {
        if (arr[i] != num)
        {
            arr[j] = arr[i];
            j++;
        }
        else
            count++;
    }
    return count;
}

short* checkOptions(int row, int col, short sudokuBoard[][9], unsigned short* size)
{
    short* res = (short*)malloc(9 * sizeof(short));
    short* count = (short*)malloc(10 * sizeof(short));
    int rowPart, colPart, index;
    *size = 0;

    resetArray(count);

    for (int i = 0; i < 9; i++)
    {
        if (sudokuBoard[row][i] != -1)
            count[sudokuBoard[row][i]]++;

        if (sudokuBoard[i][col] != -1)
            count[sudokuBoard[i][col]]++;
    }

    rowPart = (row / 3) * 3;
    colPart = (col / 3) * 3;

    for (int i = rowPart; i < (rowPart + 3); i++)
    {
        for (int j = colPart; j < (colPart + 3); j++)
        {
            if (sudokuBoard[i][j] != -1)
                count[sudokuBoard[i][j]]++;
        }
    }

    for (int i = 1, index = 0; i < 10; i++)
    {
        if (count[i] == 0)
        {
            res[index] = i;
            (*size)++;
            index++;
        }
    }

    free(count);

    if (*size < 9)
        res = (short*)realloc(res, *size * sizeof(short));

    return res;
}

Array*** PossibleDigits(short sudokuBoard[][9])
{
    Array*** res = makeMat();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudokuBoard[i][j] != -1)
            {
                res[i][j]->arr = NULL;
                res[i][j]->size = 0;
            }

            else
            {
                res[i][j]->arr = checkOptions(i, j, sudokuBoard, &(res[i][j]->size));
            }
        }
    }
    return res;
}

void resetArray(short* arr)
{
    for (int i = 0; i < 10; i++)
        arr[i] = 0;
}

int checkFull(short board[9][9])
{
    int count = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != -1)
                count++;
        }
    }

    return count;
}

void mergeSort(playerNode** arr, int size)
{
    playerNode** tempArr = NULL;

    if (size <= 1)
        return;

    mergeSort(arr, size / 2);
    mergeSort(arr + size / 2, size - size / 2);
    tempArr = merge(arr, size / 2, arr + size / 2, size - size / 2);

    if (tempArr)
    {
        copy(arr, tempArr, size);
        free(tempArr);
    }

    else
    {
        printf("Memory allocation failure!\n");
        exit(1);
    }
}

void copy(playerNode** des, playerNode** src, int size)
{
    for (int i = 0; i < size; i++)
        des[i] = src[i];
}

playerNode** merge(playerNode** a1, int size1, playerNode** a2, int size2)
{
    int ind1, ind2, ind;
    int full1, full2;

    playerNode** res = (playerNode**)malloc((size1 + size2) * sizeof(playerNode*));

    ind1 = ind2 = ind = 0;

    while ((ind1 < size1) && (ind2 < size2))
    {
        full1 = checkFull(a1[ind1]->board);
        full2 = checkFull(a2[ind2]->board);

        if (full1 < full2)
        {
            res[ind] = a1[ind1];
            ind1++;
            ind++;
        }

        else if (full1 > full2)
        {
            res[ind] = a2[ind2];
            ind2++;
            ind++;
        }

        else
        {
            if (strcmp(a1[ind1]->name, a2[ind2]->name) > 0)
            {
                res[ind] = a1[ind1];
                ind1++;
                ind++;
            }

            else
            {
                res[ind] = a2[ind2];
                ind2++;
                ind++;
            }
        }

    }

    while (ind1 < size1)
    {
        res[ind] = a1[ind1];
        ind1++;
        ind++;
    }


    while (ind2 < size2)
    {
        res[ind] = a2[ind2];
        ind2++;
        ind++;
    }

    return res;
}

int findNewSize(int size)
{
    float res;

    res = ceil(log2(size + 1));

    res = pow(2, res);

    return (int)res - 1;
}

int upDateArr(playerNode*** arr, int size)
{
    int newsize;

    newsize = findNewSize(size);

    *arr = (playerNode**)realloc(*arr, newsize * sizeof(playerNode*));

    for (int i = size; i < newsize; i++)
    {
        (*arr)[i] = NULL;
    }

    return newsize;
}

Tree BuildTreeFromArray(playerNode** arr, int  size)
{
    Tree res;

    res.root = BuildTreeFromArrayHelper(arr, size);

    return res;
}

TreeNode* BuildTreeFromArrayHelper(playerNode** arr, int size)
{
    TreeNode* root;

    if (size == 0)
        return NULL;

    else
    {
        root = createNewTNode(arr[size / 2], NULL, NULL);
        root->left = BuildTreeFromArrayHelper(arr, size / 2);
        root->right = BuildTreeFromArrayHelper(arr + (size / 2) + 1, size - (size / 2) - 1);

        return root;
    }
}

TreeNode* createNewTNode(playerNode* data, TreeNode* left, TreeNode* right)
{
    TreeNode* res;

    res = (TreeNode*)malloc(1 * sizeof(TreeNode));
    res->player = (playerNode*)malloc(1 * sizeof(playerNode));
    res->player = data;
    res->left = left;
    res->right = right;

    return res;
}

int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
    int i, j, min = 9, notligal = 0;
    int foundOneOp = 0, found = 1;

    while (found == 1)
    {
        *x = -1; *y = -1; min = 9;
        foundOneOp = 0; found = 0;

        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                if (possibilities[i][j]->size == 1)
                {
                    board[i][j] = possibilities[i][j]->arr[0];

                    upDate(possibilities, board, i, j, possibilities[i][j]->arr[0], &foundOneOp);

                    if (foundOneOp == 1)
                        found = 1;
                }
                if (board[i][j] == -1 && possibilities[i][j]->size == 0)//legal but no options left
                {
                    return FINISH_FAILURE;
                }
                if (possibilities[i][j]->size > 1 && possibilities[i][j]->size < min)
                {
                    min = possibilities[i][j]->size;
                    (*x) = i;
                    (*y) = j;
                }
            }
        }
    }

    if (checkLigalboard(board) == false)//illigal turn
        return FINISH_FAILURE;

    if (*x == -1 && *y == -1)
        return FINISH_SUCCESS;

    return NOT_FINISH;
}

int FillBoard(short board[][9], Array*** possibilities)
{
    int res, x = -1, y = -1, check;
    short chose;

    res = OneStage(board, possibilities, &x, &y);

    while (res == NOT_FINISH && res != FINISH_FAILURE)
    {
        sudokoPrintBoard(board);
        printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);

        for (int i = 0; i < possibilities[x][y]->size; i++)
            printf("%d. %d \n", i + 1, possibilities[x][y]->arr[i]);

        printf("\n");
        scanf("%hi", &chose);
        printf("Updating cell %d with value %d\n\n", ((x*9)+y), chose);

        board[x][y] = chose;

        upDate(possibilities, board, x, y, chose, &check);

        possibilities[x][y]->size = 0;
        free(possibilities[x][y]->arr);
        possibilities[x][y]->arr = NULL;

        res = OneStage(board, possibilities, &x, &y);
    }

    //res is not NOT_FINISH anymore it can be only FINISH_FAILURE or FINISH_SUCCESS
    if (res == FINISH_SUCCESS)
        return FILLED;

    else//FINISH_FAILURE
    {
        printf("User's selections led to duplications\n\n");
        return FAIL;
    }
}

bool checkLigalboard(short sudokuBoard[][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (checkLigalrow(sudokuBoard, i) == false)
                return false;

            if (checkLigalcol(sudokuBoard, j) == false)
                return false;

            if (checkLigalSquare(sudokuBoard, i, j) == false)
                return false;
        }
    }
    return true;
}

bool checkLigalrow(short sudokuBoard[][9], int row)
{
    short* count = (short*)malloc(10 * sizeof(short));

    resetArray(count);

    for (int i = 0; i < 9; i++)
    {
        if (sudokuBoard[row][i] != -1)
        {
            count[sudokuBoard[row][i]]++;

            if (count[sudokuBoard[row][i]] > 1)
            {
                return false;
            }
        }

    }

    free(count);

    return true;
}

bool checkLigalcol(short sudokuBoard[][9], int col)
{
    short* count = (short*)malloc(10 * sizeof(short));

    resetArray(count);

    for (int i = 0; i < 9; i++)
    {
        if (sudokuBoard[i][col] != -1)
        {
            count[sudokuBoard[i][col]]++;

            if (count[sudokuBoard[i][col]] > 1)
            {
                return false;
            }
        }
    }

    free(count);

    return true;
}

bool checkLigalSquare(short sudokuBoard[][9], int row, int col)
{
    int rowPart, colPart;

    short* count = (short*)malloc(10 * sizeof(short));

    resetArray(count);

    rowPart = (row / 3) * 3;
    colPart = (col / 3) * 3;

    for (int i = rowPart; i < (rowPart + 3); i++)
    {
        for (int j = colPart; j < (colPart + 3); j++)
        {
            if (sudokuBoard[i][j] != -1)
            {
                count[sudokuBoard[i][j]]++;

                if (count[sudokuBoard[i][j]] > 1)
                {
                    return false;
                }
            }
        }
    }

    free(count);

    return true;
}

void freeTree(Tree* tr)
{
    freeTreeHelper(tr->root);
    tr->root = NULL;
}

void freeTreeHelper(TreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeHelper(root->left);
        freeTreeHelper(root->right);
        free(root);
    }
}