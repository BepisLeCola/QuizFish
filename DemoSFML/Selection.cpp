#include "Selection.hpp"
#include "Player.hpp"
#include <vector>
struct PlayerCard
{
	sf::Sprite Card;
	int curentPP;
	sf::Vector2f leftpos;
	sf::Vector2f rightpos;
	sf::Sprite leftButton;
	sf::Sprite rightButton;
};

sf::Sprite backgroundSelectionSprite = LoadSprite("Assets/GameState/Menu/Background/FOND CHOIX PERS.png", false);
sf::Sprite IncreaseButton = LoadSprite("Assets/GameState/Menu/IncreaseIn.png", true);
sf::Sprite NextImage = LoadSprite("Assets/GameState/Menu/Arrow/Right Arrow Bleu.png", true);
sf::Sprite PreviousImage = LoadSprite("Assets/GameState/Menu/Arrow/Left Arrow Bleu.png", true);
sf::Text StartSelection = loadText(GetGlobalFont(), sf::Color::White, "Appuyez sur Entrée", 40);
sf::Text DeletePlayer = loadText(GetGlobalFont(), sf::Color::White, "Appuyez sur la touche \"Retour\" pour enlever un joueur !", 40);
sf::Sprite BackgroundGame = LoadSprite("Assets/GameState/Game_Fish/Background.png", false);
std::vector<struct Player> NumberPlayer;
sf::Sprite Picture[8]
{
	Picture[0] = LoadSprite("Assets/GameState/menu/Photo profil/Boy 1.png", true),
	Picture[1] = LoadSprite("Assets/GameState/menu/Photo profil/Boy 2.png", true),
	Picture[2] = LoadSprite("Assets/GameState/menu/Photo profil/Boy 3.png", true),
	Picture[3] = LoadSprite("Assets/GameState/menu/Photo profil/Boy 4.png", true),
	Picture[4] = LoadSprite("Assets/GameState/menu/Photo profil/Girl 1.png", true),
	Picture[5] = LoadSprite("Assets/GameState/menu/Photo profil/Girl 2.png", true),
	Picture[6] = LoadSprite("Assets/GameState/menu/Photo profil/Girl 3.png", true),
	Picture[7] = LoadSprite("Assets/GameState/menu/Photo profil/Girl 4.png", true)

};

sf::Sprite Card[4]
{
	Card[0] = LoadSprite("Assets/GameState/Menu/Carte/carte Bleu.png", true),
	Card[1] = LoadSprite("Assets/GameState/Menu/Carte/carte Rouge.png", true),
	Card[2] = LoadSprite("Assets/GameState/Menu/Carte/carte Verte.png", true),
	Card[3] = LoadSprite("Assets/GameState/Menu/Carte/carte Orange.png", true)
};

sf::Sprite pictureButton[8]
{
	pictureButton[0] = LoadSprite("Assets/GameState/Menu/Arrow/Right Arrow Bleu.png", true),
	pictureButton[1] = LoadSprite("Assets/GameState/Menu/Arrow/Left Arrow Bleu.png", true),
	pictureButton[2] = LoadSprite("Assets/GameState/Menu/Arrow/Right Arrow Rouge.png", true),
	pictureButton[3] = LoadSprite("Assets/GameState/Menu/Arrow/Left Arrow Rouge.png", true),
	pictureButton[4] = LoadSprite("Assets/GameState/Menu/Arrow/Right Arrow Vert.png", true),
	pictureButton[5] = LoadSprite("Assets/GameState/Menu/Arrow/Left Arrow Vert.png", true),
	pictureButton[6] = LoadSprite("Assets/GameState/Menu/Arrow/Right Arrow Orange.png", true),
	pictureButton[7] = LoadSprite("Assets/GameState/Menu/Arrow/Left Arrow Orange.png", true)
};

