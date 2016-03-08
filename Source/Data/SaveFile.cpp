#include "SaveFile.h"

SaveFile::SaveFile(std::string _fileName):
    fileName(_fileName)
{
    sStream.str(std::string());

    fileStream.open(fileName, std::ios::in); // Open to read

    if(fileStream.is_open())
    {
        std::cout << "SAVE: Save file " << fileName << " opened successfully" << std::endl;
    }
    fileStream.close();
}
SaveFile::SaveFile()
{
    fileName = "error.txt";
}
SaveFile::~SaveFile()
{

}

bool SaveFile::readFile()
{
    fileStream.open(fileName, std::ios::in); // Open to read

    if(fileStream.is_open())
    {
        saveList.clear();
        std::string line;
        while(std::getline(fileStream,line))
        {
            std::map <int, std::string> lineSeperator;
            int iter = 0;
            sStream << line;
            while (sStream.good())
            {
                std::string entry;
                std::getline(sStream, entry, ':');
                lineSeperator[iter] = entry;
                iter++;
            }
            sStream.str(std::string());
            sStream.clear();
            saveList.push_back(std::make_pair(lineSeperator[0], lineSeperator[1]));
        }
    }
    else //file does not exist
    {
        fileStream.close();
        return false;
    }

    fileStream.close();
    return true;
}
void SaveFile::writeFile()
{
    fileStream.open(fileName, std::ios::out | std::ios::trunc); // deletes and writes

    if(fileStream.is_open())
    {
        for(int it = 0; it != saveList.size(); it++)
        {
            fileStream << saveList[it].first << ":" << saveList[it].second;

            if(it != saveList.size()-1)
            {
                fileStream << std::endl;
            }
        }
    }
    fileStream.close();
}

void SaveFile::clearSave()
{
    fileStream.open(fileName, std::ios::out | std::ios::trunc); // deletes and writes
    fileStream.close();
    saveList.clear();
}
std::string SaveFile::getItem(std::string itemName)
{
    for(int it = 0; it != saveList.size(); it++)
    {
        if(saveList[it].first == itemName)
        {
            return saveList[it].second;
        }
    }
}
std::vector <std::string> SaveFile::separateString (std::string saveString)
{
    std::vector <std::string> returnVector;

    sStream << saveString;
    while (sStream.good())
    {
        std::string entry;
        std::getline(sStream, entry, ',');
        returnVector.push_back(entry);
    }
    sStream.str(std::string());
    sStream.clear();
    return returnVector;
}
std::string SaveFile::conjoinString (std::vector <std::string> stringParts)
{
    for(int it = 0; it != stringParts.size(); it++)
    {
        sStream << stringParts[it];
        if(it != stringParts.size()-1)
        {
            sStream << ",";
        }
    }
    std::string conjoinedString = sStream.str();
    sStream.str(std::string());
    sStream.clear();
    return conjoinedString;
}
