#include "BallGame.h"

/* 
BallGame . ReadMe

Initializes the balls with radius position and color
shape = playerball
Fix cooler color system
shape2 = runs around and hits are recorded, has goals where it wants to go
Catcher balls = smaller and bigger = goes from left to right, increases and decreases size of player ball depending on if they are bigger or smaller

TODO
Testa skillnad om man har window.setVerticalSyncEnabled(true); eller window.setFramerateLimit(60); (inte b�da)

Moving space background
Color shifting player ball

G�r all movement av Ball och collision fr�n en Ball array, f�r att l�ttare kunna l�gga till fler bollar

Power ups? Faster etc
*/
BallGame::BallGame(sf::RenderWindow * window, int windowWidth, int windowHeight, sf::Font font) 
	:	smallerBall1(windowWidth, windowHeight, shape.getRadius(), 0, sf::Color::Yellow, false, true),
		smallerBall2(windowWidth, windowHeight, shape.getRadius(), 30, sf::Color::Yellow, false, true),
		biggerBall1(windowWidth, windowHeight, shape.getRadius(), 90, sf::Color::Magenta, true, true) 
{
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->font = font;
	
	float step = 0.05 * 2;
	float ballSpeed = step / 3;
	float sizeChange = 10;

	text.setString("Hits: 0");
	text.setFillColor(sf::Color::Green);
	text.setFont(font);
	text.setPosition(10, 0);

	float smallestRadius = 10.f;
	float enemyBallStart = 200.f;
	hits = 0;


	shape.setRadius(25.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Red);
	shape2.setRadius(smallestRadius);
	shape.setPosition(enemyBallStart, enemyBallStart);
	shape.setFillColor(sf::Color::Blue);
	//smallerBall1(windowWidth, windowHeight, shape.getRadius(), 0, sf::Color::Yellow, false, true);
	//smallerBall2 = Ball(windowWidth, windowHeight, shape.getRadius(), 30, sf::Color::Yellow, false, true);
	//biggerBall1 = Ball(windowWidth, windowHeight, shape.getRadius(), 90, sf::Color::Magenta, true, true);

	newCirclePos(shape2); // Goal for shape2
	// Borde skicka med Ballarray
	renderingMethod(step, ballSpeed, sizeChange, smallestRadius);
}

