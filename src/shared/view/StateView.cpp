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
#include "MenuResource.h"
#include "Hand.h"
#include <cstring>

static char *resTypeToString(state::ResourceType resType)
{
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

static state::PlayerColor nameToPlayerColor(state::State* state, std::string string){
    for (state::Player p : state->players){
        if (p.name == string){
            return p.playerColor;
        }
    }
    return (state::PlayerColor) -1;
}

static char *cardIDToString(view::Card_ID card_ID)
{
    if (card_ID == view::CARD_KNIGHT)
        return "knight";
    else if (card_ID == view::CARD_MONOPOLY)
        return "monopoly";
    else if (card_ID == view::CARD_CONSTRUCTION_ROAD)
        return "roadconstruction";
    else if (card_ID == view::CARD_INVENTION)
        return "invention";
    else if (card_ID == view::CARD_VICTORY_POINT)
        return "victorypoint";
    else
        return "nothing";
}

namespace view
{

StateView::StateView(state::State *state, engine::Engine *engine) : state(state)
{
    int width = 1280;
    int height = 720;

    this->engine = engine;

    this->menuTexture = new sf::Texture();
    this->menuTexture->loadFromFile("../res/menu.png");
    this->menuTexture->setSmooth(true);

    this->squareTexture = new sf::Texture();
    this->squareTexture->loadFromFile("../res/squares.png");
    this->squareTexture->setSmooth(true);

    focusTexture = new sf::Texture();
    focusTexture->loadFromFile("../res/focus.png");

    cardTexture = new sf::Texture();
    cardTexture->loadFromFile("../res/developmentCards.png");
    cardTexture->setSmooth(true);
    
    spriteFocus = new sf::Sprite(*focusTexture);
    spriteFocus->setScale(sf::Vector2f(0.9, 0.9));
    spriteFocus->setOrigin(spriteFocus->getGlobalBounds().width/2, spriteFocus->getGlobalBounds().height/2);
    spriteFocus->setPosition(width/2, height/2);

    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[0]), &(state->players[1]), &(state->players[2]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[1]), &(state->players[0]), &(state->players[2]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[2]), &(state->players[0]), &(state->players[1]), &(state->players[3])));
    displayHUD.push_back(new DisplayHUD(width, height, &(state->players[3]), &(state->players[0]), &(state->players[1]), &(state->players[2])));

    displayState[0] = STAND_BY;
    displayState[1] = STAND_BY;
    displayState[2] = STAND_BY;
    displayState[3] = STAND_BY;

    viewPlayer = (state::PlayerColor)0;

    tileMap = new TileMap();
    tileMap->load("../res/tilesHexIso.png", sf::Vector2u(114, 131), state->map.grid, 7, 7);

    renderPieces = new RenderPieces(state, &tileMap->hexagones);

    int scrennGap = 30, ecartBouton = 60;
    clickableButton.push_back((Button *)new ButtonBuild(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48 - ecartBouton * 2, 199, 48), "Construire", &(displayState[0])));
    clickableButton.push_back((Button *)new ButtonExchange(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48 - ecartBouton, 199, 48), "Echange", &(displayState[0])));
    clickableButton.push_back((Button *)new ButtonPassTurn(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48, 199, 48), "Passer son tour", &(displayState[0])));

    font.loadFromFile("../res/poppins.ttf");
    int fontSize = 24;

    fontPlayerColor[0] = (sf::Color(181, 53, 53));
    fontPlayerColor[1] = (sf::Color(69, 98, 184));
    fontPlayerColor[2] = (sf::Color(182, 148, 82));
    fontPlayerColor[3] = (sf::Color(70, 157, 70));

    playerTurnDisplay.push_back(new sf::Text("C'est votre tour", font, fontSize));
    playerTurnDisplay.back()->setColor(sf::Color(0, 0, 0));

    playerTurnDisplay.push_back(new sf::Text((std::string)state->players[state->turn].name, font, fontSize));
    playerTurnDisplay.back()->setColor(fontPlayerColor[state->turn]);

    int offset = playerTurnDisplay[0]->getGlobalBounds().width + playerTurnDisplay[1]->getGlobalBounds().width + 10 + 30;
    int heightPlayerTurn = 165;
    playerTurnDisplay[0]->setPosition(width - offset, heightPlayerTurn);
    playerTurnDisplay[1]->setPosition(playerTurnDisplay[0]->getPosition().x + playerTurnDisplay[0]->getGlobalBounds().width + 10, heightPlayerTurn);
    
    for(int i = 0; i < 4; i++){
        handPlayers.push_back(Hand(cardTexture, (state::PlayerColor) i, state));
    }
    
}

