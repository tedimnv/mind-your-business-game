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
*   < Transitions between the different states of the game >
*  
*/

#include <iostream>
#include <cstdlib>
#include "Card.h"
#include "Data.h"
#include "Transitions.h"
#include "Utilities.h"

States Dial()
{
    std::cout << "Dialing..." << std::endl;

    PopulateDeck();

    for(int i = 0; i < 6; i++)
    {
        MoveCard(deck, playerHand, playerSets);
        MoveCard(deck, compHand, compSets);
    }

    return States::PLAYER_ASKS_CARD;
}

States PlayerAsksCard()
{
    std::cout << "Player asks for a card from the computer." << std::endl;

    auto askForValue = EnterCardValue();

    playerAskedValue = askForValue;

    if(!MoveCardsIfPresent(compHand, playerHand, playerSets, askForValue))
    {
        std::cout << "Computer doesnt have a card. " << std::endl;
        return States::PLAYER_BORROWS_1;
    }

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    if(compHand.size() == 0)
    {
        std::cout << "Computer has finished his cards. " << std::endl;
        return States::COMP_BORROWS_2;
    }

    std::cout << "Computer has given the player all the cards with the requested value " << std::endl;
    return States::PLAYER_ASKS_CARD;
}

States CompBorrows2()
{
    std::cout << "Computer borrows two cards from the deck." << std::endl;

    MoveCard(deck, compHand, compSets);
    MoveCard(deck, compHand, compSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    return States::PLAYER_ASKS_CARD;
}

States PlayerBorrowsCard()
{
    std::cout << "Player borrows a card from the deck." << std::endl;

    auto borrowedCard = deck.back();

    MoveCard(deck, playerHand, playerSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }
     
    if(borrowedCard.value == playerAskedValue)
    {
        std::cout << "Player drew a card of the same value they asked for. They get another turn." << std::endl;
        return States::PLAYER_ASKS_CARD;
    }

    return States::COMP_ASKS_CARD;
}

States CompAsksCard()
{    
    std::cout << "Computer asks for a card from the player." << std::endl;
    
    auto askForValue = CompAsksValue();

    compAskedValue = askForValue;  

    std::cout << "Computer has asked for " << askForValue << std::endl;

    if(!MoveCardsIfPresent(playerHand, compHand, compSets, askForValue))
    {
        std::cout << "Player doesnt have a card. " << std::endl;
        return States::COMP_BORROWS_1;
    }

    if(playerHand.size() == 0 && compHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::COMP_ASKS_SET;
    }

    if(playerHand.size() == 0)
    {
        std::cout << "Player has finished his cards. " << std::endl;
        return States::PLAYER_BORROWS_2;
    }

    std::cout << "Player has given the computer all the cards with the requested value " << std::endl;
    return States::COMP_ASKS_CARD;
}

States PlayerBorrows2()
{
    std::cout << "Player takes two cards from the deck." << std::endl;

    MoveCard(deck, playerHand, playerSets);
    MoveCard(deck, playerHand, playerSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    return States::COMP_ASKS_CARD;
}

States CompBorrowsCard()
{
    std::cout << "Computer borrows a card from the deck." << std::endl;

    auto borrowedCard = deck.back(); 

    MoveCard(deck, compHand, compSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    if (borrowedCard.value == compAskedValue)
    {
        std::cout << "Computer drew a card of the same value it asked for. It gets another turn." << std::endl;
        return States::COMP_ASKS_CARD;
    }

    return States::PLAYER_ASKS_CARD;
}

States PlayerAsksSet()
{
    std::cout << "Player asks for a set." << std::endl;

    auto askForValue = EnterCardValue();

    if(!MoveSetIfPresent(compSets, playerSets, askForValue))
    {
        std::cout << "Computer doesn't have the set requested" << std::endl;
        return States::COMP_ASKS_SET;
    }

    std::cout << "Computer gives a set to the player." << std::endl;

    if(compSets.size() == 0)
    {
        std::cout << "Player has collected all sets." << std::endl;
        return States::FINISH;
    }
    
    return States::PLAYER_ASKS_SET;
}

States CompAsksSet()
{
    std::cout << "Computer asks for a set from the player: ";

    auto askForValue = CompAsksValue();

    std::cout << askForValue << std::endl;

    if(!MoveSetIfPresent(playerSets, compSets, askForValue))
    {
        std::cout << "Player doesn't have the set requested" << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    std::cout << "Player gives a set to the computer." << std::endl;

    if(playerSets.size() == 0)
    {
        std::cout << "Computer has collected all sets." << std::endl;
        return States::FINISH;
    }
    
    return States::COMP_ASKS_SET;
}
