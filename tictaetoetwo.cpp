#include <iostream>
#include <array>
#include <cstdlib>
#include <iterator>
using namespace std;
#include <chrono>
//#include <windows.h>

void printBoard(string board[3][3])
{
    cout << "    1    2    3\n";
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << " ";
        cout << "[ ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ]";
            if (j != 2) cout << "[ ";
        }
        cout << "\n";
    }
}

int main()
{
    system("cls");
    int aiType = 1;
    int freeSpace = 9;
    // 0 = completely random
    // 1 = priority is corners, then center, then sides. Will first prioritize blocking any potential player wins
    string board[3][3] = {{ " ", " ", " " }, { " ", " ", " " },{ " ", " ", " " }};
    int winner = -1;
    printBoard(board);
    srand(time(0));
    while (winner == -1)
    {
    int playerX = -1;
    int playerY = -1;
    int robotX = -1;
    int robotY = -1;
    bool allowed = false;
    while (!allowed)
    {
        while (playerX == -1)
        {
            cout << "Choose your horizontal coordinate: ";
            cin >> playerX;
            if (playerX <= 0 || playerX >= 4)
            {
                playerX = -1;
                cout << "ERROR: Invalid coordinate\n";
            }
        }
        while (playerY == -1)
        {
            cout << "Choose your vertical coordinate: ";
            cin >> playerY;
            if (playerY <= 0 || playerY >= 4)
            {
                playerY = -1;
                cout << "ERROR: Invalid coordinate\n";
            }
        }
        if (board[playerX-1][playerY-1].compare(" ") == 0)
        {
            allowed = true;
            freeSpace--;
            board[playerX-1][playerY-1] = "X";
        }
    }
    printBoard(board);
    for (int i = 0; i < 3; i++) // rows
    {
        if ((board[i][0].compare("X") == 0) && (board[i][1].compare("X")==0) && (board[i][2].compare("X")==0))
        {
            winner = 0;
            cout << "Player wins!";
            break;
        }
    }
    for (int i = 0; i < 3; i++) // cols
    {
        if ((board[0][i].compare("X") == 0) && (board[1][i].compare("X")==0) && (board[2][i].compare("X")==0))
            {
                winner = 0;
                cout << "Player wins!";
                break;
            }
    }
    if (board[0][0].compare("X") == 0 && board[1][1].compare("X")==0 && board[2][2].compare("X")==0) // diag1
    {
        winner = 0;
        cout << "Player wins!";
        break;
    }
    if (board[2][0].compare("X") == 0 && board[1][1].compare("X")==0 && board[0][2].compare("X")==0) // diag2
    {
        winner = 0;
        cout << "Player wins!";
        break;
    }
    //tie check
    if (freeSpace <= 0)
    {
        winner = 0;
        cout << "Tie!";
        break;
    }
    allowed = false;
    cout << "Robot is thinking...\n";
    //Sleep(1);
    while (!allowed)
    {
        if (aiType == 1)
        {
            // securing O wins
            if (board[1][1].compare("O")==0 && board[0][0].compare("O")==0 && board[2][2].compare(" ")==0)
            {
                allowed = true;
                freeSpace--;
                board[2][2] = "O";
            }
            else if (board[1][1].compare(" ")==0 && board[0][0].compare("O")==0 && board[2][2].compare("O")==0)
            {
                allowed = true;
                freeSpace--;
                board[1][1] = "O";
            }
            else if (board[1][1].compare("O")==0 && board[0][0].compare(" ")==0 && board[2][2].compare("O")==0)
            {
                allowed = true;
                freeSpace--;
                board[0][0] = "O";
            }
            else if (board[1][1].compare("O")==0 && board[2][0].compare(" ")==0 && board[0][2].compare("O")==0)
            {
                allowed = true;
                freeSpace--;
                board[2][0] = "O";
            }
            else if (board[1][1].compare("O")==0 && board[2][0].compare("O")==0 && board[0][2].compare(" ")==0)
            {
                allowed = true;
                freeSpace--;
                board[0][2] = "O";
            }
            else if (board[1][1].compare(" ")==0 && board[2][0].compare("O")==0 && board[0][2].compare("O")==0)
            {
                allowed = true;
                freeSpace--;
                board[1][1] = "O";
            }
            if (allowed) break;
            for (int i = 0; i < 3; i++) // rows
            {
                if ((board[i][0].compare(" ") == 0) && (board[i][1].compare("O")==0) && (board[i][2].compare("O")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][0] = "O";
                    break;
                }
                else if ((board[i][0].compare("O") == 0) && (board[i][1].compare(" ")==0) && (board[i][2].compare("O")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][1] = "O";
                    break;
                }
                else if ((board[i][0].compare("O") == 0) && (board[i][1].compare("O")==0) && (board[i][2].compare(" ")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][2] = "O";
                    break;
                }
            }
            if (allowed) break;
            for (int i = 0; i < 3; i++) // cols
            {
                if ((board[0][i].compare(" ") == 0) && (board[1][i].compare("O")==0) && (board[2][i].compare("O")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[0][i] = "O";
                    break;
                }
                else if ((board[0][i].compare("O") == 0) && (board[1][i].compare(" ")==0) && (board[2][i].compare("O")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[1][i] = "O";
                    break;
                }
                else if ((board[0][i].compare("O") == 0) && (board[1][i].compare("O")==0) && (board[2][i].compare(" ")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[2][i] = "O";
                    break;
                }
            }
            if (allowed) break;
            //blocking X's potential wins
            if (board[1][1].compare("X")==0 && board[0][0].compare("X")==0 && board[2][2].compare(" ")==0)
            {
                allowed = true;
                freeSpace--;
                board[2][2] = "O";
            }
            else if (board[1][1].compare(" ")==0 && board[0][0].compare("X")==0 && board[2][2].compare("X")==0)
            {
                allowed = true;
                freeSpace--;
                board[1][1] = "O";
            }
            else if (board[1][1].compare("X")==0 && board[0][0].compare(" ")==0 && board[2][2].compare("X")==0)
            {
                allowed = true;
                freeSpace--;
                board[0][0] = "O";
            }
            else if (board[1][1].compare("X")==0 && board[2][0].compare(" ")==0 && board[0][2].compare("X")==0)
            {
                allowed = true;
                freeSpace--;
                board[2][0] = "O";
            }
            else if (board[1][1].compare("X")==0 && board[2][0].compare("X")==0 && board[0][2].compare(" ")==0)
            {
                allowed = true;
                freeSpace--;
                board[0][2] = "O";
            }
            else if (board[1][1].compare(" ")==0 && board[2][0].compare("X")==0 && board[0][2].compare("X")==0)
            {
                allowed = true;
                freeSpace--;
                board[1][1] = "O";
            }
            if (allowed) break;
            for (int i = 0; i < 3; i++) // rows
            {
                if ((board[i][0].compare(" ") == 0) && (board[i][1].compare("X")==0) && (board[i][2].compare("X")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][0] = "O";
                    break;
                }
                else if ((board[i][0].compare("X") == 0) && (board[i][1].compare(" ")==0) && (board[i][2].compare("X")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][1] = "O";
                    break;
                }
                else if ((board[i][0].compare("X") == 0) && (board[i][1].compare("X")==0) && (board[i][2].compare(" ")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[i][2] = "O";
                    break;
                }
            }
            if (allowed) break;
            for (int i = 0; i < 3; i++) // cols
            {
                if ((board[0][i].compare(" ") == 0) && (board[1][i].compare("X")==0) && (board[2][i].compare("X")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[0][i] = "O";
                    break;
                }
                else if ((board[0][i].compare("X") == 0) && (board[1][i].compare(" ")==0) && (board[2][i].compare("X")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[1][i] = "O";
                    break;
                }
                else if ((board[0][i].compare("X") == 0) && (board[1][i].compare("X")==0) && (board[2][i].compare(" ")==0))
                {
                    allowed = true;
                    freeSpace--;
                    board[2][i] = "O";
                    break;
                }
            }
            if (allowed) break;
            //corner check
            if (board[0][0].compare(" ")!=0 && board[0][2].compare(" ")!=0 && board[2][0].compare(" ")!=0 && board[2][2].compare(" ")!=0)
            {
                // if middle is available, take it
                if (board[1][1].compare(" ")==0)
                {
                    allowed = true;
                    freeSpace--;
                    board[1][1] = "O";
                }
                else
                {
                    //last resort: random side. no check for side availability is necessary, since if all corners, middle, and sides are full, then game is already over regardless
                    bool works = false;
                    while (!works)
                    {
                        robotY = (rand() % (3));
                        if (robotY == 1) robotX = (rand() % (2)) * 2;
                        else robotX = 1;
                        if (board[robotX][robotY].compare(" ") == 0)
                        {
                            works = true;
                            allowed = true;
                            freeSpace--;
                            board[robotX][robotY] = "O";
                        }
                    }
                }
            }
            else
            {
                bool works = false;
                while (!works)
                {
                    robotX = (rand() % (2)) * 2;
                    robotY = (rand() % (2)) *2;
                    if (board[robotX][robotY].compare(" ") == 0)
                    {
                        works = true;
                        allowed = true;
                        freeSpace--;
                        board[robotX][robotY] = "O";
                    }
                }
                
            }

        }
        if (aiType == 0)
        {
            robotX = 1 + (rand() % (3));
            robotY = 1 + (rand() % (3));
            if (board[robotX-1][robotY-1].compare(" ") == 0)
            {
                allowed = true;
                freeSpace--;
                board[robotX-1][robotY-1] = "O";
            }
        }
    }
        printBoard(board);
        for (int i = 0; i < 3; i++) // rows
        {
            if ((board[i][0].compare("O") == 0) && (board[i][1].compare("O")==0) && (board[i][2].compare("O")==0))
            {
                winner = 0;
                cout << "Robot wins!";
                break;
            }
        }
        for (int i = 0; i < 3; i++) // cols
        {
        if ((board[0][i].compare("O") == 0) && (board[1][i].compare("O")==0) && (board[2][i].compare("O")==0))
            {
                winner = 0;
                cout << "Robot wins!";
                break;
            }
        }
        if (board[0][0].compare("O") == 0 && board[1][1].compare("O")==0 && board[2][2].compare("O")==0) // diag1
        {
            winner = 0;
            cout << "Robot wins!";
            break;
        }
        if (board[2][0].compare("O") == 0 && board[1][1].compare("O")==0 && board[0][2].compare("O")==0) // diag2
        {
            winner = 0;
            cout << "Robot wins!";
            break;
        }
}

    
}