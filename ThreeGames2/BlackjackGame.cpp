#include "BlackjackGame.h"

BlackjackGame::BlackjackGame()
{
	//create the deck
	hearts = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	clubs = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	diamonds = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	spades = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
}

BlackjackGame::~BlackjackGame()
{

}

void BlackjackGame::setup()
{
	//clear out the hands in case of refresh
	playersHand.clear();
	houseHand.clear();

	//allows the game to check for a second hand, is false if the player already has one
	checkForSecondHand = true;

	//set all cards to false, indicating they can still be drawn
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cardsDrawn[i][j] = false;
		}
	}

	//set all hands values to 0
	playerHandValue = 0, houseHandValue = 0, playerHandValueA = 0, houseHandValueA = 0;

	//player draws two cards, house draws one
	hit(true);
	hit(true);
	hit(false);

	//check values of hands
	valueOfHand(true);
	valueOfHand(false);

	return;
}

void BlackjackGame::hit(bool player)
{
	//randomise the suit (4) and card (13)
	int i = (rand() % 4);
	int j = (rand() % 13);

	//check to see if they have already been drawn
	while (checkCard(i,j) == true)
	{
		i = (rand() % 4);
		j = (rand() % 13);
	}

	if (player == true) //adding the card to the player hand
	{
		switch (i)
		{
		case 0:
			playersHand.push_back(hearts[j]);
			cardsDrawn[i][j] = true;
			break;
		case 1:
			playersHand.push_back(clubs[j]);
			cardsDrawn[i][j] = true;
			break;
		case 2:
			playersHand.push_back(diamonds[j]);
			cardsDrawn[i][j] = true;
			break;
		case 3:
			playersHand.push_back(spades[j]);
			cardsDrawn[i][j] = true;
			break;
		}
	}
	else if (player == false) //adding the card to the house hand
	{
		switch (i)
		{
		case 0:
			houseHand.push_back(hearts[j]);
			cardsDrawn[i][j] = true;
			break;
		case 1:
			houseHand.push_back(clubs[j]);
			cardsDrawn[i][j] = true;
			break;
		case 2:
			houseHand.push_back(diamonds[j]);
			cardsDrawn[i][j] = true;
			break;
		case 3:
			houseHand.push_back(spades[j]);
			cardsDrawn[i][j] = true;
			break;
		}
	}

	return;
}

