#include "MenuChooseName.h"
#include <iostream>

namespace view{

MenuChooseName::MenuChooseName(sf::Texture menuTexture, sf::IntRect coords, DisplayState* displayState){
    this->menuTexture = menuTexture;
    this->displayState = displayState;
    this->coords = coords;

    font.loadFromFile("../res/poppins.ttf");
    fontSize = 20;

    nameSelected = -1;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(2173, 0, 621, 609));
    spriteMenu->setScale(sf::Vector2f(0.65, 0.65));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2 - 90, 720 - spriteMenu->getGlobalBounds().height - 50);

    fontPlayerColor[0] = (sf::Color(181, 53, 53));
    fontPlayerColor[1] = (sf::Color(69, 98, 184));
    fontPlayerColor[2] = (sf::Color(182, 148, 82));
    fontPlayerColor[3] = (sf::Color(70, 157, 70));
    
    int gap = 75;
    for(int i = 0; i < 4; i++){
        namePlayers[i] = sf::Text("", font, fontSize);
        namePlayers[i].setColor(fontPlayerColor[i]);
        namePlayers[i].setOrigin(namePlayers[i].getGlobalBounds().width, 0);
        namePlayers[i].setPosition(spriteMenu->getPosition().x + spriteMenu->getGlobalBounds().width/2 - 45, spriteMenu->getPosition().y + 37 + gap * i);

        coordsName[i] = sf::IntRect(spriteMenu->getPosition().x + 168, spriteMenu->getPosition().y + 28 + gap * i, 45, 45);
    }

    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("../res/button.png");
    buttonValidate = new ButtonValidate(buttonTexture, sf::IntRect(spriteMenu->getPosition().x + spriteMenu->getGlobalBounds().width/2 - 125, spriteMenu->getPosition().y + spriteMenu->getGlobalBounds().height - 70, 135, 135), "Commencer",  this->displayState);


}

void MenuChooseName::render(sf::RenderTarget& target){
    target.draw(*spriteMenu);
    for(int i = 0; i < 4; i++){
        target.draw(namePlayers[i]);
        // sf::RectangleShape shape;
        // shape.setSize(sf::Vector2f(coordsName[i].width, coordsName[i].height));
        // shape.setPosition(coordsName[i].left, coordsName[i].top);
        // shape.setFillColor(sf::Color(255, 255, 255, 125));
        // target.draw(shape);
    }
    

    buttonValidate->render(target);
}

void MenuChooseName::update(){}

void MenuChooseName::updateNameSelected(int x, int y){
    for(int i = 0; i < 4; i++){
        if(coordsName[i].contains(x, y)){
            nameSelected = i;
        }
    }
}

void MenuChooseName::updateText(char letter){
    if(nameSelected >=0 && namePlayers[nameSelected].getString().getSize() < 10){
        namePlayers[nameSelected].setString(namePlayers[nameSelected].getString() + letter);
        namePlayers[nameSelected].setOrigin(namePlayers[nameSelected].getGlobalBounds().width, 0);
        namePlayers[nameSelected].setPosition(spriteMenu->getPosition().x + spriteMenu->getGlobalBounds().width/2 - 45, namePlayers[nameSelected].getPosition().y);
    }
}

}