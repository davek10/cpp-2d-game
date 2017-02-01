#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
using namespace std;
int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Red);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sf::Vector2f pos = shape.getPosition();
			float newX = pos.x;
			if (pos.x - 1 >= 0) {
				newX--;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sf::Vector2f pos = shape.getPosition();
			float newX = pos.x;
			if (pos.x + 1.0 <= (640.0-shape.getRadius()*2)) {
				newX++;
			}
			shape.setPosition(newX, pos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f pos = shape.getPosition();
			float newY = pos.y;
			if (pos.y - 1 >= 0) {
				newY--;
			}
			shape.setPosition(pos.x, newY);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			// left key is pressed: move our character
			sf::Vector2f pos = shape.getPosition();
			float newY = pos.y;
			if (pos.y + 1 <= (480-shape.getRadius()*2)) {
				newY++;
			}
			shape.setPosition(pos.x, newY);
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

}