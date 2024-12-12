#include "QuizGame.hpp"
#include "Settings.hpp"
#define QUESTION_OFFSETX 44
#define QUESTION_OFFSETY 45

#define BOX_SIZEX 314
#define BOX_SIZEY 136

enum CardTexts
{
	QUESTION,
	ANSWER1,
	ANSWER2,
	ANSWER3,
	ANSWER4
};

struct CardButton
{
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Text text;
	bool isHovered = false;
	bool isTrue = false;
	sf::FloatRect hitbox;
};

enum CardType
{
	TRUE_FALSE,
	FOUR_ANSWERS
};

struct Cards
{
	sf::Vector2f pos;
	sf::Vector2f uncenteredPos;
	sf::Vector2f size;

	sf::Sprite sprite;

	sf::Text questionThemeText;

	bool isSelected = false;
	bool isHidden = true;

	struct CardButton button[5];

	enum CardThemes theme;
	enum CardType type;
};

bool isCardSelected = false;
bool isEffectPlaying = false;
bool isAnswerTrue = false;
float switchGSTimer = 0;

Cards cards[2];
sf::Sprite highlightSprite;

sf::Sprite backgroundSpriteQuiz;
sf::Texture cardTextures[5][3];
sf::Sound cardSoundEffect;
sf::SoundBuffer cardSoundEffectBuffer;

int GetSelectedCardID()
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (cards[i].isSelected && isCardSelected)
		{
			return i;
		}
	}
}

void FitStringInBorders(sf::Text& _text, sf::Vector2f _sizeLimit)
{
	float stringSize = _text.getString().getSize();
	sf::String originalString = _text.getString();
	_text.setString("");

	sf::Text tempText = _text;
	_text.setPosition(cards[GetSelectedCardID()].button[QUESTION].pos);

	for (unsigned int i = 0; i < stringSize; i++)
	{
		_text.setString(_text.getString() + originalString.substring(i, 1));

		if (_text.getGlobalBounds().width > _sizeLimit.x)
		{
			int it = i;
			while (originalString.substring(it, 1) != " ")
			{
				it--;
			}
			originalString.erase(it, 1);
			originalString.insert(it, "\n");

			//_originalString.erase(i - 1, 1);		   <- suppression caractère par caractère
			//_originalString.insert(i - 1, "\n");

			stringSize = originalString.getSize();
			_text.setString("");
			i = -1;
		}
		while (_text.getGlobalBounds().height > _sizeLimit.y)
		{
			_text.setCharacterSize(_text.getCharacterSize() - 1);
		}
	}
}

void LoadCardsTextures()
{
	cardSoundEffectBuffer.loadFromFile("Audio/SoundEffect/CardSE.ogg");
	cardSoundEffect.setBuffer(cardSoundEffectBuffer);
	cardTextures[PECHE][0].loadFromFile("Assets/GameState/Game_Quiz/Cards/PecheVerso.png");
	cardTextures[PECHE][1].loadFromFile("Assets/GameState/Game_Quiz/Cards/Peche4.png");
	cardTextures[PECHE][2].loadFromFile("Assets/GameState/Game_Quiz/Cards/PecheVF.png");

	cardTextures[CUISINE][0].loadFromFile("Assets/GameState/Game_Quiz/Cards/CuisineVerso.png");
	cardTextures[CUISINE][1].loadFromFile("Assets/GameState/Game_Quiz/Cards/Cuisine4.png");
	cardTextures[CUISINE][2].loadFromFile("Assets/GameState/Game_Quiz/Cards/CuisineVF.png");

	cardTextures[JEUX_VIDEOS][0].loadFromFile("Assets/GameState/Game_Quiz/Cards/JeuxVideosVerso.png");
	cardTextures[JEUX_VIDEOS][1].loadFromFile("Assets/GameState/Game_Quiz/Cards/JeuxVideos4.png");
	cardTextures[JEUX_VIDEOS][2].loadFromFile("Assets/GameState/Game_Quiz/Cards/JeuxVideosVF.png");

	cardTextures[SANTE][0].loadFromFile("Assets/GameState/Game_Quiz/Cards/SanteVerso.png");
	cardTextures[SANTE][1].loadFromFile("Assets/GameState/Game_Quiz/Cards/Sante4.png");
	cardTextures[SANTE][2].loadFromFile("Assets/GameState/Game_Quiz/Cards/SanteVF.png");

	cardTextures[ANIME][0].loadFromFile("Assets/GameState/Game_Quiz/Cards/AnimeVerso.png");
	cardTextures[ANIME][1].loadFromFile("Assets/GameState/Game_Quiz/Cards/Anime4.png");
	cardTextures[ANIME][2].loadFromFile("Assets/GameState/Game_Quiz/Cards/AnimeVF.png");
}

