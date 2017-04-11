#include "HangmanDifficulty.h"

HangmanDifficulty::HangmanDifficulty()
{
	//create the options vector for hangman difficulty menu
	options.clear();
	options.push_back("[Easy]");
	options.push_back("[Medium]");
	options.push_back("[Hard]");

	Menu::setup(false);
}

HangmanDifficulty::~HangmanDifficulty()
{

}

void HangmanDifficulty::display(int diff)
{
	//printing the difficulty menu
	if (diff == 0)
	{
		difficulty = "Easy";
	}
	else if (diff == 1)
	{
		difficulty = "Medium";
	}
	else if (diff == 2)
	{
		difficulty = "Hard";
	}

	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "%s", "Please pick a difficulty.");
	mvprintw(1, 0, "%s", "Current difficulty:");
	mvprintw(1, 20, difficulty.c_str());
	attroff(COLOR_PAIR(1));
}

int HangmanDifficulty::returnDifficulty()
{
	//returning the difficult selected to the state manager
	if (currentOption == 0)
	{
		return 0;
	}
	else if (currentOption == 1)
	{
		return 1;
	}
	else if (currentOption == 2)
	{
		return 2;
	}
}

std::string HangmanDifficulty::returnInput()
{
	//tell the state manager where to go once done
	return "hangman_m";
}