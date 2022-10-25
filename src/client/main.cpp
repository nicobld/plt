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

    Player* player = new Player("Player Test");

    cout << "Player : " << player->getName() << endl;
    cout << "Victory Point : " << player->victoryPoints << endl;



    Texture terrain, map;
    
    terrain.loadFromFile("res/terrains.png", IntRect(0, 0, 256, 256));
    Sprite spriteTerrain(terrain);
    spriteTerrain.setScale(Vector2f(0.5f, 0.5f));
    
    map.loadFromFile("res/map.png", IntRect(0, 0, 1850, 1450));
    Sprite spriteMap(map);
    spriteMap.setScale(Vector2f(0.4f, 0.4f));
    spriteMap.setOrigin(1850/2, 1450/2);
    spriteMap.setPosition(WIDTH/2, LENGTH/2);

    Texture redSquare, greenSquare, blueSquare, yellowSquare;
    int scrennGap = 30;
    int squareGap = 20;
    float scaleSquare = 0.7;

    redSquare.loadFromFile("res/square.png", IntRect(0, 0, 510, 210));
    Sprite spriteRedSquare(redSquare);
    spriteRedSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    spriteRedSquare.setPosition(scrennGap, -80);

    int widthSquare = 180;
    int lengthSquare = 210;
    greenSquare.loadFromFile("res/square.png", IntRect(400, 225, widthSquare, lengthSquare));
    Sprite spriteGreenSquare(greenSquare);
    spriteGreenSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    spriteGreenSquare.setPosition(WIDTH - scrennGap - 3*(widthSquare*scaleSquare) - 2*squareGap, -50);

    blueSquare.loadFromFile("res/square.png", IntRect(0, 225, widthSquare, lengthSquare));
    Sprite spriteBlueSquare(blueSquare);
    spriteBlueSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    spriteBlueSquare.setPosition(WIDTH - scrennGap - 2*(widthSquare*scaleSquare) - squareGap, -50);

    yellowSquare.loadFromFile("res/square.png", IntRect(200, 225, widthSquare, lengthSquare));
    Sprite spriteYellowSquare(yellowSquare);
    spriteYellowSquare.setScale(Vector2f(scaleSquare, scaleSquare));
    spriteYellowSquare.setPosition(WIDTH - scrennGap -widthSquare*scaleSquare, -50);





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
        //window.draw(spriteTerrain);
        window.draw(spriteMap);
        window.draw(spriteRedSquare);
        window.draw(spriteGreenSquare);
        window.draw(spriteBlueSquare);
        window.draw(spriteYellowSquare);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}