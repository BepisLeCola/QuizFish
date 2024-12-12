#include "Fx.hpp"

struct Particules particules[MAX_PARTICULES_ANSWER];
struct Particules confettis[MAX_CONFETTIS];
struct CircleParticules slash[MAX_PARTICULES_SLASH];
struct CircleParticules clic;
struct RectangleParticules buttonFx;

sf::Sprite rewardFx;
sf::Texture rewardFxTexture;
float rewardTimer;

sf::Texture particulesTextureTrue;
sf::Texture particulesTextureFalse;

sf::Image imageFx;        //Déclaration d'un sf::Image pour dessiner
sf::Texture textureFx;    //Déclaration d'un sf::Texture qui recevra manuellement les données de l'image
sf::Sprite spriteFx;      //Déclaration d'un sprite pour afficher le tout

struct Animation peche; //Test d'animation

sf::Texture ConfettisTexture[MAX_TEXTURE_CONFETTIS];

void LoadRewardFx(void)
{
	rewardTimer = 0;
	rewardFxTexture.loadFromFile("Assets/Fx/rewardFx.png");
	rewardFx.setTexture(rewardFxTexture);
	rewardFx.setOrigin({ (float)rewardFxTexture.getSize().x / 2, (float)rewardFxTexture.getSize().y / 2 });
	rewardFx.setColor(sf::Color::Color(255, 255, 255, 200));
}

void LoadParticules(void)
{
	particulesTextureTrue.loadFromFile("Assets/Fx/Right.png");
	particulesTextureFalse.loadFromFile("Assets/Fx/Wrong.png");

	for (unsigned int i = 0; i < MAX_PARTICULES_ANSWER; i++)
	{
		particules[i].pos = sf::Vector2f(500, 500);
		particules[i].velocity = sf::Vector2f(0, 0);
		particules[i].speed = 0;
		particules[i].angle = 0;
		particules[i].rand = 0;
		particules[i].timer = 0;
		particules[i].type = PARTICULES_TRUE;
		particules[i].texture = particulesTextureTrue;
		particules[i].sprite.setTexture(particules[i].texture);
		particules[i].sprite.setOrigin((float)particules[i].texture.getSize().x / 2, (float)particules[i].texture.getSize().y / 2);
	}
}

void LoadConfettis(void)
{
	ConfettisTexture[0].loadFromFile("Assets/Fx/confettis1.png");
	ConfettisTexture[1].loadFromFile("Assets/Fx/confettis2.png");
	ConfettisTexture[2].loadFromFile("Assets/Fx/confettis3.png");
	ConfettisTexture[3].loadFromFile("Assets/Fx/confettis4.png");

	for (unsigned int i = 0; i < MAX_CONFETTIS; i++)
	{
		confettis[i].pos = sf::Vector2f(rand() % SCREEN_WIDTH, -50);
		confettis[i].velocity = sf::Vector2f(0, 0);
		confettis[i].speed = 0;
		confettis[i].angle = 0;
		confettis[i].rand = 0;
		confettis[i].timer = 0;
		confettis[i].texture = ConfettisTexture[0];
		confettis[i].sprite.setTexture(confettis[i].texture);
		confettis[i].sprite.setOrigin((float)confettis[i].texture.getSize().x / 2, (float)confettis[i].texture.getSize().y / 2);
	}
}

void LoadSlash(void)
{
	imageFx.create(SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color::Color(255, 255, 255, 75));
	textureFx.loadFromFile("Assets/Fx/BgFx.png");
	spriteFx.setTexture(textureFx);


	for (unsigned int i = 0; i < MAX_PARTICULES_SLASH; i++)
	{
		slash[i].timer = 0.0f;

		slash[i].color = sf::Color::White;
		slash[i].shape.setFillColor(slash[i].color);


		slash[i].speed = 4000 - (2 * i);
		slash[i].radius = 10 - (0.01 * i);
		slash[i].shape.setRadius(slash[i].radius);
		slash[i].shape.setOrigin(slash[i].radius, slash[i].radius);

		sf::Vector2f vector = { SCREEN_WIDTH - slash[i].pos.x, 0 - slash[i].pos.y };
		float norme = sqrt((vector.x) * (vector.x) + (vector.y) * (vector.y));//calcul de la norme
		vector /= norme;

		slash[i].pos = { 0, SCREEN_HEIGHT };
		slash[i].velocity = vector;
	}
}

