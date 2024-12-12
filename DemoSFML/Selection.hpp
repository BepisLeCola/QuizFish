#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "Common.hpp"
#include "Screen.hpp"
#include "GameState.hpp"
#include "Menu.hpp"

void LoadSelection();
void UpdateSelection(float _dt);
void DisplaySelection(sf::RenderWindow& _window);


void AddCardPlayer();
void ButtonPressed(sf::Event _event);
void MinusPlayer();


#endif 
