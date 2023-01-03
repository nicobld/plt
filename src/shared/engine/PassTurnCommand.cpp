#include "PassTurnCommand.h"
#include <bits/stdc++.h>
#include <iostream>

namespace engine {

PassTurnCommand::PassTurnCommand() {
    commandID = PASS_TURN_CMD;
}

PassTurnCommand::PassTurnCommand(state::PlayerColor actualTurn): actualTurn(actualTurn) {
    commandID = PASS_TURN_CMD;
}

bool PassTurnCommand::verify(state::State* state){
    return true;
}

bool PassTurnCommand::execute(state::State* state) {
    state->turn = (state::PlayerColor) (((int)state->turn + 1) % 4);
    return true;
}

bool PassTurnCommand::unserialize(std::string string){
    return true;
}

}