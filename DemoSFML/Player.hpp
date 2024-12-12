#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Common.hpp"
#include "Fx.hpp"
#include "GameState.hpp"
#include <vector>

enum FishType
{
    LITTLE_FISH,
    MEDIUM_FISH,
    LARGE_FISH,
    CRAB,
    SHRIMP, // Crevette
    CLAM // Palourde
};

struct Fish
{
	sf::Sprite shadow;
	sf::Texture texture;
	sf::Vector2f pos;
	sf::Vector2f size;
	enum FishType type;
	int rotation;
	float cooldown;
	sf::Vector2f velocity;
	bool isPicked;
};

struct Player
{
	int score;
    int numClam;
    bool shrimp;
	std::vector<struct Fish> inventaire;
	sf::Sprite avatar;
};

void LoadPlayer(int _numPlayer);
void AddFish(struct Player& _player, struct Fish& _fish);
void DeleteLastFish(struct Player& _player);
void ReloadPlayers(void);

Player& GetPlayer(int _ID);
int GetPlayerTurn();
void NextPlayerTurn();
std::vector<struct Player> GetPlayersVector(void);
void RemoveClam(struct Player& _player);

#endif
