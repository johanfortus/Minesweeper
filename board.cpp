#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "board.h"
#include "random.h"
using namespace std;

Board::Board(int columnAmount, int rowAmount, int mineAmount) {

    // Creating Board - 2D Vector
    for(unsigned int i = 0; i < rowAmount; i++) {
        vector<string> row;
        for(unsigned int j = 0; j < columnAmount; j++) {
            row.push_back("•");
        }
        boardVector.push_back(row);
    }

    // Randomizing Mine Placement
    while(totalMinesPlaced != mineAmount){
        int randomRow = Random::Int(0, rowAmount - 1);
        int randomCol = Random::Int(0, columnAmount - 1);
        if(boardVector[randomRow][randomCol] != "B"){
            boardVector[randomRow][randomCol] = "B";
            totalMinesPlaced++;
        }
        else{
            continue;
        }
        /*cout << "[" << randomRow << "]" << "[" << randomCol << "]" << endl;*/
    }
    /*cout << endl;*/
}

// Printing Board Out
void Board::printBoard() {
    for(int i = 0; i < boardVector.size(); i++){
        for(int j = 0; j < boardVector[i].size(); j++){
            cout << boardVector[i][j] << " ";
        }
        cout << endl;
    }
}

// Yes I am aware this code is severely violating the DRY principle
void Board::countAdjacentMines() {

    for(int i = 0; i < boardVector.size(); i++){
        for(int j = 0; j < boardVector[i].size(); j++){

            if(boardVector[i][j] != "B"){
                int bombCount = 0;

                // Top Left Corner
                if(i == 0 && j == 0){
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                    if(boardVector[i + 1][j + 1] == "B") // Bottom Right
                        bombCount++;
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;

                }

                // Top Right Corner
                else if(i == 0 && j == boardVector[i].size() - 1){
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;
                    if(boardVector[i + 1][j - 1] == "B") // Bottom Left
                        bombCount++;
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                }

                // Bottom Left Corner
                else if(j == 0 && i == boardVector.size() - 1){
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                    if(boardVector[i - 1][j + 1] == "B") // Top Right
                        bombCount++;
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                }

                // Bottom Right Corner
                else if(j == boardVector[i].size() - 1 && i == boardVector.size() - 1){
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                    if(boardVector[i - 1][j - 1] == "B") // Top Left
                        bombCount++;
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                }

                // Top Edge
                else if(i == 0){
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                    if(boardVector[i + 1][j + 1] == "B") // Bottom Right
                        bombCount++;
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;
                    if(boardVector[i + 1][j - 1] == "B") // Bottom Left
                        bombCount++;
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                }

                // Bottom Edge
                else if(i == boardVector.size() - 1){
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                    if(boardVector[i - 1][j - 1] == "B") // Top Left
                        bombCount++;
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                    if(boardVector[i - 1][j + 1] == "B") // Top Right
                        bombCount++;
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                }

                // Left Edge
                else if(j == 0){
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                    if(boardVector[i - 1][j + 1] == "B") // Top Right
                        bombCount++;
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                    if(boardVector[i + 1][j + 1] == "B") // Bottom Right
                        bombCount++;
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;
                }

                // Right Edge
                else if(j == boardVector[i].size() - 1){
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;
                    if(boardVector[i + 1][j - 1] == "B") // Bottom Left
                        bombCount++;
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                    if(boardVector[i - 1][j - 1] == "B") // Top Left
                        bombCount++;
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                }

                else {
                    if(boardVector[i][j + 1] == "B") // Right
                        bombCount++;
                    if(boardVector[i + 1][j + 1] == "B") // Bottom Right
                        bombCount++;
                    if(boardVector[i + 1][j] == "B") // Bottom
                        bombCount++;
                    if(boardVector[i + 1][j - 1] == "B") // Bottom Left
                        bombCount++;
                    if(boardVector[i][j - 1] == "B") // Left
                        bombCount++;
                    if(boardVector[i - 1][j - 1] == "B") // Top Left
                        bombCount++;
                    if(boardVector[i - 1][j] == "B") // Top
                        bombCount++;
                    if(boardVector[i - 1][j + 1] == "B") // Top Right
                        bombCount++;
                }
                if(bombCount > 0)
                    boardVector[i][j] = to_string(bombCount);
            }

        }
        cout << endl;
    }
}

vector<vector<string>> Board::getBoardVector(){
    return boardVector;
}