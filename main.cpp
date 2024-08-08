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

void revealBlankTiles(int i, int j, int columns, int rows, vector<vector<Tile>>& boardVector);

int main(){

    ifstream inFile("config.cfg");

    string lineFromFile;

    int columns;
    int width;
    inFile >> columns;
    width = columns * 32;
//    cout << "Columns: " << columns << endl;
//    cout << "Width: " << width << endl;

    int rows;
    int height;
    inFile >> rows;
    height = (rows * 32) + 100;
//    cout << "Rows: " << rows << endl;
//    cout << "Height: " << height << endl;

    int mineCount;
    inFile >> mineCount;
//    cout << "Mine Count: " << mineCount << endl;

    int tileCount;
    tileCount = columns * rows;
//    cout << "Tile Count: " << tileCount << endl;
    inFile.close();

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

    bool gameOver = false;
    bool gameWon = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(!gameOver && !gameWon){
                switch(event.type){
                    case sf::Event::MouseButtonPressed:
                        int i, j;
                        if(event.mouseButton.button == sf::Mouse::Left) {
//                            cout << "X: " << event.mouseButton.x << " Y: " << event.mouseButton.y << endl;
//                            cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                            i = floor(event.mouseButton.y / 32);
                            j = floor(event.mouseButton.x / 32);

                            if(boardVector[i][j].GetMineStatus()){
                                gameOver = true;
                                boardVector[i][j].SetRevealStatus(true);
                            }
                            else if(!boardVector[i][j].GetFlaggedStatus() && boardVector[i][j].GetTileData() != "0"){
                                boardVector[i][j].SetRevealStatus(true);
                            }
                            else if(boardVector[i][j].GetTileData() == "0"){
                                revealBlankTiles(i, j, columns, rows, boardVector);
                            }
                        }
                        else if(event.mouseButton.button == sf::Mouse::Right) {
//                            cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                            i = floor(event.mouseButton.y / 32);
                            j = floor(event.mouseButton.x / 32);

                            // Right Clicking On Tile - Flag Tile (boardVector[i][j]) if not flagged or unflag if flagged
                            if(!boardVector[i][j].GetFlaggedStatus())
                                boardVector[i][j].SetFlaggedStatus(true);
                            else
                                boardVector[i][j].SetFlaggedStatus(false);
                        }
                        break;
                }
            }
        }
        window.clear(sf::Color::White);
        for(int i = 0; i < boardVector.size(); i++){
            for(int j = 0; j < boardVector[i].size(); j++){

                if(gameOver) {
                    if(boardVector[i][j].GetMineStatus()){
                        boardVector[i][j].SetRevealStatus(true);
                    }
                }
                if(gameWon){
                    if(!boardVector[i][j].GetRevealStatus()){
                        boardVector[i][j].SetFlaggedStatus(true);
                    }
                }

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

        // Draw Test #2 Button
        sf::Sprite testTwoBtn(TextureManager::GetTexture("test_2"));
        testTwoBtn.setPosition(sf::Vector2f(width - 128, height - 100));
        window.draw(testTwoBtn);

        // Draw Test #1 Button
        sf::Sprite testOneBtn(TextureManager::GetTexture("test_1"));
        testOneBtn.setPosition(sf::Vector2f(width - 192, height - 100));
        window.draw(testOneBtn);

        // Draw Debug Button
        sf::Sprite debugBtn(TextureManager::GetTexture("debug"));
        debugBtn.setPosition(sf::Vector2f(width - 256, height - 100));
        window.draw(debugBtn);

        // Draw Smiley Face Button
        sf::Sprite SmileyFaceButton(TextureManager::GetTexture("face_happy"));
        SmileyFaceButton.setPosition(sf::Vector2f(width/2 - 32, height - 100));
        window.draw(SmileyFaceButton);

        // Check Game Loss
        if(gameOver){
            sf::Sprite SadFaceButton(TextureManager::GetTexture("face_lose"));
            SadFaceButton.setPosition(sf::Vector2f(width/2 - 32, height - 100));
            window.draw(SadFaceButton);
        }

        // Check Game Won
        if(gameWon){
            sf::Sprite WinningFaceButton(TextureManager::GetTexture("face_win"));
            WinningFaceButton.setPosition(sf::Vector2f(width/2 - 32, height - 100));
            window.draw(WinningFaceButton);
        }
        int revealedTileCount = 0;
        for(int i = 0; i < boardVector.size(); i++){
            for(int j = 0; j < boardVector[i].size(); j++) {
                if(boardVector[i][j].GetRevealStatus())
                    revealedTileCount++;
            }
        }
        if(revealedTileCount == tileCount - mineCount){
            gameWon = true;
        }




        window.display();
    }
    TextureManager::Clear();

    return 0;
}

void revealBlankTiles(int i, int j, int columns, int rows, vector<vector<Tile>>& boardVector) {

    // BASE CASE
    // Return if tile is revealed, flagged, or a mine
    if(i < 0 || i > rows - 1 || j < 0 || j > columns - 1)
        return;
    if(boardVector[i][j].GetRevealStatus())
        return;
    if(boardVector[i][j].GetFlaggedStatus())
        return;
    if(boardVector[i][j].GetMineStatus())
        return;

    // Reveal tile
    boardVector[i][j].SetRevealStatus(true);

    // If tile has adjacent mines, recurse if it doesn't
    if(boardVector[i][j].GetTileData() != "0")
        return;

    revealBlankTiles(i - 1, j, columns, rows, boardVector); // TOP
    revealBlankTiles(i - 1, j + 1, columns, rows, boardVector); // TOP RIGHT
    revealBlankTiles(i, j + 1, columns, rows, boardVector); // RIGHT
    revealBlankTiles(i + 1, j + 1, columns, rows, boardVector); // BOTTOM RIGHT
    revealBlankTiles(i + 1, j, columns, rows, boardVector); // BOTTOM
    revealBlankTiles(i + 1, j - 1, columns, rows, boardVector); // BOTTOM LEFT
    revealBlankTiles(i, j - 1, columns, rows, boardVector); // LEFT
    revealBlankTiles(i - 1, j - 1, columns, rows, boardVector); // TOP LEFT
}
