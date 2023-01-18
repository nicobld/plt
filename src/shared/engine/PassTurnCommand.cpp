#include "PassTurnCommand.h"
#include <bits/stdc++.h>
#include <iostream>
#include <bits/stdc++.h>

namespace engine {

PassTurnCommand::PassTurnCommand() {
    commandID = PASS_TURN_CMD;
}

PassTurnCommand::PassTurnCommand(state::PlayerColor playerColor) {
    commandID = PASS_TURN_CMD;

    this->playerColor = playerColor;
}

bool PassTurnCommand::verify(state::State* state){
    if (state->turn == playerColor) 
        return true;
    else
        return false;
}

bool PassTurnCommand::execute(state::State* state) {
    state->turn = (state::PlayerColor) (((int)state->turn + 1) % 4);
    state->gameState = state::THROW_DICE_STATE;
    return true;
}

bool PassTurnCommand::unserialize(std::string string){
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