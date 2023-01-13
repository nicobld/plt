#include "MenuResource.h"
#include "ButtonSelect.h"
#include <iostream>

namespace view{

MenuResource:: MenuResource (sf::Texture menuTexture, sf::IntRect coords, DisplayState* displayState){

    this->menuTexture = menuTexture;
    this->displayState = displayState;
    this->coords = coords;

    spriteMenu = new sf::Sprite(this->menuTexture, sf::IntRect(1834, 0, 338, 117));
    spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);

    textureResource.loadFromFile("../res/icons.png");
    textureResource.setSmooth(true);
    
    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("../res/button.png");

    int gap = (spriteMenu->getGlobalBounds().width - 10)/spriteResource.size() ;
    for(int i = 0; i < spriteResource.size(); i++){
        buttonsSelect[i] = new ButtonSelect(buttonTexture, sf::IntRect(spriteMenu->getPosition().x - spriteMenu->getGlobalBounds().width/2 + 20 + i*gap, spriteMenu->getPosition().y + 52, 143, 48), SELECT_RESOURCE, "", displayState);
        spriteResource[i] = new sf::Sprite(textureResource, sf::IntRect(i * 74, 0, 74, 58));
        spriteResource[i]->setScale(sf::Vector2f(0.5, 0.5));
        spriteResource[i]->setOrigin(spriteResource[i]->getGlobalBounds().width/2, spriteResource[i]->getGlobalBounds().height/2);
        spriteResource[i]->setPosition(buttonsSelect[i]->coords.left + buttonsSelect[i]->coords.width/2 - 5, buttonsSelect[i]->coords.top + buttonsSelect[i]->coords.height/4 + 2);
    }
    std::cout << "width button" << buttonsSelect[0]->coords.width << std::endl;

}

void MenuResource::render (sf::RenderTarget& target){
    target.draw(*spriteMenu);

    for(int i = 0; i < spriteResource.size(); i++){
        buttonsSelect[i]->render(target);
        target.draw(*spriteResource[i]);
    }
}

    
void MenuResource::update (){}

int MenuResource::resourceClicked(){
    for(int i = 0; i < buttonsSelect.size(); i++){
        if(buttonsSelect[i]->clicked)
            return i;
    }
    return -1;
}

}