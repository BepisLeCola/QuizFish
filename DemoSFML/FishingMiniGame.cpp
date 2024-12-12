#include "FishingMiniGame.hpp"

struct FMGData
{
	sf::Sprite background;
	sf::Sprite bridge;
	sf::Sprite fishSprite[7];
	sf::Text fishTextType[7];
	sf::Text fishTextPoints[7];
	sf::Texture fishTexture[3][9];

	sf::FloatRect playArea;
	sf::Cursor cursor;
	sf::RectangleShape shape;
	struct Fish fish[MAX_FISH_IN_POND];
	int nbFishInPond;
	bool fishPicked;
	bool drawFish;
	bool transition;
	sf::Sound fishingLancer;
	sf::Sound fishingKrab;
	sf::Sound fishingWater;
	sf::SoundBuffer fishingKrabBuffer;
	sf::SoundBuffer fishingLancerBuffer;
	sf::SoundBuffer fishingWaterBuffer;
	sf::Sound fishingSuccess;
	sf::SoundBuffer fishingSuccessBuffer;
}fmgData;

#define M_PI 3.141592653589793238462643383279f

unsigned int GetPickedFishID();

FishType RandomFish()
{
	int number = rand() % 4;
	FishType Type;
	if (number > 0)
	{
		int randb = rand() % 3;
		switch (randb)
		{
		case 0:
			Type = LITTLE_FISH;
			break;
		case 1:
			Type = MEDIUM_FISH;
			break;
		case 2:
			Type = LARGE_FISH;
			break;
		}
	}
	else
	{
		int randb = rand() % 3;
		switch (randb)
		{
		case 0:
			Type = CRAB;
			break;
		case 1:
			Type = SHRIMP;
			break;
		case 2:
			Type = CLAM;
			break;
		}
	}
	return Type;
}

void DebugFishes()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = LITTLE_FISH;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = MEDIUM_FISH;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = LARGE_FISH;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = CRAB;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = SHRIMP;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		for (int i = 0; i < fmgData.nbFishInPond; i++)
		{
			fmgData.fish[i].type = CLAM;
		}
	}

}

void CreateFishes()
{
	fmgData.nbFishInPond = RandomInt(MIN_FISH_IN_POND, MAX_FISH_IN_POND);
	for (int i = 0; i < fmgData.nbFishInPond; i++)
	{
		fmgData.fish[i].shadow.setColor(sf::Color(255, 255, 255, 255));

		fmgData.fish[i].shadow.setTexture(fmgData.fish[0].texture);
		fmgData.fish[i].size.x = fmgData.fish[i].shadow.getGlobalBounds().width;
		fmgData.fish[i].size.y = fmgData.fish[i].shadow.getGlobalBounds().height;

		fmgData.fish[i].pos.x = RandomInt(fmgData.playArea.left + fmgData.fish[i].size.x / 2, fmgData.playArea.left + fmgData.playArea.width - fmgData.fish[i].size.x / 2);
		fmgData.fish[i].pos.y = RandomInt(fmgData.playArea.top + fmgData.fish[i].size.y / 2, fmgData.playArea.top + fmgData.playArea.height - fmgData.fish[i].size.y / 2);

		fmgData.fish[i].rotation = RandomInt(0, 360);
		fmgData.fish[i].cooldown = RandomInt(2, 5) + 1.f / RandomInt(1, 10);
		fmgData.fish[i].velocity = sf::Vector2f(0, 0);
		fmgData.fish[i].isPicked = false;
		fmgData.fish[i].type = RandomFish();

		for (int j = 0; j < i; j++)
		{
			if (IsCollidingCircleCircle(fmgData.fish[i].pos, fmgData.fish[i].size.x / 2, fmgData.fish[j].pos, fmgData.fish[j].size.x / 2))
			{
				fmgData.fish[i].pos.x = RandomInt(fmgData.playArea.left + fmgData.fish[i].size.x / 2, fmgData.playArea.left + fmgData.playArea.width - fmgData.fish[i].size.x / 2);
				fmgData.fish[i].pos.y = RandomInt(fmgData.playArea.top + fmgData.fish[i].size.y / 2, fmgData.playArea.top + fmgData.playArea.height - fmgData.fish[i].size.y / 2);
				j = 0;
			}
		}

		fmgData.fish[i].shadow.setRotation(fmgData.fish[i].rotation);
		fmgData.fish[i].shadow.setOrigin(sf::Vector2f(fmgData.fish[i].size.x / 2, fmgData.fish[i].size.y / 2));
		fmgData.fish[i].shadow.setPosition(fmgData.fish[i].pos);
	}
}

