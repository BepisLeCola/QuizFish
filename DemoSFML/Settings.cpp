#include "Settings.hpp"

sf::Texture backOutTexture;
sf::Texture backInTexture;
sf::Texture creditOutTexture;
sf::Texture creditInTexture;
sf::Texture backgroundTextureSettings;
sf::Sprite bgSettings;
sf::Sprite backgroundSpriteSettings;
sf::Sprite ButtonSprite = LoadSprite("Assets/GameState/Menu/volume/Fichier 5.png", true);
sf::Sprite BarreFull = LoadSprite("Assets/GameState/Menu/volume/Fichier 3.png", false);
sf::Sprite BarreEmpty = LoadSprite("Assets/GameState/Menu/volume/Fichier 4.png", true);
sf::Texture MuteOutTexture;
sf::Texture MuteInTexture;
sf::Sound selectMenuSoundSettings;
sf::SoundBuffer selectMenuSoundBufferSettings;
bool IsButtonPressed = false;
bool IsMuteButtonPressed = false;
float VolumePercent;
float VolumeTotal = 100;
float VoiceVolume;

sf::Text GeneralVolumeText = loadText(GetGlobalFont(), sf::Color::White, "Volume Principal :", 40);
sf::Text VoiceMute = loadText(GetGlobalFont(), sf::Color::White, "Voix des questions :", 40);

struct VolumeBarre
{
	sf::Vector2f Pos;
	float Sound;
	sf::Sprite sprite;
};

Button backButton;
Button creditButton;
Button MuteButton;

VolumeBarre GeneralBarre;
VolumeBarre GeneralButton;
sf::Vector2f distancebutton;
void LoadSESettings()
{
	selectMenuSoundBufferSettings.loadFromFile("Audio/SoundEffect/SelectMenuSound.ogg");
	selectMenuSoundSettings.setBuffer(selectMenuSoundBufferSettings);
}
float ReturnVolume()
{
	return VolumeTotal;
}
void LoadBgSetttings(void)
{
	bgSettings = LoadSprite("Assets/GameState/Menu/Background/Background.png", false);
}

void LoadBackgroundSettings(void)
{
	backgroundTextureSettings.loadFromFile("Assets/GameState/Menu/Background/Background.png");
	backgroundSpriteSettings.setTexture(backgroundTextureSettings);
	backgroundSpriteSettings.setOrigin(backgroundTextureSettings.getSize().x / 2, backgroundTextureSettings.getSize().y / 2);
	backgroundSpriteSettings.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
}

void LoadBackButton()
{
	backOutTexture.loadFromFile("Assets/GameState/Menu/Back/Back_Out.png");
	backInTexture.loadFromFile("Assets/GameState/Menu/Back/Back_In.png");
	backButton.sprite.setTexture(backOutTexture);
	backButton.sprite.setOrigin(backOutTexture.getSize().x / 2, backOutTexture.getSize().y / 2);
	backButton.sprite.setPosition(sf::Vector2f( SCREEN_WIDTH / 15, SCREEN_HEIGHT - 60));
	backButton.pos.x = SCREEN_WIDTH / 15;
	backButton.pos.y = SCREEN_HEIGHT - 60;
}

void LoadCreditsButton()
{
	creditOutTexture.loadFromFile("Assets/GameState/Settings/Credit_Out.png");
	creditInTexture.loadFromFile("Assets/GameState/Settings/Credit_In.png");
	creditButton.sprite.setTexture(creditOutTexture);
	creditButton.sprite.setOrigin(creditOutTexture.getSize().x / 2, creditOutTexture.getSize().y / 2);
	creditButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60));
	creditButton.pos.x = SCREEN_WIDTH / 2;
	creditButton.pos.y = SCREEN_HEIGHT - 60;
}

void LoadVolumeButton()
{
	BarreEmpty.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	GeneralBarre.sprite = BarreFull;
	GeneralBarre.Pos = { SCREEN_WIDTH / 2 - (float)BarreEmpty.getTexture()->getSize().x / 2, SCREEN_HEIGHT / 2 - (float)BarreEmpty.getTexture()->getSize().y / 2 };
	GeneralButton.Pos = { BarreEmpty.getPosition().x + BarreEmpty.getTexture()->getSize().x / 2 , SCREEN_HEIGHT / 2 };
	ButtonSprite.setPosition(GeneralButton.Pos);
	GeneralButton.sprite = ButtonSprite;
	GeneralVolumeText.setPosition(GeneralBarre.Pos.x + GeneralVolumeText.getGlobalBounds().width / 2, ButtonSprite.getPosition().y - ButtonSprite.getTexture()->getSize().y / 2 - GeneralVolumeText.getGlobalBounds().height * 1.20);
}

void LoadMuteVoiceButton()
{
	MuteOutTexture.loadFromFile("Assets/GameState/Menu/volume/relaché.png");
	MuteInTexture.loadFromFile("Assets/GameState/Menu/volume/appuyé.png");
	MuteButton.sprite.setTexture(MuteOutTexture);
	MuteButton.sprite.setOrigin(MuteOutTexture.getSize().x / 2, MuteOutTexture.getSize().y / 2);
	MuteButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH - 128, SCREEN_HEIGHT - 50));
	MuteButton.pos.x = SCREEN_WIDTH - 128;
	MuteButton.pos.y = SCREEN_HEIGHT - 50;
}

