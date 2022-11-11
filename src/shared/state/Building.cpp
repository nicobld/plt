#include "Building.h"

namespace state{

Building::Building(PlayerColor playerColor, BuildingType buildingType, int x1, int y1, int x2, int y2, int x3, int y3): playerColor(playerColor), buildingType(buildingType) {
    position[0].x = x1;
    position[0].y = y1;
    position[1].x = x2;
    position[1].y = y2;
    position[2].x = x3;
    position[2].y = y3;
}

}
