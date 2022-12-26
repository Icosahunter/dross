#include <iostream>
#include <list>
#include <string>
#include <ctime>
#include <math.h>
#include "Enemy.h"
#include "Projectile.h"
#include "Level.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//this allows you to create a lvlData all in one line (without setting each piece of data seperately)
levelData Level::lvlData(int enemyCol, int enemyRow, float fireFreq, float fireSpeed, int enemyDmg, float enemySpeed, int enemyLives, Texture &enemyImg, Texture &bulletImg, int enemSze, FirePattern pattern, RenderWindow& window)
{
	levelData l;
	l.enemyCol = enemyCol;
	l.enemyRow = enemyRow;
	l.fireFreq = fireFreq;
	l.fireSpeed = fireSpeed;
	l.enemyDmg = enemyDmg;
	l.enemySpeed = enemySpeed;
	l.enemyLives = enemyLives;
	l.enemyImg = &enemyImg;
	l.bulletImg = &bulletImg;
	l.window = &window;
	l.enemySize = enemSze;
	l.pattern = pattern;
	return l;
}

//build a level from a level data
Level::Level(levelData l)
{
	time = 0;
	state = PLAYING;
	win = l.window;
	fireTime = l.fireFreq;
	enemySize = l.enemySize;
	pushEnemies(l.enemyRow, l.enemyCol, l.enemySpeed, l.fireSpeed, l.enemyDmg, *l.enemyImg, *l.bulletImg, l.enemyLives, l.enemySize, l.pattern);
}

//default constructor
Level::Level() { state = PLAYING; }

Level::~Level()
{
	//nothin' here... yet
}

//level overloaded = operator
Level Level::operator=(Level &lvl)
{
	//set the stuff equal to the stuff
	time = 0;
	fireTime = lvl.fireTime;
	enemies = lvl.enemies;
	enemyFire = lvl.enemyFire;
	playerFire = lvl.playerFire;
	enemySize = lvl.enemySize;
	win = lvl.win;
	state = lvl.state;
	return *this;
}

//copy constructor
Level::Level(Level &lvl)
{
	//same deal as the overloaded =, just set all the stuff equal to the stuff
	time = 0;
	fireTime = lvl.fireTime;
	enemies = lvl.enemies;
	enemyFire = lvl.enemyFire;
	playerFire = lvl.playerFire;
	enemySize = lvl.enemySize;
	win = lvl.win;
	state = lvl.state;
}

//constructor, I know... its gotta lotta arguments.
Level::Level(int enemyCol, int enemyRow, float fireFreq, float fireSpeed, int enemyDmg, float enemySpeed, int enemyLives, Texture &enemyImg, Texture &bulletImg, int enemSze, FirePattern pattern, RenderWindow &window)
{
	//default stuff
	time = 0;
	state = PLAYING;

	//set some of the stuff equal to the provided values
	win = &window;
	fireTime = fireFreq;
	Sprite temp;
	temp.setTexture(enemyImg);
	enemySize = enemSze;

	//oh boi, gotta set up ALL the enemies
	pushEnemies(enemyRow, enemyCol, enemySpeed, fireSpeed, enemyDmg, enemyImg, bulletImg, enemyLives, enemSze, pattern);
}

//sets up the level using a levelData
void Level::loadFromData(levelData l)
{
	time = 0;
	state = PLAYING;
	win = l.window;
	enemies.clear();
	enemyFire.clear();
	playerFire.clear();
	fireTime = l.fireFreq;
	enemySize = l.enemySize;
	pushEnemies(l.enemyRow, l.enemyCol, l.enemySpeed, l.fireSpeed, l.enemyDmg, *l.enemyImg, *l.bulletImg, l.enemyLives, l.enemySize, l.pattern);
}

//set up all the enemies
void Level::pushEnemies(int row, int col, float enemySpeed, float fireSpeed, int enemyDmg, Texture& enemyImg, Texture& bulletImg, int enemyLives, int enemySize, FirePattern pattern)
{
	Sprite temp; //used to figure out the size of the enemies
	temp.setTexture(enemyImg);
	if (enemySize > -1)
		temp.setScale(Vector2f(enemySize / enemyImg.getSize().x, enemySize / enemyImg.getSize().x));

	//cycle throught i and j for rows and columns, these will be used to calculate the enemies position
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//use all the info provided in the arguments of this function to create an enemy and slap it in the list
			enemies.push_back(Enemy(enemyImg, Vector2f(j*(win->getSize().x / col) + (win->getSize().x / col / 2) - (temp.getGlobalBounds().width / 2), i * 80 - temp.getGlobalBounds().height + 20), 90, enemySpeed, fireSpeed, enemyDmg, bulletImg, enemyLives, enemySize, pattern));
		}
	}
}

