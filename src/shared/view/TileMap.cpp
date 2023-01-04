#include "TileMap.h"
#include <iostream>
#include <cmath>
#include <limits>

#define RESIZE 1.0f //NE PAS UTILISER MARCHE PAS

static const state::Position neighbors[2][6] = {
    {state::Position(+1,  0), state::Position(0, -1), state::Position(-1, -1), state::Position(-1,  0), state::Position(-1, +1), state::Position(0, +1)},
    {state::Position(+1,  0), state::Position(1, -1), state::Position(0, -1), state::Position(-1,  0), state::Position(0, +1), state::Position(1, +1)}
};

static bool equalArray(std::array<int, 2> arr0, std::array<int, 2> arr1){
    if ( (arr0[0] == arr1[0] && arr0[1] == arr1[1]) || (arr0[0] == arr1[1] && arr0[1] == arr1[0]) ){
        return true;
    } else {
        return false;
    }
}

static state::Position getNeighborWithSommets(bool even, std::array<int, 2> sommets){
    if (equalArray(sommets, {0, 1})) return neighbors[even][1];
    else if (equalArray(sommets, {1, 2})) return neighbors[even][0];
    else if (equalArray(sommets, {2, 3})) return neighbors[even][5];
    else if (equalArray(sommets, {3, 4})) return neighbors[even][4];
    else if (equalArray(sommets, {4, 5})) return neighbors[even][3];
    else if (equalArray(sommets, {5, 0})) return neighbors[even][2];
}

namespace view {

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    
    sf::Texture* backgroundHex = new sf::Texture();
    backgroundHex->loadFromFile("../res/hexagoneBack.png");
    backgroundHex->setSmooth(true);
    back.setTexture(*backgroundHex);
    back.setTextureRect(sf::IntRect(0,0,1920, 1080));
    back.setOrigin(back.getGlobalBounds().width/2, back.getGlobalBounds().height/2);
    back.setPosition(1280/2 + 20, 720/2 + 30);
    back.setScale(sf::Vector2f(0.6, 0.6));

    
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    //offset to place map in the middle
    int offsetX = 250;
    int offsetY = -300;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 12);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int j = 0; j < height; ++j){
        for (unsigned int i = 0; i < width; ++i){
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + (j * width)];

            Hexagone hexagone;

            hexagone.vertices[0].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offsetX, j*0.75 * tileSize.y + offsetY);
            hexagone.vertices[0].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 0);

            hexagone.vertices[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offsetX , (j*0.75 + 0.25) * tileSize.y + offsetY);
            hexagone.vertices[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.25 * tileSize.y);

            hexagone.vertices[2].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);
            hexagone.vertices[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);

            hexagone.vertices[3].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 1) * tileSize.y + offsetY);
            hexagone.vertices[3].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);

            hexagone.vertices[4].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);
            hexagone.vertices[4].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);

            hexagone.vertices[5].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.25) * tileSize.y + offsetY);
            hexagone.vertices[5].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.25 * tileSize.y);
                
            int xp, yp;
            for(int i = 0; i < 6; i++){ //iso transformation
                xp = hexagone.vertices[i].position.x, yp = hexagone.vertices[i].position.y;
                hexagone.vertices[i].position.x = xp - yp;
                hexagone.vertices[i].position.y = xp * 0.5 + yp * 0.5;
            }
            
            //get the actual vertices into m_vertices
            hexagone.insertVerticesMap(&m_vertices[(i + j * width) * 12]);

            hexagones.push_back(hexagone);

            }
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
 
    target.draw(back);
    target.draw(m_vertices, states);
}

std::array<state::Position, 2> TileMap::findClosestRoad(int x, int y){
    std::array<state::Position, 2> pos = {state::Position(0, 0), state::Position(0, 0)};
    float min;
    float distance;
    sf::Vector2f center;

    min = std::numeric_limits<float>::max();

    for (int h = 0; h < 49; h++){
        center = hexagones[h].getCenter();
        distance = sqrt(pow(x - center.x, 2.0) + pow(y - center.y, 2.0));
        if (distance < min){
            min = distance;
            pos[0].x = h%7;
            pos[0].y = h/7;
        }
    }
    
    std::array<int, 2> sommets = {0, 0};
    /* minisDist[0] < minisDist[1]*/
    std::array<float, 2> miniDist = {std::numeric_limits<float>::max() - 1, std::numeric_limits<float>::max()};
    Hexagone hexa = hexagones[pos[0].x + pos[0].y*7];

    for (int k = 0; k < 6; k++){
        distance = sqrt(pow(x - hexa.vertices[k].position.x, 2.0) + pow(y - hexa.vertices[k].position.y, 2.0));
        if (distance < miniDist[1]){
            if (distance < miniDist[0]){
                miniDist[1] = miniDist[0];
                sommets[1] = sommets[0];

                miniDist[0] = distance;
                sommets[0] = k;
            } else {
                miniDist[1] = distance;
                sommets[1] = k;
            }
        }
    }

    pos[1] = pos[0] + getNeighborWithSommets(pos[0].y%2, sommets);
    return pos;
}

}