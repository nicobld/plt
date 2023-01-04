#include "StateView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "ButtonBuild.h"
#include "ButtonExchange.h"
#include "ButtonPassTurn.h"
#include "Menu.h"
#include "MenuBuild.h"
#include "MenuExchange.h"
#include "MenuAcceptExchange.h"
#include "MenuThief.h"

using namespace view;

StateView::StateView(state::State &state) : state(state)
{
    int width = 1280;
    int height = 720;

    this->displayState = STAND_BY;

    this->menuTexture = new sf::Texture();
    this->menuTexture->loadFromFile("../res/menu.png");
    this->menuTexture->setSmooth(true);

    this->squareTexture = new sf::Texture();
    this->squareTexture->loadFromFile("../res/squares.png");
    this->squareTexture->setSmooth(true);

    displayHUD = new DisplayHUD(width, height, &(state.players[0]), &(state.players[1]), &(state.players[2]), &(state.players[3]));

    tileMap = new TileMap();
    tileMap->load("../res/tilesHexIso.png", sf::Vector2u(114, 131), state.map.grid, 7, 7);

    renderPieces = new RenderPieces(state, &tileMap->hexagones);
    // tileMap->setOrigin((8*114)/2, 719/2);
    // tileMap->setPosition(width/2, 30 + height/2);
    // tileMap->setScale(sf::Vector2f(0.9, 0.9));
        
    int scrennGap = 30, ecartBouton = 60;
    clickableButton.push_back((Button *) new ButtonBuild(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 - ecartBouton*2, 199, 48), "Construire", &displayState));
    clickableButton.push_back((Button *) new ButtonExchange(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 - ecartBouton, 199, 48), "Echange", &displayState));
    clickableButton.push_back((Button *) new ButtonPassTurn(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 , 199, 48), "Passer son tour", &displayState));
}

void deleteMenu(std::vector<Menu*>* menu){
    for(auto m : *menu){
        delete m;
    }
    menu->clear();
}

void deleteButton(std::vector<Button*>* button){
    int b3 = 0;
    for(auto b : *button){
        if(b3 >=3){
            delete b;
            button->erase(button->begin()+ b3);
        }
        b3++;
    }
}

void StateView::render(sf::RenderTarget &target)
{
    renderPieces->render(state, target);
    for (int i = 0; i < clickableMenu.size(); i++)
    {
        clickableMenu[i]->render(target);  
    }

    for (int i = 0; i < clickableButton.size(); i++)
    {
    clickableButton[i]->render(target);
    }
}

void StateView::updateClickableObjects(state::State *state, state::PlayerColor playerColor)
{
    deleteMenu(&clickableMenu);
    deleteButton(&clickableButton);
    switch (displayState)
    {
    case STAND_BY:
        break;

    case CHOOSE_BUILD:
        clickableMenu.push_back(((Menu *)new MenuBuild(state, *menuTexture, state->turn, &displayState)));
        break;

    case EXCHANGE :
        clickableMenu.push_back(((Menu *)new MenuExchange(state, *menuTexture, state->turn, &displayState)));
        break;

    default:
        break;
    }
}

void StateView::clickedObjects(int x, int y)
{
    for (int i = 0; i < clickableButton.size(); i++)
    {
        clickableButton[i]->isClicked(x, y);
    }
}

void StateView::releasedObjects(int x, int y)
{
    for (int i = 0; i < clickableButton.size(); i++)
    {
        if (clickableButton[i]->isReleased(x, y)){
            updateClickableObjects(&state, state.turn);
            return;
        }        
    }
    displayState = STAND_BY;
    updateClickableObjects(&state, state.turn);
}

