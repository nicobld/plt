#include "Map.h"
#include <cstring>

namespace state{

Map::Map(){
  
    int temp_grid[49] = {
        0, 0, 13, 7, 7, 14, 0,
          0, 10, 5, 1, 2, 9, 0,
        0, 10, 4, 3, 1, 3, 9,
          18, 4, 2, 6, 2, 5, 17,
        0, 12, 2, 5, 4, 1, 11,
          0, 12, 3, 4, 1, 11, 0,
        0, 0, 16, 8, 8, 15, 0,
    };

    int temp_token_grid[49] = {
        0, 0, 0, 0, 0, 0, 0,
          0, 0, 10, 2, 9, 0, 0,
        0, 0, 12, 6, 4, 10, 0,
          0, 9, 11, 0, 3, 8, 0,
        0, 0, 8, 3, 4, 5, 0,
          0, 0, 5, 6, 11, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
    };

    /*debug grid*/
    // int temp_token_grid[49] = {
    //     00, 10, 20, 30, 40, 50, 60,
    //       01, 11, 21, 31, 41, 51, 61,
    //     02, 12, 22, 32, 42, 52, 62,
    //       03, 13, 23, 33, 43, 53, 63,
    //     04, 14, 24, 34, 44, 54, 64,
    //       05, 15, 25, 35, 45, 55, 65,
    //     06, 16, 26, 36, 46, 56, 66,
    // };

    memcpy(grid, temp_grid, sizeof(int)*49);
    memcpy(tokengrid, temp_token_grid, sizeof(int)*49);

    //Thief

    thief.position = Position(4, 3);

	//Roads

	roads.push_back(Road(PlayerRed, 2,4,2,3));
	roads.push_back(Road(PlayerRed, 3,2,3,1));
	roads.push_back(Road(PlayerBlue, 2,5,3,4));
	roads.push_back(Road(PlayerBlue, 4,4,5,4));
	roads.push_back(Road(PlayerYellow, 4,2,4,1));
	roads.push_back(Road(PlayerYellow, 3,5,4,4));
	roads.push_back(Road(PlayerGreen, 4,3,5,3));
	roads.push_back(Road(PlayerGreen, 2,3,2,2));

    //Buildings

    buildings.push_back(Building(PlayerRed, Colony, 2,4,1,3,2,3));
    buildings.push_back(Building(PlayerRed, Colony, 3,2,2,1,3,1));
    buildings.push_back(Building(PlayerBlue, Colony, 4,4,5,4,4,5));
    buildings.push_back(Building(PlayerBlue, Colony, 2,4,3,4,2,5));
    buildings.push_back(Building(PlayerYellow, Colony, 4,2,5,2,4,1));
    buildings.push_back(Building(PlayerYellow, Colony, 3,5,4,4,3,4));
    buildings.push_back(Building(PlayerGreen, Colony, 4,3,5,3,5,4));
    buildings.push_back(Building(PlayerGreen, Colony, 2,2,3,2,2,3));

    // Ports
    ports.push_back(Port(3, Nothing, 2, 0, 2, 1));
    ports.push_back(Port(2, Grain, 4, 0, 3, 1));
    ports.push_back(Port(2, Ore, 5, 1, 5, 2));
    ports.push_back(Port(3, Nothing, 6, 3, 5, 3));
    ports.push_back(Port(3, Wool, 5, 5, 5, 4));
    ports.push_back(Port(2, Nothing, 4, 6, 3, 5));
    ports.push_back(Port(3, Nothing, 2, 6, 2, 5));
    ports.push_back(Port(2, Brick, 1, 4, 2, 4));
    ports.push_back(Port(2, Lumber, 1, 2, 2, 2));
}

int Map::getBuilding(std::array<Position, 3> position){
	for (int i = 0; i < buildings.size(); i++){
		if (buildings[i].position == position){
			return i;
		}
	}
	return -1;
}

}
