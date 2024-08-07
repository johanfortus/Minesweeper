#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
using namespace std;

class Board {
    vector<vector<string>> boardVector;
    int totalMinesPlaced;
public:
    Board(int columnAmount, int rowAmount, int mineAmount);
};