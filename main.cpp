#include <iostream>
#include "Game.h"

using namespace std;
using namespace GameSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    //Validate arguments
    if(argc != 3)
    {
        cerr << "Incorrect argument " <<argv[0] << ": <intRows> <intCols>"<<endl;
        exit(ERR_ARGC);
    }

    //Assigning arguments to varriables
    int intRows = stoi(argv[1]);
    int intCols = stoi(argv[2]);

    //My variables
    Directions dir = STOP;
    Directions prevDir = STOP;
    bool blnContinue = true;
    bool blnQuit = false;
    int Level = 0;
    char menu = '\n';
    int Score = 0;
    int HighScore = 0;
    int intcount =0;
    int speedLevel = 0;

    cout << "Chose Level:" << endl
        << "1. Easy (pass trough borders)" << endl
        << "2. Hard (Solid border)" << endl;
    cin >> Level;

    //Countrol guides
    int intSeconds = 4;
    while(intSeconds !=0){
        system("cls");
        cout << "                                    CONTROLS: A,W,S,D                                    " << endl;
        cout << endl;
        cout << "                                    PAUSE : P                                            " << endl;
        cout << endl;
        cout << "                                    COUNTINUE: any CONTROL                               " << endl;
        cout << endl;
        cout << "                                          " ;
        cout << intSeconds << endl;
        Sleep(1000);
        intSeconds--;
    }


    //start the world
    tWorld stcWorld = initWorld(intRows, intCols, Score);
    while(!(blnQuit))
    {
        while (blnContinue)
        {
            // Display the world
            DisplayWorld(stcWorld, Score, HighScore);

            // Get user input
           if (_kbhit())
            {
                switch (_getch())
                {
                    case 'w':
                        if (prevDir != DOWN) // Prevent reversing direction
                            dir = UP;
                        break;
                    case 's':
                        if (prevDir != UP)
                            dir = DOWN;
                        break;
                    case 'a':
                        if (prevDir != RIGHT)
                            dir = LEFT;
                        break;
                    case 'd':
                        if (prevDir != LEFT)
                            dir = RIGHT;
                        break;
                    case 'p':
                            dir = STOP;
                            cout << "PAUSED" << endl;
                        break;
                    case 'q':
                        blnContinue = false;
                        break;
                    default:
                        continue;
                }
            }

            // Move the player in the specified direction
            if(dir != STOP)
            {
                MovePlayer(stcWorld, dir, Level);
            }

            // Store the current direction as the previous direction
            prevDir = dir;

            if(stcWorld.enStatus != RUNNING)
            {
                blnContinue = false;

            }

            Score += stcWorld.intScore;
            if(Score>HighScore)
            {
                HighScore = Score;
            }

            //increase speed
            if(Score > 50 && Score <= 100)
                speedLevel = 1;
            else if(Score > 100 && Score <= 300)
                speedLevel = 2;
            else if(Score > 300 && Score <= 400)
                speedLevel = 3;

            //Speed of the game
            switch(speedLevel){
                case 0 :
                    Sleep(100);
                    break;
                case 1 :
                    Sleep(80);
                    break;
                case 2 :
                    Sleep(60);
                    break;
                case 3 :
                    Sleep(30);
                    break;
            }
        }
        system("cls");

        if(stcWorld.enStatus == LOST)
        {
            cout << "************************************************************************************************" << endl;
            cout << "**********                                  GAME OVER!!                               **********" << endl;
        }
        if(Score <= HighScore && intcount == 0)
        {
            cout << "************************************************************************************************" << endl;
            cout << "                                     YOUR SCORE: "<< Score <<"                                  " << endl;
            cout << "                                     HIGH SCORE: "<< HighScore <<"!!                            " << endl;
        }
        if(Score <= HighScore && intcount>0)
        {
            cout << "************************************************************************************************" << endl;
            cout << "                                NEW HIGH SCORE: "<< HighScore <<"!!                             " << endl;
        }
        if(Score > HighScore)
        {
            intcount++;
            HighScore = Score;
            cout << "************************************************************************************************" << endl;
            cout << "                                NEW HIGH SCORE: "<< HighScore <<"!!                             " << endl;
        }

        cout << "M. Main menu" << endl
            << "N. New Game" << endl
            << "Q. Quit Game" << endl;
        cin >> menu;
            switch (menu)
                {
                    case 'n':
                        //New game
                        blnContinue = true;
                        dir = STOP;
                        DeallocMem(stcWorld.arrWorld, stcWorld.intRows);
                        Score = 0;
                        stcWorld = initWorld(intRows, intCols, Score);
                        intcount =0;
                        break;
                    case 'm':
                        //Main menu
                        system("cls");
                        cout << "Chose Level:" << endl
                                << "1. Easy" << endl
                                << "2. Hard" << endl;
                        cin >> Level;
                        blnContinue = true;
                        dir = STOP;
                        DeallocMem(stcWorld.arrWorld, stcWorld.intRows);
                        Score = 0;
                        stcWorld = initWorld(intRows, intCols, Score);
                        intcount =0;
                        break;
                    case 'q':
                        //Quit
                        blnQuit = true;
                        break;
                    default:
                        cerr << "Invalid input" << endl;
            }
    }

    if(stcWorld.arrWorld != nullptr)
    {
        DeallocMem(stcWorld.arrWorld, stcWorld.intRows);
    }
    return SUCCESS;
}


