#include "animation.hpp"

//Public Functions //

animation::animation(sf::Texture *texture, sf::Texture *texture2)
{
    cardTemplate.resize(NUM_ROWS, std::vector<sf::RectangleShape>(KEY_ELEMENTS));
    finalGameKeys.resize(NUM_ROWS, std::vector<sf::Vector2i>(KEY_ELEMENTS));
    aux.resize(KEY_ELEMENTS);
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        aux[i].setSize(sf::Vector2f(CARD_SIZE_X, CARD_SIZE_Y));
        aux[i].setTexture(texture);
        for (int j = 0; j < NUM_ROWS; j++)

        {
            cardTemplate[j][i].setSize(sf::Vector2f(CARD_SIZE_X, CARD_SIZE_Y));
            cardTemplate[j][i].setTexture(texture);
        }
    }

    //Get each card size in the image
    cardTextureSize = texture->getSize();

    cardTextureSize.x /= NUM_VALUES;
    cardTextureSize.y /= NUM_SUITS;
    ////////////////////////////////////
    //Prize Texture ///

    prizeRectangle.setTexture(texture2);
    prizeTextureSize = texture2->getSize();
    prizeTextureSize.x /= 1;
    prizeTextureSize.y /= NUM_PRIZES;

    /////////////////////////////////

    switchTime = INITIAL_SWITCH_TIME; //Initial switch time that is going to increment 1ms each time the image rolls
    totalTime = 0.0;
    contKeys = 0;
    getKeys_Flag = false;
}

animation::~animation()
{
}

void animation::drawInitialValues(sf::RenderWindow &window)
{
    std::vector<sf::Vector2i> gameKey(KEY_ELEMENTS);
    for (int j = 0; j < NUM_ROWS; j++) //Get the cards for 5 initial rows
    {
        gameCardChoose(gameKey); // Get 7 cards for the Row
        for (int i = 0; i < KEY_ELEMENTS; i++)
        {

            cardTemplate[j][i].setTextureRect(sf::IntRect(cardTextureSize.x * gameKey[i].x, cardTextureSize.y * gameKey[i].y, cardTextureSize.x, cardTextureSize.y));
            cardTemplate[j][i].setPosition(22.f + ((CARD_SIZE_X + 2) * i), 25.f + ((CARD_SIZE_Y + 2) * j));
            window.draw(cardTemplate[j][i]);
        }
    }
}

bool animation::updateValues(sf::RenderWindow &window, float deltaTime)
{

    totalTime += deltaTime; //totalTime is the same in every computer, not depending of pc specs

    if (totalTime >= switchTime) //Time for Next Roll
    {

        totalTime -= switchTime; // ~0
        switchTime = switchTime + SWITCH_TIME_INCREMENT;
        if (switchTime >= (FINAL_TIME - 0.4f) && switchTime < (FINAL_TIME - 0.39f))
        {
            getKeys_Flag = true; //Get The Keys
        }
        getRandomVector();

        for (int j = NUM_ROWS - 1; j >= 0; j--) //  From older values to the newest
                                                //Because we want the values on the previous vector
            for (int i = 0; i < KEY_ELEMENTS; i++)
            {
                if (j == 0) //First Card Vector needs new values
                {
                    cardTemplate[j][i].setTextureRect(aux[i].getTextureRect());
                }
                else // Rest Card Vectors go down a Row except last one that disappear
                {
                    cardTemplate[j][i].setTextureRect(cardTemplate[j - 1][i].getTextureRect());
                }
                window.draw(cardTemplate[j][i]);
            }
        if (switchTime >= FINAL_TIME) //Spin is Over
        {
            return true;
        }
    }
    else //Waiting for Next Roll
    {
        for (int j = 0; j < NUM_ROWS; j++)
            for (int i = 0; i < KEY_ELEMENTS; i++)
            {
                window.draw(cardTemplate[j][i]);
            }
    }
    return false;
}

