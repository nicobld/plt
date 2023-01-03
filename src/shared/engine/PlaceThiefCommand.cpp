#include "PlaceThiefCommand.h"
#include <iostream>
#include <bits/stdc++.h>

namespace engine {

PlaceThiefCommand::PlaceThiefCommand() {
    commandID = PLACE_THIEF_CMD;
}

PlaceThiefCommand::PlaceThiefCommand(state::PlayerColor playerColor, state::Position position) : position(position) {
    this->playerColor = playerColor;
    commandID = PLACE_THIEF_CMD;
}

bool PlaceThiefCommand::verify(state::State* state){
    if (state->map.thief.position == position) {
        std::cout << "PlaceThief error : Have to change position of thief" << std::endl;
        return false;
    }

    if (position.x + 7*position.y > 49){
        std::cout << "PlaceThief error : Error tile doesn't exit" << std::endl;
        return false;
    }

    if (state->map.grid[position.x + 7*position.y] == 0 || state->map.grid[position.x + 7*position.y] >= 6) {
        std::cout << "PlaceThief error : Error place thief on a ground tile" << std::endl;
        return false;
    }

    return true;
}

bool PlaceThiefCommand::execute(state::State* state){

    state->map.thief.position = position;

    return true;
}

bool PlaceThiefCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 4){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            position.x = stoi(tokens[2]);
            position.y = stoi(tokens[3]);
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