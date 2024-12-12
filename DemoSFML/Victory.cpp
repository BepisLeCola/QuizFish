#include "Victory.hpp"
#include "Settings.hpp"
sf::Sprite bgVictory;
sf::Sprite podium;
sf::Sprite rewards[3];


sf::Font fontVict;
sf::Text scores[3];
sf::Text resultat;

Player first;
Player second;
Player third;
sf::Sound victorySound;
sf::SoundBuffer victorySoundBuffer;
void LoadVictory(void)
{
	victorySoundBuffer.loadFromFile("Audio/SoundEffect/FishingSuccess.ogg");
	victorySound.setBuffer(victorySoundBuffer);
	bgVictory = LoadSprite("Assets/GameState/Endgame/Background.png", false);
	podium = LoadSprite("Assets/GameState/Endgame/podium.png", true);
	rewards[1] = LoadSprite("Assets/GameState/Endgame/reward1.png", true);
	rewards[0] = LoadSprite("Assets/GameState/Endgame/reward2.png", true);
	rewards[2] = LoadSprite("Assets/GameState/Endgame/reward3.png", true);

	fontVict.loadFromFile("Assets/Font/Sunny Spells.ttf");

	podium.setPosition({ (float)SCREEN_WIDTH / 2,(float)SCREEN_HEIGHT - podium.getTexture()->getSize().y / 2 });
	for (int k = 0; k < 3; k++)
	{
		sf::Vector2f pos;
		pos.x = (float)(podium.getPosition().x - podium.getTexture()->getSize().x / 2) + (k * (podium.getTexture()->getSize().x / 3)) + 100;

		switch (k)
		{
		case 0:
			pos.y = (float)SCREEN_HEIGHT - (podium.getTexture()->getSize().y - 97) - (rewards[k].getTexture()->getSize().y - 10);
			break;
		case 1:
			pos.y = (float)SCREEN_HEIGHT - podium.getTexture()->getSize().y - (rewards[k].getTexture()->getSize().y - 10);
			break;
		case 2:
			pos.y = (float)SCREEN_HEIGHT - (podium.getTexture()->getSize().y - 168) - (rewards[k].getTexture()->getSize().y - 10);
			break;
		}

		scores[k].setFont(fontVict);
		scores[k].setString("");
		scores[k].setFillColor(sf::Color::Black);
		scores[k].setOrigin({ scores[k].getGlobalBounds().width / 2,scores[k].getGlobalBounds().height / 2 });
		scores[k].setPosition(pos);
	}

	resultat.setFont(fontVict);
	resultat.setString("Résultats");
	resultat.setFillColor(sf::Color::White);
	resultat.setCharacterSize(300);
	resultat.setOrigin({ resultat.getGlobalBounds().width / 2,resultat.getGlobalBounds().height / 2 });
	resultat.setPosition({ (float)SCREEN_WIDTH / 2, 100 });
}

void Tri3Val(Player& _player1, Player& _player2, Player& _player3)
{
	if (_player1.score > _player2.score && _player1.score > _player3.score)
	{
		if (_player2.score > _player3.score)
		{
			first = _player1;
			second = _player2;
			third = _player3;
		}
		else
		{
			first = _player1;
			second = _player3;
			third = _player2;
		}

	}
	else if (_player2.score > _player1.score && _player2.score > _player3.score)
	{
		if (_player1.score > _player3.score)
		{
			first = _player2;
			second = _player1;
			third = _player3;
		}
		else
		{
			first = _player2;
			second = _player3;
			third = _player1;
		}
	}
	else if (_player3.score > _player1.score && _player3.score > _player2.score)
	{
		if (_player1.score > _player2.score)
		{
			first = _player3;
			second = _player1;
			third = _player2;
		}
		else
		{
			first = _player3;
			second = _player2;
			third = _player1;
		}
	}
}

//test des podiums de 4 joueurs
void Tri4Val(Player& _player1, Player& _player2, Player& _player3, Player& _player4)
{
	if (_player4.score <= _player1.score && _player4.score <= _player2.score && _player4.score <= _player3.score)
	{
		Tri3Val(_player1, _player2, _player3);
	}
	else if (_player3.score <= _player1.score && _player3.score <= _player2.score && _player3.score <= _player4.score)
	{
		Tri3Val(_player1, _player2, _player4);
	}
	else if (_player2.score <= _player1.score && _player2.score <= _player3.score && _player2.score <= _player4.score)
	{
		Tri3Val(_player1, _player3, _player4);
	}
	else if (_player1.score <= _player2.score && _player1.score <= _player3.score && _player1.score <= _player4.score)
	{
		Tri3Val(_player2, _player3, _player4);
	}
	else
	{
		std::cout << "nope" << std::endl;
	}
}

