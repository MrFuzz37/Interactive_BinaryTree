#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <imgui.h>
#include <time.h>


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	// Sets a random timer for the colours to be randomised.
	srand((unsigned int)time(nullptr));

	// Creates the 2d renderer to draw textures to the screen
	m_2dRenderer = new aie::Renderer2D();

	// Creates all the textures for the circles and title
	m_CircleBlue = new aie::Texture("./textures/CircleBlue.png");
	m_CircleGreen = new aie::Texture("./textures/CircleGreen.png");
	m_CircleYellow = new aie::Texture("./textures/CircleYellow.png");
	m_CircleRed = new aie::Texture("./textures/CircleRed.png");
	m_title = new aie::Texture("./textures/Title.png");

	// Creates all the buttons that can be pressed by the player
	m_buttonPlay = new Button("Start Game", 600, 400, 300, 100);
	m_buttonOptions = new Button("Options", 600, 280, 300, 100);
	m_buttonExit = new Button("Exit Game", 600, 160, 300, 100);
	m_buttonEasy = new Button("Easy", 600, 400, 300, 100);
	m_buttonMedium = new Button("Medium", 600, 280, 300, 100);
	m_buttonHard = new Button("Hard", 600, 160, 300, 100);

	// Creates all the fonts required
	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	// Set all the variables to the initial values
	m_timer = 0;
	m_SequenceIndex = 0;
	it = m_SimonSequence.begin();
	m_SimonSequence.clear();
	m_playerScore = 0;
	m_currentState = 1;
	m_firstTurn = true;
	m_playersTurn = false;

	return true;
}

void Application2D::shutdown() {
	
	//delete all allocated textures, buttons and fonts
	delete m_2dRenderer;

	delete m_font;
	delete m_title;

	delete m_buttonPlay;
	delete m_buttonOptions;
	delete m_buttonExit;
	delete m_buttonEasy;
	delete m_buttonMedium;
	delete m_buttonHard;

	delete m_CircleRed;
	delete m_CircleGreen;
	delete m_CircleBlue;
	delete m_CircleYellow;

}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// Checks for input made
	aie::Input* input = aie::Input::getInstance();

	// Current state starts at the main menu and switches based on button pressed 
	if (m_currentState == 1)
	{
		if (m_buttonPlay->Update())
		{
			m_currentState = 2;
		}
		else if (m_buttonOptions->Update())
		{
			m_currentState = 3;
		}
		else if (m_buttonExit->Update())
		{
			quit();
		}
	}
	// Play state controls player input 
	else if (m_currentState == 2)
	{
		if (m_playersTurn)
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			{
				playerInput(BLUE);
			}
			if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			{
				playerInput(RED);
			}
			if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
			{
				playerInput(YELLOW);
			}
			if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
			{
				playerInput(GREEN);
			}
		}
		// If it's Simons first turn, waits a bit longer to flash
		else if (!m_playersTurn && m_firstTurn)
		{
			// Simons turn
			if (m_timer > 2)
			{
				addNewColourToSimonSequence();
				m_firstTurn = false;
				m_timer = 0;
				m_brightness = 1;
				it = m_SimonSequence.begin();

				// If at the end of the sequence, switch to player's turn
				if (m_SequenceIndex == m_SimonSequence.Count())
				{
					m_playersTurn = true;
					m_SequenceIndex = 0;
					it = m_SimonSequence.begin();
				}
			}
		}
		// Each of Simon's other turns wait depending on difficulty
		else 
		{
			// Simons turn
			if (m_timer > m_difficulty)
			{
				m_timer = 0;
				m_SequenceIndex++;
				m_brightness = 1;
				it.moveNext();

				if (m_SequenceIndex == m_SimonSequence.Count())
				{
					m_playersTurn = true;
					m_SequenceIndex = 0;
					it = m_SimonSequence.begin();
				}
			}
		}
	}
	// Options menu state for difficulty control
	else if (m_currentState = 3)
	{
		if (m_buttonEasy->Update())
		{
			m_difficulty = 0.6f;
			m_currentState = 1;
		}
		else if (m_buttonMedium->Update())
		{
			m_difficulty = 0.3f;
			m_currentState = 1;
		}
		else if (m_buttonHard->Update())
		{
			m_difficulty = 0.15f;
			m_currentState = 1;
		}
	}
	
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Draws the main menu
	if (m_currentState == 1)
	{
		m_2dRenderer->drawSprite(m_title, 600, 550);
		m_buttonPlay->Draw(m_2dRenderer);
		m_buttonOptions->Draw(m_2dRenderer);
		m_buttonExit->Draw(m_2dRenderer);
	}
	// Draws the GUI for the play state
	else if (m_currentState == 2)
	{
		drawDimmedBoard();

		if (m_playersTurn)
		{
			drawInterface();
		}
		else
		{
			// Simons turn
			if (it.IsValid())
			{
				drawActiveColour(it.GetData());
			}
			drawInterface();

		}
	}
	// Draws the buttons in the options menu
	else if (m_currentState = 3)
	{
		m_2dRenderer->drawSprite(m_title, 600, 550);
		m_buttonEasy->Draw(m_2dRenderer);
		m_buttonMedium->Draw(m_2dRenderer);
		m_buttonHard->Draw(m_2dRenderer);
	}



	// done drawing sprites
	m_2dRenderer->end();
}

