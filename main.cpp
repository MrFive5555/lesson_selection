#include "creator.h"
#include "UI.h"

//#define DISALLOW_MAIN
#ifndef DISALLOW_MAIN

int main()
{
    install();
    UI::welcome();
    UI::LogIn();
    UI::goodBye();
}

#endif // !DISALLOW_MAIN

