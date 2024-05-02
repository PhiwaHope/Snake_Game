#include "Game.h"

namespace GameSpace
{
    //A function to generate random numbers
    int getRand(int intLow, int intHigh)
    {
        assert(intHigh>intLow);
        int range = intHigh-intLow+1;
        return rand()%range+intLow;
    }
    //Allocating memory
    TwoDArray allocMem(int intRows, int intCols)
    {
        TwoDArray arrWorld;
        arrWorld = new OneDArray[intRows];
        for(int r=0; r<intRows; r++)
        {
            arrWorld[r] = new int[intCols];
            for(int c=0; c<intCols; c++)
            {
                arrWorld[r][c] = EMPTY;
            }
        }
        return arrWorld;
    }

    //A function to place boders
    void PlaceBoders(tWorld& stcWorld)
    {
        //TOP
        for(int c=0; c<stcWorld.intCols; c++)
        {
            stcWorld.arrWorld[0][c] = BODER;
        }
        //BOTTOM
        for(int c=0; c<stcWorld.intCols; c++)
        {
            stcWorld.arrWorld[stcWorld.intRows-1][c] = BODER;
        }
        //Left
        for(int r=0; r<stcWorld.intRows; r++)
        {
            stcWorld.arrWorld[r][0] = BODER;
        }
        //RIGHT
        for(int r=0; r<stcWorld.intRows; r++)
        {
            stcWorld.arrWorld[r][stcWorld.intCols-1] = BODER;
        }
    }

    //Initializing the world
    tWorld initWorld(int intRows, int intCols, int score)
    {
        tWorld stcWorld;
        stcWorld.arrWorld = allocMem(intRows, intCols);
        stcWorld.intRows = intRows;
        stcWorld.intCols = intCols;
        stcWorld.intHRow = stcWorld.intRows/2;
        stcWorld.intHCol = stcWorld.intCols/2;
        stcWorld.arrWorld[stcWorld.intHRow][stcWorld.intHCol] = HEAD;    //Placing the player
        stcWorld.intTRow = stcWorld.intHRow;
        stcWorld.intTCol = stcWorld.intHCol;
        stcWorld.intCount = 0;
        stcWorld.TailLeangth = 0;
        stcWorld.intScore = score;
        stcWorld.Placed = false;
        stcWorld.Tailx = new int[100];
        stcWorld.TailY = new int[100];
        stcWorld.Tail2x = new int[100];
        stcWorld.Tail2Y = new int[100];
        stcWorld.enStatus = RUNNING;
        PlaceBoders(stcWorld);    //Placing boders
        PlaceFruit(stcWorld);    //Placing the fruit
        return stcWorld;
    }

    //A function to place the fruit
    void PlaceFruit(tWorld& stcWorld)
    {
        int intRow = getRand(1, stcWorld.intRows-2);
        int intCol = getRand(1, stcWorld.intCols-2);
        while(stcWorld.arrWorld[intRow][intCol] != EMPTY)
        {
            intRow = getRand(1, stcWorld.intRows-2);
            intCol = getRand(1, stcWorld.intCols-2);
        }
        stcWorld.arrWorld[intRow][intCol] = FRUIT;

        stcWorld.TailLeangth++;
    }

    //Move player
    void MovePlayer(tWorld& stcWorld, int intDirection, int Level)
{
        if(stcWorld.Placed == true && stcWorld.intCount >= 40)
        {
            stcWorld.arrWorld[stcWorld.intFRow][stcWorld.intFCol] = EMPTY;
            stcWorld.Placed = false;
            stcWorld.intCount = 0;
        }
        if(stcWorld.Placed == true && stcWorld.intCount < 40)
        {
            stcWorld.intCount++;
        }

    int intDRow = stcWorld.intHRow;
    int intDCol = stcWorld.intHCol;

    switch(intDirection)
    {
        case UP:
            intDRow--;
            break;
        case DOWN:
            intDRow++;
            break;
        case LEFT:
            intDCol--;
            break;
        case RIGHT:
            intDCol++;
            break;
    }

    if(stcWorld.arrWorld[intDRow][intDCol] == TAIL)
    {
        stcWorld.enStatus = LOST;
    }
        // Update the player's position if it's a valid move
    if (stcWorld.arrWorld[intDRow][intDCol] != BODER)
    {
        IsFruit(stcWorld, intDRow, intDCol);

        // Update the new head position in the world array
        stcWorld.arrWorld[intDRow][intDCol] = HEAD;
        MoveTail(stcWorld, intDRow, intDCol);
    }
    else
    {
        if(Level == 1)
        {
            if(intDCol>=stcWorld.intCols-1)
            {
                IsFruit(stcWorld, intDRow, 1);
                stcWorld.arrWorld[intDRow][1] = HEAD;
                MoveTail(stcWorld, intDRow, 1);
            }
            if(intDCol<=0)
            {
                IsFruit(stcWorld, intDRow, stcWorld.intCols-2);
                stcWorld.arrWorld[intDRow][stcWorld.intCols-2] = HEAD;
                MoveTail(stcWorld, intDRow, stcWorld.intCols-2);
            }
            if(intDRow>=stcWorld.intRows-1)
            {
                IsFruit(stcWorld, 1, intDCol);
                stcWorld.arrWorld[1][intDCol] = HEAD;
                MoveTail(stcWorld, 1, intDCol);
            }
            if(intDRow<=0)
            {
                IsFruit(stcWorld, stcWorld.intRows-2, intDCol);
                stcWorld.arrWorld[stcWorld.intRows-2][intDCol] = HEAD;
                MoveTail(stcWorld, stcWorld.intRows-2, intDCol);
            }
        }
        if(Level == 2)
        {
            stcWorld.enStatus = LOST;
        }

    }
}

