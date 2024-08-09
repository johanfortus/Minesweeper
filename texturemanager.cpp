#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "texturemanager.h"
using namespace std;

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
    string path = "images/" + fileName + ".png";
    textures[fileName].loadFromFile(path);
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