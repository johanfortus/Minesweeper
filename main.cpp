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
            switch(event.type){
                case sf::Event::MouseButtonPressed:
                    int i, j;
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        cout << "X: " << event.mouseButton.x << " Y: " << event.mouseButton.y << endl;
                        cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                        i = floor(event.mouseButton.y / 32);
                        j = floor(event.mouseButton.x / 32);
                        if(!boardVector[i][j].GetFlaggedStatus())
                            boardVector[i][j].SetRevealStatus(true);
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right) {
                        cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                        i = floor(event.mouseButton.y / 32);
                        j = floor(event.mouseButton.x / 32);
                        if(!boardVector[i][j].GetFlaggedStatus())
                            boardVector[i][j].SetFlaggedStatus(true);
                        else
                            boardVector[i][j].SetFlaggedStatus(false);
                    }
                    break;
            }
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

                    // If Tile Is a Mine, Draw Mine Sprite
                    if(boardVector[i][j].GetMineStatus()){
                        sf::Sprite tileMineSprite(TextureManager::GetTexture("mine"));
                        tileMineSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                        window.draw(tileMineSprite);
                    }

                    // If Tile Is a Number, Draw Number Sprite
                    else if(boardVector[i][j].GetTileData() != "0"){
                        string numberData = boardVector[i][j].GetTileData();
                        string numberTextureName = "number_" + numberData;
                        sf::Sprite tileNumberDataSprite(TextureManager::GetTexture(numberTextureName));
                        tileNumberDataSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                        window.draw(tileNumberDataSprite);
                    }
                }

                // If Tile is hidden
                else{
                    sf::Sprite tileHiddenSprite(TextureManager::GetTexture("tile_hidden"));
                    tileHiddenSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                    window.draw(tileHiddenSprite);

                    // If Tile is Flagged
                    if(boardVector[i][j].GetFlaggedStatus()) {
                        sf::Sprite tileFlaggedSprite(TextureManager::GetTexture("flag"));
                        tileFlaggedSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                        window.draw(tileFlaggedSprite);
                    }
                }

            }
        }

        // Draw Test #3 Button
        sf::Sprite testThreeBtn(TextureManager::GetTexture("test_3"));
        testThreeBtn.setPosition(sf::Vector2f(width - 64, height - 100)); // instead of height - 96 bc it looks slightly better
        window.draw(testThreeBtn);


        window.display();
    }
    TextureManager::Clear();
    return 0;
}
    // height - 64
    // width - 64
