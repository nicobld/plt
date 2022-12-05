#include "ThrowDiceCommand.h"

namespace engine {

ThrowDiceCommand::ThrowDiceCommand() {}

bool ThrowDiceCommand::verify(state::State* state){
    return true;
}

bool ThrowDiceCommand::execute(state::State* state) {
    return true;
}

}