#include "Questia/Data/InputBuffer.h"

InputBuffer::InputBuffer():
	textBuffer()
	, windows()
{
	
}

InputBuffer::~InputBuffer()
{
	
}

void InputBuffer::enqueue(char32_t input)
{
	textBuffer.push_back(input);
}

std::u32string InputBuffer::getText()
{
	std::u32string text;
	text.reserve(textBuffer.size());
	for(auto& it : textBuffer)
	{
		text += it;
	}
	return text;
}

void InputBuffer::clearBuffer()
{
	textBuffer = std::deque<char32_t>();
}
