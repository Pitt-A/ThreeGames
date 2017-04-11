#include "SnakeMenu.h"

SnakeMenu::SnakeMenu()
{
	//create the options vector for snake
	options.clear();
	options.push_back("[Play]");
	options.push_back("[Back]");
	options.push_back("[Exit]");

	Menu::setup(false);
}

SnakeMenu::~SnakeMenu()
{

}

void SnakeMenu::display()
{
	//displaying the welcome message
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "%s", "Welcome to Snake!");
	attroff(COLOR_PAIR(1));
}

std::string SnakeMenu::returnInput()
{
	//returning the input to the state manager
	switch (currentOption)
	{
	case 0:
		return "snake_g";
		break;
	case 1:
		return "menu_m";
		break;
	case 2:
		return "exit";
		break;
	}
}