#include "ThrowDiceCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
//#include "../state/Position.h"

namespace engine {

ThrowDiceCommand::ThrowDiceCommand(state::PlayerColor playerTurn): playerTurn(playerTurn){

}

bool ThrowDiceCommand::execute(state::State* state) {

    if (state->turn == playerTurn){

        //lancer de dés
        int dice1 = rand() % 6 +1;
        int dice2 = rand() % 6 +1;
        result = dice1 + dice2;

        result = 10;
        std::cout << "resultat du lancer de dés : " << result << std::endl;

        //display the result
        /*
            void display_dice(int result1, int result2);
        */

        // std::cout << "\n" << state->map.thief.position.x << std::endl;
        // std::cout << state->map.thief.position.y << std::endl;

         //si 7:

        if (result == 7){

            //move the thief then steal a resource
            //state->map.thief.position.x = setChoiceX(x);
            //state->map.thief.position.y = setChoiceY(y);
            state->map.thief.position.x = 2;
            state->map.thief.position.y = 2;

            //choose a player whom to steal from
            state::PlayerColor playerChosen = state::PlayerBlue;
            //playerChosen = choosePlayer(playerColor);

            // std::cout << "nouvelle position (x) du voleur" << state->map.thief.position.x << std::endl;
            // std::cout << "nouvelle position (y) du voleur" <<state->map.thief.position.y << "\n" << std::endl;

            //display window to steal resource
            //window.displayTheft();
            //resource = 

            //state->players[playerChosen].resources.erase()
            
            //std::cout << state->players[PlayerChosen].resources.end() << std::endl;

            auto itr = std::find_if(state->players[playerChosen].resources.begin(), state->players[playerChosen].resources.end(), [&](state::Resource const& r) {return r.resourceType == 0;});

            state->players[this->playerTurn].resources[0].number+=1;

            // std::cout << "type de la ressource volée:" << state->players[this->playerTurn].resources[0].resourceType << "\n" <<std::endl;

            state->players[playerChosen].resources.erase(itr);

            //state->players[playerChosen].resources.begin()

            //std::cout << state->players[PlayerChosen].resources.end() << std::endl;


            //std::cout << "faire une fonction" << std::endl;
        }

        //receive resources according to die score

        // for (size_t i = 0; i < sizeof(state->map.tokengrid); i++)
        int i=0;

        while(i!=49)
        {
            int grid_position = state->map.grid[i]; //on sauvegarde la valeur (dés) de la case
            
            //on test tous les batiments sur le plateau
            for (size_t j = 0; j < state->map.buildings.size(); j++)
            {
                //test si le batiment appartient au joueur, et s'il est près d'une case de la valeur du résultat de ddés
                
                // std::cout << state->map.buildings[j].position[1].x << "\n" << std::endl ;

                //parmi tous les joueurs
                //for (size_t l = 0; l < sizeof(state->map.players); l++)
                //{
                    //pour toute tile entourant un batiment
                    for (int k = 0; k < 3; k++)
                    {             
                        // std::cout << << std::endl;
                        
                        if ((state->map.buildings[j].position[k].x+1+7*state->map.buildings[j].position[k].y == i) 
                         && (state->map.tokengrid[i] == result))
                         {
                            
                            // std::cout << "position détectée: " << grid_position << std::endl;
                            // std::cout << "position détectée2 : " << state->map.tokengrid[i] << std::endl;
                            std::cout << "itération : "<< i << std::endl;

                            // std::cout << "x: " << state->map.buildings[j].position[k].x << std::endl;
                            // std::cout << "y: " << state->map.buildings[j].position[k].y << std::endl;

                            if (!(state->map.thief.position.x == state->map.buildings[j].position[k].x && state->map.thief.position.y == state->map.buildings[j].position[k].y)){
                                
                                
                                std::cout << "on est la :: " << state->map.buildings[j].position[k].x << " & " <<  state->map.buildings[j].position[k].y << std::endl;

                                state::PlayerColor actualPlayer = state->map.buildings[j].playerColor;

                                // std::cout << "couleur: " << state->map.buildings[j].playerColor << std::endl;
                                std::cout << "type de ressources: " << state->players[actualPlayer].resources[grid_position].resourceType << std::endl;
                                //state::Resource r = Resource(grid_position); 
                                // std::cout << "nouveau chiffre de resource : " << state->players[actualPlayer].resources[grid_position].number << std::endl;
                                // std::cout << state->map.grid[i] << std::endl;
                                
                                
                                state->players[actualPlayer].resources[grid_position].number+=1;

                                std::cout << "nouveau chiffre de resource : " << state->players[actualPlayer].resources[grid_position].number << std::endl;

                                //pour trouver/piocher la ressource dans la reserve
                                std::cout << state->gameCards.resources.size() << std::endl;
                                auto itg = std::find_if(state->gameCards.resources.begin(), state->gameCards.resources.end()-1, [&state, &actualPlayer, &grid_position](state::Resource r) {return r.resourceType == state->players[actualPlayer].resources[grid_position].resourceType;});
                                //std::cout << itg << std::endl;

                                
                                state->gameCards.resources.erase(itg);
                                std::cout << state->gameCards.resources.size() << std::endl;

                                // continue;

                                
                            }

                            else{
                                std::cout <<"position du voleur: " << state->map.thief.position.x << "&" << state->map.thief.position.y << std::endl;
                                std::cout << "position actuelle: "<< state->map.buildings[j].position[k].x << "&"<< state->map.buildings[j].position[k].y <<std::endl;
                                std::cout <<"donc non retour de ressources" << std::endl;
                            }
                        }
                    }
            }
            

            // std::cout << i << std::endl;
            i++;  
        }

        return true;
    }

}


bool verify(state::State*){
    return true;
}
}