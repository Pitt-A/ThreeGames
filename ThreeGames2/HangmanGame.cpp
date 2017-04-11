#include "HangmanGame.h"

HangmanGame::HangmanGame()
{
	//reserving space for the words
	words.reserve(10);
}

HangmanGame::~HangmanGame()
{

}

void HangmanGame::setup(int diff)
{
	//loading a text file depending on the difficulty selected
	if (diff == 0)
	{
		loadFile("HangmanWordsEasy.txt");
	}
	else if (diff == 1)
	{
		loadFile("HangmanWordsMedium.txt");
	}
	else if (diff == 2)
	{
		loadFile("HangmanWordsHard.txt");
	}

	newWord();
	livesLeft = 8;
	playerScore = 0;

	//eliminating the strange character present with a space
	allGuesses.insert(' ');

	return;
}

void HangmanGame::loadFile(std::string fileName)
{
	words.clear();
	//loading all of the words into a vector
	std::ifstream  wordFile(fileName);
	std::string currentWord;

	while (std::getline(wordFile, currentWord))
	{
		words.push_back(currentWord);
	}

	return;
}

void HangmanGame::newWord()
{
	//clearing out the current and hidden words, ready for the new one
	currentWord.clear();
	hiddenWord.clear();
	allGuesses.clear();
	allGuesses.insert(26);
	//randomnly selecting a new word
	int wordNumber = (rand() % 10);
	currentWord = words[wordNumber];
	int wordLength = currentWord.length();

	//again, eliminating the strange character present with a space
	allGuesses.insert(' ');

	for (int i = 0; i < wordLength; i++)
	{
		hiddenWord.push_back('?');
	}

	return;
}

void HangmanGame::userGuess()
{
	//hnadling the users guess
	char currentGuess = getch();
	bool loseLife = false, alreadyGuessed = false;
	int incorrect = currentWord.length();

	for (int i = 0; i < currentWord.length(); i++)
	{
		if (currentGuess == currentWord[i])
		{
			hiddenWord[i] = currentGuess;
			incorrect--;
		}
	}

	if (incorrect == currentWord.length())
	{
		livesLeft--;
	}

	for (auto& j : allGuesses)
	{
		if (j == currentGuess)
		{
			alreadyGuessed = true;
		}
	}

	if (alreadyGuessed == false)
	{
		allGuesses.insert(currentGuess);
	}
	return;
}

void HangmanGame::printToScreen()
{
	//printing everything to the screen
	int j = 0;

	mvprintw(0, 0, "%s", "Now playing: Hangman");
	mvprintw(1, 0, "%s", "Current score:");
	mvprintw(2, 0, "%s", "Lives left:");
	attron(COLOR_PAIR(1));
	mvprintw(1, 16, "%d", playerScore);
	mvprintw(2, 13, "%d", livesLeft);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(5));
	mvprintw(12, 20 - (hiddenWord.length()/2), hiddenWord.c_str());
	attroff(COLOR_PAIR(5));
	mvprintw(20, 0, "%s", "All letters that have been guessed:");

	for (auto& i : allGuesses)
	{
		mvprintw(20, 35+j, "%c", i); 
		mvprintw(20, 35, "%s", " ");
		j++;
	}

	printPerson();

	refresh();

	return;
}

bool HangmanGame::checkWin()
{
	//checking for a win
	for (int i = 0; i < currentWord.length(); i++)
	{
		if (hiddenWord[i] == '?')
		{
			return false;
		}
	}

	return true;
}

bool HangmanGame::checkLose()
{
	//checking for a loss
	if (livesLeft <= 0)
	{
		return true;
	}

	return false;
}

void HangmanGame::gameOver()
{
	//the game over screen
	clear();
	attron(COLOR_PAIR(5));
	mvprintw(10, 24, "%s", "GAME OVER");
	attroff(COLOR_PAIR(5));

	mvprintw(13, 25, "%s", "Score:");
	mvprintw(13, 31, "%d", playerScore);
	mvprintw(14, 17, "%s", "Press enter to continue.");

	mvprintw(23, 1, "%s", "The word was:");
	attron(COLOR_PAIR(6));
	mvprintw(23, 14, currentWord.c_str());
	attroff(COLOR_PAIR(6));

	printPerson();

	refresh();

	int i = getch();
	while (i != 10)
	{
		//keep player on game over screen until enter is pressed
		i = getch();
	}

	return;
}

void HangmanGame::printPerson()
{
	//printing the person being hanged as the player loses lives
	if (livesLeft < 8)
	{
		mvprintw(15, 50, "%s", "------------");
	}

	if (livesLeft < 7)
	{
		for (int i = 8; i > 0; i--)
		{
			mvprintw(i + 6, 50, "%c", '|');
		}
	}

	if (livesLeft < 6)
	{
		mvprintw(6, 50, "%s", "----------");
	}

	if (livesLeft < 5)
	{
		mvprintw(7, 58, "%c", '|');
	}

	if (livesLeft < 4)
	{
		mvprintw(8, 58, "%c", 'O');
	}

	if (livesLeft < 3)
	{
		mvprintw(9, 58, "%c", '|');
	}

	if (livesLeft < 2)
	{
		mvprintw(9, 57, "%c", '-');
		mvprintw(9, 59, "%c", '-');
	}

	if (livesLeft < 1)
	{
		mvprintw(10, 58, "%c", '^');
		mvprintw(11, 57, "%c", '|');
		mvprintw(11, 59, "%c", '|');
	}
}

bool HangmanGame::update()
{
	//the update loop
	printToScreen();
	userGuess();

	if (checkWin() == true)
	{
		playerScore++;
		livesLeft = 8;
		clear();
		newWord();
	}

	if (checkLose() == true)
	{
		gameOver();
		return true;
	}

	return false;
}