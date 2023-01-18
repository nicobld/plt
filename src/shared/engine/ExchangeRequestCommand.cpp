#include "ExchangeRequestCommand.h"
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

//une commande, pour une dmeande a chaque joeuur
ExchangeRequestCommand::ExchangeRequestCommand() {
    commandID = EXCHANGE_REQUEST_CMD;
}

ExchangeRequestCommand::ExchangeRequestCommand(state::Resource givingResources, state::Resource receivingResources, state::PlayerColor playerColor, std::vector<state::PlayerColor> playerAsks){
    commandID = EXCHANGE_REQUEST_CMD; 
    this->givingResources = givingResources;
    this->receivingResources = receivingResources;
    this->playerAsks = playerAsks;
    this->playerColor = playerColor;

    std::cout << "demande d'échange crée " << this->givingResources.resourceType << " -> " << this->receivingResources.resourceType << std::endl;
}

bool ExchangeRequestCommand::execute(state::State* state) {
    for(state::PlayerColor playerAsk : playerAsks){
        state->players[playerAsk].playerState = state::EXCHANGE;
    }
    return true;
}

bool ExchangeRequestCommand::verify(state::State* state){
    std::cout << "ressource de " << state->players[playerColor].name << " donné avant echange " << givingResources.resourceType << " : " << state->players[playerColor].resources[givingResources.resourceType].number << std::endl;
    std::cout << "ressource de " << state->players[playerColor].name << " reçu avant echange " << receivingResources.resourceType << " : " << state->players[playerColor].resources[receivingResources.resourceType].number << std::endl;
    if(state->players[playerColor].resources[givingResources.resourceType].number >= givingResources.number){
        std::cout << "on peut proposer l'échange" << std::endl;
        return true;
    }
    std::cout << "pas d'échange" << std::endl;
    return false;
}

bool ExchangeRequestCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 6){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            if ((givingResources.resourceType = stringToResType(tokens[2])) == state::Nothing){
                std::cout << "Wrong resource name aa" << stringToResType(tokens[2]) << std::endl;
                return false;
            }
            givingResources.number = stoi(tokens[3]);
            if ((receivingResources.resourceType = stringToResType(tokens[4])) == state::Nothing){
                std::cout << "Wrong resource name" << std::endl;
                return false;
            }
            receivingResources.number = stoi(tokens[5]);
            for (int i = 0; i < 4; i++)
                if ((state::PlayerColor)i != state::PlayerRed)
                    playerAsks.push_back((state::PlayerColor)i);

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