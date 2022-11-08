#include "GameCards.h"

namespace state{

GameCards::GameCards() {
    int i;

    for (i = 0; i < 120; i++){ //20 de chaque resource
        resources.push_back(Resource(static_cast<ResourceType>(i/20)));
    }

    for (i = 0; i < 25; i++){ //5 de chaque progress card
        developments.push_back(Development(static_cast<DevelopmentType>(i/5)));
    }

}

}
