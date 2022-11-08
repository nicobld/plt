#include "TileMap.h"
#include <iostream>

using namespace view;

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    //offset to place map in the middle
    sf::Vector2u offset = sf::Vector2u(0, 0);
    float resize = 1;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 12);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i){
            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + (j * width)];

            //on boucle sur les 4 triangles
            for (unsigned int k = 0; k < 4; k++){
                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* hex = &m_vertices[(i + j * width) * 12 + k * 3];

                //la pointe en haut de l'hexagone
                hex[0].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offset.x, j*0.75 * tileSize.y + offset.y);
                hex[0].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 0);

                //on tourne dans le sens d'une montre pour chercher les 2 prochains points
                switch (k){
                    case 0:
                        hex[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.25) * tileSize.y + offset.y);
                        hex[2].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.75) * tileSize.y + offset.y);

                        hex[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.25 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);
                        break;
                    
                    case 1:
                        hex[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.75) * tileSize.y + offset.y);
                        hex[2].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 1) * tileSize.y + offset.y);

                        hex[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);
                        break;
                    
                    case 2:
                        hex[1].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 1) * tileSize.y + offset.y);
                        hex[2].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.75) * tileSize.y + offset.y);

                        hex[1].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);
                        break;

                    case 3:
                        hex[1].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.75) * tileSize.y + offset.y);
                        hex[2].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offset.x, (j*0.75 + 0.25) * tileSize.y + offset.y);

                        hex[1].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.25 * tileSize.y);
                        break;
                }

                hex[0].position *= resize;
                hex[1].position *= resize;
                hex[2].position *= resize;

                // hex[0].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x, j*0.75 * tileSize.y);
                // hex[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x, (j*0.75 + 0.25) * tileSize.y);
                // hex[2].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x, (j*0.75 + 0.75) * tileSize.y);
                // hex[3].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x, (j*0.75 + 1) * tileSize.y);
                // hex[4].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x, (j*0.75 + 0.75) * tileSize.y);
                // hex[5].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x, (j*0.75 + 0.25) * tileSize.y);

                // hex[0].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 0);
                // hex[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.25 * tileSize.y);
                // hex[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);
                // hex[3].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);
                // hex[4].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);
                // hex[5].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.25 * tileSize.y);
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
    target.draw(m_vertices, states);
}