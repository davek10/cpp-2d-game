#include "Ball.h"

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

void Ball::setRadius(float shapeRadius) // x = shape.getRadius() = Player radius
{
	float randNumber;
	if ((int)(shapeRadius - smallestRadius) == 0) {
		randNumber = 0;
	}
	else {
		randNumber = rand() % (int)(shapeRadius - smallestRadius);
	}

	if (isBigger) {
		shape.setRadius(randNumber + shapeRadius);
	}
	else {
		shape.setRadius(randNumber + smallestRadius);
	}
}

void Ball::resetPosition(float rangeOutsideScreen, bool random)
{
	if (random && rangeOutsideScreen != 0) {
		rangeOutsideScreen = rand() % (int) rangeOutsideScreen;
	}

	float randNumber;
	if ((int)(windowHeight - ceil(shape.getRadius() * 2)) == 0) {
		randNumber = 0;
	}
	else {
		randNumber = rand() % (int)(windowHeight - ceil(shape.getRadius() * 2));
	}

	if (leftToRight) {
		shape.setPosition(-shape.getRadius() - rangeOutsideScreen, randNumber);
	}
	else {
		shape.setPosition(windowWidth + rangeOutsideScreen, randNumber);
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

