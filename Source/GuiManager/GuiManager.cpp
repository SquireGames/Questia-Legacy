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
        if(buttonMap[buttonName]->isVisible)
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














//
//
//
// OLD GUI MANAGER
//
//
//

GuiManager::GuiManager(sf::RenderWindow &_window,  ResourceManager &res, bool gameOverlay):
    statLayers(0)
    , window(_window)
    , overlayVisible(false)
    , timer(25)
    , res(res)
    , gameOverlay(gameOverlay)
{
    if(gameOverlay)
    {
        if(!guiTexture.loadFromFile("Media/Image/Game/Gui/playerGui.png")) {}
        guiSprite.setTexture(guiTexture);
        guiSprite.setPosition(0,973);

        statisticsTextHP.setFont(Data_Desktop::getInstance().font1);
        statisticsTextHP.setCharacterSize(25);
        statisticsTextHP.setColor(sf::Color::Black);
        statisticsTextHP.setPosition(260,1047);

        statisticsTextMP.setFont(Data_Desktop::getInstance().font1);
        statisticsTextMP.setCharacterSize(25);
        statisticsTextMP.setColor(sf::Color::Black);
        statisticsTextMP.setPosition(900,1047);

        statisticsTextStamina.setFont(Data_Desktop::getInstance().font1);
        statisticsTextStamina.setCharacterSize(25);
        statisticsTextStamina.setColor(sf::Color::Black);
        statisticsTextStamina.setPosition(1469,1047);
    }
    else
    {
        overlayVisible = true;
    }
}

void GuiManager::toggleOverlay()
{
    if(buttonTimer())
    {
        if(overlayVisible)
        {
            overlayVisible = false;
        }
        else
        {
            overlayVisible = true;
        }
    }
}

bool GuiManager::buttonTimer()
{
    if(timer == 25)
    {
        timer = 0;
        return true;
    }
    else
    {
        return false;
    }
}


void GuiManager::setStats(std::tuple<int, int, int, int, int, int> statsTuple)
{
    int HP, MP, ST;
    int maxHP, maxMP, maxST;
    float HPP, MPP, STP;

    std::tie(HP,MP,ST,maxHP,maxMP,maxST) = statsTuple;

    HPP = (float)HP/(float)maxHP;
    MPP = (float)MP/(float)maxMP;
    STP = (float)ST/(float)maxST;

    hpSprite.setTextureRect(sf::IntRect(0,0,394*(HPP),13));
    mpSprite.setTextureRect(sf::IntRect(0,0,394*(MPP),13));
    stSprite.setTextureRect(sf::IntRect(0,0,394*(STP),13));

    //HP, MP, Stamina
    os << HP << " / " << maxHP;
    statisticsTextHP.setString(os.str());
    os.str(std::string());
    os << MP << " / " << maxMP;
    statisticsTextMP.setString(os.str());
    os.str(std::string());
    os << ST << " / " << maxST;
    statisticsTextStamina.setString(os.str());
    os.str(std::string());
}

void GuiManager::drawGui()
{
    if(timer!=25)
    {
        timer++;
    }

    if(gameOverlay)
    {
        //window.draw(guiSprite);

        window.draw(hpSprite);
        window.draw(mpSprite);
        window.draw(stSprite);

        window.draw(statisticsTextHP);
        window.draw(statisticsTextMP);
        window.draw(statisticsTextStamina);

    }

    if(overlayVisible)
    {
        for(auto mapIterator = gameDebuggerStrings.begin(); mapIterator!= gameDebuggerStrings.end(); mapIterator++)
        {
            window.draw(mapIterator->second);
        }
    }

    for(auto mapIterator = buttonMap.begin(); mapIterator!= buttonMap.end(); mapIterator++)
    {
        bool transparent;
        sf::Sprite buttonSprite;
        sf::Vector2i bounds;
        sf::Text buttonText;
        bool overlay;
        sf::RectangleShape rect;

        std::tie(transparent, buttonSprite, buttonText, rect, overlay) = mapIterator->second;

        if(!transparent)
        {
            window.draw(buttonSprite);
            window.draw(buttonText);
            if(overlay)
            {
                window.draw(rect);
            }
        }
    }
}

