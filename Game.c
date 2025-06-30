#include "Game.h"
#include "DarkMode.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

void printGameObjects(Array *gameArray, Position *P)
{
    int i;
    int j;
    system("clear");
    /*print map top boarder*/
    printf("**");
    for(i=0; i<P->Col; i++)
    {
        printf("*");
    }
    printf("\n");

    for(i=0; i<P->Row; i++)
    {
        printf("*"); /*print the left boarder*/
        for(j=0; j<P->Col; j++)
        {
            #ifdef DARK_MODE
            if(HasLantern(P))
            {
                if(CalcManhattanDistance(P->CurrentPlayerRow,P->CurrentPlayerCol,i,j)>7)
                {
                    printf(" ");
                }

                else
                {
                    if(gameArray->Arr[i][j]==6)
                    {
                        printf(".");
                    }

                    else if(gameArray->Arr[i][j]==1)
                    {
                        printf("O");
                    }

                    else if(gameArray->Arr[i][j]==2)
                    {
                        printf("@");
                    }

                    else if(gameArray->Arr[i][j]==3)
                    {
                        printf("P");
                    }

                    else if(gameArray->Arr[i][j]==4)
                    {
                        printf("~");
                    }

                    else if(gameArray->Arr[i][j]==5)
                    {
                        printf("$");
                    }

                    else
                    {
                        printf(" ");
                    }
                }
            }

            else
            {
                if(CalcManhattanDistance(P->CurrentPlayerRow,P->CurrentPlayerCol,i,j)>3)
                {
                    printf(" ");
                }

                else
                {
                    if(gameArray->Arr[i][j]==6)
                    {
                        printf(".");
                    }

                    else if(gameArray->Arr[i][j]==1)
                    {
                        printf("O");
                    }

                    else if(gameArray->Arr[i][j]==2)
                    {
                        printf("@");
                    }

                    else if(gameArray->Arr[i][j]==3)
                    {
                        printf("P");
                    }

                    else if(gameArray->Arr[i][j]==4)
                    {
                        printf("~");
                    }

                    else if(gameArray->Arr[i][j]==5)
                    {
                        printf("$");
                    }

                    else
                    {
                        printf(" ");
                    }
                }
            }
            #else
            if(gameArray->Arr[i][j]==0)
            {
                printf(" ");
            }

            else if(gameArray->Arr[i][j]==1)
            {
                printf("O");
            }

            else if(gameArray->Arr[i][j]==2)
            {
                printf("@");
                P->CurrentLanternRow=i;
                P->CurrentLanternCol=j;
            }

            else if(gameArray->Arr[i][j]==3)
            {
                printf("P");
                P->CurrentPlayerRow=i;
                P->CurrentPlayerCol=j;
            }

            else if(gameArray->Arr[i][j]==4)
            {
                printf("~");
                P->CurrentSnakeRow=i;
                P->CurrentSnakeCol=j;
            }

            else if(gameArray->Arr[i][j]==5)
            {
                printf("$");
                P->CurrentTreasureRow=i;
                P->CurrentTreasureCol=j;
            }

            else if(gameArray->Arr[i][j]==6)
            {
                printf(".");
            }
            #endif
        }
        printf("*"); /*print the right boarder*/
        printf("\n");
    }

    /*print the bottom map boarder*/
    printf("**");
    for(i=0; i<P->Col; i++)
    {
        printf("*");
    }
    printf("\n");

    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("Press u to undo\n");
}

