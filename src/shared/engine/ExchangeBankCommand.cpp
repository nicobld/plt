#include "ExchangeBankCommand.h"
#include <iostream>

using namespace std;

namespace engine {

ExchangeBankCommand::ExchangeBankCommand(state::State* , state::ResourceType  giving, state::ResourceType  receiving) {
    commandID = EXCHANGE_BANK;
    min = 4;
    this->giving = giving;
    this->receiving = receiving;
    cout << "échange crée" << to_string(this->giving) << " -> " << to_string(this->receiving) << endl;
}

bool equalArrayPosition(std::array<state::Position, 2> pos1, std::array<state::Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}
bool builidngsOnPort(std::array<state::Position, 3> pos1, std::array<state::Position, 2> pos2){
    return (equalArrayPosition({pos1[0], pos1[1]}, pos2) || equalArrayPosition({pos1[0], pos1[2]}, pos2) || equalArrayPosition({pos1[1], pos1[2]}, pos2));
}


bool ExchangeBankCommand::execute(state::State* state) {
    if(verify(state)){
        for(state::Player playerReceiving : state->players){
            if (playerReceiving.playerColor == state->turn){
                playerReceiving.resources[giving].number -= min;
                playerReceiving.resources[receiving].number += 2;
                state->gameCards.resources[receiving].number -= 2;
                state->gameCards.resources[giving].number +=min;

                cout << "transaction effectué" << endl;
                cout << "ressource du joueur donné après echange " << to_string(giving) << " : " << playerReceiving.resources[giving].number << endl;
                cout << "ressource du joueur reçu après echange" << to_string(receiving) << " : " << playerReceiving.resources[receiving].number << endl;

                cout << "ressource de la banque donné après echange " << to_string(giving) << " : " << state->gameCards.resources[giving].number  << endl;
                cout << "ressource de la banque reçu après echange" << to_string(receiving) << " : " <<  state->gameCards.resources[receiving].number << endl;

                return true;
            }
        }
    }
    return false;
}

bool ExchangeBankCommand::verify(state::State* state){
   //valeur mininimale de giving pour faire l'échange.
    
    for(state::Building b : state->map.buildings){
        if (b.playerColor == state->turn){
            cout << "c'est le joueur : " << to_string(b.playerColor) << endl;
            for(state::Port p : state->map.ports){
                if(builidngsOnPort(b.position, p.position)){
                    cout << "il a un batiment sur un port: " << endl;
                    if (p.resourceType == state::Nothing){
                        min = 3;
                    }
                    else if(p.resourceType == giving){
                        min = 2;
                    }
                }
            }
            cout << "ca coutera : " << min <<endl;
        } 
    }
    for(state::Player playerReceiving : state->players){
        if (playerReceiving.playerColor == state->turn){
                cout << "ressource du joueur donné avant echange " << to_string(giving) << " : " << playerReceiving.resources[giving].number << endl;
                cout << "ressource du joueur reçu avant echange " << to_string(receiving) << " : " << playerReceiving.resources[receiving].number << endl;

                cout << "ressource de la banque donné avant echange " << to_string(giving) << " : " << state->gameCards.resources[giving].number  << endl;
                cout << "ressource de la banque reçu avant echange " << to_string(receiving) << " : " <<  state->gameCards.resources[receiving].number << endl;
            if(playerReceiving.resources[giving].number >= min && state->gameCards.resources[receiving].number >= 2){
                cout << "on peut faire l'échange" << endl;
                return true;
            }
        }
    }
    cout << "pas d'échange" << endl;
    return false;
}

}