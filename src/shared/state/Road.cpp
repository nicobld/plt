#include "Road.h"

namespace state{

Road::Road(PlayerColor playerColor, int x1, int y1, int x2, int y2) : playerColor(playerColor) {
    position[0].x = x1;
    position[0].y = y1;
    position[1].x = x2;
    position[1].y = y2;
}

Road::Road(PlayerColor playerColor, std::array<Position, 2> position) : playerColor(playerColor), position(position) {
}

}
