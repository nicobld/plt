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

    resources.push_back(Resource(Lumber));
    resources.push_back(Resource(Brick));
    resources.push_back(Resource(Grain));
    resources.push_back(Resource(Wool));
    resources.push_back(Resource(Ore));
}

int Player::getBuilding(BuildingType buildingType){
    for (int i = 0; i < buildings.size(); i++){
        if (buildings[i].buildingType == buildingType){
            return i;
        }
    }
    return -1;
}

}
