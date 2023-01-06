#include "MenuExchange.h"
#include "ButtonValidate.h"
#include "ButtonArrow.h"
#include <iostream>




namespace view{

MenuExchange::MenuExchange(state::State* state, sf::Texture menuTexture, state::PlayerColor playerColor, sf::IntRect coords, DisplayState* displayState){
    this->menuTexture = menuTexture;
    this->menuTexture.setSmooth(true);
    this->state = state;
    this->playerColor = playerColor;
    this->displayState = displayState;
    this->coords = coords;

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 24;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(434, 0, 598, 290));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);
    
    fontSize = 20;

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("./../res/button.png");
    buttonValidate = new view::ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x, spriteMenu->getPosition().y + 220, 122, 48), "Valider", this->displayState);
    
    int x = spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 105;
    int y = spriteMenu->getPosition().y + 170;
    buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(x, y, 143, 48), (Select_ID) (4), "Banque",  this->displayState));
    
    int gapname = 120, i =0;
    
    for(state::Player playersName : this->state->players){
        if(playersName.playerColor != playerColor){
            x = spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 280 + i*gapname; 
            y = spriteMenu->getPosition().y + 170;
            
            buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(x, y, 143, 48), (Select_ID) (i+4), playersName.name,  this->displayState));
            i++;
        }
    }
        

    int gap = 50;
    resourcesGiving.resize(5);
    resourcesAsking.resize(5);
    buttonsArrowGiving.resize(10);
    buttonsArrowReceiving.resize(10);
    
    for(int i = 0; i < 5; i++){
        
        resourcesGiving[i] = (state::Resource((state::ResourceType) i));
        
        numberResourcesGiving.push_back(sf::Text(std::to_string(resourcesGiving.back().number), font, fontSize));
        numberResourcesGiving[i].setColor(sf::Color(0, 0, 0));
        numberResourcesGiving[i].setPosition(spriteMenu->getPosition().x -spriteMenu->getGlobalBounds().width/2 + 23 + i*gap, spriteMenu->getGlobalBounds().top + 73);

        int x = numberResourcesGiving.back().getPosition().x;
        int y = numberResourcesGiving.back().getPosition().y;
        buttonsArrowGiving[2*i] = (new ButtonArrow(buttonTexture, sf::IntRect(x + 21, y - 12, 45, 13), ARROW_UP, this->displayState, &resourcesGiving[i]));
        buttonsArrowGiving[2*i + 1] = (new ButtonArrow(buttonTexture, sf::IntRect(x + 21, y + 30, 45, 13), ARROW_DOWN, this->displayState, &resourcesGiving[i]));


        resourcesAsking[i] = (state::Resource((state::ResourceType) i));

        numberResourcesAsking.push_back(sf::Text(std::to_string(resourcesAsking.back().number), font, fontSize));
        numberResourcesAsking.back().setColor(sf::Color(0, 0, 0));
        numberResourcesAsking.back().setPosition(spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + 326 + i*gap, spriteMenu->getGlobalBounds().top + 74);

        x = numberResourcesAsking.back().getPosition().x;
        y = numberResourcesAsking.back().getPosition().y;
        buttonsArrowReceiving[2 * i] = (new ButtonArrow(buttonTexture, sf::IntRect(x + 21, y - 12, 45, 13), ARROW_UP, this->displayState, &resourcesAsking[i]));
        buttonsArrowReceiving[2 * i + 1] = (new ButtonArrow(buttonTexture, sf::IntRect(x + 21, y + 30, 45, 13), ARROW_DOWN, this->displayState, &resourcesAsking[i]));

    }
}

void MenuExchange::render (sf::RenderTarget& target){
    update();
    target.draw(*spriteMenu);
    
    for(int i = 0; i < 5; i++){
        target.draw(numberResourcesGiving[i]);
        target.draw(numberResourcesAsking[i]);

        buttonsArrowGiving[i]->render(target);
        buttonsArrowGiving[i+5]->render(target);

        buttonsArrowReceiving[i]->render(target);
        buttonsArrowReceiving[i+5]->render(target);
    }

    for(int i = 0; i < 4; i++){
        buttonsSelect[i]->render(target);
        //target.draw(namePlayers[i]);
    }
    buttonValidate->render(target);
}


void MenuExchange::update (){
    for(int i =0; i < numberResourcesGiving.size(); i++){
        numberResourcesGiving[i].setString(std::to_string(resourcesGiving[i].number));
        numberResourcesAsking[i].setString(std::to_string(resourcesAsking[i].number));
    }
}

bool MenuExchange::isOnlyOne(){
    bool result = false;
    for(state::Resource r : resourcesGiving){
        if(r.number > 0){
            if(result)
                return false;
            result = true;
        }
    }
    if (result == false) return result;
    result = false;
    for(state::Resource r : resourcesAsking){
        if(r.number > 0){
            if(result)
                return false;
            result = true;
        }
    }
    return result;
}


}