void animation::drawFinalValues(sf::RenderWindow &window)
{
    for (int j = 0; j < NUM_ROWS; j++)
        for (int i = 0; i < KEY_ELEMENTS; i++)
        {
            window.draw(cardTemplate[j][i]);
        }
}

void animation::prizeAnimation(sf::RenderWindow &window, int numPrizes, std::vector<int> prizes)
{
    bool prizeBool=false;
    switch (numPrizes)
    {
    case 1: //One Row

    prizeRectangle.setSize(sf::Vector2f(150, 25));
    prizeRectangle.setPosition(sf::Vector2f(210,255 ));
    prizeBool=prizeChecker(prizes[2]);
    if(prizeBool==true)window.draw(prizeRectangle);
    break;

    case 3: //Three Rows
    for(int i=0;i<3;i++)
    {

    prizeRectangle.setSize(sf::Vector2f(150, 25));
    prizeRectangle.setPosition(sf::Vector2f(210,(CARD_SIZE_Y+2)*(i+1)+55 ));
    prizeBool=prizeChecker(prizes[i+1]);
    if(prizeBool==true)window.draw(prizeRectangle);
    }
    break;   

    case 5: //5 Rows

    for(int i=0;i<5;i++)
    {

    prizeRectangle.setSize(sf::Vector2f(150, 25));
    prizeRectangle.setPosition(sf::Vector2f(210,(CARD_SIZE_Y+2)*(i)+55 ));
    prizeBool=prizeChecker(prizes[i]);
    if(prizeBool==true)window.draw(prizeRectangle);
    }

    break;
    
    default:
        break;
    }
}

void animation::resetValues()
{
    switchTime = INITIAL_SWITCH_TIME; //Initial switch time that is going to increment 1ms each time the image rolls
    totalTime = 0.0;
    contKeys = 0;
    getKeys_Flag = false;
}

//Private Functions //

void animation::getRandomVector()
{
    std::vector<sf::Vector2i> gameKey(KEY_ELEMENTS);
    gameCardChoose(gameKey);

    for (int k = 0; k < KEY_ELEMENTS; k++)
    {
        if (getKeys_Flag == true)
        {

            finalGameKeys[contKeys][k].x = gameKey[k].x;
            finalGameKeys[contKeys][k].y = gameKey[k].y;
        }

        aux[k].setTextureRect(sf::IntRect(cardTextureSize.x * gameKey[k].x, cardTextureSize.y * gameKey[k].y, cardTextureSize.x, cardTextureSize.y));
    }
    if (getKeys_Flag == true)
        contKeys++;
}


bool animation::prizeChecker(int prize)
{
    switch(prize)
    {
        case JACKPOT:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 0, prizeTextureSize.x, prizeTextureSize.y));

            break;
        case STRAIGHTFLUSH:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 1,prizeTextureSize.x, prizeTextureSize.y));

            break;
        case POKER:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 2,prizeTextureSize.x, prizeTextureSize.y));
            break;
        case FULLHOUSE:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 3,prizeTextureSize.x, prizeTextureSize.y));

            break;
        case FLUSH:

            prizeRectangle.setTextureRect(sf::IntRect(0,  prizeTextureSize.y * 4,prizeTextureSize.x, prizeTextureSize.y));
            break;
        case STRAIGHT:

            prizeRectangle.setTextureRect(sf::IntRect(0,  prizeTextureSize.y * 5,prizeTextureSize.x, prizeTextureSize.y));
            break;
        case TRIO:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 6,prizeTextureSize.x, prizeTextureSize.y));
            break;
        case DPAIR:

            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 7,prizeTextureSize.x, prizeTextureSize.y));
            break;
        case ONEPAIR:
            prizeRectangle.setTextureRect(sf::IntRect(0, prizeTextureSize.y * 8,prizeTextureSize.x, prizeTextureSize.y));
            break;

        default: //No Prize
        return false;
            break;
  
    }
    return true;
}