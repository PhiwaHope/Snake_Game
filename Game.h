#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <ctype.h>
#include <cassert>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h>


using namespace std;
namespace GameSpace
{
    enum errReturns
    {
        SUCCESS,
        ERR_ARGC,
        ERR_INPUT
    };

    enum Directions
    {
        STOP,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum Features
    {
        EMPTY,
        BODER,
        FRUIT,
        HEAD,
        TAIL,
        BIG_FRUIT
    };

    enum status
    {
        RUNNING,
        WON,
        LOST,
    };

    const char chFeature[] = {' ','#','*', 'O', 'o', '@'};

    typedef int* OneDArray;
    typedef int** TwoDArray;

    struct tWorld
    {
        TwoDArray arrWorld;
        int intRows;
        int intCols;
        int intHRow;
        int intHCol;
        int intFRow;
        int intFCol;
        int intTRow;
        int intTCol;
        int intCount;
        int TailLeangth;
        int intScore;
        int enStatus;
        bool Placed;
        OneDArray Tailx;
        OneDArray TailY;
        OneDArray Tail2x;
        OneDArray Tail2Y;
    };

    tWorld initWorld(int intRows, int intCols, int Score);
    TwoDArray allocMem(int intRows, int intCols);
    int getRand(int intLow, int intHigh);
    void PlaceBoders(tWorld& stcWorld);
    void DisplayWorld(tWorld& stcWorld, int Score, int HS);
    void PlaceFruit(tWorld& stcWorld);
    void MovePlayer(tWorld& stcWorld, int intDirection, int Level);
    void DeallocMem(TwoDArray& arrWorld, int intRows);
    void MoveTail(tWorld& stcWorld, int intDRow, int intDCol);
    void PlaceBFreuit(tWorld& stcWorld);
    void IsFruit(tWorld& stcWorld, int Row, int Col);

}

#endif // GAME_H_INCLUDED
