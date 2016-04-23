#ifndef SERVER_H
#define SERVER_H

#include <SFML/System.hpp>
#include <iostream>

class Server
{
public:
    Server():
        count_update (0)
    {

    }
    ~Server();

    void update()
    {
        count_update++;
        std::cout << count_update << std::endl;
    }

private:

    int count_update;
};

#endif // SERVER_H
