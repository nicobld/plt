#include "Card.h"
#include <iostream>

namespace view
{

Card::Card(){
    this->hover = false;
}

Card::Card(Card_ID card_ID, sf::Texture* cardTexture) : card_ID(card_ID), cardTexture(cardTexture){
    
    spriteCard = new sf::Sprite(*cardTexture, sf::IntRect(155 * (((int) card_ID )+ 2), 0, 155, 234));
    spriteCard->setScale(sf::Vector2f(1.2, 1.2));

    this->hover = false;
}

void Card::render(sf::RenderTarget& target){
    target.draw(*spriteCard);
}

bool Card::isClicked(int x, int y){
    if(spriteCard->getGlobalBounds().contains(x, y))
        return true;
    else
        return false;
}

bool Card::isReleased(int x, int y){
    if(spriteCard->getGlobalBounds().contains(x, y))
        return true;
    else
        return false;
}

} 
