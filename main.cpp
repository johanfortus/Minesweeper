#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "random.h"
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

    cout << "Random Number: " << Random::Int(0, width) << endl;
    cout << "Random Number: " << Random::Int(0, height) << endl;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}