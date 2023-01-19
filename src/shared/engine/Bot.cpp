#include "Bot.h"
#include <iostream>
#include "Engine.h"

namespace engine {

Bot::Bot(){}

void Bot::generateCommand(state::State* state, engine::Engine* engine){
    char s[64];
    int count;
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

    if (rand()%5 == 0){
        sprintf(s, "drawcard-%d", state->turn);
        engine->addSerializedCommand(s);
    }

    if (rand()%2 == 0){
        int siz = state->players[state->turn].developments.size();
        if (siz != 0){
            sprintf(s, "usecard-%d-%d", state->turn, rand() % siz);
            engine->addSerializedCommand(s);
        }
    }

    count = 10;

    while (--count){
        sprintf(s, "exchangebank-%d-%d-%d", state->turn, rand()%5, rand()%5);
        engine->addSerializedCommand(s);
    }
    
    count = 1000;

    while (--count){
        sprintf(s, "placebuilding-%d-%d-%d-%d-%d-%d-%d-%d", state->turn, rand()%5+1, rand()%5+1, rand()%5+1, rand()%5+1, rand()%5+1, rand()%5+1, rand()%2);
        engine->addSerializedCommand(s);
    }

    count = 100;

    while (--count){
        sprintf(s, "placeroad-%d-%d-%d-%d-%d", state->turn, rand()%5+1, rand()%5+1, rand()%5+1, rand()%5+1);
        engine->addSerializedCommand(s);
    }

    sprintf(s, "passturn-%d", state->turn);
    engine->addSerializedCommand(s);
}

}