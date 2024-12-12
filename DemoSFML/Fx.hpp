#ifndef FX_HPP
#define FX_HPP

#include "Common.hpp"
#include "Screen.hpp"
#include "Animation.hpp"
#include "Mouse.hpp"

#define MAX_PARTICULES_ANSWER 8
#define MAX_CONFETTIS 512
#define MAX_PARTICULES_SLASH 1024
#define MAX_TEXTURE_CONFETTIS 4

enum ParticulesTrueOrFalse
{
	PARTICULES_TRUE,
	PARTICULES_FALSE
};

struct Particules
{
	sf::Vector2f pos;
	sf::Vector2f velocity;
	float maxSpeed;
	float speed = 0.0f;
	float angle = 0.0f;
	int rand = 0;
	float timerMax;
	float timer = 0.0f;
	sf::Sprite sprite;
	sf::Texture texture;
	enum ParticulesTrueOrFalse type = PARTICULES_TRUE;
};

struct CircleParticules
{
	sf::Vector2f pos;
	sf::Vector2f velocity;
	float radius;
	float maxSpeed;
	float speed = 0.0f;
	int rand = 0;
	float timerMax;
	float timer = 0.0f;
	sf::CircleShape shape;
	sf::Color color;
};

struct RectangleParticules
{
	sf::Vector2f pos;
	sf::Vector2f size;
	float maxSpeed;
	float speed = 0.0f;
	float timerMax;
	float timer = 0.0f;
	sf::RectangleShape shape;
	sf::Color color;
};

void LoadParticules(void);
void LoadConfettis(void);
void LoadSlash(void);
void LoadClicFx(void);
void LoadButtonFx(void);
void LoadFx(void);

void UpdateParticles(float _dt);
void UpdateConfettis(float _dt);
void UpdateSlash(float _dt);
void UpdateClicFx(float _dt);
void UpdateFx(float _dt);

void DisplayParticules(sf::RenderWindow& _window);
void DisplayConfettis(sf::RenderWindow& _window);
void DisplaySlash(sf::RenderWindow& _window);
void DisplayClicFx(sf::RenderWindow& _window);
void DisplayButtonFx(sf::RenderWindow& _window);
void DisplayFx(sf::RenderWindow& _window);
void DisplayRewardFx(sf::RenderWindow& _window);
void DisplayCursor(sf::RenderWindow& _window);

void PlayParticules(sf::Vector2f _pos, enum ParticulesTrueOrFalse _type);
void PlaySlash(void);
void PlayConfettis(void);
void PlayClicFx(sf::Vector2f _pos);
void PlayButtonFx(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _color);
void PlayRewardFx(sf::Vector2f _pos, sf::Vector2f _size, float _timer = 99999999);
void StopRewardFx(void);
void StopConfettis(void);

sf::Sprite& GetRewardSprite(void);
Animation& GetCursorAnimation(void);
#endif // !FX.HPP