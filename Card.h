#pragma once

enum Colour
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

struct Card
{
    int value;
    Colour colour;
};