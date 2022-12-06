#include "Engine.h"
#include <engine.h>
#include <iostream>

using namespace state;

namespace engine {

Engine::Engine(state::State* state) : state(state) {
    std::cout << "Engine launched" << std::endl;
}

void Engine::addCommand(Command* command) {
    commandQueue.push(command);
}

ExchangeRequestCommand* saveExReqCmd;

void Engine::update() {
    for (int i = 0; i < commandQueue.size(); i++){
        if (commandQueue.front()->playerColor == state->turn){
            if (state->gameState == NORMAL_STATE){
                if (commandQueue.front()->commandID == EXCHANGE_RESPONSE_CMD); //ne rien faire
                else if (commandQueue.front()->commandID == EXCHANGE_REQUEST_CMD){
                    saveExReqCmd = static_cast<ExchangeRequestCommand*>(commandQueue.front());
                }
                else if (commandQueue.front()->verify(state)){
                    commandQueue.front()->execute(state);
                }
            } else if (state->gameState == EXCHANGE_REQUEST_STATE){
                if (commandQueue.front()->commandID == EXCHANGE_RESPONSE_CMD){ //seulement accepter les reponses
                    if (commandQueue.front()->verify(state)){
                        commandQueue.front()->execute(state);
                    }
                }
            }
        }
        else 
            std::cout << "Wrong command" << std::endl;
        
        delete commandQueue.front();
        commandQueue.pop();
    }
}

}