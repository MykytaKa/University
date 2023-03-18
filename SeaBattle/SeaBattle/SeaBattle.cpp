#include <iostream>
#include <windows.h>

using namespace std;

const int size = 10;

const string dir[] = { "up","down","left","right" };

const int coordinateX[] = { 1,2,3,4,5,6,7,8,9,10 };

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool gameOver(char** player1, char** player2)
{
    bool lose_player1 = true;

    bool lose_player2 = true;

    bool somebody_lose = false;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (player1[i][j] == 'S')
                lose_player1 = false;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (player2[i][j] == 'S')
                lose_player2 = false;

    if (lose_player1 || lose_player2)
        somebody_lose = true;

    return somebody_lose;
}

bool is_player1_win(char** player1, char** player2)
{
    bool player1_win = false;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (player1[i][j] == 'S')
                player1_win = true;

    return player1_win;
}

char** shotBoard(int Xshot, int Yshot, char** boardDefendPlayer, char** defendPlayer)
{
    if (defendPlayer[Yshot - 1][Xshot - 1] == 'S')
    {
        boardDefendPlayer[Yshot - 1][Xshot - 1] = 'X';
    }
    else
    {
        boardDefendPlayer[Yshot - 1][Xshot - 1] = 'O';
    }

    return boardDefendPlayer;
}

char** shotPlayer(int Xshot, int Yshot, char** defendPlayer)
{
    if (defendPlayer[Yshot - 1][Xshot - 1] == 'S')
    {
        defendPlayer[Yshot - 1][Xshot - 1] = 'X';
    }
    else
    {
        defendPlayer[Yshot - 1][Xshot - 1] = 'O';
    }

    return defendPlayer;
}

void printBoard(char** player)
{
    cout << "Your board" << endl << endl;

    cout << "    ";

    for (int i = 0; i < size; i++)
        cout << coordinateX[i] << "  ";

    cout << endl;

    for (int i = 0; i < size - 1; i++)
    {
        cout << " " << coordinateX[i] << "  ";
        for (int j = 0; j < size; j++)
            cout << player[i][j] << "  ";
        cout << endl;
    }

    for (int i = size - 1; i < size; i++)
    {
        cout << coordinateX[i] << "  ";
        for (int j = 0; j < size; j++)
            cout << player[i][j] << "  ";
        cout << endl;
    }
}

