#include "UseCardCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>

namespace engine {

UseCardCommand::UseCardCommand(state::Development dev, state::PlayerColor playerTurn): cardUsed(dev), playerTurn(playerTurn){
    commandID = USE_CARD_CMD;
}

bool UseCardCommand::execute(state::State* state) {

    // ? Vérifier si la carte correspond à un dévelopment
    
        
    //reveal the card used to other players
    //state::Development theCard = state->players

    this->cardUsed.used = true;

    //activation de l'effet:

    //chevalier::
    if (this->cardUsed.developmentType == state::Knight){

        //déplace le voleur:
        state->map.thief.position.x = 2;
        state->map.thief.position.y = 2;
        // state->map.thief.position = state::Position(0,0);//on doit ouvrir une fenêtre de dialogue pour permettre au jooueur de choisir la position
        /*
            void/bool thiefMove(state::Position pos)

            void thiefAction()
        */

        state::PlayerColor playerChosen = state::PlayerBlue;

        auto itr = std::find_if(state->players[playerChosen].resources.begin(), state->players[playerChosen].resources.end(), [&](state::Resource const& r) {return r.resourceType == 0;});

        state->players[this->playerTurn].resources[0].number+=1; //on choisit ressource 0

        state->players[playerChosen].resources.erase(itr);


        //le chevalier reste visible (et conservé parmis les cartes dévelopment du joueur)

        //incrémente le compteur du nombre de chevalier du joueur
        state->players[this->playerTurn].knightNumber += 1;

        //vérifier le nombre de chevaliers

        for (int i = 0; i < state->players.size(); i++)
        {
            if ((state->players[i].knightNumber < state->players[this->playerTurn].knightNumber) && (state->players[i].hasLargestArmy == true)){

                state->players[i].hasLargestArmy = false;
                state->players[this->playerTurn].hasLargestArmy = true;
            }
        }
        

        if(state->players[this->playerTurn].playerColor == playerTurn){
            //state->players[this->playerTurn].ressources
            //std::cout << "yup" << std::endl;
        }

        this->cardUsed.keep = true;
    }

    //monopole::
    else if (this->cardUsed.developmentType == state::Monopoly){

        //désigne une resource (besoin d'une fenêtre (?) pour désigner la resource demandée)
        std::vector<state::ResourceType> listResources;
        for (int i = 0; i < state::Ore; i++)
        {
            listResources.push_back(static_cast<state::ResourceType>(i));
        }
        // std::cout << listResources[0] << std::endl;
        // std::cout << listResources[1] << std::endl;
        // std::cout << listResources[2] << std::endl;
        
        //state::ResourceType resourceRandom = listResources[rand() % listResources.size()]; //on choisit au hasard pour l'instant
        state::ResourceType resourceRandom = state::Ore;
        std::cout << resourceRandom << std::endl;

        //retire la-dite ressource aux autres joueurs, et les ajoutent à l'utilisateur
        for (size_t i = 0; i < state->players.size(); i++)
        {
            //
            std::cout << "here" << std::endl;
            if (state->players[i].playerColor != playerTurn ){
                std::cout << "here" << std::endl;
                //liste des resources d'un joueur (temp)
                std::vector<state::Resource> liste = state->players[i].resources;
                std::vector<state::ResourceType> listeType;

                std::cout << "here" << std::endl;

                // for (size_t j = 0; j < liste.size(); j++)
                // {
                //     /* code */
                //     std::cout << "q" <<std::endl;
                //     listeType[j] = liste[j].resourceType;
                // }
                

                //si un joueur adverse possède la ressource...
                auto itr = std::find_if(state->players[i].resources.begin(), state->players[i].resources.end(), [&resourceRandom](state::Resource r){return r.resourceType == resourceRandom;});


                
                if (itr != state->players[i].resources.end()){

                    //... on lui la retire ...
                    //state->players[i].resources.erase(state->players[i].resources.begin(), std::find(listeType.begin(), listeType.end(), resourceRandom));
                    //ligne précédente est un test également

                    //auto it1 = std::find_if(state->gameCards.resources.begin(), state->gameCards.resources.end()-2, [&](state::Resource r) {return r.resourceType == res1;});
                    state->players[i].resources[resourceRandom].number-=1;
                    //..puis on l'ajoute aux resource de l'utilisateur
                    state->players[this->playerTurn].resources[resourceRandom].number+=1;
                }

                else{
                    std::cout << "le joueur " << state->players[i].playerColor << " ne possède pas cette ressource!" << std::endl;
                }
            }
        }

        this->cardUsed.keep = false;
        this->cardUsed.used = true;



        std::cout << "yup" << std::endl;

        //la carte redevient cachée.

        //on la mélange à la réserve et retire de l'utilisateur.
        
        //buggé
        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);

    }


    //Victory points
    else if (this->cardUsed.developmentType == state::VictoryPointsCard){

        //confère 1 point de victoire
        state->players[this->playerTurn].victoryPoints += 1;

        // hidden et retour à la réserve

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);

        this->cardUsed.keep = false;
        this->cardUsed.used = true;

    }

    //Invention
    else if (this->cardUsed.developmentType == state::Invention){

        //choix de 2 ressources 

        //aléatoire pour le moment
        std::vector<state::ResourceType> listResources;
        for (size_t i = 0; i < state::Ore; i++)
        {
            listResources.push_back(static_cast<state::ResourceType>(i));
        }
        //std::cout << listResources[1] << std::endl;
        
        state::ResourceType res1 = listResources[rand() % listResources.size()];
        state::ResourceType res2 = listResources[rand() % listResources.size()];

        
        std::cout << res1 << std::endl;
        std::cout << res2 << std::endl;
        

        // state::Resource res1 = state::Resource(resourceRandom);
        // state::Resource res2 = state::Resource(resource2Random);
        

        //ajout des ressources pour le joueur

        state->players[this->playerTurn].resources[res1].number+=1;
        state->players[this->playerTurn].resources[res2].number+=1;
        

        //suppression des ressources dans la réserve
        
        auto it1 = std::find_if(state->gameCards.resources.begin(), state->gameCards.resources.end()-2, [&](state::Resource r) {return r.resourceType == res1;});
        auto it2 = std::find_if(state->gameCards.resources.begin(), state->gameCards.resources.end()-2, [&](state::Resource r) {return r.resourceType == res2;});
       
        state->gameCards.resources.erase(it1);
        state->gameCards.resources.erase(it2);
        
        //buggé
        //state->gameCards.resources.erase(std::find(state->gameCards.resources.begin(), state->gameCards.resources.end(), res1));
        //state->gameCards.resources.erase(std::find(state->gameCards.resources.begin(), state->gameCards.resources.end(), res2));

        //après effet, on re cache la carte Invention puis on la remet dans la réserve
        this->cardUsed.keep = false;
        this->cardUsed.used = true;

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);
    }


    //Construction de route
    else if (this->cardUsed.developmentType == state::RoadConstruction){

        std::cout << "RoadConstruction" << std::endl;

        //renvoie à l'état 'construction de route'



        //vérifier longueur de route

        this->cardUsed.keep = false;
        this->cardUsed.used = true;

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);
    }



/*
    note: une seule carte dévelopment peut être jouée par tour
*/
    
    return true;
}


// bool verify(state::State*){
//     return true;
// }

}