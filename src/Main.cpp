#if !(__GNUC__ == 6 && \
     __GNUC_MINOR__ == 1 && \
     __GNUC_PATCHLEVEL__ == 0)
     #warning Wrong compiler version. Use g++ 6.1.0 (DW2).
#endif // __GNUC__

//#if (DEBUGMODE == 1)

#include <iostream>
#include <stdexcept>

#include "Questia/Application.h"

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
