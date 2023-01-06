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

static char* resTypeToString(state::ResourceType resType){
    if (resType == state::Wool)
        return "wool";
    else if (resType == state::Lumber)
        return "lumber";
    else if (resType == state::Brick)
        return "brick";
    else if (resType == state::Grain)
        return "grain";
    else if (resType == state::Ore)
        return "ore";
    else
        return "nothing";
}

namespace view{

StateView::StateView(state::State* state, engine::Engine* engine) : state(state)
{
    int width = 1280;
    int height = 720;

    this->displayState = STAND_BY;
    this->engine = engine;

    this->menuTexture = new sf::Texture();
    this->menuTexture->loadFromFile("../res/menu.png");
    this->menuTexture->setSmooth(true);

    this->squareTexture = new sf::Texture();
    this->squareTexture->loadFromFile("../res/squares.png");
    this->squareTexture->setSmooth(true);

    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[0]), &(state->players[1]), &(state->players[2]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[1]), &(state->players[0]), &(state->players[2]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[2]), &(state->players[0]), &(state->players[1]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[3]), &(state->players[0]), &(state->players[1]), &(state->players[2])));

    tileMap = new TileMap();
    tileMap->load("../res/tilesHexIso.png", sf::Vector2u(114, 131), state->map.grid, 7, 7);

    renderPieces = new RenderPieces(state, &tileMap->hexagones);
        
    int scrennGap = 30, ecartBouton = 60;
    clickableButton.push_back((Button *) new ButtonBuild(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 - ecartBouton*2, 199, 48), "Construire", &displayState));
    clickableButton.push_back((Button *) new ButtonExchange(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 - ecartBouton, 199, 48), "Echange", &displayState));
    clickableButton.push_back((Button *) new ButtonPassTurn(*this->squareTexture, sf::IntRect(width - scrennGap - 199/2, height - scrennGap - 48 , 199, 48), "Passer son tour", &displayState));
    
    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 24;

    fontPlayerColor.push_back(sf::Color(181, 53, 53));
    fontPlayerColor.push_back(sf::Color(69, 98, 184));
    fontPlayerColor.push_back(sf::Color(182, 148, 82));
    fontPlayerColor.push_back(sf::Color(70, 157, 70));

    playerTurnDisplay.push_back(new sf::Text("C'est votre tour", font, fontSize));
    playerTurnDisplay.back()->setColor(sf::Color(0, 0, 0));
    
    playerTurnDisplay.push_back(new sf::Text((std::string) state->players[state->turn].name, font, fontSize));
    playerTurnDisplay.back()->setColor(fontPlayerColor[state->turn]);
    
    int offset = playerTurnDisplay[0]->getGlobalBounds().width + playerTurnDisplay[1]->getGlobalBounds().width + 10 + 30;
    int heightPlayerTurn = 165;
    playerTurnDisplay[0]->setPosition(width - offset, heightPlayerTurn);
    playerTurnDisplay[1]->setPosition(playerTurnDisplay[0]->getPosition().x + playerTurnDisplay[0]->getGlobalBounds().width + 10, heightPlayerTurn);
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
    displayHUD[state->turn]->render(target);
    renderPieces->render(state, target);
    
    for(int i = 0; i < playerTurnDisplay.size(); i++){
        target.draw(*playerTurnDisplay[i]);
    }

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

void StateView::updateClickableObjects(state::PlayerColor playerColor)
{
    char s[64];
    state::Resource giving;
    state::Resource receiving;

    if(displayState != CHOOSING_EXCHANGE){
        deleteMenu(&clickableMenu);
        deleteButton(&clickableButton);
    }
    
    switch (displayState)
    {
    case STAND_BY :
        break;

    case CHOOSE_BUILD :
        clickableMenu.push_back((Menu *)new MenuBuild(state, *menuTexture, state->turn, sf::IntRect(1280/2 - 434/2, 720 - 269, 434, 269), &displayState));
        for (int i=0; i < ((MenuBuild*) clickableMenu.back())->buttonsSelect.size(); i++){
            clickableButton.push_back((Button*) ((MenuBuild*) clickableMenu.back())->buttonsSelect[i]);
        }
        
        break;

    case EXCHANGE :
        std::cout << "state turn : " << state->turn << std::endl;
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
        //menu d'attente de création de la commande échange
        if(((Button*)((MenuExchange*) clickableMenu.back())->buttonValidate)->clicked){
            std::cout << "a\n";
            if(((MenuExchange*) clickableMenu.back())->isOnlyOne()){
                std::cout << "echange !" << std::endl;
                
                for (state::Resource r : ((MenuExchange*) clickableMenu.back())->resourcesGiving)
                    if (r.number > 0) giving = r;
                for (state::Resource r : ((MenuExchange*) clickableMenu.back())->resourcesAsking)
                    if (r.number > 0) receiving = r;

                //commande d'échange
                sprintf(s, "request-%d-%s-%d-%s-%d", state->turn, resTypeToString(giving.resourceType), giving.number, resTypeToString(receiving.resourceType), receiving.number);
                engine->addSerializedCommand(s);

                displayState = STAND_BY;
               
            }
            else{
                ((Button*)((MenuExchange*) clickableMenu.back())->buttonValidate)->clicked = 0;
            }
        }
            
        break;

    case ACCEPT_EXCHANGE :

        break;


    case PLACE_THIEF :
        clickableMenu.push_back((Menu*) new MenuThief(state, *menuTexture, state->turn, sf::IntRect(1280/2 - 351, 720 - 167, 351, 167), &displayState));
        break;

    case THROW_DICE : 
        state->turn = (state::PlayerColor) ((state->turn +1) % 4);
        updatePlayerTurnDisplay();
        sprintf(s, "throwdice-%d", (int) state->turn);
        engine->addSerializedCommand(s);
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
            updateClickableObjects(state->turn);
            return;
        }
    }
    
    updateClickableObjects(state->turn);
}

void StateView::handleClick(int x, int y){
    std::array<state::Position, 2> pos;
    switch (displayState) {
        case STAND_BY:
            break;

        case BUILD_ROAD:
            pos = tileMap->findClosestRoad(x, y);
            engine->addCommand( new engine::PlaceRoadCommand((state::PlayerColor)0, pos));
            break;

        default:
            break;
        }
}

void StateView::updatePlayerTurnDisplay(){
    int width = 1280;

    playerTurnDisplay[1]->setString(state->players[state->turn].name);
    playerTurnDisplay[1]->setColor(fontPlayerColor[state->turn]);
    
    int offset = playerTurnDisplay[0]->getGlobalBounds().width + playerTurnDisplay[1]->getGlobalBounds().width + 10 + 30;
    int heightPlayerTurn = 165;

    playerTurnDisplay[0]->setPosition(width - offset, heightPlayerTurn);
    playerTurnDisplay[1]->setPosition(playerTurnDisplay[0]->getPosition().x + playerTurnDisplay[0]->getGlobalBounds().width + 10, heightPlayerTurn);
}

}