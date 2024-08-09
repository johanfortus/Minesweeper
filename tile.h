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
    string tileData;
    vector<sf::Sprite> tileSpriteData;
    int rowPos;
    int columnPos;
    int rowWindowPos;
    int columnWindowPos;
    string numberData = "";

    bool mine = false;
    bool revealed = false;
    bool flagged = false;
    bool numbered = false;

public:
    Tile(int i, int j);

    string GetTileData();
    bool GetMineStatus();
    bool GetRevealStatus();
    bool GetFlaggedStatus();

    void SetTileData(string newTileData);
    void SetMineStatus(bool mineStatus);
    void SetRevealStatus(bool revealStatus);
    void SetFlaggedStatus(bool flaggedStatus);
};