#include "Map.h"
#include <cstring>
#include <iostream>

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
          0, 0, 1, 2, 3, 0, 0,
        0, 0, 5, 6, 7, 8, 0,
          0, 9, 10, 11, 12, 13, 0,
        0, 0, 14, 15, 16, 17, 0,
          0, 0, 18, 19, 20, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
    };

    memcpy(grid, temp_grid, sizeof(int)*49);
    memcpy(tokengrid, temp_token_grid, sizeof(int)*49);
}

}
