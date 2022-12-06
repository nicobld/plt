#include "Engine.h"
#include <engine.h>
#include <iostream>

using namespace state;

namespace engine {

Engine::Engine(state::State* state) : state(state) {
    std::cout << "Engine launched" << std::endl;
    engineState = NORMAL_STATE;
}

void Engine::addCommand(Command* command) {
    commandQueue.push(command);
}

void Engine::update() {
    for (int i = 0; i < commandQueue.size(); i++){
        if (commandQueue.front()->playerColor == state->turn){
            if (commandQueue.front()->verify(state)){
                commandQueue.front()->execute(state);
                std::cout << "Good command" << std::endl;
            }
        }
        else 
            std::cout << "Wrong command" << std::endl;
        
        delete commandQueue.front();
        commandQueue.pop();
    }
}

}