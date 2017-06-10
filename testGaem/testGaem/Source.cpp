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
	srand(time(NULL)); // S�tter seed f�r random (os�ker exakt hur funkar, copy/paste fr�n exempel)
	
	if (!font.loadFromFile("badabb.ttf")) // Loading font 
	{
		// error
	}

	// H�r kan man l�gga in n�n slags meny d�r man kan v�lja vilket spel som ska starta och sen bara skicka med window till den

	// Ball Game
	BallGame bg = BallGame(&window, windowWidth, windowHeight, font);
}
	

	

