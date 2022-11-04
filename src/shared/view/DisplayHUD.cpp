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
        cout << "Could not find the font " << "res/poppins.ttf" << endl;
    }

    red = Color(181, 53, 53);
    green = Color(70, 157, 70);
    blue = Color(69, 98, 184);
    yellow = Color(182, 148, 82);
    //-----------------------------------------
    int scrennGap = 30;
    int squareGap = 20;
    float scaleSquare = 0.7;
    int widthSquare = 180;
    int lengthSquare = 210;
    int heigthSqaure = -30;
    
    player1Square.loadFromFile("../res/square.png", IntRect(0, 0, 510, 210));
    spritePlayer1Square.setTexture(player1Square);
    spritePlayer1Square.setScale(Vector2f(0.8, 0.8));
    spritePlayer1Square.setPosition(scrennGap, -100);

    player2Square.loadFromFile("../res/square.png", IntRect(400, 225, widthSquare, lengthSquare));
    spritePlayer2Square.setTexture(player2Square);
    spritePlayer2Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer2Square.setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, heigthSqaure);

    player3Square.loadFromFile("../res/square.png", IntRect(0, 225, widthSquare, lengthSquare));
    spritePlayer3Square.setTexture(player3Square);
    spritePlayer3Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer3Square.setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, heigthSqaure);

    player4Square.loadFromFile("../res/square.png", IntRect(200, 225, widthSquare, lengthSquare));
    spritePlayer4Square.setTexture(player4Square);
    spritePlayer4Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer4Square.setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, heigthSqaure);
}

