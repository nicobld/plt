#include "InventionCommand.h"
#include <iostream>
#include <bits/stdc++.h>

namespace engine {


InventionCommand::InventionCommand() {
    commandID = INVENTION_CMD;
    this->playerColor = playerColor;
}

bool InventionCommand::verify(state::State* state){
    if (! (state->gameCards.resources[resourceType1].number > 0 && state->gameCards.resources[resourceType2].number > 0) ){
        return true;
    }
    return false;
}

bool InventionCommand::execute(state::State* state){
    state->gameCards.resources[resourceType1].number--;
    state->gameCards.resources[resourceType2].number--;

    state->players[playerColor].resources[resourceType1].number++;
    state->players[playerColor].resources[resourceType2].number++;
    return true;
}

bool InventionCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 4){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            resourceType1 = (state::ResourceType) stoi(tokens[2]);
            resourceType2 = (state::ResourceType) stoi(tokens[3]);
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