#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <iostream>
#include "BallGame.h"
using namespace std;

// 640 x 480
int windowWidth = 1024;
int windowHeight = 768;
sf::Font font;

int main() {
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Application"); // Init rendering window
	srand(time(NULL)); // Sätter seed för random (osäker exakt hur funkar, copy/paste från exempel)
	
	if (!font.loadFromFile("badabb.ttf")) // Loading font 
	{
		// error
	}

	// Här kan man lägga in nån slags meny där man kan välja vilket spel som ska starta och sen bara skicka med window till den

	// Ball Game
	BallGame bg = BallGame(&window, windowWidth, windowHeight, font);
}
	

	