void BlackjackGame::stand()
{
	//house ocntinues to draw until it is above 17 value
	while (houseHandValue < 17)
	{
		hit(false);
		valueOfHand(false);
		printToScreen();

		int delay = 500;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	if (houseHandValue > playerHandValue && houseHandValue <= 21)
	{
		bust();
		clear();
	}
	if (checkWin() == true)
	{
		setup();
		score++;
		clear();
	}

	if (checkLose() == true)
	{
		bust();
		clear();
		setup();
	}

	if (checkDraw() == true) //check to see if the player and house hold equal value
	{
		setup();
		clear();
	}
	execute = false;

	return;
}

void BlackjackGame::split()
{
	//split the hand. checking happens outside function. should probably move that
	secondHand = true;
	checkForSecondHand = true;
	dupeCard = playersHand[0];
	playersHand.erase(playersHand.begin() + 1);

	return;
}

void BlackjackGame::valueOfHand(bool player)
{
	if (player == true) //check the player hand value
	{
		playerHandValue = 0;
		playerHandValueA = 0;

		for (int i = 0; i < playersHand.size(); i++)
		{
			if (playersHand[i] == "A")
			{
				playerHandValue = playerHandValue + 1;    //first hand where aces count as 1
				playerHandValueA = playerHandValueA + 11; //second hand where aces count as 11
			}
			else if (playersHand[i] == "2")
			{
				playerHandValue = playerHandValue + 2;
				playerHandValueA = playerHandValueA + 2;
			}
			else if (playersHand[i] == "3")
			{
				playerHandValue = playerHandValue + 3;
				playerHandValueA = playerHandValueA + 3;
			}
			else if (playersHand[i] == "4")
			{
				playerHandValue = playerHandValue + 4;
				playerHandValueA = playerHandValueA + 4;
			}
			else if (playersHand[i] == "5")
			{
				playerHandValue = playerHandValue + 5;
				playerHandValueA = playerHandValueA + 5;
			}
			else if (playersHand[i] == "6")
			{
				playerHandValue = playerHandValue + 6;
				playerHandValueA = playerHandValueA + 6;
			}
			else if (playersHand[i] == "7")
			{
				playerHandValue = playerHandValue + 7;
				playerHandValueA = playerHandValueA + 7;
			}
			else if (playersHand[i] == "8")
			{
				playerHandValue = playerHandValue + 8;
				playerHandValueA = playerHandValueA + 8;
			}
			else if (playersHand[i] == "9")
			{
				playerHandValue = playerHandValue + 9;
				playerHandValueA = playerHandValueA + 9;
			}
			else if (playersHand[i] == "10" || "Jack" || "Queen" || "King") //all worth 10
			{
				playerHandValue = playerHandValue + 10;
				playerHandValueA = playerHandValueA + 10;
			}
		}
	}
	else if (player == false) //check the house hand value
	{
		houseHandValue = 0;
		houseHandValueA = 0;

		for (int i = 0; i < houseHand.size(); i++)
		{
			if (houseHand[i] == "A")
			{
				houseHandValue = houseHandValue + 1;    //first hand where aces count as 1
				houseHandValueA = houseHandValueA + 11; //second hand where aces count as 11
			}
			else if (houseHand[i] == "2")
			{
				houseHandValue = houseHandValue + 2;
				houseHandValueA = houseHandValueA + 2;
			}
			else if (houseHand[i] == "3")
			{
				houseHandValue = houseHandValue + 3;
				houseHandValueA = houseHandValueA + 3;
			}
			else if (houseHand[i] == "4")
			{
				houseHandValue = houseHandValue + 4;
				houseHandValueA = houseHandValueA + 4;
			}
			else if (houseHand[i] == "5")
			{
				houseHandValue = houseHandValue + 5;
				houseHandValueA = houseHandValueA + 5;
			}
			else if (houseHand[i] == "6")
			{
				houseHandValue = houseHandValue + 6;
				houseHandValueA = houseHandValueA + 6;
			}
			else if (houseHand[i] == "7")
			{
				houseHandValue = houseHandValue + 7;
				houseHandValueA = houseHandValueA + 7;
			}
			else if (houseHand[i] == "8")
			{
				houseHandValue = houseHandValue + 8;
				houseHandValueA = houseHandValueA + 8;
			}
			else if (houseHand[i] == "9")
			{
				houseHandValue = houseHandValue + 9;
				houseHandValueA = houseHandValueA + 9;
			}
			else if (houseHand[i] == "10" || "Jack" || "Queen" || "King") //all worth 10
			{
				houseHandValue = houseHandValue + 10;
				houseHandValueA = houseHandValueA + 10;
			}
		}
	}
	
	return;
}

void BlackjackGame::printToScreen()
{
	//print all information player may need
	mvprintw(0, 0, "%s", "Now playing: Blackjack");
	mvprintw(2, 0, "%s", "Current score:");
	mvprintw(3, 0, "%s", "House hand value:");
	mvprintw(4, 0, "%s", "Your hand value:");

	mvprintw(2, 15, "%d", score);
	mvprintw(3, 18, "%d", houseHandValue);
	mvprintw(4, 17, "%d", playerHandValue);

	mvprintw(4, 19, "%c", '/');
	mvprintw(4, 22, "%d", playerHandValueA);

	mvprintw(19, 0, "%s", "[Hit]");
	mvprintw(20, 0, "%s", "[Stand]");
	mvprintw(21, 0, "%s", "[Double Down]");
	mvprintw(22, 0, "%s", "[Split]");
	mvprintw(23, 0, "%s", "[Exit Game]");

	mvprintw(0, 31, "%s", "Your hand contains:");

	for (int i = 0; i < playersHand.size(); i++)
	{
		mvprintw(0, 55 + (5 * i), playersHand[i].c_str());
	}

	attron(COLOR_PAIR(3));
	if (menuInput == 0)
	{
		mvprintw(19, 0, "%s", "[Hit]");
	}
	else if (menuInput == 1)
	{
		mvprintw(20, 0, "%s", "[Stand]");
	}
	else if (menuInput == 2)
	{
		mvprintw(21, 0, "%s", "[Double Down]");
	}
	else if (menuInput == 3)
	{
		mvprintw(22, 0, "%s", "[Split]");
	}
	else if (menuInput == 4)
	{
		mvprintw(23, 0, "%s", "[Exit Game]");
	}
	attroff(COLOR_PAIR(3));

	if (secondHand == true)
	{
		mvprintw(1, 31, "%s", "You have a second hand.");
	}

	refresh();
	return;
}

bool BlackjackGame::checkCard(int suit, int card)
{
	//checking to see if card has already been drawn in 2D vector
	if (cardsDrawn[suit][card] == true)
	{
		return true;
	}

	return false;
}

bool BlackjackGame::checkWin() //check to see if the player wins
{
	if (houseHandValue > 21 && playerHandValue <= 21)
	{
		return true;
	}

	if (houseHandValue <= 21 && playerHandValue > houseHandValue && playerHandValue <= 21)
	{
		return true;
	}

	return false;
}

bool BlackjackGame::checkLose() //check to see if the player loses
{
	if (houseHandValue > 17 && houseHandValue < 21 && houseHandValue > playerHandValue)
	{
		if (houseHandValue > playerHandValueA)
		{
			return true;
		}
	}

	if (playerHandValue > 21)
	{
		return true;
	}

	return false;
}

bool BlackjackGame::checkDraw() //check to see if the player draws with the house
{
	if (playerHandValue == houseHandValue)
	{
		return true;
	}

	return false;
}

void BlackjackGame::bust() //draw the BUST screen
{
	clear();
	attron(COLOR_PAIR(5));
	mvprintw(12, 35, "%s", "BUST");
	mvprintw(13, 30, "%s", "Press enter to continue.");
	attroff(COLOR_PAIR(5));
	refresh();

	int i = getch();
	while (i != 10)
	{
		//keep player on game over screen until enter is pressed
		i = getch();
	}
}

int BlackjackGame::menu() //mini menu used in blackjack_g only
{
	int c = getch();

	switch (c)
	{
	case KEY_UP:
		menuInput--;
		if (menuInput < 0)
		{
			menuInput = 4;
		}
		return menuInput;
		break;
	case KEY_DOWN:
		menuInput++;
		if (menuInput > 4)
		{
			menuInput = 0;
		}
		return menuInput;
		break;
	case 10:
		execute = true;
		return menuInput;
		break;
	}
}

bool BlackjackGame::update()
{
	//big ol' update loop
	if (playerHandValue > 21 && checkForSecondHand == true)
	{
		//check to see if player is bust
		bust();
		clear();
		setup();
	}
	else if (playerHandValue > 21 && checkForSecondHand == false)
	{
		//check to see if player is bust but has a second hand
		playersHand.clear();
		playersHand.push_back(dupeCard);
		secondHand = false;
		checkForSecondHand = true;
		clear();
		printToScreen();
	}

	printToScreen();

	//menu options
	int i = menu();
	if (i == 0 && execute == true) //hit
	{
		hit(true);
		valueOfHand(true);
		valueOfHand(false);
		execute = false;
	}

	if (i == 1 && execute == true) //stand
	{
		stand();
	}

	if (i == 2 && execute == true) //double down
	{
		if (playersHand.size() == 2 && playerHandValue >= 9 && playerHandValue <= 11)
		{
			hit(true);
			valueOfHand(true);
			stand();
		}
		execute = false;
	}

	if (checkForSecondHand == true && i == 3 && execute == true) //split
	{
		if (playersHand[0] == playersHand[1])
		{
			split();
			checkForSecondHand = false;
			execute = false;
		}
	}
	
	if (i == 4 && execute == true) //return to blackjack menu
	{
		execute = false;
		return true;
	}

	return false;
}