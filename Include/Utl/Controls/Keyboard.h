#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Window.hpp>

#include <map>

namespace ctr
{
///Key binding
//should only be used in init and non-realtime
//should not be used in text input
sf::Keyboard::Key getKey(const char& key);
char getCharacter(const sf::Keyboard::Key& key);
//key bind pairs
static std::map <char, sf::Keyboard::Key> KeyboardBinds =
{
    //letters
    {'a', sf::Keyboard::A},
    {'b', sf::Keyboard::B},
    {'c', sf::Keyboard::C},
    {'d', sf::Keyboard::D},
    {'e', sf::Keyboard::E},
    {'f', sf::Keyboard::F},
    {'g', sf::Keyboard::G},
    {'h', sf::Keyboard::H},
    {'i', sf::Keyboard::I},
    {'j', sf::Keyboard::J},
    {'k', sf::Keyboard::K},
    {'l', sf::Keyboard::L},
    {'m', sf::Keyboard::M},
    {'n', sf::Keyboard::N},
    {'o', sf::Keyboard::O},
    {'p', sf::Keyboard::P},
    {'q', sf::Keyboard::Q},
    {'r', sf::Keyboard::R},
    {'s', sf::Keyboard::S},
    {'t', sf::Keyboard::T},
    {'u', sf::Keyboard::U},
    {'v', sf::Keyboard::V},
    {'w', sf::Keyboard::W},
    {'x', sf::Keyboard::X},
    {'y', sf::Keyboard::Y},
    {'z', sf::Keyboard::Z},

    //numbers
    {'0', sf::Keyboard::Num0},
    {'1', sf::Keyboard::Num1},
    {'2', sf::Keyboard::Num2},
    {'3', sf::Keyboard::Num3},
    {'4', sf::Keyboard::Num4},
    {'5', sf::Keyboard::Num5},
    {'6', sf::Keyboard::Num6},
    {'7', sf::Keyboard::Num7},
    {'8', sf::Keyboard::Num8},
    {'9', sf::Keyboard::Num9},
    /*
    -char 32-127 are the default ascii codes
    -char 1-31 will be used for 'extra' keys consisting of
    keys like rAlt with no real ascii code
    */
    //row 1
    {'`', sf::Keyboard::Tilde},
    {'-', sf::Keyboard::Dash},
    {'+', sf::Keyboard::Add},
    {1,   sf::Keyboard::BackSpace},
    //row 2
    {2,    sf::Keyboard::Tab},
    {'[',  sf::Keyboard::LBracket},
    {']',  sf::Keyboard::RBracket},
    {'\\', sf::Keyboard::BackSlash},
    //row 3
    {';',  sf::Keyboard::SemiColon},
    {'\'', sf::Keyboard::Quote},
    {3,    sf::Keyboard::Return},
    //row 4
    {4,   sf::Keyboard::LShift},
    {',', sf::Keyboard::Comma},
    {'.', sf::Keyboard::Period},
    {'/', sf::Keyboard::Slash},
    {5,   sf::Keyboard::RShift},
    //row 5
    {6,   sf::Keyboard::LControl},
    {7,   sf::Keyboard::LAlt},
    {' ', sf::Keyboard::Space},
    {8,   sf::Keyboard::RAlt},
    {9,   sf::Keyboard::RControl},
    //arrow keys
    {10, sf::Keyboard::Up},
    {11, sf::Keyboard::Down},
    {12, sf::Keyboard::Left},
    {13, sf::Keyboard::Right},
    //extra key set
    {14, sf::Keyboard::Insert},
    {15, sf::Keyboard::Home},
    {16, sf::Keyboard::Delete},
    {17, sf::Keyboard::End},
    {18, sf::Keyboard::PageUp},
    {19, sf::Keyboard::PageDown}
};
}
#endif // KEYBOARD_H
