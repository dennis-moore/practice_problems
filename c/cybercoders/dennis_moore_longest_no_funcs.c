#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_LINES 200 //initial column size of 2d array
#define LINE_SIZE 15 //initial word length of each line(column)

// gcc -Wall -pedantic -g dennis_moore_longest.c
// valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./a.out pathtowordsfile(/usr/share/dict/words)
//./a.out /usr/share/dict/words

int main(int argc, char **argv)
{
	// only run if 2 args are passed
	if((argc == 2))
	{
		// open words file passed in from CL
		FILE *in_file = NULL;
		in_file = fopen(argv[1], "r");
		if(in_file == NULL)
		{
			// file failed to open
			fprintf(stderr, "file failed to open: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		// allocate memory to store words and their lengths
		int *char_num_array = (int *) malloc(NUM_LINES * sizeof(int)); // store line sizes(string lengths)
		char **buf = (char **) malloc(NUM_LINES * sizeof(char *)); // store list of strings(words)
		if(char_num_array == NULL || buf == NULL)
		{
			// failed to allocate memory
			fprintf(stderr, "malloc failure\n");
			free(buf);
			free(char_num_array);
			fclose(in_file);
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
				fclose(in_file);
				return EXIT_FAILURE;
			}
		}

		char c;
		int line_count = 0, line_num = 0, char_count = 0, char_num = 0;

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
						buf[line_num][char_num-1] = '\0';
						puts("realloc failure...printing current state");
						break;
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
						puts("realloc failure...printing current state");
						line_num--;
						break;
					}
					line_count = 0;

					int *temp = realloc(char_num_array, (line_num + NUM_LINES) * sizeof(int));
					if(temp)
						char_num_array = temp;
					else
					{
						puts("realloc failure...printing current state");
						line_num--;
						break;
					}
				}

				buf[line_num] = (char *) malloc(LINE_SIZE * sizeof(char)); // create space for the next line		
			}
		}

		// sort values in descending order
		int i, j, swap;
		char *cswap;
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

		// print out the 10 longest lines
		for(i = 0; i <= line_num; i++)
		{
			if(i == 10)
				break;
			puts(buf[i]);
		}
		
		// clean up
		for(i = line_num; i >= 0; i--)
		{
			free(buf[i]);
		}		
		free(buf);
		free(char_num_array);
		fclose(in_file); // close file
	}
	else
	{
		puts("Incorrect number of arguments passed");
	}

	return EXIT_SUCCESS;
}