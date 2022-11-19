#include "TileMap.h"
#include <iostream>
#include <cmath>

#define RESIZE 1.0f //NE PAS UTILISER MARCHE PAS

using namespace view;

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    
    sf::Texture* backgroundHex = new sf::Texture();
    backgroundHex->loadFromFile("../res/hexagoneBack.png");
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
                
                int xp, yp;
                for(int i=0; i<3; i++){
                    xp = hex[i].position.x, yp = hex[i].position.y;
                    hex[i].position.x = xp - yp;
                    hex[i].position.y = xp * 0.5 + yp * 0.5;
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
 
    target.draw(back);

    target.draw(m_vertices, states);
}