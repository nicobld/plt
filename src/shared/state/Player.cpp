#include "Player.h"

namespace state{

    Player::Player(std::string name) : name(name) {
        this->victoryPoints = 0;
        this->knightNumber = 0;
    }

    std::string Player::getName(){
        return this->name;
    }
}
