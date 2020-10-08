#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "fsm.hpp"
#include "defines.h"


class animation
{

public:
    animation(sf::Texture* texture,sf::Texture* texture2); //Texture1 -> Cards | Texture2 -> Combinations
    ~animation();
    //Get 5 rows of 7 cards randomly, its used after the game start
    void drawInitialValues(sf::RenderWindow &window);
    //Function that update the values of the game (SPIN the Wheel)
    //Return True if game is over and false if game is still on going
    bool updateValues(sf::RenderWindow &window, float deltaTime);
    //Function that draw final values of the game
    void drawFinalValues(sf::RenderWindow &window);
    //Prize Animation on the window in each row, if it gets no prize nothing appear
    void prizeAnimation(sf::RenderWindow &window,int numPrizes, std::vector<int> prizes);
    //Reset Values/Restart the game
    void resetValues();

    

private:
//Get a new random vector of 7 cards to the wheel (1st Position)
void getRandomVector();

//Check the prize to show on the window
//return true if it is prize
//return false if it is no prize
bool prizeChecker(int prize);

public:

std::vector<std::vector<sf::Vector2i>> finalGameKeys;

private:

    
    std::vector<std::vector<sf::RectangleShape>> cardTemplate;
    std::vector<sf::RectangleShape> aux;
    sf::RectangleShape prizeRectangle;
    sf::Vector2u cardTextureSize;
    sf::Vector2u prizeTextureSize;
    float totalTime;
    float switchTime;
    bool  getKeys_Flag;
    int contKeys;
    

};