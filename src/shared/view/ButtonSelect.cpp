#include "ButtonSelect.h"
#include <iostream>

namespace view{

ButtonSelect::ButtonSelect (sf::Texture buttonTexture, sf::IntRect coords, Select_ID select_ID, std::string message, DisplayState* displayState){
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->button_ID = BUTTON_SELECT;
    this->select_ID = select_ID;
    this->displayState = displayState;
    this->message = message;
    this->clicked = 0;


    this->font.loadFromFile("../res/poppins.ttf");
    int fontSize = 20;

    spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(0, 98, 143, 48));
    
    float scaleX, scaleY;
    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV){
        scaleX = 0.5; scaleY = 0.9;
        spriteButton->setScale(sf::Vector2f(scaleX, scaleY));
        this->coords.width =  this->coords.width * scaleX;
        this->coords.height =  this->coords.height * scaleY;
        spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
        spriteButton->setPosition(this->coords.left, this->coords.top);
    }
    else if(select_ID == SELECT_BANK || select_ID == SELECT_P1 || select_ID == SELECT_P2 || select_ID == SELECT_P3){
        scaleX = 0.8; scaleY = 0.9;
        spriteButton->setScale(sf::Vector2f(scaleX, scaleY));
        this->coords.width =  this->coords.width * scaleX;
        this->coords.height =  this->coords.height * scaleY;
        
        // namePlayers.back().setOrigin(namePlayers.back().getGlobalBounds().width/2, 0);
        // namePlayers.back().setPosition(spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 60 + namePlayers.back().getGlobalBounds().width/2, spriteMenu->getPosition().y + 157);

        spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2 * scaleX, spriteButton->getGlobalBounds().height/2 * scaleY);
        spriteButton->setPosition(this->coords.left - 22, this->coords.top);

        text = new sf::Text(message, font, fontSize);
        text->setColor(sf::Color(0, 0, 0));
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x + spriteButton->getGlobalBounds().width/4 * 0.7, spriteButton->getPosition().y);
        
        this->coords.left -= 22 * 0.5;
        this->coords.top -= spriteButton->getGlobalBounds().height/2;
    }

    this->coords.left -= (spriteButton->getGlobalBounds().width*scaleX)/2;
}

bool ButtonSelect::isClicked(int x, int y){
    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV)
        clicked = coords.contains(sf::Vector2i(x, y));
    else if(select_ID == SELECT_BANK || select_ID == SELECT_P1 || select_ID == SELECT_P2 || select_ID == SELECT_P3){
        if (clicked && coords.contains(sf::Vector2i(x, y)))
            clicked = 0;
        else if(!clicked && coords.contains(sf::Vector2i(x, y)))
            clicked = 1;
    }

    this->update();
    return clicked;
}

bool ButtonSelect::isReleased(int x, int y){
    bool result = false;

    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV){
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
    }

    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV)
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
    if(select_ID == SELECT_BANK || select_ID == SELECT_P1 || select_ID == SELECT_P2 || select_ID == SELECT_P3)
        target.draw(*text);
}


}