#include "design.hpp"

design::~design()
{
}

design::design(std::vector<sf::Texture> &textures, sf::Font &verdana)
{

    start_button.setSize(sf::Vector2f(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT));
    creditIn_button.setSize(sf::Vector2f(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT));
    creditOut_button.setSize(sf::Vector2f(BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT));
    bet_button.setSize(sf::Vector2f(BUTTON_SIZE_HEIGHT, BUTTON_SIZE_HEIGHT));
    cape.setSize(sf::Vector2f(WINDOWSIZE_WIDHT, WINDOWSIZE_HEIGHT));
    pause.setSize(sf::Vector2f(400, 120));

    start_button.setTexture(&textures[0]);
    creditIn_button.setTexture(&textures[1]);
    creditOut_button.setTexture(&textures[2]);
    bet_button.setTexture(&textures[3]);
    cape.setTexture(&textures[4]);
    pause.setTexture(&textures[5]);

    start_button.setPosition(START_BUTTON_POSITION_X, START_BUTTON_POSITION_Y);
    creditIn_button.setPosition(START_BUTTON_POSITION_X + 110.f, START_BUTTON_POSITION_Y);
    creditOut_button.setPosition(START_BUTTON_POSITION_X + 220.f, START_BUTTON_POSITION_Y);
    bet_button.setPosition(START_BUTTON_POSITION_X + 330.f, START_BUTTON_POSITION_Y);
    cape.setPosition(0.f, 0.f);
    pause.setPosition(85.f, 220.f);
    this->verdana = verdana;

    text.resize(NUM_TEXT);

    defaultText();

    //Bet Rectangle Grey
    betRectangle.setFillColor(sf::Color::White);
    betRectangle.setSize(sf::Vector2f(WINDOWSIZE_WIDHT, CARD_SIZE_Y));
    betRectangle.setPosition(sf::Vector2f(0, INITIAL_CARD_PIXEL_Y + ((CARD_SIZE_Y + 2) * 2)));
}

void design::draw(sf::RenderWindow &window, std::vector<int> &infoValues, int fsm_state)
{
    switch (fsm_state)
    {
    case 0: //Reset
    case 1: //Menu
        window.draw(cape);
        window.draw(start_button);
        window.draw(creditIn_button);
        window.draw(creditOut_button);
        window.draw(bet_button);

        break;

    case 2: //During Game
        window.draw(start_button);
        window.draw(creditIn_button);
        window.draw(creditOut_button);
        window.draw(bet_button);
        window.draw(betRectangle);

        break;

    case 3: //Pause
        window.draw(start_button);
        window.draw(creditIn_button);
        window.draw(creditOut_button);
        window.draw(bet_button);
        window.draw(pause);
        break;

    case 4: //Final Game
        window.draw(start_button);
        window.draw(creditIn_button);
        window.draw(creditOut_button);
        window.draw(bet_button);
        window.draw(betRectangle);
        break;

    default: //Error
        break;
    }

    display_info(infoValues);

    for (int i = 0; i < NUM_TEXT; i++)
    {
        window.draw(text[i]);
    }
}

void design::defaultText() //Define Default TYpe of text
{

    for (int i = 0; i < NUM_TEXT; i++)
    {

        text[i].setFont(verdana);
        text[i].setCharacterSize(12);
        text[i].setColor(sf::Color::White);
        text[i].setStyle(sf::Text::Bold);
    }
}

void design::writeOnBoard(std::ostringstream &string, int position)
{
    std::string aux = string.str();
    text[position].setString(aux);
}

void design::display_info(std::vector<int> &infoValues)
{

    text[0].setPosition(TEXT_POSITION_X, TEXT_POSITION_Y);
    text[1].setPosition(TEXT_POSITION_X, TEXT_POSITION_Y + 20.f);
    text[2].setPosition(TEXT_POSITION_X, TEXT_POSITION_Y + 40.f);
    text[3].setPosition(TEXT_POSITION_X, TEXT_POSITION_Y + 60.f);

    defaultText();

    std::ostringstream aux;

    aux << "Credits = " << infoValues[0];
    writeOnBoard(aux, 0);
    aux.str("");
    aux.clear();

    aux << "Credits Out = " << infoValues[1];
    writeOnBoard(aux, 1);
    aux.str("");
    aux.clear();

    aux << "Num. Plays = " << infoValues[2];
    writeOnBoard(aux, 2);
    aux.str("");
    aux.clear();

    aux << "Bet = " << infoValues[3] << " Credits";
    writeOnBoard(aux, 3);
    aux.str("");
    aux.clear();
}

void design::display_prizeInfo(sf::RenderWindow &window,int prize) //In the Bottom part of the Window after the game
{
    sf::Text prizeText;
    std::ostringstream aux;

    prizeText.setFont(verdana);
    prizeText.setCharacterSize(30);
    prizeText.setColor(sf::Color::White);
    prizeText.setStyle(sf::Text::Bold);
    prizeText.setPosition(10,610);

    aux << "Prize = " << prize << " Credits";
    std::string auxi = aux.str();
    prizeText.setString(auxi);
  

    window.draw(prizeText);


}