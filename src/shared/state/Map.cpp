#include "Map.h"
#include <cstring>

namespace state{

Map::Map(){
    //0: Hills, 1: Forest, 2: Mountains, 3: Fields, 4: Pasture
    //5: Desert, 6: Water, 7: NoTile
    int temp_grid[7][7] = {
        {7, 7, 6, 6, 6, 6, 7},
          {7, 6, 2, 4, 1, 0, 0},
        {7, 6, 3, 0, 0, 0, 0},
          {6, 3, 1, 5, 0, 0, 0},
        {7, 6, 1, 2, 0, 0, 0},
          {7, 6, 0, 3, 0, 0, 0},
        {7, 7, 6, 6, 6, 6, 7},
    };

    memcpy(grid, temp_grid, 49);
}

}
