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
*   < Inserting global parameters >
*  
*/

#include "Data.h"

std::vector<Card> deck;
std::vector<Card> playerHand;
std::vector<Card> compHand;
std::vector<CardValue> playerSets;
std::vector<CardValue> compSets;

bool debug = false;
CardValue playerAskedValue;
CardValue compAskedValue;
