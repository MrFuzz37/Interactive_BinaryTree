#pragma once
#include <Renderer2D.h>
#include <sstream>

template <typename T>
class BinaryTree
{
public:

	class TreeNode
	{
	public:
		// Default Constructor with default initialiser values
		TreeNode(T value)
			: m_value(value), m_right(nullptr), m_left(nullptr)
		{
		}

		~TreeNode()
		{
		}

		// Returns true if the current node has a left child
		bool hasLeft()
		{
			return (m_left != nullptr);
		}

		// Returns true if the current node has a right child
		bool hasRight()
		{
			return (m_right != nullptr);
		}

		// Returns the current node data
		int getData()
		{
			return m_value;
		}

		// Returns the current nodes left child
		TreeNode* getLeft()
		{
			return m_left;
		}

		// Returns the current nodes right child
		TreeNode* getRight()
		{
			return m_right;
		}

		// Sets the data of the current node to the passed in nodes data
		void setData(T value)
		{
			m_value = value;
		}

		// Sets the current nodes left child to the passed in node
		void setLeft(TreeNode* node)
		{
			m_left = node;
		}

		// Sets the current nodes right child to the passed in node
		void setRight(TreeNode* node)
		{
			m_right = node;
		}

		// Draws the circle with its text in the designated spot on the tree
		void draw(aie::Renderer2D* renderer, aie::Font* font, int x, int y, bool selected)
		{
			std::stringstream s;
			s << m_value;

			std::string uiText = s.str();

			renderer->setRenderColour(0, 0, 1);
			renderer->drawCircle(x, y, 30);

			// The current node selected will be highlighted
			if (selected == true)
			{
				renderer->setRenderColour(0, 0, 0.25);
				renderer->drawCircle(x, y, 28);

				renderer->setRenderColour(1, 1, 1);
				renderer->drawText(font, uiText.c_str(), x - 12, y - 10);
			}
			else
			{
				renderer->setRenderColour(0, 0, 0);
				renderer->drawCircle(x, y, 28);

				renderer->setRenderColour(1, 1, 1);
				renderer->drawText(font, uiText.c_str(), x - 12, y - 10);
			}
		}

	private:
		T m_value;

		TreeNode* m_left;
		TreeNode* m_right;
	};

public:

	BinaryTree()
		: m_pRoot(nullptr)
	{
	}

	~BinaryTree()
	{

	}

	// Returns true if the tree has no root node
	bool isEmpty() const
	{
		return (m_pRoot == nullptr);
	}

	// Insert the passed in data to the tree as a node
	void insert(T a_nValue)
	{
		// If tree is empty the passed in node becomes the root node
		if (isEmpty())
		{
			m_pRoot = new TreeNode(a_nValue);
		}

		// If not empty compare the nodes data to other nodes in the tree to determine where it gets inserted
		else
		{
			TreeNode* nodeToInsert = new TreeNode(a_nValue);
			TreeNode* insertIterator = m_pRoot;
			TreeNode* parent = insertIterator;

			while (insertIterator != nullptr)
			{
				// If nodes value is less than current Iterators position
				if (a_nValue < insertIterator->getData())
				{
					// Check to see if there is a left node before moving the iterator along to the left
					if (insertIterator->hasLeft())
					{
						insertIterator = insertIterator->getLeft();
					}
					// If no left exists we've found it's spot to be inserted
					else
					{
						// Grab the soon to be parent of our node and reset the iterator
						parent = insertIterator;
						insertIterator = nullptr;
						break;
					}
				}
				if (a_nValue > insertIterator->getData())
				{
					if (insertIterator->hasRight())
					{
						insertIterator = insertIterator->getRight();
					}
					else
					{
						parent = insertIterator;
						insertIterator = nullptr;
						break;
					}
				}
				// If the value already exists we exit the loop
				if (a_nValue == insertIterator->getData())
				{
					return;
				}
				parent = insertIterator;			
			}
			// If the nodes value is less than the parent it becomes the parents left child
			if (a_nValue < parent->getData())
			{
				parent->setLeft(nodeToInsert);
			}
			// If it's greater it becomes the parents right child
			else
			{
				parent->setRight(nodeToInsert);
			}
		}
	}

