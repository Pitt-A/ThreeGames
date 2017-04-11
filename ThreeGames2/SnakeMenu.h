#include "curses.h"
#include "Menu.h"
#include <vector>

class SnakeMenu : public virtual Menu
{
public:
	SnakeMenu();
	~SnakeMenu();
	void display();
	std::string returnInput();
private:
};