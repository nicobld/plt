#include "PlaceBuildingCommand.h"
#include <array>
#include <iostream>

using namespace state;

const Position neighbors[2][6] = {
    {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
    {Position(+1,  0), Position(1, -1), Position(0, -1), Position(-1,  0), Position(0, +1), Position(1, +1)}
};

void afficheRoadPos(std::string s, std::array<Position, 2> curPos){
    std::cout << s << std::endl;
    std::cout << "Position 0 : " << curPos[0].x << ", " << curPos[0].y << std::endl;
    std::cout << "Position 1 : " << curPos[1].x << ", " << curPos[1].y << std::endl << std::endl;
}

bool equalRoadPos(std::array<Position, 2> pos1, std::array<Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}

bool equalBuildingPos(std::array<Position, 3> pos1, std::array<Position, 3> pos2){
    for (int i = 0; i < 3; i++){
        if(!(pos1[i] == pos2[0] || pos1[i] == pos2[1] || pos1[i] == pos2[2])){
            return false;
        }
    }
    return true;
}

bool hasRoad(state::State* state, std::array<Position, 2> pos, state::PlayerColor playerColor){
    for (state::Road r : state->map.roads){
        if (r.playerColor == playerColor){
            if (equalRoadPos(pos, r.position))
                return true;
        }
    }
    return false;
}

bool hasBuilding(state::State* state, std::array<Position, 3> building){
    for (state::Building b : state->map.buildings){
        if (equalBuildingPos(building, b.position)){
            return true;
        }
    }
    return false;
}

std::array<Position, 2> findTilesRoadNeighbors(state::State* state, std::array<Position, 2> road){
    std::array<Position, 2> res;
    int t = 0;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            if (road[0] + neighbors[road[0].y%2][j] == road[1] + neighbors[road[1].y%2][i]){ //si on trouve un voisin commun
                if (!(road[0] + neighbors[road[0].y%2][j] == road[1]) && !(road[0] == road[1] + neighbors[road[1].y%2][i])){ //qui n'est pas l'autre tile de la route
                    res[t++] = road[0] + neighbors[road[0].y%2][j];
                    if (t == 2) return res;
                }
            }
        }
    }
    return res;
}

namespace engine {

PlaceBuildingCommand::PlaceBuildingCommand(state::PlayerColor playerColor, std::array<state::Position, 3> position, state::BuildingType buildingType):
    playerColor(playerColor), position(position), buildingType(buildingType) {}

bool PlaceBuildingCommand::execute(state::State* state) {
    std::array<Position, 2> tempRoadPos;
    std::array<Position, 2> tempRoadNeighbors;
    Position tempTile;

    bool foundBuilding = false;
    //verifie si le joueur a le building
    for (state::Building b : state->players[playerColor].buildings){
        if (b.buildingType == buildingType){
            foundBuilding = true;
            break;
        }
    }
    if (!foundBuilding) return false;

    //VERIFY
    for (state::Building b : state->map.buildings){
        if (b.position == position) {
            //pour upgrade colony en city
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

    //check building is on a road
    if (!hasRoad(state, {position[0], position[1]}, playerColor) && !hasRoad(state, {position[0], position[2]}, playerColor) && !hasRoad(state, {position[1], position[2]}, playerColor)){
        std::cout << "no road to place building\n";      
        return false;
    }

    //check no building around
    for (int i = 0; i < 3; i++){
        if (i == 0)
            tempRoadPos = {position[1], position[2]};
        else if (i == 1)
            tempRoadPos = {position[0], position[2]};
        else
            tempRoadPos = {position[0], position[1]};

        tempRoadNeighbors = findTilesRoadNeighbors(state, tempRoadPos);

        if (tempRoadNeighbors[0] == position[i])
            tempTile = tempRoadNeighbors[1];
        else
            tempTile = tempRoadNeighbors[0];
        
        if (hasBuilding(state, {tempTile, tempRoadPos[0], tempRoadPos[1]})){
            
            return false;
        }
    }

    state->players[playerColor].buildings.erase(state->players[playerColor].buildings.begin() + state->players[playerColor].getBuilding(buildingType));
    state->map.buildings.push_back(Building(playerColor, buildingType, position));
    return true;

}

}