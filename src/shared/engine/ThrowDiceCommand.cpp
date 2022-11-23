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
        int result = dice1 + dice2;

        //display the result
        /*
            void display_dice(int result1, int result2);
        */

         //si 7:

        if (result == 7){

            //move the thief then steal a resource
            



            std::cout << "faire une fonction" << std::endl;
        }

        //receive resources according to die score

        for (size_t i = 0; i < sizeof(state->map.tokengrid); i++)
        {
            int grid_position = state->map.grid[i]; //on sauvegarde la valeur (dés) de la case
            //on test tous les batiments sur le plateau
            for (size_t j = 0; j < sizeof(state->map.buildings); j++)
            {
                //test si le batiment appartient au joueur, et s'il est près d'une case de la valeur du résultat de ddés
                

                //parmi tous les joueurs
                //for (size_t l = 0; l < sizeof(state->map.players); l++)
                //{
                    //pour toute tile entourant un batiment
                    for (size_t k = 0; k < 3; k++)
                    {             
                        if ((state->map.buildings[j].position[k].x+1+7*state->map.buildings[j].position[k].y == i) && (state->map.tokengrid[i] == result)){
                            

                            if (!(state->map.thief.position.x == state->map.buildings[j].position[k].x) && !(state->map.thief.position.y == state->map.buildings[j].position[k].y)){
                                state::PlayerColor actualPlayer = state->map.buildings[j].playerColor;
                                state::Resource r = Resource(grid_position); 

                                state->players[actualPlayer].resources.push_back(r);

                                state->gameCards.resources.erase(state->gameCards.resources.begin() + std::find(state->gameCards.resources.begin(), state->gameCards.resources.end(), r));
                            }
                        }
                    }
                }  
            }

        return true;
    }

}
}