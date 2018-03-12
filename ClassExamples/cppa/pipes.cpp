void ExecutionPair::execute()
{
	int pipe1to2[2];
	int pipe2to1[2];

	pipe(pipe1to2);
	pipe(pipe2to1);


	if(fork() == 0)
	{
		if(in1 == 3)
		{
			dup2(pipe2to1[0], STDIN_FILENO);
		}
		if(out1 == 2)
		{
			dup2(pipe1to2[1], STDOUT_FILENO);
		}

		close(pipe1to2[0]);
		close(pipe1to2[1]);
		close(pipe2to1[0]);
		close(pipe2to1[1]);
		char **argv = cmd[0].getArgs();
		execvp(argv[0], argv);
		perror("Execvp failed");

		size_t idx = 0;
		while(argv[idx])
		{
			free(argv[idx]);
			idx++;
		}
		free(argv);
		//clean up anything allocations

		exit(errno);
	}

	if(fork() == 0)
	{

		exit(errno);
	}


	close(pipe1to2[0]);
	close(pipe1to2[1]);
	close(pipe2to1[0]);
	close(pipe2to1[1]);
}


int fd = open()
unsigned short x;
read(fd, &x, 2);

foreach(i=0..x)
{
	unsigned char commModel;
	read(fd, &commModel, 1);
	int sizeA, sizeB;
	read(fd, &sizeA, 4);
	read(fd, &sizeB, 4);
}
