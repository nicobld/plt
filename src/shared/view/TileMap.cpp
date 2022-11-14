#include "TileMap.h"
#include <iostream>
#include <cmath>

#define RESIZE 1.0f //NE PAS UTILISER MARCHE PAS

using namespace view;

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    //offset to place map in the middle
    int offsetX = 1280/7;
    int offsetY = 0;

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
                hex[0].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offsetX, j*0.75 * tileSize.y + offsetY);
                hex[0].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 0);

                //on tourne dans le sens d'une montre pour chercher les 2 prochains points
                switch (k){
                    case 0:
                        hex[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offsetX , (j*0.75 + 0.25) * tileSize.y + offsetY);
                        hex[2].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);

                        

                        hex[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.25 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);
                        break;
                    
                    case 1:
                        hex[1].position = sf::Vector2f((i + 1 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);
                        hex[2].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 1) * tileSize.y + offsetY);

                        hex[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, 0.75 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);
                        break;
                    
                    case 2:
                        hex[1].position = sf::Vector2f((i + 0.5 + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 1) * tileSize.y + offsetY);
                        hex[2].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);

                        hex[1].texCoords = sf::Vector2f((tileNumber + 0.5) * tileSize.x, 1 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);
                        break;

                    case 3:
                        hex[1].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.75) * tileSize.y + offsetY);
                        hex[2].position = sf::Vector2f((i + j%2 * 0.5) * tileSize.x + offsetX, (j*0.75 + 0.25) * tileSize.y + offsetY);

                        hex[1].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.75 * tileSize.y);
                        hex[2].texCoords = sf::Vector2f(tileNumber * tileSize.x, 0.25 * tileSize.y);
                        break;
                }

                /*
                hex[0].position.x *= cos(M_PI/4)/2;
                hex[1].position.x *= cos(M_PI/4)/2;
                hex[2].position.x *= cos(M_PI/4)/2;
                hex[0].texCoords.x *= cos(M_PI/4)/2;
                hex[1].texCoords.x *= cos(M_PI/4)/2;
                hex[2].texCoords.x *= cos(M_PI/4)/2;

                hex[0].position.y *= sin(M_PI/4)/2;
                hex[1].position.y *= sin(M_PI/4)/2;
                hex[2].position.y *= sin(M_PI/4)/2;
                hex[0].texCoords.y *= sin(M_PI/4)/2;
                hex[0].texCoords.y *= sin(M_PI/4)/2;
                hex[0].texCoords.y *= sin(M_PI/4)/2;
                */
                int xp, yp, xt, yt;
                float w = 2, h = 2; 
                for(int i=0; i<3; i++){
                    xp = hex[i].position.x, yp = hex[i].position.y, xt = hex[i].texCoords.x, yt = hex[i].texCoords.y;
                    hex[i].position.x = xp * 0.5 * w + yp * -0.5 * w;
                    hex[i].position.y = xp * 0.25 * h + yp * 0.25 * h;
                    //hex[i].texCoords.x = xt * 0.5 * w + yt * -0.5 * w;
                    //hex[i].texCoords.y = xt * 0.25 * h + yt * 0.25 * h;
                }

                hex[0].position *= RESIZE;
                hex[1].position *= RESIZE;
                hex[2].position *= RESIZE;
            }
        }

        std::cout <<"texcorrds1 : " << m_vertices[0].texCoords.x << "   | texcorrds1 : "  << m_vertices[0].texCoords.y <<std::endl;
        std::cout <<"texcorrds2 : " << m_vertices[1].texCoords.x << "   | texcorrds2 : "  << m_vertices[1].texCoords.y <<std::endl;
        std::cout <<"texcorrds3 : " << m_vertices[2].texCoords.x << "   | texcorrds3 : "  << m_vertices[2].texCoords.y <<std::endl;

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