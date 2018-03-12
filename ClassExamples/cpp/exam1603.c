


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
	while(fscanf(fd, "%d", &num) != EOF)
	{
		if(num == 0)
		{
			break;
		}
		if(size == capacity)
		{
			int* temp = (int *)malloc((capacity+1)*2*sizeof(int));
			capacity = (capacity+1) * 2;
			memcpy(temp, numbers, size*sizeof(int));
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


	fclose(fd);
	return 0;
}
