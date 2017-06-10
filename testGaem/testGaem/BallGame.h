#pragma once
#include "Ball.h"

class BallGame
{
public:
	BallGame(sf::RenderWindow* window, int windowWidth, int windowHeight, sf::Font font);
	~BallGame();
	void renderingMethod(float step, float ballSpeed, float sizeChange, float smallestRadius);
	void newCirclePos(sf::CircleShape shape);
	float stepCalcPos(float currentPosition, float goal, float step);
private:
	sf::RenderWindow* window;
	int windowWidth;
	int windowHeight;
	sf::CircleShape shape;
	sf::CircleShape shape2;
	Ball smallerBall1;
	Ball smallerBall2;
	Ball biggerBall1;
	float xBallPos; // Used for shape2
	float yBallPos;
	sf::Text text;
	sf::Font font;
	int hits;
};

