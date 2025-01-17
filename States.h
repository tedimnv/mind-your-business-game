#pragma once

#include <iostream>

enum States
{
    START,
    DIAL,
    PLAYER_ASKS_CARD,
    COMP_BORROWS_2,
    PLAYER_BORROWS_1,
    COMP_ASKS_CARD,
    PLAYER_BORROWS_2,
    COMP_BORROWS_1,
    PLAYER_ASKS_SET,
    COMP_ASKS_SET,
    FINISH
};

std::ostream& operator << (std::ostream& o, States state);