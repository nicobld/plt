#include "PlaceThiefCommand.h"
#include <iostream>
#include <bits/stdc++.h>

namespace engine {

PlaceThiefCommand::PlaceThiefCommand() {
    commandID = PLACE_THIEF_CMD;
}

PlaceThiefCommand::PlaceThiefCommand(state::PlayerColor playerColor, state::Position position) : position(position) {
    this->playerColor = playerColor;
    commandID = PLACE_THIEF_CMD;
}

bool PlaceThiefCommand::verify(state::State* state){
    if (state->map.thief.position == position) {
        std::cout << "PlaceThief error : Have to change position of thief" << std::endl;
        return false;
    }

    if (position.x + 7*position.y > 49){
        std::cout << "PlaceThief error : Error tile doesn't exit" << std::endl;
        return false;
    }

    if (state->map.grid[position.x + 7*position.y] == 0 || state->map.grid[position.x + 7*position.y] >= 6) {
        std::cout << "PlaceThief error : Error place thief on a ground tile" << std::endl;
        return false;
    }

    return true;
}

bool PlaceThiefCommand::execute(state::State* state){

    state->map.thief.position = position;

    bool stealCard = false;
    bool isInVect = false;
    std::vector<state::Player*> canStealPlayers;
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
        std::cout << "STATE STEALCARD\n";
        return true;
    }
    std::cout << "No players to steal cards" << std::endl;
    state->gameState = state::NORMAL_STATE;
    return true;
}

bool PlaceThiefCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 4){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            position.x = stoi(tokens[2]);
            position.y = stoi(tokens[3]);
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