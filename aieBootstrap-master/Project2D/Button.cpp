#include "Button.h"
#include <string>



Button::Button(const char* buttonText, float x, float y, float width, float height)
{
	strcpy_s(m_buttonText, 64, buttonText);

	m_font = new aie::Font("./font/consolas.ttf", 48);

	m_posX = x;		
	m_posY = y;
	m_width = width;
	m_height = height;
}

Button::~Button()
{
	delete m_font;
}

void Button::Draw(aie::Renderer2D* renderer)
{
	// Draws the boxes that will be the buttons
	renderer->setRenderColour(0, 0.5f, 0.7f, 1);
	renderer->drawBox(m_posX, m_posY, m_width, m_height);
	renderer->setRenderColour(1, 1, 1, 1);

	// Gets the text size and centers that text within the box
	float textWidth = m_font->getStringWidth(m_buttonText);
	float textHeight = m_font->getStringHeight(m_buttonText);
	float centredPosX = m_posX - (textWidth * 0.5f) + 2;
	float centredPosY = m_posY - (textHeight * 0.5f) + 5;

	// Draws the text in the box
	renderer->drawText(m_font, m_buttonText, centredPosX, centredPosY);
}

bool Button::Update()
{
	aie::Input* input = aie::Input::getInstance();

	// All the values that determine where the mouse is when clicked
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	float left = m_posX - (m_width * 0.5f);
	float right = m_posX + (m_width * 0.5f);
	float bottom = m_posY - (m_height * 0.5f);
	float top = m_posY + (m_height * 0.5f);

	// Checks if the mouse click was on a button and returns it
	if (mouseX > left && mouseX < right && mouseY > bottom && mouseY < top)
	{
		return input->wasMouseButtonReleased(aie::INPUT_MOUSE_BUTTON_LEFT);
	}

	return false;
}