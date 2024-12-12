#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "Common.hpp"
#include <format>

void LoadSound(int _theme, int _type, int _line);
sf::Sound& GetQuestionAudio();
#endif