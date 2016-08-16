#include "Utl/SaveFile/SaveFile.h"

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

                char firstCharacter = ' ';
                if(entry.length() > 0)
                {
                    firstCharacter = entry.at(0);
                }

                if(firstCharacter != '/' || firstCharacter != '(')
                {
                    if(firstCharacter != ' ')
                    {
                        lineSeperator[iter] = entry;
                        iter++;
                    }
                }
                else
                {
                    goto escapeStream;
                }
            }
escapeStream:
            saveList.push_back(std::make_pair(lineSeperator[0], lineSeperator[1]));
            sStream.str(std::string());
            sStream.clear();
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
        for(unsigned int it = 0; it != saveList.size(); it++)
        {
            fileStream << saveList[it].first << ":" << saveList[it].second;

            if(commentList.count(saveList[it].first))
            {
                fileStream << commentList[saveList[it].first];
            }

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
    for(unsigned int it = 0; it != saveList.size(); it++)
    {
        if(saveList[it].first == itemName)
        {
            return saveList[it].second;
        }
    }
    return std::string("nil");
}
