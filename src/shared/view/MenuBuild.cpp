#include "MenuBuild.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace view;
using namespace state;


namespace view{

MenuBuild::MenuBuild(state::Player& player1, TextureFolder* textureFolder){
    menuTexture = textureFolder->getTexture("menu");
    menuSprite = new Sprite(*menuTexture, IntRect(0, 0, 434, 268));
}

void MenuBuild::render (sf::RenderTarget& target){
    target.draw(*menuSprite);
}

void MenuBuild::update (){}



}