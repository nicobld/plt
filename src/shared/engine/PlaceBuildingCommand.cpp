#include "PlaceBuildingCommand.h"
#include <array>

namespace engine {

PlaceBuildingCommand::PlaceBuildingCommand(state::PlayerColor playerColor, std::array<state::Position, 3> position) : playerColor(playerColor), position(position) {
    commandID = PLACE_BUILDING;
}

bool PlaceBuildingCommand::execute(state::State* state) {
    //VERIFY
    for (state::Building b : state->map.buildings){
        if (b.position == position) {
            return false;
        }
    }

    

}

}