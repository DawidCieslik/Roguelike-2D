#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"

//Projekt PK4 - Dawid Cieœlik

int main()
{
    try {
        Menu main_menu;
        main_menu.main_menu();
    }
    catch (std::exception error)
    {
        std::cout << error.what() << std::endl;
        return 1;
    }
    return 0;
}