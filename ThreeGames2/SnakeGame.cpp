#include "SnakeGame.h"

SnakeGame::SnakeGame()
{
	//setting up the coords of the head
	xCoord.reserve(1);
	yCoord.reserve(1);
	xCoord.push_back(40);
	yCoord.push_back(12);
	setup();
}

SnakeGame::~SnakeGame()
{
	
}

void SnakeGame::setup()
{
	//setting up the score, direciton and initial spawn of power up
	score = 0;
	tempScore = 0;
	dir = up;
	powerX = (rand() % 78) + 1;
	powerY = (rand() % 21) + 2;
	active = true;

	return;
}

void SnakeGame::printToScreen()
{
	clear();

	//print the score
	mvprintw(0, 2, "%s", "Current score:");
	attron(COLOR_PAIR(1));
	mvprintw(0, 17, "%d", score);
	attroff(COLOR_PAIR(1));

	//print "enter to pause"
	attron(COLOR_PAIR(6));
	mvprintw(0, 58, "%s", "Press enter to pause.");
	attroff(COLOR_PAIR(6));

	//print the snake's head
	attron(COLOR_PAIR(5));
	switch (dir)
	{
	case left:
		mvprintw(yCoord[0], xCoord[0], "%s", "<");
		break;
	case right:
		mvprintw(yCoord[0], xCoord[0], "%s", ">");
		break;
	case up:
		mvprintw(yCoord[0], xCoord[0], "%s", "^");
		break;
	case down:
		mvprintw(yCoord[0], xCoord[0], "%s", "V");
		break;
	}

	//print the borders
	for (int i = 0; i < 80; i++)
	{
		mvprintw(1, i, "%c", '*');
		mvprintw(24, i, "%c", '*');
	}
	for (int i = 0; i < 23; i++)
	{
		mvprintw(1 + i, 0, "%c", '*');
		mvprintw(1 + i, 79, "%c", '*');
	}
	attroff(COLOR_PAIR(5));

	//print the snake's body
	attron(COLOR_PAIR(6));
	for (int i = 1; i <= tempScore; i++)
	{
		mvprintw(yCoord[i], xCoord[i], "%c", snakeBody);
	}
	attroff(COLOR_PAIR(6));

	//print the power-up
	attron(COLOR_PAIR(1));
	mvprintw(powerY, powerX, "%c", powerUp);
	attroff(COLOR_PAIR(1));

	refresh();
	
	return;
}

void SnakeGame::moveSnake()
{
	//checking in place to prevent the snake from going back on itself
	int c = getch();
	switch (c)
	{
	case KEY_UP:
		if (dir != down)
		{
			dir = up;
		}
		break;
	case KEY_DOWN:
		if (dir != up)
		{
			dir = down;
		}
		break;
	case KEY_LEFT:
		if (dir != right)
		{
			dir = left;
		}
		break;
	case KEY_RIGHT:
		if (dir != left)
		{
			dir = right;
		}
		break;
	case 10:
		pause();
		break;
	}

	//moving the snake based on it's direction
	switch (dir)
	{
	case left:
		xCoord[0] -= 1;
		break;
	case right:
		xCoord[0] += 1;
		break;
	case up:
		yCoord[0] -= 1;
		break;
	case down:
		yCoord[0] += 1;
		break;
	}

	//handling consuming the power up
	if (xCoord[0] == powerX && yCoord[0] == powerY)
	{
		spawnPowerUp();
		spawnSnakeBody();
		score++;
		tempScore = score;
	}

	return;
}

void SnakeGame::moveSnakeBody()
{
	//moving the snakes body parts
	for (int i = tempScore; i > 0; i--)
	{
		yCoord[i] = yCoord[i - 1];
		xCoord[i] = xCoord[i - 1];
	}
	return;
}

void SnakeGame::spawnPowerUp()
{
	//spawning the power up in a random location inside the borders
	powerX = (rand() % 78) + 1;
	powerY = (rand() % 20) + 3;

	return;
}

bool SnakeGame::pause()
{
	//printing GAME PAUSED when it is paused
	if (active == true)
	{
		active = false;
		attron(COLOR_PAIR(6));
		mvprintw(10, 33, "%s", "GAME PAUSED");
		attroff(COLOR_PAIR(6));
		refresh();
	}
	
	//setting active to true only when enter (10) is pressed
	//this is how the game is unpaused
	while (active == false)
	{
		int i = getch();
		if (i == 10)
		{
			active = true;
		}
	}
	return false;
}

void SnakeGame::spawnSnakeBody()
{
	//spawning the snake body when a power up is eaten
	tempY = yCoord[tempScore];
	tempX = xCoord[tempScore];

	yCoord.push_back(tempY);
	xCoord.push_back(tempX);

	return;
}

bool SnakeGame::checkBorderCollision()
{
	//checking to see if the snake collides with the border
	if (yCoord[0] > 23 || yCoord[0] < 2 || xCoord[0] < 1 || xCoord[0] > 79)
	{
		return true;
	}

	return false;
}

bool SnakeGame::checkBodyCollision()
{
	//checking to see if the snake collides with its body
	for (int i = 3; i < yCoord.size(); i++)
	{
		if (yCoord[0] == yCoord[i] && xCoord[0] == xCoord[i])
		{
			return true;
		}
	}

	return false;
}

void SnakeGame::gameOver()
{
	//game over screen
	tempScore = 0;

	clear();
	attron(COLOR_PAIR(5));
	mvprintw(10, 34, "%s", "GAME OVER");
	attroff(COLOR_PAIR(5));

	mvprintw(13, 35, "%s", "Score:");
	mvprintw(13, 41, "%d", score);
	mvprintw(14, 27, "%s", "Press enter to continue.");

	refresh();

	int i = getch();
	while (i != 10)
	{
		//keep player on game over screen until enter is pressed
		i = getch();	
	}

	return;
}

bool SnakeGame::update()
{
	//the update loop
	if (active == true)
	{
		printToScreen();
		moveSnakeBody();
		moveSnake();

		//snake is in no delay mode, meaning the program doesnt wait for the
		//user to input something, it will skip it if they dont do anything.
		//to prevent the entire game form being executed instantly, I only 
		//execute a "frame" every 100 milliseconds

		int delay = 100;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		if (checkBodyCollision() == true || checkBorderCollision() == true)
		{
			gameOver();
			xCoord.clear();
			yCoord.clear();
			xCoord.push_back(40);
			yCoord.push_back(12);
			return true;
		}
		else
		{
			return false;
		}
	}
}