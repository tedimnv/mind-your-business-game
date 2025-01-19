/*
*   Solution to course project # 8
*   Introduction to programming course
*   Faculty of Mathematics and Informatics of Sofia University
*   Winter semester 2024/2025
*  
*   @autor Teodora Mineva 
*   @idnumber 2MI0600537 
*   @compiler clang++ (MacBook) 
*
*   < All of the different card values and card colors and creating each card from the deck >
*  
*/

#include "Card.h"

std::ostream& operator << (std::ostream& o, Colour colour)
{
    switch (colour)
    {
        case Colour::Hearts:
            o << "H";
            break;
        case Colour::Diamonds:
            o << "D";
            break;
        case Colour::Clubs:
            o << "C";
            break;
        case Colour::Spades:
            o << "S";
            break;
    }

    return o;
}

std::ostream& operator << (std::ostream& o, CardValue value)
{
    switch (value)
    {
        case CardValue::Ace:
            o << "A";
            break;   
        case CardValue::Two:
            o << "2";
            break;
        case CardValue::Three:
            o << "3";
            break;
        case CardValue::Four:
            o << "4";
            break;
        case CardValue::Five:
            o << "5";
            break;
        case CardValue::Six:
            o << "6";
            break;
        case CardValue::Seven:
            o << "7";
            break;
        case CardValue::Eight:
            o << "8";
            break;
        case CardValue::Nine:
            o << "9";
            break;
        case CardValue::Ten:
            o << "10";
            break;
        case CardValue::Jack:
            o << "J";
            break;
        case CardValue::Queen:
            o << "Q";
            break;
        case CardValue::King:
            o << "K";
            break;
    }

    return o;
}

std::ostream& operator << (std::ostream& o, Card card)
{
    return o << card.value << card.colour;
}