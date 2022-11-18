#include "PlaceBuildingCommand.h"
#include <array>

using namespace state;

namespace engine {

PlaceBuildingCommand::PlaceBuildingCommand(state::PlayerColor playerColor, std::array<state::Position, 3> position, state::BuildingType buildingType) : 
    playerColor(playerColor), position(position), buildingType(buildingType) {
    commandID = PLACE_BUILDING;
}

bool PlaceBuildingCommand::execute(state::State* state) {
    //VERIFY
    
    for (state::Building b : state->map.buildings){
        if (b.position == position) {
            if (buildingType == City && b.buildingType == Colony && b.playerColor == playerColor) {
                //Upgrade city to colony
                state->map.buildings.erase(state->map.buildings.begin() + state->map.getBuilding(position)); //remove colony from map
                state->map.buildings.push_back(Building(playerColor, buildingType, b.position)); //add city to map
                state->players[playerColor].buildings.erase(state->players[playerColor].buildings.begin() + state->players[playerColor].getBuilding(buildingType)); //remove player building
                return true;
            } else {
                return false;
            }
        }
    }

    state->players[playerColor].buildings.erase(state->players[playerColor].buildings.begin() + state->players[playerColor].getBuilding(buildingType));
    state->map.buildings.push_back(Building(playerColor, buildingType, position));
    return true;

}

}