void SetThemeTexture(int _i)
{
	switch (GetQuestionTheme(_i))
	{
	case PECHE:
		cards[_i].sprite.setTexture(cardTextures[PECHE][0]);
		cards[_i].questionThemeText.setString("Pêche");
		break;
	case CUISINE:
		cards[_i].sprite.setTexture(cardTextures[CUISINE][0]);
		cards[_i].questionThemeText.setString("Cuisine");
		break;
	case JEUX_VIDEOS:
		cards[_i].sprite.setTexture(cardTextures[JEUX_VIDEOS][0]);
		cards[_i].questionThemeText.setString("Jeux vidéos");
		break;
	case SANTE:
		cards[_i].sprite.setTexture(cardTextures[SANTE][0]);
		cards[_i].questionThemeText.setString("Santé et bien-être");
		break;
	case ANIME:
		cards[_i].sprite.setTexture(cardTextures[ANIME][0]);
		cards[_i].questionThemeText.setString("Mangas et animes");
		break;
	default:
		break;
	}
}

void GenerateCards()
{
	ChooseRandomTheme();
	for (unsigned int i = 0; i < 2; i++)
	{
		SetThemeTexture(i);
		cards[i].questionThemeText.setPosition(cards[i].pos.x, cards[i].uncenteredPos.y + cards[i].size.y + cards[i].questionThemeText.getGlobalBounds().height);
		cards[i].questionThemeText.setOrigin(cards[i].questionThemeText.getGlobalBounds().width / 2, cards[i].questionThemeText.getGlobalBounds().height / 2);
	}
}

void LoadCards()
{
	cards[0].pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
	cards[1].pos = { SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };

	for (unsigned int i = 0; i < sizeof(cards) / sizeof(Cards); i++)
	{
		cards[i].size = { 388, 549 };
		cards[i].uncenteredPos = cards[i].pos - cards[i].size / 2.f;
		cards[i].questionThemeText = LoadText("Assets/Font/Sunny Spells.ttf", "", 64, { 0, 0 }, sf::Color::White, true);
		cards[i].questionThemeText.setOutlineColor(sf::Color::Black);
		cards[i].questionThemeText.setOutlineThickness(2);

		for (unsigned int j = 0; j < 5; j++)
		{
			cards[i].button[j].text = LoadText("Assets/Font/Hubot_Sans_SemiBold.ttf", "", 18, cards[i].pos, sf::Color::Black, false);
		}
		cards[i].sprite.setOrigin(cards[i].size / 2.f);
	}
}

#define VFOFFSET1X 74
#define VFOFFSET1Y 252

#define VFOFFSET2X 275
#define VFOFFSET2Y 252

#define FOUROFFSETX 84
#define FOUROFFSET1Y 223
#define FOUROFFSET2Y 302
#define FOUROFFSET3Y 382
#define FOUROFFSET4Y 461

void LoadQuestions(Cards& _card)
{
	_card.button[QUESTION].pos = _card.uncenteredPos + sf::Vector2f(QUESTION_OFFSETX, QUESTION_OFFSETY);

	if (GetQuestionType() == 0)
	{
		float offsets[4] = { FOUROFFSET1Y, FOUROFFSET2Y, FOUROFFSET3Y, FOUROFFSET4Y };

		// shuffle les positions
		for (unsigned int i = 0; i < 4; i++)
		{
			float tempValue;
			int random = rand() % 4;

			tempValue = offsets[i];
			offsets[i] = offsets[random];
			offsets[random] = tempValue;
		}

		for (unsigned int i = 1; i < 5; i++)
		{
			_card.button[i].pos = _card.uncenteredPos + sf::Vector2f(FOUROFFSETX, offsets[i - 1]);
			_card.button[i].hitbox = { 0, offsets[i - 1], 388, 24 };
		}

		// Applique leur string et leurs positions aux textes
		for (unsigned int i = 0; i < 5; i++)
		{
			_card.button[i].text.setString(GetStrings()[i]);

			_card.button[i].text.setOrigin(_card.sprite.getPosition());
			_card.button[i].text.setPosition(_card.button[i].pos + _card.button[i].text.getOrigin());
		}
	}
	else
	{
		_card.button[QUESTION].pos = _card.uncenteredPos + sf::Vector2f(QUESTION_OFFSETX, QUESTION_OFFSETY);
		_card.button[ANSWER1].pos = _card.uncenteredPos + sf::Vector2f(VFOFFSET1X, VFOFFSET1Y);
		_card.button[ANSWER2].pos = _card.uncenteredPos + sf::Vector2f(VFOFFSET2X, VFOFFSET2Y);

		_card.button[ANSWER1].hitbox = { 45, 246, 97, 35 };
		_card.button[ANSWER2].hitbox = { 248, 246, 97, 35 };

		for (unsigned int i = 0; i < 3; i++)
		{
			_card.button[i].text.setString(GetStrings()[i]);

			_card.button[i].text.setOrigin(_card.sprite.getPosition());
			_card.button[i].text.setPosition(_card.button[i].pos + _card.button[i].text.getOrigin());
		}
	}
}

