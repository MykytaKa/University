#include <iostream>
#include <windows.h>
#include <limits>

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
const string DIRECTIONS[] = { RIGHT, LEFT, UP, DOWN };

class Ship
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

    void setXYDirection()
    {
        bool valid = false;
        while(!valid)
        {
            cout << "Enter the vertical coordinate to place a " << size << " - deck ship:" << endl;
            cin >> y;
            if (cin.fail())
            {
                cout << "Invalid value" << endl;

                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else
            {
                valid = true;
            }
        }

        valid = false;

        while(!valid)
        {
            cout << "Enter the horizontal coordinate to place a " << size << " - deck ship:" << endl;
            cin >> x;
            if (cin.fail())
            {
                cout << "Invalid value" << endl;

                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            else
            {
                valid = true;
            }
        }

        if(size != 1)
        {
            cout << "Enter the direction to place a " << size << " - deck ship:(up,down,left,right)" << endl;
            cin >> direction;
        }
    }

    bool isShipDestroyed(char** player2Board)
    {
        if (size == 1)
        {
            if (player2Board[y - 1][x - 1] == SHIP)
                return false;
            else
                return true;
        }
        else
        {
            int magnifier = (direction == RIGHT) || (direction == DOWN) ? magnifier = 1 : magnifier = -1;
            if (direction == LEFT || direction == RIGHT)
            {
                for (int i = y - 1, j = x - 1, steps = 0; steps < size; j += magnifier)
                {
                    if (player2Board[i][j] == SHIP)
                        return false;
                    steps++;
                }
                return true;
            }
            else
            {
                for (int i = y - 1, j = x - 1, steps = 0; steps < size; i += magnifier)
                {
                    if (player2Board[i][j] == SHIP)
                        return false;
                    steps++;
                }
                return true;
            }
        }
    }
};

class ResourceHandler
{
public:
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

    static void deleteBoard(char** board)
    {
        for (int i = 0; i < SIZEBOARD; i++)
            delete[] board[i];
        delete[] board;
    }

    Ship* createShips() 
    {
        int index = 0;
        Ship* ships = new Ship[SHIPSAMOUNT];
        fillShips(ships, index, 1, 5);
        fillShips(ships, index, 2, 3);
        fillShips(ships, index, 3, 2);
        fillShips(ships, index, 4, 1);
        return ships;
    }

    void fillShips(Ship*& ships, int& index, int shipsAmount, int size)
    {
        for (int i = index, counter = 0; counter < shipsAmount; i++, counter++)
        {
            Ship ship;
            ship.setSize(size);
            ships[i] = ship;
            index++;
        }
    }

    void deleteShips(Ship* ships)
    {
        delete[] ships;
    }
};

class ValueChecker
{
public:
    bool IsValidPosition1DeskShip(Ship ship, char** player)
    {
        for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
            for (int i = ship.getY() == UPPERLIM ? ship.getY() - 1 : ship.getY(), stepsI = 0; i > 0 && stepsI < ship.getSize() + 2; i--, stepsI++)
                if (player[i][j] == SHIP)
                    return true;
        return false;
    }

    bool IsValidPositionRight(Ship ship, char** player)
    {
        int ship_s = ship.getSize();
        if (ship.getX() + ship_s - 1 > UPPERLIM)
            return true;
        if (ship.getX() == LOWERLIM + 1)
            ship_s--;
        for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2; i < SIZEBOARD && i < ship.getY() + 1; i++)
            for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
                if (player[i][j] == SHIP)
                    return true;
        return false;
    }

    bool IsValidPositionLeft(Ship ship, char** player)
    {
        int ship_s = ship.getSize();
        if (ship.getX() - ship_s < LOWERLIM)
            return true;
        if (ship.getX() == UPPERLIM)
            ship_s--;
        for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2; i < SIZEBOARD && i < ship.getY() + 1; i++)
            for (int j = ship.getX() == UPPERLIM ? ship.getX() - 1 : ship.getX(), stepsJ = 0; j >= 0 && stepsJ < ship_s + 2; j--, stepsJ++)
                if (player[i][j] == SHIP)
                    return true;
        return false;
    }

    bool IsValidPositionUp(Ship ship, char** player)
    {
        int ship_s = ship.getSize();
        if (ship.getY() - ship_s < LOWERLIM)
            return true;
        if (ship.getY() == UPPERLIM)
            ship_s--;
        for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
            for (int i = ship.getY() == UPPERLIM ? ship.getY() - 1 : ship.getY(), stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                if (player[i][j] == SHIP)
                    return true;
        return false;
    }

    bool IsValidPositionDown(Ship ship, char** player)
    {
        int ship_s = ship.getSize();
        if (ship.getY() + ship_s - 1 > UPPERLIM)
            return true;
        if (ship.getY() == LOWERLIM + 1)
            ship_s--;
        for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
            for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
                if (player[i][j] == SHIP)
                    return true;
        return false;
    }

    bool IsValidPosition(Ship ship, char** player)
    {
        bool is_error = false;

        if (!(ship.getX() > UPPERLIM || ship.getX() < LOWERLIM) && !(ship.getY() > UPPERLIM || ship.getY() < LOWERLIM))
        {
            if (ship.getSize() == 1)
            {
                is_error = IsValidPosition1DeskShip(ship, player); 
            }
            else
            {
                if (ship.getDirection() == RIGHT)
                {
                    is_error = IsValidPositionRight(ship, player);
                }
                else if (ship.getDirection() == LEFT)
                {
                    is_error = IsValidPositionLeft(ship, player);
                }
                else if (ship.getDirection() == UP)
                {
                    is_error = IsValidPositionUp(ship, player);
                }
                else if (ship.getDirection() == DOWN)
                {
                    is_error = IsValidPositionDown(ship, player);
                }
            }
        }
        else
            is_error = true;

        return is_error;
    }

    bool isValidDirection(string direction)
    {
        for (int i = 0; i < 4; i++)
            if (direction == DIRECTIONS[i])
                return true;
        return false;
    }
};