void LoadClicFx(void)
{
	clic.pos = { 0,0 };
	clic.radius = 0;
	clic.speed = 1;
	clic.timer = 0.0f;
	clic.shape.setRadius(clic.radius);
	clic.shape.setOrigin(clic.radius, clic.radius);
	clic.color = sf::Color::White;
	clic.shape.setOutlineThickness(4);
	clic.shape.setOutlineColor(clic.color);
	clic.shape.setFillColor(sf::Color::Transparent);
}

void LoadButtonFx(void)
{
	buttonFx.pos = { 0 , 0 };
	buttonFx.size = { 0 , 0 };
	buttonFx.speed = 0.0f;
	buttonFx.timer = 0.0f;
	buttonFx.color = sf::Color::White;
	buttonFx.shape.setPosition(buttonFx.pos);
	buttonFx.shape.setSize(buttonFx.size);
	buttonFx.shape.setOrigin(buttonFx.size.x / 2, buttonFx.size.y / 2);
	buttonFx.shape.setOutlineColor(buttonFx.color);
	buttonFx.shape.setOutlineThickness(4);
	buttonFx.shape.setFillColor(sf::Color::Transparent);
}

void LoadFx(void)
{
	LoadAnimation(peche, 17, "Assets/Fx/peche.png"); // Lancé

	LoadParticules();
	LoadConfettis();
	LoadSlash();
	LoadClicFx();
	LoadButtonFx();
	LoadRewardFx();
}


void UpdateParticles(float _dt)
{
	for (unsigned int i = 0; i < MAX_PARTICULES_ANSWER; i++)
	{
		if (particules[i].timer > 0)
		{
			particules[i].timer -= _dt * 2;
			particules[i].sprite.setColor(sf::Color::Color(255, 255, 255, (sf::Uint8)(255 * (particules[i].timer / particules[i].timerMax))));

			particules[i].speed = particules[i].maxSpeed * (particules[i].timer / particules[i].timerMax) * 2;

			if (particules[i].rand)
			{
				particules[i].angle += 10 * _dt;
			}
			else
			{
				particules[i].angle -= 10 * _dt;
			}

			particules[i].sprite.setRotation(particules[i].angle);
		}
		else
		{
			particules[i].timer = 0;
			particules[i].velocity.x = 0;
			particules[i].velocity.y = 0;
			particules[i].angle = 0;
			particules[i].sprite.setRotation(particules[i].angle);
		}

		particules[i].pos.x += particules[i].velocity.x * particules[i].speed * particules[i].timer * _dt;
		particules[i].pos.y += particules[i].velocity.y * particules[i].speed * particules[i].timer * _dt;
		particules[i].sprite.setPosition(particules[i].pos);
	}
}

void UpdateConfettis(float _dt)
{
	for (unsigned int i = 0; i < MAX_CONFETTIS; i++)
	{
		if (confettis[i].timer > 0)
		{
			confettis[i].timer -= _dt;

			if (confettis[i].velocity.y < 0 && confettis[i].speed > 0)
			{
				confettis[i].speed -= _dt * confettis[i].timer * 10;
			}
			if (confettis[i].velocity.y < 0 && confettis[i].speed <= 0)
			{
				confettis[i].velocity.y *= -1;
				confettis[i].velocity.x *= 0.2;
			}
			if (confettis[i].velocity.y > 0)
			{
				confettis[i].speed += 25 * _dt;

			}

			confettis[i].sprite.setColor(sf::Color::Color(255, 255, 255, (sf::Uint8)(255 * (confettis[i].timer / confettis[i].timerMax))));

		}
		else
		{
			confettis[i].pos.y = SCREEN_HEIGHT;
			confettis[i].pos.x = 0;
			confettis[i].velocity = sf::Vector2f(0, 0);
			confettis[i].sprite.setColor(sf::Color::Color(255, 255, 255, (sf::Uint8)(255)));
		}
		confettis[i].pos.x += confettis[i].velocity.x * confettis[i].speed * _dt;
		confettis[i].pos.y += confettis[i].velocity.y * confettis[i].speed * _dt;
		confettis[i].sprite.setPosition(confettis[i].pos);
	}
}

