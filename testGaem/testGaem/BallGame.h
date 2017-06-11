#pragma once
#include "Ball.h"
#include <iostream>

class BallGame
{
public:
	BallGame(sf::RenderWindow* window, int windowWidth, int windowHeight, sf::Font font);
	~BallGame();
	void renderingMethod(float step, float ballSpeed, float sizeChange, float smallestRadius, std::vector<Ball> ballArray);
	void newCirclePos(sf::CircleShape shape);
	float stepCalcPos(float currentPosition, float goal, float step);
private:
	sf::RenderWindow* window;
	int windowWidth;
	int windowHeight;
	sf::Text text;
	sf::Font font;
	sf::CircleShape shape;

	sf::CircleShape shape2;
	float xBallPos; // Used for shape2
	float yBallPos;
	int hits;

	Ball smallerBall1;
	Ball smallerBall2;
	Ball biggerBall1;
	Ball smallerBall3;
	Ball biggerBall2;
};

