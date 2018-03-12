

struct Node* createNode()
{
	struct Node* retval = (struct Node*)malloc(sizeof(struct Node));
	retval->value = 0;
	return retval;
}


struct Node* createNodeInt(int value)
{
	struct Node* retval = (struct Node*)malloc(sizeof(struct Node));
	retval->value = value;
	return retval;
}

struct Node* createNodeCopy(struct Node* other)
{
	struct Node* retval = (struct Node*)malloc(sizeof(struct Node));
	retval->value = other->value;
	return retval;
}

struct Node* destroyNode(struct Node* it)
{
	free(it);
	return NULL;
}


void setValue(struct Node* this, int value)
{
	this->value = value;
}


int getValue(struct Node* this)
{
	return this->value;
}


/*
cout << setw(10) << i << setw(0);

printf("%10i"

print "%d" % i
*/
