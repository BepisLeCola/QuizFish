#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Common.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"

void LoadSettings();
void UpdateSettings(float _dt);
void DisplaySettings(sf::RenderWindow& _window);


void VolumeButtonReleased();
void VolumeButtonPressed();
void MuteVoiceBool();
float ReturnVolume();
bool getMuteState();
#endif