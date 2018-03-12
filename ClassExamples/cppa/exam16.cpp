Object_t& operator+(const Object_t* this, const Object_t & rhs);


ostream& operator<<(ostream& out, const Object_t &rhs)



1 + (3 + 5)
1 + 8




pipefd[0], pipefd[1]

fork()
	//child upper block
		//array of strings
		//close standard in
		//replace standard in with pipe[0];
		//close writing end of pipe
		//Become someone else

	//parent lower block
		//close reading end of pipe
		//Parent can write to the pipe
		write(pipefd[1], "message to read end")



int main(int argc, char** argv)
{
	FILE* fd = fopen(argv[1], "r");
	if(fd == NULL)
	{
		handleError(errno);
	}

	int* numbers = NULL;
	size_t size = 0;
	size_t capacity = 0;

	int num = 0;
	while(fscanf(fd, "%d", &num) != -1)
	{
		if(num == 0)
		{
			break;
		}

		if(size == capacity)
		{
			capacity = (capacity+1) * 2;
			int* temp = (int *)malloc(capacity * sizeof(int));
			memcpy(temp, numbers, size * sizeof(int));
			free(numbers);
			numbers = temp;
		}

		numbers[size] = num;
		size++;
	}

	int sum = 0;
	for(size_t i=0; i<size; i++)
	{
		sum += numbers[i];
	}
	fprintf(stdout, "%d\n", sum);
	free(numbers);
	numbers = NULL;
	fclose(fd);
	return 0;
}



int main(int argc, char ** argv)
{
	int y = 3; //rbp-8
	int z = 4; //rbp-4
	z += y;
	y = func(z);

//	edx = z;			3rd
//	esi = eax = y		2nd
//	edi = "%d, %d\n"
	printf("%d, %d\n", y, z);

	//edi = eax = y; 1st
	z = func(y);

//	edx = z
//	esi = y
//	edi = "...";
	printf("%d, %d\n", y, z);
	return 0;
}
