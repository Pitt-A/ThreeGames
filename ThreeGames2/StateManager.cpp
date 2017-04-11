#include "StateManager.h"

StateManager::StateManager()
{
	//call the update function when it is built in main
	update();
	stateActive = true;
}

StateManager::~StateManager()
{

}

void StateManager::update()
{
	//set up the difficulty and var for input
	hangmanDiff = 0;
	int c = 0;
	stateActive = true;
	while (stateActive == true)
	{
		switch (states)
		{
		case menu_m: //main menu
			clear();
			mainMenu.display();
			mainMenu.update(c);
			while (states == menu_m)
			{
				c = getch();
				mainMenu.update(c);
				if (c == 10)
				{
					stateChange(mainMenu.returnInput());
				}
			}
			break;
		case blackjack_m: //blackjack menu
			clear();
			blackjackMenu.display();
			blackjackMenu.update(c);
			while (states == blackjack_m)
			{
				c = getch();
				blackjackMenu.update(c);
				if (c == 10)
				{
					stateChange(blackjackMenu.returnInput());
				}
			}
			break;
		case blackjack_g: //blackjack game
			nodelay(stdscr, false);
			clear();
			blackjackGame.setup();
			while (states == blackjack_g)
			{
				if (blackjackGame.update() == true)
				{
					states = blackjack_m;
				}
			}
			break;
		case hangman_m: //hangman menu
			clear();
			hangmanMenu.display();
			hangmanMenu.update(c);
			while (states == hangman_m)
			{
				c = getch();
				hangmanMenu.update(c);
				if (c == 10)
				{
					stateChange(hangmanMenu.returnInput());
				}
			}
			break;
		case hangman_g: //hangman game
			nodelay(stdscr, false);
			clear();
			hangmanGame.setup(hangmanDiff);
			while (states == hangman_g)
			{
				if (hangmanGame.update() == true)
				{
					states = hangman_m;
				}
			}
			break;
		case hangman_d: //hangman difficulty menu
			clear();
			hangmanDifficulty.display(hangmanDiff);
			hangmanDifficulty.update(c);
			while (states == hangman_d)
			{
				c = getch();
				hangmanDifficulty.update(c);
				if (c == 10)
				{
					hangmanDiff = hangmanDifficulty.returnDifficulty();
					stateChange(hangmanDifficulty.returnInput());
				}
			}
			break;
		case snake_m: //snake menu
			clear();
			snakeMenu.display();
			snakeMenu.update(c);
			while (states == snake_m)
			{
				c = getch();
				snakeMenu.update(c);
				if (c == 10)
				{
					stateChange(snakeMenu.returnInput());
				}
			}
			break;
		case snake_g: //snake game
			nodelay(stdscr, true);
			clear();
			snakeGame.setup();
			while (states == snake_g)
			{
				if (snakeGame.update() == true)
				{
					states = snake_m;
				}
			}
			break;
		case exit: //closing the program
			stateActive = false;
			break;
		}
	}
}

void StateManager::stateChange(std::string state)
{
	//possible states of the program
	if (state == "blackjack_m")
	{
		states = blackjack_m;
	}
	else if (state == "hangman_m")
	{
		states = hangman_m;
	}
	else if (state == "snake_m")
	{
		states = snake_m;
	}
	else if (state == "blackjack_g")
	{
		states = blackjack_g;
	}
	else if (state == "hangman_g")
	{
		states = hangman_g;
	}
	else if (state == "snake_g")
	{
		states = snake_g;
	}
	else if (state == "hangman_d")
	{
		states = hangman_d;
	}
	else if (state == "exit")
	{
		states = exit;
	}
	else
	{
		states = menu_m;
	}
}