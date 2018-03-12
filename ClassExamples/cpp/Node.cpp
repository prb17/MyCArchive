#include"Node.h"

Node_t::Node_t()
: value(0), next(NULL), prev(NULL)	//Just creation
{
	value = 0;			//Already created
	next = NULL;		//Not assigning
	prev = NULL;
}


Node_t::Node_t(int value, const Node_t* next, const Node_t* prev)
: value(value), next((Node_t *)next), prev((Node_t *)prev)
{
	this->value = value;
	this->next = (Node_t *)next;
	this->prev = (Node_t *)prev;
}

Node_t::Node_t(const Node_t* source)
: value(source->value), next(source->next), prev(source->prev)
{
	value = source->value;
	next = source->next;
	prev = source->prev;
}

Node_t::Node_t(const Node_t& source)
: Node_t(&source)
{
	value = source.value;
	next = source.next;
	prev = source.prev;
}

Node_t::~Node_t()
{}

int Node_t::setValue(int value)
{
	this->value = value;
	return value;
}

Node_t* Node_t::setNext(Node_t *next)
{
	return this->next = next;
}

Node_t* Node_t::setPrev(Node_t *prev)
{
	return this->prev = prev;
}

int Node_t::getValue() const
{
	return value;
}

Node_t* Node_t::getNext() const
{
	return this->next;
}

Node_t* Node_t::getPrev() const
{
	return this->prev;
}

string Node_t::toString() const
{
	string retval;

	char buffer[20];
	sprintf(buffer, "%d", value);

	retval = buffer;
	return retval;
}

ostream& operator<<(ostream& out, const Node_t *rhs)
{
	out << rhs->toString();
	return out;
}

ostream& operator<<(ostream& out, const Node_t &rhs)
{
	return operator<<(out, &rhs);
}
