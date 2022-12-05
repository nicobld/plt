#include "DrawCardCommand.h"

namespace engine {

DrawCardCommand::DrawCardCommand() {}

bool DrawCardCommand::verify(state::State* state) {
    return true;
}

bool DrawCardCommand::execute(state::State* state) {
    return true;
}

}