#include "ExchangeBankCommand.h"
#include <iostream>

using namespace std;

namespace engine {

ExchangeBankCommand::ExchangeBankCommand(state::PlayerColor playerColor , state::ResourceType  giving, state::ResourceType  receiving) {
    commandID = EXCHANGE_BANK_CMD;
    min = 4;
    this->giving = giving;
    this->receiving = receiving;
    this->playerColor = playerColor;
    std::cout << "échange crée" << to_string(this->giving) << " -> " << to_string(this->receiving) << endl;
}

bool equalArrayPosition(std::array<state::Position, 2> pos1, std::array<state::Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}
bool builidngsOnPort(std::array<state::Position, 3> pos1, std::array<state::Position, 2> pos2){
    return (equalArrayPosition({pos1[0], pos1[1]}, pos2) || equalArrayPosition({pos1[0], pos1[2]}, pos2) || equalArrayPosition({pos1[1], pos1[2]}, pos2));
}


bool ExchangeBankCommand::execute(state::State* state) {

    state->players[playerColor].resources[giving].number -= min;
    state->players[playerColor].resources[receiving].number += 2;
    state->gameCards.resources[receiving].number -= 2;
    state->gameCards.resources[giving].number +=min;

    std::cout << "transaction effectué" << endl;
    std::cout << "ressource du joueur donné après echange " << to_string(giving) << " : " << state->players[playerColor].resources[giving].number << endl;
    std::cout << "ressource du joueur reçu après echange" << to_string(receiving) << " : " << state->players[playerColor].resources[receiving].number << endl;

    std::cout << "ressource de la banque donné après echange " << to_string(giving) << " : " << state->gameCards.resources[giving].number  << endl;
    std::cout << "ressource de la banque reçu après echange" << to_string(receiving) << " : " <<  state->gameCards.resources[receiving].number << endl;

    return true;
}

bool ExchangeBankCommand::verify(state::State* state){
   //valeur mininimale de giving pour faire l'échange.
    
    for(state::Building b : state->map.buildings){
        if (b.playerColor == playerColor){
            std::cout << "c'est le joueur : " << to_string(b.playerColor) << endl;
            for(state::Port p : state->map.ports){
                if(builidngsOnPort(b.position, p.position)){
                    std::cout << "il a un batiment sur un port: " << endl;
                    if (p.resourceType == state::Nothing){
                        min = 3;
                    }
                    else if(p.resourceType == giving){
                        min = 2;
                    }
                }
            }
            std::cout << "ca coutera : " << min <<endl;
        } 
    }
    std::cout << "ressource du joueur donné avant echange " << to_string(giving) << " : " << state->players[playerColor].resources[giving].number << endl;
    std::cout << "ressource du joueur reçu avant echange " << to_string(receiving) << " : " << state->players[playerColor].resources[receiving].number << endl;

    std::cout << "ressource de la banque donné avant echange " << to_string(giving) << " : " << state->gameCards.resources[giving].number  << endl;
    std::cout << "ressource de la banque reçu avant echange " << to_string(receiving) << " : " <<  state->gameCards.resources[receiving].number << endl;

    if(state->players[playerColor].resources[giving].number >= min && state->gameCards.resources[receiving].number >= 2){
        std::cout << "on peut faire l'échange" << endl;
        return true;
    }
    std::cout << "pas d'échange" << endl;
    return false;
}

}