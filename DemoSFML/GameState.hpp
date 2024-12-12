#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

enum GameState
{
	MENU,
	SETTINGS,
	GAME_QUIZ,
	GAME_FISH,
	VICTORY,
	ENDGAME,
	CREDIT,
	QUIT,
	SELECTION
};

enum GameState GetGameState(void);
void SetGameState(enum GameState _state);

#endif
