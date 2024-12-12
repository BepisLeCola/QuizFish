#ifndef QUIZGAME_HPP
#define QUIZGAME_HPP

#include "Common.hpp"
#include <random>
#include "Screen.hpp"
#include "Mouse.hpp"
#include "Collisions.hpp"
#include "Question.hpp"
#include "Fx.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Audio.hpp"
#include "HUD.hpp"

void LoadQuizGame();
void UpdateQuizGame(float _dt);
void DisplayQuizGame(sf::RenderWindow& _window);

#endif