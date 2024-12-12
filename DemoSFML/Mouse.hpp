#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Common.hpp"

void LoadMouse();
void UpdateMouse(sf::RenderWindow&);
sf::Vector2i GetMousePos();
void SetMouseCursor(sf::Cursor::Type);

#endif