#include "MainMenu.h"

MainMenu::MainMenu()
{
	//create the options vector for the main menu
	options.clear();
	options.push_back("[Blackjack]");
	options.push_back("[Hangman]");
	options.push_back("[Snake]");
	options.push_back("[Close]");

	Menu::setup(true);
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::display()
{
	//display the welcome message
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "%s", "Welcome to the Three Games main menu!");
	attroff(COLOR_PAIR(1));

	Menu::setup(true);

	return;
}

std::string MainMenu::returnInput()
{
	//returning the input to the state manager
	switch (currentOption)
	{
	case 0:
		return "blackjack_m";
		break;
	case 1:
		return "hangman_m";
		break;
	case 2:
		return "snake_m";
		break;
	case 3:
		return "exit";
		break;
	}
}