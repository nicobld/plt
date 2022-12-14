#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>


// Fin test SFML

#include <state.h>
#include <view.h>
#include <engine.h>



using namespace std;
using namespace state;
using namespace view;
using namespace sf;
using namespace engine;



int main(int argc, char* argv[])
{
    int width = 1280;
    int height = 720;

    srand(time(NULL));

    // sf::Music music;

    // music.openFromFile("../res/One-Bard-Band.ogg");

    // music.setLoop(true);
    // music.play();

    sf::RenderWindow window(sf::VideoMode(width, height), "Catan");
    State state;

    state.turn = PlayerRed;
    state.gameState = NORMAL_STATE;
    
    state.players.push_back(Player("Jonah", PlayerRed));
    state.players.push_back(Player("Nicolas", PlayerBlue));
    state.players.push_back(Player("Xu", PlayerYellow));
    state.players.push_back(Player("Stephane", PlayerGreen));

    StateView stateView(state);

    if(argc == 1){
        cout << "hello" << endl;
        cout << "render" << endl;
        cout << "engine" << endl;
        return 0;
    }
    

    if(!strncmp(argv[1], "hello", 5)){
        cout << "===============| Catan |===============" << endl;
    }
    else if(!strncmp(argv[1], "render", 6)){
        cout << "===============| Catan |===============" << endl;

        state.players.at(0).developments.push_back(Development(Knight));
        state.players.at(0).developments.push_back(Development(VictoryPointsCard));
        state.players.at(0).developments.push_back(Development(Monopoly));

        state.players.at(1).developments.push_back(Development(Knight));

        state.players.at(0).resources.at(0).number = 2;
        state.players.at(0).resources.at(1).number = 3;
        state.players.at(0).resources.at(4).number = 1;
        
        state.players.at(1).resources.at(4).number = 1;
        
        state.players.at(3).resources.at(4).number = 5;
        
        state.players.at(0).knightNumber = 3;
        state.players.at(0).hasLargestArmy = 1;

        StateView stateView(state);

        

        Color sea(148, 240, 248);

        Texture focusTexture;
        focusTexture.loadFromFile("../res/focus.png");
        Sprite *focus = new Sprite(focusTexture);
        focus->setScale(Vector2f(0.9, 0.9));
        focus->setOrigin(focus->getGlobalBounds().width/2, focus->getGlobalBounds().height/2);
        focus->setPosition(width/2, height/2);

        state.players.at(0).hasLargestArmy = 0;
        state.players.at(1).hasLargestArmy = 1;

       
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
            //window.clear(Color::Black);
            window.clear(sea);

            // c'est ici qu'on dessine tout
            //HUD.display(window);
            window.draw(*stateView.tileMap);
            window.draw(*focus);
            stateView.displayHUD->render(window);
            stateView.render(window);
            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }
    }

    else if(!strncmp(argv[1], "engine", 6)){
        Engine engine(&state);
        int c = 2;

        std::string inString; 

        Color sea(148, 240, 248);

        state.players[PlayerRed].resources[Lumber].number = 0;
        state.players[PlayerBlue].resources[Brick].number = 5;

        Texture focusTexture;
        focusTexture.loadFromFile("../res/focus.png");
        Sprite *focus = new Sprite(focusTexture);
        focus->setScale(Vector2f(0.9, 0.9));
        focus->setOrigin(focus->getGlobalBounds().width/2, focus->getGlobalBounds().height/2);
        focus->setPosition(width/2, height/2);
        
        // on fait tourner le programme tant que la fenêtre n'a pas été fermée
        while (window.isOpen())
        {
            // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                window.close();

                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        if(event.mouseButton.x > stateView.displayHUD->buttonPassTurn->getPosition().x &&
                            event.mouseButton.y > stateView.displayHUD->buttonPassTurn->getPosition().y &&
                            event.mouseButton.x < stateView.displayHUD->buttonPassTurn->getPosition().x + stateView.displayHUD->buttonPassTurn->getGlobalBounds().width &&
                            event.mouseButton.y < stateView.displayHUD->buttonPassTurn->getPosition().y + stateView.displayHUD->buttonPassTurn->getGlobalBounds().height){
                                stateView.displayHUD->buttonPassTurn->setTextureRect(IntRect(175*4 + 200, 258, 199, 48));
                                stateView.displayHUD->passTurn->setCharacterSize(22);
                                stateView.displayHUD->passTurn->setOrigin(stateView.displayHUD->passTurn->getGlobalBounds().width/2, stateView.displayHUD->passTurn->getGlobalBounds().height/2);
                                stateView.displayHUD->passTurn->setPosition(stateView.displayHUD->buttonPassTurn->getPosition().x + stateView.displayHUD->buttonPassTurn->getGlobalBounds().width/2, stateView.displayHUD->buttonPassTurn->getGlobalBounds().height/2 + stateView.displayHUD->buttonPassTurn->getPosition().y - 8);
                        }
                        else {
                        }
                    }

                }
                if (event.type == sf::Event::MouseButtonReleased){
                    if (event.mouseButton.button == sf::Mouse::Left){
                        std::cout << "the left button was released" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        if(event.mouseButton.x > stateView.displayHUD->buttonPassTurn->getPosition().x &&
                            event.mouseButton.y > stateView.displayHUD->buttonPassTurn->getPosition().y &&
                            event.mouseButton.x < stateView.displayHUD->buttonPassTurn->getPosition().x + stateView.displayHUD->buttonPassTurn->getGlobalBounds().width &&
                            event.mouseButton.y < stateView.displayHUD->buttonPassTurn->getPosition().y + stateView.displayHUD->buttonPassTurn->getGlobalBounds().height){
                                stateView.displayHUD->buttonPassTurn->setTextureRect(IntRect(175*4 + 0, 258, 199, 48));
                                stateView.displayHUD->passTurn->setCharacterSize(24);
                                stateView.displayHUD->passTurn->setOrigin(stateView.displayHUD->passTurn->getGlobalBounds().width/2, stateView.displayHUD->passTurn->getGlobalBounds().height/2);
                                stateView.displayHUD->passTurn->setPosition(stateView.displayHUD->buttonPassTurn->getPosition().x + stateView.displayHUD->buttonPassTurn->getGlobalBounds().width/2, stateView.displayHUD->buttonPassTurn->getGlobalBounds().height/2 + stateView.displayHUD->buttonPassTurn->getPosition().y - 8);
                        }
                    }
                }
            }

            // effacement de la fenêtre en noir
            window.clear(sea);

            // if (c == 2){
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,1),Position(3,2)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,3),Position(3,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,3),Position(4,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(4,3),Position(4,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,3),Position(4,3)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(4,3),Position(5,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(3,5)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(4,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(3,5)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(2,5)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(2,4)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(3,4),Position(2,3)}));
            //     engine.addCommand(new PlaceRoadCommand(PlayerRed,{Position(2,3),Position(2,4)}));


            //     std::vector<state::PlayerColor> playerAsks = {PlayerBlue, PlayerGreen};
            //     engine.addCommand(new ExchangeRequestCommand(Resource(state::Lumber, 2), Resource(state::Brick, 1), state::PlayerRed, playerAsks));

            //     engine.addCommand(new ExchangeResponseCommand(Resource(state::Lumber, 2), Resource(state::Brick, 1), state::PlayerRed, PlayerBlue, true));

            // }
            // c = 3;


            /* Terminal */
            std::getline(cin, inString);
            engine.addSerializedCommand(inString);

            engine.update();

            window.draw(*stateView.tileMap);
            window.draw(*focus);
            stateView.displayHUD->render(window);
            stateView.render(window);

            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }
    }

    return 0;
}