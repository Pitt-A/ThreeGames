#include "curses.h"
#include "Menu.h"
#include <vector>

class HangmanMenu : public virtual Menu
{
public:
	HangmanMenu();
	~HangmanMenu();
	void display();
	std::string returnInput();
private:
};