#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "defines.h"

class design
{

public:
    design(std::vector<sf::Texture> &textures, sf::Font &verdana);
    ~design();

    // Draw the design of the game depending on the state of the game
    void draw(sf::RenderWindow &window, std::vector<int> &infoValues,int fsm_state); 
    //Write the values (Credits/CreditsOut/NumPlays) in the string and set the position
    void display_info(std::vector<int> &infoValues);
    //Display the Final prize in the play
    void display_prizeInfo(sf::RenderWindow &window,int prize);


public:

sf::RectangleShape betRectangle;

private:
    sf::RectangleShape start_button;
    sf::RectangleShape creditIn_button;
    sf::RectangleShape creditOut_button;
    sf::RectangleShape bet_button;
    sf::RectangleShape cape;
    sf::RectangleShape pause;
    std::vector<sf::Text> text;

    sf::Font verdana;
    void defaultText(); //Default text type
    void writeOnBoard(std::ostringstream &string, int position); 
};
