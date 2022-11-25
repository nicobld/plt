#include "TileMap.h"
#include <iostream>
#include <cmath>

#define RESIZE 1.0f //NE PAS UTILISER MARCHE PAS

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
                for(int i = 0; i < 6; i++){
                    xp = hexagone.vertices[i].position.x, yp = hexagone.vertices[i].position.y;
                    hexagone.vertices[i].position.x = xp - yp;
                    hexagone.vertices[i].position.y = xp * 0.5 + yp * 0.5;
                }
                
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

}