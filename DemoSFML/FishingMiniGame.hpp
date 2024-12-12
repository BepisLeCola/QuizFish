#ifndef FISHINGMINIGAME_HPP
#define FISHINGMINIGAME_HPP

#include "Common.hpp"
#include "Screen.hpp"
#include "Random.hpp"
#include "Mouse.hpp"
#include "Fx.hpp"
#include "Player.hpp"
#include "Collisions.hpp"
#include "Animation.hpp"
#include "HUD.hpp"
#include "Settings.hpp"

#define MAX_FISH_IN_POND 7
#define MIN_FISH_IN_POND 5

void PickFish(float _dt);

void InitFishingMiniGame();
void UpdateFishingMiniGame(float _dt);
void DisplayFishingMiniGame(sf::RenderWindow& _window);

#endif // !FISHINGMINIGAME_H