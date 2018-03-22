#include "MainGame.h"

MainGame::MainGame(sf::RenderWindow * window, int windowWidth, int windowHeight, sf::Font font)
{
	window->setVerticalSyncEnabled(true);
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->font = font;

	initStart();
}

void MainGame::initStart() {
	step = 2.f;
	startSize = 50.f;
	startPos = sf::Vector2f(windowWidth / 2 - startSize, windowHeight / 2 - startSize);
	
	shape.setRadius(50.f);
	shape.setPosition(startPos);
	shape.setFillColor(sf::Color::White);

	text.setString(sf::String("Hello")); // Example		sf::String("Hits: ") + std::to_string(hits) + sf::String(". Goal: ")
	text.setFillColor(sf::Color::Green);
	text.setFont(font);
	text.setPosition(10, 0);

	renderingMethod();
}

void MainGame::renderingMethod() {
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

		window->clear();
		window->draw(shape);
		window->draw(text);
		window->display();
	}
}


MainGame::~MainGame()
{
}

