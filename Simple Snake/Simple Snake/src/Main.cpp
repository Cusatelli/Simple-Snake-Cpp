#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>

#include "Colors.h"

bool gameOver;
int score;
int incrementTime;
int scorePrintCount;

// Dimensions
const int width = 20;
const int height = 20;

// Coordinates
int x, y, foodX, foodY;
int tailX[100], tailY[100];
int tailLength;

// Movement
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
	incrementTime = 0;
	scorePrintCount = 0;
}

void Draw()
{
	system("cls");
	// Snake Title:
	std::cout << std::endl << BOLDBLACK << "  " << RESET;
	for (int i = 0; i < width + 4; i++)
	{
		std::cout << BOLDBLACK << "# " << RESET;
	}
	std::cout << std::endl;

	std::cout << BOLDBLACK << "  #                                             # " << RESET << std::endl;
	std::cout << BOLDBLACK << "  #                  " << BOLDYELLOW << "S N A K E" << BOLDBLACK << "                  # " << RESET << std::endl;
	std::cout << BOLDBLACK << "  #               " << BOLDYELLOW << "T H E   G A M E" << BOLDBLACK << "               # " << RESET << std::endl;
	std::cout << BOLDBLACK << "  #                                             # " << RESET << std::endl;

	std::cout << BOLDBLACK << "  " << RESET;
	for (int i = 0; i < width + 4; i++)
	{
		std::cout << BOLDBLACK << "# " << RESET;
	}
	std::cout << std::endl << BOLDBLACK << "  " << RESET;
	for (int i = 0; i < width + 4; i++)
	{
		std::cout << BOLDBLACK << "# " << RESET;
	}
	std::cout << std::endl;

	// Top Border:
	std::cout << BOLDBLACK "  # " << RESET;
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << BOLDRED << "v " << RESET;
	}
	std::cout << BOLDBLACK "# " << RESET;
	std::cout << std::endl;

	// Map:
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				std::cout << BOLDBLACK << "  # " << BOLDRED << "> " << RESET;
			}

			if (i == y && j == x)
			{
				std::cout << BOLDMAGENTA << "0 " << RESET;
			}
			else if (i == foodY && j == foodX)
			{
				std::cout << BOLDGREEN << "+ " << RESET;
			}
			else
			{
				bool printed = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						std::cout << BOLDMAGENTA << "O " << RESET;
						printed = true;
					}
				}
				if (!printed)
				{
					std::cout << "  ";
				}
			}

			if (j == width - 1)
			{
				std::cout << BOLDRED << "< " << BOLDBLACK << "# " << RESET << std::endl;
			}
		}
	}

	// Bottom Border:
	std::cout << BOLDBLACK "  # " << RESET;
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << BOLDRED << "^ " << RESET;
	}
	std::cout << BOLDBLACK "# " << RESET << std::endl;

	// Print Score:
	std::cout << BOLDBLACK "  # " << RESET;
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << BOLDBLACK << "# " << RESET;
	}
	std::cout << BOLDBLACK "# " << RESET << std::endl;
	std::cout << BOLDBLACK << "  #                                             # " << RESET << std::endl;
	std::string printScore = std::to_string(score);
	std::cout << BOLDBLACK << "  #             " << BOLDYELLOW << "S C O R E:  " << RESET;
	for (int i = 0; i < printScore.length(); i++)
	{
		std::cout << BOLDYELLOW << printScore.at(i) << " " << RESET;
	}
	for (int i = 0; i < (width - 11) - printScore.length(); i++)
	{
		std::cout << "  ";
	}
	std::cout << BOLDBLACK << "  #" << RESET << std::endl;
	std::cout << BOLDBLACK << "  #                                             # " << RESET << std::endl;
	std::cout << BOLDBLACK "  # " << RESET;
	for (int i = 0; i < width + 2; i++)
	{
		std::cout << BOLDBLACK << "# " << RESET;
	}
	std::cout << BOLDBLACK "# " << RESET << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (dir != DOWN)
			{
				dir = UP;
			}
			break;
		case 'a':
			if (dir != RIGHT)
			{
				dir = LEFT;
			}
			break;
		case 's':
			if (dir != UP)
			{
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT)
			{
				dir = RIGHT;
			}
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int previousX = tailX[0];
	int previousY = tailY[0];
	int previousX_2, previousY_2;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLength; i++)
	{
		previousX_2 = tailX[i];
		previousY_2 = tailY[i];
		tailX[i] = previousX;
		tailY[i] = previousY;
		previousX = previousX_2;
		previousY = previousY_2;
	}

	switch (dir)
	{
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (x >= width || x < 0 || y >= height || y < 0)
	{
		gameOver = true;
	}

	for (int i = 0; i < tailLength; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == foodX && y == foodY)
	{
		score += 10;
		if (tailLength % 10 == 0)
		{
			scorePrintCount++;
		}

		if (score % 50 == 0 && incrementTime != 45) {
			incrementTime += 5;
		}
		foodX = rand() % width;
		foodY = rand() % height;
		tailLength++;
	}
}

void GameLoop()
{
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(46 - incrementTime);
	}
}

int main()
{
	Setup();
	GameLoop();
	return 0;
}
