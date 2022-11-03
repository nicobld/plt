#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


// Fin test SFML

#include <state.h>
#include <view.h>

using namespace std;
using namespace state;
using namespace view;
using namespace sf;

int main(int argc,char* argv[])
{

    cout << "===============| Catan |===============" << endl;

    // création de la fenêtre
    int WIDTH = 1280;
    int LENGTH = 720;
    RenderWindow window(VideoMode(WIDTH, LENGTH), "Catan");

    State state;
    TileMap tileMap;


    const int level[] = {
        0, 1, 2,
        2, 3, 4,
        5, 4, 1
    };

    Player player1("Jonah", PlayerRed);
    Player player2("Nicolas", PlayerBlue);
    Player player3("Xu", PlayerOrange);
    Player player4("Stephane", PlayerWhite);

    DisplayHUD HUD(WIDTH, LENGTH, player1, player2, player3, player4);

    cout << "Player : " << player1.name << endl;
    cout << "Victory Point : " << player1.victoryPoints << endl;


    if (!tileMap.load("../res/tiles.png", sf::Vector2u(114, 131), state.map.grid, 7, 7))
        return -1;


    
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
        //HUD.display(window);
        window.draw(tileMap);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}