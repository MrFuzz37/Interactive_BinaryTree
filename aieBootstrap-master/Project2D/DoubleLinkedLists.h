#pragma once

template <typename T>
class DoubleLinkedList
{
private:
	class Node
	{
	public:
		Node(T data, Node* next = nullptr, Node* previous = nullptr)
		{
			this->data = data;
			this->next = next;
			this->previous = previous;
		}

		T data;
		Node* next;
		Node* previous;
	};

public:
	// Iterator used to step thru the collection.
	// It can be used outside the class, so we make it public
	class Iterator
	{
	public:
		// Default constructor
		Iterator(Node* node = nullptr)
		{
			this->node = node;
		}

		// Checks if the node is valid
		bool IsValid() const
		{
			return (node != nullptr);
		}

		// Checks the data of a node
		T& GetData() const
		{
			if (node == nullptr)
			{
				throw "Invalid iterator";
			}
			return node->data;
		}

		// Move the iterator to the next node in the list
		bool moveNext()
		{
			if (node != nullptr)
			{
				node = node->next;
			}

			return IsValid();
		}

		// Move the iterator to the previous node in the list
		bool movePrevious()
		{
			if (node != nullptr)
			{
				node = node->previous;
			}

			return IsValid();
		}


	private:
		friend class DoubleLinkedList;
		Node* node;
	};


public:
	// Default Constructor
	DoubleLinkedList()
	{
		head = tail = nullptr;
	}

	// Destructor
	~DoubleLinkedList()
	{
		clear();
	}

	// Is the list empty?
	bool Empty() const
	{
		return (head == nullptr) || (tail == nullptr);
	}

	// Remove all nodes from the list
	void clear()
	{
		Node* node = head;
		Node* nodeToDelete;
		// Loop thru all nodes starting at the head, until we reach a nullptr (the end of list)
		// Get a temp copy of the node to delete & then move to the next node.
		// Finally delete the node to release memory
		while (node != nullptr)
		{
			nodeToDelete = node;
			node = node->next;
			delete nodeToDelete;
		}
		head = tail = nullptr;
	}

	// Push some data on front of list.
	// Returns true on success
	void pushFront(const T& data)
	{
		// Create a new node with ths input data
		// Make it's 'next' point to the head node
		Node* newNode = new Node(data, head);

		if (head != nullptr)
		{
			head->previous = newNode;
		}
		head = newNode;

		if (tail == nullptr)
		{
			tail = newNode;
		}
	}

	// Adding from the back
	void pushBack(const T& data)
	{
		Node* newNode = new Node(data, nullptr, tail);

		if (tail != nullptr)
		{
			tail->next = newNode;			
		}
		tail = newNode;

		if (head == nullptr)
		{
			head = newNode;
		}
	}

	// Pop data off front of list.
	// Returns data on success.
	// Throws exception if no data available.
	T popFront()
	{
		if (head == nullptr)
		{
			throw "List is empty";
		}

		// Get a reference to the node with the data
		Node* n = head;

		// Move the head/tail
		if (head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			head = head->next;
			head->previous = nullptr;
		}

		// Get a temp copy of the node data, ready to return after we delete the node
		T data = n->data;

		// Free the node data
		delete n;

		// Return the temp data
		return data;
	}

	// Removes last element
	T popBack()
	{
		if (tail == nullptr)
		{
			throw "List is empty";
		}

		Node* n = tail;

		if (head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			tail = tail->next;
			tail->previous = nullptr;
		}

		T data = n->data;

		delete n;

		return data;
	}

	// Return the first element in the list
	T& first() const
	{
		if (head == nullptr)
		{
			throw "List is empty";
		}

		return head->data;
	}

	// Gets the last element
	T& last() const
	{
		if (tail == nullptr)
		{
			throw "List is empty";
		}

		return tail->data;
	}

	// Return iterator to first element
	Iterator begin() const
	{
		return Iterator(head);
	}

	// Return an iterator to a null element
	Iterator end() const
	{
		return Iterator(tail);
	}

	// Return the number of items in the list
	unsigned int Count() const
	{
		unsigned int counter = 0;
		Node* node = head;
		while (node != nullptr)
		{
			counter++;
			node = node->next;
		}
		return counter;
	}