    //Place the big fruit
     void IsFruit(tWorld& stcWorld, int Row, int Col)
     {
         if(stcWorld.arrWorld[Row][Col] == FRUIT)
         {
            PlaceFruit(stcWorld);
            PlaceBFreuit(stcWorld);
            stcWorld.intScore = 10;
         }
         if(stcWorld.arrWorld[Row][Col] == BIG_FRUIT)
         {
            stcWorld.intScore = 50;
            stcWorld.Placed = false;
         }
         if(stcWorld.arrWorld[Row][Col] == EMPTY)
         {
            stcWorld.intScore = 0;
         }
     }

    //Display
    void DisplayWorld(tWorld& stcWorld, int Score, int HS)
    {
        system("cls");
        stcWorld.arrWorld[0][0] = BODER;
        for(int r=0; r<stcWorld.intRows; r++)
        {
            for(int c=0; c<stcWorld.intCols; c++)
            {
                int intFeature = stcWorld.arrWorld[r][c];
                cout << chFeature[intFeature] <<" ";
            }
            cout << endl;
        }
        cout <<"SCORE: "<< Score <<endl;
        cout << "High score: " << HS << endl;
    }

    void MoveTail(tWorld& stcWorld, int intDRow, int intDCol)
    {
        // Update the head position
        stcWorld.Tail2x[1] = stcWorld.intHRow;
        stcWorld.Tail2Y[1] = stcWorld.intHCol;

        stcWorld.intHRow = intDRow;
        stcWorld.intHCol = intDCol;

        int PrevX = -1;
        int PrevY = -1;

        for(int i = 1; i<= stcWorld.TailLeangth; i++)
        {
            PrevX = stcWorld.Tailx[i];
            PrevY = stcWorld.TailY[i];
            stcWorld.Tail2x[i+1] = PrevX;
            stcWorld.Tail2Y[i+1] = PrevY;
        }

        for(int i = 1; i<= stcWorld.TailLeangth+1; i++)
        {
            stcWorld.Tailx[i] = stcWorld.Tail2x[i];
            stcWorld.TailY[i] = stcWorld.Tail2Y[i];

           if(i <= stcWorld.TailLeangth)
           {
               stcWorld.arrWorld[stcWorld.Tailx[i]][stcWorld.TailY[i]] = TAIL;
           }
           if(i == stcWorld.TailLeangth+1)
           {
               stcWorld.arrWorld[stcWorld.Tailx[i]][stcWorld.TailY[i]] = EMPTY;
           }

        }
    }

    //Placing a big fruit according to the odds
    void PlaceBFreuit(tWorld& stcWorld)
    {
        if(!(stcWorld.Placed))
        {
            int Chance = getRand(0, 100);
            if(Chance <= 20)
            {
                stcWorld.intFRow = getRand(1, stcWorld.intRows-2);
                stcWorld.intFCol = getRand(1, stcWorld.intCols-2);
                while(stcWorld.arrWorld[stcWorld.intFRow][stcWorld.intFCol] != EMPTY)
                {
                    stcWorld.intFRow = getRand(1, stcWorld.intRows-2);
                    stcWorld.intFCol = getRand(1, stcWorld.intCols-2);
                }
                stcWorld.arrWorld[stcWorld.intFRow][stcWorld.intFCol] = BIG_FRUIT;
                stcWorld.Placed = true;
            }
        }


    }

    void DeallocMem(TwoDArray& arrWorld, int intRows)
    {
        for(int r=0; r<intRows; r++)
        {
            delete [] arrWorld[r];
        }
        delete arrWorld;

        arrWorld = nullptr;
    }
}
