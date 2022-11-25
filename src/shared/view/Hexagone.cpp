#include "Hexagone.h"

namespace view {

Hexagone::Hexagone() {}

void Hexagone::insertVerticesMap(sf::Vertex* hex){
    hex[0] = vertices[0];
    hex[1] = vertices[1];
    hex[2] = vertices[2];

    hex[3] = vertices[0];
    hex[4] = vertices[2];
    hex[5] = vertices[3];

    hex[6] = vertices[0];
    hex[7] = vertices[3];
    hex[8] = vertices[4];

    hex[9] = vertices[0];
    hex[10] = vertices[4];
    hex[11] = vertices[5];
}

sf::Vector2f Hexagone::getCenter(){
    sf::Vector2f center(0, 0);

    for (int i = 0; i < 6; i++){
        center += vertices[i].position;
    }

    return center/6.f;
}


}