#include "MenuBuild.h"

namespace view{
MenuBuild::MenuBuild(sf::Texture menuTexture, state::PlayerColor playerColor) : playerColor(playerColor){
    this->menuTexture = menuTexture;
    
    spriteMenu = new sf::Sprite(menuTexture, sf::IntRect(0, 0, 433, 268));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, spriteMenu->getGlobalBounds().height);
    spriteMenu->setPosition(1280/2, 760);

    


}

void MenuBuild::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);

}

void MenuBuild::update(state::State* state){}

}
