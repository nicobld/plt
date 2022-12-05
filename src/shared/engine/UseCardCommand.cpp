#include "UseCardCommand.h"

namespace engine {

UseCardCommand::UseCardCommand() {}

bool UseCardCommand::verify(state::State* state){
    return true;
}

bool UseCardCommand::execute(state::State* state) {
    return true;
}

}