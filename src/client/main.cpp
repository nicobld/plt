#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;
using namespace sf;

int main(int argc,char* argv[])
{

    cout << "===============| Catan |===============" << endl;

    // création de la fenêtre
    RenderWindow window(VideoMode(800, 600), "Catan");

    Player* player = new Player("Player Test");

    cout << "Player : " << player->getName() << endl;
    cout << "Victory Point : " << player->victoryPoints << endl;



    Texture texture;
    texture.loadFromFile("res/terrains.png", IntRect(0, 0, 256, 256));

    Sprite sprite(texture);
    sprite.setScale(Vector2f(0.5f, 0.5f));


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
        window.clear(Color::Blue);

        // c'est ici qu'on dessine tout
        // window.draw(...);
        window.draw(sprite);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}