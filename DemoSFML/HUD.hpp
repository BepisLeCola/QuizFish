#ifndef HUD_HPP
#define HUD_HPP

#include "Common.hpp"
#include "Player.hpp"
#include "Mouse.hpp"
#include "Collisions.hpp"

void LoadHUD();
void UpdateHUD(float _dt);
void DisplayHUD(sf::RenderWindow& _window);

void FadeTextOut();

#endif