#include "ExchangePlayerCommand.h"

namespace engine {

ExchangePlayerCommand::ExchangePlayerCommand(){
    commandID = EXCHANGE_PLAYER;
    this-givingNumner = givingNumber;
    this-receivingNumner = receivingNumber;
    this->givingAsk = givingAsk;
    this->receivingAsk = receivingAsk;
    this playersAsk = playersAsk;
    cout << "demande d'échange crée" << to_string(this->givingAsk) << " -> " << to_string(this->receivingAsk) << endl;
}

bool ExchangePlayerCommand::execute(state::State* state) {

    return false;
}

bool ExchangePlayerCommand::verifiy(state::State* state){
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

bool ExchangePlayerCommand::exchangeRequest(state::State* state){

    return false;   
}

}