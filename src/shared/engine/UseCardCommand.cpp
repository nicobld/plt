#include "UseCardCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>

namespace engine {

UseCardCommand::UseCardCommand(state::Development dev, state::PlayerColor playerTurn): cardUsed(dev), playerTurn(playerTurn){

}

bool UseCardCommand::execute(state::State* state) {

    // ? Vérifier si la carte correspond à un dévelopment
    
        
    //reveal the card used to other players
    //state::Development theCard = state->players

    this->cardUsed.hidden = false;

    //activation de l'effet:

    //chevalier::
    if (this->cardUsed.developmentType == state::Knight){

        //déplace le voleur:
        state->map.thief.position = state::Position(0,0);//on doit ouvrir une fenêtre de dialogue pour permettre au jooueur de choisir la position
        /*
            void/bool thiefMove(state::Position pos)

            void thiefAction()
        */


        //le chevalier reste visible (et conservé parmis les cartes dévelopment du joueur)

        //incrémente le compteur du nombre de chevalier du joueur
        state->players[this->playerTurn].knightNumber += 1;

        //vérifier le nombre de chevaliers

        for (size_t i = 0; i < sizeof(state->players); i++)
        {
            if ((state->players[i].knightNumber < state->players[this->playerTurn].knightNumber) && (state->players[i].hasLargestArmy == true)){

                state->players[i].hasLargestArmy = false;
                state->players[this->playerTurn].hasLargestArmy = true;
            }
        }
        

        if(state->players[this->playerTurn].playerColor == playerTurn){
            //state->players[this->playerTurn].ressources
            std::cout << "yup" << std::endl;
        }
    }

    //monopole::
    else if (this->cardUsed.developmentType == state::Monopoly){

        //désigne une resource (besoin d'une fenêtre (?) pour désigner la resource demandée)
        std::vector<state::ResourceType> listResources;
        for (size_t i = 0; i < state::Ore; i++)
        {
            listResources.push_back(static_cast<state::ResourceType>(i));
        }
        
        state::ResourceType resourceRandom = listResources[rand() % sizeof(listResources)]; //on choisit au hasard pour l'instant

        //retire la-dite ressource aux autres joueurs, et les ajoutent à l'utilisateur
        for (size_t i = 0; i < sizeof(state->players); i++)
        {
            //
            if (state->players[i].playerColor != playerTurn ){

                //liste des resources d'un joueur (temp)
                std::vector<state::Resource> liste = state->players[i].resources;
                std::vector<state::ResourceType> listeType;

                for (size_t i = 0; i < sizeof(liste); i++)
                {
                    /* code */
                    listeType[i] = liste[i].resourceType;
                }
                

                //si un joueur adverse possède la ressource...
                if (std::find(listeType.begin(), listeType.end(), resourceRandom) != listeType.end()){

                    //... on lui la retire ...
                    //state->players[i].resources.erase(state->players[i].resources.begin(), std::find(listeType.begin(), listeType.end(), resourceRandom));
                    //ligne précédente est un test également

                    //..puis on l'ajoute aux resource de l'utilisateur
                    state->players[this->playerTurn].resources.push_back(resourceRandom);
                }

                else{
                    std::cout << "le joueur " << state->players[i].playerColor << " ne possède pas cette ressource!" << std::endl;
                }
            }
        }


        std::cout << "yup" << std::endl;

        //la carte redevient cachée.
        this->cardUsed.hidden = true;

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
        this->cardUsed.hidden = true;

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);

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
        
        state::ResourceType resourceRandom = listResources[rand() % sizeof(listResources)];
        state::ResourceType resource2Random = listResources[rand() % sizeof(listResources)];

        state::Resource res1 = state::Resource(resourceRandom);
        state::Resource res2 = state::Resource(resource2Random);
        //

        //ajout des ressources pour le joueur
        state->players[this->playerTurn].resources.push_back(res1);
        state->players[this->playerTurn].resources.push_back(res2);

        //suppression des ressources dans la réserve
        
        //buggé
        //state->gameCards.resources.erase(std::find(state->gameCards.resources.begin(), state->gameCards.resources.end(), res1));
        //state->gameCards.resources.erase(std::find(state->gameCards.resources.begin(), state->gameCards.resources.end(), res2));

        //après effet, on re cache la carte Invention puis on la remet dans la réserve
        this->cardUsed.hidden = true;

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);
    }


    //Construction de route
    else if (this->cardUsed.developmentType == state::RoadConstruction){

        //^placeRoadCommand ?

        /*
            void placeRoad(state::PlayerColor playerColor, std::array<Position, 2> position)
        */


       /*
       if (state->players[playerColor].roads.size() == 0) {
        std::cout << "Player has no roads to place" << std::endl;
        return false;
    }

    //verifie pas déjà une route sur la map
    for (state::Road r : state->map.roads){
        if (r.position == position){
            return false;
        }
    }

    bool foundRoad = false;
    for (Road r : state->map.roads){
        if (r.playerColor == playerColor){
            if (isNeighbor(position[0], r.position[0]) && isNeighbor(position[0], r.position[1]) && isNeighbor(position[1], r.position[0]) && isNeighbor(position[1], r.position[1])){
                foundRoad = true;
            }
        }
    }

    if (!foundRoad) return false;

    //place la route et retire la route au joueur
    state->map.roads.push_back(Road(playerColor, position));
    state->players[playerColor].roads.pop_back();
    return true;
       
       
       */


        //vérifier longueur de route


        this->cardUsed.hidden = true;

        //state->players[this->playerTurn].developments.erase(std::find(state->players[this->playerTurn].developments.begin(), state->players[this->playerTurn].developments.end(), cardUsed));

        state->gameCards.developments.push_back(cardUsed);
    }



/*
    note: une seule carte dévelopment peut être jouée par tour
*/
    
    return true;
}

}