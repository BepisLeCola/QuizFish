#include "Audio.hpp"

sf::Sound QuestionAudio;
sf::SoundBuffer QuestionAudioBuffer;

void LoadSound(int _theme, int _type, int _line)
{
	std::string ThemePath;
	std::string type;
	int LinePath;
	std::string FilePath;

	switch (_theme)
	{
	case 0:
		ThemePath = "Peches";
		break;
	case 1:
		ThemePath = "Cuisine";
		break;
	case 2:
		ThemePath = "JeuxVideos";
		break;
	case 3:
		ThemePath = "Sante";
		break;
	case 4:
		ThemePath = "Anime";
		break;
	default:
		std::cout << "error" << std::endl;
		break;
	}

	switch (_type)
	{
	case 0:
		type = "4Questions";
		LinePath = _line / 5;
		break;
	case 1:
		type = "VF";
		LinePath = _line / 2;
		break;

	default:
		std::cout << "error" << std::endl;
		break;
	}

	FilePath = std::format("Audio/Questions/{}/{}/{}.ogg", ThemePath, type, LinePath + 1);
	QuestionAudioBuffer.loadFromFile(FilePath);
	QuestionAudio.setBuffer(QuestionAudioBuffer);
}

sf::Sound& GetQuestionAudio()
{
	return QuestionAudio;
}