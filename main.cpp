#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "random.h"
#include "texturemanager.h"
#include "board.h"
using namespace std;

int main(){

    ifstream inFile("config.cfg");

    string lineFromFile;

    int columns;
    int width;
    inFile >> columns;
    width = columns * 32;
    cout << "Columns: " << columns << endl;
    cout << "Width: " << width << endl;

    int rows;
    int height;
    inFile >> rows;
    height = (rows * 32) + 100;
    cout << "Rows: " << rows << endl;
    cout << "Height: " << height << endl;

    int mineCount;
    inFile >> mineCount;
    cout << "Mine Count: " << mineCount << endl;

    int tileCount;
    tileCount = columns * rows;
    cout << "Tile Count: " << tileCount << endl;
    inFile.close();

    cout << "Random Number: " << Random::Int(0, 200) << endl;
    cout << "Random Number: " << Random::Int(0, 200) << endl;

    Board board(columns, rows);

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
    tileHiddenSprite.setPosition(sf::Vector2f(0,100));




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(tileHiddenSprite);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}

// Two ways to load in a texture & create sprite

// Prof Fox
//    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));

// Default
//    sf::Texture tileHidden;
//    tileHidden.loadFromFile("images/tile_hidden.png");
//    sf::Sprite tileHiddenSprite(tileHidden);