#include "Question.hpp"

#pragma region VAR

int  questionType = 1;// genre de la question (vrai /faux ou a 4 )
int fileToGet; // quelle dossier ouvrir selon le theme

int lineToGet; // ligne a récupérer
int counter = 0; // compteur pour l'ouverture de fichier
char answer4[4][textLength];// table qui stock les phrases des questions a 4 réponses
char question[textLength];// table qui stock la question
int answer;//donné qui stock la répone en vrai ou faux

sf::Text textQuestion; //texte de la question
sf::Text textAnswerVF[2];//texte des réponses vrai / faux 
sf::Text textAnswer4[4];//texte des 4 réponses //la première réponse [0] est toujours la bonne 
std::string FilePathVF; // file path pour les questions vrai faux
std::string FilePath4; // file path pour les questions a 4 

struct Type
{
	std::vector<int> QuestionVfLeft;
	std::vector<int> Question4Left;
}type;

std::vector<Type>Theme;
int selectedTheme[2];
#pragma endregion

//fonction a appeller pour check si un vecteur est vide //attention appeler un vecteur de int pas celui de struct
bool checkIfVectorQuestionAreEmpty(std::vector<int> _vector)
{
	if (_vector.size() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// fonction a appelé pour modifier le file path //modification via la variable fileToGet
void checkFile()
{
	switch (fileToGet)
	{
	case PECHE:
		FilePathVF = "Questions/Peches/Question VF.txt";
		FilePath4 = "Questions/Peches/Question 4.txt";
		break;
	case CUISINE:
		FilePathVF = "Questions/Cuisine/Question VF.txt";
		FilePath4 = "Questions/Cuisine/Question 4.txt";
		break;
	case JEUX_VIDEOS:
		FilePathVF = "Questions/Jeux Video/Question VF.txt";
		FilePath4 = "Questions/Jeux Video/Question 4.txt";
		break;
	case SANTE:
		FilePathVF = "Questions/Sante et bien etre/Question VF.txt";
		FilePath4 = "Questions/Sante et bien etre/Question 4.txt";
		break;
	case ANIME:
		FilePathVF = "Questions/Anime/Question VF.txt";
		FilePath4 = "Questions/Anime/Question 4.txt";
		break;
	}
}

// fonction qui ouvre le dossier et prend les question / réponses , toujours l'appeler APRES qu'on ai changer la ligne 
void openFiles()
{
	// déclaration des variable fichier
	std::ifstream fichierVF;
	std::ifstream fichier4;
	checkFile();

	//ouverture fichier en mode lecture
	fichierVF.open(FilePathVF, std::ios::in);
	fichier4.open(FilePath4, std::ios::in);

	// si le genre est vrai ou faux
	if (questionType == 1)
	{
		if (fichierVF)//check si le dossier est bien ouvert
		{
			//déclaration de la variable contenant la pris dans le dossier string
			std::string ligne;
			//boucle parcourant toutes les lignes une par une
			while (std::getline(fichierVF, ligne))
			{
				// Supprime l'identifiant des caractères bugués
				ligne.erase(std::remove(ligne.begin(), ligne.end(), -61), ligne.end());

				//si la ligne correspond a la ligne rechercher 
				if (counter == lineToGet)
				{
					for (int i = 0; i < ligne.length() + 1; i++)
					{
						// assignation de la question
						question[i] = ligne[i];

						// Remplace le caractère bugué par son vrai caractère
						if (question[i] < 0)
						{
							question[i] += 320;
						}
					}
				}

				if (counter == lineToGet + 1)
				{
					//assignatioon de la réponse ( 1 : vrai, 0 :faux)
					answer = std::stoi(ligne);
					fichierVF.close();

				}
				counter++;// compteur qui équivaut a la ligne
			}
		}
	}

	//si le genre est une question a 4 
	if (questionType == 0)
	{
		if (fichier4)//check si le dossier est bien ouvert
		{
			//déclaration de la variable contenant la pris dans le dossier string
			std::string ligne;

			//boucle parcourant toutes les lignes une par une
			while (std::getline(fichier4, ligne))
			{
				// Supprime l'identifiant des caractères bugués
				ligne.erase(std::remove(ligne.begin(), ligne.end(), -61), ligne.end());

				//si la ligne correspond a la ligne rechercher 
				if (counter == lineToGet)
				{
					for (int i = 0; i < ligne.length() + 1; i++)
					{
						// assignation de la question
						question[i] = ligne[i];

						// Remplace le caractère bugué par son vrai caractère
						if (question[i] < 0)
						{
							question[i] += 320;
						}
					}
				}

				//récupération des réponses lié a la question
				for (unsigned int j = 0; j < 4; j++)
				{
					if (counter == lineToGet + 1 + j)
					{
						for (int i = 0; i < ligne.length() + 1; i++)
						{
							answer4[j][i] = ligne[i];

							// Remplace le caractère bugué par son vrai caractère
							if (answer4[j][i] < 0)
							{
								answer4[j][i] += 320;
							}
						}
					}
				}
				counter++;// compteur qui équivaut a la ligne
			}
		}
	}

}

// fonction a appellé juste une seul fois quand on load une nouvelle partie , si elle est rappellé au milieu d'une partie elle remet toutes les questions de touts les thème disponible
void ResetQuestions()
{
	if (Theme.size() > 0)
	{
		Theme.clear();
	}

	//push back les 5 thème
	for (int j = 0; j < NumberOfThem; j++)
	{
		Theme.push_back(Type());
	}

	//push back des les lignes des questions 
	for (int k = 0; k < Theme.size(); k++)
	{
		for (int i = 0; i < Peche4; i++)
		{
			if (i % 5 == 0)
			{
				Theme[k].Question4Left.push_back(i);
			}

		}

		for (int j = 0; j < PecheVF; j++)
		{
			if (j % 2 == 0)
			{
				Theme[k].QuestionVfLeft.push_back(j);
			}
		}
	}
}

//fonction a garder dans un update , permet de debugs certain pb de randoms et empeche certain theme d'être prix dans certaine condition
void FixRandomChoice()
{
	if ((checkIfVectorQuestionAreEmpty(Theme[selectedTheme[0]].QuestionVfLeft)) && (checkIfVectorQuestionAreEmpty(Theme[selectedTheme[0]].Question4Left)))
	{
		selectedTheme[0] = rand() % NumberOfThem;
	}

	if ((checkIfVectorQuestionAreEmpty(Theme[selectedTheme[1]].QuestionVfLeft)) && (checkIfVectorQuestionAreEmpty(Theme[selectedTheme[1]].Question4Left)))
	{
		selectedTheme[1] = rand() % NumberOfThem;
	}
}

//fonction a appeller pour génerer 2 thème randoms
void ChooseRandomTheme()
{
	selectedTheme[0] = rand() % NumberOfThem;
	selectedTheme[1] = rand() % NumberOfThem;

	while (selectedTheme[0] == selectedTheme[1])
	{
		selectedTheme[1] = rand() % NumberOfThem;
	}
}

//load font et assignation de celle  et assignation des phrases "vrai / faux" ////a supprimer
void SetTextStrings()
{
	textQuestion.setString(question);

	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			textAnswerVF[i].setString("Vrai");
		}
		if (i == 1)
		{
			textAnswerVF[i].setString("Faux");
		}
	}
	for (int i = 0; i < 4; i++)
	{
		textAnswer4[i].setString(answer4[i]);
	}
}

