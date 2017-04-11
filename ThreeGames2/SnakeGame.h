#include "curses.h"
#include <vector>
#include <chrono>
#include <thread>

class SnakeGame
{
public:
	SnakeGame();
	~SnakeGame();
	void setup();
	void printToScreen();
	void moveSnake();
	void moveSnakeBody();
	void spawnPowerUp();
	void spawnSnakeBody();
	bool pause();
	bool checkBorderCollision();
	bool checkBodyCollision();
	void gameOver();
	bool update();
private:
	int score, powerX, powerY, tempX, tempY, tempScore;
	char powerUp = '$', snakeBody = '#';
	bool active = true;

	std::vector<int> xCoord;
	std::vector<int> yCoord;

	enum direction {left, right, up, down};
	direction dir = up;

};