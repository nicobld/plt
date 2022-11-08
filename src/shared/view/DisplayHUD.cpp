#include "DisplayHUD.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace view;
using namespace state;


namespace view{

DisplayHUD::DisplayHUD(int WIDTH, int LENGTH, Player& player1, Player& player2, Player& player3, Player& player4) {

    //init font and color
    if (!this->font.loadFromFile("../res/poppins.ttf")){
        cout << "Could not find the font " << "../res/poppins.ttf" << endl;
    }

    red = Color(181, 53, 53);
    green = Color(70, 157, 70);
    blue = Color(69, 98, 184);
    yellow = Color(182, 148, 82);
    //-----------------------------------------
    int scrennGap = 30;
    int squareGap = 20;
    float scaleSquare = 0.8;
    int widthSquare = 175;
    int lengthSquare = 205;
    int heigthSqaure = -10;

    float scaleIconPlayer1 = 0.5;
    float scaleIconPlayers = 0.5;

    int sizeFontIconsplayers = 20;

     //------------------playerSquare--------------------------

    playerSquare.loadFromFile("../res/square.png");
    playerSquare.setSmooth(true);

    spritePlayer1Square =  new Sprite(playerSquare,IntRect(0, 0, 504, 204));
    spritePlayer1Square->setScale(Vector2f(0.9, 0.9));
    spritePlayer1Square->setPosition(scrennGap, -120);

    spritePlayer2Square = new Sprite(playerSquare, IntRect(400, 227, widthSquare, lengthSquare));
    spritePlayer2Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer2Square->setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, heigthSqaure);

