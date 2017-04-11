#include "curses.h"
#include "Menu.h"
#include <vector>

class BlackjackMenu : public virtual Menu
{
public:
	BlackjackMenu();
	~BlackjackMenu();
	void display();
	std::string returnInput();
private:
};