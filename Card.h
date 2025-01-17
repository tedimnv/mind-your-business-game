#pragma once

#include <iostream>

enum Colour
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum CardValue
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

struct Card
{
    CardValue value;
    Colour colour;
};

std::ostream& operator << (std::ostream& o, Colour colour);
std::ostream& operator << (std::ostream& o, CardValue value);
std::ostream& operator << (std::ostream& o, Card card);