void deleteMenu(std::vector<Menu *> *menu)
{
    for (auto m : *menu)
    {
        delete m;
    }
    menu->clear();
}

void deleteButton(std::vector<Button *> *button)
{
    for (int i = 3; i < button->size(); i++)
    {
        delete button->at(i);
        button->erase(button->begin() + i);
    }
}

void deleteTroisButton(std::vector<Button *> *button){
    for (int i = 0; i < button->size(); i ++){
        delete button->at(i);
    }
    button->clear();
}

void StateView::render(sf::RenderTarget &target)
{
    
    target.draw(*tileMap);
    renderPieces->render(state, target);
    target.draw(*spriteFocus);

    if (clickableButton[2]->clicked)
        displayHUD[state->turn]->render(target);
    else
        displayHUD[viewPlayer]->render(target);

    

    for (int i = 0; i < playerTurnDisplay.size(); i++)
    {
        target.draw(*playerTurnDisplay[i]);
    }

    for (int i = 0; i < clickableMenu.size(); i++)
    {
        clickableMenu[i]->render(target);
    }

    // for (int i = 0; i < clickableButton.size(); i++)
    for (int i = 0; i < 3; i++)
    {
        clickableButton[i]->render(target);
    }

    //----------Cards------------
    
    handPlayers[viewPlayer].render(target);

    updateClickableObjects(state->turn);
}

