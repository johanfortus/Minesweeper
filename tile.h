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

class Tile {
    string TileData;
public:
    Tile(int i, int j);
    string GetTileData();
    void SetTileData(string newTileData);
};