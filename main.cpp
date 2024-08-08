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
#include "tile.h"
using namespace std;
void adjacent();
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

    Board board(columns, rows, mineCount);
    board.CountAdjacentMines();
    board.PrintBoard();
    vector<vector<Tile>> boardVector = board.GetBoardVector();

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


//    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
//    tileHiddenSprite.setPosition(sf::Vector2f(0,32));

    sf::Sprite tileRevealedSprite(TextureManager::GetTexture("tile_revealed"));
    tileRevealedSprite.setPosition(sf::Vector2f(0,0));





    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        for(int i = 0; i < boardVector.size(); i++){
            for(int j = 0; j < boardVector[i].size(); j++){

                // If Tile is revealed
                if(boardVector[i][j].GetRevealStatus()){
                    // Draw Revealed Tile Sprite
                    sf::Sprite tileRevealedSprite(TextureManager::GetTexture("tile_revealed"));
                    tileRevealedSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                    window.draw(tileRevealedSprite);
                }

                // If Tile is hidden
                else{
                    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
                    tileHiddenSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                    window.draw(tileHiddenSprite);
                }
            }
        }

//        window.draw(tileHiddenSprite);
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


// Edge Cases
void test(){
    vector<vector<string>> myArray;
    myArray = {
            {"L", "•", "•", "B", "C"},
            {"•", "B", "•", "•", "•"},
            {"X", "X", "X", "X", "$"}};
//    cout << myArray[0][0] << endl;

    for(int i = 0; i < myArray.size(); i++){
        for(int j = 0; j < myArray[i].size(); j++){


            // Top Left Corner
            if(i == 0 && j == 0){
                cout << myArray[i][j];
            }

                // Top Right Corner
            else if(i == 0 && j == myArray[i].size() - 1){
                cout << myArray[i][j];
            }

                // Bottom Left Corner
            else if(j == 0 && i == myArray.size() - 1){
                cout << myArray[i][j];
            }

                // Bottom Right Corner
            else if(j == myArray[i].size() - 1 && i == myArray.size() - 1){
                cout << myArray[i][j];
            }

                // Top Edge
            else if(i == 0){
                cout << myArray[i][j];
            }

                // Bottom Edge
            else if(i == myArray.size() - 1){
                cout << myArray[i][j];
            }

                // Left Edge
            else if(j == 0){
                cout << myArray[i][j];
            }

                // Right Edge
            else if(j == myArray[i].size() - 1){
                cout << myArray[i][j];
            }

            else {
                cout << myArray[i][j];
            }
        }
        cout << endl;
    }
};

void adjacent(){
    vector<vector<string>> myArray;
    myArray = {
            {"L", "•", "•", "B", "C"},
            {"•", "B", "•", "•", "•"},
            {"X", "X", "X", "X", "$"}};
//    cout << myArray[0][0] << endl;

    int bombCount = 0;
    for(int i = 0; i < myArray.size(); i++){
        for(int j = 0; j < myArray[i].size(); j++){


            // Top Left Corner
            if(i == 0 && j == 0){
                if(myArray[i][j + 1] == "B") // Right
                    bombCount++;
                if(myArray[i + 1][j + 1] == "B") // Bottom Right
                    bombCount++;
                if(myArray[i + 1][j] == "B") // Bottom
                    bombCount++;
                if(myArray[i + 1][j - 1] == "B") // Bottom Left
                    bombCount++;
                if(myArray[i][j - 1] == "B") // Left
                    bombCount++;
                if(myArray[i - 1][j - 1] == "B") // Top Left
                    bombCount++;
                if(myArray[i - 1][j] == "B") // Top
                    bombCount++;
                if(myArray[i - 1][j + 1] == "B") // Top Right
                    bombCount++;
            }
        }
    }
    cout << "bombCount: " << bombCount << endl;
}