void UpdateSlash(float _dt)
{
	for (unsigned int i = 0; i < MAX_PARTICULES_SLASH; i++)
	{
		if (slash[i].timer > 0)
		{
			slash[i].timer -= _dt;
		}
		else
		{
			slash[i].velocity = { 0 , 0 };
			slash[i].speed = 0;
			slash[i].pos = { 0, SCREEN_HEIGHT };
		}
		slash[i].pos.x += slash[i].velocity.x * slash[i].speed * _dt;
		slash[i].pos.y += slash[i].velocity.y * slash[i].speed * _dt;
		slash[i].shape.setPosition(slash[i].pos);
	}
	textureFx.update(imageFx);
	spriteFx.setColor(sf::Color::Color(255, 255, 255, 255 * (slash[0].timer / slash[0].timerMax)));
}

void UpdateClicFx(float _dt)
{
	if (clic.timer > 0)
	{
		clic.timer -= _dt;
		clic.radius += clic.speed * _dt;
		clic.color = sf::Color::Color(255, 255, 255, 255 * (clic.timer / clic.timerMax));
		clic.shape.setOrigin(clic.radius, clic.radius);
		clic.shape.setRadius(clic.radius);
		clic.shape.setOutlineColor(clic.color);
	}
	else
	{
		clic.radius = 0;
	}
}

void UpdateButtonFx(float _dt)
{
	if (buttonFx.timer > 0)
	{
		buttonFx.timer -= _dt;

		buttonFx.size.x += 60 * _dt * buttonFx.timer;
		buttonFx.size.y += 60 * _dt * buttonFx.timer;

		buttonFx.color.a = 255 * (buttonFx.timer / 1);

		buttonFx.shape.setSize(buttonFx.size);
		buttonFx.shape.setOrigin(buttonFx.size.x / 2, buttonFx.size.y / 2);
		buttonFx.shape.setOutlineColor(buttonFx.color);
	}
	else
	{
		buttonFx.size = { 0 , 0 };
	}
}

void UpdateRewardFx(float _dt)
{
	float static angle = 0;

	if (rewardTimer > 0)
	{
		rewardTimer -= _dt;

		angle += _dt * 5;

		rewardFx.setRotation(angle);
	}
}

void UpdateFx(float _dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//ResetAnim(peche);
	}
	//PlayOneAnimation(peche, _dt, 16);
	//PlayAnimation(peche, _dt, 16);
	UpdateParticles(_dt);
	UpdateConfettis(_dt);
	UpdateSlash(_dt);
	UpdateClicFx(_dt);
	UpdateButtonFx(_dt);
	UpdateRewardFx(_dt);
}

void DisplayParticules(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < MAX_PARTICULES_ANSWER; i++)
	{
		if (particules[i].timer > 0)
		{
			_window.draw(particules[i].sprite);
		}
	}
}

void DisplayConfettis(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < MAX_CONFETTIS; i++)
	{
		if (confettis[i].timer > 0)
		{
			_window.draw(confettis[i].sprite);
		}
	}
}

void DisplaySlash(sf::RenderWindow& _window)
{
	if (slash[0].timer > 0)
	{
		_window.draw(spriteFx);
		for (unsigned int i = 0; i < MAX_PARTICULES_SLASH; i++)
		{
			_window.draw(slash[i].shape);
		}
	}
}

void DisplayClicFx(sf::RenderWindow& _window)
{
	if (clic.timer > 0)
	{
		_window.draw(clic.shape);
	}
}

