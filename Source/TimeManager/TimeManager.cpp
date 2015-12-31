#include "TimeManager.h"

TimeManager::TimeManager(unsigned char _hour, unsigned char _minute):
    hour(_hour)
    , minute(_minute)
    , timeStep (20)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::update()
{
    minute += timeStep;
    if(minute >= 60)
    {
        minute-= 60;
        hour++;
    }
    // Hours 0-23, add 1 for real time
    if(hour >= 24)
    {
        hour-=24;
    }
}