char** five_deck_ship(int X5, int Y5, string direction5, char** player)
{
    if (direction5 == "left" || direction5 == "right")
    {
        for (int i = Y5 - 1, j = X5 - 1, magnifier = direction5 == "right" ? magnifier = 1 : magnifier = -1, steps = 0; steps < 5; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
    else
    {
        for (int i = Y5 - 1, j = X5 - 1, magnifier = direction5 == "up" ? magnifier = -1 : magnifier = 1, steps = 0; steps < 5; i += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }

    return player;
}

char** three_deck_ship(int X3, int Y3, string direction3, char** player)
{
    if (direction3 == "left" || direction3 == "right")
    {
        for (int i = Y3 - 1, j = X3 - 1, magnifier = direction3 == "right" ? magnifier = 1 : magnifier = -1, steps = 0; steps < 3; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
    else
    {
        for (int i = Y3 - 1, j = X3 - 1, magnifier = direction3 == "up" ? magnifier = -1 : magnifier = 1, steps = 0; steps < 3; i += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }

    return player;
}

char** two_deck_ship(int X2, int Y2, string direction2, char** player)
{
    if (direction2 == "left" || direction2 == "right")
    {
        for (int i = Y2 - 1, j = X2 - 1, magnifier = direction2 == "right" ? magnifier = 1 : magnifier = -1, steps = 0; steps < 2; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
    else
    {
        for (int i = Y2 - 1, j = X2 - 1, magnifier = direction2 == "up" ? magnifier = -1 : magnifier = 1, steps = 0; steps < 2; i += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }

    return player;
}

char** one_deck_ship(int X1, int Y1, char** player)
{
    player[Y1 - 1][X1 - 1] = 'S';

    return player;
}

bool errorOneDeskShip(int X, int Y, char** player, int ship_s)
{
    bool is_error = false;

    if ((X <= 10 && X >= 0) && (Y <= 10 && Y >= 0))
    {
        if (X == 1)
        {
            ship_s--;
        }
        for (int i = Y == 1 ? Y - 1 : Y - 2; i < size && i < Y + 1; i++)
        {
            for (int j = X == 1 ? X - 1 : X - 2, stepsJ = 0; j < size && stepsJ < ship_s + 2; j++, stepsJ++)
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
        is_error = true;
    }

    return is_error;
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
                if (X == 1)
                {
                    ship_s--;
                }
                for (int i = Y == 1 ? Y - 1 : Y - 2; i < size && i < Y + 1; i++)
                {
                    for (int j = X == 1 ? X - 1 : X - 2, stepsJ = 0; j < size && stepsJ < ship_s + 2; j++, stepsJ++)
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
                if (X == 10)
                {
                    ship_s--;
                }
                for (int i = Y == 1 ? Y - 1 : Y - 2; i < size && i < Y + 1; i++)
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
                if (Y == 10)
                {
                    ship_s--;
                }
                for (int j = X == 1 ? X - 1 : X - 2; j < size && j < X + 1; j++)
                {
                    for (int i = Y == 10 ? Y - 1 : Y, stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
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
                if (Y == 1)
                {
                    ship_s--;
                }
                for (int j = X == 1 ? X - 1 : X - 2; j < size && j < X + 1; j++)
                {
                    for (int i = Y == 1 ? Y - 1 : Y - 2, stepsI = 0; i < size && stepsI < ship_s + 2; i++, stepsI++)
                    {
                        if (player[i][j] == 'S')
                        {
                            is_error = true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        is_error = true;
    }

    return is_error;
}

char** createPlayer1()
{
    char** pl1 = 0;

    pl1 = new char* [size];

    for (int h = 0; h < size; h++)
    {
        pl1[h] = new char[size];

        for (int w = 0; w < size; w++)
        {
            pl1[h][w] = 0;
        }
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pl1[i][j] = '-';

    return pl1;
}

char** createPlayer2()
{
    char** pl2 = 0;

    pl2 = new char* [size];

    for (int h = 0; h < size; h++)
    {
        pl2[h] = new char[size];

        for (int w = 0; w < size; w++)
        {
            pl2[h][w] = 0;
        }
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pl2[i][j] = '-';

    return pl2;
}

char** createPlayer1Hide()
{
    char** pl1 = 0;

    pl1 = new char* [size];

    for (int h = 0; h < size; h++)
    {
        pl1[h] = new char[size];

        for (int w = 0; w < size; w++)
        {
            pl1[h][w] = 0;
        }
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pl1[i][j] = '-';

    return pl1;
}

char** createPlayer2Hide()
{
    char** pl2 = 0;

    pl2 = new char* [size];

    for (int h = 0; h < size; h++)
    {
        pl2[h] = new char[size];

        for (int w = 0; w < size; w++)
        {
            pl2[h][w] = 0;
        }
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pl2[i][j] = '-';

    return pl2;
}

void DeleteBoards(char** player1, char** player2, char** player1Hide, char** player2Hide)
{
    for (int i = 0; i < size; i++)
    {
        delete[] player1[i];
    }

    delete[] player1;

    for (int i = 0; i < size; i++)
    {
        delete[] player2[i];
    }

    delete[] player2;

    for (int i = 0; i < size; i++)
    {
        delete[] player1Hide[i];
    }

    delete[] player1Hide;

    for (int i = 0; i < size; i++)
    {
        delete[] player2Hide[i];
    }

    delete[] player2Hide;
}


int main()
{
    bool is_player1_hit = true;

    bool is_game_over = false;

    int who_win; 

    string won_player;

    int X;

    int Y;

    int ship_size = 5;

    string direction;

    char** player1 = createPlayer1();

    char** player1Hide = createPlayer1Hide();

    char** player2 = createPlayer2();

    char** player2Hide = createPlayer2Hide();

    printBoard(player1);

    while (true)
    {
        cout << endl << "Enter the vertical coordinate to place a five-deck ship:" << endl;

        cin >> Y;

        cout << "Enter the horizontal coordinate to place a five-deck ship:" << endl;

        cin >> X;

        cout << "Enter the direction to place a five-deck ship:(up,down,left,right)" << endl;

        cin >> direction;

        if (!(error(X, Y, direction, player1, ship_size)))
        {
            if (direction == "left" || direction == "right")
            {
                if (direction == "right")
                {
                    if (X + 4 <= 10)
                        break;
                    else
                    {
                        cout << "Invalid value of X" << endl;
                    }
                }
                else if (direction == "left")
                {
                    if (X - 5 >= 0)
                        break;
                    else
                    {
                        cout << "Invalid value of X" << endl;
                    }
                }
            }
            else
            {
                if (direction == "up")
                {
                    if (Y - 5 >= 0)
                        break;
                    else
                    {
                        cout << "Invalid value of Y" << endl;
                    }
                }
                else if (direction == "down")
                {
                    if (Y + 4 <= 10)
                        break;
                    else
                    {
                        cout << "Invalid value of Y" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "Invalid value of X/Y" << endl;
        }
    }

    player1 = five_deck_ship(X, Y, direction, player1);

    ClearScreen();

    ship_size = 3;

    for (int i = 0; i < 2; i++)
    {
        printBoard(player1);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a three-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a three-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            cout << "Enter the direction to place a three-deck ship " << i + 1 << " :(up,down,left,right)" << endl;

            cin >> direction;

            if (!(error(X, Y, direction, player1, ship_size)))
            {
                if (direction == "left" || direction == "right")
                {
                    if (direction == "right")
                    {
                        if (X + 2 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                    else if (direction == "left")
                    {
                        if (X - 3 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                }
                else
                {
                    if (direction == "up")
                    {
                        if (Y - 3 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                    else if (direction == "down")
                    {
                        if (Y + 2 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "There is a ship in this cells / Invalid value of X/Y" << endl;
            }

        }

        player1 = three_deck_ship(X, Y, direction, player1);

        ClearScreen();
    }

    ship_size = 2;

    for (int i = 0; i < 3; i++)
    {
        printBoard(player1);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a two-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a two-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            cout << "Enter the direction to place a two-deck ship " << i + 1 << " :(up,down,left,right)" << endl;

            cin >> direction;

            if (!(error(X, Y, direction, player1, ship_size)))
            {
                if (direction == "left" || direction == "right")
                {
                    if (direction == "right")
                    {
                        if (X + 1 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                    else if (direction == "left")
                    {
                        if (X - 2 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                }
                else
                {
                    if (direction == "up")
                    {
                        if (Y - 2 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                    else if (direction == "down")
                    {
                        if (Y + 1 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "There is a ship in this cells / Invalid value of X/Y" << endl;
            }

        }

        player1 = two_deck_ship(X, Y, direction, player1);

        ClearScreen();
    }

    ship_size = 1;

    for (int i = 0; i < 4; i++)
    {
        printBoard(player1);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a one-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a one-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            if (!(error(X, Y, direction, player1, ship_size)))
            {
                if ((X <= 10 && X >= 0) && (Y <= 10 && Y >= 0))
                    break;
                else
                    cout << "Invalid value X or Y" << endl;
            }
            else
            {
                cout << "There is a ship in this cell / Invalid value of X/Y" << endl;
            }
        }

        player1 = one_deck_ship(X, Y, player1);

        ClearScreen();
    }

    ship_size = 5;

    printBoard(player2);

    while (true)
    {
        cout << endl << "Enter the vertical coordinate to place a five-deck ship:" << endl;

        cin >> Y;

        cout << "Enter the horizontal coordinate to place a five-deck ship:" << endl;

        cin >> X;

        cout << "Enter the direction to place a five-deck ship:(up,down,left,right)" << endl;

        cin >> direction;

        if (!(error(X, Y, direction, player2, ship_size)))
        {
            if (direction == "left" || direction == "right")
            {
                if (direction == "right")
                {
                    if (X + 4 <= 10)
                        break;
                    else
                    {
                        cout << "Invalid value of X" << endl;
                    }
                }
                else if (direction == "left")
                {
                    if (X - 5 >= 0)
                        break;
                    else
                    {
                        cout << "Invalid value of X" << endl;
                    }
                }
            }
            else
            {
                if (direction == "up")
                {
                    if (Y - 5 >= 0)
                        break;
                    else
                    {
                        cout << "Invalid value of Y" << endl;
                    }
                }
                else if (direction == "down")
                {
                    if (Y + 4 <= 10)
                        break;
                    else
                    {
                        cout << "Invalid value of Y" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "There is a ship in this cells / Invalid value of X/Y" << endl;
        }
    }

    player2 = five_deck_ship(X, Y, direction, player2);

    ClearScreen();

    ship_size = 3;

    for (int i = 0; i < 2; i++)
    {
        printBoard(player2);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a three-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a three-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            cout << "Enter the direction to place a three-deck ship " << i + 1 << " :(up,down,left,right)" << endl;

            cin >> direction;

            if (!(error(X, Y, direction, player2, ship_size)))
            {
                if (direction == "left" || direction == "right")
                {
                    if (direction == "right")
                    {
                        if (X + 2 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                    else if (direction == "left")
                    {
                        if (X - 3 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                }
                else
                {
                    if (direction == "up")
                    {
                        if (Y - 3 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                    else if (direction == "down")
                    {
                        if (Y + 2 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "There is a ship in this cells / Invalid value of X/Y" << endl;
            }
        }

        player2 = three_deck_ship(X, Y, direction, player2);;

        ClearScreen();
    }

    ship_size = 2;

    for (int i = 0; i < 3; i++)
    {
        printBoard(player2);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a two-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a two-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            cout << "Enter the direction to place a two-deck ship " << i + 1 << " :(up,down,left,right)" << endl;

            cin >> direction;

            if (!(error(X, Y, direction, player2, ship_size)))
            {
                if (direction == "left" || direction == "right")
                {
                    if (direction == "right")
                    {
                        if (X + 1 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                    else if (direction == "left")
                    {
                        if (X - 2 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of X" << endl;
                        }
                    }
                }
                else
                {
                    if (direction == "up")
                    {
                        if (Y - 2 >= 0)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                    else if (direction == "down")
                    {
                        if (Y + 1 <= 10)
                            break;
                        else
                        {
                            cout << "Invalid value of Y" << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "There is a ship in this cells / Invalid value of X/Y" << endl;
            }
        }


        player2 = two_deck_ship(X, Y, direction, player2);

        ClearScreen();
    }

    ship_size = 1;


    for (int i = 0; i < 4; i++)
    {
        printBoard(player2);

        while (true)
        {
            cout << "Enter the vertical coordinate to place a one-deck ship " << i + 1 << " :" << endl;

            cin >> Y;

            cout << "Enter the horizontal coordinate to place a one-deck ship " << i + 1 << " :" << endl;

            cin >> X;

            if (!(errorOneDeskShip(X, Y, player2, ship_size)))
            {
                break;
            }
            else
            {
                cout << "There is a ship in this cell / Invalid value of X/Y" << endl;
            }
        }

        player2 = one_deck_ship(X, Y, player2);

        ClearScreen();
    }

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
                }

                player2Hide = shotBoard(X, Y, player2Hide, player2);

                player2 = shotPlayer(X, Y, player2);

                is_game_over = gameOver(player1, player2);

                if (is_game_over)
                    break;

                if (player2Hide[Y - 1][X - 1] == 'O')
                {
                    ClearScreen();

                    printBoard(player2Hide);

                    cout << endl << "You miss";

                    Sleep(2000);

                    is_player1_hit = false;

                    ClearScreen();

                    break;
                }

                ClearScreen();
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
                }

                player1Hide = shotBoard(X, Y, player1Hide, player1);

                player1 = shotPlayer(X, Y, player1);

                is_game_over = gameOver(player1, player2);

                if (is_game_over)
                    break;

                if (player1Hide[Y - 1][X - 1] == 'O')
                {
                    ClearScreen();

                    printBoard(player1Hide);

                    cout << endl << "You miss";

                    Sleep(2000);

                    is_player1_hit = true;

                    ClearScreen();

                    break;
                }

                ClearScreen();
            }
        }
    }

    ClearScreen();

    if (is_player1_win(player1, player2))
        won_player = " player 1 ";
    else
        won_player = " player 2 ";

    cout << "Congratulation" << won_player << "!!!" << endl << "YOU WON!!" << endl;

    if (is_player1_win)
    {
        printBoard(player1);
        cout << endl;
        printBoard(player2);
    }
    else
    {
        printBoard(player2);
        cout << endl;
        printBoard(player1);
    }

    return 0;
}
