#include "GuiManager.h"

GuiManagerNew::GuiManagerNew(sf::RenderWindow &_window, ResourceManager &_resourceManager):
    window(_window)
    , resourceManager(_resourceManager)
    , currentButtonEdit ("NOBUTTON")
    , currentButtonAtrEdit ("NOBUTTONATR")
    , currentGroupEdit("NOGROUP")
    , currentListEdit("NOLIST")
    , mouseCoords(std::make_pair(0,0))
{

}

GuiManagerNew::~GuiManagerNew()
{
    for(std::map<std::string, Button*>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it)
    {
        delete it->second;
    }
}

void GuiManagerNew::createButtonTemplate(std::string buttonName)
{
    if(!buttonMap.count(buttonName))
    {
        Button* newButton = new Button(window, resourceManager, buttonFont, true, -1);
        newButton->buttonName = buttonName;
        buttonMap[buttonName] = newButton;
        buttonMap[buttonName]->setButton(gui::ButtonCharacteristic::isVisible, false);

        currentButtonEdit = buttonName;
    }
}

void GuiManagerNew::createButtonTemplate(std::string buttonName, int layer)
{
    if(!buttonMap.count(buttonName))
    {
        Button* newButton = new Button(window, resourceManager, buttonFont, true, -1);
        newButton->buttonName = buttonName;
        buttonMap[buttonName] = newButton;
        buttonMap[buttonName]->setButton(gui::ButtonCharacteristic::isVisible, false);

        newButton->layer = layer;

        currentButtonEdit = buttonName;
    }
}

void GuiManagerNew::createButtonTemplate(std::string copyName, std::string originalName)
{
    if(!buttonMap.count(copyName))
    {
        if(buttonMap.count(originalName))
        {
            Button* newButton = new Button(*buttonMap[originalName], -1);
            newButton->buttonName = copyName;
            buttonMap[copyName] = newButton;
            buttonMap[copyName]->setButton(gui::ButtonCharacteristic::isVisible, false);
            buttonMap[copyName]->setButton(gui::ButtonCharacteristic::isTemplate, true);

            currentButtonEdit = copyName;
        }
    }
}


void GuiManagerNew::createButton(std::string buttonName)
{
    if(!buttonMap.count(buttonName))
    {
        Button* newButton = new Button(window, resourceManager, buttonFont, false, buttonCount);
        newButton->buttonName = buttonName;
        buttonCount++;
        buttonMap[buttonName] = newButton;

        currentButtonEdit = buttonName;

        placeInDrawList(newButton);
    }
}

void GuiManagerNew::createButton(std::string buttonName, int layer)
{
    if(!buttonMap.count(buttonName))
    {
        Button* newButton = new Button(window, resourceManager, buttonFont, false, buttonCount);
        newButton->buttonName = buttonName;
        buttonCount++;
        buttonMap[buttonName] = newButton;

        currentButtonEdit = buttonName;

        newButton->layer = layer;
        placeInDrawList(newButton);
    }
}

void GuiManagerNew::createButton(std::string copyName, std::string originalName)
{
    if(buttonMap.count(originalName))
    {
        if(!buttonMap.count(copyName))
        {
            Button* newButton = new Button(*buttonMap[originalName], buttonCount);
            newButton->buttonName = copyName;
            buttonCount++;
            buttonMap[copyName] = newButton;

            currentButtonEdit = copyName;

            placeInDrawList(newButton);
        }
    }
}

void GuiManagerNew::placeInDrawList(Button* button)
{
    //check if it exists
    for(auto it = buttonDrawList.begin(); it != buttonDrawList.end(); it++)
    {
        if((*it)->buttonID == button->buttonID)
        {
            buttonDrawList.erase(it);
            break;
        }
    }

    //insert the new button
    if(buttonDrawList.size() == 0)
    {
        buttonDrawList.push_back(button);
        return;
    }
    else
    {
        for(auto it = buttonDrawList.begin(); it != buttonDrawList.end(); it++)
        {
            if (button->layer <= (*it)->layer)
            {
                buttonDrawList.insert(it,button);
                return;
            }
        }
        //in the back
        buttonDrawList.push_back(button);
    }
}

