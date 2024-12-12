#include "Mouse.hpp"

struct MouseData
{
	sf::Vector2i pos;
	sf::Cursor cursor;
	sf::Cursor::Type cursorType = sf::Cursor::Arrow;
	sf::Image cursorImg;
}mouseData;

void LoadMouse()
{
	mouseData.cursorImg.loadFromFile("Assets/cursor.png");
	mouseData.cursor.loadFromPixels(mouseData.cursorImg.getPixelsPtr(), mouseData.cursorImg.getSize(), { 0,0 });
}

void UpdateMouse(sf::RenderWindow& _window)
{
	mouseData.pos = sf::Mouse::getPosition(_window);
	_window.setMouseCursor(mouseData.cursor);
}

void SetMouseCursor(sf::Cursor::Type _cursorType)
{
	if (mouseData.cursorType != _cursorType)
	{
		mouseData.cursorType = _cursorType;
		mouseData.cursor.loadFromSystem(_cursorType);
	}
}

sf::Vector2i GetMousePos()
{
	return mouseData.pos;
}