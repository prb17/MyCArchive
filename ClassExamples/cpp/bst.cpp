#ifndef BST_CPP
#define BST_CPP

#include"bst.h"
#include<sstream>

template<typename T>
Bst_t<T>::Bst_t()
: head(NULL), _size(0)
{}

template<typename T>
Bst_t<T>::~Bst_t()
{
	if(head)
	{
		destroyNode(head);
	}
}

template<typename T>
void Bst_t<T>::destroyNode( Node_t<T>* at)
{
	Node_t<T>* left = at->getLeft();
	Node_t<T>* right = at->getRight();
	delete at;

	if(left)
	{
		destroyNode(left);
	}
	if(right)
	{
		destroyNode(right);
	}
}

template<typename T>
bool Bst_t<T>::insert(T data)
{
	if(head)
	{
		return insert(data, head);
	}
	_size++;
	head = new Node_t<T>(data, NULL, NULL);
	return true;
}

template<typename T>
bool Bst_t<T>::insert(T data, Node_t<T>* at)
{
	if(data == at->getData())
	{
		return false;
	}

	if(data < at->getData())
	{
		if(at->getLeft())
		{
			return insert(data, at->getLeft());
		}
		at->setLeft(new Node_t<T>(data, NULL, NULL));
		return true;
	}

	//implied, we are larger
	if(at->getRight())
	{
		return insert(data, at->getRight());
	}
	at->setRight(new Node_t<T>(data, NULL, NULL));
	return true;
}

template<typename T>
std::string Bst_t<T>::toString() const
{
	if(head)
	{
		return toString(head);
	}
	return "";
}


template<typename T>
std::string Bst_t<T>::toString( Node_t<T>* at) const
{
	if(!at)
	{
		return "";
	}
	std::string left = toString(at->getLeft());

	std::stringstream input;
	input << at->getData();
	std::string current = input.str();

	std::string right = toString(at->getRight());
	return left + " " + current + " " + right;
}


template<typename T>
bool Bst_t<T>::remove(T data)
{
	return remove(data, head, NULL);
}

template<typename T>
bool Bst_t<T>::remove(T data, Node_t<T>* at, Node_t<T>* parent)
{
	if(!at)
	{
		return false;
	}

	if(at->getData() == data)
	{
		//removal case
		int children = 0;
		if(at->getLeft())
		{
			children++;
		}
		if(at->getRight())
		{
			children++;
		}
		if(children == 0)
		{
			if(parent)
			{
				if(parent->getLeft() == at)
				{
					parent->setLeft(NULL);
				}
				else
				{
					parent->setRight(NULL);
				}
			}
			else
			{
				head = NULL;
			}
			delete at;
			_size--;
			return true;
		}
		if(children == 1)
		{
			Node_t<T>* orphan = at->getLeft();
			if(!orphan)
			{
				orphan = at->getRight();
			}
			if(parent)
			{
				if(parent->getLeft() == at)
				{
					parent->setLeft(orphan);
				}
				else
				{
					parent->setRight(orphan);
				}
			}
			else
			{
				head = orphan;
			}
			delete at;
			_size--;
			return true;
		}
		//children must be 2
		at->setData(findNextLargest(at->getRight()));
		return remove(at->getData(), at->getRight(), at);
	}
	else if(data < at->getData())
	{
		return remove(data, at->getLeft(), at);
	}
	else
	{
		return remove(data, at->getRight(), at);
	}
}

template<typename T>
T Bst_t<T>::findNextLargest( Node_t<T>* at)
{
	if(at->getLeft())
	{
		return findNextLargest(at->getLeft());
	}
	return at->getData();
}


#endif