void GuiManagerNew::createButtonAtr(std::string buttonName, std::string atrName, gui::ButtonAtr buttonAtr)
{
    if(buttonMap.count(buttonName))
    {
        buttonMap[buttonName]->addButtonAtr(atrName, buttonAtr);
        currentButtonEdit = buttonName;
        currentButtonAtrEdit = atrName;
    }
}

void GuiManagerNew::createButtonAtr(std::string atrName, gui::ButtonAtr buttonAtr)
{
    buttonMap[currentButtonEdit]->addButtonAtr(atrName, buttonAtr);
    currentButtonAtrEdit = atrName;
}

void GuiManagerNew::createGroup(std::string groupName)
{
    groupMap[groupName];
    currentGroupEdit = groupName;
}

void GuiManagerNew::createGroupTemplate(std::string groupName)
{
    groupTemplateMap[groupName];
    currentGroupEdit = groupName;
}

void GuiManagerNew::createGroupFromTemplate(std::string groupName, std::string templateName)
{
    if(groupTemplateMap.count(templateName))
    {
        groupMap[groupName];
        for(std::string it : groupTemplateMap[templateName])
        {
            Button* newButton = new Button(*buttonMap[it], buttonCount);
            newButton->buttonName = buttonMap[it]->buttonName;
            buttonCount++;
            std::string buttonName = it + "_" + groupName;
            buttonMap[buttonName] = newButton;
            buttonMap[buttonName]->setButton(gui::ButtonCharacteristic::coords, buttonMap[it]->buttonPosition);

            groupMap[groupName].push_back(buttonName);

            currentGroupEdit = groupName;

            placeInDrawList(newButton);
        }
    }
}

std::string GuiManagerNew::getGroupEntry(std::string groupName, std::string buttonName)
{
    if(groupMap.count(groupName))
    {
        for(const std::string& it : groupMap[groupName])
        {
            if(buttonMap[it]->buttonName == buttonName)
            {
                return it;
            }
        }
    }
    return "nil";
}

void GuiManagerNew::addToGroup(std::string groupName, std::string entryName)
{
    if(groupMap.count(groupName))
    {
        if(buttonMap.count(entryName))
        {
            groupMap[groupName].push_back(entryName);
        }
    }
    else if(groupTemplateMap.count(groupName))
    {
        if(buttonMap.count(entryName))
        {
            if(buttonMap[entryName]->isTemplate)
            {
                groupTemplateMap[groupName].push_back(entryName);
            }
        }
    }
}
void GuiManagerNew::addToGroup(std::string entryName)
{
    if(groupMap.count(currentGroupEdit))
    {
        if(buttonMap.count(entryName))
        {
            groupMap[currentGroupEdit].push_back(entryName);
        }
    }
    else if(groupTemplateMap.count(currentGroupEdit))
    {
        if(buttonMap.count(entryName))
        {
            if(buttonMap[entryName]->isTemplate)
            {
                groupTemplateMap[currentGroupEdit].push_back(entryName);
            }
        }
    }
}



bool GuiManagerNew::isClicked(std::string buttonName)
{
    if(buttonMap.count(buttonName))
    {
        if(buttonMap[buttonName]->isVisible && buttonMap[buttonName]->isActive)
        {
            std::pair <int, int> buttonCoords = buttonMap[buttonName]->buttonPosition;
            std::pair <int, int> buttonBounds = buttonMap[buttonName]->buttonBounds;
            buttonCoords.first  += buttonMap[buttonName]->scrollAmount_x;
            buttonCoords.second += buttonMap[buttonName]->scrollAmount_y;

            if(mouseCoords.first  > buttonCoords.first  && mouseCoords.first  < buttonCoords.first  + buttonBounds.first &&
                    mouseCoords.second > buttonCoords.second && mouseCoords.second < buttonCoords.second + buttonBounds.second)
            {
                return true;
            }
        }
    }
    return false;
}