void UpdateTextButtonPos(int i)
{
	for (unsigned int j = 0; j < 5; j++)
	{
		sf::Vector2f newTextPos =
		{
			cards[i].pos.x + (cards[i].button[j].pos.x - cards[i].pos.x) * cards[i].sprite.getScale().x,
			cards[i].pos.y + (cards[i].button[j].pos.y - cards[i].pos.y) * cards[i].sprite.getScale().y
		};

		cards[i].button[j].text.setPosition(newTextPos);
	}
}

void PlaySelectionEffect(sf::Texture* _texture, int i, float _dt)
{
	if (cards[i].isHidden)
	{
		cards[i].sprite.setScale(cards[i].sprite.getScale().x - _dt * 3, 1);

		if (cards[i].sprite.getScale().x < 0)
		{
			cards[i].isHidden = false;
			cards[i].sprite.setScale(0, 1);
			cards[i].sprite.setTexture(*_texture, false);

			for (unsigned int j = 0; j < 5; j++)
			{
				cards[i].button[j].text.setScale(0, 1);
			}
		}
	}
	else
	{
		if (cards[i].sprite.getScale().x < 1)
		{
			cards[i].sprite.setScale(cards[i].sprite.getScale().x + _dt * 3, 1);

			for (unsigned int j = 0; j < 5; j++)
			{
				cards[i].button[j].text.setScale(cards[i].sprite.getScale());
			}

			if (GetQuestionAudio().getStatus() != sf::Sound::Playing)
			{
				if (getMuteState() == false)
				{
					GetQuestionAudio().play();
				}
				
			}
		}
		else
		{
			cards[i].sprite.setScale(1, 1);
			cards[i].button[QUESTION].text.setPosition(cards[i].button[QUESTION].pos);
		}
	}

	UpdateTextButtonPos(i);
}

void CreateQuestion()
{
	int i = GetSelectedCardID();

	CreateNewQuestions();
	LoadQuestions(cards[i]);
	FitStringInBorders(cards[i].button[QUESTION].text, { BOX_SIZEX - 15, BOX_SIZEY - 15 });

	if (GetQuestionType == 0)
	{
		for (unsigned int j = 1; j < 5; j++)
		{
			cards[i].button[j].text.setCharacterSize(16);
		}
	}
	else
	{
		for (unsigned int j = 1; j < 5; j++)
		{
			cards[i].button[j].text.setCharacterSize(18);
		}
	}
}

void ResetCards()
{
	isCardSelected = false;
	for (unsigned int i = 0; i < 2; i++)
	{
		cards[i].isSelected = false;
		cards[i].isHidden = true;
		cards[i].sprite.setScale(1, 1);
		cards[i].sprite.setColor(sf::Color::White);
		for (unsigned int j = 0; j < 5; j++)
		{
			cards[i].button[j].text.setCharacterSize(18);
		}
	}
	GenerateCards();
}

