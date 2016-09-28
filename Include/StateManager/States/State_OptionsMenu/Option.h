#ifndef OPTION_H
#define OPTION_H

#include <utility>
#include <string>
#include <list>
#include <iterator>

#include "Option_Base.h"
#include "Utl.h"
#include "Keyboard.h"

template <class T>
class Option : public Option_Base
{
public:
    Option();

    //generic
    void setType(OptionType _optionType);
    void setOptionName (std::string _optionName);
    void setList(std::string _listName);

    T getValue();
    std::string getList();
    std::string getOptionName ();
    std::string getValueString();
    std::string* getDisplayString();
    OptionType getType();

    void init(T value);
    bool isChanged();

    //choice
    void addChoice (std::pair <std::string, T> option);
    void setChoices (std::list <std::pair <std::string, T> > _choiceList);
    void iterateForward();
    void iterateBackward();
    bool isEnd();
    bool isBegin();

    //functional
    void callFunction();

    //input
    void setInput(char key);

private:
    //options
    T oldOption;
    T newOption;
    std::string visibleOption = "NONE";
    std::string optionName = "NONE";

    OptionType optionType = OptionType::choice;

    //list
    std::string listName = "nil";

    //choices
    std::list <std::pair <std::string, T> > choiceList;
    typename std::list <std::pair <std::string, T> >::iterator choiceIterator = choiceList.begin();
};

#endif // OPTION_H
