#include "StealCardCommand.h"
#include <iostream>
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

namespace engine {

StealCardCommand::StealCardCommand() {
    commandID = STEAL_CARD_CMD;
}

StealCardCommand::StealCardCommand(state::PlayerColor playerColor, state::PlayerColor playerSteal) : playerSteal(playerSteal){
    this->playerColor = playerColor;
    commandID = STEAL_CARD_CMD;
}

bool StealCardCommand::verify(state::State* state){
    bool canSteal = false;
    for (state::Building b : state->map.buildings){ //check you can steal a player with the thief on his buildings
        if (b.playerColor == playerSteal){
            if (b.position[0] == state->map.thief.position || 
                b.position[1] == state->map.thief.position ||
                b.position[2] == state->map.thief.position)
            {
                canSteal = true;
                break;
            }
        }
    }
    if (!canSteal) {
        return false;
    }
    int r;
    if (state->players[playerSteal].developments.size() == 0){
        for (r = 0; r < 5; r++){
            if (state->players[playerSteal].resources[r].number > 0){
                break;
            }
        }
    }
    if (r == 5){
        std::cout << "Player has nothing to steal" << std::endl;
        return false;
    }

    for (state::Building b : state->map.buildings){ //check you are stealing a player with the thief on his buildings
        if (b.playerColor == playerSteal){
            if (b.position[0] == state->map.thief.position || 
                b.position[1] == state->map.thief.position ||
                b.position[2] == state->map.thief.position){
                
                return true;
            }
        }
    }

    return false;
}


bool StealCardCommand::execute(state::State* state){

    int randCardType;
    int randCard;

    while(1) {
        randCardType = rand()%2;

        if (randCardType == 0){ //steal dev card
            if (state->players[playerSteal].developments.size() != 0){
                randCard = rand() % state->players[playerSteal].developments.size();
                state->players[playerColor].developments.push_back(state->players[playerSteal].developments[randCard]);
                state->players[playerSteal].developments.erase(state->players[playerSteal].developments.begin() + randCard);
                break;
            }
        } 
        
        else { //steal resource
            int r;
            for (r = 0; r < 5; r++){
                if (state->players[playerSteal].resources[r].number > 0){
                    break;
                }
            }
            if (r < 5) {
                while (state->players[playerSteal].resources[(randCard = rand() % 5)].number > 0);
                state->players[playerSteal].resources[randCard].number--;
                state->players[playerColor].resources[randCard].number++;
                break;
            }
        }
    }

    std::cout << "Stole a card from " << state->players[(int)playerSteal].name << std::endl;
    return true;
}


bool StealCardCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 3){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            playerSteal = (state::PlayerColor) stoi(tokens[2]);
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