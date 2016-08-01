#include "FileData.h"

bool utl::doesExist(const std::string& fileLocation)
{
    if(boost::filesystem::exists(fileLocation))
    {
        return true;
    }
    return false;
}
