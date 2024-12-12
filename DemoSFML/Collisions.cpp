#include "Collisions.hpp"

bool isCollindingPointRectangle(float _pX, float _pY, sf::Vector2f _rPos, sf::Vector2f _rSize)
{
	return (_pX >= _rPos.x && _pX <= _rPos.x + _rSize.x && _pY >= _rPos.y && _pY <= _rPos.y + _rSize.y);
}

bool isCollidingRectangleRectangle(sf::Vector2f _r1Pos, sf::Vector2f _r1Size, sf::Vector2f _r2Pos, sf::Vector2f _r2Size)
{
	return (_r1Pos.x < _r2Pos.x + _r2Size.x && _r1Pos.x + _r1Size.x > _r2Pos.x && _r1Pos.y < _r2Pos.y + _r2Size.y && _r1Pos.y + _r1Size.y > _r2Pos.y);
}

bool IsCollidingCircleCircle(sf::Vector2f _c1Pos, int _c1Radius, sf::Vector2f _c2Pos, int _c2Radius)
{
	return (sqrt((_c1Pos.x - _c2Pos.x) * (_c1Pos.x - _c2Pos.x) + (_c1Pos.y - _c2Pos.y) * (_c1Pos.y - _c2Pos.y)) < (_c1Radius + _c2Radius));
}

bool IsCollidingPointCircle(float _pX, float _pY, sf::Vector2f _cPos, int _cRadius)
{
	return ((_pX - _cPos.x) * (_pX - _cPos.x) + (_pY - _cPos.y) * (_pY - _cPos.y) < _cRadius * _cRadius);
}