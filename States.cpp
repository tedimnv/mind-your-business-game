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
*   < The different states of the game >
*  
*/

#include "States.h"

std::ostream& operator << (std::ostream& o, States state)
{
    switch (state)
    {
        case States::START:
            o << "Start";
            break;   
        case States::DIAL:
            o << "Dial";
            break;
        case States::PLAYER_ASKS_CARD:
            o << "Player asks for a card";
            break;
        case States::COMP_BORROWS_2:
            o << "Computer borrows two cards from the deck";
            break;
        case States::PLAYER_BORROWS_1:
            o << "Player borrows a card from the deck";
            break;
        case States::COMP_ASKS_CARD:
            o << "Computer asks for a card from the player";
            break; 
        case States::PLAYER_BORROWS_2:
            o << "Player borrows two cards from the deck";
            break;
        case States::COMP_BORROWS_1:
            o << "Computer borrows a card from the deck";
            break;
        case States::PLAYER_ASKS_SET:
            o << "Player asks for a set from the computer";
            break;
        case States::COMP_ASKS_SET:
            o << "Computer asks for a set from the player";
            break;
        case States::FINISH:
            o << "Finish";
            break;

    }

    return o;
}