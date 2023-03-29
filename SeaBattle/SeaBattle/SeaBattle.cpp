#include <iostream>
#include <windows.h>

using namespace std;

const int SIZEBOARD = 10;

bool playerLose(char** player)
{
    bool losePlayer = true;

    for (int i = 0; i < SIZEBOARD; i++)
        for (int j = 0; j < SIZEBOARD; j++)
            if (player[i][j] == 'S')
                losePlayer = false;

    return losePlayer;
}

bool gameOver(char** player1, char** player2)
{
    bool lose_player1 = playerLose(player1);
    bool lose_player2 = playerLose(player2);    

    return lose_player1 || lose_player2;
}

bool is_player1_win(char** player1)
{
    bool player1_win = false;

    for (int i = 0; i < SIZEBOARD; i++)
        for (int j = 0; j < SIZEBOARD; j++)
            if (player1[i][j] == 'S')
                player1_win = true;

    return player1_win;
}

char** shotBoard(int Xshot, int Yshot, char** boardDefendPlayer, char** defendPlayer)
{
    if (defendPlayer[Yshot - 1][Xshot - 1] == 'S')
        boardDefendPlayer[Yshot - 1][Xshot - 1] = 'X';
    else
        boardDefendPlayer[Yshot - 1][Xshot - 1] = 'O';

    return boardDefendPlayer;
}

char** shotPlayer(int Xshot, int Yshot, char** defendPlayer)
{
    if (defendPlayer[Yshot - 1][Xshot - 1] == 'S')
        defendPlayer[Yshot - 1][Xshot - 1] = 'X';
    else
        defendPlayer[Yshot - 1][Xshot - 1] = 'O';

    return defendPlayer;
}

void printBoard(char** player)
{
    cout << "Your board" << endl << endl << "    ";

    for (int i = 0; i < SIZEBOARD; i++)
        cout << i + 1 << "  ";

    cout << endl;

    for (int i = 0; i < SIZEBOARD - 1; i++)
    {
        cout << " " << i + 1 << "  ";
        for (int j = 0; j < SIZEBOARD; j++)
            cout << player[i][j] << "  ";
        cout << endl;
    }

    for (int i = SIZEBOARD - 1; i < SIZEBOARD; i++)
    {
        cout << i + 1 << "  ";
        for (int j = 0; j < SIZEBOARD; j++)
            cout << player[i][j] << "  ";
        cout << endl;
    }
}

