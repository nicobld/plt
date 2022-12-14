#include "ExchangeRequestCommand.h"
#include <iostream>
#include "string.h"

namespace engine {

//une commande, pour une dmeande a chaque joeuur
ExchangeRequestCommand::ExchangeRequestCommand() {}

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

}