#ifndef MENU_HPP
#define MENU_HPP

#include "Common.hpp"
#include "Screen.hpp"
#include "GameState.hpp"
#include "Mouse.hpp"
#include "Fx.hpp"
#include "Credits.hpp"
#define DIFFPIXEL 16

void Loadmenu();
void UpdateMenu(float _dt);
void DisplayMenu(sf::RenderWindow& _window);

void UpdateButtonTimer(float _dt, struct Button& _button, sf::Texture& _OutTexture, sf::Texture& _InTexture, GameState _state);

std::string GetGlobalFont();

struct Button
{
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	int test = 0;
	float timer = 0.0f;
	bool pressed = false;
};

#endif 
