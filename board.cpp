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
        vector<int> row;
        for(unsigned int j = 0; j < columnAmount; j++) {
            row.push_back(0);
        }
        boardVector.push_back(row);
    }

    // Randomizing Mine Placement
    while(totalMinesPlaced != mineAmount){
        int randomRow = Random::Int(0, rowAmount - 1);
        int randomCol = Random::Int(0, columnAmount - 1);

        if(boardVector[randomRow][randomCol] != 1){
            boardVector[randomRow][randomCol] = 1;
            totalMinesPlaced++;
        }
        else{
            continue;
        }

        cout << "[" << randomRow << "]" << "[" << randomCol << "]" << endl;

    }
    cout << endl;


    for(int i = 0; i < boardVector.size(); i++){
        for(int j = 0; j < boardVector[i].size(); j++){
            cout << boardVector[i][j] << " ";
        }
        cout << endl;
    }

}