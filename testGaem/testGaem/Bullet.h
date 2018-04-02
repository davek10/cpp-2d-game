#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

/*
	Class for bullet projectiles in the game
	Should make use of polymorphism so that different type of projectiles use the same class so
	that only one container is needed to update all projectiles
*/
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
	sf::CircleShape bullet_sprite; //replace with real sprite later
};

class NormalBullet : public Bullet 
{
public:
	NormalBullet(sf::Vector2f startpos, sf::Vector2f targetpos, float size, float speed) 
		: Bullet(startpos, targetpos, size, speed) {}
};

