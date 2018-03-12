#include<stdio.h>
#include<stdlib.h>

void function(int num);



void function(int num)
{
	//Deliberately left uninitialized.
	int value = 0;

	fprintf(stdout, "Old value: %d\n", value);

	value = num;

	fprintf(stdout, "New value: %d\n", value);

}


int main(int argc, char **argv)
{
	function(5);
	fprintf(stdout,"Sea Cucumber\n");
	function(10);

	return 0;
}
