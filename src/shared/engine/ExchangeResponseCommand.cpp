#include "ExchangeResponseCommand.h"
#include <iostream>
#include "string.h"

namespace engine {

ExchangeResponseCommand::ExchangeResponseCommand(state::Resource givingResources, state::Resource receivingResources, state::PlayerColor playerReceiving, state::PlayerColor playerColor, bool response){
    commandID = EXCHANGE_RESPONSE_CMD;
    
    this->givingResources = givingResources;
    this->receivingResources = receivingResources;
    this->playerReceiving = playerReceiving;
    this->playerColor = playerColor;
    this->response = response;

}


bool ExchangeResponseCommand::execute(state::State* state){


    return false;
}


bool ExchangeResponseCommand::verify(state::State* state){
    std::cout << "ressource du joueur " << state->players[playerColor].name << " donné avant echange " << givingResources.resourceType << " : " << state->players[playerColor].resources[givingResources.resourceType].number  << std::endl;
    std::cout << "ressource du joueur " << state->players[playerColor].name << " reçu avant echange " << receivingResources.resourceType << " : " <<  state->players[playerColor].resources[receivingResources.resourceType].number<< std::endl;
    if(state->players[playerColor].resources[receivingResources.resourceType].number >= receivingResources.number){
        std::cout << "on peut faire l'échange" << std::endl;
        return true;
    }

    std::cout << "pas d'échange" << std::endl;
    return false;
}

}
