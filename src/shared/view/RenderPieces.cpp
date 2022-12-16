#include "RenderPieces.h"
#include <cmath>
#include <string>
#include <iostream>

#define RESIZE 1 //NE PAS UTILISER MARCHE PAS

using namespace view;
using namespace std;
using namespace state;

RenderPieces::RenderPieces (state::State state, std::vector<Hexagone>* hexagones) : hexagones(hexagones) {

    buildingTexture.loadFromFile("../res/pieces.png");
    roadTexture.loadFromFile("../res/roadsIso.png");
    portTexture.loadFromFile("../res/portIso2.png");
    
    font.loadFromFile("../res/poppins.ttf");

    //Thief
    sf::Texture* thiefTexture = new sf::Texture();
    thiefTexture->loadFromFile("../res/thiefIso.png");
    thief = new sf::Sprite(*thiefTexture, sf::IntRect(0, 0, 128, 128));
    thief->setOrigin(128/2, 128/2);

    thief->setScale(0.65*RESIZE, 0.65*RESIZE);
    //creer les tokens pour placer sur les tiles

    
    for(int i = 0; i < 49; i++){
        if(state.map.tokengrid[i] != 0){
            if(!(state.map.thief.position.x == i%7  && state.map.thief.position.y == i/7)){    //vérifie s'il n'y a pas un voleur sur la case
                tokens.push_back(sf::Text(std::to_string(state.map.tokengrid[i]), font, 60));
                tokens.back().setOrigin(tokens.back().getGlobalBounds().width/2, tokens.back().getGlobalBounds().height/2);
                tokens.back().setPosition(hexagones->at(i).vertices[0].position + sf::Vector2f(-65, 32.5) + sf::Vector2f(-5, -25)); //65 = hauteur d'un tile/2
                tokens.back().setColor(sf::Color(255, 255, 215, 210));
                //tokens.back().setScale(RESIZE, RESIZE);
            }
        }
    }

    //initialisation des ports

    sf::Texture* iconTexture = new sf::Texture();
    iconTexture->loadFromFile("../res/icons.png");
    sf::Vector2f centre1;
    int offsetX, offsetY;
    
    for (int i=0; i<state.map.ports.size(); i++){
        if(state.map.ports[i].position[0].x < state.map.ports[i].position[1].x){
            if(state.map.ports[i].position[0].y < state.map.ports[i].position[1].y){
               ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*1, 0, 115, 60))); 
                offsetX = -30;
                offsetY = -60;
            }
            else if(state.map.ports[i].position[0].y > state.map.ports[i].position[1].y){
                ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*5, 0, 115, 60)));
                offsetX = -90;
                offsetY = -15;
            }
            else if(state.map.ports[i].position[0].y == state.map.ports[i].position[1].y){
                ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*3, 0, 115, 60)));
                offsetX = -50;
                offsetY = -60;
            }
        }
        else if(state.map.ports[i].position[0].x > state.map.ports[i].position[1].x){
            if(state.map.ports[i].position[0].y < state.map.ports[i].position[1].y){
                ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*4, 0, 115, 60))); 
                offsetX = 20;
                offsetY = -45;
            }
            else if(state.map.ports[i].position[0].y > state.map.ports[i].position[1].y){
                ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*0, 0, 115, 60)));
                offsetX = -30;
                offsetY = 0;
            }
            else if(state.map.ports[i].position[0].y == state.map.ports[i].position[1].y){
                ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*2, 0, 115, 60)));
                offsetX = 15;
                offsetY = -60;
            }
        }
        else if(state.map.ports[i].position[0].x == state.map.ports[i].position[1].x){
            if(state.map.ports[i].position[0].y < state.map.ports[i].position[1].y){
                if(state.map.ports[i].position[0].x == 5){
                    ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*4, 0, 115, 60))); 
                    offsetX = 20;
                    offsetY = -45;
                }
                else {
                    ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*1, 0, 115, 60))); 
                    offsetX = -30;
                    offsetY = -60;
                }
            }   
            else if(state.map.ports[i].position[0].y > state.map.ports[i].position[1].y){
                if(state.map.ports[i].position[0].x == 2){
                    ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*5, 0, 115, 60)));
                    offsetX = -60;
                    offsetY = -45; 
                }
                else {
                    ports.push_back(sf::Sprite(portTexture, sf::IntRect(115*0, 0, 115, 60)));
                    offsetX = -30;
                    offsetY = 0;
                }
            }
        }
        centre1 = hexagones->at(state.map.ports[i].position[0].x + state.map.ports[i].position[0].y*7).vertices[0].position + sf::Vector2f(-25, 55);
        
        ports.back().setScale(sf::Vector2f(1.5, 1.5));
        ports.back().setOrigin(ports.back().getGlobalBounds().width/2, ports.back().getGlobalBounds().height/2);
        ports.back().setPosition(centre1.x, centre1.y);
       
        portIcons.push_back(sf::Sprite(*iconTexture, sf::IntRect((state.map.ports[i].resourceType<5?state.map.ports[i].resourceType:7)*74, 0, 74, 58)));
        portIcons.back().setScale(0.27*RESIZE, 0.27*RESIZE);
        portIcons[i].setOrigin(74/2, 58/2);
        portIcons[i].setPosition(centre1 + sf::Vector2f(offsetX, offsetY));

        portTexts.push_back(sf::Text(to_string(state.map.ports[i].exchangeRate), font, 18));
        portTexts.back().setColor(sf::Color(255, 255, 255));
        portTexts[i].setPosition(portIcons[i].getPosition() - sf::Vector2f(17, 5));
        portTexts[i].setOrigin(portTexts[i].getGlobalBounds().width/2, portTexts[i].getGlobalBounds().height/2);
    }
}

