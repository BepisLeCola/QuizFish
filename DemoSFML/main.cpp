#include "Game.hpp"

sf::Image iconImage;
sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Quiz Fish", sf::Style::Fullscreen);

int main()
{
	srand((unsigned int)time(NULL));
	rand(); rand(); rand();

	window.setFramerateLimit(60);

	iconImage.loadFromFile("Assets/Icon.png");
	window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

	Load();

	sf::Clock dtClock;
	//Boucle de jeu, qui maintiens le programme en action
	while (window.isOpen())
	{
		float dt = dtClock.restart().asSeconds();

		//Traitement des événements souris/clavier/fenêtre/etc, partie obligatoire
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //Si appui sur le bouton quitter de la fenêtre, fermeture du programme
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					if (GetGameState() == GAME_FISH)
					{
						PickFish(dt);
					}
					else
					{
						PlayClicFx((sf::Vector2f)sf::Mouse::getPosition(window));
					}
					if (GetGameState() == SELECTION)
					{
						ButtonPressed(event);
					}
					if (GetGameState() == SETTINGS)
					{
						VolumeButtonPressed();
						MuteVoiceBool();
					}

					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (GetGameState() == SETTINGS);
				{
					VolumeButtonReleased();
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::BackSpace)
				{
					if (GetGameState() == SELECTION)
					{
						MinusPlayer();
					}
				}
			}
		}

		Update(dt);
		Display(window);
	}
}