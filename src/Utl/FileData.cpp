#include "Questia/Utl/FileData.h"

bool utl::doesExist(const std::string& fileLocation)
{
    if(true)//(boost::filesystem::exists(fileLocation) )
    {
        return true;
    }
    return false;
}

std::vector<std::string> utl::getFiles(std::string directory, bool isWithDirectory)
{
    std::vector <std::string> fileNames;
    /*
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
                std::replace(st.begin(), st.end(),'\\', '/');
                fileNames.push_back(st);
            }
        }
    }
    */
    return fileNames;
}

std::vector<std::string> utl::getAllFiles(std::string directory, bool isWithDirectory)
{
    std::vector <std::string> fileNames;
    /*
    boost::filesystem::path directoryFolder {directory};

    if(boost::filesystem::exists(directoryFolder) && boost::filesystem::is_directory(directoryFolder))
    {
        boost::filesystem::recursive_directory_iterator dir(directoryFolder);

        for(auto&& it : dir)
        {
            fileNames.push_back(it.path().string());
        }
    }
    */
    return fileNames;
}

bool utl::createDirectory(const std::string& filePath)
{
    /*
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
    */
    return true;
}

std::vector<std::string> utl::filterFiles(const std::vector<std::string>& inputFiles, const std::string& extension)
{
    std::vector<std::string> newFiles = std::vector<std::string>();
    /*
    for(const std::string& file : inputFiles)
    {
        if(file.find(extension)!= std::string::npos)
        {
            newFiles.push_back(file);
        }
    }
    */
    return newFiles;
}

