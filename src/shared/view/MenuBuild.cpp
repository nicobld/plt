#include "MenuBuild.h"
#include "ButtonSelect.h"

namespace view{

MenuBuild::MenuBuild(state::State* state, sf::Texture menuTexture, state::PlayerColor playerColor, DisplayState* displayState) : playerColor(playerColor){
    this->menuTexture = menuTexture;
    this->state = state;
    this->displayState = displayState;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(0, 0, 434, 269));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);
    
    textureRoad.loadFromFile("../res/roadsIso.png");
    texturePiece.loadFromFile("../res/pieces.png");
    textureRoad.setSmooth(true);
    texturePiece.setSmooth(true);

    spritePieces.push_back(sf::Sprite(textureRoad, sf::IntRect(this->playerColor * 64, 0, 64, 32)));
    spritePieces.push_back(sf::Sprite(texturePiece, sf::IntRect(this->playerColor * 37, 0, 37, 37)));
    spritePieces.push_back(sf::Sprite(texturePiece, sf::IntRect((1 * 4 + this->playerColor)*37, 0, 37, 37)));

    int gap = 50;
    for(int h =0; h < (int) spritePieces.size(); h++){
        spritePieces[h].setOrigin(spritePieces[h].getGlobalBounds().width/2, spritePieces[h].getGlobalBounds().height);
        spritePieces[h].setPosition(spriteMenu->getPosition().x + 123, spriteMenu->getPosition().y + 90 + h * gap);
    }

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 19;

    numberPieces.push_back(sf::Text((std::to_string(state->map.roads.size()) + "/" + std::to_string(state->players[this->playerColor].roads.size())), font, fontSize));
    numberPieces.push_back(sf::Text((std::to_string(state->map.buildings.size()) + "/5"), font, fontSize));
    numberPieces.push_back(sf::Text((std::to_string(state->map.buildings.size()) + "/4"), font, fontSize));


    int gapwpieces = 80;
    for(int i =0; i < (int) numberPieces.size(); i++){
        numberPieces[i].setColor(sf::Color(0, 0, 0));
        numberPieces[i].setOrigin(numberPieces[i].getGlobalBounds().width, numberPieces[i].getGlobalBounds().height);
        numberPieces[i].setPosition(spritePieces[i].getPosition().x + gapwpieces, spritePieces[i].getPosition().y - 5);
    }

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("./../res/button.png");
    // buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spritePieces[0].getGlobalBounds().left, spritePieces[0].getGlobalBounds().top, 143, 48), SELECT_ROAD, this->displayState));
    // buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spritePieces[1].getGlobalBounds().left, spritePieces[1].getGlobalBounds().top, 143, 48), SELECT_COLONY, this->displayState));
    // buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spritePieces[2].getGlobalBounds().left, spritePieces[2].getGlobalBounds().top, 143, 48), SELECT_ROAD, this->displayState));
    // buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spritePieces[3].getGlobalBounds().left, spritePieces[3].getGlobalBounds().top, 143, 48), SELECT_DEV, this->displayState));
    gap = 50;
    for(int i = 0; i < 3; i++){
        buttonsSelect.push_back(new ButtonSelect(buttonTexture, sf::IntRect(spriteMenu->getPosition().x + 105, spriteMenu->getPosition().y + 52 + i * gap, 143, 48), (Select_ID) i, this->displayState));
    }

}

void MenuBuild::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    for (int i = 0; i<buttonsSelect.size(); i++){
        buttonsSelect[i]->render(target);
    }

    for(int i =0; i < (int) spritePieces.size(); i++){
        target.draw(spritePieces[i]);
        target.draw(numberPieces[i]);
        
    }
}

void MenuBuild::update(){}

}
