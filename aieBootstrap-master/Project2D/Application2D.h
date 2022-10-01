#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "DoubleLinkedLists.h"
#include "Button.h"
#include <string>

// An enumerator that determines which coloured circle will flash
enum SimonColour
{
	BLUE,
	GREEN,
	YELLOW,
	RED
};

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	// Allocates everything, returns true when run
	virtual bool startup();

	// Deallocates everything
	virtual void shutdown();

	// Updates any input 
	virtual void update(float deltaTime);

	// Draws everything to the screen 
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Font*			m_font;
	aie::Texture*		m_CircleRed;
	aie::Texture*		m_CircleYellow;
	aie::Texture*		m_CircleGreen;
	aie::Texture*		m_CircleBlue;
	aie::Texture*		m_title;

	DoubleLinkedList<SimonColour>	m_SimonSequence;
	DoubleLinkedList<SimonColour>::Iterator it;

	unsigned int		m_SequenceIndex = 0;
	bool				m_playersTurn = false;
	float				m_brightness = 1;
	bool				m_firstTurn;
	int					m_playerScore;

	float				m_timer;
	int					m_currentState;
	float				m_difficulty = 0.6f;

	Button*				m_buttonPlay;
	Button*				m_buttonOptions;
	Button*				m_buttonExit;
	Button*				m_buttonEasy;
	Button*				m_buttonMedium;
	Button*				m_buttonHard;


private:
	// Adds another random colour to the sequence
	void				addNewColourToSimonSequence();

	// Draws the board in a dimmed state
	void				drawDimmedBoard();

	// Draws the board with the one active colour being brighter
	void				drawActiveColour(int colour);

	// Draws the interface during the play state depending on whose turn it is
	void				drawInterface();

	// Takes in a colour based on players input and determines whether input matches the sequence
	// If it does add another colour to the sequnce and pass it to simons turn
	// Otherwise return to main menu
	void				playerInput(SimonColour colour);
};