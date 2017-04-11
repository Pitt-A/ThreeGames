#include "curses.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>

class HangmanGame
{
public:
	HangmanGame();
	~HangmanGame();

	void setup(int diff);
	void loadFile(std::string fileName);
	void newWord();
	void userGuess();
	void printToScreen();
	bool checkWin();
	bool checkLose();
	void gameOver();
	void printPerson();
	bool update();
private:
	int livesLeft = 8, playerScore = 0, choice;

	std::string currentWord;
	std::string hiddenWord;

	std::vector<std::string> words;

	std::set<char> allGuesses;
};