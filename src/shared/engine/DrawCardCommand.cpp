#include "DrawCardCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>

namespace engine {

DrawCardCommand::DrawCardCommand(state::PlayerColor playerColor): playerColor(playerColor){
    //this->playerColor = playerColor;
}

bool DrawCardCommand::execute(state::State* state ) {
    
    //verify player's exchange possibility
/*
    
    std::vector<state::Resource> &playerResources = state->players[this->playerColor].resources;
    if (std::find(playerResources.begin(), playerResources.end(), state::Grain)==state::Grain && std::find(playerResources.begin(), playerResources.end(), state::Ore)==state::Ore && std::find(playerResources.begin(), playerResources.end(), state::Wool)==state::Wool){

/*

        //pay the resources
        
        playerResources.erase(std::find(playerResources.begin(), playerResources.end(), state::Grain));
        playerResources.erase(std::find(playerResources.begin(), playerResources.end(), state::Ore));
        playerResources.erase(std::find(playerResources.begin(), playerResources.end(), state::Wool));

        //... and put them back into the ressources pile
        state->gameCards.resources.push_back(state::Grain);
        state->gameCards.resources.push_back(state::Ore);
        state->gameCards.resources.push_back(state::Wool);



        //boucle for de secours
        for (size_t i = 0; i < sizeof(playerResources); i++)
        {
            if ((playerResources[i] == state::Grain) || (playerResources[i] == state::Wool) || (playerResources[i] == state::Ore)){ 
                //operator== need overloading method to work
                playerResources.erase(playerResources.begin()+i); //retire le i-ème élément
            }

        }

        state->gameCards.resources.push_back(state::Grain);
        state->gameCards.resources.push_back(state::Ore);
        state->gameCards.resources.push_back(state::Wool);

        

        //draw the dev card
        int decksize = sizeof(state->gameCards.developments);
        int randomNb = rand() % decksize; //shuffling then drawing the top card could be an option
        state::Development development = state->gameCards.developments[randomNb];

        state::PlayerColor turnCount = state->turn;
        state->players[this->playerColor].developments.push_back(development);
        std::cout << "car added to player " << std::endl; //test line
        //rajouter exception pour tester le cas où ça fonctionne pas
        if (state->gameCards.developments.empty()){
            std::string e = "cartes de dévelopements épuisées";
            throw(e);
        }*/
        
        return true;
        
    }


}

//}