#include "EntityManager/Entity/Collidable/Entity_Collidable.h"
#include <iostream>

Entity_Collidable::Entity_Collidable()
{

}

Entity_Collidable::~Entity_Collidable()
{

}

bool Entity_Collidable::check_Collision_SAT(std::vector<sf::Vector2f>& objectVector_1, std::vector<sf::Vector2f>& objectVector_2)
{
    /// saves every axis
    std::vector<float> normalVector;
    for(unsigned int it = 0; it != objectVector_1.size(); it++)
    {
        float normal;
        if(it == objectVector_1.size() - 1)
        {
            normal = -1 * (objectVector_1[it].x - objectVector_1[0].x) / (objectVector_1[it].y-objectVector_1[0].y);
        }
        else
        {
            normal = -1 * (objectVector_1[it].x - objectVector_1[it+1].x) / (objectVector_1[it].y-objectVector_1[it+1].y);
        }
        normalVector.push_back(normal);
    }
    for(unsigned int it = 0; it != objectVector_2.size(); it++)
    {
        float normal;
        if(it == objectVector_2.size() - 1)
        {
            normal = -1 * (objectVector_2[it].x - objectVector_2[0].x) / (objectVector_2[it].y-objectVector_2[0].y);
        }
        else
        {
            normal = -1 * (objectVector_2[it].x - objectVector_2[it+1].x) / (objectVector_2[it].y-objectVector_2[it+1].y);
        }
        normalVector.push_back(normal);
    }

    ///cycle through every normal
    for(unsigned int it_normal = 0; it_normal != normalVector.size(); it_normal++)
    {
        /// finds dot product
        float poly1_dot[objectVector_1.size()];
        float poly2_dot[objectVector_2.size()];

        for(unsigned int it = 0; it != objectVector_1.size(); it++)
        {
            poly1_dot[it] = (objectVector_1[it].x + objectVector_1[it].y * normalVector[it_normal]);
        }
        for(unsigned int it = 0; it != objectVector_2.size(); it++)
        {
            poly2_dot[it] = (objectVector_2[it].x + objectVector_2[it].y * normalVector[it_normal]);
        }

        ///min, max
        float poly1_min = poly1_dot[0],
              poly1_max = poly1_dot[0],
              poly2_min = poly2_dot[0],
              poly2_max = poly2_dot[0];
        for(unsigned int it = 0; it !=  objectVector_1.size(); it++)
        {
            if(poly1_dot[it] > poly1_max)
            {
                poly1_max = poly1_dot[it];
            }
            else if(poly1_dot[it] < poly1_min)
            {
                poly1_min = poly1_dot[it];
            }
        }
        for(unsigned int it = 0; it !=  objectVector_2.size(); it++)
        {
            if(poly2_dot[it] > poly2_max)
            {
                poly2_max = poly2_dot[it];
            }
            else if(poly2_dot[it] < poly2_min)
            {
                poly2_min = poly2_dot[it];
            }
        }
        if(poly1_min > poly2_max || poly1_max < poly2_min)
        {
            return false;
        }
    }
    return true;
}
