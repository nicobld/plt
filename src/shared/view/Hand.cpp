#include "Hand.h"
#include <iostream>

namespace view
{


Hand::Hand(sf::Texture* cardTexture, state::PlayerColor playerColor, state::State* state) : cardTexture(cardTexture), state(state){
    this->playerColor = playerColor;
    coords = sf::IntRect(0, 720 - 300, 350, 300);

    int totalSpace = 150, gap = 150, height = 720;
    this->cardHover = -1;

    positionDown  = height - 165;
    positionUp = height - 265;        

    if(state->players[playerColor].developments.size() > 1)
        gap = (int) (totalSpace / (state->players[playerColor].developments.size() - 1));

    for (int i = 0; i < this->state->players[playerColor].developments.size(); i ++){
        cards.push_back(Card((Card_ID) state->players[playerColor].developments[i].developmentType, cardTexture));
        cards.back().spriteCard->setPosition(20 + i * gap, positionDown);

    }
}

void Hand::updateHand(){
    if(state->players[playerColor].developments.size() != cards.size()){
        cards.clear();

        int totalSpace = 150, height = 720;
        if(state->players[playerColor].developments.size() > 1)
            gap = (int) (totalSpace / (state->players[playerColor].developments.size() - 1));

        for (int i = 0; i < state->players[playerColor].developments.size(); i ++){
            cards.push_back(Card((Card_ID) state->players[playerColor].developments[i].developmentType, cardTexture));
            cards.back().spriteCard->setPosition(20 + i * gap, positionDown);
        }

    }
    
}


void Hand::render (sf::RenderTarget& target){
    for(int i = 0; i < cards.size(); i++){
        if(cards[i].hover)
            cards[i].spriteCard->setPosition(cards[i].spriteCard->getPosition().x, positionUp);
        else
            cards[i].spriteCard->setPosition(cards[i].spriteCard->getPosition().x, positionDown);
        
        cards[i].render(target);

    }
     for(int i = 0; i < cards.size(); i++){
        if(cards[i].hover)
            cards[i].render(target);
    }
}

bool Hand::hoverOneCard (int x, int y){

    if(cardHover == -1){   
        for(int i = 0; i < cards.size(); i++){
            if(cards[i].spriteCard->getGlobalBounds().contains(x, y)){
                cardHover = i;
            }
            else{
                cards[i].hover = false;
            }
        }
    }
    else if(cardHover != -1){
        cards[cardHover].hover = true; 
        if(!cards[cardHover].spriteCard->getGlobalBounds().contains(x, y)){
            cards[cardHover].hover = false;
            cardHover = -1;
        }
    }
}

int Hand::isClicked(int x, int y){
    if(cardHover != -1){
        if(cards[cardHover].isClicked(x, y)){
            return cardHover;
        }
    }
    return -1;
}


}