    spritePlayer3Square = new Sprite(playerSquare, IntRect(0, 227, widthSquare, lengthSquare));
    spritePlayer3Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer3Square->setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, heigthSqaure);

    spritePlayer4Square = new Sprite(playerSquare, IntRect(200, 227, widthSquare, lengthSquare));
    spritePlayer4Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer4Square->setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, heigthSqaure);

    //------------------playerSquare--------------------------

    //-------------------playerName---------------------------

    player1Name = new Text(player1.name, font, 24);
    player1Name->setFillColor(red);
    player1Name->setPosition(scrennGap + 25, 15);

    player2Name = new Text(player2.name, font, sizeFontIconsplayers);
    player2Name->setFillColor(green);
    player2Name->setOrigin((player2Name->getGlobalBounds().width)/2, 0);
    player2Name->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x , 10);

    player3Name = new Text(player3.name, font, sizeFontIconsplayers);
    player3Name->setFillColor(blue);
    player3Name->setOrigin((player3Name->getGlobalBounds().width)/2, 0);
    player3Name->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x , 10);

    player4Name = new Text(player4.name, font, sizeFontIconsplayers);
    player4Name->setFillColor(yellow);
    player4Name->setOrigin((player4Name->getGlobalBounds().width)/2, 0);
    player4Name->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x , 10);

    //-------------------playerName---------------------------

    /*
    if(!icon.loadFromFile("../res/icons.png")){
         cout << "Could not find the icons " << "../res/icons.png" << endl;
    }
    */
    icon.loadFromFile("../res/icons.png");
    icon.setSmooth(true);

    //--------------------playerVP----------------------------

    spritePlayer1VP = new Sprite(icon, IntRect(5*74, 0, 74, 58));
    spritePlayer1VP->setPosition(scrennGap + 400, 12);
    spritePlayer1VP->setScale((Vector2f(scaleIconPlayer1, scaleIconPlayer1)));

    spritePlayer2VP = new Sprite(icon, IntRect(5*74, 0, 74, 58));
    spritePlayer2VP->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x + 25, 40);
    spritePlayer2VP->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer3VP = new Sprite(icon, IntRect(5*74, 0, 74, 58));
    spritePlayer3VP->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x + 25, 40);
    spritePlayer3VP->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer4VP = new Sprite(icon, IntRect(5*74, 0, 74, 58));
    spritePlayer4VP->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x + 25, 40);
    spritePlayer4VP->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));


    player1VP = new Text(to_string(player1.victoryPoints), font, 24);
    player1VP->setFillColor(Color::White);
    player1VP->setOrigin(player1VP->getGlobalBounds().width, 0);
    player1VP->setPosition(spritePlayer1VP->getPosition().x -10 , spritePlayer1VP->getPosition().y + 3);

    player2VP = new Text(to_string(player2.victoryPoints), font, sizeFontIconsplayers);
    player2VP->setFillColor(Color::White);
    player2VP->setOrigin(player2VP->getGlobalBounds().width, 0);
    player2VP->setPosition(spritePlayer2VP->getPosition().x -10 , spritePlayer2VP->getPosition().y + 5);

    player3VP = new Text(to_string(player3.victoryPoints), font, sizeFontIconsplayers);
    player3VP->setFillColor(Color::White);
    player3VP->setOrigin(player3VP->getGlobalBounds().width, 0);
    player3VP->setPosition(spritePlayer3VP->getPosition().x -10, spritePlayer3VP->getPosition().y + 5);

    player4VP = new Text(to_string(player4.victoryPoints), font, sizeFontIconsplayers);
    player4VP->setFillColor(Color::White);
    player4VP->setOrigin(player4VP->getGlobalBounds().width, 0);
    player4VP->setPosition(spritePlayer4VP->getPosition().x -10 , spritePlayer4VP->getPosition().y + 5);

    //--------------------playerVP----------------------------

    //----------------playerNumberCards-----------------------

    spritePlayer1NumberCards = new Sprite(icon, IntRect(7*74, 0, 74, 58));
    spritePlayer1NumberCards->setPosition(scrennGap + 320, 15);
    spritePlayer1NumberCards->setScale((Vector2f(scaleIconPlayer1, scaleIconPlayer1)));

    spritePlayer2NumberCards = new Sprite(icon, IntRect(7*74, 0, 74, 58));
    spritePlayer2NumberCards->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x - 40, 45);
    spritePlayer2NumberCards->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer3NumberCards = new Sprite(icon, IntRect(7*74, 0, 74, 58));
    spritePlayer3NumberCards->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x -40, 45);
    spritePlayer3NumberCards->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer4NumberCards = new Sprite(icon, IntRect(7*74, 0, 74, 58));
    spritePlayer4NumberCards->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x -40, 45);
    spritePlayer4NumberCards->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));


    player1NumberCards = new Text("0", font, 24);
    player1NumberCards->setFillColor(Color::White);
    player1NumberCards->setOrigin(player1NumberCards->getGlobalBounds().width, 0);
    player1NumberCards->setPosition(spritePlayer1NumberCards->getPosition().x - 2, spritePlayer1NumberCards->getPosition().y);

    player2NumberCards = new Text("0", font, sizeFontIconsplayers);
    player2NumberCards->setFillColor(Color::White);
    player2NumberCards->setOrigin(player2NumberCards->getGlobalBounds().width, 0);
    player2NumberCards->setPosition(spritePlayer2NumberCards->getPosition().x -5 , spritePlayer2NumberCards->getPosition().y );

    player3NumberCards = new Text("0", font, sizeFontIconsplayers);
    player3NumberCards->setFillColor(Color::White);
    player3NumberCards->setOrigin(player3NumberCards->getGlobalBounds().width, 0);
    player3NumberCards->setPosition(spritePlayer3NumberCards->getPosition().x -5 , spritePlayer3NumberCards->getPosition().y );

    player4NumberCards = new Text("0", font, sizeFontIconsplayers);
    player4NumberCards->setFillColor(Color::White);
    player4NumberCards->setOrigin(player4NumberCards->getGlobalBounds().width, 0);
    player4NumberCards->setPosition(spritePlayer4NumberCards->getPosition().x -5 , spritePlayer4NumberCards->getPosition().y );

    //----------------playerNumberCards-----------------------

    //-------------playerNumberDevelopments-------------------

    spritePlayer2NumberDevelopments = new Sprite(icon, IntRect(8*74, 0, 74, 58));
    spritePlayer2NumberDevelopments->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x - 40, 85);
    spritePlayer2NumberDevelopments->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer3NumberDevelopments = new Sprite(icon, IntRect(8*74, 0, 74, 58));
    spritePlayer3NumberDevelopments->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x -40, 85);
    spritePlayer3NumberDevelopments->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer4NumberDevelopments = new Sprite(icon, IntRect(8*74, 0, 74, 58));
    spritePlayer4NumberDevelopments->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x -40, 85);
    spritePlayer4NumberDevelopments->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));


    player2NumberDevelopments = new Text("0", font, sizeFontIconsplayers);
    player2NumberDevelopments->setFillColor(Color::White);
    player2NumberDevelopments->setOrigin(player2NumberDevelopments->getGlobalBounds().width, 0);
    player2NumberDevelopments->setPosition(spritePlayer2NumberDevelopments->getPosition().x -5 , spritePlayer2NumberDevelopments->getPosition().y );

    player3NumberDevelopments = new Text("0", font, sizeFontIconsplayers);
    player3NumberDevelopments->setFillColor(Color::White);
    player3NumberDevelopments->setOrigin(player3NumberDevelopments->getGlobalBounds().width, 0);
    player3NumberDevelopments->setPosition(spritePlayer3NumberDevelopments->getPosition().x -5 , spritePlayer3NumberDevelopments->getPosition().y);

    player4NumberDevelopments = new Text("0", font, sizeFontIconsplayers);
    player4NumberDevelopments->setFillColor(Color::White);
    player4NumberDevelopments->setOrigin(player4NumberDevelopments->getGlobalBounds().width, 0);
    player4NumberDevelopments->setPosition(spritePlayer4NumberDevelopments->getPosition().x -5 , spritePlayer4NumberDevelopments->getPosition().y);

    //-------------playerNumberDevelopments-------------------

    //----------------playerNumberKnights---------------------


    spritePlayer1NumberKnights = new Sprite(icon, IntRect(6*74, 0, 74, 58));
    spritePlayer1NumberKnights->setPosition(scrennGap + 185, 12);
    spritePlayer1NumberKnights->setScale((Vector2f(scaleIconPlayer1, scaleIconPlayer1)));

    spritePlayer2NumberKnights = new Sprite(icon, IntRect(6*74, 0, 74, 58));
    spritePlayer2NumberKnights->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x + 25, 85);
    spritePlayer2NumberKnights->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer3NumberKnights = new Sprite(icon, IntRect(6*74, 0, 74, 58));
    spritePlayer3NumberKnights->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x + 25, 85);
    spritePlayer3NumberKnights->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));
    
    spritePlayer4NumberKnights = new Sprite(icon, IntRect(6*74, 0, 74, 58));
    spritePlayer4NumberKnights->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x + 25, 85);
    spritePlayer4NumberKnights->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));

    
    player1NumberKnights = new Text(to_string(player1.knightNumber), font, 24);
    player1NumberKnights->setFillColor(Color::White);
    player1NumberKnights->setOrigin(player1NumberKnights->getGlobalBounds().width, 0);
    player1NumberKnights->setPosition(spritePlayer1NumberKnights->getPosition().x -3, spritePlayer1NumberKnights->getPosition().y + 3);

    player2NumberKnights = new Text(to_string(player2.knightNumber), font, sizeFontIconsplayers);
    player2NumberKnights->setFillColor(Color::White);
    player2NumberKnights->setOrigin(player2NumberKnights->getGlobalBounds().width, 0);
    player2NumberKnights->setPosition(spritePlayer2NumberKnights->getPosition().x -10 , spritePlayer2NumberKnights->getPosition().y);

    player3NumberKnights = new Text(to_string(player3.knightNumber), font, sizeFontIconsplayers);
    player3NumberKnights->setFillColor(Color::White);
    player3NumberKnights->setOrigin(player3NumberKnights->getGlobalBounds().width, 0);
    player3NumberKnights->setPosition(spritePlayer3NumberKnights->getPosition().x -10, spritePlayer3NumberKnights->getPosition().y);

    player4NumberKnights = new Text(to_string(player3.knightNumber), font, sizeFontIconsplayers);
    player4NumberKnights->setFillColor(Color::White);
    player4NumberKnights->setOrigin(player4NumberKnights->getGlobalBounds().width, 0);
    player4NumberKnights->setPosition(spritePlayer4NumberKnights->getPosition().x -10 , spritePlayer4NumberKnights->getPosition().y);

    

    //----------------playerNumberKnights---------------------

    //-----------------playerNumberRoads----------------------

    spritePlayer1NumberRoads = new Sprite(icon, IntRect(9*74, 0, 74, 58));
    spritePlayer1NumberRoads->setPosition(scrennGap + 255, 15);
    spritePlayer1NumberRoads->setScale((Vector2f(scaleIconPlayer1, scaleIconPlayer1)));

    spritePlayer2NumberRoads = new Sprite(icon, IntRect(9*74, 0, 74, 58));
    spritePlayer2NumberRoads->setPosition((spritePlayer2Square->getGlobalBounds().width)/2 + spritePlayer2Square->getPosition().x, 118);
    spritePlayer2NumberRoads->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));

    spritePlayer3NumberRoads = new Sprite(icon, IntRect(9*74, 0, 74, 58));
    spritePlayer3NumberRoads->setPosition((spritePlayer3Square->getGlobalBounds().width)/2 + spritePlayer3Square->getPosition().x , 118);
    spritePlayer3NumberRoads->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));

    spritePlayer4NumberRoads = new Sprite(icon, IntRect(9*74, 0, 74, 58));
    spritePlayer4NumberRoads->setPosition((spritePlayer4Square->getGlobalBounds().width)/2 + spritePlayer4Square->getPosition().x, 118);
    spritePlayer4NumberRoads->setScale((Vector2f(scaleIconPlayers, scaleIconPlayers)));

    player1NumberRoads = new Text("0", font, 24);
    player1NumberRoads->setFillColor(Color::White);
    player1NumberRoads->setOrigin(player1NumberRoads->getGlobalBounds().width, 0);
    player1NumberRoads->setPosition(spritePlayer1NumberRoads->getPosition().x -5, spritePlayer1NumberRoads->getPosition().y);

    player2NumberRoads = new Text("0", font, sizeFontIconsplayers);
    player2NumberRoads->setFillColor(Color::White);
    player2NumberRoads->setOrigin(player2NumberRoads->getGlobalBounds().width, 0);
    player2NumberRoads->setPosition(spritePlayer2NumberRoads->getPosition().x -10 , spritePlayer2NumberRoads->getPosition().y);
    
    player3NumberRoads = new Text("0", font, sizeFontIconsplayers);
    player3NumberRoads->setFillColor(Color::White);
    player3NumberRoads->setOrigin(player3NumberRoads->getGlobalBounds().width, 0);
    player3NumberRoads->setPosition(spritePlayer3NumberRoads->getPosition().x -10 , spritePlayer3NumberRoads->getPosition().y);
    
    player4NumberRoads = new Text("0", font, sizeFontIconsplayers);
    player4NumberRoads->setFillColor(Color::White);
    player4NumberRoads->setOrigin(player4NumberRoads->getGlobalBounds().width, 0);
    player4NumberRoads->setPosition(spritePlayer4NumberRoads->getPosition().x -10 , spritePlayer4NumberRoads->getPosition().y);

    //-----------------playerNumberRoads----------------------

    //--------------------player1Cards------------------------
    /*
    Texture developmentCards;
    developmentCards.loadFromFile("../res/developmentCards.png");
    developmentCards.setSmooth(true);
    */

    //--------------------player1Cards------------------------

}

