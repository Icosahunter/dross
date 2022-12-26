#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Display.h"
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//constructor
//window: the window to draw to
//ttl: the title text for the screen
//txt: the primary text for the screen
//font: the font of the text
//txtClr: the color of the text
//dt: the mode for setting state to NEXT, either a button, click anywhere, or press enter
Display::Display(RenderWindow &window, string ttl, string txt, Font &font, Color txtClr, dispType dt)
{
	win = &window;
	type = dt;

	//set up the title text
	title.setString(ttl);
	title.setFont(font);
	title.setFillColor(txtClr);
	title.setCharacterSize(50);
	title.setPosition(((win->getSize().x)/2)-((title.getLocalBounds().width)/2), (win->getSize().y/2)-((title.getLocalBounds().height)/2) - 100);

	//set up the primary text
	text.setString(txt);
	text.setFont(font);
	text.setFillColor(txtClr);
	text.setCharacterSize(20);
	text.setPosition(((win->getSize().x) / 2) - ((text.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((text.getLocalBounds().height) / 2) + 40);

	//depending on what display type (dt) they chose, set up the prompt text appropriately
	if (type == CLICK)
		click.setString("[click anywhere to continue]");
	else if (type == ENTER)
		click.setString("[press enter to continue]");
	else if (type == BUTTON)
		click.setString("[click to continue]");

	//set up the rest of the prompt text
	click.setFont(font);
	click.setFillColor(txtClr);
	click.setCharacterSize(20);
	click.setPosition(((win->getSize().x) / 2) - ((click.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((click.getLocalBounds().height) / 2) + 80);
	
	//set up the prompt ouline box (only actually used for the BUTTON mode
	shape.setPosition(click.getPosition().x - 5, click.getPosition().y);
	shape.setSize(Vector2f(click.getGlobalBounds().width + 10, click.getGlobalBounds().height));
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(3);

	//if the type is BUTTON make the box visible
	if (type == BUTTON)
		shape.setOutlineColor(txtClr);
	else
		shape.setOutlineColor(Color::Transparent);
}

//default constructor
Display::Display()
{
	type = CLICK;
	click.setString("[click anywhere to continue]");
	click.setCharacterSize(20);
	text.setCharacterSize(20);
	title.setCharacterSize(50);
	shape.setFillColor(Color::Transparent);
	shape.setOutlineThickness(3);
}

//updates the text position to the (x) center of the screen
void Display::updateTextPos()
{
	title.setPosition(((win->getSize().x) / 2) - ((title.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((title.getLocalBounds().height) / 2) - 100);
	text.setPosition(((win->getSize().x) / 2) - ((text.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((text.getLocalBounds().height) / 2) + 40);
	click.setPosition(((win->getSize().x) / 2) - ((click.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((click.getLocalBounds().height) / 2) + 80);
	shape.setPosition(click.getPosition().x - 7, click.getPosition().y);
	shape.setSize(Vector2f(click.getGlobalBounds().width + 14, click.getGlobalBounds().height + 7));
}	

//set the primary text of the screen
void Display::setText(string txt)
{
	text.setString(txt);
	text.setPosition(((win->getSize().x) / 2) - ((text.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((text.getLocalBounds().height) / 2) + 40);
}

//draw all the stuffs
void Display::draw()
{
	win->draw(title);
	win->draw(text);
	win->draw(click);
	if (type == BUTTON)
		win->draw(shape);
}

//check to see if the state should be set to NEXT (this depends on the type of continue mode specified)
void Display::checkForNext()
{
	bool press = false;
	
	if (type == CLICK) //if the type is click
	{
		while (Mouse::isButtonPressed(Mouse::Button::Left)) //if they clicked anywhere
		{
			press = true;
		}
	}
	else if (type == ENTER) //if the type is enter
	{
		while (Keyboard::isKeyPressed(Keyboard::Return)) //if return is pressed
		{
			press = true;
		}
	}
	else if (type == BUTTON) //if the type is button
	{
		Vector2f mouse = win->mapPixelToCoords(Mouse::getPosition(*win));
		while (Mouse::isButtonPressed(Mouse::Button::Left) && shape.getGlobalBounds().contains(mouse)) //if they clicked the button
		{
			press = true;
		}
	}

	if (press == true)
		state = NEXT; //if the specified event occured then set state to NEXT
}


//update the screen, this is the function that should be called every frame this display is to be up
void Display::update()
{
	draw();
	checkForNext();
}

//returns the current state of the display
dispState Display::getState()
{
	return state;
}

//set the title text
void Display::setTitle(string txt)
{
	title.setString(txt);
	//setting position of text is complicated because you have to center it
	title.setPosition(((win->getSize().x) / 2) - ((title.getLocalBounds().width) / 2), (win->getSize().y / 2) - ((title.getLocalBounds().height) / 2) - 100);
}

//set the font
void Display::setFont(Font &font)
{
	title.setFont(font);
	text.setFont(font);
	click.setFont(font);
	updateTextPos(); //because a different font might change the texts bounding boxes
}

//set the font color
void Display::setColor(Color clr)
{
	title.setFillColor(clr);
	text.setFillColor(clr);
	click.setFillColor(clr);
	if (type == BUTTON) //if the type is button
		shape.setOutlineColor(clr); //set the color of the box to clr
	else
		shape.setOutlineColor(Color::Transparent); //otherwise it is invisible
}

//set the window
void Display::setWin(RenderWindow &window)
{
	win = &window; 
}

//set the state
void Display::setState(dispState st)
{
	state = st;
}

//set the continue type
void Display::setType(dispType tp)
{
	type = tp;
	//set the prompt appropriately
	if (type == CLICK)
		click.setString("[click anywhere to continue]");
	else if (type == ENTER)
		click.setString("[press enter to continue]");
	else if (type == BUTTON)
	{
		click.setString("[click to continue]");
		shape.setOutlineColor(text.getFillColor()); //if the new type is button then make the border visible
	}
	updateTextPos(); //the altered text will change bounding boxes so update the positions
}