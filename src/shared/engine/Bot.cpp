#include "Bot.h"
#include <iostream>

namespace engine {

Bot::Bot(){}

char* Bot::generateCommand(state::State* state){
    char s[64];
    std::cout << "Commande aléatoire" << std::endl;
    //printf(s, "throwdice-%d", state->turn);
    return s;
}

char* Bot::throwDice(state::State* state){
    char s[64];
    std::cout << "Bot lance les dès" << std::endl;
    sprintf(s, "throwdice-%d", state->turn);
    return s;
}

}