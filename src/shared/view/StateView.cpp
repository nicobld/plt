#include "StateView.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace view;

StateView::StateView(state::State& state) : state(state){
    int width = 1280;
    int height = 720;
    

    displayHUD = new DisplayHUD(width, height, state.players[0], state.players[1], state.players[2], state.players[3]);
    
    tileMap = new TileMap();
    tileMap->load("../res/tilesHexIso.png", sf::Vector2u(114, 131), state.map.grid, 7, 7);

    //renderPieces = new RenderPieces(state, &tileMap->m_vertices, hexagones);
    // tileMap->setOrigin((8*114)/2, 719/2);
    // tileMap->setPosition(width/2, 30 + height/2);
    // tileMap->setScale(sf::Vector2f(0.9, 0.9));
    
    std::cout << "avant menu" << std::endl;
    MenuBuild menu1(state.players[0], textureFolder);
    MenuBuild menu2(state.players[1], textureFolder);


}

void StateView::render(sf::RenderTarget& target){
   //renderPieces->render(state, target);
    
    // menu1.render(target);
    // menu2.render(target);

}