//premier load a n'appeler que quand une nouvelle partie est créer  //a adapter pour la version complete
void LoadQuestions()
{
	ResetQuestions();
	//premier random a faire obligatoirement sinon toujours la meme question
	if (questionType == 0)
	{
		int random4 = rand() % Theme[fileToGet].Question4Left.size();
		lineToGet = Theme[fileToGet].Question4Left[random4];
		Theme[fileToGet].Question4Left.erase(Theme[fileToGet].Question4Left.begin() + random4, Theme[fileToGet].Question4Left.begin() + random4 + 1);
	}
	else
	{
		int random2 = rand() % Theme[fileToGet].QuestionVfLeft.size();
		lineToGet = Theme[fileToGet].QuestionVfLeft[random2];
		Theme[fileToGet].QuestionVfLeft.erase(Theme[fileToGet].QuestionVfLeft.begin() + random2, Theme[fileToGet].QuestionVfLeft.begin() + random2 + 1);
	}
}

//fonction qui update les questions
void RefreshQuestions()
{
	// si un theme n'as plus de questions disponnible
	if ((checkIfVectorQuestionAreEmpty(Theme[fileToGet].QuestionVfLeft)) && (checkIfVectorQuestionAreEmpty(Theme[fileToGet].QuestionVfLeft)))
	{
		CreateNewQuestions();
	}
	else //generation des questions randoms
	{
		//random entre VF et Q4
		questionType = rand() % 2;

		if (questionType == 1)
		{
			//check si le vector est rempli
			if (!(checkIfVectorQuestionAreEmpty(Theme[fileToGet].QuestionVfLeft)))
			{
				int random = rand() % Theme[fileToGet].QuestionVfLeft.size(); //prendre une ID question aléatoire dans le vector
				lineToGet = Theme[fileToGet].QuestionVfLeft[random];//définir LineToget
				Theme[fileToGet].QuestionVfLeft.erase(Theme[fileToGet].QuestionVfLeft.begin() + random, Theme[fileToGet].QuestionVfLeft.begin() + random + 1); //éffacer du vector la question choisis pour ne pas avoir de redondance
				counter = 0;
			}
			else//sinon switcher de type
			{
				questionType = 0;
			}
			openFiles();
			SetTextStrings();
		}
		if (questionType == 0)
		{
			//check si le vector est rempli
			if (!(checkIfVectorQuestionAreEmpty(Theme[fileToGet].Question4Left)))
			{
				//meme principe qu'en haut
				int random = rand() % Theme[fileToGet].Question4Left.size();
				lineToGet = Theme[fileToGet].Question4Left[random];
				Theme[fileToGet].Question4Left.erase(Theme[fileToGet].Question4Left.begin() + random, Theme[fileToGet].Question4Left.begin() + random + 1);
				counter = 0;
			}
			else//sinon switcher de type
			{
				questionType = 1;
			}
			//fonction nécessaire pour afficher nouvelle questions
			openFiles();
			SetTextStrings();
		}
	}
}

