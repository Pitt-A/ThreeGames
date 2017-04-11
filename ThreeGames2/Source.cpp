//The central file for three games, Andrew Pitt
#include "curses.h"
#include "StateManager.h"
#include <chrono>

int main()
{
	//seeding the random elements of this program
	srand(time(0));

	//start PDCurses
	initscr();

	//turning the cursor invisible
	curs_set(0);
	//prevent buttons pressed to be printed to the screen
	noecho();
	//enable the keypad for using up, down, left, right keys etc.
	keypad(stdscr, true);

	//setting up color pairs to be used elsewere in the program
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);

	StateManager stateManager;

	//end PDCurses
	endwin();

	//end program
	return 0;
}