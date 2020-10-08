#include "fsm.hpp"

int checkMenu(std::vector<int> &infoValues, int button, sf::RectangleShape& betRectangle)
{
    switch (button)
    {
    case 1: //Start Button
        if (infoValues[0] >= infoValues[3])
        {
            infoValues[0] -= infoValues[3];
            return 2; // Game Started
        }
        break;
    case 2:                                 //Credit In Button
        infoValues[0] = infoValues[0] + 10; // Increment num. of credits
        break;

    case 3: //Credit Out Button
        infoValues[1] += infoValues[0];
        infoValues[0] = 0;
        break;

    case 4: //Bet Button
        switch (infoValues[3])
        {
        case 10: //One Row (Middle)
            infoValues[3] = 30;

            betRectangle.setSize(sf::Vector2f(WINDOWSIZE_WIDHT, (CARD_SIZE_Y + 2) * 3));
            betRectangle.setPosition(sf::Vector2f(0, INITIAL_CARD_PIXEL_Y + ((CARD_SIZE_Y + 2))));

            break;

        case 30: // Three Rows (Middle)
            infoValues[3] = 50;

            betRectangle.setSize(sf::Vector2f(WINDOWSIZE_WIDHT, (CARD_SIZE_Y + 2) * 5));
            betRectangle.setPosition(sf::Vector2f(0, INITIAL_CARD_PIXEL_Y));

            break;

        case 50: // Five Rows (All Rows)
            infoValues[3] = 10;

            betRectangle.setSize(sf::Vector2f(WINDOWSIZE_WIDHT, CARD_SIZE_Y));
            betRectangle.setPosition(sf::Vector2f(0, INITIAL_CARD_PIXEL_Y + ((CARD_SIZE_Y + 2) * 2)));

            break;

        default:
            break;
        }

        break;

        break;
    default: //None of this buttons was clicked
        break;
    }

    return 1; //Stay at same state (1-Menu or 4-Final)
}

int checkButtonPressed(sf::Vector2i mousePos)
{
    //Click Start Button
    if (mousePos.x > START_BUTTON_POSITION_X &&
        mousePos.x < (START_BUTTON_POSITION_X + BUTTON_SIZE_WIDTH) &&
        mousePos.y > START_BUTTON_POSITION_Y &&
        mousePos.y < (START_BUTTON_POSITION_Y + BUTTON_SIZE_HEIGHT))
        return 1;

    //Click Credit In Button
    if (mousePos.x > (START_BUTTON_POSITION_X + 110.f) &&
        mousePos.x < (START_BUTTON_POSITION_X + BUTTON_SIZE_WIDTH + 110.f) &&
        mousePos.y > START_BUTTON_POSITION_Y &&
        mousePos.y < (START_BUTTON_POSITION_Y + BUTTON_SIZE_HEIGHT))
        return 2;

    //Click Credit Out Button
    if (mousePos.x > (START_BUTTON_POSITION_X + 220.f) &&
        mousePos.x < (START_BUTTON_POSITION_X + BUTTON_SIZE_WIDTH + 220.f) &&
        mousePos.y > START_BUTTON_POSITION_Y &&
        mousePos.y < (START_BUTTON_POSITION_Y + BUTTON_SIZE_HEIGHT))
        return 3;

    //Click Bet Button
    if (mousePos.x > (START_BUTTON_POSITION_X + 330.f) &&
        mousePos.x < (START_BUTTON_POSITION_X + BUTTON_SIZE_HEIGHT + 330.f) &&
        mousePos.y > START_BUTTON_POSITION_Y &&
        mousePos.y < (START_BUTTON_POSITION_Y + BUTTON_SIZE_HEIGHT))
        return 4;

    return 0; //None of these buttons clicked
}

void gameCardChoose(std::vector<sf::Vector2i> &key) //Non Repetitive Cards
{
    std::vector<int> aux(KEY_ELEMENTS);
    int auxi = 0;
    bool flag = true;
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        flag = true;
        while (flag == true) // Wait for a not repetitive number
        {
            flag = false;
            auxi = rand() % 52; // Number between 0-51;
            for (int j = 0; j < i; j++)
            {

                if (auxi == aux[j])
                    flag = true;
            }
        }
        aux[i] = auxi;

        //Transform into a matrix of the Cards with value(x) and suit(y)
        //X - Between 0-12 || 13-25 || 25 - 38 || 39 - 51
        //Y - Clubs - 0 || Spades - 1 || Hearts - 2 || Diamonds - 3

        if (auxi <= 12) // Clubs
        {
            key[i].x = auxi;
            key[i].y = 0;
        }
        if (auxi >= 13 && auxi <= 25) //Spades
        {
            key[i].x = auxi - 13;
            key[i].y = 1;
        }
        if (auxi >= 26 && auxi <= 38) //Hearts
        {
            key[i].x = auxi - 26;
            key[i].y = 2;
        }
        if (auxi >= 39 && auxi <= 51) //Diamonds
        {
            key[i].x = auxi - 39;
            key[i].y = 3;
        }
    }
}

