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
*   < State machine - the structure of the game >
*  
*/


#include "StateMachine.h"
#include "Transitions.h"
#include "Utilities.h"
#include "Data.h"

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
        case States::COMP_BORROWS_2:
            return CompBorrows2();
        case States::PLAYER_BORROWS_1:
            return PlayerBorrowsCard();
        case States::COMP_ASKS_CARD:
            return CompAsksCard();
        case States::PLAYER_BORROWS_2:
            return PlayerBorrows2();
        case States::COMP_BORROWS_1:
            return CompBorrowsCard();
        case States::PLAYER_ASKS_SET:
            return PlayerAsksSet();
        case States::COMP_ASKS_SET:
            return CompAsksSet();
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
        if(debug)
            std::cout << "Current state: " << state << std::endl;

        PrintGameState();
        state = Transition(state);
            
        if(debug)    
            std::cout << "Changed to: " << state << std::endl;
    } 
    while(state != States::FINISH);
    
}

