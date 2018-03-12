#include"Node.h"

#include<string.h>

Node_t::Node_t()
: value(0), next(NULL)	//defines at creation time
{
						//value/next already created
	value = 0;			//assign value/next
	next = NULL;
}

Node_t::Node_t(int value, Node_t* next)
: value(value), next(next)
{
	this->value = value;
	this->next = next;
}

Node_t::Node_t(const Node_t* source)
: value(source->value), next(source->next)
{
	value = source->value;
	next = source->next;
}

// x->y 		(*x).y

Node_t::Node_t(const Node_t& source)
: Node_t(&source)
{}

Node_t::~Node_t()
{}

int Node_t::getValue() const
{
	return value;
}

Node_t* Node_t::getNext() const
{
	return next;
}

int Node_t::setValue(int value)
{
	this->value = value;
	return value;
}

Node_t* Node_t::setNext(Node_t* next)
{
	return this->next = next;
}

string Node_t::toString() const
{
	string retval;
	counter++;

	char *buffer = (char *)malloc(20 * sizeof(char));

	sprintf(buffer, "%d", value);

	for(size_t i=0; i<strlen(buffer); i++)
	{
		retval += buffer[i];
	}

	free(buffer);
	return retval;
}

ostream& operator<<(ostream& out, const Node_t* rhs)
{
	out << rhs->toString();
	return out;
}
ostream& operator<<(ostream& out, const Node_t& rhs)
{
	return operator<<(out, &rhs);
}


/*
const int& operator+=(int& lhs, const int& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}
*/
/*
x = y = 3;
x = (y = 3);	-> x = 3
	x = y

x = 3
y = 2
x += y += 3
x += y, where y is now 5
x is now 8

const int x;
int y;
const int z;

const int *ptr = &y;	//Pointing to constant ints
	*(ptr + 1) = 10;

int const *ptr;			//Points to ints, pointer is constant

int x[10];
int const *x -> 10 ints;
*/
