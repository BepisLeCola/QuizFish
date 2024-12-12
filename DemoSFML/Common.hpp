#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <time.h>
#include <format>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"

sf::Sprite LoadSprite(const std::string _path, bool);
sf::Text LoadText(const std::string _fontPath, sf::String _string, float _characterSize, sf::Vector2f _pos, sf::Color _color, bool _isCentered);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window);
void DrawPixel(sf::Image& _image, sf::Vector2i _pos, sf::Color _color);

#endif 