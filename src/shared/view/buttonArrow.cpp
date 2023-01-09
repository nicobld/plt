#include "ButtonArrow.h"
#include <iostream>


namespace view{

    ButtonArrow::ButtonArrow (sf::Texture buttonTexture, sf::IntRect coords, Arrow_ID arrow_ID, DisplayState* displayState, state::Resource* resource){
    this->buttonTexture = buttonTexture;
    this->coords = coords;
    this->button_ID = BUTTON_ARROW;
    this->arrow_ID = arrow_ID;
    this->displayState = displayState;
    this->resource = resource;
    this->clicked = 0;

    if(arrow_ID == ARROW_UP)
        spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(246, 49, 45, 13));
    if(arrow_ID == ARROW_DOWN)
        spriteButton = new sf::Sprite(this->buttonTexture, sf::IntRect(246 + 45*2, 49, 45, 14));
    
    spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0 );
    spriteButton->setPosition(this->coords.left, this->coords.top);

    this->coords.left -= spriteButton->getGlobalBounds().width/2;
}

bool ButtonArrow::isClicked(int x, int y){
    
    clicked = coords.contains(sf::Vector2i(x, y));
    this->update();
    return clicked;
}

bool ButtonArrow::isReleased(int x, int y){
    bool result = false;
    if( (clicked = coords.contains(sf::Vector2i(x, y))) ){
        //commande
        std::cout << "Boutton arrow" << std::endl;

        if(arrow_ID == ARROW_UP){
            resource->number +=1;
        }
        if(arrow_ID == ARROW_DOWN){

            resource->number -=1;
        }

        result = true;
    }
    clicked = 0;
    this->update();

    return result;
}


void ButtonArrow::update(){
    if(clicked){   
        if(arrow_ID == ARROW_UP)
            spriteButton->setTextureRect(sf::IntRect(246 +45*1 + 1, 49, 45, 13));
        if(arrow_ID == ARROW_DOWN)
            spriteButton->setTextureRect(sf::IntRect(246 + 45*3 + 1, 49, 45, 14));
    }
    else{
        if(arrow_ID == ARROW_UP)
            spriteButton->setTextureRect(sf::IntRect(246, 49, 45, 13));
        if(arrow_ID == ARROW_DOWN)
            spriteButton->setTextureRect(sf::IntRect(246 + 45*2, 49, 45, 14));
    }
}

void ButtonArrow::render (sf::RenderTarget& target){
    target.draw(*spriteButton);
}


}