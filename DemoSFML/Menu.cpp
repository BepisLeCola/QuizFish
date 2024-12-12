#include "Menu.hpp"
#include "Settings.hpp"
#pragma region ACCUEIL
sf::Sprite backgroundSprite;
sf::Texture backgroundTexture;
sf::Texture settingsOutTexture;
sf::Texture settingsInTexture;
sf::Texture quitOutTexture;
sf::Texture playOutTexture;
sf::Texture playInTexture;
sf::Texture quitInTexture;
sf::Texture logoTexture;
sf::Sprite logoSprite;
sf::Sound selectMenuSound;
sf::SoundBuffer selectMenuSoundBuffer;
std::string GetGlobalFont()
{
	std::string GlobalFont = "Assets/Font/Sunny Spells.ttf";
	return GlobalFont;
}

sf::Text Start = loadText(GetGlobalFont(), sf::Color::White, "Appuyez sur Entrée", 80);

Button playButton;
Button settingsButton;
Button quitButton;

void LoadSEMenu()
{
	selectMenuSoundBuffer.loadFromFile("Audio/SoundEffect/SelectMenuSound.ogg");
	selectMenuSound.setBuffer(selectMenuSoundBuffer);
}
void UpdateButtonTimer(float _dt, struct Button& _button, sf::Texture& _OutTexture, sf::Texture& _InTexture, GameState _state)
{
	if (_button.timer > 0)
	{
		_button.sprite.setPosition(_button.pos.x + DIFFPIXEL, _button.pos.y + DIFFPIXEL);
		_button.texture = _InTexture;
		_button.sprite.setTexture(_button.texture);
		_button.timer -= _dt * 3;
	}
	else
	{
		if (_button.test == 1)
		{
			SetGameState(_state);
			_button.texture = _OutTexture;
			_button.sprite.setTexture(_button.texture);
		}
		_button.test = 0;
	}
}

void LoadLogo()
{
	logoTexture.loadFromFile("Assets/GameState/Menu/Background/Logo Jeux.png");
	logoSprite.setTexture(logoTexture);
	logoSprite.setOrigin(logoTexture.getSize().x / 2, logoTexture.getSize().y / 2);
	logoSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3));
}

void LoadExitButton()
{
	quitOutTexture.loadFromFile("Assets/GameState/Menu/Quit/Quit_Out.png");
	quitInTexture.loadFromFile("Assets/GameState/Menu/Quit/Quit_In.png");
	quitButton.sprite.setTexture(quitOutTexture);
	quitButton.sprite.setOrigin(quitOutTexture.getSize().x / 2, quitOutTexture.getSize().y / 2);
	quitButton.sprite.setPosition(sf::Vector2f(75, SCREEN_HEIGHT - 75));
	quitButton.pos.x = 75;
	quitButton.pos.y = SCREEN_HEIGHT - 75;
}

void LoadBackground(void)
{
	backgroundTexture.loadFromFile("Assets/GameState/Menu/Background/Background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
	backgroundSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
}

void LoadSettingsButton(void)
{
	settingsOutTexture.loadFromFile("Assets/GameState/Menu/Settings/Settings_Out.png");
	settingsInTexture.loadFromFile("Assets/GameState/Menu/Settings/Settings_In.png");
	settingsButton.sprite.setTexture(settingsOutTexture);
	settingsButton.sprite.setOrigin(settingsOutTexture.getSize().x / 2, settingsOutTexture.getSize().y / 2);
	settingsButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 75));
	settingsButton.pos.x = SCREEN_WIDTH - 75;
	settingsButton.pos.y = SCREEN_HEIGHT - 75;
}

#pragma endregion 

//////////////////////////////////////// Fonctions sacrées ////////////////////////////////////////

void Loadmenu()
{
	LoadBackground();
	LoadSettingsButton();
	LoadExitButton();
	LoadLogo();
	LoadSEMenu();
	Start.setPosition(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT * 0.2));
}

void UpdateMenu(float _dt)
{
	selectMenuSound.setVolume(ReturnVolume());
	UpdateButtonTimer(_dt, playButton, playOutTexture, playInTexture, SELECTION);
	UpdateButtonTimer(_dt, settingsButton, settingsOutTexture, settingsInTexture, SETTINGS);
	UpdateButtonTimer(_dt, quitButton, quitOutTexture, quitInTexture, QUIT);
	int posXmouse = GetMousePos().x;
	int posYmouse = GetMousePos().y;



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posXmouse < quitButton.sprite.getPosition().x + quitOutTexture.getSize().x / 2 && posXmouse > quitButton.sprite.getPosition().x - quitOutTexture.getSize().x / 2
		&& posYmouse > quitButton.sprite.getPosition().y - quitOutTexture.getSize().y / 2 && posYmouse < quitButton.sprite.getPosition().y + quitOutTexture.getSize().y / 2)
	{
		if (quitButton.test != 1)
		{
			selectMenuSound.play();
			quitButton.test = 1;
			quitButton.timer = 0.5;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		selectMenuSound.play();
		playButton.pressed = true;
		if (playButton.test != 1)
		{
			playButton.test = 1;
			playButton.timer = 0.5;
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posXmouse < settingsButton.sprite.getPosition().x + settingsOutTexture.getSize().x / 2 && posXmouse > settingsButton.sprite.getPosition().x - settingsOutTexture.getSize().x / 2
		&& posYmouse > settingsButton.sprite.getPosition().y - settingsOutTexture.getSize().y / 2 && posYmouse < settingsButton.sprite.getPosition().y + settingsOutTexture.getSize().y / 2)
	{
		selectMenuSound.play();
		if (settingsButton.test != 1)
		{
			settingsButton.test = 1;
			settingsButton.timer = 0.5;
		}
	}

	static float Transparence = 255;
	static float a = 0;

	a += 2 * _dt;
	Transparence = 126 * (cosf(a) + 1);
	Start.setFillColor(sf::Color(255, 255, 255, Transparence));

	quitButton.sprite.setPosition(sf::Vector2f(75, SCREEN_HEIGHT - 75));
	settingsButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH - 75, SCREEN_HEIGHT - 75));
}

void DisplayMenu(sf::RenderWindow& _window)
{
	_window.draw(backgroundSprite);
	_window.draw(logoSprite);
	_window.draw(Start);

	//buttons
	_window.draw(settingsButton.sprite);
	_window.draw(quitButton.sprite);
}
