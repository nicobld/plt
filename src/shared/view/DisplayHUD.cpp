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

    playerSquare.loadFromFile("../res/squares.png");
    playerSquare.setSmooth(true);

    spritePlayer1Square =  new Sprite(playerSquare,IntRect(0, 0, 504, 204));
    spritePlayer1Square->setScale(Vector2f(0.9, 0.9));
    spritePlayer1Square->setPosition(scrennGap, -120);

    spritePlayer2Square = new Sprite(playerSquare, IntRect(widthSquare*3, 205, widthSquare, lengthSquare));
    spritePlayer2Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer2Square->setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, heigthSqaure);

    spritePlayer3Square = new Sprite(playerSquare, IntRect(widthSquare*1, 205, widthSquare, lengthSquare));
    spritePlayer3Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer3Square->setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, heigthSqaure);

    spritePlayer4Square = new Sprite(playerSquare, IntRect(widthSquare*2, 205, widthSquare, lengthSquare));
    spritePlayer4Square->setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer4Square->setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, heigthSqaure);

    //------------------playerSquare--------------------------

    //----------------playerRessources-----------------------

    spriteRessourceSquare = new Sprite(playerSquare, IntRect(widthSquare*4, 205, 309, 52));
    spriteRessourceSquare->setPosition(scrennGap, spritePlayer1Square->getGlobalBounds().height + spritePlayer1Square->getPosition().y + 20);
    spriteRessourceSquare->setScale(Vector2f(1.31, 1.3));
    for(int i = 0; i<5; i++){
        vectorSpriteRessource.push_back(Sprite(icon, IntRect(i*74, 0, 74, 58)));
        vectorSpriteRessource.back().setScale(Vector2f(0.5, 0.5));
        vectorSpriteRessource.back().setPosition(spriteRessourceSquare->getPosition().x + 40 + i*80, spriteRessourceSquare->getPosition().y + spriteRessourceSquare->getGlobalBounds().height/2 - 13);

        vectorTextRessource.push_back(Text(to_string(player1.resources.at(i).number), font, 24));
        vectorTextRessource.back().setPosition(vectorSpriteRessource.back().getPosition().x - 20, vectorSpriteRessource.back().getPosition().y);
        vectorTextRessource.back().setFillColor(Color(0,0,0));
    }
    
    //----------------playerRessources-----------------------

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

    developmentCards.loadFromFile("../res/developmentCards.png");
    developmentCards.setSmooth(true);

    //--------------------player1Cards------------------------

    //-----------------------Button---------------------------
    int ecartBouton = 60;

    buttonPassTurn = new Sprite(playerSquare, IntRect(1010, 205, 199, 48));
    buttonExhchange = new Sprite(playerSquare, IntRect(1010 + 199, 205, 199, 48));
    buttonBuild = new Sprite(playerSquare, IntRect(1011 + 199*2, 205, 199, 48));

    passTurn = new Text("Passer son tour", font, 24);
    exchange = new Text("Echange", font, 24);
    build = new Text("Construction", font, 24);

    buttonPassTurn->setPosition(WIDTH - scrennGap - buttonPassTurn->getGlobalBounds().width, LENGTH - scrennGap -  buttonPassTurn->getGlobalBounds().height);
    passTurn->setOrigin(passTurn->getGlobalBounds().width/2, passTurn->getGlobalBounds().height/2);
    passTurn->setPosition(buttonPassTurn->getPosition().x + buttonPassTurn->getGlobalBounds().width/2, buttonPassTurn->getGlobalBounds().height/2 + buttonPassTurn->getPosition().y - 8);

    buttonExhchange->setPosition(WIDTH - scrennGap - buttonPassTurn->getGlobalBounds().width, LENGTH - scrennGap -  buttonPassTurn->getGlobalBounds().height - ecartBouton);
    exchange->setOrigin(exchange->getGlobalBounds().width/2, exchange->getGlobalBounds().height/2);
    exchange->setPosition(buttonExhchange->getPosition().x + buttonExhchange->getGlobalBounds().width/2, buttonExhchange->getGlobalBounds().height/2 + buttonExhchange->getPosition().y - 4); 

    buttonBuild->setPosition(WIDTH - scrennGap - buttonBuild->getGlobalBounds().width, LENGTH - scrennGap -  buttonBuild->getGlobalBounds().height - ecartBouton*2);
    build->setOrigin(build->getGlobalBounds().width/2, build->getGlobalBounds().height/2);
    build->setPosition(buttonBuild->getPosition().x + buttonBuild->getGlobalBounds().width/2, buttonBuild->getGlobalBounds().height/2 + buttonBuild->getPosition().y - 8); 


    //-----------------------Button---------------------------

}