void ResetFishes()
{
	for (int i = 0; i < fmgData.nbFishInPond; i++)
	{
		fmgData.fish[i].shadow.setColor(sf::Color(255, 255, 255, 0));

		fmgData.fish[i].pos.x = 0;
		fmgData.fish[i].pos.y = 0;
		fmgData.fish[i].rotation = 0;

		fmgData.fish[i].shadow.setRotation(fmgData.fish[i].rotation);
		fmgData.fish[i].shadow.setPosition(fmgData.fish[i].pos);
	}
	fmgData.nbFishInPond = RandomInt(MIN_FISH_IN_POND, MAX_FISH_IN_POND);
}

void LoadFishTextures()
{
	for (unsigned int i = 0; i < 9; i++)
	{
		fmgData.fishTexture[LITTLE_FISH][i].loadFromFile(std::format("Assets/GameState/Game_Fish/Fishes/Little_Fish/Little_Fish{}.png", i + 1));
		fmgData.fishTexture[MEDIUM_FISH][i].loadFromFile(std::format("Assets/GameState/Game_Fish/Fishes/Medium_Fish/Medium_Fish{}.png", i + 1));
		fmgData.fishTexture[LARGE_FISH][i].loadFromFile(std::format("Assets/GameState/Game_Fish/Fishes/Large_Fish/Large_Fish{}.png", i + 1));
	}
}

