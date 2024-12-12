#include "Animation.hpp"


//Initialise l'animation avec une struct animation, son nombre de frames et l'emplacement de la texture
void LoadAnimation(struct Animation& _animation, int _frames, sf::String _path)
{
	sf::IntRect rect;
	sf::Sprite sprite;
	sf::Texture* texture = new sf::Texture;

	_animation.sprite = sprite;
	texture->loadFromFile(_path);
	_animation.frames = _frames;
	_animation.timer = 0;
	_animation.sprite.setTexture(*texture);

	int sizeX = (int)((*texture).getSize().x / _animation.frames);
	int sizeY = (int)((*texture).getSize().y);

	rect = { (int)(0 * (*texture).getSize().x),0,sizeX, sizeY};

	_animation.sprite.setTextureRect(rect);
}

void PlayAnimation(struct Animation& _animation, float _dt, float _speed)
{
	sf::IntRect rect;
	sf::Texture texture = *_animation.sprite.getTexture();
	int sizeX = (int)(texture.getSize().x / _animation.frames);
	int sizeY = (int)texture.getSize().y;

	if (_animation.timer < _animation.frames)
	{
		_animation.timer += _dt * _speed;
	}
	else
	{
		_animation.timer = 0;
	}
	
	rect = { (int)((int)_animation.timer * sizeX),0,(int)(texture.getSize().x / _animation.frames),(int)texture.getSize().y};
	_animation.sprite.setTextureRect(rect);
}

void PlayOneAnimation(struct Animation& _animation, float _dt, float _speed)
{
	sf::IntRect rect;
	sf::Texture texture = *_animation.sprite.getTexture();
	int sizeX = (int)(texture.getSize().x / _animation.frames);
	int sizeY = (int)texture.getSize().y;

	if (_animation.timer < _animation.frames-1)
	{
		_animation.timer += _dt*_speed;

	}

	rect = { (int)((int)_animation.timer * sizeX),0,(int)(texture.getSize().x / _animation.frames),(int)texture.getSize().y };
	_animation.sprite.setTextureRect(rect);
}

void ResetAnim(struct Animation& _animation)
{
	if (_animation.timer >= _animation.frames-1)
	{
		_animation.timer = 0;
	}
}