int checkPrize(std::vector<sf::Vector2i> &key) //Biggest Prize to lower because can be both true
{
    //The Probability of each event and the reward given was not studied
    if (checkROYALSTRAIGHTFLUSH(key))
        return JACKPOT;
    if (checkFLUSHSTRAIGHT(key))
        return STRAIGHTFLUSH;
    if (checkPOKER(key))
        return POKER;
    if (checkFULLHOUSE(key))
        return FULLHOUSE;
    if (checkFLUSH(key))
        return FLUSH;
    if (checkSTRAIGHT(key))
        return STRAIGHT;
    if (checkTRIO(key))
        return TRIO;
    if (checkDPAIR(key))
        return DPAIR;
    if (checkPAIR(key))
        return ONEPAIR;

    return 0;
}

bool checkPAIR(std::vector<sf::Vector2i> &key)
{
    int count = 0;
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        for (int j = 0; j < KEY_ELEMENTS; j++)
        {
            if (j > i)
            {
                if (key[i].x == key[j].x) //Par encontrado
                {
                    count++;
                }
            }
        }
    }
    if (count >= 1)
    {
        return true;
    }
    return false;
}

bool checkDPAIR(std::vector<sf::Vector2i> &key)
{
    int count = 0;
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        for (int j = 0; j < KEY_ELEMENTS; j++)
        {
            if (j > i)
            {
                if (key[i].x == key[j].x) //Par encontrado
                {
                    count++;
                }
            }
        }
    }
    if (count >= 2)
    {
        return true;
    }
    return false;
}

bool checkTRIO(std::vector<sf::Vector2i> &key)
{
    int count = 0;
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        for (int j = 0; j < KEY_ELEMENTS; j++)
        {

            if (j > i)
            {
                if (key[i].x == key[j].x) //Par encontrado
                {
                    count++;
                }
            }
        }

        if (count >= 2)
        {
            return true;
        }
        else
        {
            count = 0;
        }
    }
    return false;
}

bool checkSTRAIGHT(std::vector<sf::Vector2i> &key)
{

    if (key[4].x - key[3].x == 1 && key[3].x - key[2].x == 1 && key[2].x - key[1].x == 1 && (key[1].x - key[0].x == 1 || key[1].x - key[0].x == 9)) // 9 because of ace being 1
        return true;

    return false;
}
bool checkFLUSH(std::vector<sf::Vector2i> &key)
{
    for (int i = 1; i < KEY_ELEMENTS; i++)
    {
        if (key[0].y != key[i].y)
            return false;
    }
    return true;
}
bool checkPOKER(std::vector<sf::Vector2i> &key)
{
    int count = 0;

    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        for (int j = 0; j < KEY_ELEMENTS; j++)
        {

            if (j > i)
            {
                if (key[i].x == key[j].x) //Par encontrado
                {
                    count++;
                }
            }
        }

        if (count >= 3)
        {
            return true;
        }
        else
        {
            count = 0;
        }
    }
    return false;
}

bool checkFULLHOUSE(std::vector<sf::Vector2i> &key)
{
    if (checkTRIO(key) == false)
        return false;

    int count = 0;
    for (int i = 0; i < KEY_ELEMENTS; i++)
    {
        for (int j = 0; j < KEY_ELEMENTS; j++)
        {
            if (j != i)
            {
                if (key[i].x == key[j].x) //Par encontrado
                {
                    count++;
                }
            }
        }
        if (count == 1)
            return true;
        count = 0;
    }

    return false;
}
bool checkFLUSHSTRAIGHT(std::vector<sf::Vector2i> &key)
{

    if (checkFLUSH(key) && checkSTRAIGHT(key))
        return true;

    return false;
}
bool checkROYALSTRAIGHTFLUSH(std::vector<sf::Vector2i> &key)
{
    if (checkFLUSHSTRAIGHT(key) && key[0].x == 1)
        return true;
    return false;
}
