void defaultHash();
int basic_hash();

class hash
{

	hash()
	: buckets(10), f(defaultHash)
	{}
//	vector<vector<unsigned int>> buckets(10);

	hash()
	: buckets(10, vector<unsigned int>(3,4))
	{}
//	vector<vector<unsigned int>> buckets(10, 
//	vector<unsigned int>(3,4));


	hash(size_t num)
	{}


	hash(size_t num, int(*y)(int))
	: f(y)
	{
		f = y;
	}

	size_t size()
	{
		return _size;
		size_t retval = 0;
		for(size_t i=0; i<buckets.size(); i++)
		{
			retval += buckets[i].size();
		}
		return retval;
	}

	vector<vector<unsigned int>> buckets;
	int(*f)(int);
	size_t _size;
}


void defaultHash()
{
	..
}
int basic_hash();
