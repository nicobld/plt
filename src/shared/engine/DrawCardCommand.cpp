#include "DrawCardCommand.h"
#include <iostream>
#include <stdlib.h>

namespace engine {

DrawCardCommand::DrawCardCommand(state::PlayerColor& pC){
    this->colorPlayer = pC;
}

bool DrawCardCommand::execute(state::State* state) {
    //state::Player& playerTemp = state::Player("temp", state::PlayerColor::PlayerRed);
    //state::gameCards& gamec;

    state::Player player = state->players[rand() % 4];
    state::GameCards deck = state->gameCards;
    int decksize = sizeof(deck.developments);

    int randomNb = rand() % decksize; //shuffling then drawing the top card could be an option

    state::Development development = deck.developments[randomNb];

    state::PlayerColor turnCount = state->turn;
    player.developments.push_back(development);
    std::cout << "car added to player " << std::endl;
     //rajouter exception pour tester le cas où ça fonctionne pas
    return true;
}

/*

void DrawCardCommand::drawCard(state::Player& drawingPlayer, state::GameCards& gameCards){

    int deckSize = sizeof(gameCards.developments);
    int randomNb = rand() % deckSize; //shuffling then drawing the top card could be an option
    state::Development development = gameCards.developments[randomNb];

    drawingPlayer.developments.push_back(development);
    std::cout << "car added to player " << std::endl;

}*/

}