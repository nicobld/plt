#include "PlaceRoadCommand.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace state;

const Position neighbors[2][6] = {
    {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
    {Position(+1,  0), Position(1, -1), Position(0, -1), Position(-1,  0), Position(0, +1), Position(1, +1)}
};

static bool isNeighbor(Position pos1, Position pos2){

    Position pos = pos2 - pos1;
    if (pos == Position(0, 0))
        return true;
    for (int i = 0; i < 6; i++){
        if (pos == neighbors[pos1.y % 2][i])
            return true;
    }
    return false;
}

static void afficheRoadPos(std::string s, std::array<Position, 2> curPos){
    std::cout << s << std::endl;
    std::cout << "Position 0 : " << curPos[0].x << ", " << curPos[0].y << std::endl;
    std::cout << "Position 1 : " << curPos[1].x << ", " << curPos[1].y << std::endl << std::endl;
}

/*
* Returns 2 tiles which are road neighbors
*/
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

static bool equalArrayPos(std::array<Position, 2> pos1, std::array<Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}

/*
* return true if there is a road on the map at position pos
*/
static bool hasRoad(state::State* state, std::array<Position, 2> pos, state::PlayerColor playerColor){
    for (Road road : state->map.roads){
        if (equalArrayPos(road.position, pos) && road.playerColor == playerColor)
            return true;
    }
    return false;
}

static void afficheTilePos(std::string s, Position pos){
    std::cout << s << std::endl;
    std::cout << "Tile pos : " << pos.x << ", " << pos.y << std::endl << std::endl;
}



static bool hasVisitedRoad(std::array<Position, 2> road, std::vector<std::array<Position, 2>>& localVisitedRoads){
    for (std::array<Position, 2> r : localVisitedRoads){
        if (equalArrayPos(road, r)){
            return true;
        }
    }
    return false;
}

/*
* On part d'une route qui est en extrémité
*/
static int countMaxRoadFromEnd(state::State* state, std::array<Position, 2> curPos, Position visitedRoadNeighbor, std::vector<std::array<Position,2>> lastLocalVisitedRoads, state::PlayerColor playerColor){
    int localMaxRoad = 1;
    std::vector<std::array<Position, 2>> localVisitedRoads;
    std::vector<Road>* roads = &(state->map.roads);
    std::array<Position, 2> tileNeighbors;
    Position nextTile;
    Position tempCurPos;
    //int interMaxRoad;

    localVisitedRoads.insert(std::end(localVisitedRoads), std::begin(lastLocalVisitedRoads), std::end(lastLocalVisitedRoads));

    //localVisitedRoads.push_back({curPos[1], visitedRoadNeighbor}); //affreux, c'est le curPos d'avant l'intersection

    localVisitedRoads.push_back(curPos);

    tileNeighbors = findTilesRoadNeighbors(state, curPos);

    if (tileNeighbors[1] == Position(0, 0))
        std::cout << "tileNeighbors error" << std::endl;

    //on prend comme nextTile celui qui possède une route et qui n'est pas celui qui à été noté par l'intersection
    if ((hasRoad(state, {tileNeighbors[0], curPos[0]}, playerColor) || hasRoad(state, {tileNeighbors[0], curPos[1]}, playerColor)) && !(visitedRoadNeighbor == tileNeighbors[0]))
        nextTile = tileNeighbors[0];
    else if ((hasRoad(state, {tileNeighbors[1], curPos[0]}, playerColor) || hasRoad(state, {tileNeighbors[1], curPos[1]}, playerColor)) && !(visitedRoadNeighbor == tileNeighbors[1]))
        nextTile = tileNeighbors[1];
    else {
        return 1;
    }

    //tant qu'il y a exactement 1 route sur le chemin (pas d'intersection)
    while ((hasRoad(state, {nextTile, curPos[0]}, playerColor) ^ hasRoad(state, {nextTile, curPos[1]}, playerColor))){
        if (hasRoad(state, {nextTile, curPos[0]}, playerColor)){
            tempCurPos = curPos[1]; //on sauvegarde le curPos non choisi
            curPos[1] = nextTile;
            tileNeighbors = findTilesRoadNeighbors(state, curPos);
            if (tileNeighbors[0] == tempCurPos)
                nextTile = tileNeighbors[1];
            else 
                nextTile = tileNeighbors[0];

        } else if (hasRoad(state, {nextTile, curPos[1]}, playerColor)){
            tempCurPos = curPos[0];
            curPos[0] = nextTile;
            tileNeighbors = findTilesRoadNeighbors(state, curPos);
            if (tileNeighbors[0] == tempCurPos)
                nextTile = tileNeighbors[1];
            else 
                nextTile = tileNeighbors[0];
        }

        if (hasVisitedRoad(curPos, localVisitedRoads)){
            return localMaxRoad;
        }
        localVisitedRoads.push_back(curPos);
        localMaxRoad++;
    }

    //intersection
    if (hasRoad(state, {nextTile, curPos[0]}, playerColor) && hasRoad(state, {nextTile, curPos[1]}, playerColor)){
        if (hasVisitedRoad({nextTile, curPos[0]}, localVisitedRoads) || hasVisitedRoad({nextTile, curPos[1]}, localVisitedRoads)){
            return localMaxRoad;
        }
        localMaxRoad += std::max(countMaxRoadFromEnd(state, {nextTile, curPos[0]}, curPos[1], localVisitedRoads, playerColor), countMaxRoadFromEnd(state, {nextTile, curPos[1]}, curPos[0], localVisitedRoads, playerColor));
    }

    return localMaxRoad;
}


static std::vector<std::array<Position,2>> findEndRoads(state::State* state, state::PlayerColor playerColor){
    std::vector<std::array<Position,2>> endRoads;
    std::vector<Road>* roads = &(state->map.roads);
    std::array<Position, 2> tileNeighbors;
    Position tempNeighbors;

    for(int i = 0; i < roads->size(); i++){
        if (roads->at(i).playerColor == playerColor){
            tileNeighbors = findTilesRoadNeighbors(state, (*roads)[i].position);
            if (!(hasRoad( state, {(*roads)[i].position[0],tileNeighbors[0]}, playerColor)) && !(hasRoad( state, {(*roads)[i].position[1], tileNeighbors[0]}, playerColor))){
                endRoads.push_back((*roads)[i].position);
            }
            else if(!(hasRoad( state, {(*roads)[i].position[0], tileNeighbors[1]}, playerColor)) && !(hasRoad( state, {(*roads)[i].position[1], tileNeighbors[1]}, playerColor))){
                endRoads.push_back((*roads)[i].position);
            }
        }
    }

    return endRoads;
}


static int countMaxRoad(state::State* state, state::PlayerColor playerColor){
    std::vector<std::array<Position,2>> endRoads = findEndRoads(state, playerColor);
    int maxRoad = 0;
    int tempMaxRoad;
    for (std::array<Position,2> endRoad : endRoads){
        if (maxRoad < (tempMaxRoad = countMaxRoadFromEnd(state, endRoad, Position(0,0), {}, playerColor))){
            maxRoad = tempMaxRoad;
        }
    }

    return maxRoad;
}



namespace engine {

PlaceRoadCommand::PlaceRoadCommand() {}

PlaceRoadCommand::PlaceRoadCommand(state::PlayerColor playerColor, std::array<Position, 2> position): position(position) {
    this->playerColor = playerColor;
    commandID = PLACE_ROAD_CMD;
}

bool PlaceRoadCommand::verify(state::State* state){
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

    //verifie s'il y a une route de la bonne couleur à côté
    bool foundRoad = false;
    for (Road r : state->map.roads){
        if (r.playerColor == playerColor){
            if (isNeighbor(position[0], r.position[0]) && isNeighbor(position[0], r.position[1]) && isNeighbor(position[1], r.position[0]) && isNeighbor(position[1], r.position[1])){
                foundRoad = true;
            }
        }
    }
    if (!foundRoad) return false;

    return true;
}



bool PlaceRoadCommand::execute(state::State* state) {
    int maxRoad = 4;
    int tempMaxRoad;
    int bestPlayer = -1;

    //place la route et retire la route au joueur
    state->map.roads.push_back(Road(playerColor, position));
    state->players[playerColor].roads.pop_back();

    for (int i = 0; i < state->players.size(); i++){
        state->players[i].hasLongestRoad = false;
        if (maxRoad < (tempMaxRoad = countMaxRoad(state, state->players[i].playerColor))){
            maxRoad = tempMaxRoad;
            bestPlayer = i;
        }
        state->players[i].longestRoad = tempMaxRoad;
    }
    if (bestPlayer != -1){
        state->players[bestPlayer].hasLongestRoad = true;
    }
    afficheRoadPos("COMMAND : Placed road at\n", position);
    return true;
}


bool PlaceRoadCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    std::cout << "UNSERIALIZE \n";

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 6){
            playerColor = (PlayerColor) stoi(tokens[1]);
            position[0].x = stoi(tokens[2]);
            position[0].y = stoi(tokens[3]);
            position[1].x = stoi(tokens[4]);
            position[1].y = stoi(tokens[5]);
        } else {
            std::cout << "Invalid number of arguments\n";
        }
    }
    catch (const std::invalid_argument& ia) {
	    std::cerr << "Invalid argument: " << ia.what() << '\n';
        return false;
    }

    return true;
}


}