#ifndef GAME_HPP
#define GAME_HPP

#include "Common.hpp"
#include "Screen.hpp"
#include "GameState.hpp"
#include "Fx.hpp"
#include "Menu.hpp"
#include "Selection.hpp"
#include "Settings.hpp"
#include "Credits.hpp"
#include "FishingMiniGame.hpp"
#include "QuizGame.hpp"
#include "Victory.hpp"
#include "HUD.hpp"

void Load(void);
void Update(float _dt);
void Display(sf::RenderWindow& _window);

#endif