#ifndef FILEDATA_H
#define FILEDATA_H

#include <boost/filesystem.hpp>
#include <sstream>

#include <iostream>

namespace utl
{
    bool doesExist(const std::string& fileLocation);
    std::vector<std::string> getFiles(std::string directory, bool isWithDirectory);
    bool createDirectory(const std::string& filePath);
}

#endif // FILEDATA_H