std::vector <PlayerCard> PlayerVector;
int nmbPlayer = 1;
int posXmouse = sf::Mouse::getPosition().x;
int posYmouse = sf::Mouse::getPosition().y;
int alpha = 255;
bool Gamestarted;
int changeDir;
int PPtoCheck = 0;

void CheckIfPPAreFree(int _index)
{	
	if (PlayerVector[PPtoCheck].curentPP == PlayerVector[_index].curentPP)
	{
		PlayerVector[PPtoCheck].curentPP += changeDir;
	}
	
}
void AddCardPlayer()
{
	PlayerCard newCarte;
	switch (nmbPlayer)
	{
	case 1:
		newCarte.Card = Card[0];
		newCarte.curentPP = 0;
		PPtoCheck = 0;
		newCarte.Card.setColor(sf::Color(0, 0, 255, 255));
		newCarte.rightButton = pictureButton[0];
		newCarte.leftButton = pictureButton[1];
		break;
	case 2:
		newCarte.Card = Card[1];
		newCarte.curentPP = 1;
		PPtoCheck = 1;
		newCarte.rightButton = pictureButton[2];
		newCarte.leftButton = pictureButton[3];
		break;
	case 3:
		newCarte.Card = Card[2];
		newCarte.curentPP = 2;
		PPtoCheck = 2;
		newCarte.rightButton = pictureButton[4];
		newCarte.leftButton = pictureButton[5];
		break;
	case 4:
		newCarte.Card = Card[3];
		newCarte.curentPP = 3;
		PPtoCheck = 3;
		newCarte.rightButton = pictureButton[6];
		newCarte.leftButton = pictureButton[7];
		break;
	}
	nmbPlayer++;
	PlayerVector.push_back(newCarte);
}



void UpdatePPConflict()
{
	for (int i = 0; i < PlayerVector.size(); i++)
	{
		if (PPtoCheck != i)
		{
			CheckIfPPAreFree(i);
		}	
	}
	for (int i = 0; i < PlayerVector.size(); i++)
	{
		if (PlayerVector[i].curentPP > 7)
		{
			PlayerVector[i].curentPP = 0;
		}

		if (PlayerVector[i].curentPP < 0)
		{
			PlayerVector[i].curentPP = 7;
		}
	}
}


void ButtonPressed(sf::Event _event)
{
	for (int i = 0; i < PlayerVector.size(); i++)
	{
		if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && posXmouse < PlayerVector[i].rightpos.x + PreviousImage.getTexture()->getSize().x / 2 && posXmouse > PlayerVector[i].rightpos.x - PreviousImage.getTexture()->getSize().x / 2
			&& posYmouse > PlayerVector[i].rightpos.y - PreviousImage.getTexture()->getSize().y / 2 && posYmouse < PlayerVector[i].rightpos.y + PreviousImage.getTexture()->getSize().y / 2)
		{
			PlayerVector[i].curentPP++;
			changeDir = 1;
			PPtoCheck = i;
		}
		if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && posXmouse < PlayerVector[i].leftpos.x + PreviousImage.getTexture()->getSize().x / 2 && posXmouse > PlayerVector[i].leftpos.x - PreviousImage.getTexture()->getSize().x / 2
			&& posYmouse > PlayerVector[i].leftpos.y - PreviousImage.getTexture()->getSize().y / 2 && posYmouse < PlayerVector[i].leftpos.y + PreviousImage.getTexture()->getSize().y / 2)
		{
			PlayerVector[i].curentPP--;
			changeDir = -1;
			PPtoCheck = i;
		}
	}
}

void MinusPlayer()
{
	if (PlayerVector.size() > 2)
	{
		PlayerVector.pop_back();
		nmbPlayer--;
	}
}

/////////////////////////FONCTION SACREE/////////////////////////

