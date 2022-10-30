#include "GameCards.h"

namespace state{

GameCards::GameCards() {
    int i;

    for (i = 0; i < 120; i++){ //20 de chaque resource
        resources.push_back(Resource(static_cast<ResourceType>(i/20)));
    }

    for (i = 0; i < 10; i++){ //5 de chaque knight et victorypoint
        developments.push_back(Development(true, static_cast<DevelopmentType>(i/5)));
    }

    for (i = 10; i < 25; i++){ //5 de chaque progress card
        developments.push_back(Development(false, static_cast<DevelopmentType>(i/5)));
    }

}

}
