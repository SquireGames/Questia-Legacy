#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <deque>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Questia/Utl/Type/Vector2.h"

class InputBuffer
{
public:
	//ctor + dtor
	InputBuffer();
	~InputBuffer();

	//text input
	//should only be used for player input
	void enqueue(char32_t input);
	std::u32string getText();
	void clearBuffer();

	//mouse input
	utl::Vector2i getMousePos(unsigned int window);
	utl::Vector2i getScaledMousePos(unsigned int window);

private:
	//text container
	std::deque<char32_t> textBuffer;

	//window storage for mouse input
	struct WindowData
	{
		sf::RenderWindow* window;
		utl::Vector2i screenResolution;
		utl::Vector2f screenScaleFactor;
	};
	std::vector<WindowData> windows;
};

#endif // INPUTBUFFER_H
