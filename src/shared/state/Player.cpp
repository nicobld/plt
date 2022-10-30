#include "Player.h"

namespace state{

Player::Player(std::string name, PlayerColor playerColor) : name(name), playerColor(playerColor) {
    int i;
    
    victoryPoints = 0;
    knightNumber = 0;
    hasLargestArmy = false;
    hasLongestRoad = false;

    for (i = 0; i < 5; i++){
        buildings.push_back(Building(playerColor, Colony));
    }

    for (i = 0; i < 4; i++){
        buildings.push_back(Building(playerColor, City));
    }

    for (i = 0; i < 15; i++){
        roads.push_back(Road(playerColor));
    }
}

}
