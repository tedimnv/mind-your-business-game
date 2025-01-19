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
*   < Main function - Starting the game >
*  
*/

#include <cstdlib>
#include "StateMachine.h"
#include "Data.h"

int main(int argc, char* argv[])
{
    srand(time(0));

    
    if(argc == 2)
    {

        if(!strcmp(argv[1], "--debug"))
            debug = true;
    }

    StartGame();

    return 0;
}