#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

struct levelData
{
	int enemyCol; //number of columns of enemies
	int enemyRow; //number of rows of enemies
	float fireFreq; //the fire rate of enemies
	float fireSpeed; //the speed of bullets of enemies
	int enemyDmg; //the damage of enemies
	float enemySpeed; //the speed of enemies
	int enemyLives; //the number of lives per enemy
	Texture* enemyImg; //the enemy texture
	Texture* bulletImg; //the enemy bullet texture
	RenderWindow* window; //the window to draw to
	int enemySize; //the size of the enemy
	FirePattern pattern; //enemy bullet pattern
};

enum WinState {WON, LOST, PLAYING, RESET};

class Level
{

private:

	int killCount = 0; //the number of kills so far on this level
 	list<Enemy> enemies; //the enemies
	list<Projectile> enemyFire, playerFire; //the enemy and player missiles
	RenderWindow* win; //the window to draw to
	WinState state; //the state of the level
	int time = 0; //this is used for firing frequency, it cycles through a provided nu ber, and fires when it reaches the max, before resetting
	int fireTime = 0; //the max value for time
	int enemySize = 1; //the size of the enemies

public:
	Level(); //default constructor
	//constructor
	Level(int enemyCol, int enemyRow, float fireFreq, float fireSpeed, int enemyDmg, float enemySpeed, int enemyLives, Texture &enemyImg, Texture &bulletImg, int enemSze, FirePattern pattern, RenderWindow& window);
	Level(levelData l); //constructor using level data
	Level(Level &l); //copy constructor
	Level operator =(Level &lvl); //overloaded equals operator
	~Level(); //destructor
	void draw(); //draw everything to the render window
	void moveAll(); //move all the projectiles and enemies
	void checkForEnemyKills(); //check to see if any enemies got shot and damage them appropriately
	void update(Player &ship); //update the level (draw, check for dead enemies, move, etc.)
	void fireEnemies(); //loop through and fire the proper enemies
	void checkForEntOutOfBounds(Player &ship); //check for entities out of bounds
	void addPlayerShot(Projectile p); //add the provided projectile to the player fire list
	bool allEnemiesGone(); //returns true if all enemies are dead
	//set up a level data struct
	static levelData lvlData(int enemyCol, int enemyRow, float fireFreq, float fireSpeed, int enemyDmg, float enemySpeed, int enemyLives, Texture &enemyImg, Texture &bulletImg, int enemSze, FirePattern pattern, RenderWindow& window);
	void checkForShipHit(Player& ship); //check to see if the provided player was hit and damage it appropriately
	void loadFromData(levelData l); //set all the stuff in the level to the stats provided in the levelData
	WinState getState(); //returns the state of the level
	int getKills(); //returns the kills so far this level
	void resetKills(); //reset the kill number (to 0)
	//generate all the enemies and add them to the list using the provided data
	void pushEnemies(int row, int col, float enemySpeed, float fireSpeed, int enemyDmg, Texture& enemyImg, Texture& bulletImg, int enemyLives, int enemySize, FirePattern pattern);
};