void GuiManagerNew::drawButtons()
{
    for(auto it = buttonDrawList.begin(); it != buttonDrawList.end(); it++)
    {
        (*it)->drawButton();
    }
}

void GuiManagerNew::setButtonLayer(std::string buttonName, int layer)
{
    if(buttonMap.count(buttonName))
    {
        Button* button = buttonMap[buttonName];
        button->layer = layer;
        if(button->isTemplate != true)
        {
            placeInDrawList(button);
        }
    }
}
void GuiManagerNew::setButtonLayer(int layer)
{
    Button* button = buttonMap[currentButtonEdit];
    button->layer = layer;
    if(button->isTemplate != true)
    {
        placeInDrawList(button);
    }
}

void GuiManagerNew::deleteButton(std::string buttonName)
{
    delete buttonMap[buttonName];
    buttonMap.erase(buttonName);
}

void GuiManagerNew::setMousePosition(std::pair <float, float> _mouseCoords)
{
    mouseCoords = _mouseCoords;

    for(std::map<std::string, Button*>::iterator it = buttonMap.begin(); it != buttonMap.end(); ++it)
    {
        it->second->update(static_cast <std::pair <int, int> > (_mouseCoords));
    }
}

void GuiManagerNew::setFont(sf::Font _buttonFont)
{
    buttonFont = _buttonFont;
}







void GuiManagerNew::createList(std::string listName)
{
    listMap[listName] = std::make_pair(std::make_pair("NOTEMPLATE", std::make_pair( std::make_pair(0,0), 0)), std::vector<std::string>());
    currentListEdit = listName;
}

void GuiManagerNew::setListSpacing(std::string listName, int spacing)
{
    if(listMap.count(listName))
    {
        listMap[listName].first.second.second = spacing;
    }
}
void GuiManagerNew::setListSpacing(int spacing)
{
    listMap[currentListEdit].first.second.second = spacing;
}
void GuiManagerNew::setListTemplate(std::string listName, std::string groupTemplate)
{
    if(listMap.count(listName))
    {
        if(groupTemplateMap.count(groupTemplate))
        {
            listMap[listName].first.first = groupTemplate;
        }
    }
}
void GuiManagerNew::setListTemplate(std::string groupTemplate)
{
    if(groupTemplateMap.count(groupTemplate))
    {
        listMap[currentListEdit].first.first = groupTemplate;
    }
}

void GuiManagerNew::setListPosition(std::string listName, std::pair<int, int> position)
{
    if(listMap.count(listName))
    {
        listMap[listName].first.second.first = position;
    }
}
void GuiManagerNew::setListPosition(std::pair<int, int> position)
{
    listMap[currentListEdit].first.second.first = position;
}

std::string GuiManagerNew::createListEntry(std::string listName)
{
    if(listMap[listName].first.first != "NOTEMPLATE")
    {
        int entries = listMap[listName].second.size();
        std::stringstream ss;
        ss << entries;
        std::string entryName = listName + "_" + ss.str();

        createGroupFromTemplate(entryName, listMap[listName].first.first);
        setGroupAtr(gui::ButtonCharacteristic::coords, std::make_pair(listMap[listName].first.second.first.first,
                    listMap[listName].first.second.first.second + entries * listMap[listName].first.second.second));
        listMap[listName].second.push_back(entryName);

        return entryName;
    }
    return "nil";
}
std::string GuiManagerNew::createListEntry()
{
    if(listMap[currentListEdit].first.first != "NOTEMPLATE")
    {
        int entries = listMap[currentListEdit].second.size();
        std::stringstream ss;
        ss << entries;
        std::string entryName = currentListEdit + "_" + ss.str();

        createGroupFromTemplate(entryName, listMap[currentListEdit].first.first);
        setGroupAtr(gui::ButtonCharacteristic::coords, std::make_pair(listMap[currentListEdit].first.second.first.first,
                    listMap[currentListEdit].first.second.first.second + entries * listMap[currentListEdit].first.second.second));
        listMap[currentListEdit].second.push_back(entryName);

        return entryName;
    }
    return "nil";
}
