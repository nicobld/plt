#include "MenuBuild.h"
#include "ButtonSelect.h"
#include <iostream>

static int getNumberOfCity(state::State* state, state::PlayerColor playerColor){
    int n = 0;
    for (int i = 0; i < state->map.buildings.size(); i++){
        if (state->map.buildings[i].buildingType == state::City && state->map.buildings[i].playerColor == playerColor)
            n++;
    }
    return n;
}

static int getNumberOfColony(state::State* state, state::PlayerColor playerColor){
    int n = 0;
    for (int i = 0; i < state->map.buildings.size(); i++){
        if (state->map.buildings[i].buildingType == state::Colony && state->map.buildings[i].playerColor == playerColor)
            n++;
    }
    return n;
}

static int getNumberOfRoads(state::State* state, state::PlayerColor playerColor){
    int n = 0;
    for (int i = 0; i < state->map.roads.size(); i++){
        if (state->map.roads[i].playerColor == playerColor)
            n++;
    }
    return n;
}

namespace view{

MenuBuild::MenuBuild(state::State* state, sf::Texture menuTexture, state::PlayerColor playerColor, sf::IntRect coords, DisplayState* displayState) : playerColor(playerColor){
    this->menuTexture = menuTexture;
    this->state = state;
    this->displayState = displayState;
    this->coords = coords;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(0, 0, 434, 269));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);
    
    textureRoad.loadFromFile("../res/roadsIso.png");
    texturePiece.loadFromFile("../res/pieces.png");
    textureIcon.loadFromFile("../res/icons.png");
    
    
    
    textureRoad.setSmooth(true);
    texturePiece.setSmooth(true);
    textureIcon.setSmooth(true);

    spritePieces.push_back(sf::Sprite(textureRoad, sf::IntRect(this->playerColor * 64, 0, 64, 32)));
    spritePieces.push_back(sf::Sprite(texturePiece, sf::IntRect(this->playerColor * 37, 0, 37, 37)));
    spritePieces.push_back(sf::Sprite(texturePiece, sf::IntRect((1 * 4 + this->playerColor)*37, 0, 37, 37)));
    spritePieces.push_back(sf::Sprite(textureIcon, sf::IntRect(8 * 74, 0, 74, 58)));
    spritePieces.back().setScale(sf::Vector2f(0.5, 0.5));

    int gap = 50;
    for(int h =0; h < (int) spritePieces.size() - 1; h++){
        spritePieces[h].setOrigin(spritePieces[h].getGlobalBounds().width/2, spritePieces[h].getGlobalBounds().height);
        spritePieces[h].setPosition(spriteMenu->getPosition().x + 123, spriteMenu->getPosition().y + 90 + h * gap);
    }

    spritePieces.back().setOrigin(spritePieces.back().getGlobalBounds().width/2, spritePieces.back().getGlobalBounds().height/2);
    spritePieces.back().setPosition(spriteMenu->getPosition().x + 115, spriteMenu->getPosition().y + 65 + 3 * gap);

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 19;

    numberPieces.push_back(sf::Text((std::to_string(getNumberOfRoads(state, playerColor)) + "/" + std::to_string(15)), font, fontSize));
    numberPieces.push_back(sf::Text((std::to_string(getNumberOfColony(state, playerColor)) + "/5"), font, fontSize));
    numberPieces.push_back(sf::Text((std::to_string(getNumberOfCity(state, playerColor)) + "/4"), font, fontSize));


    int gapwpieces = 80;
    for(int i =0; i < (int) numberPieces.size(); i++){
        numberPieces[i].setColor(sf::Color(0, 0, 0));
        numberPieces[i].setOrigin(numberPieces[i].getGlobalBounds().width, numberPieces[i].getGlobalBounds().height);
        numberPieces[i].setPosition(spritePieces[i].getPosition().x + gapwpieces, spritePieces[i].getPosition().y - 5);
    }

    

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("../res/button.png");
    gap = 50;
    for(int i = 0; i < spritePieces.size(); i++){
        buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spriteMenu->getPosition().x + 105, spriteMenu->getPosition().y + 52 + i * gap, 143, 48), (Select_ID) i, "", this->displayState));
    }

    
}

void MenuBuild::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    for (int i = 0; i < spritePieces.size(); i++){
        buttonsSelect[i]->render(target);
        target.draw(spritePieces[i]);
    }

    for(int i =0; i < (int) numberPieces.size(); i++){
        target.draw(numberPieces[i]);
        
    }
}

void MenuBuild::update(){}

}
