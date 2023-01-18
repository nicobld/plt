#include "ThrowDiceCommand.h"
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>

static std::string printResource(state::ResourceType res){
    switch(res){
        case 0:
            return "Wool";
        case 1:
            return "Lumber";
        case 2:
            return "Brick";
        case 3:
            return "Grain";
        case 4:
            return "Ore";
        default:
            return "Nothing";
    }
}

int resourceSum(state::Player* player){
    int sum = 0;
    for (int i = 0; i < 5; i++){
        sum += player->resources[i].number;
    }
    return sum;
}

static void removeCards(state::State* state, state::PlayerColor color){
    state::Player* p = &(state->players[(int)color]);
    int resTot;
    if ((resTot = resourceSum(p)) > 7){
        resTot /= 2;
        int r;
        while (resTot > 0){
            r = rand() % 5;
            if (p->resources[r].number > 0){
                p->resources[r].number--;
                state->gameCards.resources[r].number++;
                resTot--;
            }
        }
    }
}

namespace engine {

ThrowDiceCommand::ThrowDiceCommand() {
    commandID = THROW_DICE_CMD;
    dice1 = 0;
    dice2 = 0;
}

ThrowDiceCommand::ThrowDiceCommand(state::PlayerColor playerColor){
    commandID = THROW_DICE_CMD;
    this->playerColor = playerColor;
    playerSteal = playerColor;
}

bool ThrowDiceCommand::execute(state::State* state) {
    std::vector<state::Player*> canStealPlayers;

    if (state->turn == playerColor){
        //std::cout << "throwDice" << std::endl;

        if (state->gameState == state::THROW_DICE_STATE){
            //lancer de dés
            dice1 = rand() % 6 + 1;
            dice2 = rand() % 6 + 1;
            result = dice1 + dice2;

            std::cout << "resultat du lancer de dés : " << result << std::endl;
        }

        if (result == 7 /*|| state->gameState == state::PLACE_THIEF_STATE || state->gameState == state::STEAL_CARD_STATE*/){

            state::PlayerColor color;
            for (int i = 0; i < 4; i ++){
                color = (state::PlayerColor) i;
                removeCards(state, color);
            }
            std::cout << "Please place thief" << std::endl;
            state->gameState = state::PLACE_THIEF_STATE;
            return true;
        }
        int i;

        for (i = 0; i < 49; i++ ){
            int grid_position = state->map.grid[i];

            if (grid_position >= 1 && grid_position <= 5){
                
                for (state::Building b : state->map.buildings){
                    //pour toute tile entourant un batiment
                    for (int k = 0; k < 3; k++){ 

                        if ((b.position[k].x + 7*b.position[k].y == i) && (state->map.tokengrid[i] == result)){

                            if (!(state->map.thief.position == b.position[k])){

                                state::PlayerColor actualPlayer = b.playerColor;

                                if (state->gameCards.resources[grid_position - 1].number == 0){ //no resources left in bank
                                    std::cout << "Not enough resources in bank" << std::endl;
                                    continue;
                                }
                                std::cout << "Player color : " << actualPlayer << " wins resource number " <<  printResource((state::ResourceType)(grid_position - 1)) << std::endl;
                                if (b.buildingType == state::City){
                                    state->gameCards.resources[grid_position - 1].number --;
                                    state->players[actualPlayer].resources[grid_position - 1].number ++;
                                }
                                state->gameCards.resources[grid_position - 1].number --;
                                state->players[actualPlayer].resources[grid_position - 1].number ++;
                            }
                        }
                    }
                }
            }

        }
        
        return true;
    }

}


bool ThrowDiceCommand::verify(state::State*){
    return true;
}

bool ThrowDiceCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 2){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
        } else {
            std::cout << "Invalid number of arguments\n";
            return false;
        }
    }
    catch (const std::invalid_argument& ia) {
	    std::cerr << "Invalid argument: " << ia.what() << '\n';
        return false;
    }

    return true;
}

}