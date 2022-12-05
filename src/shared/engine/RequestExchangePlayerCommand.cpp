#include "RequestExchangePlayerCommand.h"
#include <iostream>
#include "string.h"

namespace engine {

//une commande, pour une dmeande a chaque joeuur


RequestExchangePlayerCommand::RequestExchangePlayerCommand(state::Resource givingResources, state::Resource receivingResources, state::PlayerColor playerColor, state::PlayerColor playerAsk){
    commandID = EXCHANGE_PLAYER; 
    this->givingResources = givingResources;
    this->receivingResources = receivingResources;
    this->playerAsk = playerAsk;
    this->playerColor = playerColor;

    std::cout << "demande d'échange crée" << this->givingResources.resourceType << " -> " << this->receivingResources.resourceType << std::endl;
}

bool RequestExchangePlayerCommand::execute(state::State* state) {
    if(verify(state)){
        //state->players[playerAsk]
        return true;
    }
    return false;
}

bool RequestExchangePlayerCommand::verify(state::State* state){
    std::cout << "ressource du joueur donné avant echange " << givingResources.resourceType << " : " << givingResources.number << std::endl;
    std::cout << "ressource du joueur reçu avant echange " << receivingResources.resourceType << " : " << receivingResources.number << std::endl;
    if(state->players[playerColor].resources[givingResources.resourceType].number >= givingResources.number){
        std::cout << "on peut proposer l'échange" << std::endl;
        return true;
    }
    std::cout << "pas d'échange" << std::endl;
    return false;
}

bool RequestExchangePlayerCommand::verifyAfterPropose(state::State* state){
    std::cout << "ressource du joueur " << state->players[playerAsk].name << " donné avant echange " << givingResources.resourceType << " : " << state->players[playerAsk].resources[givingResources.resourceType].number  << std::endl;
    std::cout << "ressource du joueur " << state->players[playerAsk].name << " reçu avant echange " << receivingResources.resourceType << " : " <<  state->players[playerAsk].resources[receivingResources.resourceType].number<< std::endl;
    if(state->players[playerAsk].resources[receivingResources.resourceType].number >= receivingResources.number){
        std::cout << "on peut faire l'échange" << std::endl;
        return true;
    }

    std::cout << "pas d'échange" << std::endl;
    return false;
}


}