void LoadSelection()
{
	StartSelection.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 1.5) + SCREEN_HEIGHT * 0.2);
	DeletePlayer.setPosition(SCREEN_WIDTH / 2, 100);
	for (int i = 0; i < 8; i++)
	{
		Picture[i].setScale({ 0.18,0.18 });
	}
	AddCardPlayer();
	AddCardPlayer();
}

void UpdateSelection(float _dt)
{
	posXmouse = sf::Mouse::getPosition().x;
	posYmouse = sf::Mouse::getPosition().y;
	IncreaseButton.setPosition((float)SCREEN_HEIGHT / 1.5 + (PlayerVector.size() - 1) * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2);
	UpdatePPConflict();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posXmouse < IncreaseButton.getPosition().x + IncreaseButton.getTexture()->getSize().x / 2 && posXmouse > IncreaseButton.getPosition().x - IncreaseButton.getTexture()->getSize().x / 2
		&& posYmouse > IncreaseButton.getPosition().y - IncreaseButton.getTexture()->getSize().y / 2 && posYmouse < IncreaseButton.getPosition().y + IncreaseButton.getTexture()->getSize().y / 2)
	{
		AddCardPlayer();
	}

	for (int i = 0; i < PlayerVector.size(); i++)
	{
		PlayerVector[i].rightpos = { (float)(i * 480) + PlayerVector[i].Card.getTexture()->getSize().x + 65, 425 };
		PlayerVector[i].leftpos = { (float)(i * 480) + 153, 425 };
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || Gamestarted)
	{
		Gamestarted = true;

		alpha -= _dt * 300;

		if (alpha <= 0)
		{
			LoadPlayer(PlayerVector.size());

			for (int i = 0; i < PlayerVector.size(); i++)
			{
				GetPlayer(i).avatar = Picture[PlayerVector[i].curentPP];
				GetPlayer(i).avatar.setColor(sf::Color(255, 255, 255, 255));
			}


			Gamestarted = false;
			alpha = 255;

			SetGameState(GAME_QUIZ);
		}
	}

	IncreaseButton.setColor(sf::Color(255, 255, 255, alpha));
	StartSelection.setFillColor(sf::Color(255, 255, 255, alpha));
	DeletePlayer.setFillColor(sf::Color(255, 255, 255, alpha));
	for (int i = 0; i < PlayerVector.size(); i++)
	{
		PlayerVector[i].Card.setColor(sf::Color(255, 255, 255, alpha));
		PlayerVector[i].rightButton.setColor(sf::Color(255, 255, 255, alpha));
		PlayerVector[i].leftButton.setColor(sf::Color(255, 255, 255, alpha));
		Picture[PlayerVector[i].curentPP].setColor(sf::Color(255, 255, 255, alpha));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		SetGameState(MENU);
	}

	if (alpha == 255)
	{
		static float Transparence = 255;
		static float a = 0;

		a += 2 * _dt;
		Transparence = 126 * (cosf(a) + 1);
		StartSelection.setFillColor(sf::Color(255, 255, 255, Transparence));
	}


}

void DisplaySelection(sf::RenderWindow& _window)
{
	//_window.draw(BackgroundGame);
	_window.draw(backgroundSelectionSprite);
	for (int i = 0; i < PlayerVector.size(); i++)
	{
		BlitSprite(PlayerVector[i].Card, { (float)(i * SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8), SCREEN_HEIGHT / 2 }, 0, _window);
		BlitSprite(PlayerVector[i].leftButton, PlayerVector[i].leftpos, 0, _window);
		BlitSprite(PlayerVector[i].rightButton, PlayerVector[i].rightpos, 0, _window);
		BlitSprite(Picture[PlayerVector[i].curentPP], { (float)(i * SCREEN_WIDTH / 4 + SCREEN_WIDTH / 8), SCREEN_HEIGHT / 2 - 120 }, 0, _window);
	}

	BlitSprite(IncreaseButton, IncreaseButton.getPosition(), 0, _window);

	_window.draw(DeletePlayer);
	_window.draw(StartSelection);
}