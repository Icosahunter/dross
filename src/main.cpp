//to add:
//error checking
//transitions use enter
//altered damage works
//
#include <iostream>
#include <cmath>
#include <filesystem>
#include "Game.h"
#include "Level.h"
#include "Enemy.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 

//============================================================
// Nathaniel Markham
//============================================================

#ifndef DATA_DIR
#define DATA_DIR "./"
#endif

#ifndef HIT_BOX
#define HIT_BOX true
#endif

#ifndef ALL_LEVELS
#define ALL_LEVELS true
#endif

int main()
{
	srand(time(0));
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	Texture invader, missile, ship, boss, boss2, invader2, enemyMissile, wall;
	filesystem::path invaderImagePath ("images/face.png");
	filesystem::path missileImagePath ("images/red.png");
	filesystem::path playerImagePath ("images/Death_sphere.png");
	filesystem::path invader2ImagePath ("images/face_2.png");
	filesystem::path bossImagePath ("images/boss.png");
	filesystem::path boss2ImagePath ("images/boss_2");
	filesystem::path wallImagePath ("images/wall.png");
	filesystem::path enemyMissileImagePath ("images/enemyMissile.png");
	filesystem::path backgroundImagePath ("images/back.png");
	filesystem::path fontPath ("fonts/RubikBurned/RubikBurned-Regular.ttf");
	filesystem::path dataDir (DATA_DIR);


	invader.loadFromFile(dataDir / invaderImagePath);
	missile.loadFromFile(dataDir / missileImagePath);
	ship.loadFromFile(dataDir / playerImagePath);
	invader2.loadFromFile(dataDir / invader2ImagePath);
	boss.loadFromFile(dataDir / bossImagePath);
	boss2.loadFromFile(dataDir / boss2ImagePath);
	wall.loadFromFile(dataDir / wallImagePath);
	enemyMissile.loadFromFile(dataDir / enemyMissileImagePath);
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dross");
	Font font;
	font.loadFromFile(dataDir / fontPath);
 	Text text;

	Player player(ship, missile, 5, 2, 5, true, window.getSize().y - 80);
	Game game(window, player, Color::Green, font);

	levelData lvl1 = Level::lvlData(10,   1,       150,       1.5,        1,        0.5,           1,   invader,   enemyMissile,   40, STRAIGHT, window);
	levelData lvl2 = Level::lvlData( 5,   1,       100,       1.5,        1,        0.2,          10,  invader2,   enemyMissile,   70, STRAIGHT, window);
	levelData lvl3 = Level::lvlData( 3,   1,       100,       1.5,        1,        0.2,          10,  invader2,   enemyMissile,   70,   SPREAD, window);
	levelData lvl4 = Level::lvlData( 1,   1,         7,         4,        1,       0.13,         100,      boss,   enemyMissile,  200, STRAIGHT, window);

	levelData lvl5 = Level::lvlData(20,   2,       200,       1.5,        1,        0.3,           1,   invader,   enemyMissile,   35, STRAIGHT, window);
	levelData lvl6 = Level::lvlData( 8,   1,        95,       1.7,        1,        0.2,          10,  invader2,   enemyMissile,   70, STRAIGHT, window);
	levelData lvl7 = Level::lvlData( 5,   1,        95,       1.7,        1,        0.2,           8,  invader2,   enemyMissile,   70,   SPREAD, window);
	levelData lvl8 = Level::lvlData( 1,   1,         3,         5,        1,       0.12,         165,     boss2,   enemyMissile,  400, STRAIGHT, window);
	
	levelData lvl9 = Level::lvlData(30,    3,       300,       1.5,        1,        0.1,           1,    invader,   enemyMissile,   30, STRAIGHT, window);
	levelData lvl10 = Level::lvlData(8,    2,        90,         2,        1,        0.2,          10,   invader2,   enemyMissile,   70, STRAIGHT, window);
	levelData lvl11 = Level::lvlData(8,    1,        90,         2,        1,        0.2,           8,   invader2,   enemyMissile,   70,   SPREAD, window);
	levelData lvl12 = Level::lvlData(1,    1,         1,         6,        1,       0.1,         220,       wall,   enemyMissile,  800, STRAIGHT, window);

	game.addLevel(lvl1);
	game.addLevel(lvl2);
	if (ALL_LEVELS)
	{
		game.addLevel(lvl3);
		game.addLevel(lvl4);
		game.addLevel(lvl5);
		game.addLevel(lvl6);
		game.addLevel(lvl7);
		game.addLevel(lvl8);
		game.addLevel(lvl9);
		game.addLevel(lvl10);
		game.addLevel(lvl11);
		game.addLevel(lvl12);
	}
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	Texture starsTexture;
	if (!starsTexture.loadFromFile(dataDir / backgroundImagePath))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	background.setScale(WINDOW_WIDTH/background.getGlobalBounds().width, WINDOW_HEIGHT / background.getGlobalBounds().height);
	game.start();

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		game.update();

		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}