void RenderPieces::update(state::State state){
    sf::Vector2f centre1, centre2, centre3;
    

    buildings.clear();
    //ajout des sprite buildings
    for(state::Building b : state.map.buildings){
        buildings.push_back(sf::Sprite(buildingTexture, sf::IntRect((b.buildingType * 4 + b.playerColor)*37, 0, 37, 37)));

        centre1 = hexagones->at(b.position[0].x + b.position[0].y*7).vertices[0].position + sf::Vector2f(-65, 32.5); //on trouve les 3 centres des tiles
        centre2 = hexagones->at(b.position[1].x + b.position[1].y*7).vertices[0].position + sf::Vector2f(-65, 32.5);
        centre3 = hexagones->at(b.position[2].x + b.position[2].y*7).vertices[0].position + sf::Vector2f(-65, 32.5);
        buildings.back().setPosition((centre1.x + centre2.x + centre3.x)/3, (centre1.y + centre2.y + centre3.y)/3); //moyenne sur les centres pour avoir la pointe qu'il faut pour placer le building
        buildings.back().setOrigin(19, 18.5);
        buildings.back().setScale(RESIZE, RESIZE);
        //cout << "x : " << buildings.back().getPosition().x << "  |  y : " << buildings.back().getPosition().y << endl;
    }

    int roadOffset = 0;
    roads.clear();
    //ajout des sprite road en fonction de la direction des road
    for(state::Road r : state.map.roads){
        //on calcule la disposition des 2 tiles pour savoir quelle direction est leur arrete commune
        if(r.position[0].y == r.position[1].y){
            roadOffset = 0;
        }
        else if(r.position[0].y%2 == 0){
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
        roads.push_back(sf::Sprite(roadTexture, sf::IntRect((r.playerColor + roadOffset) * 64, 0, 64, 32)));
        roads.back().setScale(sf::Vector2f(1.5, 1.5));
        roads.back().setOrigin(roads.back().getGlobalBounds().width/2, roads.back().getGlobalBounds().height/2);

        centre1 = hexagones->at(r.position[0].x + r.position[0].y*7).vertices[0].position + sf::Vector2f(-45, 45); //on trouve les 2 centres des tiles
        centre2 = hexagones->at(r.position[1].x + r.position[1].y*7).vertices[0].position + sf::Vector2f(-45, 45);
        

        roads.back().setPosition((centre1.x + centre2.x)/2, (centre1.y + centre2.y)/2); //leur moyenne donne le centre de leur arrete commune pour placer la route
        //roads.back().setScale(RESIZE, RESIZE);
    }

        
    thief->setPosition(hexagones->at(state.map.thief.position.x + state.map.thief.position.y*7).vertices[0].position + sf::Vector2f(-65, 32.5) + sf::Vector2f(0, -20));
}

void RenderPieces::render(state::State state, sf::RenderTarget& target){
    update(state); //pour l'instant on update à chaque render

    int i;

    for(i = 0; i < roads.size(); i++){
        target.draw(roads[i]);
    }
    
    for (i = 0; i < ports.size(); i++){
        target.draw(ports[i]);
        target.draw(portIcons[i]);
        target.draw(portTexts[i]);
    }

    for(i = 0; i < buildings.size(); i++){
        target.draw(buildings[i]);
    }

    for(int i = 0; i < tokens.size(); i++){
        
        target.draw(tokens[i]);
        //target.draw(spriteTokens.at(i));
    }

    target.draw(*thief);
}