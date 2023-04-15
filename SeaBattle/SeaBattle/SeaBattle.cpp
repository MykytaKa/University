#include <iostream>
#include <windows.h>
#include <ctype.h>

using namespace std;

const int SIZEBOARD = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;
const string Directions[] = { "right", "left", "up", "down" };  

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

char** shotBoard(int Xshot, int Yshot, char** boardDefendPlayer, char** defendPlayer)
{
    boardDefendPlayer[Yshot - 1][Xshot - 1] = defendPlayer[Yshot - 1][Xshot - 1] == 'S' ? 'X' : 'O';

    return boardDefendPlayer;
}

void printBoard(char** player, string text)
{
    cout << text << endl << endl << "    ";

    for (int i = 0; i < SIZEBOARD; i++)
        cout << i + 1 << "  ";

    cout << endl;

    for (int i = 0; i < SIZEBOARD; i++)
    {
        if (i < SIZEBOARD - 1)
            cout << " ";
        cout << i + 1 << "  ";
        for (int j = 0; j < SIZEBOARD; j++)
            cout << player[i][j] << "  ";
        cout << endl;
    }
}

char** placeShipFunc(char** player, int i, int j, int magnifier, int shipSize)
{
    for  (int steps = 0; steps < shipSize; j += magnifier)
    {
        player[i][j] = 'S';
        steps++;
    }

    return player;
}

