#include "RenderPieces.h"
#include <iostream>
#include <string>

using namespace view;
using namespace std;
using namespace state;

RenderPieces::RenderPieces (state::State state, sf::VertexArray& tile_vertices){
    thief = new sf::Sprite();
    buildingTexture.loadFromFile("../res/pieces.png");
    roadTexture.loadFromFile("../res/roads.png");
    portTexture.loadFromFile("../res/port.png");

    font.loadFromFile("../res/poppins.ttf");

    //creer les tokens pour placer sur les tiles
    for(int i = 0; i < 49; i++){
        if(state.map.tokengrid[i] != 0){
            tokens.push_back(sf::Text(std::to_string(state.map.tokengrid[i]), font, 60));
            tokens.back().setOrigin(tokens.back().getGlobalBounds().width/2, tokens.back().getGlobalBounds().height/2);
            tokens.back().setPosition(tile_vertices[i*12].position + sf::Vector2f(0, 55)); //65 = hauteur d'un tile/2
            tokens.back().setColor(sf::Color(255, 255, 255, 190));
        }
    }

    //initialisation des ports

    sf::Texture* iconTexture = new sf::Texture();
    iconTexture->loadFromFile("../res/icons.png");

    for (Port port : state.map.ports){
        ports.push_back(sf::Sprite(portTexture, sf::IntRect(0, 0, 128, 128)));
        portTexts.push_back(sf::Text(to_string(port.exchangeRate) + ":1", font, 24));
        portIcons.push_back(sf::Sprite(*iconTexture, sf::IntRect((port.resourceType<5?port.resourceType:7)*74, 0, 74, 58)));
        portIcons.back().setScale(0.5, 0.5);
    }
        
    sf::Vector2f v;
    sf::Vector2f centre1, centre2;
    std::array<Position, 2>* array2;
    float portRotation;

    for(int i = 0; i < ports.size(); i++){
        array2 = &state.map.ports[i].position;

        if (state.map.grid[(*array2)[0].x + (*array2)[0].y*7] > state.map.grid[(*array2)[1].x + (*array2)[1].y*7]){
            //port.position[0] is the beach
            centre1 = (tile_vertices)[(((*array2)[0].x + (*array2)[0].y*7))*12].position + sf::Vector2f(0, 65);
            centre2 = (tile_vertices)[(((*array2)[1].x + (*array2)[1].y*7))*12].position + sf::Vector2f(0, 65);
        } else {
            //port.position[1] is the beach
            centre1 = (tile_vertices)[(((*array2)[1].x + (*array2)[1].y*7))*12].position + sf::Vector2f(0, 65);
            centre2 = (tile_vertices)[(((*array2)[0].x + (*array2)[0].y*7))*12].position + sf::Vector2f(0, 65);
        }
        ports[i].setPosition(centre1.x, centre1.y);
        ports[i].setOrigin(portTexture.getSize().x/2, portTexture.getSize().y/2);

        v = centre1 - centre2;
        if (centre1.y == centre2.y){
            if (v.x > 0)
                portRotation = 180;
            else
                portRotation = 0;
            
        } else if (v.x > 0 && v.y > 0)
            portRotation = 240;
        else if (v.x > 0 && v.y < 0)
            portRotation = 120;
        else if (v.x < 0 && v.y > 0)
            portRotation = 300;
        else
            portRotation = 60;

        ports[i].setRotation(portRotation);

        portIcons[i].setPosition(centre1 + sf::Vector2f(0, 0));
        portIcons[i].setOrigin(74/2, 58/2);

        portTexts[i].setPosition(centre1 - sf::Vector2f(0, 30));
        portTexts[i].setOrigin(portTexts[i].getGlobalBounds().width/2, portTexts[i].getGlobalBounds().height/2);
    }

}

void RenderPieces::update(state::State state){
    buildings.clear();
    //ajout des sprite buildings
    for(state::Building b : state.map.buildings){
        buildings.push_back(sf::Sprite(buildingTexture, sf::IntRect((b.buildingType * 4 + b.playerColor)*37, 0, 37, 37)));
    }

    int roadOffset = 0;
    roads.clear();
    //ajout des sprite road en fonction de la direction des road
    for(state::Road r : state.map.roads){
        //on calcule la disposition des 2 tiles pour savoir quelle direction est leur arrete commune
        if(r.position[0].y == r.position[1].y){
            roadOffset = 0;
        }
        else if(r.position[0].x%2 == 0){
            if(r.position[1] - r.position[0] == Position(0, -1) || r.position[1] - r.position[0] == Position(-1, 1)){
                roadOffset = 8;
            } else if (r.position[1] - r.position[0] == Position(-1, -1) || r.position[1] - r.position[0] == Position(0, 1)){
                roadOffset = 4;
            }
        }
        else {
            if(r.position[1] - r.position[0] == Position(1, -1) || r.position[1] - r.position[0] == Position(0, 1)){
                roadOffset = 8;
            } else if (r.position[1] - r.position[0] == Position(0, -1) || r.position[1] - r.position[0] == Position(1, 1)){
                roadOffset = 4;
            }
        }
        roads.push_back(sf::Sprite(roadTexture, sf::IntRect((r.playerColor + roadOffset) * 56, 0, 56, 58)));
    }
}

void RenderPieces::render(state::State state, sf::RenderTarget& target, sf::VertexArray& tile_vertices){
    update(state);

    std::array<Position, 3>* array;
    sf::Vector2f centre1, centre2, centre3;
    std::array<Position, 2>* array2;
    float portRotation;
    int i;

    for(i = 0; i < roads.size(); i++){
        array2 = &state.map.roads[i].position;
        centre1 = (tile_vertices)[(((*array2)[0].x + (*array2)[0].y*7))*12].position + sf::Vector2f(0, 65); //on trouve les 2 centres des tiles
        centre2 = (tile_vertices)[(((*array2)[1].x + (*array2)[1].y*7))*12].position + sf::Vector2f(0, 65);
        roads[i].setPosition((centre1.x + centre2.x)/2, (centre1.y + centre2.y)/2); //leur moyenne donne le centre de leur arrete commune pour placer la route
        roads[i].setOrigin(28, 29);

        target.draw(roads[i]);
    }

    for(i = 0; i < buildings.size(); i++){
        array = &state.map.buildings[i].position;
        centre1 = (tile_vertices)[(((*array)[0].x + (*array)[0].y*7))*12].position + sf::Vector2f(0, 65); //on trouve les 3 centres des tiles
        centre2 = (tile_vertices)[(((*array)[1].x + (*array)[1].y*7))*12].position + sf::Vector2f(0, 65);
        centre3 = (tile_vertices)[(((*array)[2].x + (*array)[2].y*7))*12].position + sf::Vector2f(0, 65);
        buildings[i].setPosition((centre1.x + centre2.x + centre3.x)/3, (centre1.y + centre2.y + centre3.y)/3); //moyenne sur les centres pour avoir la pointe qu'il faut pour placer le building
        buildings[i].setOrigin(19, 18.5);

        target.draw(buildings[i]);
    }

    for (i = 0; i < ports.size(); i++){
        target.draw(portIcons[i]);
        target.draw(portTexts[i]);
        target.draw(ports[i]);
    }

    


    for(int i = 0; i < tokens.size(); i++){
        target.draw(tokens[i]);
    }
}