void disableBuffer() /*To receive user input without pressing enter*/
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer() /*To recieve user input without pressing enter*/
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void PlayerMovement(char Move, Position *P, Array *gameArray, LinkedList *myList)
{
	int **Arr=gameArray->Arr;
	int NewRow=P->CurrentPlayerRow;
	int NewCol=P->CurrentPlayerCol;
    int initialRow=P->CurrentPlayerRow;
    int initialCol=P->CurrentPlayerCol;
    Position *newPlayerPosition=(Position *)malloc(sizeof(Position));
    
    *newPlayerPosition=*P;
    InsertFirst(myList,newPlayerPosition);
    switch(Move)
	{
		case 'w': /*Moves up*/
		{
			if(NewRow-1 >=0 && NewRow-1<P->Row && Arr[NewRow-1][NewCol] !=1) /*ensure that the NewRow index is within the boundary and player does not hit the wall*/
			{
				NewRow=NewRow-1;
			}
			break;
		}
		
		case 's': /*Move down*/
		{
			if(NewRow+1>=0 && NewRow+1<P->Row && Arr[NewRow+1][NewCol]!=1)
			{
				NewRow=NewRow+1;
			}
			break;
		}
		
		case 'a': /*Moves left*/
		{
			if(NewCol-1>=0 && NewCol-1<P->Col && Arr[NewRow][NewCol-1]!=1)
			{
				NewCol=NewCol-1;
			}
			break;
		}
		
		case 'd': /*Moves right*/
		{
			if(NewCol+1>=0 && NewCol+1<P->Col && Arr[NewRow][NewCol+1]!=1)
			{
				NewCol=NewCol+1;
			}
			break;
		}

        default:
        {
            break;
        }
	}

    if(initialRow == NewRow && initialCol == NewCol) 
    {
        P->PlayerStationary=1; /*Player is stational since the initial position equals to new position*/
    }

    else
    {
        P->PlayerStationary=0; /*Not stationary*/
        Arr[initialRow][initialCol]=0; /*set the previous position to empty*/
        gameArray->Arr[initialRow][initialCol]=0;
        if(NewRow>=0 && NewRow<P->Row && NewCol>=0 && NewCol<P->Col)
        {
        P->CurrentPlayerRow=NewRow; /*Assign the prevrow to the newrow*/
        P->CurrentPlayerCol=NewCol; /*Assign the prevcol to the newcol*/
        Arr[NewRow][NewCol]=3; /*Set the new player position*/
        gameArray->Arr[NewRow][NewCol]=3;
        }
    }
}

int PlayerStatus(Position *P, Array *gameArray, int status)
{
    int Row=P->CurrentPlayerRow;
    int Col=P->CurrentPlayerCol;
    int **Arr=gameArray->Arr;
    if(Arr[Row][Col]==Arr[P->CurrentTreasureRow][P->CurrentTreasureCol])
    {
        status=2; /*Win*/
    }

    else if(P->CurrentSnakeRow==P->CurrentPlayerRow && P->CurrentSnakeCol==P->CurrentPlayerCol) /*Eaten by snake*/
    {
        status=1; /*Lose*/
    }

    else
    {
        status=0;
    }
    return status;
}

int PlayerOneGridAwaySnake(Position *P)
{
    int OneGridAway=0; /*Initialize to false*/
    int DifferenceinRow=abs(P->CurrentSnakeRow-P->CurrentPlayerRow); /*Calculate the distance between snake and player on horizontal*/
    int DifferenceinCol=abs(P->CurrentPlayerCol-P->CurrentSnakeCol); /*Calculate the distance between snake and player vertically*/
    if(DifferenceinCol==1 && DifferenceinRow==1) /*One row and one col away*/
    {
        OneGridAway=1;
    }

    else if(DifferenceinCol==1 && DifferenceinRow==0) /*Same row and one col away*/
    {
        OneGridAway=1;
    }

    else if(DifferenceinCol==0 && DifferenceinRow==1) /*Same col and one row away*/
    {
        OneGridAway=1;
    }
    return OneGridAway;
}

void RamdomSnakeMovement(Position *P, Array *gameArray, LinkedList *myList)
{
    int NewRow;
    int NewCol;
    int **Arr=gameArray->Arr;
    int RandomNum;
    Position *newSnakePosition=(Position *)malloc(sizeof(Position));
    *newSnakePosition=*P;
    InsertFirst(myList, newSnakePosition); /*Insert the snake state into the list*/
    if(!P->PlayerStationary)
    {
        if(!PlayerOneGridAwaySnake(P)) /*If player not one grid away, move the snake randomly*/
        {
        do
        {
            do
            {
                NewRow=P->CurrentSnakeRow;
                NewCol=P->CurrentSnakeCol;
                RandomNum=randomUCP(1,8); /*Randomly generate a number from 1 to 8 inclusively*/
                switch(RandomNum)
                {
                    case 1:  /*Snake move up*/
                    {
                        NewRow=NewRow-1;
                        break;
                    }

                    case 2: /*Snake move down*/
                    {
                        NewRow=NewRow+1;
                        break;
                    }

                    case 3: /*Snake move left*/
                    {
                        NewCol=NewCol-1;
                        break;
                    }

                    case 4: /*Snake move right*/
                    {
                        NewCol=NewCol+1;
                        break;
                    }

                    case 5: /*Snake move diagonally left up Col-1 and Row-1*/
                    {
                        NewCol=NewCol-1;
                        NewRow=NewRow-1;
                        break;
                    }

                    case 6: /*Snake move diagonally right up Col+1 and Row-1*/
                    {
                        NewCol=NewCol+1;
                        NewRow=NewRow-1;
                        break;
                    }

                    case 7: /*Snake moves diagonally left down Row+1 and Col-1*/
                    {
                        NewCol=NewCol-1;
                        NewRow=NewRow+1;
                        break;
                    }

                    default: /*Snake moves diagonally right down row +1 and col+1*/
                    {
                        NewCol=NewCol+1;
                        NewRow=NewRow+1;
                        break;
                    }
                }
            }while(!CheckSnakeWithinBoundary(NewRow, NewCol, P) ); /*Not within the boundary*/
        }while(CheckSnakeHitWall(NewRow, NewCol, gameArray) ); /*Has hit the wall*/
        Arr[P->CurrentSnakeRow][P->CurrentSnakeCol]=0; /*Clear the previous snake position*/
        P->CurrentSnakeRow=NewRow;
        P->CurrentSnakeCol=NewCol;
        Arr[NewRow][NewCol]=4; /*Update the current snake position*/
        }

        else
        {
            /*Snake eat the player*/
            Arr[P->CurrentSnakeRow][P->CurrentSnakeCol]=0; /*Clear the previous snake position*/
            P->CurrentSnakeRow=P->CurrentPlayerRow; 
            P->CurrentSnakeCol=P->CurrentPlayerCol;
            Arr[P->CurrentSnakeRow][P->CurrentSnakeCol]=4; /*Update the snake new position*/
        }
    }
}

