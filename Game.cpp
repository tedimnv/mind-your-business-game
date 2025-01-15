#include <iostream>
#include "Game.h"
#include "States.h"
#include "Card.h"

States Dial()
{
    std::cout << "Dialing..." << std::endl;
    return States::PLAYER_ASKS_CARD;
}

States PlayerAsksCard()
{
    std::cout << "Player asks for a card." << std::endl;
    std::cout << "Computer doesnt have a card." << std::endl;
    return States::PLAYER_BORROWS_1;
    //return States::PLAYER_TAKES_CARD;
}

States PlayerTakesCard()
{
    std::cout << "Player takes a card from the computer." << std::endl;
    return States::PLAYER_ASKS_CARD;
    //return States::COMP_BORROWS_2;
    //return States::PLAYER_ASKS_SET;
}

States CompBorrows2()
{
    std::cout << "Player borrows two cards from the deck." << std::endl;
    return States::PLAYER_ASKS_CARD;
}

States PlayerBorrowsCard()
{
    std::cout << "Player borrows a card from the deck." << std::endl;
    return States::COMP_ASKS_CARD;
}

States CompAsksCard()
{
    std::cout << "Computer asks for a card." << std::endl;
    std::cout << "Player gives a card." << std::endl;
    //return States::COMP_BORROWS_1;
    return States::COMP_TAKES_CARD;
}

States CompTakesCard()
{
    std::cout << "Computer takes a card from the player." << std::endl;
    //return States::COMP_ASKS_CARD;
    //return States::PLAYER_BORROWS_2;
    std::cout << "All cards have been put into sets" << std::endl;
    return States::COMP_ASKS_SET;
}

States PlayerBorrows2()
{
    std::cout << "Player takes two cards from the deck." << std::endl;
    return States::COMP_ASKS_CARD;
}

States CompBorrowsCard()
{
    std::cout << "Computer borrows a card from the deck." << std::endl;
    return States::PLAYER_ASKS_CARD;
}

States PlayerAsksSet()
{
    std::cout << "Player asks for a set." << std::endl;
    std::cout << "Computer gives a set." << std::endl;
    //return States::COMP_ASKS_SET;
    return States::PLAYER_TAKES_SET;
}

States PlayerTakesSet()
{
    std::cout << "Player takes set." << std::endl;
    //return States::PLAYER_ASKS_SET;
    std::cout << "Player has collected all sets." << std::endl;
    return States::FINISH;
}


States CompAsksSet()
{
    std::cout << "Computer asks for a set." << std::endl;
    std::cout << "Player doesnt have the set." << std::endl;
    return States::PLAYER_ASKS_SET;
    //return States::COMP_TAKES_SET;
}

States CompTakesSet()
{
    std::cout << "Computer takes set." << std::endl;
    return States::COMP_ASKS_SET;
    //return States::FINISH;
}

States Transition(States state)
{
    switch(state)
    {
        case States::START: 
            return States::DIAL;
        case States::DIAL:
            return Dial();
        case States::PLAYER_ASKS_CARD:
            return PlayerAsksCard();
        case States::PLAYER_TAKES_CARD:
            return PlayerTakesCard();
        case States::COMP_BORROWS_2:
            return CompBorrows2();
        case States::PLAYER_BORROWS_1:
            return PlayerBorrowsCard();
        case States::COMP_ASKS_CARD:
            return CompAsksCard();
        case States::COMP_TAKES_CARD:
            return CompTakesCard();
        case States::PLAYER_BORROWS_2:
            return PlayerBorrows2();
        case States::COMP_BORROWS_1:
            return CompBorrowsCard();
        case States::PLAYER_ASKS_SET:
            return PlayerAsksSet();
        case States::PLAYER_TAKES_SET:
            return PlayerTakesSet();
        case States::COMP_ASKS_SET:
            return CompAsksSet();
        case States::COMP_TAKES_SET:
            return CompTakesSet();
        case States::FINISH:
            std::cout << "Internal Error: Unexpected state States::FINISH" << std::endl;
            exit(1);
    }
}

void StartGame()
{
    auto state = States::START;

    do
    {
        std::cout << "Cuttent state: " << state << std::endl;
        state = Transition(state);
        std::cout << "Changed to: " << state << std::endl;
    } 
    while(state != States::FINISH);
}