	// Insert a node after the specified spot
	void Insert(Iterator& iter, const T& data)
	{
		if (Empty())
		{
			pushFront(data);
		}
		else
		{
			Node* insertNode = iter.node;
			if (insertNode != nullptr)
			{
				Node* newNode = new Node(data, insertNode->next, insertNode);

				if (insertNode->next != nullptr)
				{
					insertNode->next->previous = newNode;
				}
				insertNode->next = newNode;
			}

			if (tail == insertNode)
			{
				Node* newNode = new Node(data, insertNode->next, insertNode);
				tail = newNode;
			}
			
		}
	}

	// Removes all data with the same value
	void Remove(const T& value)
	{
		Iterator it = begin();

		while (it.isValid())
		{
			if (it.getData() == value)
			{
				Iterator itToRemove(it);
				it.moveNext();

				Erase(itToRemove);
			}
			else
			{
				it.moveNext();
			}
		}
	}

	// Removes a node at a specific location
	void Erase(Iterator& itLocation)
	{
		if (itLocation.isValid())
		{
			Node* nodeToRemove = itLocation.node;
			if (nodeToRemove->previous != nullptr)
			{
				nodeToRemove->previous->next = nodeToRemove->next;
			}
			else if (head->previous == nullptr)
			{
				head = nodeToRemove->next;
			}			
			if (nodeToRemove->next != nullptr)
			{
				nodeToRemove->next->previous = nodeToRemove->previous;
			}
			else if (tail->next == nullptr)
			{
				tail = nodeToRemove->previous;
			}

			delete nodeToRemove;
		}
	}

	// Sorts all data in the array
	void BubbleSort()
	{
		bool swapped = true;
		Iterator it = begin();
		Iterator itNext = begin();
		itNext.moveNext();

		while (swapped)
		{
			Iterator it = begin();
			Iterator itNext = begin();
			itNext.moveNext();
			swapped = false;
			for (Iterator it = begin(); it.node->next != nullptr;)
			{
				if (it.node->previous != nullptr)
				{
					if (it.node->next->next != nullptr)
					{
						if (it.getData() > itNext.getData())
						{
							it.node->previous->next = it.node->next;
							it.node->next->next->previous = it.node;

							it.node->next = it.node->next->next;
							it.node->previous->next->previous = it.node->previous;

							it.node->previous = it.node->previous->next;
							it.node->previous->next = it.node;
							itNext.moveNext();
							itNext.moveNext();
							swapped = true;
						}
						else
						{
							it.moveNext();
							itNext.moveNext();
						}
					}
					else
					{
						if (it.getData() > itNext.getData())
						{
							it.node->previous->next = it.node->next;
							it.node->next->previous = it.node->previous;

							it.node->previous = it.node->next;
							it.node->next = nullptr;

							it.node->previous->next = it.node;
							tail = it.node;
							swapped = true;
						}
						else
						{
							it.moveNext();
							itNext.moveNext();
						}
					}
				}
				else
				{
					if (it.getData() > itNext.getData())
					{
						it.node->next->next->previous = it.node;
						it.node->previous = it.node->next;

						it.node->next->previous = nullptr;
						it.node->next = it.node->next->next;

						it.node->previous->next = it.node;
						head = itNext.node;
						itNext.moveNext();
						itNext.moveNext();
						swapped = true;
					}
					else
					{
						it.moveNext();
						itNext.moveNext();
					}
				}
			}
		}
	}

	// Searches for a node iterating through them all until the node is found
	T LinearSearch(const T& value)
	{
		Node* nodeToSearch = head;
		while (nodeToSearch != nullptr)
		{
			if (nodeToSearch->data == value)
			{
				return nodeToSearch->data;
			}
			nodeToSearch = nodeToSearch->next;
		}
		return NULL;
	}

	// Prints out all nodes data to the console
	void Print()
	{
		Iterator it = begin();
		while (it.isValid())
		{
			std::cout << it.getData() << std::endl;
			it.moveNext();
		}
	}

private:
	Node* head;
	Node* tail;
};