void StateView::updateClickableObjects(state::PlayerColor playerColor)
{
    handPlayers[viewPlayer].updateHand();
    char s[64];
    state::Resource giving;
    state::Resource receiving;
    if (state->turn != viewPlayer){
        viewPlayer = state->turn;
        updatePlayerTurnDisplay();
        reloadTroisButtons();
    }

    if (state->players[viewPlayer].playerState == state::EXCHANGE){
        displayState[viewPlayer] = ACCEPT_EXCHANGE;
    }
    else if (state->gameState == state::PLACE_THIEF_STATE){
        displayState[state->turn] = PLACE_THIEF;
    }
    else if (state->gameState == state::STEAL_CARD_STATE){
        displayState[state->turn] = STEAL_PLAYER;
    }
    else if (state->gameState == state::ROAD_CONSTRUCTION_STATE){
        displayState[state->turn] = BUILD_ROAD;
    }



    if (displayState[viewPlayer] != CHOOSING_EXCHANGE) //c'est un menu qui reste ouvert longtemps
    {
        deleteMenu(&clickableMenu);
        deleteButton(&clickableButton);
    }

    switch (displayState[viewPlayer])
    {
    case STAND_BY:
        // clickableMenu.push_back((Menu *)new MenuResource(*menuTexture, sf::IntRect(1280 / 2 - 434 / 2, 720 - 269, 434, 269), &(displayState[viewPlayer])));
        // for (int i = 0; i < ((MenuResource *)clickableMenu.back())->buttonsSelect.size(); i++)
        //     clickableButton.push_back((Button *)((MenuResource *)clickableMenu.back())->buttonsSelect[i]);
        // std::cout << "ressource " << resTypeToString((state::ResourceType) ((MenuResource *) clickableMenu.back())->resourceClicked()) << std::endl;
        break;

    case CHOOSE_BUILD:
        clickableMenu.push_back((Menu *)new MenuBuild(state, *menuTexture, viewPlayer, sf::IntRect(1280 / 2 - 434 / 2, 720 - 269, 434, 269), &(displayState[viewPlayer])));
        for (int i = 0; i < ((MenuBuild *)clickableMenu.back())->buttonsSelect.size(); i++)
        {
            clickableButton.push_back((Button *)((MenuBuild *)clickableMenu.back())->buttonsSelect[i]);
        }

        break;

    case EXCHANGE:
        clickableMenu.push_back((Menu *)new MenuExchange(state, *menuTexture, viewPlayer, sf::IntRect(1280 / 2 - 598 / 2, 720 - 290, 598, 290), &(displayState[viewPlayer])));
        for (int i = 0; i < ((MenuExchange *)clickableMenu.back())->buttonsArrowGiving.size(); i++)
        {
            clickableButton.push_back((Button *)((MenuExchange *)clickableMenu.back())->buttonsArrowGiving[i]);
            clickableButton.push_back((Button *)((MenuExchange *)clickableMenu.back())->buttonsArrowReceiving[i]);
        }

        for (int i = 0; i < ((MenuExchange *)clickableMenu.back())->buttonsSelect.size(); i++)
        {
            clickableButton.push_back((Button *)((MenuExchange *)clickableMenu.back())->buttonsSelect[i]);
        }

        clickableButton.push_back((Button *)((MenuExchange *)clickableMenu.back())->buttonValidate);

        displayState[viewPlayer] = CHOOSING_EXCHANGE;

        break;

    case CHOOSING_EXCHANGE:
        // menu d'attente de création de la commande échange
        if (((Button *)((MenuExchange *)clickableMenu.back())->buttonValidate)->clicked)
        {
            if (((MenuExchange *)clickableMenu.back())->isOnlyOne())
            {
                std::cout << "echange !" << std::endl;

                for (state::Resource r : ((MenuExchange *)clickableMenu.back())->resourcesGiving)
                    if (r.number > 0)
                        giving = r;
                for (state::Resource r : ((MenuExchange *)clickableMenu.back())->resourcesAsking)
                    if (r.number > 0)
                        receiving = r;

                // commande d'échange
                sprintf(s, "request-%d-%s-%d-%s-%d", viewPlayer, resTypeToString(giving.resourceType), giving.number, resTypeToString(receiving.resourceType), receiving.number);
                engine->addSerializedCommand(s);

                // displayState = ACCEPT_EXCHANGE;
            }
            else
            {
                ((Button *)((MenuExchange *)clickableMenu.back())->buttonValidate)->clicked = 0;
            }
        }

        break;

    case ACCEPT_EXCHANGE:
        clickableMenu.push_back((Menu *)new MenuAcceptExchange(state, *menuTexture, state->turn, giving, receiving, sf::IntRect(1280 / 2 - 351 / 2, 720 - 205, 351, 205), &(displayState[viewPlayer])));
        clickableButton.push_back((Button *)((MenuAcceptExchange *)clickableMenu.back())->buttonValidate);
        clickableButton.push_back((Button *)((MenuAcceptExchange *)clickableMenu.back())->buttonDeny);
        break;

    case STEAL_PLAYER:
        std::cout << "menu thief\n";
        clickableMenu.push_back((Menu *)new MenuThief(state, *menuTexture, viewPlayer, sf::IntRect(1280 / 2 - 351, 720 - 167, 351, 167), &(displayState[viewPlayer])));
        for (int i = 0; i < ((MenuThief*) clickableMenu.back())->buttonsSelect.size(); i++)
            clickableButton.push_back((Button*) ((MenuThief*) clickableMenu.back())->buttonsSelect[i]);
        break;

    case THROW_DICE:
        sprintf(s, "throwdice-%d", viewPlayer);
        engine->addSerializedCommand(s);
        break;

    default:
        break;
    }

}

void StateView::displayStateEffect(){
    char s[64];
    switch (displayState[viewPlayer]){
    case ACCEPT_EXCHANGE:
        if (((Button*) ((MenuAcceptExchange *)clickableMenu.back())->buttonValidate )->clicked)
        {
            std::cout << "échange accepter !" << std::endl;
            sprintf(s, "response-%d-1", viewPlayer);
            engine->addSerializedCommand(s);
            displayState[viewPlayer] = STAND_BY;
        }
        else if (((Button *)((MenuAcceptExchange *)clickableMenu.back())->buttonDeny)->clicked)
        {
            std::cout << "échange refusé..." << std::endl;
            sprintf(s, "response-%d-0", viewPlayer);
            engine->addSerializedCommand(s);
            displayState[viewPlayer] = STAND_BY;
        }
        break;

    case STEAL_PLAYER:
        for (int i = 3; i < clickableButton.size(); i++){
            if (clickableButton[i]->clicked){
                sprintf(s, "stealcard-%d-%d", (int) viewPlayer, (int) nameToPlayerColor(state, ((ButtonSelect*) clickableButton[i])->message));
                engine->addSerializedCommand(s);
                return;
            }
        }
        if (state->gameState != state::STEAL_CARD_STATE){
            displayState[viewPlayer] = STAND_BY;
        }
        break;
    }
        
}

