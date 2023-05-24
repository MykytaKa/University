#pragma once
#include <iostream>

const int SIZEBOARD = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;
const int SHIPSAMOUNT = 10;
const char EMPTY = 'O';
const char SHIP = 'S';
const char DESTROYEDSHIP = 'X';
const char UNKNOWNCELL = '-';

const std::string RIGHT = "right";
const std::string LEFT = "left";
const std::string UP = "up";
const std::string DOWN = "down"; 
const std::string DIRECTIONS[] = { RIGHT, LEFT, UP, DOWN };