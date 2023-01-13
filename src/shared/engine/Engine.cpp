#include "Engine.h"
#include <engine.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace state;

// const Position neighbors[2][6] = {
//     {Position(+1,  0), Position(0, -1), Position(-1, -1), Position(-1,  0), Position(-1, +1), Position(0, +1)},
//     {Position(+1,  0), Position(1, -1), Position(0, -1), Position(-1,  0), Position(0, +1), Position(1, +1)}
// };

// const struct neighborsIndices {
//     const int x[12] = {1, 0, -1, -1, -1, 0, 1, 1, 0, -1, 0, 1}; //les 6 premiers si le tile en y est pair
//     const int y[12] = {0, -1, -1? 0, 1, 1, 0, -1, -1, 0, 1, 1};
// } neightborIndices; 


// static bool equalArrayPos(std::array<Position, 2> pos1, std::array<Position, 2> pos2){
//     return (pos1[0] == pos2[0] && pos1[1] == pos2[1]) || (pos1[0] == pos2[1] && pos1[1] == pos2[0]);
// }

// /*
// * return true if there is a road on the map at position pos
// */
// static bool hasRoad(state::State* state, std::array<Position, 2> pos){
//     for (Road road : state->map.roads){
//         if (equalArrayPos(road.position, pos))
//             return true;
//     return false;
// }

// static int countRoadsSpaces(state::State* state){
//     int roads = 0;
//     for (int x = 1; x < 6; x++){
//         for (int y = 1; y < 6; y++){
//             for (int k = 0; k < 6; k++){
//                 if (hasRoad(state::State*, {Position(x, y), Position(x + neightborIndices.x[k + (y%2)*7], y + neightborIndices.y[k + (y%2)*7])})){
//                     roads++; 
//                 }
//             }
//         }
//     }
// }

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
    if (1 == 0){
    }
    else if (commandType == "request"){ 
        ExchangeRequestCommand* exchangeRequestCommand = new ExchangeRequestCommand();
        if (exchangeRequestCommand->unserialize(string))
            addCommand(exchangeRequestCommand);
    }
    else if (commandType == "response"){
        ExchangeResponseCommand* exchangeResponseCommand = new ExchangeResponseCommand();
        if (exchangeResponseCommand->unserialize(string))
            addCommand(exchangeResponseCommand);
    }
    else if (commandType == "usecard"){ 
        UseCardCommand* useCardCommand = new UseCardCommand();
        if (useCardCommand->unserialize(string))
            addCommand(useCardCommand);
    }
    else if (commandType == "monopoly"){ 
        MonopolyCommand* monopolyCommand = new MonopolyCommand();
        if (monopolyCommand->unserialize(string))
            addCommand(monopolyCommand);
    }
    else if (commandType == "passturn"){ 
        PassTurnCommand* passTurnCommand = new PassTurnCommand();
        if (passTurnCommand->unserialize(string))
            addCommand(passTurnCommand);
    }
    else if (commandType == "placebuilding"){ 
        PlaceBuildingCommand* placeBuildingCommand = new PlaceBuildingCommand();
        if (placeBuildingCommand->unserialize(string))
            addCommand(placeBuildingCommand);
    }
    else if (commandType == "placeroad"){
        PlaceRoadCommand* placeRoadCommand = new PlaceRoadCommand();
        if (placeRoadCommand->unserialize(string))
            addCommand(placeRoadCommand);
    }
    else if (commandType == "exchangebank"){
        ExchangeBankCommand* exchangeBankCommand = new ExchangeBankCommand();
        if (exchangeBankCommand->unserialize(string))
            addCommand(exchangeBankCommand);
    }
    else if (commandType == "throwdice"){
        ThrowDiceCommand* throwDiceCommand = new ThrowDiceCommand();
        if (throwDiceCommand->unserialize(string))
            addCommand(throwDiceCommand);
    }
    else if (commandType == "stealcard"){
        StealCardCommand* stealCardCommand = new StealCardCommand();
        if (stealCardCommand->unserialize(string))
            addCommand(stealCardCommand);
    }
    else if (commandType == "placethief"){
        PlaceThiefCommand* placeThiefCommand = new PlaceThiefCommand();
        if (placeThiefCommand->unserialize(string))
            addCommand(placeThiefCommand);
    }
    else if (commandType == "drawcard"){
        DrawCardCommand* drawCardCommand = new DrawCardCommand();
        if (drawCardCommand->unserialize(string))
            addCommand(drawCardCommand);
    }
    else if (commandType == "invention"){
        InventionCommand* inventionCommand = new InventionCommand();
        if (inventionCommand->unserialize(string))
            addCommand(inventionCommand);
    }
    else {
        std::cout << "Bad command type\n";
    }
}

