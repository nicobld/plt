#include "ButtonValidate.h"
#include <iostream>

namespace view{

ButtonValidate::ButtonValidate(sf::Texture buttonTexture, sf::IntRect coords, std::string message, DisplayState* displayState) {
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->buttonTexture = buttonTexture;
    this->message = message;
    this->button_ID = BUTTON_VALIDATE;
    this->displayState = displayState;
    clicked = false;

    this->font.loadFromFile("../res/poppins.ttf");
    fontSize = 20;

    spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(0, 0, 122, 48));
    spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
    spriteButton->setPosition(this->coords.left, this->coords.top);

    if(this->message == "Commencer")
        fontSize = 18;
    text = new sf::Text(this->message, font, fontSize);
    text->setColor(sf::Color(255, 255, 255));
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
    text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);

    

    this->coords.left -= spriteButton->getGlobalBounds().width/2;

}

bool ButtonValidate::isClicked(int x, int y){
    
    clicked = coords.contains(sf::Vector2i(x, y));
    std::cout << clicked << std::endl;
    this->update();
    return clicked;
}

bool ButtonValidate::isReleased(int x, int y){
    bool result = false;
    if(clicked = coords.contains(sf::Vector2i(x, y))){
        //commande
        std::cout << "Boutton Valider" << std::endl;
        result = true;
    }
    //clicked = 0;
    std::cout << "released " << clicked << std::endl;
    this->update();

    return result;
}

void ButtonValidate::update(){
    if(clicked){
        spriteButton->setTextureRect(sf::IntRect(122, 0, 122, 48));
        text->setColor(sf::Color(245, 245, 245));
        text->setCharacterSize(fontSize-2);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
    else{
        spriteButton->setTextureRect(sf::IntRect(0, 0, 122, 48));
        text->setColor(sf::Color(255, 255, 255));
        text->setCharacterSize(fontSize);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
}

void ButtonValidate::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
    target.draw(*text);
}


}