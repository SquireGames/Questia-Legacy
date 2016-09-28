#include <iostream>
#include <stdexcept>

#include "Application.h"

int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (std::exception& exc)
    {
        std::cout << std::endl << "Exception: " << exc.what() <<std::endl;
    }
}
