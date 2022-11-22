#include "PlaceRoadCommand.h"
#include <iostream>

using namespace state;

namespace engine {

const Position neighbors[2][6] = {
    {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
    {Position(+1,  0), Position(1, -1), Position(0, -1), Position(-1,  0), Position(0, +1), Position(1, +1)}
};

bool isNeighbor(Position pos1, Position pos2){

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

/*
* Returns 2 tiles which are road neighbors
*/
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

bool equalArrayPos(std::array<Position, 2> pos1, std::array<Position, 2> pos2){
    return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
}

/*
* return true if there is a road on the map at position pos
*/
bool hasRoad(state::State* state, std::array<Position, 2> pos){
    for (Road road : state->map.roads){
        if (equalArrayPos(road.position, pos))
            return true;
    }
    return false;
}

void afficheRoadPos(std::string s, std::array<Position, 2> curPos){
    std::cout << s << std::endl;
    std::cout << "Position 0 : " << curPos[0].x << ", " << curPos[0].y << std::endl;
    std::cout << "Position 1 : " << curPos[1].x << ", " << curPos[1].y << std::endl << std::endl;
}

void afficheTilePos(std::string s, Position pos){
    std::cout << s << std::endl;
    std::cout << "Tile pos : " << pos.x << ", " << pos.y << std::endl << std::endl;
}

/*
* On part d'une route qui est en extrémité
*/
int countMaxRoad(state::State* state, std::array<Position, 2> curPos){
    static int maxRoad = 1;
    int localMaxRoad = 1;
    std::vector<Road>* roads = &(state->map.roads);
    std::array<Position, 2> tileNeighbors;
    Position nextTile;
    Position tempCurPos;

    tileNeighbors = findTilesRoadNeighbors(state, curPos);

    if (tileNeighbors[1] == Position(0, 0))
        std::cout << "tileNeighbors error" << std::endl;

    //on prend comme nextTile celui qui possède une route
    if (hasRoad(state, {tileNeighbors[0], curPos[0]}) || hasRoad(state, {tileNeighbors[0], curPos[1]}))
        nextTile = tileNeighbors[0];
    else
        nextTile = tileNeighbors[1];

    //tant qu'il y a exactement 1 route sur le chemin (pas d'intersection)
    while (hasRoad(state, {nextTile, curPos[0]}) ^ hasRoad(state, {nextTile, curPos[1]})){
        maxRoad++;

        if (hasRoad(state, {nextTile, curPos[0]})){
            tempCurPos = curPos[1]; //on sauvegarde le curpos non choisi
            curPos[1] = nextTile;
            tileNeighbors = findTilesRoadNeighbors(state, curPos);
            if (tileNeighbors[0] == tempCurPos)
                nextTile = tileNeighbors[1];
            else 
                nextTile = tileNeighbors[0];

        } else if (hasRoad(state, {nextTile, curPos[1]})){
            tempCurPos = curPos[0];
            curPos[0] = nextTile;
            tileNeighbors = findTilesRoadNeighbors(state, curPos);
            if (tileNeighbors[0] == tempCurPos)
                nextTile = tileNeighbors[1];
            else 
                nextTile = tileNeighbors[0];
        }
    }

    return maxRoad;
}


std::vector<std::array<Position,2>> findEndRoads(state::State* state){
    std::vector<std::array<Position,2>> endRoads;
    std::vector<Road>* roads = &(state->map.roads);
    std::array<Position, 2> tileNeighbors;
    Position tempNeighbors;

    for(int i = 0; i< roads->size(); i++){
        tileNeighbors = findTilesRoadNeighbors(state, (*roads)[i].position);
        std::cout << "route testé n° "<< i << std::endl;
        if (!(hasRoad( state, {(*roads)[i].position[0],tileNeighbors[0]})) && !(hasRoad( state, {(*roads)[i].position[1], tileNeighbors[0]}))){
            std::cout << "Test 1" << std::endl;
            endRoads.push_back((*roads)[i].position);
            afficheRoadPos("route avec extremité", endRoads.back());
        }
        else if(!(hasRoad( state, {(*roads)[i].position[0], tileNeighbors[1]})) && !(hasRoad( state, {(*roads)[i].position[1], tileNeighbors[1]}))){
            std::cout << "Test 2" << std::endl;
            //if(endRoads.back() != (*roads)[i].position){
                std::cout << "elle n'y est pas deja" << std::endl;
                endRoads.push_back((*roads)[i].position);
                afficheRoadPos("route avec extremité", endRoads.back());
            //}
        }
    }

    return endRoads;
}

}