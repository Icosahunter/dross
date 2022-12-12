#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "NP_Entity.h"
#include "Projectile.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum FirePattern{STRAIGHT, SPREAD, SHEET};

class Enemy: public NP_Entity
{
private:

	int lives; //then enemies lives
	float fireSpeed; //the enemies bullet speed
	int bulletDmg; //the bullet's damage
	Texture *bulletImg; //the bullets texture
	FirePattern pattern;
	 
public:

	//the constructor
	Enemy(Texture &image, Vector2f pos, float dir, float spd, float fireSpd, int fireDmg, Texture &fireImg, int lvs, int size, FirePattern firePat) : NP_Entity(image, pos, dir, spd, size, hitBoxType(DEFAULT), 0)
	{
		lives = lvs;
		fireSpeed = fireSpd;
		bulletDmg = fireDmg;
		bulletImg = &fireImg;
		pattern = firePat;
	}
	vector<Projectile> fire(); //returns the projectile the enemy "fired"
	void decrementLife(); //decrement the enemies life
	int getLife(); //returns the enemies current lives
	void damage(int dmg); //damage the enemy by the specified amount
};