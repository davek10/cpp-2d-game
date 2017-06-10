#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
class Ball
{
public:
	Ball(int windowWidth, int windowHeight);
	Ball(int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, sf::Color color, bool isBigger, bool lefty);
	~Ball();
	sf::CircleShape getBall();
	float getX();
	float getY();
	float getRadius();
	void resetMove(float radius);
	void setRadius(int x);
	void resetPosition(int rangeOutsideScreen, bool random);
	void setPosition(float x, float y);
	void setColor(sf::Color color);

	
private:
	int windowWidth;
	int windowHeight;
	bool isBigger;
	bool leftToRight;
	sf::CircleShape shape;
	const float smallestRadius = 10.f;
	float xBallPos; // Used for shape2
	float yBallPos;
	sf::Text text;
	sf::Font font;
	int hits = 0;
};

