#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "States.h"
#include "Card.h"
#include "Data.h"

void PrintCards(std::vector<Card>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i];

        if(i < v.size()-1)
            std::cout << " ";
    }    

    std::cout << std::endl;
}

void PrintSets(std::vector<CardValue>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i];

        if(i < v.size()-1)
            std::cout << " ";
    }    

    std::cout << std::endl;
}


void PrintGameState()
{
    std::cout << "> Game state" << std::endl;
    std::cout << "> Deck: ";
    PrintCards(deck);

    std::cout << "> Player's hand: ";
    PrintCards(playerHand);

    std:: cout << "> Computer's hand: ";
    PrintCards(compHand);

    std::cout << "> Player's sets: ";
    PrintSets(playerSets);

    std::cout << "> Computer's sets: ";
    PrintSets(compSets);
    
}

bool HasCard(std::vector<Card>& v, Card& lookFor)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].colour == lookFor.colour && v[i].value == lookFor.value)
            return true;
    }

    return false;
}

void PopulateDeck()
{
    for(int i = 0; i < 52; i++)
    {
        Card card{};

        do
        {
            auto cardValue = static_cast<CardValue>(rand() % 13);
            auto colour = static_cast<Colour>(rand() % 4);
            card = Card{cardValue, colour};
        }
        while(HasCard(deck, card));
         
         
        deck.push_back(card);
    }


}

void PutDownSet(std::vector<Card>& hand, std::vector<CardValue>& set, CardValue value)
{
    int count{};

    for(auto it = hand.begin(); it != hand.end(); it++)
    {
        if(it->value == value)
            count++;
    }

    if(count != 4)
        return;  

    std::cout << "Putting down a set of " << value << std::endl;

    for(auto it = hand.begin(); it != hand.end();)
    {
        if(it->value == value)
            it = hand.erase(it);
        else
            it++;
    }

    set.push_back(value); 
}

bool MoveCardsIfPresent(std::vector<Card>& fromHand, std::vector<Card>& toHand, std::vector<CardValue>& toSet, CardValue lookFor)
{
    bool found = false;

    for(auto it = fromHand.begin(); it != fromHand.end();)
    {
        if(it->value == lookFor)
        {
            toHand.push_back(*it);
            it = fromHand.erase(it);

            PutDownSet(toHand, toSet, toHand.back().value);
            found = true;
        }
        else
        {
            it++;
        }
    }
    return found;
}

void MoveCard(std::vector<Card>& fromHand, std::vector<Card>& toHand, std::vector<CardValue>& toSet)
{
    if(fromHand.size() == 0)
    {
        std::cout << "Source depleated. " << std::endl; 
        return;
    }
    
    toHand.push_back(fromHand.back());
    fromHand.pop_back(); 

    std::cout << "Taking one card... " << std::endl;

    PutDownSet(toHand, toSet, toHand.back().value);
}

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

CardValue EnterCardValue()
{
    CardValue cardValue;
    
    while(true)
    {
        std::cout << "Enter card value(2,...10, J, Q, K, A): ";
        std::string inp;
        std::cin >> inp;
    
        if(inp == "2")
            cardValue = CardValue::Two;
        else if(inp == "3")
            cardValue = CardValue::Three;
        else if(inp == "4")
            cardValue = CardValue::Four;
        else if(inp == "5")
            cardValue = CardValue::Five;
        else if(inp == "6")
            cardValue = CardValue::Six;
        else if(inp == "7")
            cardValue = CardValue::Seven;
        else if(inp == "8")
            cardValue = CardValue::Eight;
        else if(inp == "9")
            cardValue = CardValue::Nine;
        else if(inp == "10")
            cardValue = CardValue::Ten;
        else if(inp == "J")
            cardValue = CardValue::Jack;
        else if(inp == "Q")
            cardValue = CardValue::Queen;
        else if(inp == "K")
            cardValue = CardValue::King;
        else if(inp == "A")
            cardValue = CardValue::Ace;
        else
        {
            std::cout << "Error: wrong input, please try again. " << std::endl;
            continue;
        }
            
        break;
    }
    return cardValue;
}


States PlayerAsksCard()
{
    std::cout << "Player asks for a card from the computer." << std::endl;

    auto askForValue = EnterCardValue();

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

    MoveCard(deck, playerHand, playerSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    return States::COMP_ASKS_CARD;
}

States CompAsksCard()
{
    std::cout << "Computer asks for a card from the player." << std::endl;
    
    auto askForValue = EnterCardValue();

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

    MoveCard(deck, compHand, compSets);

    if(compHand.size() == 0 && playerHand.size() == 0 && deck.size() == 0)
    {
        std::cout << "No more cards in play. " << std::endl;
        return States::PLAYER_ASKS_SET;
    }

    return States::PLAYER_ASKS_CARD;
}

bool MoveSetIfPresent(std::vector<CardValue>& fromSet, std::vector<CardValue>& toSet, CardValue lookFor)
{
    bool found = false;

    for(auto it = fromSet.begin(); it != fromSet.end();)
    {
        if(*it == lookFor)
        {
            toSet.push_back(*it);
            it = fromSet.erase(it);

            found = true;
        }
        else
        {
            it++;
        }
    }
    return found;
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
    std::cout << "Computer asks for a set from the player." << std::endl;

    auto askForValue = EnterCardValue();

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
        std::cout << "Current state: " << state << std::endl;
        PrintGameState();
        state = Transition(state);
        std::cout << "Changed to: " << state << std::endl;
    } 
    while(state != States::FINISH);
}
