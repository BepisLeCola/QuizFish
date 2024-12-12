#include "Game.hpp"
sf::Music MusicGame;
void Load(void)
{
	MusicGame.openFromFile("Audio/Musique/mainmusic.ogg");
	MusicGame.setLoop(true);
	MusicGame.play();
	LoadMouse();
	SetGameState(MENU);
	Loadmenu();
	LoadSelection();
	LoadCredits();
	LoadSettings();
	LoadVictory();
	LoadFx();
	InitFishingMiniGame();
	LoadQuizGame();
	LoadHUD();
}

void Update(float _dt)
{
	if (MusicGame.getStatus() != sf::Sound::Status::Playing)
	{
		MusicGame.play();
	}
	MusicGame.setVolume(ReturnVolume());
	switch (GetGameState())
	{
	case MENU:
		UpdateMenu(_dt);
		break;
	case SETTINGS:
		UpdateSettings(_dt);
		break;
	case GAME_QUIZ:
		UpdateQuizGame(_dt);
		UpdateHUD(_dt);
		break;
	case GAME_FISH:
		// c'est normal
		UpdateFishingMiniGame(_dt);
		UpdateFishingMiniGame(_dt);
		break;
	case SELECTION:
		UpdateSelection(_dt);
		break;
	case ENDGAME:
		UpdateVictory(_dt);
		break;
	case CREDIT:
		UpdateCredits(_dt);
		break;
	case QUIT:
		break;
	}

	UpdateFx(_dt);
}

void Display(sf::RenderWindow& _window)
{
	UpdateMouse(_window);

	if (GetGameState() == GAME_FISH)
	{
		_window.setMouseCursorVisible(false);
	}
	else
	{
		_window.setMouseCursorVisible(true);
	}

	//Affichage
	(_window).clear(sf::Color::Black); //Effacement du contenu de la fenêtre par du noir

	switch (GetGameState())
	{
	case MENU:
		DisplayMenu(_window);
		DisplayClicFx(_window);
		break;
	case SETTINGS:
		DisplaySettings(_window);
		DisplayFx(_window);
		break;
	case GAME_QUIZ:
		DisplayQuizGame(_window);
		DisplayFx(_window);
		DisplayHUD(_window);
		break;
	case GAME_FISH:
		DisplayFishingMiniGame(_window);
		break;
	case SELECTION:
		DisplaySelection(_window);
		DisplayFx(_window);
		break;
	case ENDGAME:
		DisplayVictory(_window);
		DisplayFx(_window);
		break;
	case CREDIT:
		DisplayCredits(_window);
		break;
	case QUIT:
		_window.close();
		break;
	}

	_window.display();               //Présentation de la fenêtre à l'écran: marque la fin de l'affichage
}