//move ALL the enemies and projectiles appropriately
void Level::moveAll()
{
	list<Enemy>::iterator enemyIter; //enemy iterator
	list<Projectile>::iterator projIter; //projectile iterator

	//go through all the enemies and move them
		for (enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
		{
			enemyIter->move();
		}
	//go through all the enemy bullets and move them
		for (projIter = enemyFire.begin(); projIter != enemyFire.end(); projIter++)
		{
			projIter->move();
		}
	//go through all the player bullets and move them
		for (projIter = playerFire.begin(); projIter != playerFire.end(); projIter++)
		{
			projIter->move();
		}
}

//select an enemy and shoot
void Level::fireEnemies()
{
	list<Enemy>::iterator enemyIter; //enemy iterator
	vector<Projectile> p;
	int i = 0;
	int random = rand();
	for (enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++) //go through all the enemies
	{
		if (random % enemies.size() == i && time == floor(fireTime/enemies.size())) //if the the enemy has been selected and the time is ripe
		{
			p = enemyIter->fire();
			for (int j = 0; j < p.size(); j++)
				enemyFire.push_back(p[j]); //fire!
		}
		i++;
	}

	//if you've reached the time to shoot, reset the shoot timer
	if (time != floor(fireTime/(enemies.size())))
		time++;
	else
		time = 0;
}

//draw everything
void Level::draw()
{
	list<Enemy>::iterator enemyIter; //enemy iterator
	list<Projectile>::iterator projIter; //projectile iterator

	//go through all the enemies and draw them
		for (enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++)
		{
			enemyIter->draw(*win);
		}
	//go through all the enemy projectiles and draw them
		for (projIter = enemyFire.begin(); projIter != enemyFire.end(); projIter++)
		{
			projIter->draw(*win);
		}
	//go through all the player projectiles and draw them
		for (projIter = playerFire.begin(); projIter != playerFire.end(); projIter++)
		{
			projIter->draw(*win);
		}
}

//update the level, this does all the stuff necessary per frame to operate the level
void Level::update(Player &ship)
{
	if (allEnemiesGone()) //if the enemies are all gone, ya done won
		state = WON;
	else
	{   //otherwise update all the stuff
		moveAll();
		fireEnemies();
		checkForEnemyKills();
		checkForEntOutOfBounds(ship);
	}
	draw(); //draw all the stuff
}

// check to see if any of the enemies have been shot
void Level::checkForEnemyKills()
{
	list<Enemy>::iterator enemIter; //enemy iterator
	list<Projectile>::iterator projIter; //projectile iterator
	for (enemIter = enemies.begin(); enemIter != enemies.end(); ) //go through all the enemies
	{
		for (projIter = playerFire.begin(); projIter != playerFire.end(); ) //go through all the players missiles
		{
			if (NP_Entity::checkCollision(*enemIter, *projIter)) //check to see if the missile uder inspection has hit the enemy under inspection
			{
				enemIter->damage(projIter->getDamage()); //the enemy gets hurt
				projIter = playerFire.erase(projIter); //get ridda that missile
			}
			else
				projIter++;
		}
		if (enemIter->getLife() == 0) //if the enemies life is 0
		{
			enemIter = enemies.erase(enemIter); //get ridda that enemy
			killCount++; //increment kill count
		}
		else
			enemIter++;
	}
}

//check to see if enemy or bullets are out of bounds
void Level::checkForEntOutOfBounds(Player &ship)
{
	list<Enemy>::iterator enemyIter; //enemy iterator
	list<Projectile>::iterator projIter; //projectile iterator
	Rect<float> screen(Vector2f(0, 0), Vector2f(win->getSize()));

		for (enemyIter = enemies.begin(); enemyIter != enemies.end(); enemyIter++) //go through all the enemies
		{
			//if the enemy under inspection is out of bounds, AND the ship still has lives, and the level isn't currently flagged to RESET
			if ((enemyIter->getPos().y + enemyIter->getBounds().height) > ship.getPos().y && ship.getLife() > 0 && state != RESET)
			{
				state = RESET; //set the state to RESET
				ship.decrementLives(); //decrement the ships lives
			}
		}
		
		for (projIter = enemyFire.begin(); projIter != enemyFire.end();) //go through all the enemy missiles
		{
			//if the missile is out of bounds
			if (!screen.contains(projIter->getPos()))
			{
				projIter = enemyFire.erase(projIter); //get ridda that missile
			}
			else
				projIter++;
		}

		for (projIter = playerFire.begin(); projIter != playerFire.end();) //go through all the player missiles
		{
			//if the missile is out of bounds
			if (!screen.contains(projIter->getPos()))
			{
				projIter = playerFire.erase(projIter); //get ridda that missile
			}
			else
				projIter++;
		}
}

//add a projectile to the player missile list
void Level::addPlayerShot(Projectile p)
{
	playerFire.push_back(p);
}

// check if all the enemies are gone
bool Level::allEnemiesGone()
{
	bool val = false;
	if (enemies.size() == 0)
		val = true;
	return val;
}

//check to see if the ship has been hit and update stuff appropriately
void Level::checkForShipHit(Player& ship)
{
	list<Enemy>::iterator enemyIter; //enemy iterator
	list<Projectile>::iterator projIter; //projectile iterator

	for (projIter = enemyFire.begin(); projIter != enemyFire.end(); ) //go through all the enemy projectiles
	{
		//if the ship is hit, and the ship has lives, and the level is not flagged to RESET
		if (ship.checkCollision(*projIter) && ship.getLife() > 0 && ship.getLife() > 0 && state != RESET)
		{
			ship.damage(projIter->getDamage()); //damage the ship
			projIter = enemyFire.erase(projIter); //get ridda that missile
			state = RESET; //set the state to RESET
		}
		else
			projIter++;
		if (ship.getLife() == 0) //if the ship is dead
		{
			state = LOST; //ya lose buddy
		}
	}
}

//return the level's state
WinState Level::getState()
{
	return state;
}

//return kill count
int Level::getKills()
{
	return killCount;
}

//set the kill count to 0
void Level::resetKills()
{
	killCount = 0;
}