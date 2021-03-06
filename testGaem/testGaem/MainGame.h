#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class MainGame {
	public:
		MainGame(sf::RenderWindow * window, int windowWidth, int windowHeight, sf::Font font);
		void initStart();
		void renderingMethod();
		~MainGame();
	private:
		sf::RenderWindow* window;
		int windowWidth;
		int windowHeight;
		sf::Text text;
		sf::Font font;
		sf::CircleShape shape;
		sf::Vector2f startPos;
		float startSize; 
		float step;
};