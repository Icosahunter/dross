#pragma once
#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Display.h"
#include <string>
#include <list>
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum GameState{MENU, LEVEL, PAUSE, TRANSITION, WIN, LOSE};

class Game
{

private:

	int killCount = 0; //the number of total kills this game (resets if you lose the game though)
	Player player; //the player
	vector<levelData> levels; //the data for all the levels
	Level currentLevel; //the current level
	int lvlCounter; //the current level number
	RenderWindow* win; //the window to draw to
	Display screen; //this is reused for the pause, win, lose, transition, and menu screens
	GameState state; //the state of the game, playing a level, paused, on the menu, etc.
	Text kills; //the number of kills on the current level is displayed with this
	Text lives; //the current number of lives is displayed with this
	Text level; //the current level number is displayed with this
	bool space; //whether or not the space bar was pressed (resets when you release it)
	bool click; //whether or not the left mouse button has been clicked (resets when you release it)
	RectangleShape bar; //the top bar of the screen (not really necessary since I changed the background, but would be necessary for some backgrounds)

public:
	Game(RenderWindow &win, Player &plyr, Color clr, Font &font); //constructor
	~Game(); //default constructor
	void loadLevel(int lvlNum); //load a level from the que
	void addLevel(levelData lvl); //add a level using a levelData
	void updateLevel(); //update the current level
	void update(); //update the entire game (updating the games state, drawing things, etc.)
	void moveShip(); //move the ship if the user presses the right keys
	void fireShip(); //fire the ship if the user presses the right buttons
	void loseScreen();//setup / update the lose screen
	void winScreen(); //setup / update the win screen
	void menuScreen(); //setup / update the menu screen
	void pause(); //setup / update the pause screen
	void nextLevel(); //load the next level
	void transition(); //set up / update the transition screen
	GameState getState(); //returns the state of the game
	void start(); //set up / reset the game
	void updateTextPos(); //reposition text
	void restartLevel(); //restart the level
	void resetShipPos(); //reset the ships position (to middle of screen)
};