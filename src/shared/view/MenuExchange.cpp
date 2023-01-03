#include "MenuExchange.h"
#include "ButtonValidate.h"
#include <iostream>

namespace view{

MenuExchange::MenuExchange(state::State* state, sf::Texture menuTexture, state::PlayerColor, DisplayState* displayState){
    this->menuTexture = menuTexture;
    this->menuTexture.setSmooth(true);
    this->state = state;
    this->playerColor = playerColor;
    this->displayState = displayState;

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 24;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(434, 0, 598, 290));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);
    

    namePlayers.push_back(sf::Text("Banque", font, fontSize));
    namePlayers.back().setColor(sf::Color(0, 0, 0));
    namePlayers.back().setPosition(spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 60 , spriteMenu->getPosition().y + 157);

    int i=0, gap = 50, gapname = 120;
    for(state::Player playersName : this->state->players){
        if(playersName.playerColor != playerColor){
            namePlayers.push_back(sf::Text(playersName.name, font, fontSize));
            namePlayers.back().setOrigin(namePlayers.back().getGlobalBounds().width/2, 0);
            namePlayers.back().setColor(sf::Color(0, 0, 0));
            namePlayers.back().setPosition(spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 270 + i*gapname , spriteMenu->getPosition().y + 157);
            i++;
        }
    }

    for(int i = 0; i < 5; i++){
        numberRessourcesGiving.push_back(sf::Text("0", font, fontSize));
        numberRessourcesGiving.back().setColor(sf::Color(0, 0, 0));
        numberRessourcesGiving.back().setPosition(spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 23 + i*gap, spriteMenu->getGlobalBounds().top + 73);

        numberRessourcesAsking.push_back(sf::Text("0", font, fontSize));
        numberRessourcesAsking.back().setColor(sf::Color(0, 0, 0));
        numberRessourcesAsking.back().setPosition(spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + 326 + i*gap, spriteMenu->getGlobalBounds().top + 74);
    }

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("./../res/button.png");
    buttonValidate = new view::ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 220, 122, 48), "Valider", this->displayState);
    
}

void MenuExchange::render (sf::RenderTarget& target){
    target.draw(*spriteMenu);
    
    for(int i = 0; i < 5; i++){
        target.draw(numberRessourcesGiving[i]);
        target.draw(numberRessourcesAsking[i]);
    }

    for(int i = 0; i < 4; i++){
        target.draw(namePlayers[i]);
    }
    buttonValidate->render(target);
}

void MenuExchange::update (){

}



}