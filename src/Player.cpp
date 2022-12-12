#include <iostream>
#include <string>
#include <cmath>
#include "Projectile.h"
#include "Player.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//default constructor
Player::Player()
{
	//just initialize some stuff to 0
	speed = 0;
	fireSpeed = 0;
	bulletImg = nullptr;
	lives = 0;
}

//constructor
Player::Player(Texture &shipImage, Texture &bulletImage, float spd, float bulletSpd, int hp , bool boxBool, float yPos)
{
	Sprite shp; //create a sprite so you can set it up before using it to initialize the private data
	//set it up
	shp.setTexture(shipImage);
	shp.setPosition(Vector2f(400, yPos));
	//initialize stuff
	ship = shp;
	speed = spd;
	lives = hp;
	fireSpeed = bulletSpd;
	bulletImg = &bulletImage;
	maxLives = hp;
	//set the scale
	ship.setScale(Vector2f(2, 2));
	//more initializing
	hitBoxBool = boxBool;
	hitBox.setFillColor(Color(255, 255, 255, 200));
	hitBox.setSize(Vector2f(ship.getGlobalBounds().width / 2.5, ship.getGlobalBounds().width / 2.5));
	//this is a horrible line 'cause you have to center the hitbox on the sprite widthwise and heightwise
	hitBox.setPosition(ship.getPosition().x + (ship.getGlobalBounds().width/2) - (hitBox.getGlobalBounds().width/2), ship.getPosition().y + (ship.getGlobalBounds().height / 2) - (hitBox.getGlobalBounds().height / 2));
}

//returns the proper projectile to be fired
Projectile Player::shoot()
{
	return Projectile(1, *bulletImg, Vector2f(ship.getPosition().x + (ship.getGlobalBounds().width / 2) - (bulletImg->getSize().x / 2), ship.getPosition().y), 270, fireSpeed, NP_Entity::defaultSize);
}

//moves the player to the right
void Player::moveRight()
{
	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		ship.move(speed / 1.5, 0);
		hitBox.move(speed / 1.5, 0);
	}
	else
	{
		ship.move(speed, 0);
		hitBox.move(speed, 0);
	}
}

//move the player to the left
void Player::moveLeft()
{
	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		ship.move(-speed / 1.5, 0);
		hitBox.move(-speed / 1.5, 0);
	}
	else
	{
		ship.move(-speed, 0);
		hitBox.move(-speed, 0);
	}
}

//returns the bounds of the player
Rect<float> Player::getBounds()
{
	return ship.getGlobalBounds();
}

//decrement the players lives
void Player::decrementLives()
{
	lives--;
}

//deal specified damage to the player
void Player::damage(int dmg)
{
	lives -= dmg;
}

//check to see if the player has collided with provided NP_Entity
bool Player::checkCollision(NP_Entity &NP)
{
	bool hit = false;
	if (hitBoxBool == true && hitBox.getGlobalBounds().intersects(NP.getBounds())) //if the hitbox is on then check for that
	{
		hit = true;
	}
	else if (hitBoxBool == false && getBounds().intersects(NP.getBounds())) //otherwise just check if it collided with the player's sprite itself
	{
		hit = true;
	}
	return hit;
}

//draw the stuff
void Player::draw(RenderWindow &win)
{
	win.draw(ship);
	if (hitBoxBool == true) //if hit box is on then draw it
		win.draw(hitBox);
}

//returns the player's lives
int Player::getLife()
{
	return lives;
}

//reset the players lives to max
void Player::resetLife()
{
	lives = maxLives;
}

//returns the players position
Vector2f Player::getPos()
{
	return ship.getPosition();
}

//set the players x position
void Player::setPos(float x)
{
	ship.setPosition(Vector2f(x, ship.getPosition().y));
	hitBox.setPosition(ship.getPosition().x + (ship.getGlobalBounds().width / 2) - (hitBox.getGlobalBounds().width / 2), ship.getPosition().y + (ship.getGlobalBounds().height / 2) - (hitBox.getGlobalBounds().height / 2));
}