void DisplayHUD::display(sf::RenderTarget& target, Player player1, Player player2, Player player3, Player player4){
    
    target.draw(spritePlayer1Square);
    target.draw(spritePlayer2Square);
    target.draw(spritePlayer3Square);
    target.draw(spritePlayer4Square);

    int scrennGap = 30;

    Text player1Name, player2Name, player3Name, player4Name;
    player1Name.setFont(font);
    player1Name.setString(player1.name);
    player1Name.setCharacterSize(24);
    player1Name.setFillColor(red);
    player1Name.setPosition(scrennGap + 25, 15);
    
    player2Name.setFont(font);
    player2Name.setString(player2.name);
    player2Name.setCharacterSize(18);
    player2Name.setFillColor(green);
    player2Name.setOrigin((player2Name.getGlobalBounds().width)/2, 0);
    player2Name.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x , 15);

    player3Name.setFont(font);
    player3Name.setString(player3.name);
    player3Name.setCharacterSize(18);
    player3Name.setFillColor(blue);
    player3Name.setOrigin((player3Name.getGlobalBounds().width)/2, 0);
    player3Name.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x , 15);

    player4Name.setFont(font);
    player4Name.setString(player4.name);
    player4Name.setCharacterSize(18);
    player4Name.setFillColor(yellow);
    player4Name.setOrigin((player4Name.getGlobalBounds().width)/2, 0);
    player4Name.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x , 15);

    target.draw(player1Name);
    target.draw(player2Name);
    target.draw(player3Name);
    target.draw(player4Name);

    Texture icon;
    icon.loadFromFile("../res/icons.png");
    
    //--------------------playerVP----------------------------

    Sprite spritePlayer1VP, spritePlayer2VP, spritePlayer3VP, spritePlayer4VP;
    spritePlayer1VP.setTexture(icon);
    spritePlayer1VP.setTextureRect(IntRect(5*74, 0, 74, 58));
    spritePlayer1VP.setPosition(scrennGap + 350, 12);
    spritePlayer1VP.setScale((Vector2f(0.5, 0.5)));

    spritePlayer2VP.setTexture(icon);
    spritePlayer2VP.setTextureRect(IntRect(5*74, 0, 74, 58));
    spritePlayer2VP.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x + 25, 42);
    spritePlayer2VP.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer3VP.setTexture(icon);
    spritePlayer3VP.setTextureRect(IntRect(5*74, 0, 74, 58));
    spritePlayer3VP.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x + 25, 42);
    spritePlayer3VP.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer4VP.setTexture(icon);
    spritePlayer4VP.setTextureRect(IntRect(5*74, 0, 74, 58));
    spritePlayer4VP.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x + 25, 42);
    spritePlayer4VP.setScale((Vector2f(0.4, 0.4)));

    target.draw(spritePlayer1VP);
    target.draw(spritePlayer2VP);
    target.draw(spritePlayer3VP);
    target.draw(spritePlayer4VP);

    Text player1VP, player2VP, player3VP, player4VP;
    player1VP.setFont(font);
    player1VP.setString(to_string(player1.victoryPoints));
    player1VP.setCharacterSize(24);
    player1VP.setFillColor(Color::White);
    player1VP.setOrigin(player1VP.getGlobalBounds().width, 0);
    player1VP.setPosition(scrennGap + 340, 15);

    player2VP.setFont(font);
    player2VP.setString(to_string(player2.victoryPoints));
    player2VP.setCharacterSize(18);
    player2VP.setFillColor(Color::White);
    player2VP.setOrigin(player2VP.getGlobalBounds().width, 0);
    player2VP.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x + 15 , 45);

    player3VP.setFont(font);
    player3VP.setString(to_string(player3.victoryPoints));
    player3VP.setCharacterSize(18);
    player3VP.setFillColor(Color::White);
    player3VP.setOrigin(player3VP.getGlobalBounds().width, 0);
    player3VP.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x + 15 , 45);

    player4VP.setFont(font);
    player4VP.setString(to_string(player4.victoryPoints));
    player4VP.setCharacterSize(18);
    player4VP.setFillColor(Color::White);
    player4VP.setOrigin(player4VP.getGlobalBounds().width, 0);
    player4VP.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x + 15 , 45);

    target.draw(player1VP);
    target.draw(player2VP);
    target.draw(player3VP);
    target.draw(player4VP);

    //--------------------playerVP----------------------------

    //----------------playerNumberCards-----------------------

    Sprite spritePlayer1NumberCards, spritePlayer2NumberCards, spritePlayer3NumberCards, spritePlayer4NumberCards;
    spritePlayer1NumberCards.setTexture(icon);
    spritePlayer1NumberCards.setTextureRect(IntRect(7*74, 0, 74, 58));
    spritePlayer1NumberCards.setPosition(scrennGap + 270, 15);
    spritePlayer1NumberCards.setScale((Vector2f(0.5, 0.5)));

    spritePlayer2NumberCards.setTexture(icon);
    spritePlayer2NumberCards.setTextureRect(IntRect(7*74, 0, 74, 58));
    spritePlayer2NumberCards.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x - 35, 45);
    spritePlayer2NumberCards.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer3NumberCards.setTexture(icon);
    spritePlayer3NumberCards.setTextureRect(IntRect(7*74, 0, 74, 58));
    spritePlayer3NumberCards.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x -35, 45);
    spritePlayer3NumberCards.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer4NumberCards.setTexture(icon);
    spritePlayer4NumberCards.setTextureRect(IntRect(7*74, 0, 74, 58));
    spritePlayer4NumberCards.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x -35, 45);
    spritePlayer4NumberCards.setScale((Vector2f(0.4, 0.4)));

    target.draw(spritePlayer1NumberCards);
    target.draw(spritePlayer2NumberCards);
    target.draw(spritePlayer3NumberCards);
    target.draw(spritePlayer4NumberCards);
    
    Text player1NumberCards, player2NumberCards, player3NumberCards, player4NumberCards;
    player1NumberCards.setFont(font);
    player1NumberCards.setString("0");
    player1NumberCards.setCharacterSize(24);
    player1NumberCards.setFillColor(Color::White);
    player1NumberCards.setOrigin(player1NumberCards.getGlobalBounds().width, 0);
    player1NumberCards.setPosition(scrennGap + 265, 15);

    player2NumberCards.setFont(font);
    player2NumberCards.setString("0");
    player2NumberCards.setCharacterSize(18);
    player2NumberCards.setFillColor(Color::White);
    player2NumberCards.setOrigin(player2NumberCards.getGlobalBounds().width, 0);
    player2NumberCards.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x -40 , 45);

    player3NumberCards.setFont(font);
    player3NumberCards.setString("0");
    player3NumberCards.setCharacterSize(18);
    player3NumberCards.setFillColor(Color::White);
    player3NumberCards.setOrigin(player3NumberCards.getGlobalBounds().width, 0);
    player3NumberCards.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x -40 , 45);

    player4NumberCards.setFont(font);
    player4NumberCards.setString("0");
    player4NumberCards.setCharacterSize(18);
    player4NumberCards.setFillColor(Color::White);
    player4NumberCards.setOrigin(player4NumberCards.getGlobalBounds().width, 0);
    player4NumberCards.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x -40, 45);

    target.draw(player1NumberCards);
    target.draw(player2NumberCards);
    target.draw(player3NumberCards);
    target.draw(player4NumberCards);

    //----------------playerNumberCards-----------------------

    //-------------playerNumberDevelopments-------------------

    Sprite spritePlayer2NumberDevelopments, spritePlayer3NumberDevelopments, spritePlayer4NumberDevelopments;
    spritePlayer2NumberDevelopments.setTexture(icon);
    spritePlayer2NumberDevelopments.setTextureRect(IntRect(8*74, 0, 74, 58));
    spritePlayer2NumberDevelopments.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x - 35, 80);
    spritePlayer2NumberDevelopments.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer3NumberDevelopments.setTexture(icon);
    spritePlayer3NumberDevelopments.setTextureRect(IntRect(8*74, 0, 74, 58));
    spritePlayer3NumberDevelopments.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x -35, 80);
    spritePlayer3NumberDevelopments.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer4NumberDevelopments.setTexture(icon);
    spritePlayer4NumberDevelopments.setTextureRect(IntRect(8*74, 0, 74, 58));
    spritePlayer4NumberDevelopments.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x -35, 80);
    spritePlayer4NumberDevelopments.setScale((Vector2f(0.4, 0.4)));

    target.draw(spritePlayer2NumberDevelopments);
    target.draw(spritePlayer3NumberDevelopments);
    target.draw(spritePlayer4NumberDevelopments);

    Text player2NumberDevelopments, player3NumberDevelopments, player4NumberDevelopments;
    player2NumberDevelopments.setFont(font);
    player2NumberDevelopments.setString("0");
    player2NumberDevelopments.setCharacterSize(18);
    player2NumberDevelopments.setFillColor(Color::White);
    player2NumberDevelopments.setOrigin(player2NumberDevelopments.getGlobalBounds().width, 0);
    player2NumberDevelopments.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x -40 , 80);

    player3NumberDevelopments.setFont(font);
    player3NumberDevelopments.setString("0");
    player3NumberDevelopments.setCharacterSize(18);
    player3NumberDevelopments.setFillColor(Color::White);
    player3NumberDevelopments.setOrigin(player3NumberDevelopments.getGlobalBounds().width, 0);
    player3NumberDevelopments.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x -40 , 80);

    player4NumberDevelopments.setFont(font);
    player4NumberDevelopments.setString("0");
    player4NumberDevelopments.setCharacterSize(18);
    player4NumberDevelopments.setFillColor(Color::White);
    player4NumberDevelopments.setOrigin(player4NumberDevelopments.getGlobalBounds().width, 0);
    player4NumberDevelopments.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x -40, 80);

    target.draw(player2NumberDevelopments);
    target.draw(player3NumberDevelopments);
    target.draw(player4NumberDevelopments);

    //-------------playerNumberDevelopments-------------------

    //----------------playerNumberKnights---------------------


    Sprite spritePlayer1NumberKnights, spritePlayer2NumberKnights, spritePlayer3NumberKnights, spritePlayer4NumberKnights;
    spritePlayer1NumberKnights.setTexture(icon);
    spritePlayer1NumberKnights.setTextureRect(IntRect(6*74, 0, 74, 58));
    spritePlayer1NumberKnights.setPosition(scrennGap + 200, 12);
    spritePlayer1NumberKnights.setScale((Vector2f(0.5, 0.5)));

    spritePlayer2NumberKnights.setTexture(icon);
    spritePlayer2NumberKnights.setTextureRect(IntRect(6*74, 0, 74, 58));
    spritePlayer2NumberKnights.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x + 25, 80);
    spritePlayer2NumberKnights.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer3NumberKnights.setTexture(icon);
    spritePlayer3NumberKnights.setTextureRect(IntRect(6*74, 0, 74, 58));
    spritePlayer3NumberKnights.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x + 25, 80);
    spritePlayer3NumberKnights.setScale((Vector2f(0.4, 0.4)));
    
    spritePlayer4NumberKnights.setTexture(icon);
    spritePlayer4NumberKnights.setTextureRect(IntRect(6*74, 0, 74, 58));
    spritePlayer4NumberKnights.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x + 25, 80);
    spritePlayer4NumberKnights.setScale((Vector2f(0.4, 0.4)));

    target.draw(spritePlayer1NumberKnights);
    target.draw(spritePlayer2NumberKnights);
    target.draw(spritePlayer3NumberKnights);
    target.draw(spritePlayer4NumberKnights);

    Text player1NumberKnights, player2NumberKnights, player3NumberKnights, player4NumberKnights;
    player1NumberKnights.setFont(font);
    player1NumberKnights.setString(to_string(player1.knightNumber));
    player1NumberKnights.setCharacterSize(24);
    player1NumberKnights.setFillColor(Color::White);
    player1NumberKnights.setOrigin(player1NumberKnights.getGlobalBounds().width, 0);
    player1NumberKnights.setPosition(scrennGap + 192, 15);

    player2NumberKnights.setFont(font);
    player2NumberKnights.setString(to_string(player2.knightNumber));
    player2NumberKnights.setCharacterSize(18);
    player2NumberKnights.setFillColor(Color::White);
    player2NumberKnights.setOrigin(player2NumberKnights.getGlobalBounds().width, 0);
    player2NumberKnights.setPosition((spritePlayer2Square.getGlobalBounds().width)/2 + spritePlayer2Square.getPosition().x + 15, 80);

    player3NumberKnights.setFont(font);
    player3NumberKnights.setString(to_string(player3.knightNumber));
    player3NumberKnights.setCharacterSize(18);
    player3NumberKnights.setFillColor(Color::White);
    player3NumberKnights.setOrigin(player3NumberKnights.getGlobalBounds().width, 0);
    player3NumberKnights.setPosition((spritePlayer3Square.getGlobalBounds().width)/2 + spritePlayer3Square.getPosition().x + 15, 80);

    player4NumberKnights.setFont(font);
    player4NumberKnights.setString(to_string(player3.knightNumber));
    player4NumberKnights.setCharacterSize(18);
    player4NumberKnights.setFillColor(Color::White);
    player4NumberKnights.setOrigin(player4NumberKnights.getGlobalBounds().width, 0);
    player4NumberKnights.setPosition((spritePlayer4Square.getGlobalBounds().width)/2 + spritePlayer4Square.getPosition().x + 15, 80);

    target.draw(player1NumberKnights);
    target.draw(player2NumberKnights);
    target.draw(player3NumberKnights);
    target.draw(player4NumberKnights);

    //----------------playerNumberKnights---------------------

}
}