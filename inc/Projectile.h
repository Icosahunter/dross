#pragma once
#include <iostream>
#include <string>
#include "NP_Entity.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Projectile: public NP_Entity
{

private:

	int damage = 1; //the projectiles damage

public:

	//constructor
	Projectile(int dmg, Texture &image, Vector2f pos, float dir, float spd, int size, hitBoxType boxType, int hitBoxSize) : NP_Entity(image, pos, dir, spd, size, boxType, hitBoxSize)
	{
		damage = dmg;
	}

	Projectile(int dmg, Texture &image, Vector2f pos, float dir, float spd, int size) : NP_Entity(image, pos, dir, spd, size, hitBoxType(DEFAULT), 0)
	{
		damage = dmg;
	}

	int getDamage();

};