void VolumeButtonPressed()
{
	if (sqrtf(distancebutton.x * distancebutton.x + distancebutton.y * distancebutton.y) < ButtonSprite.getTexture()->getSize().x / 2)
	{
		IsButtonPressed = true;
	}
}

void VolumeButtonReleased()
{
	IsButtonPressed = false;
}

void MuteVoiceBool()
{
	if (GetMousePos().x < MuteButton.sprite.getPosition().x + MuteOutTexture.getSize().x / 2 && GetMousePos().x > MuteButton.sprite.getPosition().x - MuteOutTexture.getSize().x / 2
		&& GetMousePos().y > MuteButton.sprite.getPosition().y - MuteOutTexture.getSize().y / 2 && GetMousePos().y < MuteButton.sprite.getPosition().y + MuteOutTexture.getSize().y / 2)
	{
		if (IsMuteButtonPressed)
		{
			VoiceVolume = 100;
			IsMuteButtonPressed = false;
		}
		else
		{
			VoiceVolume = 0;
			IsMuteButtonPressed = true;
		}
	}
}


//////////////////////////////////////// Fonctions sacrées


void LoadSettings()
{
	LoadBgSetttings();
	LoadBackButton();
	LoadCreditsButton();
	LoadBackgroundSettings();
	LoadVolumeButton();
	LoadMuteVoiceButton();
	LoadSESettings();
}

void UpdateSettings(float _dt)
{
	selectMenuSoundSettings.setVolume(VolumeTotal);
	UpdateButtonTimer(_dt, backButton, backOutTexture, backInTexture, MENU);
	UpdateButtonTimer(_dt, creditButton, creditOutTexture, creditInTexture, CREDIT);
	//UpdateButtonTimer(_dt, MuteButton, MuteOutTexture, MuteInTexture, SETTINGS);
	int posXmouse = GetMousePos().x;
	int posYmouse = GetMousePos().y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posXmouse < backButton.sprite.getPosition().x + backOutTexture.getSize().x / 2 && posXmouse > backButton.sprite.getPosition().x - backOutTexture.getSize().x / 2
		&& posYmouse > backButton.sprite.getPosition().y - backOutTexture.getSize().y / 2 && posYmouse < backButton.sprite.getPosition().y + backOutTexture.getSize().y / 2)
	{
		selectMenuSoundSettings.play();
		if (backButton.test != 1)
		{
			backButton.test = 1;
			backButton.timer = 0.5;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && posXmouse < creditButton.sprite.getPosition().x + creditOutTexture.getSize().x / 2 && posXmouse > creditButton.sprite.getPosition().x - creditOutTexture.getSize().x / 2
		&& posYmouse > creditButton.sprite.getPosition().y - creditOutTexture.getSize().y / 2 && posYmouse < creditButton.sprite.getPosition().y + creditOutTexture.getSize().y / 2)
	{
		selectMenuSoundSettings.play();
		LoadCredits();

		if (creditButton.test != 1)
		{
			creditButton.test = 1;
			creditButton.timer = 0.5;
		}

	}

	if (IsMuteButtonPressed)
	{
		MuteButton.sprite.setTexture(MuteInTexture);
	}
	else if (!IsMuteButtonPressed)
	{
		MuteButton.sprite.setTexture(MuteOutTexture);
	}

	VolumePercent = GeneralButton.Pos.x - GeneralBarre.Pos.x;

	BarreFull.setTextureRect({ 0,0 , (int)VolumePercent, (int)BarreFull.getTexture()->getSize().y });

	backButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 15, SCREEN_HEIGHT - 50));
	MuteButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH - 128, SCREEN_HEIGHT - 50));
	creditButton.sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50));

	distancebutton = { posXmouse - GeneralButton.sprite.getPosition().x, posYmouse - GeneralButton.sprite.getPosition().y };

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sqrtf(distancebutton.x * distancebutton.x + distancebutton.y * distancebutton.y) < 25 || IsButtonPressed)
	{
		GeneralButton.Pos.x = posXmouse;
	}
	GeneralButton.sprite.setPosition(GeneralButton.Pos);

	if (GeneralButton.Pos.x <= BarreEmpty.getPosition().x - BarreEmpty.getTexture()->getSize().x / 2)
	{
		GeneralButton.Pos.x = BarreEmpty.getPosition().x - BarreEmpty.getTexture()->getSize().x / 2 + 1;
	}

	if (GeneralButton.Pos.x >= BarreEmpty.getPosition().x + BarreEmpty.getTexture()->getSize().x / 2)
	{
		GeneralButton.Pos.x = BarreEmpty.getPosition().x + BarreEmpty.getTexture()->getSize().x / 2 - 1;

	}
	VolumeTotal = VolumePercent / 949.5 * 100;

}

void DisplaySettings(sf::RenderWindow& _window)
{
	BlitSprite(bgSettings, { 0, 0 }, 0, _window);
	BlitSprite(BarreEmpty, BarreEmpty.getPosition(), 0, _window);
	BlitSprite(BarreFull, { GeneralBarre.Pos.x, GeneralBarre.Pos.y }, 0, _window);
	BlitSprite(ButtonSprite, GeneralButton.Pos, 0, _window);
	BlitSprite(MuteButton.sprite, MuteButton.pos, 0, _window);

	_window.draw(backButton.sprite);
	_window.draw(creditButton.sprite);
	_window.draw(GeneralVolumeText);
}

bool getMuteState()
{
	return IsMuteButtonPressed;
}