#include "PassTurnCommand.h"

namespace engine {

PassTurnCommand::PassTurnCommand() {}

bool PassTurnCommand::verify(state::State* state){
    return true;
}

bool PassTurnCommand::execute(state::State* state) {
    return true;
}

}