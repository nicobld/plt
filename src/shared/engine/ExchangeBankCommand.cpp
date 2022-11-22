#include "ExchangeBankCommand.h"

namespace engine {

ExchangeBankCommand::ExchangeBankCommand(state::State* state, state::RessourceType giving, state::RessourceType receiving){
    commandID = EXCHANGE_BANK;
}


bool ExchangeBankCommand::execute(state::State* state) {
    
    return true;
}






}