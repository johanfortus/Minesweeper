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


void Board::countAdjacentMines() {
    vector<vector<string>> myArray;
    myArray = {
            {"L", "•", "•", "B", "C"},
            {"•", "B", "•", "•", "•"},
            {"X", "X", "X", "X", "$"}};
//    cout << myArray[0][0] << endl;

    for(int i = 0; i < myArray.size(); i++){
        for(int j = 0; j < myArray[i].size(); j++){

            int bombCount;

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
}