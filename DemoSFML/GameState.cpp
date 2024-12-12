#include "GameState.hpp"

enum GameState gameState = MENU;

enum GameState GetGameState(void)
{
	return gameState;
}

void SetGameState(enum GameState _state)
{
	gameState = _state;
}