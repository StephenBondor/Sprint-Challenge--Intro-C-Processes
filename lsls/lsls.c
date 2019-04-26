#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

/**
 * Main
 */

char* Concat(const char *s1, const char *s2) // A concatenation function cus 
// AFTER 40 YEARS C STILL HAS NO IDEA HOW TO DO THIS AND IT HURTS ME
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

long long int GetSize(const char *filepath)
{
	struct stat buf;
	int err = stat(filepath, &buf);

	if (err != -1) // if there is no error
	{
		if (S_ISREG(buf.st_mode)) // if the file is a regular file
		{
			return buf.st_size;
		}
		else
		{
			return -1; 
			// directory size is totally inconsistent and error prone, 
			// thus it UNIVERSALLY gets an error code. As there is no point in 
			// trying to sort which size is real. 
		}
	}
	else // ERRORS 
	{
		if (S_ISREG(buf.st_mode)) // if the file is a regular file
		{
			return -2;
		}
		else if (S_ISDIR(buf.st_mode))  // or a directory
		{	
			return -3;
		} 
		else // or something else? Sure, Why not!
		{ 
			return -5;
		}
	}
}

int main(int argc, char **argv)
{
	// Declarations
	struct dirent *ent;
	long long int size;
	char* filepath;

	// Parse command line
	if (argc != 2)
	{
		printf("There are %d command line argument(s). Ya need 2, ya goof- $ ./lsls <path>\n", argc);
		exit(1);
	} 
	if (strcmp(argv[1]+strlen(argv[1])-1, "/") != 0) // User forgot to add a "/" ? Do it for them.
	{
		argv[1] = Concat(argv[1], "/");
	}

	// Open directory
	printf("We gunna look up the path: %s\n", argv[1]);
	DIR *d = opendir(argv[1]);
	if (d == NULL)
	{
		printf("Failed to open directory, GET REKT\n");
		exit(1);
	}

	// Repeatedly read and print entries
	ent = readdir(d);
	while (ent != NULL)
	{
		// Get the size
		filepath = Concat(argv[1], ent->d_name);
		size = GetSize(filepath);

		// Conditional rendering
		if (size == -5)  // The error of all errors
		{
			printf("No one living knows what happend here   %s\n", ent->d_name);
		}
		else if ((size == -3) | (size == -1)) //size call was or wasn't an error, but it's a directory
		{ 
			printf("                                 <DIR>  %s\n", ent->d_name);
		}
		else if (size == -2) //size call was an error, and it's a file
		{ 
			printf("               Error reading file size  %s\n", ent->d_name);
		}
		else // Size call was a success and it's a regular file
		{ 
			printf("               %23llu  %s\n", size, ent->d_name);
		}

		// loop
		ent = readdir(d);
	}

	// Finish executing
	closedir(d);
	free(filepath);

	return 0;
}
