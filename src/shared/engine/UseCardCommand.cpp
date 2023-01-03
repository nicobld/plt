#include "UseCardCommand.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>

static state::DevelopmentType stringToDevType(std::string string){
    if (string == "knight")
        return state::Knight;
    else if (string == "monopoly")
        return state::Monopoly;
    else if (string == "roadconstruction")
        return state::RoadConstruction;
    else if (string == "invention")
        return state::Invention;
    else
        return (state::DevelopmentType)-1;
}

namespace engine {

UseCardCommand::UseCardCommand(){
    commandID = USE_CARD_CMD;
}

UseCardCommand::UseCardCommand(state::PlayerColor playerColor, state::DevelopmentType dev): developmentType(dev){
    commandID = USE_CARD_CMD;
    this->playerColor = playerColor;
}

bool UseCardCommand::execute(state::State* state) {

    // ? Vérifier si la carte correspond à un dévelopment


    for (int d = 0; d < state->players[playerColor].developments.size(); d++){
        if (state->players[playerColor].developments[d].developmentType == developmentType){
            state->players[playerColor].developments.erase(state->players[playerColor].developments.begin() + d);
            break;
        }
    }

    //activation de l'effet:

    if (developmentType == state::Knight){
        state->players[playerColor].knightNumber ++;
        state->gameState = state::PLACE_THIEF_STATE;
        std::cout << "Used card Knight, please place thief" << std::endl;
    }

    else if (developmentType == state::Monopoly){
        state->gameState = state::MONOPOLY_STATE;
        std::cout << "Used card Monopoly, which resource do you want to steal?" << std::endl;
    }


    //Invention
    else if (developmentType == state::Invention){
        state->gameState = state::INVENTION_STATE;
        std::cout << "Used card Invention, select 2 resources to take" << std::endl;
    }


    //Construction de route
    else if (developmentType == state::RoadConstruction){
        int roadsToPlace = 2;
        if (state->map.roads.size() > 70){
            roadsToPlace = state->map.roads.size() - 70;
        }
        for (int i = 0; i < roadsToPlace; i++){ //ajouter les resources pour pouvoir cosnstruire
            state->players[playerColor].resources[state::Lumber].number++;
            state->players[playerColor].resources[state::Brick].number++;
        }
        std::cout << "Used RoadConstruction, please place " << roadsToPlace << " roads" << std::endl;
        state->gameState = state::ROAD_CONSTRUCTION_STATE;
    }
    
    return true;
}


bool UseCardCommand::verify(state::State* state){

    for (state::Player p : state->players){
        for (state::Development d : p.developments){
            if (d.developmentType == developmentType){
                return true;
            }
        }
    }
    return false;
}

bool UseCardCommand::unserialize(std::string string){
    std::stringstream stream(string);

    std::string token;

    std::vector<std::string> tokens;

    while (std::getline(stream, token, '-')){
        tokens.push_back(token);
    }

    try {
        if (tokens.size() == 3){
            playerColor = (state::PlayerColor) stoi(tokens[1]);
            if ((developmentType = stringToDevType(tokens[2])) == -1){
                std::cout << "Wrong development type" << std::endl;
                return false;
            }

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