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

    Player player1("Jonah", PlayerRed);
    Player player2("Nicolas", PlayerBlue);
    Player player3("Xu", PlayerOrange);
    Player player4("Stephane", PlayerWhite);

    cout << "Player : " << player1.name << endl;
    cout << "Victory Point : " << player1.victoryPoints << endl;

    
    Texture map;
    
    map.loadFromFile("res/map.png", IntRect(0, 0, 1850, 1450));
    Sprite spriteMap(map);
    spriteMap.setScale(Vector2f(0.4f, 0.4f));
    spriteMap.setOrigin(1850/2, 1450/2);
    spriteMap.setPosition(WIDTH/2, LENGTH/2);
    
    


    DisplayHUD HUD(WIDTH, LENGTH, player1, player2, player3, player4);

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
        window.draw(spriteMap);
        HUD.display(window);

        window.draw(HUD.spritePlayer1Square);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}