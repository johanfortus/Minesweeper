#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "tile.h"
using namespace std;

class Board {
    vector<vector<Tile>> boardVector;

    int totalMinesPlaced;
public:
    Board(int columnAmount, int rowAmount, int mineAmount);
    void CountAdjacentMines();
    void PrintBoard();
    vector<vector<Tile>> GetBoardVector();
};