//Gloabl update for victory state
void UpdateVictory(float _dt)
{
	victorySound.setVolume(ReturnVolume());
	if (victorySound.getStatus() != sf::Sound::Status::Playing)
	{
		victorySound.play();
	}
	switch (GetPlayersVector().size())
	{
	case 2:
		if (GetPlayer(0).score > GetPlayer(1).score)
		{
			first = GetPlayer(0);
			second = GetPlayer(1);
		}
		else
		{
			first = GetPlayer(1);
			second = GetPlayer(0);
		}
			//Premier
			scores[1].setString(std::to_string(first.score));
			scores[1].setOrigin({ scores[1].getGlobalBounds().width / 2,scores[1].getGlobalBounds().height / 2 });

			//Second
			scores[0].setString(std::to_string(second.score));
			scores[0].setOrigin({ scores[0].getGlobalBounds().width / 2,scores[0].getGlobalBounds().height / 2 });
		break;
	case 3:

		Tri3Val(GetPlayer(0), GetPlayer(1), GetPlayer(2));

		//Premier
		scores[1].setString(std::to_string(first.score));
		scores[1].setOrigin({ scores[1].getGlobalBounds().width / 2,scores[1].getGlobalBounds().height / 2 });

		//Second
		scores[0].setString(std::to_string(second.score));
		scores[0].setOrigin({ scores[0].getGlobalBounds().width / 2,scores[0].getGlobalBounds().height / 2 });

		//Troisieme
		scores[2].setString(std::to_string(third.score));
		scores[2].setOrigin({ scores[2].getGlobalBounds().width / 2,scores[2].getGlobalBounds().height / 2 });
		break;
	case 4:

		Tri4Val(GetPlayer(0), GetPlayer(1), GetPlayer(2), GetPlayer(3));


		//Premier
		scores[1].setString(std::to_string(first.score));
		scores[1].setOrigin({ scores[1].getGlobalBounds().width / 2,scores[1].getGlobalBounds().height / 2 });

		//Second
		scores[0].setString(std::to_string(second.score));
		scores[0].setOrigin({ scores[0].getGlobalBounds().width / 2,scores[0].getGlobalBounds().height / 2 });

		//Troisieme
		scores[2].setString(std::to_string(third.score));
		scores[2].setOrigin({ scores[2].getGlobalBounds().width / 2,scores[2].getGlobalBounds().height / 2 });
		break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		StopConfettis();
		ReloadPlayers();
		LoadQuestions();
		SetGameState(MENU);
	}

}

//Global Display for Victory
void DisplayVictory(sf::RenderWindow& _window)
{
	BlitSprite(bgVictory, { 0,0 }, 0, _window);
	BlitSprite(podium, { (float)SCREEN_WIDTH / 2,(float)SCREEN_HEIGHT - podium.getTexture()->getSize().y/2}, 0, _window);
	_window.draw(resultat);

	switch (GetPlayersVector().size())
	{
	case 2:
		BlitSprite(first.avatar, { scores[1].getPosition().x, scores[1].getPosition().y - 45 }, 0, _window);
		BlitSprite(second.avatar, { scores[0].getPosition().x, scores[0].getPosition().y - 45 }, 0, _window);
		break;
	case 3:
		BlitSprite(first.avatar, { scores[1].getPosition().x, scores[1].getPosition().y - 45 }, 0, _window);
		BlitSprite(second.avatar, { scores[0].getPosition().x, scores[0].getPosition().y - 45 }, 0, _window);
		BlitSprite(third.avatar, { scores[2].getPosition().x, scores[2].getPosition().y - 45 }, 0, _window);
		break;
	case 4:
		BlitSprite(first.avatar, { scores[1].getPosition().x, scores[1].getPosition().y - 45 }, 0, _window);
		BlitSprite(second.avatar, { scores[0].getPosition().x, scores[0].getPosition().y - 45 }, 0, _window);
		BlitSprite(third.avatar, { scores[2].getPosition().x, scores[2].getPosition().y - 45 }, 0, _window);
		break;
	}

	//draw rewards and scores
	for (int k = 0; k < 3; k++)
	{
		sf::Vector2f pos;
		pos.x = (float)(podium.getPosition().x - podium.getTexture()->getSize().x / 2) + (k * (podium.getTexture()->getSize().x / 3)) + 100 ;

		switch (k)
		{
		case 0:
			pos.y = (float)SCREEN_HEIGHT - (podium.getTexture()->getSize().y-97) - (rewards[k].getTexture()->getSize().y / 2);
			break;
		case 1:
			pos.y = (float)SCREEN_HEIGHT - podium.getTexture()->getSize().y  - (rewards[k].getTexture()->getSize().y/2);
			break;
		case 2:
			pos.y = (float)SCREEN_HEIGHT - (podium.getTexture()->getSize().y - 168) - (rewards[k].getTexture()->getSize().y / 2);
			break;
		}
		
		BlitSprite(rewards[k], pos , 0, _window);

		_window.draw(scores[k]);

	}

}