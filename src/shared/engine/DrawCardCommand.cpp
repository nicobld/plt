#include "DrawCardCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>

namespace engine {

DrawCardCommand::DrawCardCommand(state::PlayerColor playerColor): playerColor(playerColor){
    //this->playerColor = playerColor;
    std::cout << this->playerColor << std::endl;
}

bool DrawCardCommand::execute(state::State* state) {
    
    //verify player's exchange possibility
    int verif = 0;
    //std::cout << state->players[this->playerColor].resources[0].resourceType << std::endl;
    //std::cout << state->players[this->playerColor].developments[0].developmentType << std::endl;
    
    std::vector<state::Resource>& playerResources = state->players[this->playerColor].resources;

    //std::cout << sizeof(playerResources) << std::endl;

    //std::cout << sizeof(playerResources[7].resourceType) << std::endl;
    //std::cout << playerResources[1].resourceType << std::endl;
    std::cout << "oui12" << std::endl;

    //auto itg = std::find_if(playerResources.begin(), playerResources.end(), [](state::Resource r) {return r.resourceType == state::Grain;});

     for(int j = 1; j < state->players[this->playerColor].resources.size(); j++){
        int verification = 0;

        state::Resource r = state->players[this->playerColor].resources.at(j);

        if ((state->players[this->playerColor].resources.at(j).resourceType == state::Grain) || (state->players[this->playerColor].resources.at(j).resourceType == state::Ore) || (state->players[this->playerColor].resources.at(j).resourceType == state::Wool)){
            std::cout << "oui3" << std::endl;
            if (playerResources[j].number > 0){
                
                verif+=1;
            }
            else{ return false;}
        }
        
        

    } 


    std::cout << "oui2" << std::endl;
    
    //auto itg = std::find_if(playerResources.begin(), playerResources.end(), [](state::Resource& r) {return r.resourceType == state::Grain;});

    

     /* std::cout << "oui3" << std::endl;
    auto ito = std::find_if(playerResources.begin(), playerResources.end(), [&](state::Resource const& r) {return r.resourceType == state::Ore;});
    auto itw = std::find_if(playerResources.begin(), playerResources.end(), [&](state::Resource const& r) {return r.resourceType == state::Wool;});
    std::cout << "oui2" << std::endl;  */
    //if ((itg != playerResources.end()) && (ito != playerResources.end()) && (itw != playerResources.end())){
    if (verif == 3){

    //if (std::find(playerResources.begin(), playerResources.end(), state::Grain)!= playerResources.end() && std::find(playerResources.begin(), playerResources.end(), state::Ore)!= playerResources.end() && std::find(playerResources.begin(), playerResources.end(), state::Wool)!= playerResources.end()){



        //pay the resources
        std::cout << "oui3" << std::endl;
        /* playerResources.erase(playerResources.begin(), itg);
        playerResources.erase(playerResources.begin(), ito);
        playerResources.erase(playerResources.begin(), itw); */

        playerResources[state::Grain].number-=1;
        playerResources[state::Ore].number-=1;
        playerResources[state::Wool].number-=1;


        //... and put them back into the ressources pile
        state->gameCards.resources.push_back(state::Resource(state::Grain));
        state->gameCards.resources.push_back(state::Resource(state::Ore));
        state->gameCards.resources.push_back(state::Resource(state::Wool));


        

        /* std::cout << "oui4" << std::endl;
        //boucle for de secours 
        for (size_t i = 0; i < sizeof(playerResources); i++)
        {
            if ((playerResources[i].resourceType == state::Grain) || (playerResources[i].resourceType == state::Wool) || (playerResources[i].resourceType == state::Ore)){ 
                //operator== need overloading method to work
                std::cout << "oui5" << std::endl;
                playerResources.erase(playerResources.begin()+i); //retire le i-ème élément
            }

        }
        std::cout << "oui6" << std::endl;
        state->gameCards.resources.push_back(state::Resource(state::Grain));
        state->gameCards.resources.push_back(state::Resource(state::Ore));
        state->gameCards.resources.push_back(state::Resource(state::Wool)); */

        

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
        }

        //std::cout << state->players[this->playerColor].resources[0].resourceType << std::endl;
        //std::cout << state->players[this->playerColor].developments[0].developmentType << std::endl;
        
        return true;
        
    }


}



}