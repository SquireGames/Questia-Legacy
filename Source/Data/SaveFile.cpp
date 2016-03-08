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


/*
    std::ifstream openFile;
    openFile.open(config);

    if(openFile.is_open() && openFile.good())
    {

        std::stringstream sStream;
        std::map <int, std::string> optionsVector;
        int level = 0;

        while(!openFile.eof())
        {
            char line[200];
            for(int y = 0; y!= 200; y++)
            {
                line[y] = ' ';
            }
            openFile.getline(line, 200);
            int it = 0;

            for(it; it != 200; it++)
            {
                if(line[it] == ':')
                {
                    for(int x = 1; x < 10; x++)
                    {
                        if(line[it+x] != '(' &&line[it+x] != ' ')
                        {
                            sStream << line[it+x];
                        }
                        else
                        {
                            x = 10;
                        }
                    }
                    std::string optionString;
                    sStream >> optionString;
                    optionsVector[level] = optionString;
                    it = 199;
                    sStream.clear();
                }
            }
            level++;
        }

        std::cout<< "Window mode:  " << optionsVector[0] << std::endl << "Sound mode:  " << optionsVector[1] << std::endl;

        windowType = std::atoi(optionsVector[0].c_str());
        maxFPS = std::atoi(optionsVector[1].c_str());
        musicVolume = std::atoi(optionsVector[2].c_str());
        fontType = std::atoi(optionsVector[3].c_str());

        keyMap[0] = getConvertedKey(optionsVector[5].at(0));
        keyMap[1] = getConvertedKey(optionsVector[6].at(0));
        keyMap[2] = getConvertedKey(optionsVector[7].at(0));
        keyMap[3] = getConvertedKey(optionsVector[8].at(0));

        keyMap[4] = getConvertedKey(optionsVector[9].at(0));
        keyMap[5] = getConvertedKey(optionsVector[10].at(0));
        keyMap[6] = getConvertedKey(optionsVector[11].at(0));


        key_moveUp = optionsVector[5].at(0);
        key_moveDown = optionsVector[6].at(0);
        key_moveLeft = optionsVector[7].at(0);
        key_moveRight = optionsVector[8].at(0);

        key_skill4 = optionsVector[9].at(0);
        key_skill5 = optionsVector[10].at(0);
        key_skill6 = optionsVector[11].at(0);

        changeFont(fontType);

        switch(std::atoi(optionsVector[0].c_str()))
        {
        case 0:
            return 0;
            break;
        case 1:
            return 1;
            break;
        default:
            break;
        }
    }
    writeOptions(0, 0, 50, 1, 'w', 's', 'a', 'd', 'S', 'A', 'B');
    font1.loadFromFile("Media/Fonts/Lato-Medium.ttf");
    return 0;
*/
