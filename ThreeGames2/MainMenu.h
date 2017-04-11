#include "curses.h"
#include "Menu.h"
#include <vector>

class MainMenu : public virtual Menu
{
public:
	MainMenu();
	~MainMenu();
	void display();
	std::string returnInput();
private:
};