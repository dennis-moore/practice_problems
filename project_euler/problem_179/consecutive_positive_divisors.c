#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	const unsigned int limit = 10000000;
	unsigned short *num_divisors = calloc((limit + 1), sizeof(unsigned short)); // place on the heap(too large for stack); +1 because i'm starting at 1 instead of 0
	unsigned int i, j;
	unsigned int count = 0;

	// looping from 1 to n and incrementing i*j will give me the number of divisors for each number from 1 to n
	for(i = 1; i <= limit; i++)
	{
		for(j = 1; i*j <= limit; j++)
		{
			num_divisors[i*j]++;
		}
	}

	// loop through and check if n = n + 1
	for(i = 1; i < limit; i++)
	{
		if(num_divisors[i] == num_divisors[i+1])
			count++;
	}

	free(num_divisors);
	printf("%d\n", count);
}