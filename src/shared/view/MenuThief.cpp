#include "MenuThief.h"
#include "ButtonValidate.h"

namespace view{

MenuThief::MenuThief(state::State* state, sf::Texture menuTexture, state::PlayerColor playerColor, DisplayState* displayState){
    this->menuTexture = menuTexture;
    this->menuTexture.setSmooth(true);
    this->state = state;
    this->displayState = displayState;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(1384, 0, 351, 167));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 19;

    for(state::Player playersName : this->state->players){
        if(playersName.playerColor != this->state->turn)
            namePlayers.push_back(sf::Text(playersName.name, font, fontSize));
    }



    int gapbtwnames = 85;
    for(int i =0; i < (int) namePlayers.size(); i++){
        namePlayers[i].setColor(sf::Color(0, 0, 0));
        namePlayers[i].setOrigin(namePlayers[i].getGlobalBounds().width/2, 0);
        namePlayers[i].setPosition(spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + gapbtwnames * (i+1), spriteMenu->getPosition().y + 60);
    }

//     spriteButton = new sf::Sprite(this->menuTexture, sf::IntRect(0, 290, 178, 48));
//     spriteButton->setOrigin(spriteButton->getGlobalBounds().width/2, 0);
//     spriteButton->setPosition(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 100);

        sf::Texture buttonTexture;
        buttonTexture.loadFromFile("./../res/button.png");
        buttonTexture.setSmooth(true);
        buttonValidate = new view::ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 100, 122, 48), "Valider", this->displayState);

}



void MenuThief::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    for(sf::Text names : namePlayers){
        target.draw(names);
    }
    buttonValidate->render(target);
}

void MenuThief::update(){}



}