#pragma once

#include <iostream>
#include <cstdlib>
#include "States.h"
#include "Card.h"
#include "Data.h"

CardValue EnterCardValue();
CardValue CompAsksValue();
void PrintCards(std::vector<Card>& v);
void PrintSets(std::vector<CardValue>& v);
void PrintGameState();
bool HasCard(std::vector<Card>& v, Card& lookFor);
void PopulateDeck();
void PutDownSet(std::vector<Card>& hand, std::vector<CardValue>& set, CardValue value);
void MoveCard(std::vector<Card>& fromHand, std::vector<Card>& toHand, std::vector<CardValue>& toSet);
bool MoveCardsIfPresent(std::vector<Card>& fromHand, std::vector<Card>& toHand, std::vector<CardValue>& toSet, CardValue lookFor);
bool MoveSetIfPresent(std::vector<CardValue>& fromSet, std::vector<CardValue>& toSet, CardValue lookFor);