void InitFishingMiniGame()
{
	LoadFishTextures();
	fmgData.fishingSuccessBuffer.loadFromFile("Audio/SoundEffect/Success.ogg");
	fmgData.fishingLancerBuffer.loadFromFile("Audio/SoundEffect/FishingLancer.ogg");
	fmgData.fishingWaterBuffer.loadFromFile("Audio/SoundEffect/FishingWater.ogg");
	fmgData.fishingKrabBuffer.loadFromFile("Audio/SoundEffect/FishingLancer.ogg");
	fmgData.fishingLancer.setBuffer(fmgData.fishingLancerBuffer);
	fmgData.fishingKrab.setBuffer(fmgData.fishingKrabBuffer);
	fmgData.fishingWater.setBuffer(fmgData.fishingWaterBuffer);
	fmgData.fishingSuccess.setBuffer(fmgData.fishingSuccessBuffer);
	fmgData.fishSprite[LITTLE_FISH] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Little_Fish/Little_Fish1.png", true);
	fmgData.fishSprite[LITTLE_FISH].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[LITTLE_FISH] = LoadText("Assets/Font/Fishland.otf", "Petit poisson", 76, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[LITTLE_FISH] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "+ 100 Points", 76, { fmgData.fishSprite[LITTLE_FISH].getPosition().x, fmgData.fishSprite[LITTLE_FISH].getPosition().y + fmgData.fishSprite[LITTLE_FISH].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);

	fmgData.fishSprite[MEDIUM_FISH] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Medium_Fish/Medium_Fish1.png", true);
	fmgData.fishSprite[MEDIUM_FISH].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[MEDIUM_FISH] = LoadText("Assets/Font/Fishland.otf", "Poisson moyen", 96, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[MEDIUM_FISH] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "+ 200 Points", 76, { fmgData.fishSprite[MEDIUM_FISH].getPosition().x, fmgData.fishSprite[MEDIUM_FISH].getPosition().y + fmgData.fishSprite[MEDIUM_FISH].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);

	fmgData.fishSprite[LARGE_FISH] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Large_Fish/Large_Fish1.png", true);
	fmgData.fishSprite[LARGE_FISH].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[LARGE_FISH] = LoadText("Assets/Font/Fishland.otf", "Gros poisson", 96, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[LARGE_FISH] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "+ 300 Points", 76, { fmgData.fishSprite[LARGE_FISH].getPosition().x, fmgData.fishSprite[LARGE_FISH].getPosition().y + fmgData.fishSprite[LARGE_FISH].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);

	fmgData.fishSprite[CRAB] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Crab.png", true);
	fmgData.fishSprite[CRAB].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[CRAB] = LoadText("Assets/Font/Fishland.otf", "Crabe", 96, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[CRAB] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "Vous avez perdu votre dernier poisson...", 58, { fmgData.fishSprite[CRAB].getPosition().x, fmgData.fishSprite[CRAB].getPosition().y + fmgData.fishSprite[CRAB].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);

	fmgData.fishSprite[SHRIMP] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Shrimp.png", true);
	fmgData.fishSprite[SHRIMP].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[SHRIMP] = LoadText("Assets/Font/Fishland.otf", "Crevette", 96, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[SHRIMP] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "Votre prochaine prise vous rapportera 2x plus de points !", 54, { fmgData.fishSprite[SHRIMP].getPosition().x, fmgData.fishSprite[SHRIMP].getPosition().y + fmgData.fishSprite[SHRIMP].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);

	fmgData.fishSprite[CLAM] = LoadSprite("Assets/GameState/Game_Fish/Fishes/Clam.png", true);
	fmgData.fishSprite[CLAM].setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	fmgData.fishTextType[CLAM] = LoadText("Assets/Font/Fishland.otf", "Palourde", 96, { 0, 0 }, sf::Color::White, false);
	fmgData.fishTextPoints[CLAM] = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "Vous pourrez l'utiliser si vous vous trompez à une question !", 52, { fmgData.fishSprite[CLAM].getPosition().x, fmgData.fishSprite[CLAM].getPosition().y + fmgData.fishSprite[CLAM].getGlobalBounds().height / 2 }, sf::Color::Yellow, false);


	for (unsigned int i = 0; i < 6; i++)
	{
		fmgData.fishTextType[i].setPosition(fmgData.fishSprite[i].getPosition().x, fmgData.fishSprite[i].getPosition().y - fmgData.fishSprite[i].getGlobalBounds().height / 2 - fmgData.fishTextPoints[i].getGlobalBounds().height / 4);
		fmgData.fishTextType[i].setOrigin(fmgData.fishTextType[i].getGlobalBounds().width / 2, fmgData.fishTextType[i].getGlobalBounds().height * 1.5);
		fmgData.fishTextType[i].setOutlineColor(sf::Color::Black);
		fmgData.fishTextType[i].setOutlineThickness(2);

		fmgData.fishTextPoints[i].setPosition(fmgData.fishSprite[i].getPosition().x, fmgData.fishSprite[i].getPosition().y + fmgData.fishSprite[i].getGlobalBounds().height / 2 + fmgData.fishTextPoints[i].getGlobalBounds().height);
		fmgData.fishTextPoints[i].setOrigin(fmgData.fishTextPoints[i].getGlobalBounds().width / 2, 0);
		fmgData.fishTextPoints[i].setOutlineColor(sf::Color::Black);
		fmgData.fishTextPoints[i].setOutlineThickness(2);
	}

	fmgData.background = LoadSprite("Assets/GameState/Game_Fish/Background.png", false);
	fmgData.bridge = LoadSprite("Assets/GameState/Game_Fish/Bridge.png", false);
	fmgData.playArea = { 280, 220, 1340, 607 };

	fmgData.fish[0].texture.loadFromFile("Assets/GameState/Game_Fish/Shadow.png");

	// Réinitialiser le jeu
	CreateFishes();

	fmgData.drawFish = false;
	fmgData.fishPicked = false;
	fmgData.transition = false;
}

void UpdateFishes(float _dt)
{
	DebugFishes();
	fmgData.fishingLancer.setVolume(ReturnVolume());
	fmgData.fishingKrab.setVolume(ReturnVolume());
	fmgData.fishingWater.setVolume(ReturnVolume());
	fmgData.fishingSuccess.setVolume(ReturnVolume());
	//std::cout << "nbFishInPond : " << fmgData.nbFishInPond << "\nfishPicked : " << fmgData.fishPicked << "\ndrawFish : " << fmgData.drawFish << "\ntransition : " << fmgData.transition << std::endl << std::endl;

	for (int i = 0; i < fmgData.nbFishInPond; i++)
	{
		if (!fmgData.fishPicked)
		{
			sf::Vector2f offset(195, 76);
			GetCursorAnimation().sprite.setPosition((sf::Vector2f)GetMousePos() - offset);

			// Déplacements aléatoires
			fmgData.fish[i].cooldown -= _dt;

			if (fmgData.fish[i].cooldown < 0)
			{
				if (fmgData.fish[i].velocity != sf::Vector2f(0, 0))
				{
					fmgData.fish[i].velocity = sf::Vector2f(0, 0);
					fmgData.fish[i].cooldown = RandomInt(5, 15) + RandomInt(1, 9) / 10.f;
				}
				else
				{
					fmgData.fish[i].shadow.setRotation(fmgData.fish[i].rotation);

					fmgData.fish[i].velocity = sf::Vector2f(40 * (cos(fmgData.fish[i].rotation * M_PI / 180)), 40 * (sin(fmgData.fish[i].rotation * M_PI / 180)));
					fmgData.fish[i].cooldown = RandomInt(20, 40) / 10.f;
				}
			}

			//Collisions avec la zone de jeu
			if (isCollindingPointRectangle(GetMousePos().x, GetMousePos().y, { fmgData.playArea.left , fmgData.playArea.top }, { fmgData.playArea.width , fmgData.playArea.height }))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					PlayClicFx(sf::Vector2f(GetMousePos()));
					if (fmgData.fishingWater.getStatus() != sf::Sound::Status::Playing)
						fmgData.fishingWater.play();
				}
			}
			//gauche de la zone de jeu
			if (fmgData.fish[i].pos.x - fmgData.fish[i].size.x / 2 < fmgData.playArea.left)
			{
				fmgData.fish[i].pos.x = fmgData.playArea.left + fmgData.fish[i].size.x / 2;
				fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				fmgData.fish[i].cooldown = RandomInt(5, 15) + RandomInt(1, 9) / 10.f;
			}
			//droite de la zone de jeu
			else if (fmgData.fish[i].pos.x + fmgData.fish[i].size.x / 2 > fmgData.playArea.left + fmgData.playArea.width)
			{
				fmgData.fish[i].pos.x = fmgData.playArea.left + fmgData.playArea.width - fmgData.fish[i].size.x / 2;
				fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				fmgData.fish[i].cooldown = RandomInt(5, 15) + RandomInt(1, 9) / 10.f;
			}
			//haut de la zone de jeu
			else if (fmgData.fish[i].pos.y - fmgData.fish[i].size.x / 2 < fmgData.playArea.top)
			{
				fmgData.fish[i].pos.y = fmgData.playArea.top + fmgData.fish[i].size.x / 2;
				fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				fmgData.fish[i].cooldown = RandomInt(5, 15) + RandomInt(1, 9) / 10.f;
			}
			//bas de la zone de jeu
			else if (fmgData.fish[i].pos.y + fmgData.fish[i].size.x / 2 > fmgData.playArea.top + fmgData.playArea.height)
			{
				fmgData.fish[i].pos.y = fmgData.playArea.top + fmgData.playArea.height - fmgData.fish[i].size.x / 2;
				fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				fmgData.fish[i].cooldown = RandomInt(5, 15) + RandomInt(1, 9) / 10.f;
			}

			else
			{
				if (fmgData.fish[i].pos.y == fmgData.playArea.top + fmgData.playArea.height - fmgData.fish[i].size.x / 2)
					fmgData.fish[i].rotation = RandomInt(180, 360);

				else if (fmgData.fish[i].pos.y == fmgData.playArea.top + fmgData.fish[i].size.x / 2)
					fmgData.fish[i].rotation = RandomInt(0, 180);

				else if (fmgData.fish[i].pos.x == fmgData.playArea.left + fmgData.playArea.width - fmgData.fish[i].size.x / 2)
					fmgData.fish[i].rotation = RandomInt(90, 270);

				else if (fmgData.fish[i].pos.x == fmgData.playArea.left + fmgData.fish[i].size.x / 2)
					fmgData.fish[i].rotation = RandomInt(0, 90);

				else
					fmgData.fish[i].rotation = RandomInt(0, 360);
			}

			//Collisions avec les autres poissons
			for (unsigned int j = 0; j < fmgData.nbFishInPond; j++)
			{
				if (i != j)
					if (IsCollidingCircleCircle(fmgData.fish[i].pos, fmgData.fish[i].size.x / 2, fmgData.fish[j].pos, fmgData.fish[j].size.x / 2))
					{
						float norm = sqrtf((fmgData.fish[j].pos.x - fmgData.fish[i].pos.x) * (fmgData.fish[j].pos.x - fmgData.fish[i].pos.x) + (fmgData.fish[j].pos.y - fmgData.fish[i].pos.y) * (fmgData.fish[j].pos.y - fmgData.fish[i].pos.y));
						fmgData.fish[j].pos.x = fmgData.fish[i].pos.x + ((fmgData.fish[j].pos.x - fmgData.fish[i].pos.x) * 1 / norm) * (fmgData.fish[j].size.x / 2 + fmgData.fish[i].size.x / 2);
						fmgData.fish[j].pos.y = fmgData.fish[i].pos.y + ((fmgData.fish[j].pos.y - fmgData.fish[i].pos.y) * 1 / norm) * (fmgData.fish[j].size.x / 2 + fmgData.fish[i].size.x / 2);

						// Ta grosse mère la pute
					}
			}
		}
		else
		{
			sf::Vector2f offset(78, 175);
			GetCursorAnimation().sprite.setPosition(fmgData.fish[GetPickedFishID()].pos - offset);

			PlayOneAnimation(GetCursorAnimation(), _dt, 2);

			float alpha = fmgData.fish[i].shadow.getColor().a;
			if (alpha - _dt * 100 < 0)
			{
				fmgData.drawFish = true;
				alpha = 0;
			}
			else
			{
				alpha -= _dt * 100;
			}

			if (!fmgData.fish[i].isPicked)
			{
				float distance = atan2f(fmgData.fish[GetPickedFishID()].pos.y - fmgData.fish[i].pos.y, fmgData.fish[GetPickedFishID()].pos.x - fmgData.fish[i].pos.x);

				fmgData.fish[i].velocity = sf::Vector2f(_dt * 2500 * -cos(distance), _dt * 2500 * -sin(distance));
				fmgData.fish[i].shadow.setColor(sf::Color(255, 255, 255, alpha));

				fmgData.fish[i].shadow.setRotation(distance * 180 / M_PI);

				if (fmgData.fish[i].pos.x - fmgData.fish[i].size.x / 2 < fmgData.playArea.left ||
					fmgData.fish[i].pos.x + fmgData.fish[i].size.x / 2 > fmgData.playArea.left + fmgData.playArea.width ||
					fmgData.fish[i].pos.y - fmgData.fish[i].size.x / 2 < fmgData.playArea.top ||
					fmgData.fish[i].pos.y + fmgData.fish[i].size.x / 2 > fmgData.playArea.top + fmgData.playArea.height)
				{
					fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				}
			}
		}

		fmgData.fish[i].pos.x += fmgData.fish[i].velocity.x * _dt;
		fmgData.fish[i].pos.y += fmgData.fish[i].velocity.y * _dt;
		fmgData.fish[i].shadow.setPosition(fmgData.fish[i].pos);

		if (fmgData.drawFish)
		{
			if (fmgData.fishingSuccess.getStatus() != sf::Sound::Status::Playing)
			{
				fmgData.fishingSuccess.play();
			}
			PlayRewardFx(fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].getPosition(), (sf::Vector2f)fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].getTexture()->getSize());

			float alpha = fmgData.fish[GetPickedFishID()].shadow.getColor().a;
			if (alpha - _dt * 100 < 0)
			{
				fmgData.drawFish = true;
				alpha = 0;
			}
			else
			{
				alpha -= _dt * 100;
			}

			fmgData.fish[GetPickedFishID()].shadow.setColor(sf::Color(255, 255, 255, alpha));

			// Confirmation 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Mouse::isButtonPressed(sf::Mouse::Left) && !fmgData.transition)
			{
				fmgData.transition = true;
				if (fmgData.fish[GetPickedFishID()].type == CRAB)
				{
					fmgData.fishingKrab.play();
					PlaySlash();
				}
			}

			if (fmgData.transition)
			{
				float alpha = fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type].getFillColor().a;

				if (alpha > 0)
				{
					alpha -= _dt / 2;

					fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type].setFillColor(sf::Color(255, 255, 255, alpha));
					fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type].setOutlineColor(sf::Color(0, 0, 0, alpha));

					fmgData.fishTextPoints[fmgData.fish[GetPickedFishID()].type].setFillColor(sf::Color(255, 255, 0, alpha));
					fmgData.fishTextPoints[fmgData.fish[GetPickedFishID()].type].setOutlineColor(sf::Color(0, 0, 0, alpha));

					// Sprites
					fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].setColor(sf::Color(255, 255, 255, alpha));
					fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].setScale(fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].getScale().x + _dt / 2 * 0.1, fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].getScale().y + _dt / 2 * 0.1);

					GetRewardSprite().setColor(sf::Color(255, 255, 255, alpha));
				}
				else
				{
					alpha = 0;
					AddFish(GetPlayer(GetPlayerTurn()), fmgData.fish[GetPickedFishID()]);

					//Reset
					GetRewardSprite().setColor(sf::Color::White);

					fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].setColor(sf::Color(255, 255, 255, 255));
					fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type].setScale(1, 1);
					fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type].setFillColor(sf::Color(255, 255, 255, 255));
					fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type].setOutlineColor(sf::Color(0, 0, 0, 255));
					fmgData.fishTextPoints[fmgData.fish[GetPickedFishID()].type].setFillColor(sf::Color(255, 255, 0, 255));
					fmgData.fishTextPoints[fmgData.fish[GetPickedFishID()].type].setOutlineColor(sf::Color(0, 0, 0, 255));

					StopRewardFx();
					ResetFishes();
					fmgData.fish[GetPickedFishID()].isPicked = false;
					CreateFishes();
					ResetAnim(GetCursorAnimation());
					PlayOneAnimation(GetCursorAnimation(), _dt, 2);

					fmgData.transition = false;
					fmgData.fishPicked = false;
					fmgData.drawFish = false;

					FadeTextOut();
					SetGameState(GAME_QUIZ);

					NextPlayerTurn();
				}
			}
		}
	}
}

