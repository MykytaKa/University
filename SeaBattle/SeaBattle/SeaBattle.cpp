#include <iostream>
#include <windows.h>

using namespace std;

const int SIZEBOARD = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;
const int SHIPSAMOUNT = 10;
const char EMPTY = 'O';
const char SHIP = 'S';
const char DESTROYEDSHIP = 'X';
const char UNKNOWNCELL = '-';

const string RIGHT = "right";
const string LEFT = "left";
const string UP = "up";
const string DOWN = "down";
const string Directions[] = { RIGHT, LEFT, UP, DOWN };

char** createBoard()
{
    char** board;
    board = new char* [SIZEBOARD];
    for (int i = 0; i < SIZEBOARD; i++)
    {
        board[i] = new char[SIZEBOARD];
        for (int j = 0; j < SIZEBOARD; j++)
            board[i][j] = UNKNOWNCELL;
    }

    return board;
}

void deleteBoard(char** board)
{
    for (int i = 0; i < SIZEBOARD; i++)
        delete[] board[i];
    delete[] board;
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
                    if (player[i][j] == SHIP)
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
                        if (player[i][j] == SHIP)
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
                        if (player[i][j] == SHIP)
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
                        if (player[i][j] == SHIP)
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
                        if (player[i][j] == SHIP)
                            is_error = true;
            }
        }
    }
    else
        is_error = true;

    return is_error;
}

