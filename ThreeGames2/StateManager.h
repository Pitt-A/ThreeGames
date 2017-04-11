#include "curses.h"
#include "MainMenu.h"
#include "BlackjackMenu.h"
#include "HangmanMenu.h"
#include "SnakeMenu.h"
#include "BlackjackGame.h"
#include "HangmanGame.h"
#include "SnakeGame.h"
#include "HangmanDifficulty.h"

class StateManager
{
public:
	StateManager();
	~StateManager();
	void update();
	void stateChange(std::string state);

	MainMenu mainMenu;
	BlackjackMenu blackjackMenu;
	HangmanMenu hangmanMenu;
	SnakeMenu snakeMenu;
	BlackjackGame blackjackGame;
	HangmanGame hangmanGame;
	SnakeGame snakeGame;
	HangmanDifficulty hangmanDifficulty;

private:
	enum state {menu_m, blackjack_m, blackjack_g, hangman_m, hangman_g, hangman_d, snake_m, snake_g, exit};
	state states = menu_m;
	bool stateActive;
	int hangmanDiff;

};