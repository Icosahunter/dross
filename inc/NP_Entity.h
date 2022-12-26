#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum hitBoxType{DEFAULT, BOTTOM};

class NP_Entity
{

private:

	Sprite entity; //the entities sprite
	float direction = 0; //the entities direction
	float speed = 1; //the entities speed
	RectangleShape hitBox;

public:
	static const int defaultSize = -1;
	NP_Entity(Texture &image, Vector2f pos, float dir, float spd, int size, hitBoxType boxType, int hitBoxSize);
	~NP_Entity();
	void move();
	void draw(RenderWindow &win);
	static bool checkCollision(NP_Entity &NP1, NP_Entity &NP2);
	Rect<float> getBounds();
	Vector2f getPos();
	float getDir();
	Rect<float> getHitBox();
};