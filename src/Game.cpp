#include <iostream>
#include "Level.h"
#include "Player.h"
#include "Game.h"
#include "Display.h"
#include <string>
#include <list>
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//the constructor
//window: the render window to draw to
//plyr: the player
//clr: the color of the text
//font: the font
Game::Game(RenderWindow &window, Player &plyr, Color clr, Font &font)
{
	space = 0;
	click = 0;
	state = MENU;
	lvlCounter = 0;
	player = plyr;
	win = &window;

	//set up the screen (the screen is used for transitions, pause screen, menu, win screen, and lose screen)
	screen.setWin(window);
	screen.setFont(font);
	screen.setColor(clr);

	//set up kill count text
	kills.setString(to_string(killCount));
	kills.setFont(font);
	kills.setFillColor(clr);
	kills.setCharacterSize(30);

	//set up life count text
	lives.setString(to_string(player.getLife()));
	lives.setFont(font);
	lives.setFillColor(clr);
	lives.setCharacterSize(30);

	//set up level count text
	level.setString(to_string(lvlCounter));
	level.setFont(font);
	level.setFillColor(clr);
	level.setCharacterSize(30);

	//set the text pos to their proper place
	updateTextPos();

	//set up the top bar
	bar.setFillColor(Color::Black);
	bar.setSize(Vector2f(win->getSize().x, 60));
	bar.setPosition(Vector2f(0, 0));

	//by default make the screen type button
	screen.setType(BUTTON);
}

Game::~Game()
{
	//nothin' here... yet
}

//add a level to the game, levels are played in the order they are added
void Game::addLevel(levelData lvl)
{
	levels.push_back(lvl);
}

//reset the ship pos to center of screen
void Game::resetShipPos()
{
	player.setPos((win->getSize().x + player.getBounds().width) / 2);
}

//this updates all necessary things for running the game, it should be called every frame
void Game::updateLevel()
 {
	currentLevel.checkForShipHit(player); // check to see if the player was hit, if so do the proper stuff
	currentLevel.update(player); //update the players stuff
	moveShip(); //move the player if movement keys pressed
	player.draw(*win); //draw the player
	fireShip(); //have the player shoot if space/mouse pressed
	kills.setString("Kills: " + to_string(currentLevel.getKills())); //update the kills text
	lives.setString("Lives: " + to_string(player.getLife())); //update the life count text 
	level.setString("Level: " + to_string(lvlCounter + 1)); //update the level count text
	updateTextPos(); //update the kill count, life count, and level count, positions

	//draw more stuff
	win->draw(bar);
	win->draw(level);
	win->draw(kills);
	win->draw(lives);
}

//put the kill count, life count, and level count text where they should go
void Game::updateTextPos()
{
	float buffer = 10; // the buffer between the text and the screen edge
	kills.setPosition(Vector2f(buffer, buffer));
	lives.setPosition(Vector2f(win->getSize().x - lives.getLocalBounds().width - buffer, buffer));
	level.setPosition(Vector2f((win->getSize().x - level.getLocalBounds().width)/2, buffer));
}

//if the space or left mouse is pressed, fire a bullet from the space ship
void Game::fireShip()
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) //if space pressed
		space = 1; //store that it happened
	if (Mouse::isButtonPressed(Mouse::Button::Left)) //if mouse pressed
		click = 1; //store that it happened
	if ((!Keyboard::isKeyPressed(Keyboard::Space) && space == 1) || (!Mouse::isButtonPressed(Mouse::Button::Left) && click == 1)) //if space or mouse released
	{
		//reset the space and left mouse bools
		space = 0;
		click = 0;
		//fire the shot
		currentLevel.addPlayerShot(player.shoot());
	}
}

//load a level from the que
void Game::loadLevel(int lvlNum)
{
	currentLevel.loadFromData(levels[lvlNum]);
}

//restart the current level
void Game::restartLevel()
{
	loadLevel(lvlCounter); //reload the level
	resetShipPos(); //reset the ships pos
}

//move the player if the movement keys are pressed
void Game::moveShip()
{
	if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && !(player.getPos().x < 0)) //if the left arrow, or A key are pressed, AND the player is not at the left edge of the screen
	{
		player.moveLeft(); //move the player left
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && !(player.getPos().x + player.getBounds().width > win->getSize().x)) //if the right arrow, or D key is pressed, AND the player is not at the right edge of the screen
	{
		player.moveRight(); //move the player right
	}
}

