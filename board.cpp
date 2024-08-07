#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "board.h"
using namespace std;

Board::Board(int columnAmount, int rowAmount) {
    for(unsigned int i = 0; i < rowAmount; i++) {
        vector<int> row;
        for(unsigned int j = 0; j <= columnAmount; j++) {
            row.push_back(0);
        }
        boardVector.push_back(row);
    }

//    for(int i = 0; i < boardVector.size(); i++){
//        for(int j = 0; j < boardVector[i].size(); j++){
//            cout << boardVector[i][j] << " ";
//        }
//        cout << endl;
//    }

}