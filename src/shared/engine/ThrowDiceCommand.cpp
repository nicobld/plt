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
}

ThrowDiceCommand::ThrowDiceCommand(state::PlayerColor playerColor){
    commandID = THROW_DICE_CMD;
    this->playerColor = playerColor;
    playerSteal = playerColor;
}

bool ThrowDiceCommand::execute(state::State* state) {
    int dice1;
    int dice2;
    std::vector<state::Player*> canStealPlayers;

    if (state->turn == playerColor){
        //std::cout << "throwDice" << std::endl;

        if (state->gameState == state::NORMAL_STATE){
            //lancer de dés
            dice1 = rand() % 6 + 1;
            dice2 = rand() % 6 + 1;
            result = dice1 + dice2;

            //result = 7;
            std::cout << "resultat du lancer de dés : " << result << std::endl;
        }

        if (result == 7 || state->gameState == state::PLACE_THIEF_STATE || state->gameState == state::STEAL_CARD_STATE){
            bool stealCard = false;
            bool isInVect = false;
            //TODO DEFAUSSER PLUS DE 7 CARTES
            switch (state->gameState) {
                case state::NORMAL_STATE:
                    state::PlayerColor color;
                    for (int i = 0; i < 4; i ++){
                        color = (state::PlayerColor) i;
                        removeCards(state, color);
                    }
                    std::cout << "Please place thief" << std::endl;
                    state->gameState = state::PLACE_THIEF_STATE;
                    return true;
                case state::PLACE_THIEF_STATE:

                    for (state::Building b : state->map.buildings){ //check you can steal a player with the thief on his buildings
                        if (b.playerColor != playerColor){
                            for (state::Player* p : canStealPlayers){
                                if (b.playerColor == p->playerColor){
                                    isInVect = true;
                                }
                            }
                            if (!isInVect){
                                if (b.position[0] == state->map.thief.position || 
                                    b.position[1] == state->map.thief.position ||
                                    b.position[2] == state->map.thief.position){
                                    
                                    int r;
                                    if (state->players[b.playerColor].developments.size() == 0){
                                        for (r = 0; r < 5; r++){
                                            if (state->players[b.playerColor].resources[r].number > 0){
                                                canStealPlayers.push_back(&(state->players[b.playerColor]));
                                                stealCard = true;
                                                break;
                                            }
                                        }
                                    } else {
                                        canStealPlayers.push_back(&(state->players[b.playerColor]));
                                        stealCard = true;
                                    }
                                    
                                }
                            }
                        }
                    }
                    if (stealCard){
                        std::cout << "Please steal a card from : ";
                        for (state::Player* p : canStealPlayers){
                            std::cout << p->name << ", ";
                        } std::cout << std::endl;
                        state->gameState = state::STEAL_CARD_STATE;
                        return true;
                    }
                    std::cout << "No players to steal cards" << std::endl;
                    state->gameState = state::NORMAL_STATE;
                    return true;
                    break;
                case state::STEAL_CARD_STATE:
                    state->gameState = state::NORMAL_STATE;
                    break;
            }

            //result = 7;

            //TODO appeler thief menu

            state::ResourceType randRes;
            while (state->players[playerSteal].resources[randRes = ((state::ResourceType) (rand() % 5))].number == 0){
                state->players[playerSteal].resources[randRes].number --;
                state->players[playerColor].resources[randRes].number ++;
            }
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