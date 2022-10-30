#include "Map.h"
#include <cstring>

namespace state{

Map::Map(){
    //0: Hills, 1: Forest, 2: Mountains, 3: Fields, 4: Pasture
    //5: Desert, 6: Water, 7: NoTile
    int temp_grid[7][7] = {
        {7, 7, 6, 6, 6, 6, 7},
          {7, 6, 2, 4, 1, 6, 7},
        {7, 6, 3, 0, 4, 0, 6},
          {6, 3, 1, 5, 1, 2, 6},
        {7, 6, 1, 2, 3, 4, 6},
          {7, 6, 0, 3, 4, 6, 7},
        {7, 7, 6, 6, 6, 6, 7},
    };

    memcpy(grid, temp_grid, 49);
}

}
