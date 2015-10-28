#ifndef STRUCT_CHARACTER_H
#define STRUCT_CHARACTER_H


struct Struct_Character
{
    Struct_Character(float x,float y, float a, int s):position_x(x), position_y(y),angle(a), step(s){}
    Struct_Character(){}

    float position_x, position_y;
    float angle; int step;
};

#endif // STRUCT_CHARACTER_H
