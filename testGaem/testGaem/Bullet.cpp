#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startpos, sf::Vector2f targetpos, float size, float speed)
{
	pos = startpos;
	bullet_sprite.setPosition(pos);
	bullet_sprite.setRadius(size);
	bullet_sprite.setFillColor(sf::Color::White);
	float xdist = targetpos.x - startpos.x;
	float ydist = targetpos.y - startpos.y;
	velocity = (targetpos - startpos) / sqrt(xdist*xdist + ydist*ydist) * speed;
}

Bullet::~Bullet()
{

}

void Bullet::update() {
	pos += velocity;
	bullet_sprite.setPosition(pos);
}

sf::Vector2f Bullet::getCenterPos()
{
	//sf::Vector2f align = sf::Vector2f(bullet_sprite.getRadius, bullet_sprite.getRadius);
	return pos;//+align;
}

const sf::CircleShape& Bullet::getSprite()
{
	return bullet_sprite;
}

