#ifndef Game_H
#define Game_H
typedef struct
{
    int CurrentPlayerRow;
    int CurrentPlayerCol;
    int CurrentSnakeRow;
    int CurrentSnakeCol;
    int CurrentTreasureRow;
    int CurrentTreasureCol;
    int CurrentLanternRow;
    int CurrentLanternCol;
    int CurrentWallRow;
    int CurrentWallCol;
    int Row; /*Num of row in the map*/
    int Col; /*Num of col in the map*/
    int PlayerStationary;
    int LanternCollected;
}Position;

typedef struct
{
    int **Arr;
}Array;

typedef struct ListNode
{
    void *Data; /*generic pointer to hold any data type*/
    struct ListNode *Next; /*a pointer of the listnode that points to the next node*/
}ListNode;

typedef struct LinkedList
{
    struct ListNode *Head; /*a pointer that points to the node of the start of the list*/
}LinkedList;

LinkedList *CreateEmptyList();
int isEmpty(LinkedList *List);
void InsertFirst(LinkedList *List, void *Data);
void *RemoveFirst(LinkedList *List);
void FreeLinkedList(LinkedList *PlayerMovementList, LinkedList *SnakeMovementList);
ListNode *PeekFirst(LinkedList *List);
int CountNode(LinkedList *List);
void UndoFeature(LinkedList *PlayerMovementList, LinkedList *SnakeMovementList, Position *P, Array *gameArray);
void initRandom();/*Random snake movement*/
int randomUCP(int low, int high); /*Random snake movement*/
void disableBuffer(); /*Take char immediately*/
void enableBuffer(); /*Take char immediately*/
void printGameObjects(Array *gameArray, Position *P);
void PlayerMovement(char Move, Position *P, Array *gameArray, LinkedList *myList);
void GamePlay(Position *P, Array *gameArray);
int CheckSnakeHitWall(int NewRow, int NewCol, Array *gameArray);
int CheckSnakeWithinBoundary(int NewRow, int NewCol, Position *P);
int PlayerOneGridAwaySnake(Position *P);
void RamdomSnakeMovement(Position *P, Array *gameArray, LinkedList *myList);
void UndoFeature(LinkedList *PlayerMovementList, LinkedList *SnakeMovementList, Position *P, Array *gameArray);

#endif