//fonction permettant de reload les questions
void CreateNewQuestions()
{
	RefreshQuestions();
}




bool IsCorrectAnswerSelected(sf::Text _text)
{
	if (questionType == 0)
	{
		if (_text.getString() == textAnswer4[0].getString())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (questionType == 1)
	{
		if ((answer == 1) && (_text.getString() == "Vrai"))
		{
			return true;
		}

		if ((answer == 0) && (_text.getString() == "Faux"))
		{
			return true;
		}

		return false;
	}
}

void SetSelectedTheme(int _i)
{
	fileToGet = selectedTheme[_i];
}

int GetQuestionType()
{
	return questionType;
}

int GetQuestionTheme(int _i)
{
	return selectedTheme[_i];
}

int GetQuestionLine()
{
	return lineToGet;
}

std::vector<sf::String> GetStrings()
{
	std::vector<sf::String> strings;
	sf::String tempString;

	if (strings.size() > 0)
	{
		strings.clear();
	}

	tempString = textQuestion.getString();

	strings.push_back(tempString);

	if (questionType == 0)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			tempString = textAnswer4[i].getString();
			strings.push_back(tempString);
		}
	}
	else
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			tempString = textAnswerVF[i].getString();
			strings.push_back(tempString);
		}
	}

	return strings;
}