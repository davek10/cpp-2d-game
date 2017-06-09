#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
using namespace std;

// 640 x 480
int windowWidth = 1024;
int windowHeight = 768;
sf::CircleShape shape;
sf::CircleShape shape2;
sf::CircleShape smallerBall1;
sf::CircleShape smallerBall2;
sf::CircleShape biggerBall1;
float xBallPos;
float yBallPos;

sf::Text text;
sf::Font font;
sf::String hitText = "Hits: ";
int hits = 0;

// Calculates ball coordinates for the small ball (not really modular since xBallPos is only used by shape2)
void newCirclePos(sf::CircleShape shape) {
	xBallPos = rand() % (int)(windowWidth - ceil(shape.getRadius()*2));
	yBallPos = rand() % (int)(windowHeight - ceil(shape.getRadius()*2));
}

// Calculates the next coordinate when you are in @currentPosition and you are aiming to go to @goal with @step
float stepCalcPos(float currentPosition, float goal, float step) {
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

int main() {
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Application");
	float step = 0.05*2;
	float ballSpeed = step/3;
	srand(time(NULL)); // Sätter seed för random (osäker exakt hur funkar, copy/paste från exempel)
	float smallestRadius = 10.f;
	float enemyBallStart = 200.f;

	/* Initializes the balls with radius position and color
		shape = playerball
			Fix cooler color system
		shape2 = runs around and hits are recorded, has goals where it wants to go
		Catcher balls = smaller and bigger = goes from left to right, increases and decreases size of player
			ball depending on if they are bigger or smaller
	*/
	shape.setRadius(25.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Red);
	shape2.setRadius(smallestRadius);
	shape.setPosition(enemyBallStart, enemyBallStart);
	shape.setFillColor(sf::Color::Blue);
	smallerBall1.setRadius((rand() % (int)(shape.getRadius()- smallestRadius) + smallestRadius));
	smallerBall1.setPosition(-smallerBall1.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall1.getRadius() * 2)));
	smallerBall1.setFillColor(sf::Color::Yellow);
	smallerBall2.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
	smallerBall2.setPosition(-smallerBall2.getRadius()-30, rand() % (int)(windowHeight - ceil(smallerBall2.getRadius() * 2)));
	smallerBall2.setFillColor(sf::Color::Yellow);
	biggerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + shape.getRadius()));
	biggerBall1.setPosition(-biggerBall1.getRadius()-90, rand() % (int)(windowHeight - ceil(biggerBall1.getRadius() * 2)));
	biggerBall1.setFillColor(sf::Color::Magenta);

	newCirclePos(shape2); // Goal for shape2

	if (!font.loadFromFile("badabb.ttf")) // Loading font 
	{
		// error
	}

	text.setString("Hits: 0");
	text.setFillColor(sf::Color::Green);
	text.setFont(font);

	while (window.isOpen()) { // Main loop for rendering

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
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
			if (pos.x + step <= ((float)windowWidth - shape.getRadius()*2)) {
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
			if (pos.y + step <= ((float)windowHeight - shape.getRadius()*2)) {
				newY = newY + step;
			}
			shape.setPosition(pos.x, newY);
		}

		// Movement for balls
		shape2.setPosition(stepCalcPos(shape2.getPosition().x, xBallPos, step), stepCalcPos(shape2.getPosition().y, yBallPos, step));
		if (shape2.getPosition().x == xBallPos && shape2.getPosition().y == yBallPos) {
			newCirclePos(shape2);
		}

		smallerBall1.setPosition(stepCalcPos(smallerBall1.getPosition().x, windowWidth+smallerBall1.getRadius(), ballSpeed), smallerBall1.getPosition().y);
		if (smallerBall1.getPosition().x >= windowWidth + smallerBall1.getRadius()) {
			smallerBall1.setPosition(-smallerBall1.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall1.getRadius() * 2)));
			smallerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
		}
		
		smallerBall2.setPosition(stepCalcPos(smallerBall2.getPosition().x, windowWidth + smallerBall2.getRadius(), ballSpeed), smallerBall2.getPosition().y);
		if (smallerBall2.getPosition().x >= windowWidth+smallerBall2.getRadius()) {
			smallerBall2.setPosition(-smallerBall2.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall2.getRadius() * 2)));
			smallerBall2.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
		}

		biggerBall1.setPosition(stepCalcPos(biggerBall1.getPosition().x, windowWidth + biggerBall1.getRadius(), ballSpeed), biggerBall1.getPosition().y);
		if (biggerBall1.getPosition().x >= windowWidth+biggerBall1.getRadius()) {
			biggerBall1.setPosition(-biggerBall1.getRadius(), rand() % (int)(windowHeight - ceil(biggerBall1.getRadius() * 2)));
			biggerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + shape.getRadius()));
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
		
		// collision between player and balls to increase and decrease player ball size
		if (pow((shape.getPosition().x + shape.getRadius()) - (smallerBall1.getPosition().x + smallerBall1.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (smallerBall1.getPosition().y + smallerBall1.getRadius()), 2) <= pow(shape.getRadius() + smallerBall1.getRadius(), 2)) {
			if (shape.getRadius() >= smallerBall1.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + smallerBall1.getRadius()/10);
				smallerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
				smallerBall1.setPosition(-smallerBall1.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall1.getRadius() * 2)));
			}
			else if (shape.getRadius() < smallerBall1.getRadius()) {
				shape.setRadius(shape.getRadius() - smallerBall1.getRadius() / 10);
				smallerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
				smallerBall1.setPosition(-smallerBall1.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall1.getRadius() * 2)));
			}
		}

		if (pow((shape.getPosition().x + shape.getRadius()) - (smallerBall2.getPosition().x + smallerBall2.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (smallerBall2.getPosition().y + smallerBall2.getRadius()), 2) <= pow(shape.getRadius() + smallerBall2.getRadius(), 2)) {
			if (shape.getRadius() >= smallerBall2.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + smallerBall2.getRadius() / 10);
				smallerBall2.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
				smallerBall2.setPosition(-smallerBall2.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall2.getRadius() * 2)));
			}
			else if (shape.getRadius() < smallerBall2.getRadius()) { 
				shape.setRadius(shape.getRadius() - smallerBall2.getRadius() / 10);
				smallerBall2.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + smallestRadius));
				smallerBall2.setPosition(-smallerBall2.getRadius(), rand() % (int)(windowHeight - ceil(smallerBall2.getRadius() * 2)));
			}
		}

		if (pow((shape.getPosition().x + shape.getRadius()) - (biggerBall1.getPosition().x + biggerBall1.getRadius()), 2) +
			pow((shape.getPosition().y + shape.getRadius()) - (biggerBall1.getPosition().y + biggerBall1.getRadius()), 2) <= pow(shape.getRadius() + biggerBall1.getRadius(), 2)) {
			if (shape.getRadius() >= biggerBall1.getRadius()) { // Eat it
				shape.setRadius(shape.getRadius() + biggerBall1.getRadius() / 10);
				biggerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + shape.getRadius()));
				biggerBall1.setPosition(-biggerBall1.getRadius(), rand() % (int)(windowHeight - ceil(biggerBall1.getRadius() * 2)));
			}
			else if (shape.getRadius() < biggerBall1.getRadius()) { 
				shape.setRadius(shape.getRadius() - biggerBall1.getRadius() / 10);
				biggerBall1.setRadius((rand() % (int)(shape.getRadius() - smallestRadius) + shape.getRadius()));
				biggerBall1.setPosition(-biggerBall1.getRadius(), rand() % (int)(windowHeight - ceil(biggerBall1.getRadius() * 2)));
			}
		}
		
		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.draw(smallerBall1);
		window.draw(smallerBall2);
		window.draw(biggerBall1);
		window.draw(text);
		window.display();
	}
}
