#include "BinaryTreeApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ImGUI.h"

BinaryTreeApp::BinaryTreeApp()
{

}

BinaryTreeApp::~BinaryTreeApp() {

}

bool BinaryTreeApp::startup() {

	// Creates the 2d renderer to draw textures to the screen
	m_2dRenderer = new aie::Renderer2D();

	// Creates required font
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BinaryTreeApp::shutdown() {

	// Deetes all allocations
	delete m_font;
	delete m_2dRenderer;
}

void BinaryTreeApp::update(float deltaTime) {

	// Checks for input made
	aie::Input* input = aie::Input::getInstance();

	
	static int value = 0;
	ImGui::InputInt("Value", &value);

	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.insert(value);
		m_selectedNode = m_binaryTree.find(value);
	}
	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.remove(value);
	}
	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.find(value);
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BinaryTreeApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Draws the nodes to the screen as they are inserted
	m_binaryTree.draw(m_2dRenderer, m_font, m_selectedNode);


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}