char** placeShip(int X5, int Y5, string direction5, char** player, int shipSize)
{
    if (direction5 == "left" || direction5 == "right")
    {
        for (int i = Y5 - 1, j = X5 - 1, magnifier = direction5 == "right" ? magnifier = 1 : magnifier = -1, steps = 0; steps < shipSize; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
    else
    {
        for (int i = Y5 - 1, j = X5 - 1, magnifier = direction5 == "up" ? magnifier = -1 : magnifier = 1, steps = 0; steps < shipSize; i += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }

    return player;
}

bool error(int X, int Y, string direction, char** player, int ship_s)
{
    bool is_error = false;

    if (!(X > 10 || X < 0) && !(Y > 10 || Y < 0))
    {
        if (direction == "left" || direction == "right")
        {
            if (direction == "right")
            {
                if (X + ship_s - 1 > 10)
                    is_error = true;
                if (X == 1)
                {
                    ship_s--;
                }
                for (int i = Y == 1 ? Y - 1 : Y - 2; i < SIZEBOARD && i < Y + 1; i++)
                {
                    for (int j = X == 1 ? X - 1 : X - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
                    {
                        if (player[i][j] == 'S')
                        {
                            is_error = true;
                        }
                    }
                }
            }
            else
            {
                if (X - ship_s < 0)
                    is_error = true;
                if (X == 10)
                {
                    ship_s--;
                }
                for (int i = Y == 1 ? Y - 1 : Y - 2; i < SIZEBOARD && i < Y + 1; i++)
                {
                    for (int j = X == 10 ? X - 1 : X, stepsJ = 0; j > 0 && stepsJ < ship_s + 2; j--, stepsJ++)
                    {
                        if (player[i][j] == 'S')
                        {
                            is_error = true;
                        }
                    }
                }
            }
        }
        else
        {
            if (direction == "up")
            {
                if (Y - ship_s < 0)
                    is_error = true;
                if (Y == 10)
                        ship_s--;
                for (int j = X == 1 ? X - 1 : X - 2; j < SIZEBOARD && j < X + 1; j++)
                    for (int i = Y == 10 ? Y - 1 : Y, stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                        if (player[i][j] == 'S')
                            is_error = true;
            }
            else
            {
                if (Y + ship_s - 1 > 10)
                    is_error = true;
                if (Y == 1)
                    ship_s--;
                for (int j = X == 1 ? X - 1 : X - 2; j < SIZEBOARD && j < X + 1; j++)
                    for (int i = Y == 1 ? Y - 1 : Y - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
                        if (player[i][j] == 'S')
                            is_error = true;
            }
        }
    }
    else
    {
        is_error = true;
    }

    return is_error;
}

char** placeBoard(char** player)
{
    int X;
    int Y;
    int shipSize = 5;
    string direction;

    printBoard(player);

    while (true)
    {
        cout << endl << "Enter the vertical coordinate to place a five-deck ship:" << endl;
        cin >> Y;

        cout << "Enter the horizontal coordinate to place a five-deck ship:" << endl;
        cin >> X;

        cout << "Enter the direction to place a five-deck ship:(up,down,left,right)" << endl;
        cin >> direction;

        if (error(X, Y, direction, player, shipSize))
        {
            cout << "ERRROOR" << endl;
        }
        else
        {
            break;
        }
    }

    player = placeShip(X, Y, direction, player, shipSize);
    system("cls");

    shipSize = 3;

    for (int i = 0; i < 2; i++)
    {
        printBoard(player);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a three-deck ship " << i + 1 << " :" << endl;
            cin >> Y;

            cout << "Enter the horizontal coordinate to place a three-deck ship " << i + 1 << " :" << endl;
            cin >> X;

            cout << "Enter the direction to place a three-deck ship " << i + 1 << " :(up,down,left,right)" << endl;
            cin >> direction;

            if (error(X, Y, direction, player, shipSize))
            {
                cout << "ERRROOR" << endl;
            }
            else
            {
                break;
            }
        }

        player = placeShip(X, Y, direction, player, shipSize);
        system("cls");
    }

    shipSize = 2;

    for (int i = 0; i < 3; i++)
    {
        printBoard(player);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a two-deck ship " << i + 1 << " :" << endl;
            cin >> Y;

            cout << "Enter the horizontal coordinate to place a two-deck ship " << i + 1 << " :" << endl;
            cin >> X;

            cout << "Enter the direction to place a two-deck ship " << i + 1 << " :(up,down,left,right)" << endl;
            cin >> direction;

            if (error(X, Y, direction, player, shipSize))
            {
                cout << "ERRROOR" << endl;
            }
            else
            {
                break;
            }
        }

        player = placeShip(X, Y, direction, player, shipSize);
        system("cls");
    }

    shipSize = 1;

    for (int i = 0; i < 4; i++)
    {
        printBoard(player);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a one-deck ship " << i + 1 << " :" << endl;
            cin >> Y;

            cout << "Enter the horizontal coordinate to place a one-deck ship " << i + 1 << " :" << endl;
            cin >> X;

            if (error(X, Y, direction, player, shipSize))
            {
                cout << "ERRROOR" << endl;
            }
            else
            {
                break;
            }
        }

        player = placeShip(X, Y, direction, player, shipSize);
        system("cls");
    }

    return player;
}

char** createBoard()
{
    char** pl = 0;
    pl = new char* [SIZEBOARD];

    for (int h = 0; h < SIZEBOARD; h++)
    {
        pl[h] = new char[SIZEBOARD];
        for (int w = 0; w < SIZEBOARD; w++)
            pl[h][w] = 0;
    }

    for (int i = 0; i < SIZEBOARD; i++)
        for (int j = 0; j < SIZEBOARD; j++)
            pl[i][j] = '-';

    return pl;
}

void DeleteBoards(char** player1, char** player2, char** player1Hide, char** player2Hide)
{
    for (int i = 0; i < SIZEBOARD; i++)
        delete[] player1[i];
    delete[] player1;

    for (int i = 0; i < SIZEBOARD; i++)
        delete[] player2[i];
    delete[] player2;

    for (int i = 0; i < SIZEBOARD; i++)
        delete[] player1Hide[i];
    delete[] player1Hide;

    for (int i = 0; i < SIZEBOARD; i++)
        delete[] player2Hide[i];
    delete[] player2Hide;
}


int main()
{
    bool is_player1_hit = true;
    bool is_game_over = false;

    string won_player;
    string direction;

    int X;
    int Y;
    int shipSize = 5;

    char** player1 = createBoard();
    char** player1Hide = createBoard();
    char** player2 = createBoard();
    char** player2Hide = createBoard();

    player1 = placeBoard(player1);
    player2 = placeBoard(player2);

    while (!is_game_over)
    {
        if (is_player1_hit)
        {
            while (true)
            {
                printBoard(player2Hide);

                while (true)
                {
                    cout << "Player 1, enter the vertical coordinate for the shot:" << endl;
                    cin >> Y;

                    cout << "Player 1, enter the horizontal coordinate for the shot:" << endl;
                    cin >> X;

                    if ((X <= 10 && X >= 0) && (Y <= 10 && Y >= 0))
                        break;
                    else
                    {
                        cout << "ERROR";
                    }
                }

                player2Hide = shotBoard(X, Y, player2Hide, player2);
                player2 = shotPlayer(X, Y, player2);
                is_game_over = gameOver(player1, player2);

                if (is_game_over)
                    break;

                if (player2Hide[Y - 1][X - 1] == 'O')
                {
                    system("cls");
                    printBoard(player2Hide);

                    cout << endl << "You miss";
                    Sleep(2000);

                    is_player1_hit = false;
                    system("cls");

                    break;
                }
                system("cls");
            }
        }
        else
        {
            while (true)
            {
                printBoard(player1Hide);

                while (true)
                {
                    cout << "Player 2, enter the vertical coordinate for the shot:" << endl;
                    cin >> Y;

                    cout << "Player 2, enter the horizontal coordinate for the shot:" << endl;
                    cin >> X;

                    if ((X <= 10 && X >= 0) && (Y <= 10 && Y >= 0))
                        break;
                    else
                    {
                        cout << "ERROR";
                    }
                }

                player1Hide = shotBoard(X, Y, player1Hide, player1);
                player1 = shotPlayer(X, Y, player1);
                is_game_over = gameOver(player1, player2);

                if (is_game_over)
                    break;

                if (player1Hide[Y - 1][X - 1] == 'O')
                {
                    system("cls");
                    printBoard(player1Hide);

                    cout << endl << "You miss";
                    Sleep(2000);

                    is_player1_hit = true;
                    system("cls");

                    break;
                }
                system("cls");
            }
        }
    }

    system("cls");

    if (is_player1_win(player1))
        won_player = " player 1 ";
    else
        won_player = " player 2 ";

    cout << "Congratulation" << won_player << "!!!" << endl << "YOU WON!!" << endl;

    if (is_player1_win(player1))
    {
        cout << "WIN BOARD" << endl;
        printBoard(player1);
        cout << endl << "LOSE BOARD";
        printBoard(player2);
    }
    else
    {
        cout << "WIN BOARD" << endl;
        printBoard(player2);
        cout << endl << "LOSE BOARD";
        printBoard(player1);
    }

    return 0;
}
