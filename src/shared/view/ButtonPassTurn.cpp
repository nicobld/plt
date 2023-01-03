#include "ButtonPassTurn.h"
#include <iostream>

namespace view{

ButtonPassTurn::ButtonPassTurn(sf::Texture buttonTexture, sf::IntRect coords, std::string message, DisplayState* displayState) {
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->buttonTexture = buttonTexture;
    this->message = message;
    this->button_ID = BUTTON_PASS_TURN;
    this->displayState = displayState;

    this->font.loadFromFile("../res/poppins.ttf");
    int fontSize = 20;

    spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(701, 258, 199, 48));
    spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
    spriteButton->setPosition(this->coords.left, this->coords.top);

    text = new sf::Text(this->message, font, fontSize);
    text->setColor(sf::Color(255, 255, 255));
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
    text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);

    this->coords.left -= spriteButton->getGlobalBounds().width/2;
}

bool ButtonPassTurn::isClicked(int x, int y){
    
    clicked = coords.contains(sf::Vector2i(x, y));
    this->update();
    return clicked;
}

bool ButtonPassTurn::isReleased(int x, int y){
    bool result = false;
    if(clicked = coords.contains(sf::Vector2i(x, y))){
        //commande
        std::cout << "Boutton passer son tour" << std::endl;
        *displayState = THROW_DICE;
        result = true;
    }
    clicked = 0;
    this->update();
    return result;
}


void ButtonPassTurn::update(){
    int fontSize = 20;
    if(clicked){
        spriteButton->setTextureRect(sf::IntRect(701 + 199*1, 258, 199, 48));
        text->setColor(sf::Color(245, 245, 245));
        text->setCharacterSize(fontSize-2);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
    else{
        spriteButton->setTextureRect(sf::IntRect(701 + 199*0, 258, 199, 48));
        text->setColor(sf::Color(255, 255, 255));
        text->setCharacterSize(fontSize);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
}

void ButtonPassTurn::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
    target.draw(*text);
}


}