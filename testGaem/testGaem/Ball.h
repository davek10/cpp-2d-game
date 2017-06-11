#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
class Ball
{
public:
	Ball(int windowWidth, int windowHeight);
	Ball(int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, bool isBigger, bool lefty, float ballSpeed);
	~Ball();
	sf::CircleShape getBall();
	float getX();
	float getY();
	float getRadius();
	void resetMove(float radius);
	void setRadius(float shapeRadius);
	void resetPosition(float rangeOutsideScreen, bool random);
	void setPosition(float x, float y);
	void setColor(sf::Color color);
	void move(float shapeRadius);
	void moveOut(float shapeRadius);
	float stepCalcPos(float currentPosition, float goal, float step);
	bool isDestroyer();
	
private:
	int windowWidth;
	int windowHeight;
	bool isBigger;
	bool leftToRight;
	float ballSpeed;
	bool destroys;
	sf::CircleShape shape;
	const float smallestRadius = 10.f;
	float xBallPos; // Used for shape2
	float yBallPos;
	sf::Text text;
	sf::Font font;
	int hits = 0;
};