void DisplayHUD::render(sf::RenderTarget& target, Player player1, Player player2, Player player3, Player player4){
    
    update(player1, player2, player3, player4);

    target.draw(*spritePlayer1Square);
    target.draw(*spritePlayer2Square);
    target.draw(*spritePlayer3Square);
    target.draw(*spritePlayer4Square);

    target.draw(*spriteRessourceSquare);
    for(int i = 0; i<5; i++){
        target.draw(vectorSpriteRessource.at(i));
        target.draw(vectorTextRessource.at(i));
    }

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

    for(int i = 0; i < player1.developments.size(); i++){
        target.draw(vectorSpriteCards.at(i));
    }
    vectorSpriteCards.clear();

    target.draw(*buttonPassTurn);
    target.draw(*buttonExhchange);
    target.draw(*buttonBuild);
    target.draw(*passTurn);
    target.draw(*exchange);
    target.draw(*build);
}


void DisplayHUD::update(Player player1, Player player2, Player player3, Player player4){
    
    player1VP->setString(to_string(player1.victoryPoints));
    player2VP->setString(to_string(player2.victoryPoints));
    player3VP->setString(to_string(player3.victoryPoints));
    player4VP->setString(to_string(player4.victoryPoints));
    
    int sommeResources1 = 0, sommeResources2 = 0, sommeResources3 = 0, sommeResources4 = 0;
    for(int i = 0; i<5; i++){
        vectorTextRessource.at(i).setString(to_string(player1.resources.at(i).number));
        sommeResources1 += player1.resources.at(i).number;
        sommeResources2 += player2.resources.at(i).number;
        sommeResources3 += player3.resources.at(i).number;
        sommeResources4 += player4.resources.at(i).number;
    }

    player1NumberCards->setString(to_string(sommeResources1));
    player2NumberCards->setString(to_string(sommeResources2));
    player3NumberCards->setString(to_string(sommeResources3));
    player4NumberCards->setString(to_string(sommeResources4));

    player2NumberDevelopments->setString(to_string(player2.developments.size()));
    player3NumberDevelopments->setString(to_string(player3.developments.size()));
    player4NumberDevelopments->setString(to_string(player4.developments.size()));

    player1NumberKnights->setString(to_string(player1.knightNumber));
    player2NumberKnights->setString(to_string(player2.knightNumber));
    player3NumberKnights->setString(to_string(player3.knightNumber));
    player4NumberKnights->setString(to_string(player4.knightNumber));

        if(player1.hasLargestArmy)
            player1NumberKnights->setFillColor(Color(red));
        if(player2.hasLargestArmy)
            player2NumberKnights->setFillColor(Color(red));
        if(player3.hasLargestArmy)
            player3NumberKnights->setFillColor(Color(red));
        if(player4.hasLargestArmy)
            player4NumberKnights->setFillColor(Color(red));

    player1NumberRoads->setString("0");
    player2NumberRoads->setString("0");
    player3NumberRoads->setString("0");
    player4NumberRoads->setString("0");

        if(player1.hasLongestRoad)
            player1NumberRoads->setFillColor(Color(red));
        if(player2.hasLongestRoad)
            player2NumberRoads->setFillColor(Color(red));
        if(player3.hasLongestRoad)
            player3NumberRoads->setFillColor(Color(red));
        if(player4.hasLongestRoad)
            player4NumberRoads->setFillColor(Color(red));

    //--------------------player1Cards------------------------
    int ecart = 80;
    int compteur = 1;
    for(int i = player1.developments.size()-1; i >= 0; i--){
        vectorSpriteCards.push_back(Sprite(developmentCards, IntRect(155 * (player1.developments.at(i).developmentType + 2), 0, 155, 234)));
        vectorSpriteCards.back().setScale(Vector2f(1.2, 1.2));
        vectorSpriteCards.back().setPosition( 30 + (player1.developments.size() - compteur)*( 155- ecart), 455);
        compteur++;
    }
    //--------------------player1Cards------------------------

}

}