#include "Menu.h"

Menu::Menu()
{
	//setting the initial option to the first
	currentOption = 0;
}

Menu::~Menu()
{

}

void Menu::setup(bool vertical)
{
	//setting up the vectors of coordinates
	screenY = 24, screenX = 80;

	if (vertical)
	{
		Y = { screenY / 10 * 2, screenY / 10 * 3, screenY / 10 * 4, screenY / 10 * 5 };
		X = { screenX / 2 - 5, screenX / 2 - 4, screenX / 2 - 3, screenX / 2 - 3 };
	}
	else
	{
		Y = { screenY - 5, screenY - 5, screenY - 5, screenY - 5 };
		X = { screenX / 8, screenX / 8 * 3, screenX / 8 * 5, screenX / 8 * 7 };
	}

	//ensuring the user can go off the menu with a maximum option 
	maxOption = options.size() - 1;

	return;
}

int Menu::optionSelect(int userInput) 
{
	//using the users input to navigate the menu
	//I allowed the user to use left and right on vertical menus
	//and vice versa
	while (active)
	{
		switch (userInput)
		{
		case KEY_UP:
			currentOption--;
			if (currentOption < 0)
			{
				currentOption = maxOption;
			}
			break;
		case KEY_DOWN:
			currentOption++;
			if (currentOption > maxOption)
			{
				currentOption = 0;
			}
			break;
		case KEY_RIGHT:
			currentOption++;
			if (currentOption > maxOption)
			{
				currentOption = 0;
			}
			break;
		case KEY_LEFT:
			currentOption--;
			if (currentOption < 0)
			{
				currentOption = maxOption;
			}
			break;
		default:
			break;
		}

		return currentOption;
	}
		
}

void Menu::highlightSelection()
{
	//highlighting the current option
	clearLast();
	attron(COLOR_PAIR(3));
	mvprintw(Y[currentOption], X[currentOption], options.at(currentOption).c_str());
	attroff(COLOR_PAIR(3));
	refresh();

	return;
}

void Menu::clearLast()
{
	//clearing the previous option so that only one option is highlighted at a time
	attron(COLOR_PAIR(2));
	for (int i = 0; i <= maxOption; i++)
	{
		mvprintw(Y[i], X[i], options.at(i).c_str());
	}
	attroff(COLOR_PAIR(2));

	return;
}

void Menu::update(int userInput)
{
	//update loop
	currentOption = optionSelect(userInput);
	highlightSelection();
	refresh();
}

bool Menu::isActive()
{
	return active;
}