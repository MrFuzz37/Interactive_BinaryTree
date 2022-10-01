#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "BinaryTree.h"
#include <string>

class BinaryTreeApp : public aie::Application {
public:

	BinaryTreeApp();
	~BinaryTreeApp();
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
	aie::Font*			m_font;
	BinaryTree<int>		m_binaryTree;
	BinaryTree<int>::TreeNode*	m_selectedNode = nullptr;

};

