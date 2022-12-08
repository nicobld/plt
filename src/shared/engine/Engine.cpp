#include "Engine.h"
#include <engine.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace state;

namespace engine {

Engine::Engine(state::State* state) : state(state) {
    std::cout << "Engine launched" << std::endl;
}

void Engine::addCommand(Command* command) {
    commandQueue.push(command);
}

void Engine::addSerializedCommand(std::string string){
    std::stringstream stream(string);

    std::string commandType;

    std::getline(stream, commandType, '-');

    if (commandType == "4"){
        PlaceBuildingCommand* placeBuildingCommand = new PlaceBuildingCommand();
        placeBuildingCommand->unserialize(string);
        addCommand(placeBuildingCommand);
    }
    else if (commandType == "5"){
        PlaceRoadCommand* placeRoadCommand = new PlaceRoadCommand();
        placeRoadCommand->unserialize(string);
        addCommand(placeRoadCommand);
    }
    else if (commandType == "6"){
        ExchangeBankCommand* exchangeBankCommand = new ExchangeBankCommand();
        exchangeBankCommand->unserialize(string);
        addCommand(exchangeBankCommand);
    }
    else {
        std::cout << "Bad command type\n";  
    }
}

ExchangeRequestCommand* saveExReqCmd;

void Engine::update() {

    while(commandQueue.size() != 0) {

        if (state->gameState == NORMAL_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID != EXCHANGE_RESPONSE_CMD) {

                if (commandQueue.front()->verify(state)){

                    if (commandQueue.front()->commandID == EXCHANGE_REQUEST_CMD){ //passer en exchange state
                        saveExReqCmd = static_cast<ExchangeRequestCommand*>(commandQueue.front());
                        state->gameState = EXCHANGE_REQUEST_STATE;
                    }

                    commandQueue.front()->execute(state);
                
                } else
                    std::cout << "Wrong command" << std::endl;

                }
            } else {
                std::cout << "Not your turn player " << commandQueue.front()->playerColor << std::endl;
            }
        } 
        
        else if (state->gameState == EXCHANGE_REQUEST_STATE){
            if (commandQueue.front()->commandID == EXCHANGE_RESPONSE_CMD){ //seulement accepter les reponses
                if (commandQueue.front()->verify(state)){
                    if(commandQueue.front()->execute(state) == true){
                        state->gameState = NORMAL_STATE;
                        for (int i = 0; i < state->players.size(); i++){
                            if (state->players[i].playerColor != saveExReqCmd->playerColor){
                                state->players[i].playerState = STAND_BY;
                            }
                        }
                    }
                } else {
                    std::cout << "Wrong command" << std::endl;
                }
            }
        }


        delete commandQueue.front();
        commandQueue.pop();
        std::cout << commandQueue.size() << std::endl;
    }
}

}