int CheckSnakeWithinBoundary(int NewRow, int NewCol, Position *P)
{
    int False=0; 
    int True=1;
    int Check=False; /*Initialize to False*/
    if(NewRow>=0 && NewRow<P->Row && NewCol>=0 && NewCol<P->Col) /*out of map boarder*/
    {
        Check=True;   
    }
    return Check;
}

int CheckSnakeHitWall(int NewRow, int NewCol, Array *gameArray)
{
    int **Arr=gameArray->Arr;
    int False=0; 
    int True=1;
    int Check=False; /*Initialize to False*/
    if(Arr[NewRow][NewCol]==1) /*Hits the wall*/
    {
        Check=True;
    }
    return Check;
}

void initRandom() /*For the snake random movement*/
{
    srand(time(NULL));
}

int randomUCP(int low, int high) /*For the snake random movement*/
{
    int number = -1;

    if(low <= high)
    {
        number = (rand() % (high-low+1)) + low;
    }
    return number;
}

void GamePlay(Position *P, Array *gameArray)
{
    char Move;
    int Status=0; /*Winning status is 2, Losing is 1, 0 is no win no lose*/
    /*int HasUndoBefore;*/
    LinkedList *PlayerMovementList;
    LinkedList *SnakeMovementList;
    PlayerMovementList=CreateEmptyList(); /*Create a linked list to store the movement of player*/
    SnakeMovementList=CreateEmptyList(); /*Create a linked list to store the movement of snake*/
    do
    {
        do /*Recieving user input without pressing enter key*/
        {
            disableBuffer();
            scanf(" %c", &Move);
            enableBuffer();
        }while(Move != 'w' && Move !='a' && Move!='s' && Move !='d' && Move !='u');

        if(Move=='u')
        {
            UndoFeature(PlayerMovementList, SnakeMovementList, P, gameArray);
            printGameObjects(gameArray, P);
            /*HasUndoBefore=1;*/
        }

        else
        {
	    PlayerMovement(Move, P, gameArray, PlayerMovementList);
        RamdomSnakeMovement(P, gameArray, SnakeMovementList);
        Status=PlayerStatus(P, gameArray, Status);
        #ifdef DARK_MODE
        UpdateGame(P, gameArray);
        #endif
	    printGameObjects(gameArray, P);
        switch(Status)
        {
            case 1:
                printf("You lose.\n");
                break;

            case 2:
                printf("You win\n");
                break;

            default:
                break;
        }
        }
    }while(Status ==0); /*No win no lose*/
    FreeLinkedList(PlayerMovementList,SnakeMovementList); /*Free the linked list*/
    free(PlayerMovementList);
    free(SnakeMovementList);
}

