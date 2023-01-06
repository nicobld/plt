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
    for(int i = 3; i < button->size(); i++){
            button->erase(button->begin()+ i);
    }
}

void StateView::render(sf::RenderTarget &target)
{
    displayHUD->render(target);
    renderPieces->render(state, target);
    for (int i = 0; i < clickableMenu.size(); i++)
    {
        clickableMenu[i]->render(target);
    }

    //for (int i = 0; i < clickableButton.size(); i++)
    for (int i = 0; i < 3; i++)
    {
    clickableButton[i]->render(target);
    }
}

void StateView::updateClickableObjects(state::State *state, state::PlayerColor playerColor)
{
    if(displayState != CHOOSING_EXCHANGE){
        deleteMenu(&clickableMenu);
        deleteButton(&clickableButton);
    }
    
    switch (displayState)
    {
    case STAND_BY :
        break;

    case CHOOSE_BUILD :

    // spriteMenu->setOrigin(spriteMenu->getGlobalBounds().width/2, 0);
    // spriteMenu->setPosition(1280/2, 720 - spriteMenu->getGlobalBounds().height);

        clickableMenu.push_back((Menu *)new MenuBuild(state, *menuTexture, state->turn, sf::IntRect(1280/2 - 434/2, 720 - 269, 434, 269), &displayState));
        for (int i=0; i < ((MenuBuild*) clickableMenu.back())->buttonsSelect.size(); i++){
            clickableButton.push_back((Button*) ((MenuBuild*) clickableMenu.back())->buttonsSelect[i]);
        }
        
        break;

    case EXCHANGE :
        clickableMenu.push_back((Menu *)new MenuExchange(state, *menuTexture, state->turn, sf::IntRect(1280/2 - 598/2 , 720 - 290, 598, 290), &displayState));
        for (int i=0; i < ((MenuExchange*) clickableMenu.back())->buttonsArrowGiving.size(); i++){
            clickableButton.push_back((Button*) ((MenuExchange*) clickableMenu.back())->buttonsArrowGiving[i]);
            clickableButton.push_back((Button*) ((MenuExchange*) clickableMenu.back())->buttonsArrowReceiving[i]);

        }

        for (int i=0; i < ((MenuExchange*) clickableMenu.back())->buttonsSelect.size(); i++){
            clickableButton.push_back((Button*) ((MenuExchange*) clickableMenu.back())->buttonsSelect[i]);
        }
        
        clickableButton.push_back((Button*) ((MenuExchange*) clickableMenu.back())->buttonValidate);
        
        displayState = CHOOSING_EXCHANGE;
        
        break;

    case CHOOSING_EXCHANGE :
        //just here to not recreate menu/button
        break;


    case PLACE_THIEF :
        clickableMenu.push_back((Menu*) new MenuThief(state, *menuTexture, state->turn, sf::IntRect(1280/2 - 351, 720 - 167, 351, 167), &displayState));
        break;

    case THROW_DICE : 

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
    if(clickableMenu.size() > 0){ 
        if(!clickableMenu.back()->isClicked(x, y))
            displayState = STAND_BY;
    }
    for (int i = 0; i < clickableButton.size(); i++)
    {
        if (clickableButton[i]->isReleased(x, y)){
            updateClickableObjects(&state, state.turn);
            return;
        }       
    }
    
    updateClickableObjects(&state, state.turn);
}