void BallGame::renderingMethod(float step, float ballSpeed, float sizeChange, float smallestRadius) {
	while (window->isOpen()) { // Main loop for rendering

		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}

		// Keypresses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Green);
			float newX = pos.x;
			if (pos.x - step >= 0) {
				newX = newX - step;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Blue);
			float newX = pos.x;
			if (pos.x + step <= ((float)windowWidth - shape.getRadius() * 2)) {
				newX = newX + step;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Magenta);
			float newY = pos.y;
			if (pos.y - step >= 0) {
				newY = newY - step;
			}
			shape.setPosition(pos.x, newY);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f pos = shape.getPosition();
			shape.setFillColor(sf::Color::Cyan);
			float newY = pos.y;
			if (pos.y + step <= ((float)windowHeight - shape.getRadius() * 2)) {
				newY = newY + step;
			}
			shape.setPosition(pos.x, newY);
		}
		
		// Movement for the tiny ball
		shape2.setPosition(stepCalcPos(shape2.getPosition().x, xBallPos, step), stepCalcPos(shape2.getPosition().y, yBallPos, step));
		if (shape2.getPosition().x == xBallPos && shape2.getPosition().y == yBallPos) {
			newCirclePos(shape2);
		}

		// Collision between the 2 balls, shape and shape2 (calculating hits)
		if (pow((shape.getPosition().x + shape.getRadius()) - (shape2.getPosition().x + shape2.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (shape2.getPosition().y + shape2.getRadius()), 2) <= pow(shape.getRadius() + shape2.getRadius(), 2)) {
			hits++;
			sf::String str = "Hits: " + std::to_string(hits);
			text.setString(str);
			sf::Vector2f newPos = sf::Vector2f(rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)), rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)));
			newCirclePos(shape2);
			shape2.setPosition(newPos);
		}
		
		// Movement for dynamic balls
		// This will be made to work on a Ball[]
		smallerBall1.setPosition(stepCalcPos(smallerBall1.getX(), windowWidth + smallerBall1.getRadius(), ballSpeed), smallerBall1.getY());
		if (smallerBall1.getX() >= windowWidth + smallerBall1.getRadius()) {
			smallerBall1.resetMove(shape.getRadius());
		}

		smallerBall2.setPosition(stepCalcPos(smallerBall2.getX(), windowWidth + smallerBall2.getRadius(), ballSpeed), smallerBall2.getY());
		if (smallerBall2.getX() >= windowWidth + smallerBall2.getRadius()) {
			smallerBall2.resetMove(shape.getRadius());
		}

		biggerBall1.setPosition(stepCalcPos(biggerBall1.getX(), windowWidth + biggerBall1.getRadius(), ballSpeed), biggerBall1.getY());
		if (biggerBall1.getX() >= windowWidth + biggerBall1.getRadius()) {
			biggerBall1.resetMove(shape.getRadius());
		}


		// collision between player and balls to increase and decrease player ball size
		if (pow((shape.getPosition().x + shape.getRadius()) - (smallerBall1.getX() + smallerBall1.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (smallerBall1.getY() + smallerBall1.getRadius()), 2) <= pow(shape.getRadius() + smallerBall1.getRadius(), 2)) {
			if (shape.getRadius() >= smallerBall1.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + smallerBall1.getRadius() / sizeChange);
				smallerBall1.resetMove(shape.getRadius());
			}
			else if (shape.getRadius() < smallerBall1.getRadius()) { // Shrink
				shape.setRadius(shape.getRadius() - smallerBall1.getRadius() / sizeChange);
				smallerBall1.resetMove(shape.getRadius());
			}
		}

		if (pow((shape.getPosition().x + shape.getRadius()) - (smallerBall2.getX() + smallerBall2.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (smallerBall2.getY() + smallerBall2.getRadius()), 2) <= pow(shape.getRadius() + smallerBall2.getRadius(), 2)) {
			if (shape.getRadius() >= smallerBall2.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + smallerBall2.getRadius() / sizeChange);
				smallerBall2.resetMove(shape.getRadius());
			}
			else if (shape.getRadius() < smallerBall2.getRadius()) { // Shrink
				shape.setRadius(shape.getRadius() - smallerBall2.getRadius() / sizeChange);
				smallerBall2.resetMove(shape.getRadius());
			}
		}

		if (pow((shape.getPosition().x + shape.getRadius()) - (biggerBall1.getX() + biggerBall1.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (biggerBall1.getY() + biggerBall1.getRadius()), 2) <= pow(shape.getRadius() + biggerBall1.getRadius(), 2)) {
			if (shape.getRadius() >= biggerBall1.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + biggerBall1.getRadius() / sizeChange);
				biggerBall1.resetMove(shape.getRadius());
			}
			else if (shape.getRadius() < biggerBall1.getRadius()) { // Shrink
				shape.setRadius(shape.getRadius() - biggerBall1.getRadius() / sizeChange);
				biggerBall1.resetMove(shape.getRadius());
			}
		}
		
		window->clear();
		window->draw(shape);
		window->draw(shape2);
		window->draw(smallerBall1.getBall());
		window->draw(smallerBall2.getBall());
		window->draw(biggerBall1.getBall());
		window->draw(text);
		window->display();
	}
}


BallGame::~BallGame()
{
}

// Calculates ball coordinates for the small ball (not really modular since xBallPos is only used by shape2)
void BallGame::newCirclePos(sf::CircleShape shape) {
	xBallPos = rand() % (int)(windowWidth - ceil(shape.getRadius() * 2));
	yBallPos = rand() % (int)(windowHeight - ceil(shape.getRadius() * 2));
}

// Calculates the next coordinate when you are in @currentPosition and you are aiming to go to @goal with @step
float BallGame::stepCalcPos(float currentPosition, float goal, float step) {
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