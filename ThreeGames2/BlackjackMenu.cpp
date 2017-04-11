#include "BlackjackMenu.h"

BlackjackMenu::BlackjackMenu()
{
	//create the options vector for blackjack
	options.clear();
	options.push_back("[Play]");
	options.push_back("[Back]");
	options.push_back("[Exit]");

	Menu::setup(false);
}

BlackjackMenu::~BlackjackMenu()
{

}

void BlackjackMenu::display()
{
	//display the welcome message
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "%s", "Welcome to Blackjack!");
	attroff(COLOR_PAIR(1));

	return;
}

std::string BlackjackMenu::returnInput()
{
	//returning the input to the state manager
	switch (currentOption)
	{
	case 0:
		return "blackjack_g";
		break;
	case 1:
		return "menu_m";
		break;
	case 2:
		return "exit";
		break;
	}
}