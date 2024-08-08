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
    int totalAdjacentMines;
public:
    Board(int columnAmount, int rowAmount, int mineAmount);
    void CountAdjacentMines();
    int GetTotalAdjacentMines();
    void PrintBoard();
    vector<vector<Tile>> GetBoardVector();
};