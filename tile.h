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
    bool revealed = true;
    bool flagged = false;
    bool numbered = false;
public:
    Tile(int i, int j);
    string GetTileData();
    void SetTileData(string newTileData);
    string GetNumberData();
    void SetNumberData(string newNumberData);

    bool GetMineStatus();
    void SetMineStatus(bool mineStatus);

    bool GetRevealStatus();
    void SetRevealStatus(bool revealStatus);

    bool GetFlaggedStatus();
    void SetFlaggedStatus(bool flaggedStatus);

    bool GetNumberStatus();
    void SetNumberStatus(bool numberStatus);


    sf::Sprite& GetSprite();
};