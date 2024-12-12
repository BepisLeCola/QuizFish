#ifndef CREDITS_HPP
#define CREDITS_HPP

#include "Common.hpp"
#include "Screen.hpp"
#include "GameState.hpp"
#include "Menu.hpp"

sf::Text loadText(std::string font, sf::Color _color, std::string _text, int _size);


void LoadCredits();
void UpdateCredits(float _dt);
void DisplayCredits(sf::RenderWindow& _window);

#endif