void UpdateFishingMiniGame(float _dt)
{
	UpdateFishes(_dt);
}

void PickFish(float _dt)
{
	if (!fmgData.fishPicked)
	{
		for (unsigned int i = 0; i < fmgData.nbFishInPond; i++)
		{
			if (IsCollidingPointCircle(GetMousePos().x, GetMousePos().y, fmgData.fish[i].pos, fmgData.fish[i].size.x / 2))
			{
				fmgData.fishingLancer.play();
				fmgData.fish[i].velocity = sf::Vector2f(0, 0);
				fmgData.fish[i].isPicked = true;
				fmgData.fishPicked = true;

				if (fmgData.fish[i].type == LITTLE_FISH)
					fmgData.fishSprite[fmgData.fish[i].type].setTexture(fmgData.fishTexture[LITTLE_FISH][rand() % 9]);
				if (fmgData.fish[i].type == MEDIUM_FISH)
					fmgData.fishSprite[fmgData.fish[i].type].setTexture(fmgData.fishTexture[MEDIUM_FISH][rand() % 9]);
				if (fmgData.fish[i].type == LARGE_FISH)
					fmgData.fishSprite[fmgData.fish[i].type].setTexture(fmgData.fishTexture[LARGE_FISH][rand() % 9]);

			}
		}
	}
}

void DisplayFishingMiniGame(sf::RenderWindow& _window)
{
	_window.setMouseCursorVisible(false);
	_window.draw(fmgData.background);

	for (unsigned int i = 0; i < fmgData.nbFishInPond; i++)
	{
		_window.draw(fmgData.fish[i].shadow);
	}

	BlitSprite(fmgData.bridge, sf::Vector2f(0, 0), 0, _window);

	if (fmgData.drawFish)
	{
		DisplayRewardFx(_window);
		BlitSprite(fmgData.fishSprite[fmgData.fish[GetPickedFishID()].type], { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, 0, _window);
		_window.draw(fmgData.fishTextType[fmgData.fish[GetPickedFishID()].type]);
		_window.draw(fmgData.fishTextPoints[fmgData.fish[GetPickedFishID()].type]);
	}

	DisplaySlash(_window);

	if (!fmgData.drawFish)
	{
		DisplayCursor(_window);
	}
}

unsigned int GetPickedFishID()
{
	for (unsigned int i = 0; i < fmgData.nbFishInPond; i++)
	{
		if (fmgData.fish[i].isPicked)
		{
			return i;
		}
	}
}