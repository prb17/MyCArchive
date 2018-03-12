#include<stdio.h>
#include<stdlib.h>

struct BigThing_t;
int func(struct BigThing_t *container, int inc);
struct BigThing_t copier(struct BigThing_t *source);
void printThing(struct BigThing_t source, FILE* output, int a, int b, int c, int d, int e, int f, int g);

struct BigThing_t
{
	long long nums[4];
};

int main(int argc, char **argv)
{
	struct BigThing_t data = {{1,2,3,4}};

	int value = func(&data, 2);

	struct BigThing_t copy = copier(&data);

	fprintf(stdout, "Result of func: %d\n", value);
	printThing(copy, stdout, 1, 2, 3, 4, 5, 6, 7);
	return 0;
}

int func(struct BigThing_t *container, int inc)
{
	container->nums[0] += inc;
	container->nums[1] += inc;
	container->nums[2] += inc;
	container->nums[3] += inc;
	return 4 * inc;
}

struct BigThing_t copier(struct BigThing_t *source)
{
	struct BigThing_t retval;
	for(int i=0; i<4; i++)
	{
		retval.nums[i] = source->nums[i];
	}
	return retval;
}

void printThing(struct BigThing_t source, FILE* output, int a, int b, int c, int d, int e, int f, int g)
{
	fprintf(output, "%lld, %lld, %lld, %lld\n", source.nums[0], source.nums[1], source.nums[2], source.nums[3]);
}