void SelectButton(int i, float _dt)
{
	for (unsigned int j = 1; j < 5; j++)
	{
		sf::Vector2f buttonPos = cards[i].uncenteredPos + sf::Vector2f(cards[i].button[j].hitbox.left, cards[i].button[j].hitbox.top);
		sf::Vector2f buttonSize = { cards[i].button[j].hitbox.width, cards[i].button[j].hitbox.height };

		if (isCollindingPointRectangle(GetMousePos().x, GetMousePos().y, buttonPos, buttonSize))
		{
			cards[i].button[j].text.setOutlineThickness(1);
			cards[i].button[j].text.setOutlineColor(sf::Color::White);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isEffectPlaying)
			{
				switchGSTimer = 0.40f;
				if (IsCorrectAnswerSelected(cards[i].button[j].text))
				{
					PlayParticules((sf::Vector2f)GetMousePos(), PARTICULES_TRUE);
					isAnswerTrue = true;
				}
				else
				{
					if (GetPlayer(GetPlayerTurn()).numClam == 0)
					{
						PlayParticules((sf::Vector2f)GetMousePos(), PARTICULES_FALSE);
						isAnswerTrue = false;
					}
				}
				isEffectPlaying = true;
			}
		}
		else
		{
			cards[i].button[j].text.setOutlineColor(sf::Color::Transparent);
		}
	}
}

void HideUnchosenCard(float _dt)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (!cards[i].isSelected)
		{
			if (cards[i].sprite.getScale().x - _dt > 0)
			{
				cards[i].sprite.setScale(cards[i].sprite.getScale() - sf::Vector2f(_dt * 1.5, _dt * 1.5));
				cards[i].sprite.setColor(sf::Color(255, 255, 255, 255 * cards[i].sprite.getScale().x));
			}
			else
			{
				cards[i].sprite.setScale(0, 0);
				cards[i].sprite.setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////

void LoadQuizGame()
{
	backgroundSpriteQuiz = LoadSprite("Assets/GameState/Game_Quiz/background.png", false);
	highlightSprite = LoadSprite("Assets/GameState/Game_Quiz/Cards/Highlight.png", true);
	highlightSprite.setPosition(-1000, -1000);
	LoadCardsTextures();
	LoadCards();
	GenerateCards();
	LoadQuestions();
}

void UpdateQuizGame(float _dt)
{

	cardSoundEffect.setVolume(ReturnVolume());
	FixRandomChoice();

	bool hasCollided = false;
	for (unsigned int i = 0; i < 2; i++)
	{
		if (isCollindingPointRectangle(GetMousePos().x, GetMousePos().y, cards[i].uncenteredPos, cards[i].size) && !isCardSelected)
		{
			hasCollided = true;

			if (highlightSprite.getColor().a != 255)
			{
				highlightSprite.setColor(sf::Color(255, 255, 255, 255));
			}

			highlightSprite.setPosition(cards[i].pos);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (cardSoundEffect.getStatus() != sf::Sound::Status::Playing)
				{
					cardSoundEffect.play();
				}
				cards[i].isSelected = true;
				isCardSelected = true;
				SetSelectedTheme(i);
				CreateQuestion();
				LoadSound(GetQuestionTheme(i), GetQuestionType(), GetQuestionLine() + 1);
			}
		}
		else if (!hasCollided)
		{
			if (highlightSprite.getColor().a != 0)
			{
				highlightSprite.setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	if (isCardSelected)
	{
		int i = GetSelectedCardID();

		PlaySelectionEffect(&cardTextures[GetQuestionTheme(i)][1 + GetQuestionType()], i, _dt);

		HideUnchosenCard(_dt);
		if (!cards[i].isHidden && cards[i].sprite.getScale().x == 1)
		{
			SelectButton(i, _dt);
		}
	}

	if (isEffectPlaying)
	{
		if (switchGSTimer > 0)
		{
			switchGSTimer -= _dt;
		}
		else
		{
			switchGSTimer = 0;
			if (isAnswerTrue)
			{
				SetGameState(GAME_FISH);
			}
			else
			{
				if (GetPlayer(GetPlayerTurn()).numClam == 0)
				{
					NextPlayerTurn();
					FadeTextOut();
				}
				else
				{
					RemoveClam(GetPlayer(GetPlayerTurn()));
				}
			}
			isAnswerTrue = false;
			isEffectPlaying = false;
			GetQuestionAudio().stop();
			ResetCards();
		}
	}
}

void DisplayQuizGame(sf::RenderWindow& _window)
{
	BlitSprite(backgroundSpriteQuiz, { 0, 0 }, 0, _window);

	_window.draw(highlightSprite);

	for (unsigned int i = 0; i < 2; i++)
	{
		if (!isCardSelected)
		{
			_window.draw(cards[i].questionThemeText);
		}

		BlitSprite(cards[i].sprite, cards[i].pos, 0, _window);

		if (!cards[i].isHidden)
		{
			for (unsigned int j = 0; j < 3 + (GetQuestionType() == 0) * 2; j++)
			{
				_window.draw(cards[i].button[j].text);
			}
		}
	}
}