void DisplayHUD::render(sf::RenderTarget& target, Player player1, Player player2, Player player3, Player player4){
    
    update(player1, player2, player3, player4);

    target.draw(*spritePlayer1Square);
    target.draw(*spritePlayer2Square);
    target.draw(*spritePlayer3Square);
    target.draw(*spritePlayer4Square);
   
    target.draw(*player1Name);
    target.draw(*player2Name);
    target.draw(*player3Name);
    target.draw(*player4Name);

    target.draw(*spritePlayer1VP);
    target.draw(*spritePlayer2VP);
    target.draw(*spritePlayer3VP);
    target.draw(*spritePlayer4VP);
    
    target.draw(*player1VP);
    target.draw(*player2VP);
    target.draw(*player3VP);
    target.draw(*player4VP);

    target.draw(*spritePlayer1NumberCards);
    target.draw(*spritePlayer2NumberCards);
    target.draw(*spritePlayer3NumberCards);
    target.draw(*spritePlayer4NumberCards);

    target.draw(*player1NumberCards);
    target.draw(*player2NumberCards);
    target.draw(*player3NumberCards);
    target.draw(*player4NumberCards);
    
    target.draw(*spritePlayer2NumberDevelopments);
    target.draw(*spritePlayer3NumberDevelopments);
    target.draw(*spritePlayer4NumberDevelopments);

    target.draw(*player2NumberDevelopments);
    target.draw(*player3NumberDevelopments);
    target.draw(*player4NumberDevelopments);

    target.draw(*spritePlayer1NumberKnights);
    target.draw(*spritePlayer2NumberKnights);
    target.draw(*spritePlayer3NumberKnights);
    target.draw(*spritePlayer4NumberKnights);

    target.draw(*player1NumberKnights);
    target.draw(*player2NumberKnights);
    target.draw(*player3NumberKnights);
    target.draw(*player4NumberKnights);

    target.draw(*spritePlayer1NumberRoads);
    target.draw(*spritePlayer2NumberRoads);
    target.draw(*spritePlayer3NumberRoads);
    target.draw(*spritePlayer4NumberRoads);

    target.draw(*player1NumberRoads);
    target.draw(*player2NumberRoads);
    target.draw(*player3NumberRoads);
    target.draw(*player4NumberRoads);




    Texture developmentCards;
    developmentCards.loadFromFile("../res/developmentCards.png");
    developmentCards.setSmooth(true);

    std::vector<int> cardsPlayer1(10);
    cardsPlayer1.at(0) = 2;
    cardsPlayer1.at(0) = 3;
    
    std::vector<Sprite> vectorSpriteCards(10);
    int ecart = 0;
    for(int i = cardsPlayer1.size()-1; i > 0; i--){

        Sprite *spriteCard = new Sprite(developmentCards, IntRect(154 * cardsPlayer1.at(i), 0, 154, 234));
        spriteCard->setPosition(100-ecart, 500);
        vectorSpriteCards.at(i) = *spriteCard;
        ecart += 20;
    }

    for(int i= 0; i<9; i++){
        target.draw(vectorSpriteCards.at(i));
    }
}


