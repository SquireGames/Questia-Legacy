#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <string>  //std::string
#include <utility> //std::pair
#include <vector>  //std::vector
#include <fstream> //std::fstream
#include <sstream> //std::stringstream
#include <stdlib.h>//std::atoi
#include <map>     //std::map
#include <iostream>



// This object assumes the file is good

class SaveFile
{
public:
    SaveFile(std::string _fileName); // opens path
    SaveFile(); // warning! fileName must be assigned!
    ~SaveFile();

    void setFilePath(std::string _fileName) {fileName = _fileName;}

    template <class T>
    void addItem  (std::string itemName, T item) // saving lists of entities, things with the same type
    {
        sStream << item;
        saveList.push_back(std::make_pair(itemName, sStream.str()));
        sStream.str(std::string());
    }

    template <class T>
    void saveItem (std::string itemName, T item) // overwriting entries
    {
        for(int it = 0; it != saveList.size(); it++)
        {
            if(saveList[it].first == itemName)
            {
                sStream << item;
                saveList[it].second = sStream.str();
                sStream.str(std::string());
                return;
            }
        }
        addItem(itemName, item);
    }

    std::vector<std::string> getItemList()
    {
        std::vector<std::string> itemList;
        for(int it = 0; it != saveList.size(); it++)
        {
            itemList.push_back(saveList[it].first);
        }
        return itemList;
    }

    bool readFile();  // gets updated vector
    void writeFile(); // saves changes
    void clearSave(); // clears map

    void addComment(std::string item, std::string _comment); // only works on saveItems, wont save on reload

    std::string getItem(std::string itemName);

    int asNumber (std::string _string)
    {
        return atoi(_string.c_str());
    }

    template <class T>
    std::string asString (T _item)
    {
        sStream << _item;
        std::string item = sStream.str();
        sStream.str(std::string());
        return item;
    }

    std::vector <std::pair <std::string, std::string> >& getSaveList() {return saveList;}

    std::vector <std::string> separateString (std::string saveString); // reading values of entry with many parts
    std::string conjoinString (std::vector <std::string> stringParts); // combine things into one string

private:
    std::string fileName;

    std::vector <std::pair <std::string, std::string> > saveList;
    std::map <std::string, std::string> commentList;
    std::fstream fileStream;
    std::stringstream sStream;
};

#endif // SAVEFILE_H