char** placeShip(int x, int y, string direction, char** player, int shipSize)
{
    int magnifier = direction == RIGHT || direction == DOWN ? magnifier = 1 : magnifier = -1;
    if (direction == LEFT || direction == RIGHT)
    {
        for (int i = y - 1, j = x - 1, steps = 0; steps < shipSize; j += magnifier)
        {
            player[i][j] = SHIP;
            steps++;
        }
    }
    else
    {
        for (int i = y - 1, j = x - 1, steps = 0; steps < shipSize; i += magnifier)
        {
            player[i][j] = SHIP;
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

void getShipParameter(string tetxPosition, string textSeparator, int shipSize)
{
    cout << "Enter the" << tetxPosition << "to place a " << shipSize << " - deck ship" << textSeparator << endl;
}

class ship
{
    int x, y, size;
    string direction;
public:
    void setSize(int Size)
    {
        size = Size; 
    }
    int getSize()
    {
        return size;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    string getDirection()
    {
        return direction;
    }
    char** setXYDirection(char** board)
    {
        while (true)
        {
            getShipParameter(" vertical coordinate ", ":", size);
            cin >> y;

            getShipParameter(" horizontal coordinate ", ":", size);
            cin >> x;

            while (true && size != 1)
            {
                getShipParameter(" direction ", ":(up,down,left,right)", size);
                cin >> direction;

                if (!isCorrectDirection(direction))
                    break;
                else
                    cout << "ERROR" << endl;
            }

            if (error(x, y, direction, board, size))
                cout << "ERRROOR" << endl;
            else
                break;
        }
        board = placeShip(x, y, direction, board, size);

        return board;
    }
};

void fillShips(ship*& ships, int& index, int shipsAmount, int size)
{
    for (int i = index, counter = 0; counter < shipsAmount; i++, counter++)
    {
        ship Ship;
        Ship.setSize(size);
        ships[i] = Ship;
        index++;
    }
}

ship* createShips()
{
    int index = 0;
    ship* ships = new ship[SHIPSAMOUNT];
    fillShips(ships, index, 1, 5);
    fillShips(ships, index, 2, 3);
    fillShips(ships, index, 3, 2);
    fillShips(ships, index, 4, 1);
    return ships;
}

void deleteShips(ship* Ship)
{
    delete[] Ship;
}

bool playerLose(char** board)
{
    for (int i = 0; i < SIZEBOARD; i++)
        for (int j = 0; j < SIZEBOARD; j++)
            if (board[i][j] == SHIP)
                return false;
    return true;
}

bool ShipDestroyed(char** player2Board, ship Ship)
{
    if (Ship.getSize() == 1)
    {
        if (player2Board[Ship.getY() - 1][Ship.getX() - 1] == SHIP)
            return false;
        return true;
    }
    else
    {
        int magnifier = Ship.getDirection() == RIGHT || Ship.getDirection() == DOWN ? magnifier = 1 : magnifier = -1;
        if (Ship.getDirection() == LEFT || Ship.getDirection() == RIGHT)
        {
            for (int i = Ship.getY() - 1, j = Ship.getX() - 1, steps = 0; steps < Ship.getSize(); j += magnifier)
            {
                if (player2Board[i][j] == SHIP)
                    return false;
                steps++;
            }
            return true;
        }
        else
        {
            for (int i = Ship.getY() - 1, j = Ship.getX() - 1, steps = 0; steps < Ship.getSize(); i += magnifier)
            {
                if (player2Board[i][j] == SHIP)
                    return false;
                steps++;
            }
            return true;
        }
    }
}

class game
{
private:
    char** player1Board;
    char** player2Board;
    char** player1HideBoard;
    char** player2HideBoard;
    ship* player1Ships;
    ship* player2Ships;
    bool isPlayerHit;
public:
    char** getPlayer2HideBoard()
    {
        return player2HideBoard;
    }
    char** getPlayer1Board()
    {
        return player1Board;
    }
    char** getPlayer2Board()
    {
        return player2Board;
    }

    void makeTurn()
    {
        swap(player1Board, player2Board);
        swap(player1HideBoard, player2HideBoard);
        swap(player1Ships, player2Ships);
    }

    void cirleShips()
    {
        for (int k = 0; k < 2; k++)
        {
            if (ShipDestroyed(player2Board, player2Ships[k]))
            {
                int ship_s = player2Ships[k].getSize();
                if (player2Ships[k].getSize() == 1)
                {
                    for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                        for (int i = player2Ships[k].getY() == UPPERLIM ? player2Ships[k].getY() - 1 : player2Ships[k].getY(), stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                            if (player2Board[i][j] == UNKNOWNCELL)
                            {
                                player2Board[i][j] = EMPTY;
                                player2HideBoard[i][j] = EMPTY;
                            }
                }
                else
                {
                    if (player2Ships[k].getDirection() == RIGHT)
                    {
                        if (player2Ships[k].getX() == LOWERLIM + 1)
                            ship_s--;
                        for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2; i < SIZEBOARD && i < player2Ships[k].getY() + 1; i++)
                            for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
                                if (player2Board[i][j] == UNKNOWNCELL)
                                {
                                    player2Board[i][j] = EMPTY;
                                    player2HideBoard[i][j] = EMPTY;
                                }
                    }
                    else if (player2Ships[k].getDirection() == LEFT)
                    {
                        if (player2Ships[k].getX() == UPPERLIM)
                            ship_s--;
                        for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2; i < SIZEBOARD && i < player2Ships[k].getY() + 1; i++)
                            for (int j = player2Ships[k].getX() == UPPERLIM ? player2Ships[k].getX() - 1 : player2Ships[k].getX(), stepsJ = 0; j >= 0 && stepsJ < ship_s + 2; j--, stepsJ++)
                                if (player2Board[i][j] == UNKNOWNCELL)
                                {
                                    player2Board[i][j] = EMPTY;
                                    player2HideBoard[i][j] = EMPTY;
                                }
                    }
                    else if (player2Ships[k].getDirection() == UP)
                    {
                        if (player2Ships[k].getY() == UPPERLIM)
                            ship_s--;
                        for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                            for (int i = player2Ships[k].getY() == UPPERLIM ? player2Ships[k].getY() - 1 : player2Ships[k].getY(), stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                                if (player2Board[i][j] == UNKNOWNCELL)
                                {
                                    player2Board[i][j] = EMPTY;
                                    player2HideBoard[i][j] = EMPTY;
                                }
                                    
                    }
                    else if (player2Ships[k].getDirection() == DOWN)
                    {
                        if (player2Ships[k].getY() == LOWERLIM + 1)
                            ship_s--;
                        for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                            for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
                                if (player2Board[i][j] == UNKNOWNCELL)
                                {
                                    player2Board[i][j] = EMPTY;
                                    player2HideBoard[i][j] = EMPTY;
                                }
                    }
                } 
            }
        }
    }

    void shoot(string text)
    {
        int x, y;
        while (true)
        {
            cout << text << ", enter the vertical coordinate for the shot:" << endl;
            cin >> y;

            cout << text << ", enter the horizontal coordinate for the shot:" << endl;
            cin >> x;

            if ((x <= UPPERLIM && x >= LOWERLIM) && (y <= UPPERLIM && y >= LOWERLIM))
                break;
            else
                cout << "ERROR";
        }

        if (player2Board[y - 1][x - 1] == SHIP)
        {
            player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
            player2Board[y - 1][x - 1] = DESTROYEDSHIP;
            isPlayerHit = true;
        }
        else if (player2Board[y - 1][x - 1] == DESTROYEDSHIP)
        {
            player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
            player2Board[y - 1][x - 1] = DESTROYEDSHIP;
            isPlayerHit = true;
        }
        else
        {
            player2HideBoard[y - 1][x - 1] = EMPTY;
            player2Board[y - 1][x - 1] = EMPTY;
            isPlayerHit = false;
        }
    }

    bool getIsPlayerHit()
    {
        return isPlayerHit;
    }

    bool gameOver()
    {
        return playerLose(player1Board) || playerLose(player2Board);
    }

    void setPlayer1Ships()
    {
        for (int i = 0; i < SHIPSAMOUNT; i++)
        {
            printBoard(player1Board, "PLAYER'S 1 BOARD");
            player1Ships[i].setXYDirection(player1Board);
            system("cls");
        }
    }

    void setPlayer2Ships()
    {
        for (int i = 0; i < SHIPSAMOUNT; i++)
        {
            printBoard(player2Board, "PLAYER'S 2 BOARD");
            player2Ships[i].setXYDirection(player2Board);
            system("cls");
        }
    }

    void printBoard(char** board, string text)
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
                cout << board[i][j] << "  ";
            cout << endl;
        }

        cout << endl;
    }

    game()
    {
        player1Board = createBoard();
        player2Board = createBoard();
        player1HideBoard = createBoard();
        player2HideBoard = createBoard();
        player1Ships = createShips();
        player2Ships = createShips();
    }

    ~game()
    {
        deleteBoard(player1Board);
        deleteBoard(player2Board);
        deleteBoard(player1HideBoard);
        deleteBoard(player2HideBoard);
        deleteShips(player1Ships);
        deleteShips(player2Ships);
    }
}; 

int main()
{
    game Game;
    string text = "Player 1";
    string label = "PLAYER'S 2 BOARD";

    Game.setPlayer1Ships();
    Game.setPlayer2Ships();

    while (!Game.gameOver()) 
    {
        Game.printBoard(Game.getPlayer2HideBoard(), label);
        Game.shoot(text);
        Game.cirleShips();
        system("cls");
        if (!Game.getIsPlayerHit()) 
        {
            Game.printBoard(Game.getPlayer2HideBoard(), label);
            cout << "YOU MISS" << endl;
            Sleep(2000);
            Game.makeTurn();
            if (text == "Player 1")
            {
                label = "PLAYER'S 1 BOARD";
                text = "Player 2";
            }
            else
            {
                label = "PLAYER'S 2 BOARD";
                text = "Player 1";
            }
            system("cls");
        }
    }

    Game.printBoard(Game.getPlayer1Board(), "WINNER");
    cout << endl;
    Game.printBoard(Game.getPlayer2Board(), "LOSER");

    return 0;
}