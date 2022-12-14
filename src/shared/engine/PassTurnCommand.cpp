#include "PassTurnCommand.h"

namespace engine {

PassTurnCommand::PassTurnCommand(state::PlayerColor actualTurn): actualTurn(actualTurn) {
    commandID = PASS_TURN_CMD;
}

bool PassTurnCommand::verify(state::State* state){
    return true;
}

bool PassTurnCommand::execute(state::State* state) {
    return true;
}

}