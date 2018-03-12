#include"List.h"

List_t::List_t()
: head(NULL), size(0)
{}

List_t::List_t(const List_t* source)
: head(NULL), size(source->size)
{
	Node_t *at = source->head;
	/*while(at)
	{
		insert(at->getValue());
		at = at->getNext();
	}*/
	Node_t *previous = NULL;
	while(at)
	{
		if(!head)
		{
			head = new Node_t(at->getValue(), NULL);
			previous = head;
		}
		else
		{
			previous->setNext(new Node_t(at->getValue(), NULL));
			previous = previous->getNext();
		}
		at = at->getNext();
	}
}

List_t::List_t(const List_t& source)
: List_t(&source)
{}

List_t::~List_t()
{
	while(head)
	{
		Node_t *next = head->getNext();
		delete head;
		head = next;
	}
}


const List_t& List_t::operator=(const List_t& rhs)
{
	return operator=(&rhs);
}
const List_t& List_t::operator=(const List_t* rhs)
{
	if(this == rhs)
	{
		return *this;
	}
/*	while(size != 0)
	{
		remove(head->getValue());
	}*/
	while(head)
	{
		Node_t *next = head->getNext();
		delete head;
		head = next;
	}
	size = rhs->size;

	Node_t *at = rhs->head;
	Node_t *previous = NULL;
	while(at)
	{
		if(!head)
		{
			head = new Node_t(at->getValue(), NULL);
			previous = head;
		}
		else
		{
			previous->setNext(new Node_t(at->getValue(), NULL));
			previous = previous->getNext();
		}
		at = at->getNext();
	}
	return *this;
}


size_t List_t::getSize() const
{
	return size;
}

bool List_t::insert(int data)
{
	if(find(data))
	{
		return false;
	}

	size++;
	if(!head)
	{
		head = new Node_t(data, NULL);
	}
	else
	{
		Node_t *newNode = new Node_t(data, head);
		head = newNode;
	}
	return true;
}

bool List_t::find(int data) const
{
	Node_t *cur = head;
	while(cur)
	{
		if(cur->getValue() == data)
		{
			return true;
		}
		cur = cur->getNext();
	}
	return false;
}

bool List_t::remove(int data)
{
	Node_t *cur = head;
	Node_t *previous = NULL;
	while(cur)
	{
		if(cur->getValue() == data)
		{
			size--;
			if(head == cur)
			{
				head = cur->getNext();
			}
			else
			{
				previous->setNext(cur->getNext());
			}
			delete cur;
			return true;
		}
		previous = cur;
		cur = cur->getNext();
	}
	return false;
}

string List_t::toString() const
{
	string retval;

	Node_t *at = head;
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

ostream& operator<<(ostream& out, const List_t* rhs)
{
	out << rhs->toString();
	return out;
}
ostream& operator<<(ostream& out, const List_t& rhs)
{
	return operator<<(out, &rhs);
}
