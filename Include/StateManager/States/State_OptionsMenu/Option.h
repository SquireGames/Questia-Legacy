#ifndef OPTION_H
#define OPTION_H

#include <utility>
#include <string>
#include <list>
#include <iterator>

#include "Option_Base.h"

template <class T>
class Option : public Option_Base
{
public:
    Option();

    void init(T value);
    void setValue(T value);
    T getValue();

    void iterateForward();
    void iterateBackward();
    void callFunction();

    bool isEnd();
    bool isBegin();

    void setList(std::string _listName);
    std::string getList();

    bool isChanged();

    void setOptionName (std::string _optionName);
    std::string getOptionName ();
    void addChoice (std::pair <std::string, T> option);
    void setChoices (std::list <std::pair <std::string, T> > _choiceList);

    std::string* getDisplayString();


private:
    //options
    T oldOption;
    T newOption;
    std::string visibleOption = "NONE";
    std::string optionName = "NONE";

    //list
    std::string listName = "nil";

    //choices
    std::list <std::pair <std::string, T> > choiceList;
    typename std::list <std::pair <std::string, T> >::iterator choiceIterator = choiceList.begin();
};

#endif // OPTION_H
