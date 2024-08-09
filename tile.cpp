#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "tile.h"
#include "texturemanager.h"
using namespace std;

Tile::Tile(int i, int j) {
    tileData = "•";
    rowPos = i;
    columnPos = j;
}
string Tile::GetTileData() {
    return tileData;
}
bool Tile::GetMineStatus() {
    return mine;
}
bool Tile::GetRevealStatus() {
    return revealed;
}
bool Tile::GetFlaggedStatus() {
    return flagged;
}

void Tile::SetTileData(string newTileData) {
    tileData = newTileData;
}
void Tile::SetMineStatus(bool mineStatus) {
    mine = mineStatus;
}
void Tile::SetRevealStatus(bool revealStatus) {
    revealed = revealStatus;
}
void Tile::SetFlaggedStatus(bool flaggedStatus) {
    flagged = flaggedStatus;
}