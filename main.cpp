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
void testFileLayout(vector<vector<Tile>>& boardVector, int& mineCount, string fileName);

int main(){
    ifstream inFile("config.cfg");
    string lineFromFile;

    int columns;
    int width;
    inFile >> columns;
    width = columns * 32;

    int rows;
    int height;
    inFile >> rows;
    height = (rows * 32) + 100;
    cout << "Width: " << width << ", Height: " << height << endl;

    int mineCount;
    inFile >> mineCount;
    int originalMineCount = mineCount; // mineCount may be updated due to testing purposes

    int tileCount;
    tileCount = columns * rows;
    inFile.close();

    bool gameOver = false;
    bool gameWon = false;
    bool debugMode = false;

    // Bottom Menu Buttons - height set to minus 100 instead of height minus 96 (32*3) bc it looks slightly better
    // Hard Coded values are based on the button size (64x64)
    sf::Vector2f smileyFaceBtnPos(width/2 - 32, height - 100);
    sf::Vector2f debugBtnPos(width - 256, height - 100);
    sf::Vector2f testOneBtnPos(width - 192, height - 100);
    sf::Vector2f testTwoBtnPos(width - 128, height - 100);
    sf::Vector2f testThreeBtnPos(width - 64, height - 100);


    Board board(columns, rows, mineCount);
    board.CountAdjacentMines();
    board.PrintBoard();
    vector<vector<Tile>> boardVector = board.GetBoardVector();

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            /*=== RESTART BUTTON FUNCTIONALITY ===*/
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(event.mouseButton.x >= width / 2 - 32 && event.mouseButton.x <= width / 2 + 32 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                        mineCount = originalMineCount;
                        Board board(columns, rows, mineCount);
                        board.CountAdjacentMines();
                        board.PrintBoard();
                        boardVector = board.GetBoardVector();
                        gameOver = false;
                        gameWon = false;
                        cout << "Restart Successful" << endl;
                    }
                }
            }

            /*=== DEBUG BUTTON FUNCTIONALITY ===*/
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(event.mouseButton.x >= width - 256 && event.mouseButton.x <= width - 256 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                        cout << "DEBUG BUTTON CLICKED" << endl;
                        if(debugMode)
                            debugMode = false;
                        else
                            debugMode = true;
                    }
                }
            }

            /*=== TEST BUTTONS FUNCTIONALITY ===*/
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left){

                    // Test One Button
                    if(event.mouseButton.x >= width - 192 && event.mouseButton.x <= width - 192 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                        cout << "TEST ONE BUTTON CLICKED" << endl;
                        gameOver = false;
                        gameWon = false;
                        testFileLayout(boardVector, mineCount, "testboard1.brd");
                        board.UpdateBoard(boardVector);
                        board.CountAdjacentMines();
                        board.PrintBoard();
                        boardVector = board.GetBoardVector();

                        sf::Sprite SmileyFaceButton(TextureManager::GetTexture("face_happy"));
                        SmileyFaceButton.setPosition(smileyFaceBtnPos);
                        window.draw(SmileyFaceButton);
                    }

                    // Test Two Button
                    else if(event.mouseButton.x >= width - 128 && event.mouseButton.x <= width - 128 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                        cout << "TEST TWO BUTTON CLICKED" << endl;
                        gameOver = false;
                        gameWon = false;
                        testFileLayout(boardVector, mineCount, "testboard2.brd");
                        board.UpdateBoard(boardVector);
                        board.CountAdjacentMines();
                        board.PrintBoard();
                        boardVector = board.GetBoardVector();

                        sf::Sprite SmileyFaceButton(TextureManager::GetTexture("face_happy"));
                        SmileyFaceButton.setPosition(smileyFaceBtnPos);
                        window.draw(SmileyFaceButton);
                    }

                    // Test Three Button
                    else if(event.mouseButton.x >= width - 64 && event.mouseButton.x <= width - 64 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                        cout << "TEST THREE BUTTON CLICKED" << endl;
                        gameOver = false;
                        gameWon = false;
                        testFileLayout(boardVector, mineCount, "testboard3.brd");
                        board.UpdateBoard(boardVector);
                        board.CountAdjacentMines();
                        board.PrintBoard();
                        boardVector = board.GetBoardVector();
                    }
                }
            }

            /*=== Handling Mouse Click Events & Game Data ===*/
            if(!gameOver && !gameWon) {
                switch(event.type) {
                    case sf::Event::MouseButtonPressed:
                        int i, j;

                        /* === LEFT CLICK === */
                        if(event.mouseButton.button == sf::Mouse::Left) {
                            cout << "X: " << event.mouseButton.x << " Y: " << event.mouseButton.y << endl;
                            cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                            i = floor(event.mouseButton.y / 32);
                            j = floor(event.mouseButton.x / 32);

                            if(i >= 0 && i < rows && j >= 0 && j < columns) {

                                // Left Click - If Tile is a Mine, reveal mine and set gameOver to true if NOT flagged
                                if(boardVector[i][j].GetMineStatus()){
                                    if(!boardVector[i][j].GetFlaggedStatus()){
                                        gameOver = true;
                                        boardVector[i][j].SetRevealStatus(true);
                                    }
                                }

                                    // Left Click - If Tile is not a blank tile, reveal
                                else if(!boardVector[i][j].GetFlaggedStatus() && boardVector[i][j].GetTileData() != "0"){
                                    boardVector[i][j].SetRevealStatus(true);
                                }

                                    // Left Click - If Tile is a blank tile, recursive function is called to reveal neighboring blank tiles
                                else if(boardVector[i][j].GetTileData() == "0"){
                                    revealBlankTiles(i, j, columns, rows, boardVector);
                                }
                            }
                        }

                        /* === RIGHT CLICK === */
                        else if(event.mouseButton.button == sf::Mouse::Right) {
//                            cout << "[" << floor(event.mouseButton.y / 32) << "][" << floor(event.mouseButton.x / 32) << "]" << endl;
                            i = floor(event.mouseButton.y / 32);
                            j = floor(event.mouseButton.x / 32);

                            // Right Click - Flag Tile (boardVector[i][j]) if not flagged or unflag if flagged
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

        /*=== Draw Sprites Based on Game Data ===*/
        for(int i = 0; i < boardVector.size(); i++){
            for(int j = 0; j < boardVector[i].size(); j++){

                // Set all mine tiles reveal status to true if game is over
                if(gameOver) {
                    if(boardVector[i][j].GetMineStatus()){
                        boardVector[i][j].SetRevealStatus(true);
                    }
                }

                // Set all mine tiles flagged status to true if game is won
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

                // Debug Mode
                if(debugMode){
                    if(boardVector[i][j].GetMineStatus()){
                        sf::Sprite tileMineSprite(TextureManager::GetTexture("mine"));
                        tileMineSprite.setPosition(sf::Vector2f(j * 32,i * 32));
                        window.draw(tileMineSprite);
                    }
                }
            }
        }

        // Draw Test #3 Button
        sf::Sprite testThreeBtn(TextureManager::GetTexture("test_3"));
        testThreeBtn.setPosition(testThreeBtnPos);
        window.draw(testThreeBtn);

        // Draw Test #2 Button
        sf::Sprite testTwoBtn(TextureManager::GetTexture("test_2"));
        testTwoBtn.setPosition(testTwoBtnPos);
        window.draw(testTwoBtn);

        // Draw Test #1 Button
        sf::Sprite testOneBtn(TextureManager::GetTexture("test_1"));
        testOneBtn.setPosition(testOneBtnPos);
        window.draw(testOneBtn);

        // Draw Debug Button
        sf::Sprite debugBtn(TextureManager::GetTexture("debug"));
        debugBtn.setPosition(debugBtnPos);
        window.draw(debugBtn);

        // Draw Smiley Face Button
        sf::Sprite SmileyFaceButton(TextureManager::GetTexture("face_happy"));
        SmileyFaceButton.setPosition(smileyFaceBtnPos);
        window.draw(SmileyFaceButton);

        // Check Game Loss
        if(gameOver){
            sf::Sprite SadFaceButton(TextureManager::GetTexture("face_lose"));
            SadFaceButton.setPosition(smileyFaceBtnPos);
            window.draw(SadFaceButton);
        }

        // Check Game Won - If revealed tiles amount matches tileCount minus mineCount
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

void testFileLayout(vector<vector<Tile>>& boardVector, int& mineCount, string fileName){
    ifstream testFile(fileName);
    string line;
    mineCount = 0;

    for(unsigned int i = 0; i < boardVector.size(); i++){
        if(getline(testFile, line)){
            for(unsigned int j = 0; j < boardVector[i].size(); j++){
                if(line[j] == '1'){
                    cout << "row[j] is 1" << endl;
                    boardVector[i][j].SetTileData("B");
                    boardVector[i][j].SetMineStatus(true);
                    mineCount++;
                }
                else {
                    boardVector[i][j].SetTileData("0");
                    boardVector[i][j].SetMineStatus(false);
                }
                boardVector[i][j].SetRevealStatus(false);
                boardVector[i][j].SetFlaggedStatus(false);
            }
        }
    }
}

// Recursive reveal neighboring tiles function
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
