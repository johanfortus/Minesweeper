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

void Tile::SetTileData(string newTileData) {
    tileData = newTileData;
}

string Tile::GetNumberData() {
    return numberData;
}
void Tile::SetNumberData(string newNumberData) {
    numberData = newNumberData;
}


//void SetNumberDataSprite(string number) {
//    if(number == "1")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_1"));
//    if(number == "2")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_2"));
//    if(number == "3")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_3"));
//    if(number == "4")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_4"));
//    if(number == "5")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_5"));
//    if(number == "6")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_6"));
//    if(number == "7")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_7"));
//    if(number == "8")
//        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture("number_8"));
//}




bool Tile::GetMineStatus() {
    return mine;
}
bool Tile::GetRevealStatus() {
    return revealed;
}
bool Tile::GetFlaggedStatus() {
    return flagged;
}
bool Tile::GetNumberStatus() {
    return numbered;
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
void Tile::SetNumberStatus(bool numberStatus) {
    numbered = numberStatus;
}






//sf::Sprite& Tile::GetSprite() {
//    return TileSprite;
//}