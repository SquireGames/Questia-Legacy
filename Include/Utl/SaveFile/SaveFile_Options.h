#ifndef SAVEFILE_OPTIONS_H
#define SAVEFILE_OPTIONS_H

#include "SaveFile.h"
#include "Option_Base.h"

class SaveFile_Options
{
public:
    SaveFile_Options();
    ~SaveFile_Options();

    void saveOption(Option_Base* option);

private:
    SaveFile saveFile;
};

#endif // SAVEFILE_OPTIONS_H
