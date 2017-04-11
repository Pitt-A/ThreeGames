#include "curses.h"
#include <vector>
#include <thread>
#include <chrono>

class BlackjackGame
{
public:
	BlackjackGame();
	~BlackjackGame();

	void setup();
	void hit(bool player);
	void stand();
	void split();
	void valueOfHand(bool player);
	void printToScreen();

	bool checkCard(int suit, int card);
	bool checkWin();
	bool checkLose();
	bool checkDraw();

	void bust();

	int menu();

	bool update();

private:
	int playerHandValue, houseHandValue, playerHandValueA, houseHandValueA, score = 0, menuInput;

	bool execute, secondHand, checkForSecondHand;

	bool cardsDrawn[4][13];

	std::string dupeCard;

	std::vector<std::string> hearts;
	std::vector<std::string> clubs;
	std::vector<std::string> diamonds;
	std::vector<std::string> spades;

	std::vector<std::string> playersHand;
	std::vector<std::string> houseHand;
	//std::vector<std::string> playersSecondHand;

};