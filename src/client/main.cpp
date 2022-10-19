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
    Exemple exemple;
    exemple.setX(53);
    
    cout << "It works !" << endl;

        // création de la fenêtre
    RenderWindow window(VideoMode(800, 600), "Catan");
    window.setVerticalSyncEnabled(true);

    Image icon;
    if(!icon.loadFromFile("catan.png"))
        EXIT_FAILURE;
 

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
        // window.draw(...);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}
