#include "PlaceRoadCommand.h"
#include <iostream>

using namespace state;

namespace engine {

bool isNeighbor(Position pos1, Position pos2){
    static Position neighbors[2][6] = {
        {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
        {Position(+1,  0), Position(1, -1), Position(0, 1), Position(-1,  0), Position(0, +1), Position(1, +1)}
    };
    Position pos = pos2 - pos1;
    if (pos == Position(0, 0))
        return true;
    for (int i = 0; i < 6; i++){
        if (pos == neighbors[pos1.x % 2][i])
            return true;
    }
    return false;
}

PlaceRoadCommand::PlaceRoadCommand(state::PlayerColor playerColor, std::array<Position, 2> position):
    playerColor(playerColor), position(position) {}

bool PlaceRoadCommand::execute(state::State* state) {
    //verifie player a des routes
    if (state->players[playerColor].roads.size() == 0) {
        std::cout << "Player has no roads to place" << std::endl;
        return false;
    }

    //verifie pas déjà une route sur la map
    for (state::Road r : state->map.roads){
        if (r.position == position){
            return false;
        }
    }

    bool foundRoad = false;
    for (Road r : state->map.roads){
        if (r.playerColor == playerColor){
            if (isNeighbor(position[0], r.position[0]) && isNeighbor(position[0], r.position[1]) && isNeighbor(position[1], r.position[0]) && isNeighbor(position[1], r.position[1])){
                foundRoad = true;
            }
        }
    }

    if (!foundRoad) return false;

    //place la route et retire la route au joueur
    state->map.roads.push_back(Road(playerColor, position));
    state->players[playerColor].roads.pop_back();
    return true;
}

}