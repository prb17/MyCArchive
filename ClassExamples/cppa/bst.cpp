#ifndef BST_CPP
#define BST_CPP

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
		return destroyNode(right);
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
	return toString(head);
}


template<typename T>
std::string Bst_t<T>::toString( Node_t<T>* at) const
{
	if(!at)
	{
		return "";
	}

	std::string left = toString(at->getLeft());

	std::string current;
	std::stringstream output;
	output << at->getData();
	current = output.str();

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
	if(data == at->getData())
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
			_size--;
			delete at;
			return true;
		}
		else if(children == 1)
		{
			Node_t<T>* child = at->getLeft();
			if(!child)
			{
				child = at->getRight();
			}
			if(parent)
			{
				if(parent->getLeft() == at)
				{
					parent->setLeft(child);
				}
				else
				{
					parent->setRight(child);
				}
			}
			else
			{
				head = child;
			}
			_size--;
			delete at;
			return true;
		}
		//we have two kids:
		at->setData(getNextLargest(at->getRight()));
		return remove(at->getData(), at->getRight(), at);

	}
	else if(data < at->getData())
	{
		return remove(data, at->getLeft(), at);
	}
	return remove(data, at->getRight(), at);
}

template<typename T>
T Bst_t<T>::getNextLargest( Node_t<T>* at) const
{
	if(at->getLeft())
	{
		return getNextLargest(at->getLeft());
	}
	return at->getData();
}
#endif
