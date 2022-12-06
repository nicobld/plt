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
    if(response){
        state->players[playerReceiving].resources[givingResources.resourceType].number -= givingResources.number;
        state->players[playerReceiving].resources[receivingResources.resourceType].number += receivingResources.number;
        state->players[playerColor].resources[receivingResources.resourceType].number -= receivingResources.number;
        state->players[playerColor].resources[givingResources.resourceType].number += givingResources.number;

        std::cout << "ressource de "  << state->players[playerReceiving].name << " donné après échange"   <<  givingResources.resourceType << " : " <<  state->players[playerReceiving].resources[givingResources.resourceType].number  << std::endl;
        std::cout << "ressource de "  << state->players[playerReceiving].name << " reçu après échange"   <<  receivingResources.resourceType << " : " <<  state->players[playerReceiving].resources[receivingResources.resourceType].number  << std::endl;

        std::cout << "ressource de "  << state->players[playerColor].name << " donné après échange"   <<  givingResources.resourceType << " : " <<  state->players[playerColor].resources[givingResources.resourceType].number  << std::endl;
        std::cout << "ressource de "  << state->players[playerColor].name << " reçu après échange"   <<  receivingResources.resourceType << " : " <<  state->players[playerColor].resources[receivingResources.resourceType].number  << std::endl;

        return true;
    }
    std::cout << state->players[playerColor].name << " ne veut pas faire l'échange" << std::endl;
    return false;
}


bool ExchangeResponseCommand::verify(state::State* state){
    std::cout << "ressource de " << state->players[playerColor].name << " donné avant echange " << givingResources.resourceType << " : " << state->players[playerColor].resources[givingResources.resourceType].number  << std::endl;
    std::cout << "ressource de " << state->players[playerColor].name << " reçu avant echange " << receivingResources.resourceType << " : " <<  state->players[playerColor].resources[receivingResources.resourceType].number<< std::endl;
    if(state->players[playerColor].resources[receivingResources.resourceType].number >= receivingResources.number){
        std::cout << "on peut faire l'échange" << std::endl;
        return true;
    }

    std::cout << "pas d'échange" << std::endl;
    return false;
}

}
