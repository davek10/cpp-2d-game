#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Bullet.h"
#include <ctime>

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
		std::vector<Bullet> bullets;
		clock_t reload;
		float startSize; 
		float step;
		sf::Vertex shotLine[];
};