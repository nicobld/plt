#include "Bot.h"
#include <iostream>
#include "Engine.h"

namespace engine {

Bot::Bot(){}

char* Bot::generateCommand(state::State* state, engine::Engine* engine){
    char s[64];
    std::cout << "Commande aléatoire" << std::endl;
    sprintf(s, "throwdice-%d", state->turn);
    engine->addSerializedCommand(s);
    engine->update();

    while (state->gameState == state::PLACE_THIEF_STATE){
        sprintf(s, "placethief-%d-%d-%d", state->turn, rand()%7, rand()%7);
        engine->addSerializedCommand(s);
        engine->update();
    }

    while (state->gameState == state::STEAL_CARD_STATE){
        sprintf(s, "stealcard-%d-%d", state->turn, rand()%4);
        engine->addSerializedCommand(s);
        engine->update();
    }

    while (state->gameState == state::ROAD_CONSTRUCTION_STATE){
        sprintf(s, "placeroad-%d-%d-%d-%d-%d", state->turn, rand()%7, rand()%7, rand()%7, rand()%7);
        engine->addSerializedCommand(s);
        engine->update();
    }

    while (state->gameState == state::MONOPOLY_STATE){
        sprintf(s, "monopoly-%d-%d", state->turn, (state::ResourceType) (rand()%5));
        engine->addSerializedCommand(s);
        engine->update();
    }

    while (state->gameState == state::INVENTION_STATE){
        sprintf(s, "invention-%d-%d-%d", state->turn, (state::ResourceType) (rand()%5), (state::ResourceType) (rand()%5));
        engine->addSerializedCommand(s);
        engine->update();
    }

    if (rand()%20 == 0){
        sprintf(s, "drawcard-%d", state->turn);
        engine->addSerializedCommand(s);
    }

    if (rand()%20 == 0){
        int siz = state->players[state->turn].developments.size();
        if (siz != 0){
            sprintf(s, "usecard-%d-%d", state->turn, rand() % siz);
            engine->addSerializedCommand(s);
        }
    }

    int count = 100;

    while (--count){
        sprintf(s, "placeroad-%d-%d-%d-%d-%d", state->turn, rand()%7, rand()%7, rand()%7, rand()%7);
        engine->addSerializedCommand(s);
        sprintf(s, "placebuilding-%d-%d-%d-%d-%d-%d-%d-%d", state->turn, rand()%7, rand()%7, rand()%7, rand()%7, rand()%7, rand()%7, rand()%2);
        engine->addSerializedCommand(s);
    }

    sprintf(s, "passturn-%d", state->turn);
    engine->addSerializedCommand(s);
    return s;
}

char* Bot::throwDice(state::State* state){
    static char s[64];
    std::cout << "Bot lance les des" << std::endl;
    sprintf(s, "throwdice-%d", state->turn);
    return s;
}

char* passTurn (state::State* state){
    static char s[64];
    std::cout << "Bot pass turn" << std::endl;
    sprintf(s, "passturn-%d", state->turn);
    return s;
}

}