void GuiManager::addButton(unsigned short buttonID, bool transparent, unsigned short x_b, unsigned short y_b, std::string filePath,
                           std::string text, unsigned short x_t, unsigned short y_t, unsigned short textStyle, unsigned short textSize, sf::Color textColor,
                           sf::Color overlayColor)
{
    sf::Sprite buttonSprite;
    buttonSprite.setTexture (res.getTexture(filePath));
    buttonSprite.setPosition (x_b, y_b);

    sf::Text buttonText;
    buttonText.setString(text);
    buttonText.setPosition(x_t, y_t);
    switch (textStyle)
    {
    case 0:
        break;
    case 1:
        buttonText.setFont(Data_Desktop::getInstance().font1);
        break;
    }
    buttonText.setCharacterSize(textSize);
    buttonText.setColor(textColor);

    sf::RectangleShape rect;

    rect.setFillColor(overlayColor);
    rect.setPosition(x_b, y_b);
    rect.setSize(sf::Vector2f(buttonSprite.getGlobalBounds().width,buttonSprite.getGlobalBounds().height));

    buttonMap[buttonID] = std::make_tuple(transparent, buttonSprite,  buttonText, rect, false);
}

void GuiManager::buttonCheck()
{
    sf::Vector2f  mouse = Data_Desktop::getInstance().getScaledMousePosition(window);
    for(auto mapIterator = buttonMap.begin(); mapIterator!= buttonMap.end(); mapIterator++)
    {
        bool transparent;
        sf::Sprite buttonSprite;
        sf::Vector2i bounds;
        sf::Text buttonText;
        bool overlay;
        sf::RectangleShape rect;

        std::tie(transparent, buttonSprite, buttonText, rect, overlay) = mapIterator->second;

        if (buttonSprite.getGlobalBounds().contains(mouse))
        {
            overlay = true;
        }
        else
        {
            overlay = false;
        }
        mapIterator->second = std::make_tuple(transparent, buttonSprite,  buttonText, rect, overlay);
    }
}

bool GuiManager::testButton(unsigned short buttonID)
{
    sf::Vector2f  mouse = Data_Desktop::getInstance().getScaledMousePosition(window);

    bool transparent;
    sf::Sprite buttonSprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, buttonSprite, buttonText, rect, overlay) =  buttonMap[buttonID];

    if(!transparent)
    {
        if (buttonSprite.getGlobalBounds().contains(mouse))
        {
            if(buttonID >= 1000)
            {
                return true;
            }
            else if(buttonTimer())
            {
                return true;
            }
        }
    }
    return false;
}

void GuiManager::changeVisibility(int button, bool transparent)
{
    bool transparentTemp;
    sf::Sprite buttonSprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparentTemp, buttonSprite, buttonText, rect, overlay) = buttonMap[button];

    if(transparentTemp != transparent)
    {
        buttonMap[button] = std::make_tuple(transparent, buttonSprite,  buttonText, rect, false);
    }
}

void GuiManager::rotateSprite(int button, int degrees)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    sprite.setRotation(degrees);

    buttonMap[button] = std::make_tuple(transparent, sprite,  buttonText, rect, false);
}

void GuiManager::moveSprite(int button, int x, int y)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    sf::Vector2f textOffset;
    textOffset.x = x + (buttonText.getPosition().x - sprite.getPosition().x);
    textOffset.y = y + (buttonText.getPosition().y - sprite.getPosition().y);

    buttonText.setPosition(textOffset);

    sprite.setPosition(x, y);

    sf::Vector2f rectOffset;
    rectOffset.x = sprite.getPosition().x;
    rectOffset.y = sprite.getPosition().y;

    rect.setPosition(rectOffset);

    buttonMap[button] = std::make_tuple(transparent, sprite,  buttonText, rect, false);
}

sf::Vector2i GuiManager::getButtonCoords(int button)
{
    bool transparent;
    sf::Sprite sprite;
    sf::Vector2i bounds;
    sf::Text buttonText;
    bool overlay;
    sf::RectangleShape rect;

    std::tie(transparent, sprite, buttonText, rect, overlay) = buttonMap[button];

    return sf::Vector2i(sprite.getPosition());
}

void GuiManager::deleteButton(int button)
{
    buttonMap.erase(button);
}