	// Takes in a value to remove 
	// Finds the node to remove
	// Removes the node
	void remove(T a_nValue)
	{
		TreeNode* currentNode = m_pRoot;
		TreeNode* parent = m_pRoot;
		TreeNode* Iterator = m_pRoot;

		// Call the find function to search the tree for the value passed in
		findNode(a_nValue, currentNode, parent);

		Iterator = currentNode;

		if (currentNode->hasRight())
		{
			Iterator = Iterator->getRight();

			// Traverse down the left branch from the node right child to find the minimum value
			// Keeping the parent node one above the Iterator
			while (Iterator->hasLeft())
			{
				parent = Iterator;
				Iterator = Iterator->getLeft();
			}
			// If the node to remove is a child of the root node the above while loop never runs
			// Therefore, need to set the parent node to the node to delete
			if (parent == m_pRoot)
			{
				parent = currentNode;
			}
			// Copy the minimum value into the node we want to remove
			currentNode->setData(Iterator->getData());
			
			// If deleting the parent of the minimum nodes left child
			if (parent->hasLeft() && parent->getLeft()->getData() == currentNode->getData())
			{
				// Set the parents left child to the node to deletes right child if there is one
				if (Iterator->hasRight())
				{					
					parent->setLeft(Iterator->getRight());
				}
				else if (Iterator->hasLeft())
				{
					parent->setLeft(Iterator->getLeft());
				}
				else
				{
					parent->setLeft(nullptr);
				}
			}
			else if (parent->hasRight() && parent->getRight()->getData() == currentNode->getData())
			{
				if (Iterator->hasRight())
				{
					parent->setRight(Iterator->getRight());
				}
				else if (Iterator->hasLeft())
				{
					parent->setLeft(Iterator->getLeft());
				}
				else
				{
					parent->setRight(nullptr);
				}
			}

		}
		// If the node to delete has no right child
		if (currentNode->hasRight() == false)
		{
			// If deleting the parents left child set the parent of the node to delete left child to the node to deletes left child
			if (parent->hasLeft() && parent->getLeft()->getData() == a_nValue)
			{
				parent->setLeft(currentNode->getLeft());
			}
			// If deleting the parents right child set the parent of the node to delete right child to the node to deletes left child
			if (parent->hasRight() && parent->getRight()->getData() == a_nValue)
			{
				parent->setRight(currentNode->getLeft());
			}
			// If deleting the root set it to the roots left child
			if (m_pRoot->getData() == a_nValue)
			{
				m_pRoot = m_pRoot->getLeft();
			}
		}

	}

	TreeNode* find(T a_nValue)
	{
		TreeNode* nodeToFind = m_pRoot;
		// Start iterating while the pointer isn't null
		while (nodeToFind != nullptr)
		{
			// If the current nodes data is less than the value we want to find
			if (a_nValue < nodeToFind->getData())
			{
				// Check if the node has a left child
				if (nodeToFind->hasLeft())
				{
					// Traverse to the next node
					nodeToFind = nodeToFind->getLeft();
				}
				// If it doesn't then the value doesn't exist in the tree
				else
				{
					return nullptr;
				}
			}
			if (a_nValue > nodeToFind->getData())
			{
				if (nodeToFind->hasRight())
				{
					nodeToFind = nodeToFind->getRight();
				}
				else
				{
					return nullptr;
				}
			}
			// If the value equals the current nodes value then return that node
			if (a_nValue == nodeToFind->getData())
			{
				return nodeToFind;
			}
		}
		// If we somehow reach null return not found
		return nullptr;
	}

	// Takes in the renderer, font to use and node to draw
	// Calls another draw function with extra spacing parameters for the node and where it start on the tree
	void draw(aie::Renderer2D* renderer, aie::Font* font, TreeNode* selected)
	{
		draw(renderer, font, m_pRoot, 640, 680, 640, selected);
	}

private:
	// Takes in all the parameters of the above functions call
	// Determines where the node needs to be drawn on the screen and draws the line to connect them
	void draw(aie::Renderer2D* renderer, aie::Font* font, TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
	{
		horizontalSpacing /= 2;

		if (pNode)
		{
			if (pNode->hasLeft())
			{
				renderer->setRenderColour(1, 0, 0);
				renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
				draw(renderer, font, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, selected);
			}

			if (pNode->hasRight())
			{
				renderer->setRenderColour(1, 0, 0);
				renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
				draw(renderer, font, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, selected);
			}

			pNode->draw(renderer, font, x, y, (selected == pNode));
		}
	}

private:
	bool findNode(T a_nValue, TreeNode*& currentNode, TreeNode*& parent)
	{
		// While the node we are looking to find isn't null
		while (currentNode != nullptr)
		{
			// If the nodes value equals the value we're looking for return the node and its parent
			if (a_nValue == currentNode->getData())
			{
				return currentNode && parent;
			}
			else
			{
				// If the value is less than the current nodes value
				if (a_nValue < currentNode->getData())
				{
					// Check if there is a left node
					if (currentNode->hasLeft())
					{
						// Sets the parent node to equal the current node in case the next node is the one
						// we are looking for and moves the node pointer left
						parent = currentNode;
						currentNode = currentNode->getLeft();
					}
				}
				else if (currentNode->hasRight())
				{
					parent = currentNode;
					currentNode = currentNode->getRight();
				}
				// If current node has no left or right and the value doesn't equal the one we want return false
				else
				{
					// Not found
					return false;
				}
			}
		}

		return false;
	}

	TreeNode* m_pRoot;
};