#include "MenuAcceptExchange.h"
#include <string>
#include "ButtonValidate.h"
#include "ButtonDeny.h"


namespace view {

MenuAcceptExchange::MenuAcceptExchange (state::State* state, sf::Texture menuTexture, state::PlayerColor playerProposing, state::Resource resourceGiving, state::Resource resourceReceiving, sf::IntRect coords, DisplayState* displayState){

    this->menuTexture = menuTexture;
    this->playerProposing = playerProposing;
    this->state = state;
    this->resourceGiving = resourceGiving;
    this->resourceReceiving = resourceReceiving;
    this->displayState = displayState;
    this->coords = coords;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(1032, 0, 351, 205));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 19;
    
    std::string sentenceExchange = this->state->players[this->playerProposing].name + " veut faire un echange";
    
    playerProposingName = new sf::Text(sentenceExchange, font, fontSize+2);
    playerProposingName->setColor(sf::Color(0, 0, 0));
    playerProposingName->setOrigin(playerProposingName->getGlobalBounds().width/2, 0);
    playerProposingName->setPosition(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 20);

    icon.loadFromFile("./../res/icons.png");
    resources.push_back(sf::Sprite(icon, sf::IntRect(this->resourceGiving.resourceType * 73, 0, 74, 58)));
    resources.push_back(sf::Sprite(icon, sf::IntRect(this->resourceReceiving.resourceType * 73, 0, 74, 58)));

    resourcesNumber.push_back(sf::Text(std::to_string(this->resourceGiving.number), font, fontSize));
    resourcesNumber.push_back(sf::Text(std::to_string(this->resourceReceiving.number), font, fontSize));
    
    for(int i=0; i<2; i++){
        resources[i].setScale(sf::Vector2f(0.5, 0.5));
        resources[i].setPosition(spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + 80 + 160*i, spriteMenu->getPosition().y +85);
        resourcesNumber[i].setColor(sf::Color(0, 0, 0));
        resourcesNumber[i].setPosition(resources[i].getPosition().x -15, resources[i].getPosition().y + 5);
    }

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("./../res/button.png");
    buttonValidate = new view::ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x + 75, spriteMenu->getPosition().y + 130, 122, 48), "Accepter",this->displayState);
    buttonDeny = new view::ButtonDeny(buttonTexture, sf::IntRect(spriteMenu->getPosition().x - 75, spriteMenu->getPosition().y + 130, 122, 48), "Refuser", this->displayState);

}

void MenuAcceptExchange::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    target.draw(*playerProposingName);
    
    for(int i=0; i<2; i++){
        target.draw(resources[i]);
        target.draw(resourcesNumber[i]);
    }

    buttonValidate->render(target);
    buttonDeny->render(target);

}

void MenuAcceptExchange::update(){}


}