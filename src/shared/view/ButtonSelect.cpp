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
    fontSize = 20;

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
    else if (select_ID == SELECT_RESOURCE){
        scaleX = 0.4; scaleY = 0.9;
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

        spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2 * scaleX, spriteButton->getGlobalBounds().height/2 * scaleY);
        spriteButton->setPosition(this->coords.left - 22, this->coords.top);

        text = new sf::Text(message, font, fontSize);
        text->setColor(sf::Color(0, 0, 0));
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x + spriteButton->getGlobalBounds().width/4 * 0.7, spriteButton->getPosition().y);
        
        this->coords.left -= 22 * 0.5;
        this->coords.top -= spriteButton->getGlobalBounds().height/2;
    }

    else if(select_ID == SELECT_ALEA_GEN){
        
        spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);  //comme btton validate
        spriteButton->setPosition(this->coords.left, this->coords.top);

        // spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2 * scaleX, spriteButton->getGlobalBounds().height/2 * scaleY);
        // spriteButton->setPosition(this->coords.left - 22, this->coords.top);

        fontSize = fontSize - 3;
        text = new sf::Text(message, font, fontSize);
        text->setColor(sf::Color(0, 0, 0));
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);

        scaleX = 1;
    }

        this->coords.left -= (spriteButton->getGlobalBounds().width*scaleX)/2;
}

bool ButtonSelect::isClicked(int x, int y){
    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV )
        clicked = coords.contains(sf::Vector2i(x, y));
    else if(select_ID == SELECT_BANK || select_ID == SELECT_P1 || select_ID == SELECT_P2 || select_ID == SELECT_P3 || select_ID == SELECT_RESOURCE || select_ID == SELECT_ALEA_GEN){
        if (clicked && coords.contains(sf::Vector2i(x, y))){
            clicked = 0;
        }
            
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
            
            if(select_ID == SELECT_ROAD)
                *displayState = BUILD_ROAD;
            else if(select_ID == SELECT_CITY)
                *displayState = BUILD_CITY_DISPLAY;
            else if(select_ID == SELECT_COLONY)
                *displayState = BUILD_COLONY_DISPLAY;
            else if(select_ID == SELECT_DEV)
                //commande piocher developpment
                *displayState = DRAW_CARD_DISPLAY;
            
            result = true;
        }
    }

    if(select_ID == SELECT_ROAD || select_ID == SELECT_COLONY || select_ID == SELECT_CITY || select_ID == SELECT_DEV)
        clicked = 0;
    
    this->update();

    return result;
}


void ButtonSelect::update(){
    if(clicked)
        spriteButton->setTextureRect(sf::IntRect(0 + 144*1, 98, 145, 48));
    else
        spriteButton->setTextureRect(sf::IntRect(0, 98, 143, 48));
}

void ButtonSelect::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
    if(select_ID == SELECT_BANK || select_ID == SELECT_P1 || select_ID == SELECT_P2 || select_ID == SELECT_P3 || select_ID == SELECT_ALEA_GEN)
        target.draw(*text);
}


}