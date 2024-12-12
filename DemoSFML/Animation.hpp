#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Common.hpp"

struct Animation
{
	sf::Sprite sprite;
	int frames;
	float timer;
};

void LoadAnimation(struct Animation& _animation, int _frames, sf::String _path);
void PlayAnimation(struct Animation& _animation, float _dt, float _speed);
void PlayOneAnimation(struct Animation& _animation, float _dt, float _speed);
void ResetAnim(struct Animation& _animation);
#endif