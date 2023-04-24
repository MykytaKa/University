#include <iostream>
#include <windows.h>
#include <ctype.h>

using namespace std;

const int SIZEBOARD = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;

const string RIGHT = "right";
const string LEFT = "left";
const string UP = "up";
const string DOWN = "down";
const string Directions[] = { RIGHT, LEFT, UP, DOWN };

struct shipPosition
{
public:
    int x;
    int y;
    string direction;
};

struct game
{
public:
    char** playerAttack;
    char** playerDefend;
    char** playerDefendHide;
    bool isGameOver;
    bool is_player1_hit;
};

struct ShotPosition
{
public:
    int x;
    int y;
};

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

char** shotBoard(ShotPosition shot, char** boardDefendPlayer, char** defendPlayer)
{
    boardDefendPlayer[shot.y - 1][shot.x - 1] = defendPlayer[shot.y - 1][shot.x - 1] == 'S' ? 'X' : 'O';

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

    cout << endl;
}

char** placeShip(shipPosition ship, char** player, int shipSize)
{
    int magnifier = ship.direction  == RIGHT || ship.direction == DOWN ? magnifier = 1 : magnifier = -1;
    if (ship.direction == LEFT || ship.direction == RIGHT)
    {
        for (int i = ship.y - 1, j = ship.x - 1, steps = 0; steps < shipSize; j += magnifier)
        {
            player[i][j] = 'S';
            steps++;
        }
    }
    else
    {
        for (int i = ship.y - 1, j = ship.x - 1, steps = 0; steps < shipSize; i += magnifier)
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
            if (direction == RIGHT)
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
            else if (direction == LEFT)
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
            else if (direction == UP)
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
            else if (direction == DOWN)
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

void getShipParameter(string tetxPosition, string textSeparator, int shipSize, int number)
{
    cout << "Enter the" << tetxPosition << "to place a " << shipSize << " - deck ship";

    if (shipSize != 5)
        cout << number + 1;
    cout << textSeparator << endl;
}

shipPosition placeShipFunc(int shipSize, char** player, int number) 
{
    shipPosition ship;

    while (true)
    {
        getShipParameter(" vertical coordinate ", ":", shipSize, number);
        cin >> ship.y;

        getShipParameter(" horizontal coordinate ", ":", shipSize, number);
        cin >> ship.x;

        while (true && shipSize != 1)
        {
                getShipParameter(" direction ", ":(up,down,left,right)", shipSize, number);
                cin >> ship.direction;
                
                if (!isCorrectDirection(ship.direction))  
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

        player = placeShip(ship, player, shipSize); 
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

ShotPosition EnterShotPosition(string text) 
{
    ShotPosition shot;

    while (true)
    {
        cout << text << ", enter the vertical coordinate for the shot : " << endl;
        cin >> shot.y;

        cout << text << ", enter the horizontal coordinate for the shot:" << endl;
        cin >> shot.x;

        if ((shot.x <= UPPERLIM && shot.x >= LOWERLIM) && (shot.y <= UPPERLIM && shot.y >= LOWERLIM))
            break;
        else
            cout << "ERROR";
    }

    return shot;
}

void func(bool& stop, game& game1)
{
    system("cls");
    printBoard(game1.playerDefendHide, "Enemy's board");

    cout << endl << "You miss";
    Sleep(2000);

    game1.is_player1_hit = false;
    system("cls");

    stop = false;
}
game playFunc(char** playerAttack, char** playerDefend, char** playerDefendHide, bool player1Hit, string text)
{
    game game1;
    ShotPosition shot;
    bool stop = true;

    while (stop)
    {
        printBoard(playerDefendHide, "Enemy's board");

        shot = EnterShotPosition(text);
        
        game1.playerDefendHide = shotBoard(shot, playerDefendHide, playerDefend);
        game1.playerDefend = shotBoard(shot, playerDefend, playerDefend);
        game1.isGameOver = gameOver(playerAttack, playerDefend);

        if (game1.playerDefendHide[shot.y - 1][shot.x - 1] == 'O')
        {
            func(stop, game1);
        }

        system("cls");

        if (game1.isGameOver)
            stop = false;
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
            game1 = playFunc(player1, player2, player2Hide, is_player1_hit, "Player 1");

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
