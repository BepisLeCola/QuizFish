#include "Credits.hpp"

sf::Text credits[12];
sf::Font font;
sf::Texture backgroundCreditsTexture;
sf::Sprite backgroundCreditsSprite; 
int posY = SCREEN_HEIGHT / 2;


sf::Text loadText(std::string font, sf::Color _color, std::string _text, int _size)
{
	sf::Text Text;
	sf::Font* tempfont = new sf::Font();
	tempfont->loadFromFile(font);
	Text.setFont(*tempfont);
	Text.setFillColor(_color);
	Text.setString(_text);
	Text.setCharacterSize(_size);
	Text.setOrigin(Text.getLocalBounds().width / 2., Text.getLocalBounds().height / 2.);
	return Text;
}

void LoadBackgroundCredits(void)
{
	backgroundCreditsTexture.loadFromFile("Assets/GameState/Menu/Background/Background.png");
	backgroundCreditsSprite.setTexture(backgroundCreditsTexture);
	backgroundCreditsSprite.setOrigin(backgroundCreditsTexture.getSize().x / 2, backgroundCreditsTexture.getSize().y / 2);
	backgroundCreditsSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
}

void LoadCredits()
{
	LoadBackgroundCredits();
	posY = SCREEN_HEIGHT / 2;

	credits[0] = loadText(GetGlobalFont(), sf::Color::White, "Programmeurs :", 100);
	credits[1] = loadText(GetGlobalFont(), sf::Color::White, "\nKillian Almenar", 100);
	credits[2] = loadText(GetGlobalFont(), sf::Color::White, "\nLuc D'eurveilher", 100);
	credits[3] = loadText(GetGlobalFont(), sf::Color::White, "\nCharles De Souza", 100);
	credits[4] = loadText(GetGlobalFont(), sf::Color::White, "\nNeyl Mahfouf", 100);
	credits[5] = loadText(GetGlobalFont(), sf::Color::White, "\nYohann Morits", 100);
	credits[6] = loadText(GetGlobalFont(), sf::Color::White, "\nAntoine Richard", 100);
	credits[7] = loadText(GetGlobalFont(), sf::Color::White, "\n\nGraphistes :", 100);
	credits[8] = loadText(GetGlobalFont(), sf::Color::White, "\n\n\nLana Gratreaud", 100);
	credits[9] = loadText(GetGlobalFont(), sf::Color::White, "\n\n\nBechir Khalfallah", 100);
	credits[10] = loadText(GetGlobalFont(), sf::Color::White, "\n\n\nIan Le Bihan", 100);
	credits[11] = loadText(GetGlobalFont(), sf::Color::White, "\n\n\nNathan Robert", 100);

	for (int i = 0; i < 12; i++)
	{
		credits[i].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (posY + i * 100));
	}

}



void UpdateCredits(float _dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		SetGameState(SETTINGS);
	}
	for (int i = 0; i < 12; i++)
	{
		credits[i].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (posY + i * 100));
	}

	posY -= 1;


}

void DisplayCredits(sf::RenderWindow& _window)
{
	_window.draw(backgroundCreditsSprite);
	for (int i = 0; i < 12; i++)
	{
		_window.draw(credits[i]);
	}
}