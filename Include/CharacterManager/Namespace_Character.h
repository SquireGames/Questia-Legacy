#ifndef NAMESPACE_CHARACTER_H
#define NAMESPACE_CHARACTER_H

namespace Character
{
enum ClassType
{
    //Human
    knight, rogue,
    //Elf
    ranger,
    //Lich
    mage,
    //Giant
    hunter,


    none
};

enum InformationType
{
    description,
    race
};

}


#endif // NAMESPACE_CHARACTER_H
