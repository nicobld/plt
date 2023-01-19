#include "VictoryScreen.h"

namespace view
{

VictoryScreen::VictoryScreen (std::vector<state::Player> playersRanking) : playersRanking(playersRanking){
    
    int width = 1280, height = 720;
    
    victoryScreenTexture.loadFromFile("../res/victoryScreen.png");
    victoryScreenTexture.setSmooth(true);

    victoryScreenSprite = new sf::Sprite(victoryScreenTexture);

    font.loadFromFile("../res/poppins.ttf");

    fontSize = 40;
    fontColor[0] = sf::Color(181, 53, 53);
    fontColor[1] = sf::Color(69, 98, 184);
    fontColor[2] = sf::Color(182, 148, 82);
    fontColor[3] = sf::Color(70, 157, 70);

    winSentence[0] = new sf::Text("Victoire de ", font, fontSize + 5);
    winSentence[0]->setColor(sf::Color(255, 255, 255));

    winSentence[1] = new sf::Text(playersRanking[0].name, font, fontSize + 5);
    winSentence[1]->setColor(fontColor[playersRanking[0].playerColor]);

    winSentence[0]->setPosition(width/2 - (winSentence[0]->getGlobalBounds().width + winSentence[1]->getGlobalBounds().width)/2, 180);
    winSentence[1]->setPosition(winSentence[0]->getPosition().x + winSentence[0]->getGlobalBounds().width, 180);

    int gap = 77, xDeparture = 320, yDeparture = 327;
    for(int i = 0; i < playersRanking.size(); i++){

        playersName[i] = new sf::Text(playersRanking[i].name, font, fontSize);
        playersName[i]->setColor(fontColor[playersRanking[i].playerColor]);
        playersName[i]->setPosition(xDeparture, yDeparture + i * gap);

        playerVictoryPoint[i] = new sf::Text(std::to_string(playersRanking[i].victoryPoints), font, fontSize);
        playerVictoryPoint[i]->setColor(sf::Color(0, 0, 0));
        playerVictoryPoint[i]->setPosition(xDeparture + 285 , yDeparture + i * gap);

        playerKnight[i] = new sf::Text(std::to_string(playersRanking[i].knightNumber), font, fontSize);
        playerKnight[i]->setColor(sf::Color(0, 0, 0));
        playerKnight[i]->setPosition(xDeparture + 285 + 90 , yDeparture + i * gap);
        
        playerRoad[i] = new sf::Text(std::to_string(playersRanking[i].longestRoad), font, fontSize);
        playerRoad[i]->setColor(sf::Color(0, 0, 0));
        playerRoad[i]->setPosition(xDeparture + 285 + 172 , yDeparture + i * gap);
        
        int victoryCard = 0;
        for(int j = 0 ; j < playersRanking[i].developments.size(); j++){
            if(playersRanking[i].developments[j].developmentType == state::VictoryPointsCard)
                victoryCard ++;
        }

        playerVictoryCard[i] = new sf::Text(std::to_string(victoryCard), font, fontSize);
        playerVictoryCard[i]->setColor(sf::Color(0, 0, 0));
        playerVictoryCard[i]->setPosition(xDeparture + 285 + 270 , yDeparture + i * gap);
        
        
        playerTotal[i] = new sf::Text(std::to_string(playersRanking[i].victoryPoints + victoryCard), font, fontSize);
        playerTotal[i]->setColor(sf::Color(0, 0, 0));
        playerTotal[i]->setPosition(xDeparture + 285 + 375 , yDeparture + i * gap);

    }

}

void VictoryScreen::render (sf::RenderTarget& target){
    target.draw(*victoryScreenSprite);
    for(sf::Text* t : winSentence)
        target.draw(*t);

    for(int i = 0; i < playersRanking.size(); i++){
        target.draw(*playersName[i]);
        target.draw(*playerVictoryPoint[i]);
        target.draw(*playerKnight[i]);
        target.draw(*playerRoad[i]);
        target.draw(*playerVictoryCard[i]);
        target.draw(*playerTotal[i]);
    }

}


}
