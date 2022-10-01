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
	
	srand((unsigned int)time(nullptr));

	m_2dRenderer = new aie::Renderer2D();

	m_2dRenderer->setRenderColour(1, 0, 0);
	m_2dRenderer->drawBox(50, 50, 30, 20);
	m_2dRenderer->drawBox(50, 50, 30, 20);
	m_2dRenderer->drawBox(50, 50, 30, 20);
	m_2dRenderer->drawCircle(50, 50, 30);

	m_2dRenderer->setRenderColour(1, 1, 1);

	m_texture = new aie::Texture("./textures/numbered_grid.tga");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	m_timer = 0;

	it = m_SimonSequence.begin();
	//m_binaryTree = new BinaryTree();
	addNewColourToSimonSequence();
	addNewColourToSimonSequence();
	addNewColourToSimonSequence();
	m_SequenceIndex = 0;

	return true;
}

void Application2D::shutdown() {
	
	//delete m_binaryTree;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (m_playersTurn)
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_UP))
		{
			if (it.GetData() == BLUE)
			{
				it.moveNext();
			}
		}
	}
	else
	{
		// Simons turn
		if (m_timer > 1)
		{
			m_timer = 0;
			m_SequenceIndex++;
			m_brightness = 1;

			if (m_SequenceIndex == m_SimonSequence.Count())
			{
				m_playersTurn = true;
				m_SequenceIndex = 0;
				it = m_SimonSequence.begin();
			}
		}
	}

/*
	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	//m_binaryTree->update(deltaTime);
*/

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();



	// begin drawing sprites
	m_2dRenderer->begin();

	drawDimmedBoard();

	if (m_playersTurn)
	{
		m_2dRenderer->setRenderColour(0, 0, 1);
		m_2dRenderer->drawText(m_font, "Player's Turn", 0, 0);
	}
	else
	{
		// Simons turn
		if (m_SequenceIndex < m_SimonSequence.Count())
		{
			drawActiveBox(m_SimonSequence.(m_SequenceIndex));
		}

		m_2dRenderer->setRenderColour(1, 0, 0);
		m_2dRenderer->drawText(m_font, "Simon's Turn", 0, 0);
	}

/*
	//m_binaryTree->draw(m_2dRenderer);

	
	
	// demonstrate animation
	m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	// draw a thin line
	m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	m_2dRenderer->setRenderColour(1, 0, 0, 1);
	m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
*/

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::addNewColourToSimonSequence()
{
	m_SimonSequence.PushBack((SimonColour)(rand() % 4));
}

void Application2D::drawDimmedBoard()
{
	// Draw all boxes on screen dimmed
	m_2dRenderer->setRenderColour(0.2f, 0, 0);
	m_2dRenderer->drawSprite(200, 200, 50, 50);

	m_2dRenderer->setRenderColour(0, 0.2f, 0);
	m_2dRenderer->drawBox(250, 200, 50, 50);

	m_2dRenderer->setRenderColour(0.2f, 0.2f, 0);
	m_2dRenderer->drawBox(300, 200, 50, 50);

	m_2dRenderer->setRenderColour(0, 0, 0.2f);
	m_2dRenderer->drawBox(350, 200, 50, 50);
}

void Application2D::drawActiveBox(int colour)
{
	switch (colour)
	{
	case BLUE:
		m_2dRenderer->setRenderColour(0, 0, m_brightness);
		m_2dRenderer->drawBox(350, 200, 50, 50);
		break;
	case RED:
		m_2dRenderer->setRenderColour(m_brightness, 0, 0);
		m_2dRenderer->drawBox(200, 200, 50, 50);
		break;
	case YELLOW:
		m_2dRenderer->setRenderColour(m_brightness, m_brightness, 0);
		m_2dRenderer->drawBox(300, 200, 50, 50);
		break;
	case GREEN:
		m_2dRenderer->setRenderColour(0, 0, m_brightness);
		m_2dRenderer->drawBox(350, 200, 50, 50);
		break;

	}

	m_brightness *= 0.95f;
	if (m_brightness < 0.2f)
		m_brightness = 0.2f;
}
