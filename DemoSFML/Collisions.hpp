#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "Common.hpp"

bool isCollindingPointRectangle(float _pX, float _pY, sf::Vector2f _rPos, sf::Vector2f _rSize);
bool isCollidingRectangleRectangle(sf::Vector2f _r1Pos, sf::Vector2f _r1Size, sf::Vector2f _r2Pos, sf::Vector2f _r2Size);
bool IsCollidingCircleCircle(sf::Vector2f _c1Pos, int _c1Radius, sf::Vector2f _c2Pos, int _c2Radius);
bool IsCollidingPointCircle(float _pX, float _pY, sf::Vector2f _cPos, int _cRadius);

#endif