ExchangeRequestCommand* saveExReqCmd = new ExchangeRequestCommand();
ThrowDiceCommand* saveThrDiceCmd = new ThrowDiceCommand();
CommandID saveCmd;
int roadConstrutionNum = 2;
int buildRoads = 0;

void Engine::update() {

    while(commandQueue.size() != 0) {
        std::cout << "ENGINE : New command : " << commandQueue.front()->commandID << std::endl;
        std::cout << "ENGINE : gameState : " << state->gameState << std::endl;
        if (state->gameState == NORMAL_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID != EXCHANGE_RESPONSE_CMD &&
                    commandQueue.front()->commandID != PLACE_THIEF_CMD &&
                    commandQueue.front()->commandID != STEAL_CARD_CMD &&
                    commandQueue.front()->commandID != MONOPOLY_CMD &&
                    commandQueue.front()->commandID != STEAL_CARD_CMD) {
                    if (commandQueue.front()->verify(state)){

                        if (commandQueue.front()->commandID == EXCHANGE_REQUEST_CMD){ //passer en exchange state
                            saveCmd = EXCHANGE_REQUEST_CMD;
                            *saveExReqCmd = *(static_cast<ExchangeRequestCommand*>(commandQueue.front()));
                            state->gameState = EXCHANGE_REQUEST_STATE;

                        }
                        
                        else if (commandQueue.front()->commandID == THROW_DICE_CMD){
                            saveCmd = THROW_DICE_CMD;
                            *saveThrDiceCmd = *(static_cast<ThrowDiceCommand*>(commandQueue.front()));
                        }
                        
                        else if (commandQueue.front()->commandID == USE_CARD_CMD){
                            saveCmd = USE_CARD_CMD;
                            buildRoads = 0;
                            if (state->map.roads.size() > 70){ //set le nombres de routes a créé au cas où ya plus de place sur la map
                                roadConstrutionNum = state->map.roads.size() - 70;
                            }
                        }
                        commandQueue.front()->execute(state);
                    } else {
                        std::cout << "Command failed" << std::endl;
                    }
                } else {
                    std::cout << "Cannot execute command " << commandQueue.front()->commandID << " in this state" << std::endl;
                }
            } else {
                std::cout << "Not your turn player" << commandQueue.front()->playerColor << std::endl;
            }
        } 
        
        else if (state->gameState == EXCHANGE_REQUEST_STATE){
            if (commandQueue.front()->commandID == EXCHANGE_RESPONSE_CMD && commandQueue.front()->playerColor != state->turn){ //seulement accepter les reponses
                ((ExchangeResponseCommand*)commandQueue.front())->givingResources = saveExReqCmd->receivingResources;
                ((ExchangeResponseCommand*)commandQueue.front())->receivingResources = saveExReqCmd->givingResources;
                ((ExchangeResponseCommand*)commandQueue.front())->playerReceiving = saveExReqCmd->playerColor;
                if (state->players[commandQueue.front()->playerColor].playerState == EXCHANGE){
                    if (commandQueue.front()->verify(state)){
                        if(commandQueue.front()->execute(state) == true){
                            state->gameState = NORMAL_STATE;
                            for (int i = 0; i < state->players.size(); i++){
                                if (state->players[i].playerColor != saveExReqCmd->playerColor){
                                    state->players[i].playerState = STAND_BY;
                                }
                            }
                        }
                    } else { //si le player ne peut pas echanger
                        state->players[commandQueue.front()->playerColor].playerState = STAND_BY;
                    }
                }
                int s = 0;
                for (state::Player p : state->players){
                    s += p.playerState == EXCHANGE ? 1 : 0;
                }
                if (s == 0) {
                    state->gameState = NORMAL_STATE;
                    std::cout << "Reviens en normal state\n";
                }

            } else {
                std::cout << "Error, game is in EXCHANGE_REQUEST_STATE, players who have to answer are : ";
                for (state::Player p : state->players){
                    if (p.playerState == state::EXCHANGE) std::cout << p.name << " ";
                } std::cout << std::endl;
            }
        }

        else if (state->gameState == PLACE_THIEF_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID == PLACE_THIEF_CMD){
                    if (commandQueue.front()->verify(state) == true){
                        commandQueue.front()->execute(state);
                        if (saveCmd == THROW_DICE_CMD){
                            if (((PlaceThiefCommand*) commandQueue.front())->canSteal)
                                state->gameState = STEAL_CARD_STATE;
                            else {
                                //state->turn = (state::PlayerColor)(((int) state->turn) + 1);
                                state->gameState = NORMAL_STATE;
                            }
                        } else if (saveCmd == USE_CARD_CMD){
                            state->gameState = STEAL_CARD_STATE;
                        }
                    } else {
                        std::cout << "Place thief error\n";
                    }
                } else {
                    std::cout << "Error, game is in PLACE_THIEF_STATE" << std::endl;
                }
            } else {
                std::cout << "Not your turn player " << commandQueue.front()->playerColor << std::endl;
            }
        }

        else if (state->gameState == STEAL_CARD_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID == STEAL_CARD_CMD){
                    if (commandQueue.front()->verify(state) == true){
                        commandQueue.front()->execute(state);
                        if (saveCmd == THROW_DICE_CMD){
                            //state->turn = (state::PlayerColor)(((int) state->turn) + 1);
                        }
                        state->gameState = NORMAL_STATE;
                    } else {
                        std::cout << "Cannot steal from this player" << std::endl;
                    }
                } else {
                    std::cout << "Error, game is in STEAL_CARD_STATE" << std::endl;
                }
            }
        }

        else if (state->gameState == MONOPOLY_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID == MONOPOLY_CMD){
                    if (commandQueue.front()->verify(state) == true){
                        commandQueue.front()->execute(state);
                        state->gameState = NORMAL_STATE;
                    }
                } else {
                    std::cout << "Error game is in state MONOPOLY" << std::endl;
                }
            }
        }

        else if (state->gameState == ROAD_CONSTRUCTION_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID == PLACE_ROAD_CMD){
                    if (commandQueue.front()->verify(state) == true){
                        commandQueue.front()->execute(state);
                        buildRoads++;
                    } if (buildRoads == roadConstrutionNum) {
                        state->gameState = NORMAL_STATE; //si le joueur à placé ses routes
                    }
                } else {
                    std::cout << "Error, please place " << roadConstrutionNum - buildRoads << " roads" << std::endl;
                }
            }
        }

        else if (state->gameState == INVENTION_STATE){
            if (commandQueue.front()->playerColor == state->turn){
                if (commandQueue.front()->commandID == INVENTION_CMD){
                    if (commandQueue.front()->verify(state) == true){
                        commandQueue.front()->execute(state);
                        state->gameState = NORMAL_STATE;
                        std::cout << "YESSAIEEE\n";
                    } else {
                        std::cout << "NOT VERIFIED\n";
                    }
                } else {
                    std::cout << "Error game is in state INVENTION_STATE" << std::endl;
                }
            } else {
                std::cout << "not your turn\n";
            }
        }


        delete commandQueue.front();
        commandQueue.pop();
    }
}

}