void DisplayHUD::update(Player player1, Player player2, Player player3, Player player4){
    
    player1VP->setString(to_string(player1.victoryPoints));
    player2VP->setString(to_string(player2.victoryPoints));
    player3VP->setString(to_string(player3.victoryPoints));
    player4VP->setString(to_string(player4.victoryPoints));

    player1NumberCards->setString("0");
    player2NumberCards->setString("0");
    player3NumberCards->setString("0");
    player4NumberCards->setString("0");

    player2NumberDevelopments->setString("0");
    player3NumberDevelopments->setString("0");
    player4NumberDevelopments->setString("0");

    player1NumberKnights->setString(to_string(player1.knightNumber));
    player2NumberKnights->setString(to_string(player2.knightNumber));
    player3NumberKnights->setString(to_string(player3.knightNumber));
    player4NumberKnights->setString(to_string(player4.knightNumber));

    player1NumberRoads->setString("0");
    player2NumberRoads->setString("0");
    player3NumberRoads->setString("0");
    player4NumberRoads->setString("0");

    //--------------------player1Cards------------------------
    /*
    Texture developmentCards;
    developmentCards.loadFromFile("../res/developmentCards.png");
    developmentCards.setSmooth(true);

    std::vector<int> cardsPlayer1(10);
    cardsPlayer1.at(0) = 2;
    cardsPlayer1.at(0) = 3;
    
    std::vector<Sprite> vectorSpriteCards(10);
    
    for(int i = 0; i < cardsPlayer1.size(); i++){

        Sprite *spriteCard = new Sprite(developmentCards, IntRect(154 * cardsPlayer1.at(i), 0, 154, 234));
        vectorSpriteCards.at(i) = *spriteCard;
    }
    
   */
    //--------------------player1Cards------------------------

}

}