void UndoFeature(LinkedList *PlayerMovementList, LinkedList *SnakeMovementList, Position *P, Array *gameArray)
{
    ListNode *PlayerNode;
    ListNode *SnakeNode;
    Position *newPlayerPosition;
    Position *newSnakePosition;
    int **Arr=gameArray->Arr;
    if(!isEmpty(PlayerMovementList) && !isEmpty(SnakeMovementList))
    {
        if(CountNode(SnakeMovementList)>1 && CountNode(PlayerMovementList)>1)
        {
            RemoveFirst(PlayerMovementList);
            RemoveFirst(SnakeMovementList);
        }
        PlayerNode=PeekFirst(PlayerMovementList);
        SnakeNode=PeekFirst(SnakeMovementList);
        
        if(PlayerNode !=NULL && SnakeNode !=NULL)
        {
            newPlayerPosition=PlayerNode->Data;
            newSnakePosition=SnakeNode->Data;
            /*Updating the current player position to the removed position*/
            Arr[P->CurrentPlayerRow][P->CurrentPlayerCol]=0; /*Remove the previous position*/
            P->CurrentPlayerRow=newPlayerPosition->CurrentPlayerRow;
            P->CurrentPlayerCol=newPlayerPosition->CurrentPlayerCol;
            Arr[P->CurrentPlayerRow][P->CurrentPlayerCol]=3; /*Update the new position of Player*/

            /*Updating the current snake position to the removed position*/
            Arr[P->CurrentSnakeRow][P->CurrentSnakeCol]=0; /*Remove the previous position*/
            P->CurrentSnakeRow=newSnakePosition->CurrentSnakeRow;
            P->CurrentSnakeCol=newSnakePosition->CurrentSnakeCol;
            Arr[P->CurrentSnakeRow][P->CurrentSnakeCol]=4; /*Update the new position of Snake*/
        }
    }
}

LinkedList *CreateEmptyList()
{
    LinkedList *list=(LinkedList *)malloc(sizeof(LinkedList)); /*Dynamically allocated memory for Linkedlist*/
    if(list !=NULL) /*Check if the memory is successfully allocated*/
    {
        list->Head=NULL; /*Set head to null initially*/
    }
    return list; /*Return a pointer to the calling function*/
}

ListNode *PeekFirst(LinkedList *List)
{
    return (List->Head);
}

void InsertFirst(LinkedList *List, void *Data)
{
    ListNode *newNode=(ListNode *)malloc(sizeof(ListNode)); /*Memory allocated for new node*/
    if(newNode !=NULL) /*Check whether memory has been successfully allocated*/
    {
        newNode->Data=Data; /*sets the Data to points to the Value*/
        if(isEmpty(List))
        {
            List->Head=newNode; /*Points the head to the newNode*/
            newNode->Next=NULL; /*Point the newNode next to null*/
        }

        else
        {
            newNode->Next=List->Head; /*Set the next of the newNode to the current head*/
            List->Head=newNode; /*Update the head to the newNode*/
        }
    }
}

int CountNode(LinkedList *List)
{
    int Count=0;
    ListNode *CurrentNode=List->Head;
    while(CurrentNode!=NULL)
    {
        Count++;
        CurrentNode=CurrentNode->Next;
    }
    return Count;
}

void *RemoveFirst(LinkedList *List)
{
    void *DeletedData=NULL;
    if(!isEmpty(List)) /*Ensure the list is not empty*/
    {
        ListNode *nodeToDelete=List->Head; /*Pointer to the node to be deleted*/
        DeletedData=nodeToDelete->Data; /*Retrieve stored data of the deleted node*/
        List->Head=List->Head->Next; /*Update the head pointer to the next node*/
        free(nodeToDelete); /*free memory allocated for deleted node*/
        free(DeletedData); /*free memory allocated for deleted data*/
    }
    return DeletedData; 
}

int isEmpty(LinkedList *List)
{
    int Empty=0; /*Initialize to false*/
    if(List->Head == NULL) /*Empty*/
    {
        Empty=1; /*Set to true*/
    }
    return Empty;
}

void FreeLinkedList(LinkedList *PlayerMovementList, LinkedList *SnakeMovementList)
{
    Position *PlayerData;
    Position *SnakeData;
    ListNode *PlayerCurrentNode=PlayerMovementList->Head;
    ListNode *SnakeCurrentNode=SnakeMovementList->Head;
    ListNode *PlayerNextNode;
    ListNode *SnakeNextNode;
    while(PlayerCurrentNode!=NULL)
    {
        PlayerNextNode=PlayerCurrentNode->Next;
        PlayerData=PlayerCurrentNode->Data;
        free(PlayerCurrentNode);
        free(PlayerData);
        PlayerCurrentNode=PlayerNextNode;
    }

    while(SnakeCurrentNode!=NULL)
    {
        SnakeNextNode=SnakeCurrentNode->Next;
        SnakeData=SnakeCurrentNode->Data;
        free(SnakeCurrentNode);
        free(SnakeData);
        SnakeCurrentNode=SnakeNextNode;
    }
    free(PlayerMovementList);
    free(SnakeMovementList);
}