void StateView::clickedObjects(int x, int y)
{
    char s[64];
    updateClickableObjects(viewPlayer);
    for (int i = 0; i < clickableButton.size(); i++)
    {
        clickableButton[i]->isClicked(x, y);
    }
    int c_id = -1;
    if((c_id = handPlayers[viewPlayer].isClicked(x, y)) != -1){
        std::cout << "dev type : " << cardIDToString(handPlayers[viewPlayer].cards[c_id].card_ID) << std::endl;
        sprintf(s, "usecard-%d-%s", viewPlayer, cardIDToString(handPlayers[viewPlayer].cards[c_id].card_ID));
        engine->addSerializedCommand(s);
    }

    displayStateEffect();
}

void StateView::releasedObjects(int x, int y)
{
    if (clickableMenu.size() > 0)
    {
        if (!clickableMenu.back()->isClicked(x, y)){
            displayState[viewPlayer] = STAND_BY;
            updateClickableObjects(viewPlayer);
        }
    }
    for (int i = 0; i < clickableButton.size(); i++)
    {
        if (clickableButton[i]->isReleased(x, y))
        {
            updateClickableObjects(viewPlayer);
            return;
        }
    }

    
}

void StateView::handleClick(int x, int y)
{
    std::array<state::Position, 3> buildPos;
    std::array<state::Position, 2> roadPos;
    state::Position pos;
    char s[64];

    switch (displayState[viewPlayer])
    {
    case STAND_BY:
        break;

    case BUILD_ROAD:
        roadPos = tileMap->findClosestRoad(x, y);
        sprintf(s, "placeroad-%d-%d-%d-%d-%d", viewPlayer, roadPos[0].x, roadPos[0].y, roadPos[1].x, roadPos[1].y);
        engine->addSerializedCommand(s);
        break;

    case BUILD_CITY_DISPLAY:
        buildPos = tileMap->findClosestBuilding(x, y);
        sprintf(s, "placebuilding-%d-%d-%d-%d-%d-%d-%d-1", viewPlayer, buildPos[0].x, buildPos[0].y, buildPos[1].x, buildPos[1].y, buildPos[2].x, buildPos[2].y);
        engine->addSerializedCommand(s);
        break;

    case BUILD_COLONY_DISPLAY:
        buildPos = tileMap->findClosestBuilding(x, y);
        sprintf(s, "placebuilding-%d-%d-%d-%d-%d-%d-%d-0", viewPlayer, buildPos[0].x, buildPos[0].y, buildPos[1].x, buildPos[1].y, buildPos[2].x, buildPos[2].y);
        engine->addSerializedCommand(s);
        break;

    case DRAW_CARD_DISPLAY:
        sprintf(s, "drawcard-%d", viewPlayer);
        engine->addSerializedCommand(s);
        break;

    case PLACE_THIEF:
        pos = tileMap->findClosestTile(x, y);
        sprintf(s, "placethief-%d-%d-%d", viewPlayer, pos.x, pos.y);
        engine->addSerializedCommand(s);
        break;

    default:
        break;
    }


}

void StateView::reloadTroisButtons(){
    int width = 1280;
    int height = 720;
    int scrennGap = 30, ecartBouton = 60;
    deleteTroisButton(&clickableButton);
    clickableButton.push_back((Button *)new ButtonBuild(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48 - ecartBouton * 2, 199, 48), "Construire", &(displayState[viewPlayer])));
    clickableButton.push_back((Button *)new ButtonExchange(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48 - ecartBouton, 199, 48), "Echange", &(displayState[viewPlayer])));
    clickableButton.push_back((Button *)new ButtonPassTurn(*this->squareTexture, sf::IntRect(width - scrennGap - 199 / 2, height - scrennGap - 48, 199, 48), "Passer son tour", &(displayState[viewPlayer])));
}

void StateView::updatePlayerTurnDisplay()
{
    int width = 1280;

    playerTurnDisplay[1]->setString(state->players[state->turn].name);
    playerTurnDisplay[1]->setColor(fontPlayerColor[state->turn]);

    int offset = playerTurnDisplay[0]->getGlobalBounds().width + playerTurnDisplay[1]->getGlobalBounds().width + 10 + 30;
    int heightPlayerTurn = 165;

    playerTurnDisplay[0]->setPosition(width - offset, heightPlayerTurn);
    playerTurnDisplay[1]->setPosition(playerTurnDisplay[0]->getPosition().x + playerTurnDisplay[0]->getGlobalBounds().width + 10, heightPlayerTurn);
}


}