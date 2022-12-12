#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include "Enemy.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//"fire" a bullets (returns the bullet to be "fired")
vector<Projectile> Enemy::fire()
{
	vector<Projectile> p;
	float boundX = getBounds().width, boundY = getBounds().height;
	int boundInt = boundX;
	float b = getBounds().width;

	//if the enemy is big then randomize the position of the bullet along the front of the enemy
	if (pattern == STRAIGHT)
	{
		if (getBounds().width > 60)
			p.push_back(Projectile(bulletDmg, *bulletImg, Vector2f(getPos().x + (boundX / 2) - (bulletImg->getSize().x / 2) + (rand() % boundInt - boundInt / 2), getPos().y + boundY - 20), getDir(), fireSpeed, NP_Entity::defaultSize, hitBoxType(BOTTOM), 50));
		else
			//otherwise just fire from the center
			p.push_back(Projectile(bulletDmg, *bulletImg, Vector2f(getPos().x + (boundX / 2) - (bulletImg->getSize().x / 2), getPos().y + boundY - 20), getDir(), fireSpeed, NP_Entity::defaultSize, hitBoxType(BOTTOM), 50));
	}
	else if (pattern == SPREAD)
	{
		float num = getBounds().width / 20;
		float angle = 35;
		for (int i = 0; i <= num; i++)
		{
			p.push_back(Projectile(bulletDmg, *bulletImg, Vector2f(getPos().x - (bulletImg->getSize().x / 2) + i*(getBounds().width/num), getPos().y + boundY - 20), getDir() - angle + (i*angle*2)/num, fireSpeed, NP_Entity::defaultSize, hitBoxType(BOTTOM), 50));
		}
	}
	return p;
}

//die already!
void Enemy::decrementLife()
{
	lives--;
}

//deal specified damage to the enemy
void Enemy::damage(int dmg)
{
	lives -= dmg;
}

//return the lives of the enemy
int Enemy::getLife()
{
	return lives;
}