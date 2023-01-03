#include "PlaceBuildingCommand.h"
#include <array>
#include <iostream>
#include <bits/stdc++.h>

using namespace state;

const Position neighbors[2][6] = {
    {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
    {Position(+1,  0), Position(1, -1), Position(0, -1), Position(-1,  0), Position(0, +1), Position(1, +1)}
};

static void afficheRoadPos(std::string s, std::array<Position, 2> curPos){
    std::cout << s << std::endl;
    std::cout << "Position 0 : " << curPos[0].x << ", " << curPos[0].y << std::endl;
    std::cout << "Position 1 : " << curPos[1].x << ", " << curPos[1].y << std::endl << std::endl;
}

static bool equalRoadPos(std::array<Position, 2> pos1, std::array<Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}

static bool equalBuildingPos(std::array<Position, 3> pos1, std::array<Position, 3> pos2){
    for (int i = 0; i < 3; i++){
        if(!(pos1[i] == pos2[0] || pos1[i] == pos2[1] || pos1[i] == pos2[2])){
            return false;
        }
    }
    return true;
}

static bool hasRoad(state::State* state, std::array<Position, 2> pos, state::PlayerColor playerColor){
    for (state::Road r : state->map.roads){
        if (r.playerColor == playerColor){
            if (equalRoadPos(pos, r.position))
                return true;
        }
    }
    return false;
}

static bool hasBuilding(state::State* state, std::array<Position, 3> building){
    for (state::Building b : state->map.buildings){
        if (equalBuildingPos(building, b.position)){
            return true;
        }
    }
    return false;
}

static std::array<Position, 2> findTilesRoadNeighbors(state::State* state, std::array<Position, 2> road){
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

PlaceBuildingCommand::PlaceBuildingCommand() {
    commandID = PLACE_BUILDING_CMD;
}

PlaceBuildingCommand::PlaceBuildingCommand(state::PlayerColor playerColor, std::array<state::Position, 3> position, state::BuildingType buildingType):
position(position), buildingType(buildingType) {
    
    this->playerColor = playerColor;
    commandID = PLACE_BUILDING_CMD;
}

bool PlaceBuildingCommand::verify(state::State* state){
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
    if (!foundBuilding){
        std::cout << "PlaceBuilding error : You don't have any buildings to place" << std::endl;
        return false;
    }

    if (buildingType == 0){
        if (!(state->players[playerColor].resources[state::Lumber].number >= 1 &&
            state->players[playerColor].resources[state::Brick].number >= 1 &&
            state->players[playerColor].resources[state::Grain].number >= 1 &&
            state->players[playerColor].resources[state::Wool].number >= 1)){

            std::cout << "PlaceBuilding error : Not enough resources" << std::endl;
            return false;
        }
    } else {
        if (!(state->players[playerColor].resources[state::Grain].number >= 2 &&
            state->players[playerColor].resources[state::Ore].number >= 3)){
            
            std::cout << "PlaceBuilding error : Not enough resources" << std::endl;
            return false;
        }
    }

    for (state::Building b : state->map.buildings){//pour upgrade colony en city
        if (b.position == position) {
            if (buildingType == City && b.buildingType == Colony && b.playerColor == playerColor) {
                break;
            } else {
                std::cout << "PlaceBuilding error : Cannot place building, already a building here" << std::endl;
                return false;
            }
        }
    }

    //check building is on a road
    if (!hasRoad(state, {position[0], position[1]}, playerColor) && !hasRoad(state, {position[0], position[2]}, playerColor) && !hasRoad(state, {position[1], position[2]}, playerColor)){
        std::cout << "PlaceBuilding error : No road to place building" << std::endl;
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
            std::cout << "PlaceBuilding error : There is a building next to this position" << std::endl;
            return false;
        }
    }

    return true;
}


bool PlaceBuildingCommand::execute(state::State* state) {
    if (buildingType == state::Colony){
        state->players[playerColor].resources[state::Lumber].number--;
        state->players[playerColor].resources[state::Brick].number--;
        state->players[playerColor].resources[state::Grain].number--;
        state->players[playerColor].resources[state::Wool].number--;

        state->players[playerColor].buildings.erase(state->players[playerColor].buildings.begin() + state->players[playerColor].getBuilding(buildingType)); //remove player building
        state->map.buildings.push_back(Building(playerColor, buildingType, position)); //add city to map
        return true;
    } else {//city
        state->players[playerColor].resources[state::Grain].number -= 2;
        state->players[playerColor].resources[state::Ore].number -= 3;

        state::Building* b = &(state->map.buildings[state->map.getBuilding(position)]);

        state->map.buildings.erase(state->map.buildings.begin() + state->map.getBuilding(position)); //remove colony from map
        state->players[playerColor].buildings.push_back(Building(playerColor, buildingType, position)); //give back colony to player
        state->map.buildings.push_back(Building(playerColor, buildingType, position)); //add city to map
        state->players[playerColor].buildings.erase(state->players[playerColor].buildings.begin() + state->players[playerColor].getBuilding(buildingType)); //remove player building

        return true;
    }

    return true;
}

bool PlaceBuildingCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;
    
    std::cout << "UNSERIALIZE \n";

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 9){
            playerColor = (PlayerColor) stoi(tokens[1]);
            position[0].x = stoi(tokens[2]);
            position[0].y = stoi(tokens[3]);
            position[1].x = stoi(tokens[4]);
            position[1].y = stoi(tokens[5]);
            position[2].x = stoi(tokens[6]);
            position[2].y = stoi(tokens[7]);
            buildingType = (BuildingType) stoi(tokens[8]);
        } else {
            std::cout << "Invalid number of arguments\n";
            return false;
        }
    }
    catch (const std::invalid_argument& ia) {
	    std::cerr << "Invalid argument: " << ia.what() << '\n';
        return false;
    }


    return true;
}

}