#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System/Time.hpp>


// Fin test SFML

#include <state.h>
#include <view.h>
#include <engine.h>

// #define ALLBOTS

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
    window.setPosition(sf::Vector2i(1920/2 -width/2, 1080/2 - height/2));
    window.setVerticalSyncEnabled(true);
    
    
    if(argc == 1){
        cout << "hello" << endl;
        cout << "render" << endl;
        cout << "engine" << endl;
        cout << "random_ai" << endl;
        return 0;
    }
    

    if(!strncmp(argv[1], "hello", 5)){
        cout << "===============| Catan |===============" << endl;
    }
    else if(!strncmp(argv[1], "render", 6)){
        cout << "===============| Catan |===============" << endl;

            State state;
            state.players.push_back(Player("Jonah", PlayerRed));
            state.players.push_back(Player("Nicolas", PlayerBlue));
            state.players.push_back(Player("Xu", PlayerYellow));
            state.players.push_back(Player("Stephane", PlayerGreen));
            Engine engine(&state);
            StateView stateView(&state, &engine);


        // state.players.at(0).developments.push_back(Development(Knight));
        // state.players.at(0).developments.push_back(Development(VictoryPointsCard));
        // state.players.at(0).developments.push_back(Development(Monopoly));

        // state.players.at(1).developments.push_back(Development(Knight));

        state.players.at(0).resources.at(0).number = 2;
        state.players.at(0).resources.at(1).number = 3;
        state.players.at(0).resources.at(4).number = 1;
        state.players.at(1).resources.at(4).number = 1;
        state.players.at(3).resources.at(4).number = 5;
        state.players.at(0).knightNumber = 3;
        state.players.at(0).hasLargestArmy = 1;
        
        Color sea(148, 240, 248);

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
            //stateView.displayHUD->render(window);
            stateView.render(window);

            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }
    }

    else if(!strncmp(argv[1], "engine", 6)){
        
        State state;
        state.players.push_back(Player("Jonah", PlayerRed));
        state.players.push_back(Player("Nicolas", PlayerBlue));
        state.players.push_back(Player("Xu", PlayerYellow));
        state.players.push_back(Player("Stephane", PlayerGreen));
        Engine engine(&state);
        StateView stateView(&state, &engine);


        int c = 2;

        std::string inString; 

        Color sea(148, 240, 248);

        sf::Mouse mouse;
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
                            stateView.clickedObjects(event.mouseButton.x, event.mouseButton.y);
                            stateView.handleClick(event.mouseButton.x, event.mouseButton.y);
                        break;
                    }
                }

                else if (event.type == sf::Event::MouseButtonReleased){
                    if (event.mouseButton.button == sf::Mouse::Left){
                            //stateView.clickedObjects(event.mouseButton.x, event.mouseButton.y);
                            stateView.releasedObjects(event.mouseButton.x, event.mouseButton.y);
                            stateView.reloadTroisButtons();
                            std::cout << "displayState : " << stateView.displayState[stateView.viewPlayer] << std::endl;
                    }
                }
                if(stateView.displayState[0] == CHOOSING_NAME){
                    if (event.type == sf::Event::TextEntered){
                        if (event.text.unicode < 128){
                            //std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                            stateView.updateChooseName(static_cast<char>(event.text.unicode));
                        }
                }
                }
                else{
                    if (event.type == sf::Event::KeyPressed){
                        if (event.key.code == sf::Keyboard::V){
                                std::cout << "V\n";
                                stateView.viewPlayer = (state::PlayerColor) ((stateView.viewPlayer + 1) % 4);
                                stateView.reloadTroisButtons();
                                stateView.updatePlayerTurnDisplay();
                                stateView.updateClickableObjects(state.turn);
                        }
                    }
                }

                

                    stateView.handPlayers[state.turn].hoverOneCard(mouse.getPosition(window).x, mouse.getPosition(window).y);
                    //stateView.updateChooseName();
            }

            // effacement de la fenêtre en noir
            window.clear(sea);

            /* Terminal */
            // std::getline(cin, inString);
            // engine.addSerializedCommand(inString);

            // c'est ici qu'on dessine tout
            engine.update();
            stateView.render(window);
            
            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }
    }


    else if(!strncmp(argv[1], "random_ai", 9)){
        std::vector<std::string> namePlayers = {"a", "b"};
        State* state = new State(namePlayers);
        Engine engine(state);
        StateView stateView (state, &engine);

        state->players[0].resources[0].number = 100;
        state->players[0].resources[1].number = 100;
        state->players[0].resources[2].number = 100;
        state->players[0].resources[3].number = 100;
        state->players[0].resources[4].number = 100;

        state->players[1].resources[0].number = 100;
        state->players[1].resources[1].number = 100;
        state->players[1].resources[2].number = 100;
        state->players[1].resources[3].number = 100;
        state->players[1].resources[4].number = 100;

        // stateView.displayState[0] = view::STAND_BY;
        // stateView.displayState[1] = view::STAND_BY;
        // stateView.displayState[2] = view::STAND_BY;
        // stateView.displayState[3] = view::STAND_BY;

        // stateView.clickedObjects(0, 0);
        // stateView.handleClick(0, 0);
#ifdef ALLBOTS
        stateView.home = 0;
#endif


        std::string inString; 

        Color sea(148, 240, 248);

        sf::Mouse mouse;
        // on fait tourner le programme tant que la fenêtre n'a pas été fermée
        while (window.isOpen())
        {
            // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                
                if(!(state->players[state->turn].isBot)){

                    if (event.type == sf::Event::MouseButtonPressed){
                        if (event.mouseButton.button == sf::Mouse::Left){
                            stateView.clickedObjects(event.mouseButton.x, event.mouseButton.y);
                            stateView.handleClick(event.mouseButton.x, event.mouseButton.y);
                            break;
                        }
                    }

                    else if (event.type == sf::Event::MouseButtonReleased){
                        if (event.mouseButton.button == sf::Mouse::Left){
                                //stateView.clickedObjects(event.mouseButton.x, event.mouseButton.y);
                                stateView.releasedObjects(event.mouseButton.x, event.mouseButton.y);
                                stateView.reloadTroisButtons();
                                std::cout << "displayState : " << stateView.displayState[stateView.viewPlayer] << std::endl;
                        }
                    }

                if(stateView.displayState[0] == CHOOSING_NAME){
                    if (event.type == sf::Event::TextEntered){
                        if (event.text.unicode < 128){
                            //std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                            stateView.updateChooseName(static_cast<char>(event.text.unicode));
                        }
                }
                }
                else{
                    if (event.type == sf::Event::KeyPressed){
                        if (event.key.code == sf::Keyboard::V){
                                std::cout << "V\n";
                                stateView.viewPlayer = (state::PlayerColor) ((stateView.viewPlayer + 1) % 4);
                                stateView.reloadTroisButtons();
                                stateView.updatePlayerTurnDisplay();
                                stateView.updateClickableObjects(state->turn);
                        }
                    }
                }

            
                    stateView.handPlayers[state->turn].hoverOneCard(mouse.getPosition(window).x, mouse.getPosition(window).y);

                }
                
                else {       //si c'est un bot
                    // std::cout << "BOT\n";
                    // engine.randomBot.generateCommand(state, &engine);
                    // stateView.dice->update(engine.saveThrDiceCmd->dice1 + engine.saveThrDiceCmd->dice2, engine.saveThrDiceCmd->dice1, engine.saveThrDiceCmd->dice2);
                    // stateView.updateClickableObjects(state->turn);
                }

            }


            // effacement de la fenêtre en noir
            window.clear(sea);

            /* Terminal */
            // std::getline(cin, inString);
            // engine.addSerializedCommand(inString);

            if(state->players[state->turn].isBot){
                std::cout << "CURRENT BOT " << state->players[state->turn].playerColor << std::endl;
                engine.randomBot.generateCommand(state, &engine);
                stateView.viewPlayer = (PlayerColor) (((int)stateView.viewPlayer + 1) % 4);
                stateView.displayState[stateView.viewPlayer] = view::STAND_BY;
                stateView.reloadTroisButtons();
                stateView.updatePlayerTurnDisplay();
                stateView.updateClickableObjects(state->turn);
                //sf::sleep(sf::seconds(0.1f));
#ifdef ALLBOTS
                stateView.displayState[0] = view::STAND_BY;
                stateView.displayState[1] = view::STAND_BY;
                stateView.displayState[2] = view::STAND_BY;
                stateView.displayState[3] = view::STAND_BY;
#endif
            }

            // c'est ici qu'on dessine tout
            engine.update();
            stateView.render(window);
            
            // fin de la frame courante, affichage de tout ce qu'on a dessiné
            window.display();
        }
    }

    return 0;
}