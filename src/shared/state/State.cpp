#include "State.h"

namespace state {

static char* iToColor(int i){
    switch(i){
        case 0 :
            return "Red";
            break;
        case 1 :
            return "Blue";
            break;
        case 2 :
            return "Yellow";
            break;
        case 3 :
            return "Green";
            break;
    }
}

State::State() {

    turn = PlayerRed;
    gameState = THROW_DICE_STATE;
}

State::State (std::vector<std::string> namePlayers){
    for(int i = 0; i < 4; i++){
        if(i < namePlayers.size()){
            players.push_back(Player(namePlayers[i], (PlayerColor) i));
        }
        else{
            players.push_back(Player(iToColor(i), (PlayerColor) i));
            players.back().isBot = true;
        }
    }
    turn = PlayerRed;
    gameState = NORMAL_STATE;
    
}

}