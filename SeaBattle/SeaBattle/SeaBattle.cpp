#include <iostream>
#include <windows.h>
#include <ctype.h>

using namespace std;

const int SIZEBOARD = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;
const string Directions[] = {"right", "left", "up", "down" };


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
    return playerLose(player1) || playerLose(player2);
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
    else if (defendPlayer[Yshot - 1][Xshot - 1] == 'X')
    {
        cout << endl << "You've already shot at this cell";
        Sleep(2000);
    }
    else
        defendPlayer[Yshot - 1][Xshot - 1] = 'O';

    return defendPlayer;
}

void printBoard(char** player, string text)
{
    cout << text << endl << endl << "    ";

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

char** placeShip(int X, int Y, string direction, char** player, int shipSize)
{
    if (direction == "left" || direction == "right")
    {
        int magnifier = direction == "right" ? magnifier = 1 : magnifier = -1;

        for (int i = Y - 1, j = X - 1, steps = 0; steps < shipSize; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    } 
    else
    {
        int magnifier = direction == "up" ? magnifier = -1 : magnifier = 1;

        for (int i = Y - 1, j = X - 1, steps = 0; steps < shipSize; i += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
        
    return player;
}

bool isCorrectDirection(string direction)
{
    bool errorDirection = true;
    for (int i = 0; i < 4; i++)
        if (direction == Directions[i])
        {
            errorDirection = false;
            break;
        }

    return errorDirection;
}

bool error(int X, int Y, string direction, char** player, int ship_s)
{
    bool is_error = false;

    if (!(X > UPPERLIM || X < LOWERLIM) && !(Y > UPPERLIM || Y < LOWERLIM))
    {
        if (ship_s == 1)
        {
            for (int j = X == LOWERLIM + 1 ? X - 1 : X - 2; j < SIZEBOARD && j < X + 1; j++)
                for (int i = Y == UPPERLIM ? Y - 1 : Y, stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                    if (player[i][j] == 'S')
                        is_error = true;
        }
        else
        {
            if (direction == "right")
            {
                if (X + ship_s - 1 > UPPERLIM)
                    is_error = true;
                if (X == LOWERLIM + 1)
                    ship_s--;
                for (int i = Y == LOWERLIM + 1 ? Y - 1 : Y - 2; i < SIZEBOARD && i < Y + 1; i++)
                    for (int j = X == LOWERLIM + 1 ? X - 1 : X - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
                        if (player[i][j] == 'S')
                            is_error = true;

            }
            else if (direction == "left")
            {
                if (X - ship_s < LOWERLIM)
                    is_error = true;
                if (X == UPPERLIM)
                    ship_s--;
                for (int i = Y == LOWERLIM + 1 ? Y - 1 : Y - 2; i < SIZEBOARD && i < Y + 1; i++)
                    for (int j = X == UPPERLIM ? X - 1 : X, stepsJ = 0; j >= 0 && stepsJ < ship_s + 2; j--, stepsJ++)
                        if (player[i][j] == 'S')
                            is_error = true;
            }
            else if (direction == "up")
            {
                if (Y - ship_s < LOWERLIM)
                    is_error = true;
                if (Y == UPPERLIM)
                    ship_s--;
                for (int j = X == LOWERLIM + 1 ? X - 1 : X - 2; j < SIZEBOARD && j < X + 1; j++)
                    for (int i = Y == UPPERLIM ? Y - 1 : Y, stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                        if (player[i][j] == 'S')
                            is_error = true;
            }
            else if (direction == "down")
            {
                if (Y + ship_s - 1 > UPPERLIM)
                    is_error = true;
                if (Y == LOWERLIM + 1)
                    ship_s--;
                for (int j = X == LOWERLIM + 1 ? X - 1 : X - 2; j < SIZEBOARD && j < X + 1; j++)
                    for (int i = Y == LOWERLIM + 1 ? Y - 1 : Y - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
                        if (player[i][j] == 'S')
                            is_error = true;
            }
        }
    }
    else
        is_error = true;

    return is_error;
}

struct shipPosition
{
public:
    int x;
    int y;
    string direction;
};

shipPosition placeBoardFunc(int shipSize, char** player, int number)
{
    shipPosition ship;

    while (true)
    {
        cout << "Enter the vertical coordinate to place a " << shipSize << "-deck ship ";

        if (shipSize != 5)
            cout << number + 1 << " :" << endl;
        else
            cout << " :" << endl;

        cin >> ship.y;

        cout << "Enter the horizontal coordinate to place a " << shipSize << "-deck ship ";

        if (shipSize != 5)
            cout << number + 1 << " :" << endl;
        else
            cout << " :" << endl;

        cin >> ship.x;
        while (true)
        {
            if (shipSize != 1)
            {
                cout << "Enter the direction to place a " << shipSize << "-deck ship ";

                if (shipSize != 5)
                    cout << number + 1 << " :(up,down,left,right)" << endl;
                else
                    cout << " :(up,down,left,right)" << endl;

                cin >> ship.direction;

                if (!isCorrectDirection(ship.direction))
                    break;
                else
                    cout << "ERROR" << endl;
            }
        }

        if (error(ship.x, ship.y, ship.direction, player, shipSize))
            cout << "ERRROOR" << endl;
        else
            break;
    }

    return ship;
}

char** placeBoard(char** player)
{
    int shipSize = 5;

    printBoard(player, "Your board");
    
    shipPosition ship = placeBoardFunc(shipSize, player, 0);

    player = placeShip(ship.x, ship.y, ship.direction, player, shipSize);
    system("cls");

    shipSize = 3;

    for (int i = 0; i < 2; i++)
    {
        printBoard(player, "Your board");

        ship = placeBoardFunc(shipSize, player, i);

        player = placeShip(ship.x, ship.y, ship.direction, player, shipSize);
        system("cls");
    }

    shipSize = 2;

    for (int i = 0; i < 3; i++)
    {
        printBoard(player, "Your board");

        ship = placeBoardFunc(shipSize, player, i);

        player = placeShip(ship.x, ship.y, ship.direction, player, shipSize);
        system("cls");
    }

    shipSize = 1;

    for (int i = 0; i < 4; i++)
    {
        printBoard(player, "Your board");

        ship = placeBoardFunc(shipSize, player, i);

        player = placeShip(ship.x, ship.y, ship.direction, player, shipSize);
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

void DeleteBoardFunc(char** board)
{
    for (int i = 0; i < SIZEBOARD; i++)
        delete[] board[i];
    delete[] board;
}

void DeleteBoards(char** player1, char** player2, char** player1Hide, char** player2Hide)
{
    DeleteBoardFunc(player1);
    DeleteBoardFunc(player2);
    DeleteBoardFunc(player1Hide);
    DeleteBoardFunc(player2Hide);
}

void printWinLosePlayer(char** playerWon, char** playerLose)
{
    printBoard(playerWon, "WIN BOARD");
    printBoard(playerLose, "LOSE BOARD");
}

struct game
{
public:
    char** playerDefend;
    char** playerDefendHide;
    bool isGameOver;
    bool is_player1_hit;
};

game playFunc(char** playerAttack, char** playerDefend, char** playerDefendHide, bool player1Hit, string text)
{
    game game1;
    int X, Y;

    while (true)
    {
        printBoard(playerDefendHide, "Enemy's board");

        while (true)
        {
            cout << text << ", enter the vertical coordinate for the shot : " << endl;
            cin >> Y;

            cout << text << ", enter the horizontal coordinate for the shot:" << endl;
            cin >> X;

            if (isdigit(X) && isdigit(Y) && (X <= UPPERLIM && X >= LOWERLIM) && (Y <= UPPERLIM && Y >= LOWERLIM))
                break;
            else
                cout << "ERROR";
        }

        game1.playerDefendHide = shotBoard(X, Y, playerDefendHide, playerDefend);
        game1.playerDefend = shotPlayer(X, Y, playerDefend);
        game1.isGameOver = gameOver(playerAttack, playerDefend);

        if (playerDefendHide[Y - 1][X - 1] == 'O')
        {
            system("cls");
            printBoard(playerDefendHide, "Enemy's board");

            cout << endl << "You miss";
            Sleep(2000);

            game1.is_player1_hit = false;
            system("cls");

            break;
        }

        system("cls");

        if (game1.isGameOver)
            break;
    }

    return game1;
}

int main()
{
    bool is_player1_hit = true;
    bool is_game_over = false;

    string won_player;

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
            game game1 = playFunc(player1, player2, player2Hide, is_player1_hit, "Player 1");

            player2 = game1.playerDefend;
            player2Hide = game1.playerDefendHide;
            is_player1_hit = game1.is_player1_hit;
            is_game_over = game1.isGameOver;
        }
        else
        {
            game game1 = playFunc(player2, player1, player1Hide, is_player1_hit, "Player 2");

            player1 = game1.playerDefend;
            player1Hide = game1.playerDefendHide;
            is_player1_hit = game1.is_player1_hit;
            is_game_over = game1.isGameOver;
        }
    }

    system("cls");

    won_player = is_player1_win(player1) ? " player 1 " : " player 2 ";
    cout << "Congratulation" << won_player << "!!!" << endl << "YOU WON!!" << endl;

    if (is_player1_win(player1))
        printWinLosePlayer(player1, player2);
    else
        printWinLosePlayer(player2, player1);

    DeleteBoards(player1, player2, player1Hide, player2Hide);

    return 0;
}
