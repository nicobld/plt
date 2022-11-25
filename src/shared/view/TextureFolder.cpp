#include "TextureFolder.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace view;


namespace view{

TextureFolder::TextureFolder(){}


sf::Texture* TextureFolder::getTexture(std::string name){
    cout << "Recherche Texture" << endl;
    auto texturePair = textureMap.find(name);
   cout << "Fin Recherche Texture" << endl;
    if(texturePair != textureMap.end()){
        cout << "La texture existait déjà" << endl;
        return (&texturePair->second);
    }
    else{
        
        Texture& texture = textureMap[name];
        texture.loadFromFile("../res/" + name);
        cout << "Chargement d'une nouvelle texture" << endl;
        return  &textureMap[name];
    }
}
}