// Adds a new colour to the sequence
void Application2D::addNewColourToSimonSequence()
{
	m_SimonSequence.pushBack((SimonColour)(rand() % 4));
}

// Draw all colours on screen in a dimmed state
void Application2D::drawDimmedBoard()
{
	m_2dRenderer->setRenderColour(0.3f, 0, 0);
	m_2dRenderer->drawSprite(m_CircleRed, 600, 200, 150, 150);

	m_2dRenderer->setRenderColour(0, 0.3f, 0);
	m_2dRenderer->drawSprite(m_CircleGreen, 400, 350, 150, 150);

	m_2dRenderer->setRenderColour(0.3f, 0.3f, 0);
	m_2dRenderer->drawSprite(m_CircleYellow, 800, 350, 150, 150);

	m_2dRenderer->setRenderColour(0, 0, 0.3f);
	m_2dRenderer->drawSprite(m_CircleBlue, 600, 500, 150, 150);
}

// Draws a single colour brighter
void Application2D::drawActiveColour(int colour)
{
	switch (colour)
	{
	case BLUE:
		m_2dRenderer->setRenderColour(0, 0, m_brightness);
		m_2dRenderer->drawSprite(m_CircleBlue, 600, 500, 150, 150);
		break;
	case RED:
		m_2dRenderer->setRenderColour(m_brightness, 0, 0);
		m_2dRenderer->drawSprite(m_CircleRed, 600, 200, 150, 150);
		break;
	case YELLOW:
		m_2dRenderer->setRenderColour(m_brightness, m_brightness, 0);
		m_2dRenderer->drawSprite(m_CircleYellow, 800, 350, 150, 150);
		break;
	case GREEN:
		m_2dRenderer->setRenderColour(0, m_brightness, 0);
		m_2dRenderer->drawSprite(m_CircleGreen, 400, 350, 150, 150);
		break;
	}

	// Colour fades back to dimmed state
	m_brightness *= 0.95f;
	if (m_brightness < 0.3f)
		m_brightness = 0.3f;
}

// Draws the interface on the screen
void Application2D::drawInterface()
{
	if (m_playersTurn)
	{
		m_2dRenderer->setRenderColour(0, 0, 1);
		m_2dRenderer->drawText(m_font, "Player's Turn", 475, 10);
	}
	else
	{
		m_2dRenderer->setRenderColour(1, 0, 0);
		m_2dRenderer->drawText(m_font, "Simon's Turn", 475, 10);
	}

	char fps[32];
	m_2dRenderer->setRenderColour(1, 1, 0);
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->setRenderColour(1, 1, 1);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	char score[32];
	sprintf_s(score, 32, "Score: %i", m_playerScore);
	m_2dRenderer->drawText(m_font, score, 1000, 720 - 32);
}

// Checks players input with the sequence
void Application2D::playerInput(SimonColour colour)
{
	if (it.GetData() == colour)
	{
		m_SequenceIndex++;
		it.moveNext();
		if (m_SequenceIndex == m_SimonSequence.Count())
		{
			m_SequenceIndex = 0;
			it = m_SimonSequence.begin();
			addNewColourToSimonSequence();
			m_playerScore++;
			m_playersTurn = false;
			m_timer = 0;
		}
	}
	else if (it.GetData() != colour)
	{
		startup();
	}
}
