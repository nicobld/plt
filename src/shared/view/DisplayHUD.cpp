#include "DisplayHUD.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace view;
using namespace state;


namespace view{

DisplayHUD::DisplayHUD(int WIDTH, int LENGTH, Player player1, Player player2, Player player3, Player player4) {
    
    //init font and color
    Font font;
    if (!font.loadFromFile("../res/poppins.ttf")){
        cout << "Could not find the font " << "res/poppins.ttf" << endl;
    }

    Color red(181, 53, 53);
    Color green(70, 157, 70);
    Color blue(69, 98, 184);
    Color yellow(182, 148, 82);
    //-----------------------------------------
    int scrennGap = 30;
    int squareGap = 20;
    float scaleSquare = 0.7;
    int widthSquare = 180;
    int lengthSquare = 210;
    
    player1Square.loadFromFile("../res/square.png", IntRect(0, 0, 510, 210));
    spritePlayer1Square.setTexture(player1Square);
    spritePlayer1Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer1Square.setPosition(scrennGap, -80);


    player2Square.loadFromFile("../res/square.png", IntRect(400, 225, widthSquare, lengthSquare));
    spritePlayer2Square.setTexture(player2Square);
    spritePlayer2Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer2Square.setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, -50);

    player3Square.loadFromFile("../res/square.png", IntRect(0, 225, widthSquare, lengthSquare));
    spritePlayer3Square.setTexture(player3Square);
    spritePlayer3Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer3Square.setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, -50);

    player4Square.loadFromFile("../res/square.png", IntRect(200, 225, widthSquare, lengthSquare));
    spritePlayer4Square.setTexture(player4Square);
    spritePlayer4Square.setScale(Vector2f(scaleSquare, scaleSquare));
    spritePlayer4Square.setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, -50);
    
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
}

void DisplayHUD::display(sf::RenderTarget& target){
    
    target.draw(spritePlayer1Square);
    target.draw(spritePlayer2Square);
    target.draw(spritePlayer3Square);
    target.draw(spritePlayer4Square);
    
    target.draw(player1Name);
    target.draw(player2Name);
    target.draw(player3Name);
    target.draw(player4Name);
    
}
}