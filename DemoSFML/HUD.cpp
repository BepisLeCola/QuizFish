#include "HUD.hpp"

#define HUD_OFFSET_Y 31

sf::Sprite HUDSprites[4];
sf::Text yourTurnText;
sf::Sprite inventorySprite[4];
sf::Sprite miniFish[6];

#define INV_Y 126
#define INV_X 83  


void FadeTextOut()
{
	yourTurnText.setFillColor(sf::Color::White);
}

void LoadMiniFishes()
{
	miniFish[LITTLE_FISH] = LoadSprite("Assets/HUD/Inventory/Little_Fish.png", true);
	miniFish[MEDIUM_FISH] = LoadSprite("Assets/HUD/Inventory/Medium_Fish.png", true);
	miniFish[LARGE_FISH] = LoadSprite("Assets/HUD/Inventory/Large_Fish.png", true);
	miniFish[CRAB] = LoadSprite("Assets/HUD/Inventory/Crab.png", true);
	miniFish[SHRIMP] = LoadSprite("Assets/HUD/Inventory/Shrimp.png", true);
	miniFish[CLAM] = LoadSprite("Assets/HUD/Inventory/Clam.png", true);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LoadHUD()
{
	LoadMiniFishes();
	for (unsigned int i = 0; i < 4; i++)
	{
		HUDSprites[i] = LoadSprite(std::format("Assets/HUD/Player{}HUD.png", i + 1), true);
		HUDSprites[i].setPosition(SCREEN_WIDTH / 2, 0 + HUDSprites[i].getTexture()->getSize().y / 1.75);

		inventorySprite[i] = LoadSprite(std::format("Assets/HUD/inventory{}.png", i + 1), false);
		inventorySprite[i].setPosition(SCREEN_WIDTH / 2 - 441 / 2, SCREEN_HEIGHT - 73);
	}
	yourTurnText = LoadText("Assets/Font/Sunny Spells.ttf", "A toi de jouer !", 64, { 0,0 }, sf::Color::White, true);
}

void UpdateHUD(float _dt)
{
	if (yourTurnText.getFillColor().a - 4 > 0)
	{
		yourTurnText.setFillColor(sf::Color(255, 255, 255, yourTurnText.getFillColor().a - 4));
	}
	else
	{
		yourTurnText.setFillColor(sf::Color(255, 255, 255, 0));
	}

	if (GetPlayersVector().size() > 0)
	{
		if (isCollindingPointRectangle(GetMousePos().x, GetMousePos().y, inventorySprite[GetPlayerTurn()].getPosition(), (sf::Vector2f)inventorySprite[GetPlayerTurn()].getTexture()->getSize()))
		{
			if (inventorySprite[GetPlayerTurn()].getPosition().y > SCREEN_HEIGHT - inventorySprite[GetPlayerTurn()].getTexture()->getSize().y)
			{
				inventorySprite[GetPlayerTurn()].setPosition(inventorySprite[GetPlayerTurn()].getPosition().x, inventorySprite[GetPlayerTurn()].getPosition().y - _dt * 400);
			}
			else
			{
				inventorySprite[GetPlayerTurn()].setPosition(inventorySprite[GetPlayerTurn()].getPosition().x, SCREEN_HEIGHT - inventorySprite[GetPlayerTurn()].getTexture()->getSize().y);
			}
		}
		else
		{
			if (inventorySprite[GetPlayerTurn()].getPosition().y < SCREEN_HEIGHT - 73)
			{
				inventorySprite[GetPlayerTurn()].setPosition(inventorySprite[GetPlayerTurn()].getPosition().x, inventorySprite[GetPlayerTurn()].getPosition().y + _dt * 400);
			}
			else
			{
				inventorySprite[GetPlayerTurn()].setPosition(inventorySprite[GetPlayerTurn()].getPosition().x, SCREEN_HEIGHT - 73);
			}
		}
	}
}

void DisplayHUD(sf::RenderWindow& _window)
{
	if (GetPlayersVector().size() > 0)
	{
		int i = GetPlayerTurn();

		BlitSprite(HUDSprites[i], HUDSprites[i].getPosition(), 0, _window);
		BlitSprite(GetPlayer(i).avatar, { HUDSprites[i].getPosition().x , HUDSprites[i].getPosition().y - HUD_OFFSET_Y }, 0, _window);
		yourTurnText.setPosition(HUDSprites[i].getPosition().x, HUDSprites[i].getPosition().y + HUDSprites[i].getTexture()->getSize().y / 2 + yourTurnText.getGlobalBounds().height / 2);
		_window.draw(yourTurnText);
		_window.draw(inventorySprite[i]);

		for (unsigned int j = 0; j < GetPlayer(i).inventaire.size(); j++)
		{
			BlitSprite(miniFish[GetPlayer(i).inventaire[j].type], inventorySprite[i].getPosition() + sf::Vector2f(INV_X + 69.f * j, INV_Y), 0, _window);
		}
	}
}