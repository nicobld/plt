#include "ExchangeBankCommand.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

static bool equalArrayPosition(std::array<state::Position, 2> pos1, std::array<state::Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}
static bool builidngsOnPort(std::array<state::Position, 3> pos1, std::array<state::Position, 2> pos2){
    return (equalArrayPosition({pos1[0], pos1[1]}, pos2) || equalArrayPosition({pos1[0], pos1[2]}, pos2) || equalArrayPosition({pos1[1], pos1[2]}, pos2));
}

namespace engine {

ExchangeBankCommand::ExchangeBankCommand() {
    commandID = EXCHANGE_BANK_CMD;
    min = 4;
}

ExchangeBankCommand::ExchangeBankCommand(state::PlayerColor playerColor , state::ResourceType  giving, state::ResourceType  receiving) {
    commandID = EXCHANGE_BANK_CMD;
    min = 4;
    this->giving = giving;
    this->receiving = receiving;
    this->playerColor = playerColor;
    std::cout << "échange crée" << to_string(this->giving) << " -> " << to_string(this->receiving) << endl;
}


bool ExchangeBankCommand::execute(state::State* state) {

    state->players[playerColor].resources[giving].number -= min;
    state->players[playerColor].resources[receiving].number ++;
    state->gameCards.resources[receiving].number --;
    state->gameCards.resources[giving].number += min;

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
            std::cout << "port : c'est le joueur : " << to_string(b.playerColor) << endl;
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
            
        } 
    }
    std::cout << "ca coutera : " << min <<endl;

    std::cout << "ressource du joueur donné avant echange " << to_string(giving) << " : " << state->players[playerColor].resources[giving].number << endl;
    std::cout << "ressource du joueur reçu avant echange " << to_string(receiving) << " : " << state->players[playerColor].resources[receiving].number << endl;

    std::cout << "ressource de la banque donné avant echange " << to_string(giving) << " : " << state->gameCards.resources[giving].number  << endl;
    std::cout << "ressource de la banque reçu avant echange " << to_string(receiving) << " : " <<  state->gameCards.resources[receiving].number << endl;

    if(state->players[playerColor].resources[giving].number >= min && state->gameCards.resources[receiving].number >= 1){
        std::cout << "on peut faire l'échange" << endl;
        return true;
    }
    std::cout << "pas d'échange" << endl;
    return false;
}

bool ExchangeBankCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    std::cout << "UNSERIALIZE \n";

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 4){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            giving = (state::ResourceType) stoi(tokens[2]);
            receiving = (state::ResourceType) stoi(tokens[3]);
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