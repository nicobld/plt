#include "RenderPieces.h"
#include <iostream>

using namespace view;
using namespace std;

RenderPieces::RenderPieces(state::State state, sf::VertexArray& tile_vertices){
    thief = new sf::Sprite();
    buildingTexture.loadFromFile("../res/pieces.png");
    buildingTexture.setSmooth(true);

}

void RenderPieces::update(state::State state){
    buildings.clear();
    for(state::Building b : state.map.buildings){
        buildings.push_back(sf::Sprite(buildingTexture, sf::IntRect((b.buildingType * 4 + b.playerColor)*39, 0, 38, 37)));
    }
}

void RenderPieces::render(state::State state, sf::RenderTarget& target, sf::VertexArray& tile_vertices){
    update(state);

    std::tuple<state::Position, state::Position, state::Position>* tuple;
    sf::Vector2f centre1, centre2, centre3;
    for(int i = 0; i < buildings.size(); i++){
        tuple = &state.map.buildings[i].position;
        centre1 = (tile_vertices)[(get<0>(get<0>(*tuple)) + get<1>(get<0>(*tuple))*7)*12].position + sf::Vector2f(0, 65);
        centre2 = (tile_vertices)[(get<0>(get<1>(*tuple)) + get<1>(get<1>(*tuple))*7)*12].position + sf::Vector2f(0, 65);
        centre3 = (tile_vertices)[(get<0>(get<2>(*tuple)) + get<1>(get<2>(*tuple))*7)*12].position + sf::Vector2f(0, 65);
        buildings[i].setPosition((centre1.x + centre2.x + centre3.x)/3, (centre1.y + centre2.y + centre3.y)/3);
        buildings[i].setOrigin(19, 18.5);
        target.draw(buildings[i]);
    }
}