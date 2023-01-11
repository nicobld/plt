#include "Hand.h"
#include <iostream>

namespace view
{

static void deleteCard(std::vector<Card*> card)
{
    for (auto c : card)
    {
        delete c;
    }
    card.clear();
}

Hand::Hand(sf::Texture* cardTexture, state::PlayerColor playerColor, state::State* state) : cardTexture(cardTexture), state(state){
    this->playerColor = playerColor;
    coords = sf::IntRect(0, 720 - 300, 350, 300);

    int totalSpace = 150, gap = 150, height = 720;

    positionDown  = height - 165;
    positionUp = height - 265;        

    if(state->players[playerColor].developments.size() > 1)
        gap = (int) (totalSpace / (state->players[playerColor].developments.size() - 1));

    for (int i = 0; i < this->state->players[playerColor].developments.size(); i ++){
        cards.push_back(Card((Card_ID) state->players[playerColor].developments[i].developmentType, cardTexture));
        cards.back().spriteCard->setPosition(20 + i * gap, positionDown);
        cards.back().coords = sf::IntRect(cards.back().spriteCard->getPosition().x, cards.back().spriteCard->getPosition().y, gap, cards.back().spriteCard->getGlobalBounds().height);

    }
}

void Hand::updateHand(){
    //deleteCard(cards);
    if(state->players[playerColor].developments.size() != cards.size()){
        cards.clear();

        int totalSpace = 150, height = 720;
        if(state->players[playerColor].developments.size() > 1)
            gap = (int) (totalSpace / (state->players[playerColor].developments.size() - 1));

        for (int i = 0; i < state->players[playerColor].developments.size(); i ++){
            cards.push_back(Card((Card_ID) state->players[playerColor].developments[i].developmentType, cardTexture));
            cards.back().spriteCard->setPosition(20 + i * gap, positionDown);
            cards.back().coords = sf::IntRect(cards.back().spriteCard->getPosition().x, cards.back().spriteCard->getPosition().y, gap, cards.back().spriteCard->getGlobalBounds().height);
        }
        cards.back().coords = (sf::IntRect) cards.back().spriteCard->getGlobalBounds();

    }
    
    // cards.shrink_to_fit();
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
    for(int i = 0; i < cards.size(); i++){
        if(cards[i].coords.contains(x, y)){
            cards[i].hover = true;
            cards[i].spriteCard->setPosition(cards[i].spriteCard->getPosition().x, positionUp);
            cards[i].coords = (sf::IntRect) cards[i].spriteCard->getGlobalBounds();
            std::cout << "hover card : " << cards[i].card_ID << std::endl;
        }
        else{
            cards[i].hover = false;
            cards[i].spriteCard->setPosition(cards[i].spriteCard->getPosition().x, positionDown);
            cards.back().coords = sf::IntRect(cards.back().spriteCard->getPosition().x, cards.back().spriteCard->getPosition().y, gap, cards.back().spriteCard->getGlobalBounds().height);

        }
    }
}

}
