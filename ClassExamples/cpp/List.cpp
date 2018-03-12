#include"List.h"

List_t::List_t()
: head(NULL), size(0)
{}

List_t::List_t(const List_t* source)
: head(NULL), size(source->size)
{
	/*
	Node_t* at = source->getLast();

	while(at)
	{
		insert(at->getValue());
		at = at->getPrev();
	}
	*/

	Node_t* at = source->head;

	Node_t* prev = NULL;
	while(at)
	{
		if(!head)
		{
			head = new Node_t(at->getValue(), NULL, NULL);
			prev = head;
		}
		else
		{
			prev->setNext(new Node_t(at->getValue(), NULL, prev));
			prev = prev->getNext();
		}
		at = at->getNext();
	}
}

List_t::List_t(const List_t& source)
: List_t(&source)
{}

const List_t& List_t::operator=(const List_t* rhs)
{
	if(rhs == this)
	{
		return *this;
	}

	while(head)
	{
		Node_t *temp = head->getNext();
		delete head;
		head = temp;
	}
	size = rhs->size;

	Node_t* at = rhs->head;

	Node_t* prev = NULL;
	while(at)
	{
		if(!head)
		{
			head = new Node_t(at->getValue(), NULL, NULL);
			prev = head;
		}
		else
		{
			prev->setNext(new Node_t(at->getValue(), NULL, prev));
			prev = prev->getNext();
		}
		at = at->getNext();
	}

	return *this;
}

const List_t& List_t::operator=(const List_t& rhs)
{
	return operator=(&rhs);
}


List_t::~List_t()
{
	while(head)
	{
		Node_t *temp = head->getNext();
		delete head;
		head = temp;
	}
}

size_t List_t::getSize() const
{
	return size;
}

bool List_t::insert(int num)
{
	if(find(num))
	{
		return false;
	}
	size++;
	if(!head)
	{
		head = new Node_t(num, NULL, NULL);
	}
	else
	{
		Node_t* newNode = new Node_t(num, head, NULL);
		head->setPrev(newNode);
		head = newNode;
	}
	return true;
}

bool List_t::remove(int num)
{
	Node_t* at = head;
	while(at)
	{
		if(num == at->getValue())
		{
			if(at == head)
			{
				head = at->getNext();
				if(head)
				{
					head->setPrev(NULL);
				}
				delete at;
			}
			else
			{
				Node_t *prev = at->getPrev();
				Node_t *next = at->getNext();
				prev->setNext(next);
				if(next)
				{
					next->setPrev(prev);
				}
				delete at;
			}
			size--;
			return true;
		}
		at = at->getNext();
	}
	return false;
}

bool List_t::find(int num) const
{
	Node_t* at = head;
	while(at)
	{
		if(num == at->getValue())
		{
			return true;
		}
		at = at->getNext();
	}
	return false;
}

string List_t::toString() const
{
	string retval;

	Node_t* at = head;
	while(at)
	{
		retval += at->toString();

		at = at->getNext();

		if(at)
		{
			retval += ", ";
		}
	}

	return retval;
}

Node_t* List_t::getEnd() const
{
	Node_t* at = head;
	while(at)
	{
		if(at->getNext() == NULL)
		{
			return at;
		}
		at = at->getNext();
	}
	return at;
}

ostream& operator<<(ostream& out, const List_t *rhs)
{
	out << rhs->toString();
	return out;
}
ostream& operator<<(ostream& out, const List_t &rhs)
{
	return operator<<(out, &rhs);
}