void DisplayButtonFx(sf::RenderWindow& _window)
{
	if (buttonFx.timer > 0)
	{
		_window.draw(buttonFx.shape);
	}
}

void DisplayRewardFx(sf::RenderWindow& _window)
{
	if (rewardTimer > 0)
	{
		_window.draw(rewardFx);
	}
}

void DisplayCursor(sf::RenderWindow& _window)
{
	_window.draw(peche.sprite);
}

void DisplayFx(sf::RenderWindow& _window)
{
	DisplayParticules(_window);
	DisplayConfettis(_window);
	DisplaySlash(_window);
	DisplayClicFx(_window);
	DisplayButtonFx(_window);
	DisplayRewardFx(_window);
}

//Play particules where you want and don't forget to precise the type (PARTICULES_TRUE or PARTICULES_FALSE)
void PlayParticules(sf::Vector2f _pos, enum ParticulesTrueOrFalse _type)
{
	for (unsigned int i = 0; i < MAX_PARTICULES_ANSWER; i++)
	{
		if (particules[i].timer <= 0)
		{
			particules[i].rand = rand() % 2;

			if (_type == PARTICULES_TRUE)
			{
				particules[i].texture = particulesTextureTrue;
				particules[i].sprite.setTexture(particules[i].texture);
			}
			else
			{
				particules[i].texture = particulesTextureFalse;
				particules[i].sprite.setTexture(particules[i].texture);
			}

			particules[i].timerMax = 1;
			particules[i].timer = particules[i].timerMax;

			particules[i].pos = _pos;

			particules[i].maxSpeed = (float)100 + ((rand() / (float)RAND_MAX) * 100);
			particules[i].speed = particules[i].maxSpeed;

			if (i < MAX_PARTICULES_ANSWER / 2)
			{
				particules[i].velocity.x = (float)(5 + (rand() / (float)RAND_MAX) * 5);
				particules[i].velocity.y = (float)(-25 + (rand() / (float)RAND_MAX) * 50);

				float norme = sqrt((particules[i].velocity.x) * (particules[i].velocity.x) + (particules[i].velocity.y) * (particules[i].velocity.y));//calcul de la norme

				particules[i].velocity = particules[i].velocity / norme;

			}
			else
			{
				particules[i].velocity.x = (float)(-10 + (rand() / (float)RAND_MAX) * 5);
				particules[i].velocity.y = (float)(-25 + (rand() / (float)RAND_MAX) * 50);

				float norme = sqrt((particules[i].velocity.x) * (particules[i].velocity.x) + (particules[i].velocity.y) * (particules[i].velocity.y));//calcul de la norme

				particules[i].velocity = particules[i].velocity / norme;

			}
			particules[i].sprite.setPosition(particules[i].pos);
		}
	}
}

//Play Slash animation (no need arguments)
void PlaySlash(void)
{
	if (slash[MAX_PARTICULES_SLASH - 1].pos.x <= 0)
	{
		for (unsigned int i = 0; i < MAX_PARTICULES_SLASH; i++)
		{
			slash[i].timerMax = 2;
			slash[i].timer = slash[i].timerMax;

			slash[i].speed = 6000 - (4.5 * i);

			sf::Vector2f vector = { SCREEN_WIDTH - slash[i].pos.x, 0 - slash[i].pos.y };
			float norme = sqrt((vector.x) * (vector.x) + (vector.y) * (vector.y));//calcul de la norme
			vector /= norme;

			slash[i].pos = { 0, SCREEN_HEIGHT };
			slash[i].velocity = vector;

		}
	}

}

