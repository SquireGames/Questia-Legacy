#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

class TimeManager
{
    public:
        TimeManager(unsigned char _hour, unsigned char _minute);
        ~TimeManager();

        void update();

        void setTimeStep(unsigned char _timeStep)                   {timeStep = _timeStep;}
        void setTime(unsigned char _hour, unsigned char _minute)    {hour = _hour; minute = _minute;}
        void setTime(int _minute)
        {
            minute = _minute % 60;
            hour = (_minute - minute) / 60;
        }
        int getTime() {return (minute + (hour * 60));}

        unsigned char getHour()         {return hour;}
        unsigned char getMinute()       {return minute;}
        float         getDecimalTime()  {return (static_cast<float>(hour) + ((static_cast<float>(minute) / 60.f)));}



    private:
        unsigned char hour;
        unsigned char minute;

        unsigned char timeStep;
};

#endif // TIMEMANAGER_H
