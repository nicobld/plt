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
            if (buildingType == Colony && b.buildingType == City && b.playerColor == playerColor) {
                //Upgrade city to colony
                //state->map.
            } else {
                return false;
            }
        }
    }

    

}

}