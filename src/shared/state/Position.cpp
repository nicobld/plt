#include "Position.h"

namespace state {

Position::Position() {
    x = 0;
    y = 0;
}

Position::Position(int x, int y) : x(x), y(y) {}

Position operator+(Position pos1, Position pos2){
    return Position(pos1.x + pos2.x, pos1.y + pos2.y);
}

bool operator==(Position pos1, Position pos2){
    return (pos1.x == pos2.x) && (pos1.y == pos2.y);
}

Position operator-(Position pos1, Position pos2){
    return Position(pos1.x - pos2.x, pos1.y - pos2.y);
}
}