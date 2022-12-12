#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

enum dispState {STAY, NEXT};
enum dispType {ENTER, CLICK, BUTTON};

class Display
{
	
private:

	RenderWindow * win; //the window to draw to
	dispState state; //the state of the display (whether the user has clicked to move on)
	dispType type; //the way the user selects to move on
	Text title; //the title text
	Text text; //the primary text
	Text click; //the prompt text
	RectangleShape shape; //the prompt box, only dispalys if the type is set to BUTTON

public:

	Display(RenderWindow &window, string ttl, string txt, Font &font, Color txtClr, dispType dt); //constructor
	Display(); //default constructor
	void update(); //draw the display and update it's state
	void draw(); //draw the display
	void setText(string txt); //set the primary text
	void setTitle(string txt); //set the title text
	void setFont(Font &font); //set the font
	void setColor(Color clr); //set the text color
	void setWin(RenderWindow &win); //set the window to draw to
	void checkForNext(); //check for a state chenge and update the state appropriately
	dispState getState(); //returns the current state
	void updateTextPos(); //reposition all text
	void setState(dispState st); //set the state to the given value
	void setType(dispType tp); //set the method for the user to dismiss the display

};