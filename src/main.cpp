#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "fsm.hpp"
#include "design.hpp"
#include "animation.hpp"
#include "defines.h"

int main()
{
    srand(time(0)); //Initialize randomize
    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE_WIDHT, WINDOWSIZE_HEIGHT), "SlotPoker", sf::Style::Titlebar | sf::Style::Close);

    std::vector<sf::Texture> textures;
    textures.resize(NUM_OBJECTS);

    textures[0].loadFromFile("textures/start.png");
    textures[1].loadFromFile("textures/c_in.png");
    textures[2].loadFromFile("textures/c_out.png");
    textures[3].loadFromFile("textures/bet.png");
    textures[4].loadFromFile("textures/poker_cape.jpg");
    textures[5].loadFromFile("textures/pause.png");

    sf::Font verdana;
    verdana.loadFromFile("fonts/verdana.ttf");

    std::vector<int> infoValues;
    infoValues.resize(NUM_TEXT);

    sf::Texture animationTexture;
    sf::Texture animationPrize;

    animationTexture.loadFromFile("textures/cards_texture.png");
    animationPrize.loadFromFile("textures/poker_combinations.png");

    
    
    //Variables for the Game

    infoValues[0] = 0;  // Créditos
    infoValues[1] = 0;  // Créditos Out
    infoValues[2] = 0;  // Num. Plays
    infoValues[3] = 10; // Bet Value
    int button = 0;     //0 -> Start  1-> CreditIn  2-> CreditOut
    int fsm_state = 1;  //0-> Declare Values 1-> Menu  2-> During Game 3->Paused Game
    bool gameStart_Flag=false;
    bool gameFinished_Flag=false;
    bool pause_Flag = false;
    std::vector<int> prize(NUM_ROWS);
    int finalPrize=0;
    float deltaTime=0.0f;
    sf::Vector2i mousePos; // Check if touch a button

    //Class
    design design(textures, verdana); //Create Menu
    animation animation(&animationTexture,&animationPrize); //Create Animation of Cards Rolling
    sf::Clock clock;
    sf::Event event;

    //////////////////////////////

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        design.draw(window, infoValues, fsm_state);
        
        deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) //Event Ocurred
        {
            if (event.type == sf::Event::Closed) //App closed
                window.close();
        }

        switch (fsm_state) //FSM for the Game
        {
     
        case 1: //MENU

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    ; // Wait for release

                mousePos = sf::Mouse::getPosition(window);
                button = checkButtonPressed(mousePos);
                fsm_state=checkMenu(infoValues,button,design.betRectangle);
            }

            break;

        case 2: //During Game
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && pause_Flag == true) //Check if Start Button was released
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                button = checkButtonPressed(mousePos);
                if (button == 1) //Start Button released -> Continue Game
                    fsm_state = 3;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Check if a Button was clicked during game
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                button = checkButtonPressed(mousePos);
                if (button == 1)// Check if start Button was clicked during game
                    pause_Flag = true;
            }

            if (gameStart_Flag == false)
            {
                deltaTime = 0.0f; //Reset Timer for Roll
                gameStart_Flag = true;
                animation.drawInitialValues(window); //Draw 5 initial Values
            }
            else //Game is Going On
            {
                //12 Secs per spin pre-defined

                gameFinished_Flag = animation.updateValues(window, deltaTime);
                if (gameFinished_Flag == true)
                {
                    window.display(); //Display last Values
                    for (int i = 0; i < NUM_ROWS; i++)
                    {
                        prize[i] = checkPrize(animation.finalGameKeys[i]);
                    }
                    switch (infoValues[3])//Prize depending on Bet
                    {
                    case 10: 

                        finalPrize = prize[2];
                        break;
                    case 30:
                        finalPrize = prize[1] + prize[2] + prize[3];

                    case 50:

                        finalPrize = prize[0] + prize[1] + prize[2] + prize[3] + prize[4];
                        break;

                    default: //Error
                        break;
                    }

                    infoValues[0] += finalPrize;
                    infoValues[2]++;
                    fsm_state = 4;
                    animation.prizeAnimation(window,(infoValues[3]/10),prize); //Display prizes for 3 seconds
                    window.display();
                    sleep(3);
                }

                break;

            case 3: //Paused Game
                pause_Flag = false;
                animation.drawFinalValues(window);
                design.draw(window, infoValues, fsm_state);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Wait for Start button to Resume
                {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        ; // Wait for release

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    button = checkButtonPressed(mousePos);
                    if (button == 1)
                        fsm_state = 2;
                }
                break;

            case 4: //Final Game -> Wait to Start Again - Reroll

                

                button=0;
                animation.drawFinalValues(window);
                design.display_prizeInfo(window,finalPrize);
                

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Mouse pressed
                {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        ; // Wait for release

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    button = checkButtonPressed(mousePos);

                    fsm_state=checkMenu(infoValues,button,design.betRectangle);
                    if(fsm_state==1) //Not supossed to change state
                    {
                        fsm_state=4; //Stay at state 4
                    }
                    
                    if (button == 1) //New Game to Start
                    {
                        animation.resetValues();
                        button = 0;
                        gameStart_Flag = false;
                        gameFinished_Flag = false;
                        finalPrize = 0;
                        deltaTime = 0.0f;
                        std::fill(prize.begin(), prize.end(), 0);
                    }
                    if (button == 3) //Credit Out 
                    {
                        fsm_state=1; //Initial Menu
                        infoValues[2]=0; //Num plays Reset because user credit out
                        animation.resetValues();
                        button = 0;
                        gameStart_Flag = false;
                        gameFinished_Flag = false;
                        finalPrize = 0;
                        deltaTime = 0.0f;
                        std::fill(prize.begin(), prize.end(), 0);
                    }
                }
                break;

                break;
            default: //Error
                break;
            }
        }
        window.display();
    }
    return 0;
}
