#include "HangmanMenu.h"

HangmanMenu::HangmanMenu()
{
	//create the options vector for hangman
	options.clear();
	options.push_back("[Play]");
	options.push_back("[Difficulty]");
	options.push_back("[Back]");
	options.push_back("[Exit]");

	Menu::setup(false);
}

HangmanMenu::~HangmanMenu()
{

}

void HangmanMenu::display()
{
	//display the welcome message
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "%s", "Welcome to Hangman!");
	attroff(COLOR_PAIR(1));
}

std::string HangmanMenu::returnInput()
{
	//returning the input to the state manager
	switch (currentOption)
	{
	case 0:
		return "hangman_g";
		break;
	case 1:
		return "hangman_d";
		break;
	case 2:
		return "menu_m";
		break;
	case 3:
		return "exit";
		break;
	}
}