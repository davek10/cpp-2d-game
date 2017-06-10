#include "Ball.h"

/*
	Prevent that no rand % can do it with 0
*/

Ball::Ball(int windowWidth, int windowHeight)
{
	Ball::windowWidth = windowWidth;
	Ball::windowHeight = windowHeight;
}

Ball::Ball(int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, sf::Color color, bool isBigger, bool lefty)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->setColor(color);
	this->isBigger = isBigger;
	this->leftToRight = lefty;
	this->setRadius(playerRadius);
	if (rangeOutsideScreen != 0) {
		this->resetPosition(rangeOutsideScreen, true);
	}
	else {
		this->resetPosition(rangeOutsideScreen, false);
	}
}

Ball::~Ball()
{
}

sf::CircleShape Ball::getBall()
{
	return this->shape;
}

void Ball::resetMove(float radius) {
	this->shape.setPosition(-shape.getRadius(), 0); // Should be outisde screen for every ball
	this->setRadius(radius);
	this->resetPosition(0, false);
}

void Ball::setRadius(int x) // x = shape.getRadius() = Player radius
{
	if (isBigger) {
		shape.setRadius((rand() % (int)(x - smallestRadius) + x));
	}
	else {
		shape.setRadius((rand() % (int)(x - smallestRadius) + smallestRadius));
	}
}

void Ball::resetPosition(int rangeOutsideScreen, bool random)
{
	if (random) {
		rangeOutsideScreen = rand() % rangeOutsideScreen;
	}
	if (leftToRight) {
		shape.setPosition(-shape.getRadius() - rangeOutsideScreen, rand() % (int)(windowHeight - ceil(shape.getRadius() * 2)));
	}
	else {
		shape.setPosition(windowWidth + rangeOutsideScreen, rand() % (int)(windowHeight - ceil(shape.getRadius() * 2)));
	}
}

void Ball::setPosition(float x, float y) {
	this->shape.setPosition(x, y);
}

float Ball::getX() {
	return this->shape.getPosition().x;
}

float Ball::getY() {
	return this->shape.getPosition().y;
}

float Ball::getRadius()
{
	return this->shape.getRadius();
}

void Ball::setColor(sf::Color color) {
	shape.setFillColor(color);
}

