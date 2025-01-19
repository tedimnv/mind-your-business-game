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
*   < The different actions in each state of the game >
*  
*/

#include "Utilities.h"

void PrintCards(std::vector<Card>& v)
{
    if(v.size() == 0)
        std::cout << "0 cards";

    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i];

        if(i < v.size()-1)
            std::cout << " ";
    }    
    
    std::cout << std::endl;
}

void PrintDeck()
{
    if(debug)
        return PrintCards(deck);
    
    if(deck.size() <= 3)
        std::cout << deck.size();
    else if(deck.size() < 10)
        std::cout << "few";
    else 
        std::cout << "many";
    
    std::cout << " cards" << std::endl;
}

void PrintCompHand()
{
    if(debug)
        return PrintCards(compHand);

    std::cout << compHand.size() << " cards" << std::endl;
}

void PrintSets(std::vector<CardValue>& v)
{
    if(!debug)
    {
        std::cout << v.size() << " sets" << std::endl;
        return;
    }

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
    PrintDeck();

    std::cout << "> Player's hand: ";
    PrintCards(playerHand);

    std:: cout << "> Computer's hand: ";
    PrintCompHand();

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

CardValue CompAsksValue()
{
    CardValue cardValue = static_cast<CardValue>(rand() % 13);
                
    return cardValue;    
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
