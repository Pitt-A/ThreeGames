#include "curses.h"
#include "Menu.h"

class HangmanDifficulty : public virtual Menu
{
public:
	HangmanDifficulty();
	~HangmanDifficulty();
	void display(int diff);
	int returnDifficulty();
	std::string returnInput();
private:
	std::string difficulty;
};