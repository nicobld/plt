#include "DiceDisplay.h"

namespace view{

DiceDisplay::DiceDisplay(state::State& state){
    
    //Dice texture
    diceTexture.loadFromFile("../res/dice.png");
    // diceSprite1 = new sf::Sprite(diceTexture, sf::IntRect(0, 0, 127, 127));
    // diceSprite1->setPosition(500, 300);

    // diceSprite2 = new sf::Sprite(diceTexture, sf::IntRect(127, 0, 127, 127));
    // diceSprite2->setPosition(700, 300);

    diceSprite1 = new sf::Sprite(diceTexture, sf::IntRect(0, 0, 127, 127));
    diceSprite1->setPosition(500, 300);

    diceSprite2 = new sf::Sprite(diceTexture, sf::IntRect(0, 0, 127, 127));
    diceSprite2->setPosition(700, 300);
}


void DiceDisplay::render(sf::RenderTarget& target){
    target.draw(*diceSprite1);
    target.draw(*diceSprite2);
}

void DiceDisplay::update(int dice1, int dice2){
    diceSprite1->setTextureRect(sf::IntRect(dice1-1*127, 0, 127, 127));
    diceSprite2->setTextureRect(sf::IntRect(dice2-1*127, 0, 0, 0));
}



}