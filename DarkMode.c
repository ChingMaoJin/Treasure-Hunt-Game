#include "DarkMode.h"
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>

int CalcManhattanDistance(int PlayerRow, int PlayerCol, int ObjectRow, int ObjectCol) /*For dark mode*/
{
    return abs(PlayerRow-ObjectRow) + abs(PlayerCol-ObjectCol);
}

int HasLantern(Position *P) /*For dark mode*/
{
    return P->LanternCollected;
}

void UpdateGame(Position *P, Array *gameArray) /*For dark mode*/
{
    int Default_Visibility = 3;
    int Extended_Visibility = 7;
    int i, j;
    int visibilityRange;
    int **Arr=gameArray->Arr;
    /*Check if the player is on the lantern position, and if so, pick it up*/
    if (P->CurrentPlayerRow == P->CurrentLanternRow && P->CurrentPlayerCol == P->CurrentLanternCol)
    {
        P->LanternCollected = 1;  /*Player picks up the lantern*/
    }

    /*Check if the player has picked the lantern. If true use extended visibility, if false use default visibility*/
    visibilityRange = HasLantern(P) ? Extended_Visibility : Default_Visibility; /*Conditional operator*/

    /*Update the visibility in the game based on the current visibility range*/
    for (i = 0; i < P->Row; i++)
    {
        for (j = 0; j < P->Col; j++)
        {
            if (CalcManhattanDistance(P->CurrentPlayerRow, P->CurrentPlayerCol, i, j) < visibilityRange)
            {
                if (Arr[i][j] == 0)
                {
                    gameArray->Arr[i][j]=6;  /*To print . when it is empty*/
                }

                else if(Arr[i][j]==1)
                {
                    gameArray->Arr[i][j]=1;
                }

                else if(Arr[i][j]==2)
                {
                    gameArray->Arr[i][j]=2;
                }

                else if(Arr[i][j]==3)
                {
                    gameArray->Arr[i][j]=3;
                }

                else if(Arr[i][j]==4)
                {
                    gameArray->Arr[i][j]=4;
                }

                else if(Arr[i][j]==5)
                {
                    gameArray->Arr[i][j]=5;
                }

                else if(Arr[i][j]==6)
                {
                    gameArray->Arr[i][j]=6;
                }

                else
                {
                    printf("Invalid");
                }
            }
        }
    }
}