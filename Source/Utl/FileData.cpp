#include "FileData.h"

bool utl::doesExist(const std::string& fileLocation)
{
    if(boost::filesystem::exists(fileLocation) )
    {
        return true;
    }
    return false;
}

std::vector<std::string> utl::getFiles(std::string directory, bool isWithDirectory)
{
    std::vector <std::string> fileNames;
    boost::filesystem::path directoryFolder {directory};
    if(boost::filesystem::exists(directoryFolder))
    {
        if(boost::filesystem::is_directory(directoryFolder))
        {
            for(boost::filesystem::directory_entry& x: boost::filesystem::directory_iterator(directoryFolder))
            {
                std::stringstream ss;
                std::string st;
                if(isWithDirectory)
                {
                    ss<<x.path().string();
                }
                else
                {
                    ss<<x.path().filename().string();
                }
                ss>>st;
                fileNames.push_back(st);
            }
        }
    }
    return fileNames;
}

bool utl::createDirectory(const std::string& filePath)
{
    boost::filesystem::path directory(filePath);

    if(!(boost::filesystem::exists(directory)))
    {
        if(boost::filesystem::create_directory(directory))
        {
            std::cout << "Directory was made: " << filePath << std::endl;
            return true;
        }
        else
        {
            std::cout << "Directory failed to be made: " << filePath << std::endl;
            return false;
        }
    }
    return true;
}