//load up the next level
void Game::nextLevel()
{
	player.resetLife(); //reset the players lives (fresh start!)
	loadLevel(++lvlCounter); //increment the level counter and load up that level
}

//calling this function sets up the instance of Display stored in game as a level transition screen
void Game::transition()
{
	screen.setTitle("Level " + to_string(lvlCounter + 1) + " Completed");
	screen.setText("Kills [ This LVL: " + to_string(currentLevel.getKills()) + ", Total: " + to_string(killCount) + " ]");
	screen.setType(ENTER);
	screen.update();
}

//calling this function sets up the instance of Display stored in game as a lose screen
void Game::loseScreen()
{
	screen.setTitle("YOU LOSE");
	screen.setText("LVLs completed: " + to_string(lvlCounter) + "  Total kills: " + to_string(killCount));
	screen.setType(BUTTON);
	screen.update();
}

//calling this function sets up the instance of Display stored in game as a win screen
void Game::winScreen()
{
	screen.setTitle("YOU WIN");
	screen.setText("Total kills: " + to_string(killCount));
	screen.setType(BUTTON);
	screen.update();
}

//calling this function sets up the instance of Display stored in game as a menu screen
void Game::menuScreen()
{
	screen.setTitle("THE GAME");
	screen.setText("by Nathaniel Markham");
	screen.setType(BUTTON);
	screen.update();
}

//calling this function sets up the instance of Display stored in game as a pause screen
void Game::pause()
{
	screen.setTitle("PAUSED");
	screen.setText("");
	screen.setType(ENTER);
	screen.update();
}

//returns the state of the game
GameState Game::getState()
{
	return state;
}

//set up the game to start
void Game::start()
{
	player.resetLife(); //reset the players lives
	killCount = 0; //reset the kill count
	lvlCounter = 0; //set the level counter to 0 (1st level)
	loadLevel(lvlCounter);  //load the first level
}

//this function does different things depending on the state of the game
//if the level is playing it does all the update stuff to run that, if the
//menu screen is should be displayed it does all the update stuff for that
//it also checks the states of the thing currently running to see if it
//needs to do something different
void Game::update()
{
	//if the game state is MENU then display the menu
	if (state == MENU)
	{
		menuScreen();
		//when the menu screen is dismissed, set the game state to LEVEL
		if (screen.getState() == NEXT)
		{
			state = LEVEL;
			screen.setState(STAY);
		}
	}
	//otherwise, if the game state is LEVEL
	else if (state == LEVEL)
	{
		//if the esc button is pressed set the game state to PAUSE
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			state = PAUSE;
		//other wise check to see if they won the game, if so set game state to WIN
		else if (currentLevel.getState() == WON && lvlCounter == (levels.size() - 1))
		{
			state = WIN;
			killCount += currentLevel.getKills();
		}
		//check to see if they won the level, if so set game state to TRANSITION
		else if (currentLevel.getState() == WON)
		{
			state = TRANSITION;
			killCount += currentLevel.getKills();
		}
		//check to see if they lost the game, if so set the game state to LOSE
		else if (currentLevel.getState() == LOST)
		{
			state = LOSE;
			killCount += currentLevel.getKills();
		}
		//check to see if the level needs to be reset (ie. the player lost a life), if so then restart the level
		else if (currentLevel.getState() == RESET)
		{
			restartLevel();
		}
		//if theres nothin' special goin' on just update the level
		else
			updateLevel();
	}
	//if the game state is PAUSE
	else if (state == PAUSE)
	{
		pause(); //set up / update the pause screen
		if (screen.getState() == NEXT) //check if they've decided to continue with the game yet
		{
			state = LEVEL;
			screen.setState(STAY);
		}
	}
	//if the game state is TRANSITION
	else if (state == TRANSITION)
	{
		transition(); //set up / update the transition screen
		if (screen.getState() == NEXT) //move on when they decided to start the next level
		{
			currentLevel.resetKills();
			nextLevel();
			screen.setState(STAY);
			state = LEVEL;
		}
	}
	//if the game state is WIN
	else if (state == WIN)
	{
		winScreen(); //set up / update the win screen
		if (screen.getState() == NEXT) //restart the game when they click continue
		{
			state = MENU;
			start();
			screen.setState(STAY);
		}
	}
	//if the game state is LOSE
	else if (state == LOSE)
	{
		loseScreen(); //set up / update the win screen
		if (screen.getState() == NEXT) //restart the game when they click continue
		{
			state = MENU;
			start();
			screen.setState(STAY);
		}
	}
}