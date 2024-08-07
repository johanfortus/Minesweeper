#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include "texturemanager.h"
using namespace std;

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
    string path = fileName + ".png";

    textures[fileName].loadFromFile(path);

    // fileName == space
    // path == images/space.png
}

sf::Texture& TextureManager::GetTexture(string textureName){

    // if the texture DOESN'T exist...
    if(textures.find(textureName) == textures.end())
        LoadTexture(textureName);

    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear(); // Get rid of all stored objects
}