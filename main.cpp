#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include "texturemanager.h"
#include "board.h"
#include "tile.h"
using namespace std;

void revealBlankTiles(int i, int j, int columns, int rows, vector<vector<Tile>>& boardVector);
void testFileLayout(vector<vector<Tile>>& boardVector, int& mineCount, const string& fileName);
void loadDigits(unordered_map<string, sf::Sprite>& digitSprites, int width, int height);
void drawCounter(unordered_map<string, sf::Sprite>& digitSprites, int flaggedMines, sf::RenderWindow& window, int width, int height);
void setMenuBtnPos(sf::Sprite& faceWin, sf::Sprite& faceLose, sf::Sprite& faceHappy, sf::Sprite& debug, sf::Sprite& testOne, sf::Sprite& testTwo, sf::Sprite& testThree, int width, int height);

int main(){
    ifstream inFile("boards/config.cfg");
    string lineFromFile;

    int columns;
    int width;
    inFile >> columns;
    width = columns * 32;

    int rows;
    int height;
    inFile >> rows;
    height = (rows * 32) + 100;

    int mineCount;
    inFile >> mineCount;
    int flaggedMines = mineCount;
    int originalMineCount = mineCount; // mineCount may be updated due to testing purposes

    int tileCount;
    tileCount = columns * rows;
    inFile.close();

    bool gameOver = false;
    bool gameWon = false;
    bool debugMode = false;

    // Bottom Menu Buttons - height set to minus 100 instead of height minus 96 (32*3) bc it looks slightly better
    // Hard Coded values are based on the button size (64x64)
    sf::Sprite testThreeBtn(TextureManager::GetTexture("test_3"));
    sf::Sprite testTwoBtn(TextureManager::GetTexture("test_2"));
    sf::Sprite testOneBtn(TextureManager::GetTexture("test_1"));
    sf::Sprite debugBtn(TextureManager::GetTexture("debug"));
    sf::Sprite SmileyFaceBtn(TextureManager::GetTexture("face_happy"));
    sf::Sprite SadFaceBtn(TextureManager::GetTexture("face_lose"));
    sf::Sprite WinningFaceBtn(TextureManager::GetTexture("face_win"));
    setMenuBtnPos(WinningFaceBtn, SadFaceBtn, SmileyFaceBtn, debugBtn, testOneBtn, testTwoBtn, testThreeBtn, width, height);

    Board board(columns, rows, mineCount);
    board.CountAdjacentMines();
    vector<vector<Tile>> boardVector = board.GetBoardVector();

    unordered_map<string, sf::Sprite> digitSprites;
    loadDigits(digitSprites, width, height);

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
                        flaggedMines = mineCount;
                        Board board(columns, rows, mineCount);
                        board.CountAdjacentMines();
                        boardVector = board.GetBoardVector();
                        gameOver = false;
                        gameWon = false;
                    }
                }
            }

            /*=== TEST BUTTONS FUNCTIONALITY ===*/
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left){

                    bool testOneClicked = event.mouseButton.x >= width - 192 && event.mouseButton.x <= width - 192 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36;
                    bool testTwoClicked = event.mouseButton.x >= width - 128 && event.mouseButton.x <= width - 128 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36;
                    bool testThreeClicked = event.mouseButton.x >= width - 64 && event.mouseButton.x <= width - 64 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36;

                    if(testOneClicked || testTwoClicked || testThreeClicked){
                        string testFile;

                        if(testOneClicked)
                            testFile = "boards/testboard1.brd";
                        else if(testTwoClicked)
                            testFile = "boards/testboard2.brd";
                        else if(testThreeClicked)
                            testFile = "boards/testboard3.brd";

                        gameOver = false;
                        gameWon = false;
                        testFileLayout(boardVector, mineCount, testFile);
                        flaggedMines = mineCount;
                        board.UpdateBoard(boardVector);
                        board.CountAdjacentMines();
                        boardVector = board.GetBoardVector();

                        window.draw(SmileyFaceBtn);
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

                            // Toggle Debug Mode
                            if(event.mouseButton.x >= width - 256 && event.mouseButton.x <= width - 256 + 64 && event.mouseButton.y >= height - 100 && event.mouseButton.y <= height - 36){
                                if(debugMode)
                                    debugMode = false;
                                else
                                    debugMode = true;
                            }

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
                            i = floor(event.mouseButton.y / 32);
                            j = floor(event.mouseButton.x / 32);

                            // Right Click - Flag Tile (boardVector[i][j]) if not flagged or unflag if flagged
                            if(!boardVector[i][j].GetFlaggedStatus()){
                                boardVector[i][j].SetFlaggedStatus(true);
                                flaggedMines--;
                            }
                            else{
                                boardVector[i][j].SetFlaggedStatus(false);
                                flaggedMines++;
                            }
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
        window.draw(testThreeBtn);

        // Draw Test #2 Button
        window.draw(testTwoBtn);

        // Draw Test #1 Button
        window.draw(testOneBtn);

        // Draw Debug Button
        window.draw(debugBtn);

        // Draw Smiley Face Button
        window.draw(SmileyFaceBtn);

        // Draw Counter
        drawCounter(digitSprites, flaggedMines, window, width, height);

        // Check Game Loss
        if(gameOver)
            window.draw(SadFaceBtn);

        // Check Game Won - If revealed tiles amount matches tileCount minus mineCount
        if(gameWon) {
            window.draw(WinningFaceBtn);
            drawCounter(digitSprites, 0, window, width, height);
        }

        int revealedTileCount = 0;
        for(int i = 0; i < boardVector.size(); i++){
            for(int j = 0; j < boardVector[i].size(); j++) {
                if(boardVector[i][j].GetRevealStatus())
                    revealedTileCount++;
            }
        }
        if(revealedTileCount == tileCount - mineCount)
            gameWon = true;

        window.display();
    }
    TextureManager::Clear();
    return 0;
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

void testFileLayout(vector<vector<Tile>>& boardVector, int& mineCount, const string& fileName){
    ifstream testFile(fileName);
    string line;
    mineCount = 0;

    for(unsigned int i = 0; i < boardVector.size(); i++){
        if(getline(testFile, line)){
            for(unsigned int j = 0; j < boardVector[i].size(); j++){
                if(line[j] == '1'){
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

// rectLeft is for cropping purposes - position the number is on the texture
void loadDigits(unordered_map<string, sf::Sprite>& digitSprites, int width, int height){
    // Hard Coded Values Based On Digits Texture - 231x32
    // Rectangle Width is 21, due to 11 values
    int rectLeft = 0;
    for(int i = 0; i < 11; i++){
        sf::Sprite digit(TextureManager::GetTexture("digits"));
        sf::IntRect rectDigit(rectLeft, 0, 21, 32);
        digit.setTextureRect(rectDigit);
        if(i == 10)
            digitSprites["-"] = digit;
        else
            digitSprites[to_string(i)] = digit;
        rectLeft+=21;
    }
}

// Draw Counter - Change xPos while checking string flag count index
void drawCounter(unordered_map<string, sf::Sprite>& digitSprites, int flaggedMines, sf::RenderWindow& window, int width, int height) {
    string digitString;
    if(flaggedMines < 100 && flaggedMines >= 10)
        digitString = "0" + to_string(flaggedMines);
    else if(flaggedMines < 10 && flaggedMines >= 0)
        digitString = "00" + to_string(flaggedMines);
    else if(flaggedMines < 0 && flaggedMines > -10)
        digitString = "-00" + to_string(abs(flaggedMines));
    else if(flaggedMines <= -100)
        digitString = "-" + to_string(abs(flaggedMines));
    else if(flaggedMines <= -10)
        digitString = "-0" + to_string(abs(flaggedMines));
    else if(flaggedMines >= 100)
        digitString = to_string(flaggedMines);

    int iterationAmount;
    int xPos = width - width;
    int yPos = height - 100;
    if(flaggedMines >= 0)
        iterationAmount = 3;
    else if(flaggedMines < 0)
        iterationAmount = 4;

    for(unsigned int i = 0; i < iterationAmount; i++) {
        string key(1, digitString[i]);
        sf::Sprite digit = digitSprites[key];
        digit.setPosition(xPos, yPos);
        window.draw(digit);
        xPos+=21;
    }
}

// Set Bottom Menu Button Sprite Positions
void setMenuBtnPos(sf::Sprite& faceWin, sf::Sprite& faceLose, sf::Sprite& faceHappy, sf::Sprite& debug, sf::Sprite& testOne, sf::Sprite& testTwo, sf::Sprite& testThree, int width, int height) {
    faceWin.setPosition(sf::Vector2f(width / 2 - 32, height - 100));
    faceLose.setPosition(sf::Vector2f(width / 2 - 32, height - 100));
    faceHappy.setPosition(sf::Vector2f(width / 2 - 32, height - 100));
    debug.setPosition(sf::Vector2f(width - 256, height - 100));
    testOne.setPosition(sf::Vector2f(width - 192, height - 100));
    testTwo.setPosition(sf::Vector2f(width - 128, height - 100));
    testThree.setPosition(sf::Vector2f(width - 64, height - 100));
}