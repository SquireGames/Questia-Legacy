#ifndef FILEDATA_H
#define FILEDATA_H

#include <boost/filesystem.hpp>
#include <sstream>

namespace utl
{
    bool doesExist(const std::string& fileLocation);
    std::vector<std::string> getFiles(std::string directory, bool isWithDirectory);
}

#endif // FILEDATA_H
