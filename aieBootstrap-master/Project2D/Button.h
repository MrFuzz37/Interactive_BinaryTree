#pragma once
#include "Renderer2D.h"
#include "Font.h"
#include "Input.h"

class Button
{
public:
	Button(const char* buttonText, float x, float y, float width, float height);
	~Button();

	aie::Font* m_font;
	char m_buttonText[64];

	float m_posX;
	float m_posY;
	float m_width;
	float m_height;

	// Takes in the renderer to draw the buttons with their text on the screen 
	void Draw(aie::Renderer2D* renderer);

	// Checks if the player has clicked on a button
	bool Update();
};

