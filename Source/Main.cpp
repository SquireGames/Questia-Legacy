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
        /*D*/   std::cout<<std::endl<<"Exception: "<<exc.what()<<std::endl;
    }
}

///WHEN YOU GO BACK TO THIS:
//figure out why ResourceManager is not allowing access to textureMap
