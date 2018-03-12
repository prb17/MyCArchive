#include<stddef.h>

ptrdiff_t diff = (char *)&nums[3] - (char *)&object;
	//24 decimal, 0x18

0x00007fff fffff000 $rsp/$rbp
sub 0x50, $rsp

0x00007fff ffffefa0 $rsp

[nums[0]]	0x0-0x3	abcd
[nums[1]]	0x4-0x7	edfg
[nums[2]]	0x8-0xb	hijk
[nums[3]]	0xc-0xf	lmno
[nums[4]]	0x10-0x13	pqrs
*[length]	0x14-0x17	tuv\0
[word]		0x18-0x1f


char *ptr = &(struct Data.word)
ptr -= 0x18
struct Data *goal = (struct Data *)ptr;

obj->word = (char *)obj;
fscanf(stdin, "%s", obj)

struct Data* constructData2(int wordSize)
{
	struct Data* retval = (struct Data*)
		malloc(sizeof(struct Data));
	for(int i=0; i<5; i++)
	{
		retval->nums[i] = 0;
	}
	retval->length = wordSize;
	retval->word = (char *)
		malloc(wordSize * sizeof(char));
	return retval;
}



myData = struct Data
	nums -> [0->10, 0, 0, 0, 0]
	length = 10
	word = malloc(10)
ptr = &myData.word

someFunc(ptr = &myData.word, value = 10)
{
	ptr -= 0x18;
	int *change = (int *)ptr;
	*change = value;
}

a)	(int *)(0x2050)
	(int * 0x2050) + 2
	(int * 0x2058)
	(int *** 0x2058)

c)
&ptr = 0x2028
ptr = 0x2028
ptr[2] -> *(ptr + 2)
			*(ptr + 2 * sizeof(int))
			*(0x2028 + 8)
			*(0x2030)
		0x2020

d) *(int *)x		-> *0x2020 -> 0x2018

e) &array[0] = 0x2020, &array[1] = 0x2024

f) ***(int *ptr = 0x2028)
	**(int ptr = 0x2028)
	error, can't dereference non-pointer
(char ***)ptr;

d)	(&ptr) -> (int ** 0x3030)
//	no cast: (int ** 0x3038)
			(int * 0x3030) + 1
			(int * 0x3034)
			(int *** 0x3034)
	***(0x3034)
	**(0x3028)
	*(0x3010)
	0x8


f)	&*x		fails, can't dereference non-pointer
	*&x		x


00000000001
11111111110

//returns char* of size
char* makeArray(size_t size)
{
	//
}

//Returns corrected Node.
struct Node* fixNode(struct Node* it)
{
	//return 1 is it has LSB as 1.
	if(it is odd)
	{
		return it - 1;
	}
	return it;
	return it & ~0x1;
}

int needFix(struct Node* it)
{
	return it & 0x1;
}

void insert(struct List* list, int value)
{
	struct Node* at = list->head;
	struct Node* prev = NULL;

	if(at == NULL)
	{
		list->head = newNode();
		return;
	}

	while(at != NULL)
	{
		if(needFix(at))
		{
			struct Node* actual = fixNode(at);
			actual->data = value;


			if(prev == NULL)
			{
				list->head = actual;
			}
			else
			{
				prev->next = actual;
			}
			return;
		}
			
		prev = at;
		at = at->next;
	}
	prev->next = newNode();
}

int remove(struct List*list, int value)
{
	struct Node* prev = NULL;
	struct Node* at = list->head;

	int retval = 0;
	while(at != NULL)
	{
		if(!fixNode(at))
		{
			//check
			if(at->data == value)
			{
				retval++;
				prev->next = prev->next | 0x1;
			}
		}

		prev = fixNode(at);
		at = fixNode(at)->next;
	}
	return retval;

}



	0001010101
|	0011110000
	----------
	0011110101

exit(2);
return 0;
