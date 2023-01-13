#include "Dice.h"

namespace view
{

Dice::Dice(){

    int width = 1280, height = 720;

    darkEffect = new sf::RectangleShape(sf::Vector2f(width, height));
    darkEffect->setFillColor(sf::Color(0, 0, 0, 100));

    diceTexture = new sf::Texture();
    diceTexture->loadFromFile("../res/dice.png");
    diceTexture->setSmooth(true);

    int gap = 20;
    for(int i = 0; i < spriteDice.size(); i++){
        spriteDice[i] = new sf::Sprite(*diceTexture, sf::IntRect(0, 0, 128, 128));
        spriteDice[i]->setScale(sf::Vector2f(1.2, 1.2));
        //spriteDice[i]->setOrigin(spriteDice[i]->getGlobalBounds().width/2, spriteDice[i]->getGlobalBounds().height/2);
        spriteDice[i]->setOrigin(0, spriteDice[i]->getGlobalBounds().height/2);
        spriteDice[i]->setPosition(width/2 - spriteDice[i]->getGlobalBounds().width - gap/2 + i * (spriteDice[i]->getGlobalBounds().width + gap), height/2);
    }


    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 34;
    message = new sf::Text("Cliquez pour lancer les des", font, fontSize);
    message->setColor(sf::Color(255, 255, 255));
    message->setOrigin(message->getGlobalBounds().width/2, 0);
    message->setPosition(width/2,  spriteDice[0]->getGlobalBounds().top - gap - spriteDice[0]->getGlobalBounds().height/2);

    score = new sf::Text("", font, fontSize);

}

void Dice::render(sf::RenderTarget& target){
    target.draw(*darkEffect);
    target.draw(*message);
    for(int i = 0; i < spriteDice.size(); i++){
        target.draw(*spriteDice[i]);
    }
    target.draw(*score);
}

void Dice::update(int score, int dice1, int dice2){
    
    int width = 1280, height = 720;

    spriteDice[0]->setTextureRect(sf::IntRect(128 * (dice1 - 1), 0, 128, 128));
    spriteDice[1]->setTextureRect(sf::IntRect(128 * (dice2 - 1), 0, 128, 128));

    int gap = 20;
    this->score->setString(std::to_string(score));
    this->score->setCharacterSize(80);
    this->score->setOrigin(this->score->getGlobalBounds().width/2, 0);
    this->score->setPosition(width/2, spriteDice[0]->getPosition().y + gap/2 + spriteDice[0]->getGlobalBounds().height/2);
    
}


}