//Play Confettis effects (no need arguments)
void PlayConfettis(void)
{
	for (unsigned int i = 0; i < MAX_CONFETTIS / 2; i++)
	{
		int texture = rand() % MAX_TEXTURE_CONFETTIS;
		if (confettis[i].timer <= 0)
		{
			confettis[i].pos.y = SCREEN_HEIGHT;
			confettis[i].pos.x = 0;

			confettis[i].velocity.y = -1;
			confettis[i].velocity.x = (rand() / (float)RAND_MAX) * 2000;

			sf::Vector2f vector = { confettis[i].velocity.x - confettis[i].pos.x, confettis[i].velocity.y - confettis[i].pos.y };
			float norme = sqrt((vector.x) * (vector.x) + (vector.y) * (vector.y));//calcul de la norme
			vector /= norme;

			confettis[i].timerMax = 15 + rand() % 6;
			confettis[i].timer = confettis[i].timerMax;
			confettis[i].angle = rand() % 360;
			confettis[i].maxSpeed = 200 + (rand() / (float)RAND_MAX) * 2000;
			confettis[i].speed = confettis[i].maxSpeed;
			confettis[i].velocity = vector;

			confettis[i].texture = ConfettisTexture[texture];
			confettis[i].sprite.setTexture(confettis[i].texture);

			confettis[i].sprite.setRotation(confettis[i].angle);
		}
	}
	for (unsigned int j = MAX_CONFETTIS / 2; j < MAX_CONFETTIS; j++)
	{
		int texture = rand() % MAX_TEXTURE_CONFETTIS;
		if (confettis[j].timer <= 0)
		{
			confettis[j].pos.y = SCREEN_HEIGHT;
			confettis[j].pos.x = SCREEN_WIDTH;

			confettis[j].velocity.y = -1;
			confettis[j].velocity.x = (rand() / (float)RAND_MAX) * 2000;

			sf::Vector2f vector = { confettis[j].velocity.x - confettis[j].pos.x, confettis[j].velocity.y - confettis[j].pos.y };
			float norme = sqrt((vector.x) * (vector.x) + (vector.y) * (vector.y));//calcul de la norme
			vector /= norme;

			confettis[j].timerMax = 15 + rand() % 6;
			confettis[j].timer = confettis[j].timerMax;
			confettis[j].angle = rand() % 360;
			confettis[j].maxSpeed = 200 + (rand() / (float)RAND_MAX) * 2000;
			confettis[j].speed = confettis[j].maxSpeed;
			confettis[j].velocity = vector;

			confettis[j].texture = ConfettisTexture[texture];
			confettis[j].sprite.setTexture(confettis[j].texture);

			confettis[j].sprite.setRotation(confettis[j].angle);
		}
	}
}

//Play effect on click
void PlayClicFx(sf::Vector2f _pos)
{
	if (clic.timer <= 0 && clic.radius <= 0)
	{
		clic.pos = _pos;
		clic.shape.setPosition(clic.pos);

		clic.maxSpeed = 50;
		clic.speed = clic.maxSpeed;

		clic.timerMax = 0.5;
		clic.timer = clic.timerMax;
	}

}

void PlayButtonFx(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _color)
{
	if (buttonFx.timer <= 0)
	{
		buttonFx.timer = 1;

		buttonFx.pos = _pos;
		buttonFx.size = _size;
		buttonFx.size.x /= 1.4;
		buttonFx.size.y /= 1.4;
		buttonFx.color = _color;

		buttonFx.shape.setPosition(buttonFx.pos);
		buttonFx.shape.setSize(buttonFx.size);
		buttonFx.shape.setOutlineColor(buttonFx.color);
	}
}

void PlayRewardFx(sf::Vector2f _pos, sf::Vector2f _size, float _timer)
{
	float scale;
	float size = (_size.x > _size.y) ? scale = _size.x / rewardFxTexture.getSize().x * 1.5 : scale = _size.y / rewardFxTexture.getSize().y * 1.5;

	rewardTimer = _timer;
	rewardFx.setPosition(_pos);

	rewardFx.setScale({ scale,scale });
}

void StopRewardFx(void)
{
	rewardTimer = 0;
}

void StopConfettis()
{
	for (unsigned int i = 0; i < MAX_CONFETTIS; i++)
	{
		confettis[i].timer = 0;
	}
}

sf::Sprite& GetRewardSprite(void)
{
	return rewardFx;
}

Animation& GetCursorAnimation()
{
	return peche;
}