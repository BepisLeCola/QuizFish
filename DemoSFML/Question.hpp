#ifndef QUESTION_HPP
#define QUESTION_HPP
#include <iostream>
#include <time.h>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"
#include "common.hpp"

#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string.h>
#include <fstream>
#include <iostream>

enum CardThemes
{
	PECHE,
	CUISINE,
	JEUX_VIDEOS,
	SANTE,
	ANIME
};


#define SCREEN_H 768
#define SCREEN_W 1024

#define textLength 500 //valeur par défaut a agrandir si texte trop grand

#pragma region question nb (a changer)

#define PecheVF 39 //correspond au nombre de question possible en VF (en ligne)
#define Peche4 96//correspond au nombre de question possible a 4 (en ligne)
#define NumberOfThem 5
#pragma endregion

void LoadQuestions();
void CreateNewQuestions();

bool IsCorrectAnswerSelected(sf::Text _text);
void SetSelectedTheme(int _i);
int GetQuestionType();
int GetQuestionTheme(int _i);
std::vector<sf::String> GetStrings();


void ChooseRandomTheme();
void FixRandomChoice();
int GetQuestionLine();

#endif