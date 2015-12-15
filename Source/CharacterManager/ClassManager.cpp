#include "ClassManager.h"

#include <fstream>

ClassManager::ClassManager(bool _isInGame):
    isInGame(_isInGame)
{
    //ctor
}

ClassManager::~ClassManager()
{
    //dtor
}

std::string ClassManager::returnCharacterInformation(Character::ClassType classType, Character::InformationType infoType)
{
    std::string outputString;

    std::string classDir;
    std::string infoFileName;
    std::string completePath;

    std::ifstream fileStream;

    switch(classType)
    {
    /// Human
    case Character::ClassType::knight:
    {
        classDir = std::string("Data/Classes/Human/0Knight/");
    }
    break;

    /// Elf
    case Character::ClassType::ranger:
    {
        classDir = std::string("Data/Classes/Elf/0Ranger/");
    }
    break;

    /// Not implemented
    default:
    {
        return std::string("Not implemented yet");
    }
    break;
    }


    switch(infoType)
    {
    case Character::InformationType::description:
    {
        infoFileName = "description.txt";
    }
    break;
    default:
    {
        return std::string("Not implemented information type");
    }
    break;
    }

    completePath = classDir + infoFileName;
    fileStream.open(completePath);
    while(!fileStream.eof())
    {
        std::getline(fileStream, outputString);
    }
    return outputString;
}