char** placeShip(int X, int Y, string direction, char** player, int shipSize) //// TO DO ////////////////////// 
{
    int magnifier = direction  == "right" || direction == "down" ? magnifier = 1 : magnifier = -1; /////// rightm down - enum
    int i = Y - 1;
    int j = X - 1;
    if (direction == "left" || direction == "right")
    {
        player = placeShipFunc(player, i, j, magnifier, shipSize);
    }
    else
    {
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
    for (int i = 0; i < 4; i++)
        if (direction == Directions[i])
            return false;
    return true;
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

void getShipParameter(string tetxPosition, string textSeparator, int shipSize, int number)
{
    cout << "Enter the" << tetxPosition << "to place a " << shipSize << " - deck ship ";

    if (shipSize != 5)
        cout << number + 1;
    cout << textSeparator << endl;
}

shipPosition placeShipFunc(int shipSize, char** player, int number)
{
    shipPosition ship;

    while (true)
    {
        getShipParameter("vertical coordinate", " :", shipSize, number);
        cin >> ship.y;

        getShipParameter("horizontal coordinate", " :", shipSize, number);
        cin >> ship.x;

        while (true && shipSize != 1)
        {
                getShipParameter("direction", " :(up,down,left,right)", shipSize, number);
                cin >> ship.direction;

                if (!isCorrectDirection(ship.direction))  /// TODO /////////////////////////////////////////////
                    break;
                else
                    cout << "ERROR" << endl;
        }

        if (error(ship.x, ship.y, ship.direction, player, shipSize))
            cout << "ERRROOR" << endl;
        else
            break;
    }

    return ship;
}

char** putShips(char** player, int shipSize, int amountShips)
{
    shipPosition ship;
    for (int i = 0; i < amountShips; i++)
    {
        printBoard(player, "Your board");

        ship = placeShipFunc(shipSize, player, i);

        player = placeShip(ship.x, ship.y, ship.direction, player, shipSize); /// ѕередавати усю структуру зам≥сть параметр≥в структури
        system("cls");
    }

    return player;
}

char** placeBoard(char** player)
{
    player = putShips(player, 5, 1);
    player = putShips(player, 3, 2);
    player = putShips(player, 2, 3);
    player = putShips(player, 1, 4);
    return player;
}

char** createBoard()
{
    char** pl = 0;
    pl = new char* [SIZEBOARD];

    for (int i = 0; i < SIZEBOARD; i++)
    {
        pl[i] = new char[SIZEBOARD];
        for (int j = 0; j < SIZEBOARD; j++)
            pl[i][j] = '-';
    }
   
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
    char** playerAttack;
    char** playerDefend;
    char** playerDefendHide;
    bool isGameOver;
    bool is_player1_hit;
};

game playFunc(char** playerAttack, char** playerDefend, char** playerDefendHide, bool player1Hit, string text)
{
    game game1;
    int X, Y;
    bool stop = true;

    while (stop)
    {
        printBoard(playerDefendHide, "Enemy's board");

        while (true) /////// make function //////////////////////////////////
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
        game1.playerDefend = shotBoard(X, Y, playerDefend, playerDefend);
        game1.isGameOver = gameOver(playerAttack, playerDefend);

        if (playerDefendHide[Y - 1][X - 1] == 'O') ///////////////// make function with using adress
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

    game game1;

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
            game1 = playFunc(player1, player2, player2Hide, is_player1_hit, "Player 1"); ///// TO DO /////////////////

            player2 = game1.playerDefend;
            player2Hide = game1.playerDefendHide;
            is_player1_hit = game1.is_player1_hit;
            is_game_over = game1.isGameOver;
        }
        else
        {
            game1 = playFunc(player2, player1, player1Hide, is_player1_hit, "Player 2");

            player1 = game1.playerDefend;
            player1Hide = game1.playerDefendHide;
            is_player1_hit = game1.is_player1_hit;
            is_game_over = game1.isGameOver;
        }
    }

    system("cls");

    won_player = !playerLose(player1) ? " player 1 " : " player 2 ";
    cout << "Congratulation" << won_player << "!!!" << endl << "YOU WON!!" << endl; 

    if (!playerLose(player1))
        printWinLosePlayer(player1, player2);
    else
        printWinLosePlayer(player2, player1);

    DeleteBoards(player1, player2, player1Hide, player2Hide); 

    return 0;
}


















/*#include <iostream>
#include <windows.h>
#include <ctype.h>

using namespace std;  

const int SIZEBOARD = 10; 
const int UPPERLIM = 10; 
const int LOWERLIM = 0; 
const string Directions[] = { "right", "left", "up", "down" }; 
 
class Board
{
public:
    char** PlayerBoard;
    char** PlayerHideBoard;

    Board()
    {
        PlayerBoard = 0;
        PlayerBoard = new char* [SIZEBOARD];

        for (int h = 0; h < SIZEBOARD; h++)
        {
            PlayerBoard[h] = new char[SIZEBOARD];
            for (int w = 0; w < SIZEBOARD; w++)
                PlayerBoard[h][w] = 0;
        }

        for (int i = 0; i < SIZEBOARD; i++)
            for (int j = 0; j < SIZEBOARD; j++)
                PlayerBoard[i][j] = '-';

        PlayerHideBoard = 0;
        PlayerHideBoard = new char* [SIZEBOARD];

        for (int h = 0; h < SIZEBOARD; h++)
        {
            PlayerHideBoard[h] = new char[SIZEBOARD];
            for (int w = 0; w < SIZEBOARD; w++)
                PlayerHideBoard[h][w] = 0;
        }

        for (int i = 0; i < SIZEBOARD; i++)
            for (int j = 0; j < SIZEBOARD; j++)
                PlayerHideBoard[i][j] = '-';
    }

    ~Board()
    {
        for (int i = 0; i < SIZEBOARD; i++)
            delete[] PlayerBoard[i];
        delete[] PlayerBoard;

        for (int i = 0; i < SIZEBOARD; i++)
            delete[] PlayerHideBoard[i];
        delete[] PlayerHideBoard;
    }

    void printBoard(char** board, string text)
    {
        cout << text << endl << endl << "    ";

        for (int i = 0; i < SIZEBOARD; i++)
            cout << i + 1 << "  ";

        cout << endl;

        for (int i = 0; i < SIZEBOARD - 1; i++)
        {
            cout << " " << i + 1 << "  ";
            for (int j = 0; j < SIZEBOARD; j++)
                cout << board[i][j] << "  ";
            cout << endl;
        }

        for (int i = SIZEBOARD - 1; i < SIZEBOARD; i++)
        {
            cout << i + 1 << "  ";
            for (int j = 0; j < SIZEBOARD; j++)
                cout << board[i][j] << "  ";
            cout << endl;
        }
    }
};

class Ship
{
public:
    int x, y, size;
    string direction;

    void setPosition()
    {
        cout << "Enter the vertical coordinate to place a " << size << "-deck ship ";

        if (size != 5)
            cout << 0 + 1 << " :" << endl;
        else
            cout << " :" << endl;

        cin >> y;

        cout << "Enter the horizontal coordinate to place a " << size << "-deck ship ";

        if (size != 5)
            cout << 0 + 1 << " :" << endl;
        else
            cout << " :" << endl;

        cin >> x;

        if (size != 1)
        {
            cout << "Enter the direction to place a " << size << "-deck ship ";

            if (size != 5)
                cout << 0 + 1 << " :(up,down,left,right)" << endl;
            else
                cout << " :(up,down,left,right)" << endl;

            cin >> direction;
        }
    }

    char** place(char** pl)
    {
        if (direction == "left" || direction == "right")
        {
            int magnifier = direction == "right" ? magnifier = 1 : magnifier = -1;

            for (int i = y - 1, j = x - 1, steps = 0; steps < size; j += magnifier)
            {
                pl[i][j] = 'S';
                steps++;
            }
        }
        else
        {
            int magnifier = direction == "up" ? magnifier = -1 : magnifier = 1;

            for (int i = y - 1, j = x - 1, steps = 0; steps < size; i += magnifier)
            {
                pl[i][j] = 'S';
                steps++;
            }
        }

        return pl;
    }
};

bool isCorrectPosition(Ship ship, Board pl)
{
    bool is_error = false;

    if (!(ship.x > UPPERLIM || ship.x < LOWERLIM) && !(ship.y > UPPERLIM || ship.y < LOWERLIM))
    {
        if (ship.size == 1)
        {
            for (int j = ship.x == LOWERLIM + 1 ? ship.x - 1 : ship.x - 2; j < SIZEBOARD && j < ship.x + 1; j++)
                for (int i = ship.y == UPPERLIM ? ship.y - 1 : ship.y, stepsI = 0; i > 0 && stepsI < ship.size + 2; i--, stepsI++)
                    if (pl.PlayerBoard[i][j] == 'S')
                        is_error = true;
        }
        else
        {
            if (ship.direction == "right")
            {
                if (ship.x + ship.size - 1 > UPPERLIM)
                    is_error = true;
                if (ship.x == LOWERLIM + 1)
                    ship.size--;
                for (int i = ship.y == LOWERLIM + 1 ? ship.y - 1 : ship.y - 2; i < SIZEBOARD && i < ship.y + 1; i++)
                    for (int j = ship.y == LOWERLIM + 1 ? ship.x - 1 : ship.x - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship.size + 2; j++, stepsJ++)
                        if (pl.PlayerBoard[i][j] == 'S')
                            is_error = true;

            }
            else if (ship.direction == "left")
            {
                if (ship.x - ship.size < LOWERLIM)
                    is_error = true;
                if (ship.x == UPPERLIM)
                    ship.size--;
                for (int i = ship.y == LOWERLIM + 1 ? ship.y - 1 : ship.y - 2; i < SIZEBOARD && i < ship.y + 1; i++)
                    for (int j = ship.x == UPPERLIM ? ship.x - 1 : ship.x, stepsJ = 0; j >= 0 && stepsJ < ship.size + 2; j--, stepsJ++)
                        if (pl.PlayerBoard[i][j] == 'S')
                            is_error = true;
            }
            else if (ship.direction == "up")
            {
                if (ship.y - ship.size < LOWERLIM)
                    is_error = true;
                if (ship.y == UPPERLIM)
                    ship.size--;
                for (int j = ship.x == LOWERLIM + 1 ? ship.x - 1 : ship.x - 2; j < SIZEBOARD && j < ship.x + 1; j++)
                    for (int i = ship.y == UPPERLIM ? ship.y - 1 : ship.y, stepsI = 0; i > 0 && stepsI < ship.size + 2; i--, stepsI++)
                        if (pl.PlayerBoard[i][j] == 'S')
                            is_error = true;
            }
            else if (ship.direction == "down")
            {
                if (ship.y + ship.size - 1 > UPPERLIM)
                    is_error = true;
                if (ship.y == LOWERLIM + 1)
                    ship.size--;
                for (int j = ship.x == LOWERLIM + 1 ? ship.x - 1 : ship.x - 2; j < SIZEBOARD && j < ship.x + 1; j++)
                    for (int i = ship.y == LOWERLIM + 1 ? ship.y - 1 : ship.y - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship.size + 2; i++, stepsI++)
                        if (pl.PlayerBoard[i][j] == 'S')
                            is_error = true;
            }
        }
    }
    else
        is_error = true;

    return is_error;
}

int main()
{
    //////////////////////////////////
    //                              //
    // «робити масив з клас≥в Ship  //
    //                              //
    //////////////////////////////////

    Board pl1, pl2;
    Ship ship;

    ship.size = 1;

    pl1.printBoard(pl1.PlayerBoard, "Player's 1 board");

    while (true)
    {
        ship.setPosition();
        if (!isCorrectPosition(ship, pl1))
            break;
    }

    pl1.PlayerBoard = ship.place(pl1.PlayerBoard);

    pl1.printBoard(pl1.PlayerBoard, "Player's 1 board");

    return 0;
}*/
