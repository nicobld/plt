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

    // int temp_token_grid[49] = {
    //     0, 0, 0, 0, 0, 0, 0,
    //       0, 0, 1, 2, 3, 0, 0,
    //     0, 0, 5, 6, 7, 8, 0,
    //       0, 9, 10, 11, 12, 13, 0,
    //     0, 0, 14, 15, 16, 17, 0,
    //       0, 0, 18, 19, 20, 0, 0,
    //     0, 0, 0, 0, 0, 0, 0,
    // };

    
    int temp_token_grid[49] = {
        00, 10, 20, 30, 40, 50, 60,
          01, 11, 21, 31, 41, 51, 61,
        02, 12, 22, 32, 42, 52, 62,
          03, 13, 23, 33, 43, 53, 63,
        04, 14, 24, 34, 44, 54, 64,
          05, 15, 25, 35, 45, 55, 65,
        06, 16, 26, 36, 46, 56, 66,
    };

    memcpy(grid, temp_grid, sizeof(int)*49);
    memcpy(tokengrid, temp_token_grid, sizeof(int)*49);

    buildings.push_back(Building(PlayerRed, City));
    buildings.back().position = {Position(1, 1), Position(2, 1), Position(2, 2)};

    buildings.push_back(Building(PlayerBlue, City));
    buildings.back().position = {Position(3, 2), Position(2, 3), Position(3, 3)};

    buildings.push_back(Building(PlayerGreen, Colony));
    buildings.back().position = {Position(1, 3), Position(1, 2), Position(0, 3)};

    roads.push_back(Road(PlayerRed));
    roads.back().position = {Position(1, 1), Position(2, 2)};

    roads.push_back(Road(PlayerRed));
    roads.back().position = {Position(1, 2), Position(2, 2)};

    roads.push_back(Road(PlayerRed));
    roads.back().position = {Position(1, 3), Position(2, 2)};

    roads.push_back(Road(PlayerRed));
    roads.back().position = {Position(1, 3), Position(2, 3)};

    // Ports

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(6, 3), Position(5, 3)};

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(6, 2), Position(5, 3)};

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(6, 4), Position(5, 3)};

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(1, 4), Position(1, 3)};

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(0, 3), Position(1, 3)};

    ports.push_back(Port(2, Wool));
    ports.back().position = {Position(1, 3), Position(1, 2)};
}

}
