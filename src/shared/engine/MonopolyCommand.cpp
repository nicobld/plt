#include "MonopolyCommand.h"
#include <iostream>
#include <bits/stdc++.h>

static state::ResourceType stringToResType(std::string string){
    if (string == "wool")
        return state::Wool;
    else if (string == "lumber")
        return state::Lumber;
    else if (string == "brick")
        return state::Brick;
    else if (string == "grain")
        return state::Grain;
    else if (string == "ore")
        return state::Ore;
    else
        return state::Nothing;
}


namespace engine {

MonopolyCommand::MonopolyCommand(){
    commandID = MONOPOLY_CMD;
}

bool MonopolyCommand::verify(state::State* state){
    return true;
}

bool MonopolyCommand::execute(state::State* state){
    int resNum = 0;
    for (size_t i = 0; i < state->players.size(); i++){
        if (state->players[i].playerColor != playerColor){
            resNum += state->players[i].resources[resourceType].number;
            state->players[i].resources[resourceType].number = 0;
        }
    }

    std::cout << "You stole " << resNum << " resources" << std::endl;
    state->players[playerColor].resources[resourceType].number += resNum;
    return true;
}

bool MonopolyCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 3){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            if ((resourceType = stringToResType(tokens[2])) == state::Nothing){
                std::cout << "Wrong resource type" << std::endl;
                return false;
            }
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