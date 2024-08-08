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

Tile::Tile(int i, int j) {
    TileData = "•";
}

string Tile::GetTileData() {
    return TileData;
}

void Tile::SetTileData(string newTileData) {
    TileData = newTileData;
}