#ifndef VICTORY_HPP
#define VICTORY_HPP

#include "Common.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Question.hpp"

struct Winner
{
	sf::Vector2f pos;
	sf::Sprite Sprite;
	int score;
};

void LoadVictory(void);
void UpdateVictory(float _dt);
void DisplayVictory(sf::RenderWindow& _window);
#endif
