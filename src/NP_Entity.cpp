#include <iostream>
#include <list>
#include <cmath>
#include <string>
#include "NP_Entity.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//return the direction of the entity
float NP_Entity::getDir()
{
	return direction;
}

//return the position of the entity
Vector2f NP_Entity::getPos()
{
	return entity.getPosition();
}

//Constructor
NP_Entity::NP_Entity(Texture &image, Vector2f pos, float dir, float spd, int size, hitBoxType boxType, int hitBoxSize)
{
	//you need this so you can set it up with the argument data before initializing the private data with it
	Sprite ent;
	//set up the entity
	ent.setPosition(pos);
	ent.setTexture(image);
	if (size > defaultSize) //if you aren't stickin' with default size, then set the size appropriately
		ent.setScale(Vector2f(static_cast<float>(size) / image.getSize().x, static_cast<float>(size) / image.getSize().x));

	//initialize the private data
	entity = ent;
	direction = dir;
	speed = spd;
	if (boxType == DEFAULT)
	{
		hitBox.setPosition(entity.getPosition());
		hitBox.setSize(Vector2f(ent.getGlobalBounds().width, ent.getGlobalBounds().height));
	}
	else if (boxType == BOTTOM)
	{
		hitBox.setSize(Vector2f(entity.getGlobalBounds().width, entity.getGlobalBounds().height*(hitBoxSize/100)));
		hitBox.setPosition(Vector2f(entity.getPosition().x, entity.getPosition().y + entity.getGlobalBounds().height*(1-(hitBoxSize/100))));
	}
}

NP_Entity::~NP_Entity()
{
	//nothin' here... yet.
}

//calculate the x and y movement based on speed and direction and then move the entity accordingly
void NP_Entity::move()
{
	entity.move(speed*cos((3.1415/180)*direction), speed*sin((3.1415 / 180)*direction));
	hitBox.move(speed*cos((3.1415 / 180)*direction), speed*sin((3.1415 / 180)*direction));
}

//check to see if two entities have collided
bool NP_Entity::checkCollision(NP_Entity &NP1, NP_Entity &NP2)
{
	bool val = false;
	if (NP1.hitBox.getGlobalBounds().intersects(NP2.hitBox.getGlobalBounds()))
	{
		val = true;
	}
	return val;
}

//draw the entity to the provided RenderWindow
void NP_Entity::draw(RenderWindow &win)
{
	win.draw(entity);
}

//returns the global bounds of the entity
Rect<float> NP_Entity::getBounds()
{
	return entity.getGlobalBounds();
}

Rect<float> NP_Entity::getHitBox()
{
	return hitBox.getGlobalBounds();
}