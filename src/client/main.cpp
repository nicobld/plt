#include <iostream>
#include <string.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>


// Fin test SFML

#include <state.h>
#include <engine.h>
#include <view.h>

using namespace std;
using namespace state;
using namespace view;
using namespace sf;
using namespace engine;

int main(int argc,char* argv[])
{
    if(argc == 1){
        cout << "hello" << endl;
        cout << "render" << endl;
        cout << "engine" << endl;
        return 0;
    }

    if(!strncmp(argv[1], "hello", 5)){
        cout << "===============| Catan |===============" << endl;
        return 0;
    }
    else if(!strncmp(argv[1], "render", 6)){
        cout << "===============| Catan |===============" << endl;

        int width = 1280;
        int height = 720;
        sf::RenderWindow window(sf::VideoMode(width, height), "Catan");

        State state;

        state.players.push_back(Player("Jonah", PlayerRed));
        state.players.push_back(Player("Nicolas", PlayerBlue));
        state.players.push_back(Player("Xu", PlayerYellow));
        state.players.push_back(Player("Stephane", PlayerGreen));

        state.players.at(0).developments.push_back(Development(Knight));
        state.players.at(0).developments.push_back(Development(VictoryPointsCard));
        state.players.at(0).developments.push_back(Development(Monopoly));

        state.players.at(0).resources.at(0).number = 2;
        state.players.at(0).resources.at(1).number = 3;
        state.players.at(0).resources.at(4).number = 1;
        state.players.at(1).resources.at(4).number = 1;
        state.players.at(3).resources.at(4).number = 5;
        
        state.players.at(0).knightNumber = 3;
        state.players.at(0).hasLargestArmy = 1;

        StateView stateView(state);

        
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
            window.draw(*stateView.tileMap);
            stateView.displayHUD->render(window, state.players[0], state.players[1], state.players[2], state.players[3]);
            stateView.render(window);

            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }

    return 0;
    }

// test d'engine sur la pioche
    else if(strcmp(argv[1], "eng") == 0){

        State* state;
        Engine engine;

        DrawCardCommand drawCommand(state->turn);

        if(drawCommand.execute(state) ==  true){
            cout << "oui" << endl;
        }
        
    }

    else if(!strncmp(argv[1], "engine", 6)){

        cout << "===============| Catan |===============" << endl;
    }
}