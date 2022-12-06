#include "ExchangeRequestCommand.h"
#include <iostream>
#include "string.h"

namespace engine {

//une commande, pour une dmeande a chaque joeuur


ExchangeRequestCommand::ExchangeRequestCommand(state::Resource givingResources, state::Resource receivingResources, state::PlayerColor playerColor, std::vector<state::PlayerColor> playerAsks){
    commandID = EXCHANGE_REQUEST_CMD; 
    this->givingResources = givingResources;
    this->receivingResources = receivingResources;
    this->playerAsks = playerAsks;
    this->playerColor = playerColor;

    std::cout << "demande d'échange crée" << this->givingResources.resourceType << " -> " << this->receivingResources.resourceType << std::endl;
}

bool ExchangeRequestCommand::execute(state::State* state) {
    if(verify(state)){
        //state->players[playerAsk]
        return true;
    }
    return false;
}

bool ExchangeRequestCommand::verify(state::State* state){
    std::cout << "ressource du joueur donné avant echange " << givingResources.resourceType << " : " << givingResources.number << std::endl;
    std::cout << "ressource du joueur reçu avant echange " << receivingResources.resourceType << " : " << receivingResources.number << std::endl;
    if(state->players[playerColor].resources[givingResources.resourceType].number >= givingResources.number){
        std::cout << "on peut proposer l'échange" << std::endl;
        return true;
    }
    std::cout << "pas d'échange" << std::endl;
    return false;
}

}