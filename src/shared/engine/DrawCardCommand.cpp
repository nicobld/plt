#include "DrawCardCommand.h"
#include <iostream>
#include <bits/stdc++.h>

namespace engine {

DrawCardCommand::DrawCardCommand() {
    commandID = DRAW_CARD_CMD;
}

DrawCardCommand::DrawCardCommand(state::PlayerColor playerColor): playerColor(playerColor){
    commandID = DRAW_CARD_CMD;
}

bool DrawCardCommand::verify(state::State* state){
    state::Player* player = &(state->players[this->playerColor]);

    if (state->gameCards.developments.size() == 0){
        std::cout << "No more cards to draw :(" << std::endl;
        return false;
    }

    if (player->resources[state::Grain].number >= 1 && player->resources[state::Ore].number >= 1 && player->resources[state::Wool].number >= 1)
        return true;
    else
        return false;
}

bool DrawCardCommand::execute(state::State* state) {

    state::Player* player = &(state->players[this->playerColor]);

    player->resources[state::Grain].number--;
    player->resources[state::Ore].number--;
    player->resources[state::Wool].number--;

    state->gameCards.resources[state::Grain].number++;
    state->gameCards.resources[state::Ore].number++;
    state->gameCards.resources[state::Wool].number++;

    int randCard = rand() % state->gameCards.developments.size();
    state::Development development = state->gameCards.developments[randCard];
    state->gameCards.developments.erase(state->gameCards.developments.begin() + randCard);

    state->players[this->playerColor].developments.push_back(development);
    
    return true;
        
    }

bool DrawCardCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 2){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
        } else {
            std::cout << "Invalid number of arguments\n";
            return false;
        }
    }
    catch (const std::invalid_argument& ia) {
	    std::cerr << "Invalid argument: " << ia.what() << '\n';
        return false;
    }

    return true;
}

}
