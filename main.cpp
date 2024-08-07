#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
using namespace std;

int main(){

    ifstream inFile("config.cfg");

    string lineFromFile;

    int width;
    inFile >> width;
    width = width * 32;
    cout << "Width: " << width << endl;

    int height;
    inFile >> height;
    height = (height * 32) + 100;
    cout << "Height: " << height << endl;

    int mineCount;
    inFile >> mineCount;
    mineCount = mineCount * 16;
    cout << "Mine Count: " << mineCount << endl;

    inFile.close();


//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }

    return 0;
}