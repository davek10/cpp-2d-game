#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
class Bullet
{
public:
	Bullet(sf::Vector2f startpos, sf::Vector2f targetpos, float size, float speed);
	~Bullet();
	void update();
	sf::Vector2f getCenterPos();
	const sf::CircleShape& getSprite();
private:
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::CircleShape bullet_sprite;
};

