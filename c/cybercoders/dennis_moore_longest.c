#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LINES 200 //initial column size of 2d array
#define LINE_SIZE 15 //initial word length of each line(column)

// not really reusable functions(tightly coupled with global vars), but done to make the code more readable
int allocate_mem();
int read_file_to_array();
void sort_descending();
void print_words(int n);
void clean_up();

// global vars(these could be passed around, but I made them global to make the code simpler and more readable)
int line_num = 0; // number of lines(words) in word file
int *char_num_array = NULL;
char **buf = NULL;
FILE *in_file = NULL;

// gcc -Wall -pedantic -g dennis_moore_longest.c
// valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./a.out pathtowordsfile(/usr/share/dict/words)
//./a.out /usr/share/dict/words

int main(int argc, char **argv)
{
	// only run if 2 args are passed
	if((argc == 2))
	{
		// open words file passed in from CL
		in_file = fopen(argv[1], "r");
		if(in_file == NULL)
		{
			// file failed to open
			fprintf(stderr, "file failed to open: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		// allocate memory to store words and their lengths
		int rc = allocate_mem();
		if(rc == EXIT_FAILURE)
		{
			//failed to allocate memory, close file and exit process
			fclose(in_file);
			return EXIT_FAILURE;
		}

		// read in word file to 2d array
		rc = read_file_to_array();
		if(rc == EXIT_FAILURE)
		{
			//realloc failure, clean up and exit process
			clean_up();
			return EXIT_FAILURE;
		}

		// sort values in descending order
		sort_descending();

		// print out the 10 longest lines
		print_words(10);
		
		// clean up
		clean_up();
	}
	else
	{
		puts("Incorrect number of arguments passed");
	}

	return EXIT_SUCCESS;
}

int allocate_mem()
{
	char_num_array = (int *) malloc(NUM_LINES * sizeof(int)); // store line sizes(string lengths)
	buf = (char **) malloc(NUM_LINES * sizeof(char *)); // store list of strings(words)
	if(char_num_array == NULL || buf == NULL)
	{
		// failed to allocate memory
		fprintf(stderr, "malloc failure\n");
		free(buf);
		free(char_num_array);
		return EXIT_FAILURE;
	}
	else
	{
		buf[0] = (char *) malloc(LINE_SIZE * sizeof(char)); // allocate memory for first word
		if(buf[0] == NULL)
		{
			fprintf(stderr, "malloc failure\n");
			free(buf);
			free(char_num_array);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int read_file_to_array()
{
	char c;
	int line_count = 0, char_count = 0, char_num = 0;

	// read words into array
	while((c = getc(in_file)) != EOF) // read chars until end of file is reached
	{
		if(c != '\n')
		{
			buf[line_num][char_num] = c;
			char_num++;
			char_count++;

			if(char_count == LINE_SIZE) //line is too long, allocate more space
			{
				char *tmp = realloc(buf[line_num], (char_num + LINE_SIZE) * sizeof(char));
				if(tmp)
					buf[line_num] = tmp;
				else
				{
					fprintf(stderr, "realloc failure\n");
					return EXIT_FAILURE;
				}
				char_count = 0;
			}
		}
		else //newline
		{
			buf[line_num][char_num] = '\0'; // add null char to end of char array
			char_num_array[line_num] = char_num; // store line(word) length for later use

			char_num = char_count = 0;
			line_num++;
			line_count++;

			if(line_count == NUM_LINES) //too many lines in file, allocate more space
			{
				char **tmp = realloc(buf, (line_num + NUM_LINES) * sizeof(char *));
				if(tmp)
					buf = tmp;
				else
				{
					fprintf(stderr, "realloc failure\n");
					line_num--;
					return EXIT_FAILURE;
				}
				line_count = 0;

				int *temp = realloc(char_num_array, (line_num + NUM_LINES) * sizeof(int));
				if(temp)
					char_num_array = temp;
				else
				{
					fprintf(stderr, "realloc failure\n");
					line_num--;
					return EXIT_FAILURE;
				}
			}

			buf[line_num] = (char *) malloc(LINE_SIZE * sizeof(char)); // create space for the next line		
		}
	}

	return EXIT_SUCCESS;
}

void sort_descending()
{
	int i, j, swap = 0;
	char *cswap = NULL;
	for(i = 0; i <= line_num; i++)
	{
		for(j = i + 1; j <= line_num; j++)
		{
			if(char_num_array[i] < char_num_array[j]) // keep an array of lengths so I don't need to call strlen
			{
				// swap word lengths in array so that indices match(alternatively I could use strlen)
				swap = char_num_array[i];
				char_num_array[i] = char_num_array[j];
				char_num_array[j] = swap;

				cswap = buf[i];
				buf[i] = buf[j];
				buf[j] = cswap;
			}
		}
	}
}

void print_words(int n)
{
	// print out the n longest words
	for(int i = 0; i <= line_num; i++) // compare to line_num for the case where line_num(# of words in file) is less than 10
	{
		if(i == n)
			break;
		puts(buf[i]);
	}
}

void clean_up()
{
	for(int i = line_num; i >= 0; i--)
	{
		free(buf[i]);
	}		
	free(buf);
	free(char_num_array);
	fclose(in_file); // close file
}