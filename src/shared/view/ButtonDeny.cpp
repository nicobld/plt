#include "ButtonDeny.h"
#include <iostream>

namespace view{

ButtonDeny::ButtonDeny(sf::Texture buttonTexture, sf::IntRect coords, std::string message, DisplayState* displayState) {
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->buttonTexture = buttonTexture;
    this->message = message;
    this->button_ID = BUTTON_DENY;
    this->displayState = displayState;
    clicked = false;

    this->font.loadFromFile("../res/poppins.ttf");
    int fontSize = 20;

    spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(123*2, 0, 122, 48));
    spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
    spriteButton->setPosition(this->coords.left, this->coords.top);

    text = new sf::Text(this->message, font, fontSize);
    //text = new sf::Text("Valider", this->font, fontSize);
    text->setColor(sf::Color(255, 255, 255));
    text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
    text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);

}

bool ButtonDeny::isClicked(int x, int y){
    
    clicked = coords.contains(sf::Vector2i(x, y));
    this->update();
    return clicked;
}

bool ButtonDeny::isReleased(int x, int y){
    if(clicked = coords.contains(sf::Vector2i(x, y))){
        //commande
        std::cout << "Boutton Deny" << std::endl;
        return true;
    }
    //clicked = 0;
    this->update();
}

void ButtonDeny::update(){
    int fontSize = 20;
    if(clicked){
        spriteButton->setTextureRect(sf::IntRect(123*3, 0, 122, 48));
        text->setColor(sf::Color(245, 245, 245));
        text->setCharacterSize(fontSize-2);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
    else{
        spriteButton->setTextureRect(sf::IntRect(123*2, 0, 122, 48));
        text->setColor(sf::Color(255, 255, 255));
        text->setCharacterSize(fontSize-2);
        text->setOrigin(text->getGlobalBounds().width/2, text->getGlobalBounds().height/2);
        text->setPosition(spriteButton->getPosition().x, spriteButton->getPosition().y + spriteButton->getGlobalBounds().height/2 - 7);
    }
}

void ButtonDeny::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
    target.draw(*text);
}


}