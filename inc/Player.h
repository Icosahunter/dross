#pragma once
#include <iostream>
#include <string>
#include "Projectile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{

private:

	Sprite ship; //the players sprite
	float speed = 1; //the players speed
	float fireSpeed = 1; //the players bullet speed
	int maxLives = 5; //the max lives of the player
	int lives = 5; //the current lives of the player
	Texture *shipImg; //the players texture
	Texture *bulletImg; //the player's bullet texture
	RenderWindow* win; //the window to draw to
	RectangleShape hitBox; //the players hit box
	bool hitBoxBool = true; //set to true to use the special hit box, false uses the player's sprites bounding box as the hit box

public:

	Player();
	Player(Texture &shipImage, Texture &bulletImg, float speed, float bulletSpd, int lives, bool boxBool, float yPos);
	Projectile shoot();
	void moveRight();
	void moveLeft();
	Rect<float> getBounds();
	void decrementLives();
	bool checkCollision(NP_Entity &NP);
	void draw(RenderWindow &win);
	int getLife();
	void resetLife();
	Vector2f getPos();
	void setPos(float x);
	void damage(int dmg);
};