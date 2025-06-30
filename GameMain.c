#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "DarkMode.h"

int main(int argc, char **argv)
{
    char *FileName;
    FILE *fptr;
    int Row, Col, NumOfWalls;
    int **Arr;
    Position *gameposition;
    Array *gameArray;
    int i, j;
    gameposition=(Position *)malloc(sizeof(Position)); /*Memory allocation for game position */
    gameArray=(Array *)malloc(sizeof(Array)); /*Memory allocation for game array*/

    if(argc !=2) /*check if the arguement is correct*/
    {
        printf("Please enter one more arguement");
        free(gameposition);
        free(gameArray);
    }

    else
    {
        FileName=argv[1];
        fptr=fopen(FileName, "r");
        
        /*Check if the file is successfully opened*/
        if(fptr ==NULL)
        {
            perror("Error in opening the file"); 
            free(gameArray);
            free(gameposition); 
        }

        else
        {
            fscanf(fptr, "%d %d", &Row, &Col); /*Read the first row which consists of the row number and col number*/
            fscanf(fptr, "%d", &NumOfWalls); /*Read the second row which is the number of walls*/
            gameposition->Row=Row; /*Access the member variable through the pointer of the struct*/
            gameposition->Col=Col; 
            Arr=(int **)malloc(Row *sizeof(int*)); /*memory allocation*/
            for(i=0; i<Row; i++)
            {
                Arr[i]=(int *)malloc(Col *sizeof(int)); /*memory allocation for each row*/
            }

            /*Reading the file*/
            for(i=0; i<Row; i++)
            {
                for(j=0; j<Col; j++)
                {
                    fscanf(fptr, "%d ", &Arr[i][j]);
                    if(Arr[i][j]==1)
                    {
                        gameposition->CurrentWallRow=i;
                        gameposition->CurrentWallCol=j;
                    }
                    if(Arr[i][j]==2)
                    {
                        gameposition->CurrentLanternRow=i;
                        gameposition->CurrentLanternCol=j;
                    }

                    else if(Arr[i][j]==3)
                    {
                        gameposition->CurrentPlayerRow=i;
                        gameposition->CurrentPlayerCol=j;
                    }
                    
                    else if(Arr[i][j]==4)
                    {
                        gameposition->CurrentSnakeRow=i;
                        gameposition->CurrentSnakeCol=j;
                    }

                    else if(Arr[i][j]==5)
                    {
                        gameposition->CurrentTreasureRow=i;
                        gameposition->CurrentTreasureCol=j;
                    }
                }
            }
            gameArray->Arr=Arr;
            for(i=0; i<gameposition->Row; i++)
            {
                for(j=0; j<gameposition->Col;j++)
                {
                    printf("%d ",gameArray->Arr[i][j]);
                }
                printf("\n");
            }
            
            #ifdef DARK_MODE
                UpdateGame(gameposition, gameArray);
                printGameObjects(gameArray, gameposition);
            #else
                printGameObjects(gameArray, gameposition);
            #endif
            GamePlay(gameposition, gameArray);
        }
        /*free memory allocation*/
        for(i=0; i<Row; i++)
        {
            free(Arr[i]);
        }
        free(Arr); 
        fclose(fptr);  
    }
    return 0;
}