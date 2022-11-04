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

    Player player1("Jonah", PlayerRed);
    Player player2("Nicolas", PlayerBlue);
    Player player3("Xu", PlayerOrange);
    Player player4("Stephane", PlayerWhite);

    player1.victoryPoints = 10;
    player1.knightNumber = 3;

    DisplayHUD HUD(WIDTH, LENGTH, player1, player2, player3, player4);

    cout << "Player : " << player1.name << endl;
    cout << "Victory Point : " << player1.victoryPoints << endl;


    if (!tileMap.load("../res/tiles.png", sf::Vector2u(114, 131), state.map.grid, 7, 7))
        return -1;
    tileMap.setOrigin((8*114)/2, 719/2);
    tileMap.setPosition(WIDTH/2, 50 + LENGTH/2);
    tileMap.setScale(Vector2f(0.9, 0.9));


    
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
        //Color sea(55, 233, 254);
        //window.clear(sea);

        // c'est ici qu'on dessine tout
        //HUD.display(window);
        window.draw(tileMap);
        HUD.render(window, player1, player2, player3, player4);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}