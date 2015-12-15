#ifndef CLASSMANAGER_H
#define CLASSMANAGER_H

#include <string>

#include "Namespace_Character.h"


class ClassManager
{
public:
    ClassManager(bool _isInGame);
    ~ClassManager();

    std::string returnCharacterInformation(Character::ClassType classType, Character::InformationType infoType);

private:
    bool isInGame;
};

#endif // CLASSMANAGER_H
