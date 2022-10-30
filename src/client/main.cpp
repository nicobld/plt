#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;
using namespace sf;

int main(int argc,char* argv[])
{

    cout << "===============| Catan |===============" << endl;

    // création de la fenêtre
    int WIDTH = 1280;
    int LENGTH = 720;
    RenderWindow window(VideoMode(WIDTH, LENGTH), "Catan");

    Player* player1 = new Player("Jonah", PlayerRed);
    Player* player2 = new Player("Nicolas", PlayerBlue);
    Player* player3 = new Player("Xu", PlayerOrange);
    Player* player4 = new Player("Stephane", PlayerWhite);

    cout << "Player : " << player1->name << endl;
    cout << "Victory Point : " << player1->victoryPoints << endl;

    GameCards* gameCards = new GameCards();

    // Font font;
    // font.loadFromFile("res/poppins.ttf");

    // Texture map;
    
    // map.loadFromFile("res/map.png", IntRect(0, 0, 1850, 1450));
    // Sprite spriteMap(map);
    // spriteMap.setScale(Vector2f(0.4f, 0.4f));
    // spriteMap.setOrigin(1850/2, 1450/2);
    // spriteMap.setPosition(WIDTH/2, LENGTH/2);

    // Texture redSquare, greenSquare, blueSquare, yellowSquare;
    // int scrennGap = 30;
    // int squareGap = 20;
    // float scaleSquare = 0.7;

    // redSquare.loadFromFile("res/square.png", IntRect(0, 0, 510, 210));
    // Sprite spriteRedSquare(redSquare);
    // spriteRedSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    // spriteRedSquare.setPosition(scrennGap, -80);

    // int widthSquare = 180;
    // int lengthSquare = 210;
    // greenSquare.loadFromFile("res/square.png", IntRect(400, 225, widthSquare, lengthSquare));
    // Sprite spriteGreenSquare(greenSquare);
    // spriteGreenSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    // spriteGreenSquare.setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, -50);

    // blueSquare.loadFromFile("res/square.png", IntRect(0, 225, widthSquare, lengthSquare));
    // Sprite spriteBlueSquare(blueSquare);
    // spriteBlueSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    // spriteBlueSquare.setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, -50);

    // yellowSquare.loadFromFile("res/square.png", IntRect(200, 225, widthSquare, lengthSquare));
    // Sprite spriteYellowSquare(yellowSquare);
    // spriteYellowSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    // spriteYellowSquare.setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, -50);

    // Color* red = new Color(181, 53, 53);
    // Color* green = new Color(70, 157, 70);
    // Color* blue = new Color(69, 98, 184);
    // Color* yellow = new Color(182, 148, 82);

    // Text player1Name;
    // player1Name.setFont(font);
    // player1Name.setString(player1->getName());
    // player1Name.setCharacterSize(24);
    // player1Name.setFillColor(*red);
    // player1Name.setPosition(scrennGap + 25, 15);

    // Text player2Name;
    // player2Name.setFont(font);
    // player2Name.setString(player2->getName());
    // player2Name.setCharacterSize(18);
    // player2Name.setFillColor(*green);
    // player2Name.setOrigin((player2Name.getGlobalBounds().width)/2, 0);
    // player2Name.setPosition((spriteGreenSquare.getGlobalBounds().width)/2 + spriteGreenSquare.getPosition().x , 15);

    // Text player3Name;
    // player3Name.setFont(font);
    // player3Name.setString(player3->getName());
    // player3Name.setCharacterSize(18);
    // player3Name.setFillColor(*blue);
    // player3Name.setOrigin((player3Name.getGlobalBounds().width)/2, 0);
    // player3Name.setPosition((spriteBlueSquare.getGlobalBounds().width)/2 + spriteBlueSquare.getPosition().x , 15);

    // Text player4Name;
    // player4Name.setFont(font);
    // player4Name.setString(player4->getName());
    // player4Name.setCharacterSize(18);
    // player4Name.setFillColor(*yellow);
    // player4Name.setOrigin((player4Name.getGlobalBounds().width)/2, 0);
    // player4Name.setPosition((spriteYellowSquare.getGlobalBounds().width)/2 + spriteYellowSquare.getPosition().x , 15);




    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == Event::Closed)
                window.close();
        }

        // effacement de la fenêtre en noir
        window.clear(Color::Black);

        // c'est ici qu'on dessine tout

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}