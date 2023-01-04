#include "ButtonSelect.h"
#include <iostream>

namespace view{

ButtonSelect::ButtonSelect (sf::Texture buttonTexture, sf::IntRect coords, Select_ID select_ID, DisplayState* displayState){
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->button_ID = BUTTON_SELECT;
    this->select_ID = select_ID;
    this->displayState = displayState;

    this->font.loadFromFile("../res/poppins.ttf");
    int fontSize = 20;

    spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(0, 98, 143, 48));
    spriteButton->setScale(sf::Vector2f(0.5, 0.9));
    spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
    spriteButton->setPosition(this->coords.left, this->coords.top);

    this->coords.left -= spriteButton->getGlobalBounds().width/2;
}

bool ButtonSelect::isClicked(int x, int y){
    
    clicked = coords.contains(sf::Vector2i(x, y));
    this->update();
    return clicked;
}

bool ButtonSelect::isReleased(int x, int y){
    bool result = false;
    if(clicked = coords.contains(sf::Vector2i(x, y))){
        
        std::cout << "Boutton Selection" << std::endl;
        
        if(select_ID == SELECT_ROAD)
            *displayState = BUILD_ROAD;
        else if(select_ID == SELECT_CITY || select_ID == SELECT_COLONY)
            *displayState = BUILD_BUILDING;
        else if(select_ID == SELECT_DEV)
            //commande piocher developpment
            *displayState = STAND_BY;
        
        result = true;
    }
    clicked = 0;
    this->update();

    return result;
}


void ButtonSelect::update(){
    int fontSize = 20;
    if(clicked)
        spriteButton->setTextureRect(sf::IntRect(0 + 143*1, 98, 143, 48));
    else
        spriteButton->setTextureRect(sf::IntRect(0, 98, 143, 48));
}

void ButtonSelect::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
}


}