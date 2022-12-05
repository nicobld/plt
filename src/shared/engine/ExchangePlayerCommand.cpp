#include "ExchangePlayerCommand.h"

namespace engine {

ExchangePlayerCommand::ExchangePlayerCommand(){
    // commandID = EXCHANGE_PLAYER;
    // this->givingNumner = givingNumber;
    // this->receivingNumner = receivingNumber;
    // this->givingAsk = givingAsk;
    // this->receivingAsk = receivingAsk;
    // this playersAsk = playersAsk;

    // for(state::Player playerReceiving : state->players){
    //     if (playerReceiving.playerColor == state->turn){
    //         this->playeReceiving = playerReceviving;
    //     }
    // }
    // cout << "demande d'échange crée" << to_string(this->givingAsk) << " -> " << to_string(this->receivingAsk) << endl;
}

// bool ExchangePlayerCommand::execute(state::State* state) {
//     for(state::Player playerAsk : playersAsk){
//         verifiyAfterPoprose(state, playerAsk);


//     }
//     return false;
// }

// bool ExchangePlayerCommand::verifiyBeforePropose(state::State* state){
//     cout << "ressource du joueur donné avant echange " << to_string(giving) << " : " << playerReceiving.resources[giving].number << endl;
//     cout << "ressource du joueur reçu avant echange " << to_string(receiving) << " : " << playerReceiving.resources[receiving].number << endl;
//     if(playerReceiving.resources[giving].number >= givingNumner){
//         cout << "on peut proposer l'échange" << endl;
//         return true;
//     }
//     cout << "pas d'échange" << endl;
//     return false;
// }

// bool ExchangePlayerCommand::verifiyAfterPoprose(state::State* state, state::Player playerAsk){
//     cout << "ressource du joueur " << playerAsk.name << " donné avant echange " << to_string(giving) << " : " << playerAsk.resources[giving].number  << endl;
//     cout << "ressource du joueur " << playerAsk.name << " reçu avant echange " << to_string(receiving) << " : " <<  playerAsk.resources[receiving].number << endl;
//     if(playerAsk.resources[giving].number >= receivingNumber){
//         cout << "on peut faire l'échange" << endl;
//         return true;
//     }
//     cout << "pas d'échange" << endl;
//     return false;
// }

// bool ExchangePlayerCommand::exchangeRequest(state::State* state){
//     verifiyBeforePropose(state);
//     for(state::Player playerAsk : playersAsk){
        


//     }
//     return false;   
// }

bool ExchangePlayerCommand::execute(state::State* state){
    return true;
}

bool ExchangePlayerCommand::verify(state::State* state){
    return true;
}

}