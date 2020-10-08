
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "defines.h"

//Check Menu function
//Options-> Start Game, Credit Out, Credit In, Change the bet)
int checkMenu(std::vector<int>& infoValues, int button,sf::RectangleShape& betRectangle);
//Check Which button was pressed (Return -> Start(1) / Credit In(2) / Credit Out(3) / Other Pixel in the window(0))
int checkButtonPressed(sf::Vector2i mousePos);

//Function that Choose the Final Key of the started Game
void gameCardChoose(std::vector<sf::Vector2i> &key);
//Check which prize to give
//Return the value of the prize
int checkPrize(std::vector<sf::Vector2i> &key);

// Possible Combinations

bool checkPAIR(std::vector<sf::Vector2i> &key);
bool checkDPAIR(std::vector<sf::Vector2i> &key);
bool checkTRIO(std::vector<sf::Vector2i> &key);
bool checkSTRAIGHT(std::vector<sf::Vector2i> &key);
bool checkFLUSH(std::vector<sf::Vector2i> &key);
bool checkFULLHOUSE(std::vector<sf::Vector2i> &key);
bool checkPOKER(std::vector<sf::Vector2i> &key);
bool checkFLUSHSTRAIGHT(std::vector<sf::Vector2i> &key);
bool checkROYALSTRAIGHTFLUSH(std::vector<sf::Vector2i> &key); //Jackpot

///////////////////////////