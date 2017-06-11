#include "Ball.h"

// Not used
Ball::Ball(int windowWidth, int windowHeight)
{
	Ball::windowWidth = windowWidth;
	Ball::windowHeight = windowHeight;
}

Ball::Ball(int windowWidth, int windowHeight, int playerRadius, int rangeOutsideScreen, bool isBigger, bool lefty, float ballSpeed)
{
	sf::Color bigger = sf::Color::Magenta;
	sf::Color smaller = sf::Color::Yellow;
	sf::Color destroyer = sf::Color::Red;
	float randomBallSpeed = 20;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->isBigger = isBigger;
	if (isBigger) {
		int nmb = rand() % 2;
		if (nmb == 0) { // 50 % = bigger ball = destroys
			this->destroys = true;
			this->setColor(destroyer);
		}
		else {
			this->destroys = false;
			this->setColor(bigger);
		}
	}
	else {
		this->destroys = false;
		this->setColor(smaller);
	}
	this->leftToRight = lefty;
	this->setRadius(playerRadius);
	if (rangeOutsideScreen != 0) {
		this->resetPosition(rangeOutsideScreen, true);
	}
	else {
		this->resetPosition(rangeOutsideScreen, false);
	}
	this->ballSpeed = (ballSpeed/ randomBallSpeed)*(rand() % (int)randomBallSpeed) + (ballSpeed / 2);
}

Ball::~Ball()
{
}

sf::CircleShape Ball::getBall()
{
	return this->shape;
}

bool Ball::isDestroyer() {
	return this->destroys;
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
		if (randNumber > windowHeight / 2) {
			randNumber = windowHeight / 2;
		}
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

void Ball::move(float shapeRadius) {
	if (leftToRight) {
		this->setPosition(stepCalcPos(this->getX(), windowWidth + this->getRadius(), this->ballSpeed), this->getY());
		if (this->getX() >= windowWidth + this->getRadius()) {
			this->resetMove(shapeRadius);
		}
	}
	else {
		this->setPosition(stepCalcPos(this->getX(), -this->getRadius(), ballSpeed), this->getY());
		if (this->getX() <= -this->getRadius()) {
			this->resetMove(shapeRadius);
		}
	}
}

void Ball::moveOut(float shapeRadius) { // Flytta tillbaks bollarna utanför skärmen
	if (!leftToRight) {
		this->setPosition(stepCalcPos(this->getX(), windowWidth + this->getRadius(), this->ballSpeed*2), this->getY());
		if (this->getX() >= windowWidth + this->getRadius()) {
			this->resetMove(shapeRadius);
		}
	}
	else {
		this->setPosition(stepCalcPos(this->getX(), -this->getRadius(), ballSpeed*2), this->getY());
		if (this->getX() <= -this->getRadius()) {
			this->resetMove(shapeRadius);
		}
	}
}

// Calculates the next coordinate when you are in @currentPosition and you are aiming to go to @goal with @step
float Ball::stepCalcPos(float currentPosition, float goal, float step) {
	step = step * 2;
	if (currentPosition < goal) {
		if ((currentPosition + step) > goal) {
			return goal;
		}
		else {
			return (currentPosition + step);
		}
	}
	else if (currentPosition > goal) {
		if ((currentPosition - step) < goal) {
			return goal;
		}
		else {
			return (currentPosition - step);
		}
	}
	else if (currentPosition == goal) {
		return currentPosition;
	}
}