class Boards 
{
private:
    char** player1Board;
    char** player2Board;
    char** player1HideBoard;
    char** player2HideBoard;
    Ship* player1Ships; 
    Ship* player2Ships; 
    bool isPlayerHit;
    string playerHandlerLabel = "Player 1";
    string playerInfoLabel = "PLAYER'S 2 BOARD";
    friend class Game;
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
    string getPlayerHandlerLabel()
    {
        return playerHandlerLabel;
    }
    string getPlayerInfoLabel()
    {
        return playerInfoLabel;
    }

    char** placeShip(Ship ship, char** player)
    {
        if(ship.getSize() == 1)
            player[ship.getY() - 1][ship.getX() - 1] = SHIP;
        else
        {
            int magnifier = ship.getDirection() == RIGHT || ship.getDirection() == DOWN ? magnifier = 1 : magnifier = -1;

            if (ship.getDirection() == LEFT || ship.getDirection() == RIGHT)
            {
                for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); j += magnifier)
                {
                    player[i][j] = SHIP;
                    steps++;
                }
            }
            else
            {
                for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); i += magnifier)
                {
                    player[i][j] = SHIP;
                    steps++;
                }
            }
        }
        return player;
    }

    void setPlayer1Ships()
    {
        ValueChecker error;
        for (int i = 0; i < SHIPSAMOUNT; i++)
        {
            printBoard(player1Board, "PLAYER'S 1 BOARD");
            while(true)
            {
                player1Ships[i].setXYDirection();
                if (player1Ships[i].getSize() == 1)
                {
                    if (error.IsValidPosition(player1Ships[i], player1Board))
                        cout << "ERROR" << endl;
                    else
                        break;
                }
                else
                {
                    if(!error.isValidDirection(player1Ships[i].getDirection()))
                        cout << "ERROR" << endl;
                    else
                        if (error.IsValidPosition(player1Ships[i], player1Board))
                            cout << "ERROR" << endl;
                        else
                            break;
                }
            }
            player1Board = placeShip(player1Ships[i], player1Board);
            system("cls");
        }
    }

    void setPlayer2Ships()
    {
        ValueChecker error;
        for (int i = 0; i < SHIPSAMOUNT; i++)
        {
            printBoard(player2Board, "PLAYER'S 2 BOARD");
            while (true)
            {
                player2Ships[i].setXYDirection();
                if (player2Ships[i].getSize() == 1)
                {
                    if (error.IsValidPosition(player2Ships[i], player2Board))
                        cout << "ERROR" << endl;
                    else
                        break;
                }
                else
                {
                    if (!error.isValidDirection(player2Ships[i].getDirection()))
                        cout << "ERROR" << endl;
                    else
                        if (error.IsValidPosition(player2Ships[i], player2Board))
                            cout << "ERROR" << endl;
                        else
                            break;
                }
            }
            player2Board = placeShip(player2Ships[i], player2Board);
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

    void circleShips()
    {
        for (int k = 0; k < SHIPSAMOUNT; k++)
        {
            if (player2Ships[k].isShipDestroyed(player2Board))
            {
                int ship_s = player2Ships[k].getSize();
                if (player2Ships[k].getSize() == 1)
                {
                    for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                        for (int i = player2Ships[k].getY() == UPPERLIM ? player2Ships[k].getY() - 1 : player2Ships[k].getY(), stepsI = player2Ships[k].getY() == UPPERLIM ? 1 : 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
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

    Boards()
    {
        ResourceHandler creator;
        player1Board = creator.createBoard();
        player2Board = creator.createBoard();
        player1HideBoard = creator.createBoard();
        player2HideBoard = creator.createBoard();
        player1Ships = creator.createShips();
        player2Ships = creator.createShips();
    }

    ~Boards()
    {
        ResourceHandler deletor;
        deletor.deleteBoard(player1Board);
        deletor.deleteBoard(player2Board);
        deletor.deleteBoard(player1HideBoard);
        deletor.deleteBoard(player2HideBoard);
        deletor.deleteShips(player1Ships);
        deletor.deleteShips(player2Ships);
    }
};

class Game
{
    bool isPlayerHit;
public:
    void shoot(string text, Boards& players)
    {
        int x, y;
        while (true)
        {
            while (true)
            {
                cout << text << ", enter the vertical coordinate for the shot:" << endl;
                cin >> y;
                if (!cin.fail())
                    break;
            }

            cout << text << ", enter the horizontal coordinate for the shot:" << endl;
            cin >> x;

            if ((x <= UPPERLIM && x >= LOWERLIM) && (y <= UPPERLIM && y >= LOWERLIM))
                break;
            else
                cout << "ERROR";
        }

        if (players.player2Board[y - 1][x - 1] == SHIP)
        {
            players.player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
            players.player2Board[y - 1][x - 1] = DESTROYEDSHIP;
            isPlayerHit = true;
        }
        else if (players.player2Board[y - 1][x - 1] == DESTROYEDSHIP)
        {
            players.player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
            players.player2Board[y - 1][x - 1] = DESTROYEDSHIP;
            players.isPlayerHit = true;
        }
        else
        {
            players.player2HideBoard[y - 1][x - 1] = EMPTY;
            players.player2Board[y - 1][x - 1] = EMPTY;
            isPlayerHit = false;
        }
    }

    bool getIsPlayerHit()
    {
        return isPlayerHit;
    }

    void makeTurn(Boards& players)
    {
        swap(players.player1Board, players.player2Board);
        swap(players.player1HideBoard, players.player2HideBoard);
        swap(players.player1Ships, players.player2Ships);
        if (players.playerHandlerLabel == "Player 1")
        {
            players.playerInfoLabel = "PLAYER'S 1 BOARD";
            players.playerHandlerLabel = "Player 2";
        }
        else
        {
            players.playerInfoLabel = "PLAYER'S 2 BOARD";
            players.playerHandlerLabel = "Player 1";
        }
    }

    bool isPlayerLose(char** board)
    {
        for (int i = 0; i < SIZEBOARD; i++)
            for (int j = 0; j < SIZEBOARD; j++)
                if (board[i][j] == SHIP)
                    return false;
        return true;
    }

    bool gameOver(Boards& players)
    {
        return isPlayerLose(players.player1Board) || isPlayerLose(players.player2Board);
    }
};

int main()
{
    Game SeaBattle;
    Boards Players;

    Players.setPlayer1Ships();
    Players.setPlayer2Ships();

    while (!SeaBattle.gameOver(Players))
    {
        Players.printBoard(Players.getPlayer2HideBoard(), Players.getPlayerInfoLabel());
        SeaBattle.shoot(Players.getPlayerHandlerLabel(), Players);
        Players.circleShips();
        system("cls");
        if (!SeaBattle.getIsPlayerHit())
        {
            Players.printBoard(Players.getPlayer2HideBoard(), Players.getPlayerInfoLabel());
            cout << "YOU MISS";
            Sleep(2000);
            SeaBattle.makeTurn(Players);
            system("cls");
        }
    }

    Players.printBoard(Players.getPlayer1Board(), "WINNER");
    cout << endl;
    Players.printBoard(Players.getPlayer2Board(), "LOSER");

    return 0;
}