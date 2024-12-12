#include "Player.hpp"

std::vector<struct Player> players;
int playerTurn;
int RoundNB;

void LoadPlayer(int _numPlayer)
{
	for (unsigned int i = 0; i < _numPlayer; i++)
	{
		Player player;
		player.score = 0;
		player.numClam = 0;
		player.shrimp = false;
		players.push_back(player);
	}
	playerTurn = 0;
	RoundNB = 0;
}

void AddFish(struct Player& _player, struct Fish& _fish)
{
	Fish fish = _fish;

	switch (_fish.type)
	{
	case LITTLE_FISH:
		_player.score += 100 * (1 + _player.shrimp);
		_player.inventaire.push_back(fish);
		_player.shrimp = false;
		break;
	case MEDIUM_FISH:
		_player.score += 200 * (1 + _player.shrimp);
		_player.inventaire.push_back(fish);
		_player.shrimp = false;
		break;
	case LARGE_FISH:
		_player.score += 300 * (1 + _player.shrimp);
		_player.inventaire.push_back(fish);
		_player.shrimp = false;
		break;
	case CRAB:
		DeleteLastFish(_player);
		_player.inventaire.push_back(fish);
		break;
	case CLAM:
		_player.numClam += 1;
		_player.inventaire.push_back(fish);
		break;
	case SHRIMP:
		_player.shrimp = true;
		_player.inventaire.push_back(fish);
		break;
	default:
		std::cout << "not a fish" << std::endl;
		break;
	}
}

void DeleteLastFish(struct Player& _player)
{
	if (_player.inventaire.size() > 0 && _player.score)
	{
		for (unsigned int i = 0; i < _player.inventaire.size(); i++)
		{
			switch (_player.inventaire[_player.inventaire.size() - 1 - i].type)
			{
			case LITTLE_FISH:
				_player.score -= 100;
				_player.inventaire.erase(_player.inventaire.begin() + i, _player.inventaire.begin() + i + 1);
				return;
				break;
			case MEDIUM_FISH:
				_player.score -= 200;
				_player.inventaire.erase(_player.inventaire.begin() + i, _player.inventaire.begin() + i + 1);
				return;
				break;
			case LARGE_FISH:
				_player.score -= 300;
				_player.inventaire.erase(_player.inventaire.begin() + i, _player.inventaire.begin() + i + 1);
				return;
				break;
			}
		}
	}
}


//Clear all vector
void ReloadPlayers(void)
{
	for (int k = 0; k < players.size(); k++)
	{
		players[k].inventaire.clear();
	}

	players.clear();
}

int GetPlayerTurn()
{
	return playerTurn;
}

void NextPlayerTurn()
{
	if (playerTurn + 1 < players.size())
	{
		playerTurn++;
	}
	else
	{
		playerTurn = 0;
		if (RoundNB + 1 < 5)
		{
			RoundNB++;
		}
		else
		{
			SetGameState(ENDGAME);
			PlayConfettis();
		}
	}
}

Player& GetPlayer(int _ID)
{
	return players[_ID];
}

std::vector<struct Player> GetPlayersVector(void)
{
	return players;
}

void RemoveClam(struct Player& _player)
{
	if (_player.numClam > 0)
	{
		for (unsigned int i = 0; i < _player.inventaire.size(); i++)
		{
			if (_player.inventaire[i].type == CLAM)
			{
				_player.numClam--;
				_player.inventaire.erase(_player.inventaire.begin() + i, _player.inventaire.begin() + i + 1);
				return;
			}
		}
	}
}