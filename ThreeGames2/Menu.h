#ifndef MENU_H
#define MENU_H

#include "curses.h"
#include <vector>
#include <string>

class Menu
{
public:
	Menu();
	~Menu();

	int screenY, screenX, currentOption;
	int maxOption;

	std::vector<std::string> options;

	std::vector<int> Y;
	std::vector<int> X;

	void setup(bool vertical);
	int optionSelect(int userInput);
	void highlightSelection();
	void clearLast();
	void update(int userInput);
	bool isActive();

protected:
	bool active = true;

private:

};

#endif