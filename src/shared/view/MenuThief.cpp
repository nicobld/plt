#include "MenuThief.h"
#include "ButtonValidate.h"
#include "ButtonSelect.h"

namespace view{

MenuThief::MenuThief(state::State* state, sf::Texture menuTexture, state::PlayerColor playerColor, std::vector<state::Player> playerToSteal, sf::IntRect coords, DisplayState* displayState){
    this->menuTexture = menuTexture;
    this->menuTexture.setSmooth(true);
    this->state = state;
    this->displayState = displayState;
    this->coords = coords;
    this->playerToSteal = playerToSteal;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(1385, 0, 450, 134));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 20;

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("./../res/button.png");
    buttonTexture.setSmooth(true);

    int gapbtwnames = spriteMenu->getGlobalBounds().width / playerToSteal.size();
    int offset = gapbtwnames/2, i = 0, x, y;

    // for(state::Player playersName : this->state->players){
    for(state::Player playersName : this->playerToSteal){
        if(playersName.playerColor != playerColor){
            x = spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + gapbtwnames * (i) + offset;
            y = spriteMenu->getPosition().y + spriteMenu->getGlobalBounds().height/2 + 10;
            
            buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(x, y, 143, 48), (Select_ID) (i+4), playersName.name,  this->displayState));
            i++;
        }
    }

        //buttonValidate = new view::ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 100, 122, 48), "Valider", this->displayState);

}



void MenuThief::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    for(int i = 0; i < buttonsSelect.size(); i++){
        buttonsSelect[i]->render(target);
    }
    //buttonValidate->render(target);


}

void MenuThief::update(){}



}