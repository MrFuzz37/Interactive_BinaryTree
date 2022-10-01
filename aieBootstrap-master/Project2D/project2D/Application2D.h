#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "DoubleLinkedLists.h"

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

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	DoubleLinkedList<SimonColour>	m_SimonSequence;
	DoubleLinkedList<SimonColour>::Iterator it;

	unsigned int		m_SequenceIndex = 0;
	bool				m_playersTurn = false;
	float				m_brightness = 1;

	float m_timer;

private:
	void				addNewColourToSimonSequence();
	void				drawDimmedBoard();
	void				drawActiveBox(int colour);
};