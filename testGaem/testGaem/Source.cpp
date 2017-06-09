#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
using namespace std;

int windowWidth = 640;
int windowHeight = 480;
sf::CircleShape shape;
sf::CircleShape shape2;
float xBallPos;
float yBallPos;

sf::Text text;
sf::Font font;
sf::String hitText = "Hits: ";
int hits = 0;

void newCirclePos(sf::CircleShape shape) {
	xBallPos = rand() % (int)(windowWidth - ceil(shape.getRadius()*2));
	yBallPos = rand() % (int)(windowHeight - ceil(shape.getRadius()*2));
}

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
	srand(time(NULL)); // Sätter seed för random (osäker exakt hur funkar, copy/paste från exempel)
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Application");

	// Could be moved to a movement class once threads are read up on.
	shape.setRadius(25.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Red);
	shape2.setRadius(10.f);
	shape.setPosition(200.f, 200.f);
	shape.setFillColor(sf::Color::Blue);
	float step = 0.05;
	newCirclePos(shape2);

	if (!font.loadFromFile("badabb.ttf"))
	{
		std::printf("memes");
		// error
	}

	text.setString("Hits: 0");
	text.setFillColor(sf::Color::Green);
	text.setFont(font);

	while (window.isOpen()) {

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

		// Movement for small ball
		shape2.setPosition(stepCalcPos(shape2.getPosition().x, xBallPos, step), stepCalcPos(shape2.getPosition().y, yBallPos, step));
		if (shape2.getPosition().x == xBallPos && shape2.getPosition().y == yBallPos) {
			newCirclePos(shape2);
		}
		
		// Collision between the 2 balls
		if (pow((shape.getPosition().x + shape.getRadius()) - (shape2.getPosition().x + shape2.getRadius()), 2) + 
			pow((shape.getPosition().y + shape.getRadius()) - (shape2.getPosition().y + shape2.getRadius()), 2) <= pow(shape.getRadius() + shape2.getRadius(), 2)) {
			hits++;
			sf::String str = "Hits: " + std::to_string(hits);
			text.setString(str);
			if (shape.getRadius() >= shape2.getRadius()) { // Eat it
				sf::Vector2f newPos = sf::Vector2f(rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)), rand() % (int)(windowWidth - ceil(shape.getRadius() * 2)));
				shape2.setPosition(newPos);
			}
		}
		
		window.clear();
		window.draw(shape);
		window.draw(shape2);
		window.draw(text);
		window.display();
	}
}
