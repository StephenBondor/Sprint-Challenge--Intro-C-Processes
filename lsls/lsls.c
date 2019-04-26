#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

/**
 * Main
 */

long long int GetSize(const char *filepath)
{
	struct stat buf;
	stat(filepath, &buf);

	if (S_ISDIR(buf.st_mode))
	{
		printf("<DIR>");
		return 0;
	}
	else
	{
		if (stat(filepath, &buf) == -1)
		{
			return -1;
		}
		return buf.st_size;
	}
}

// (int argc, char **argv)
int main(int argc, char **argv)
{
	struct dirent *ent;

	// Parse command line
	if (argc < 2)
	{
		printf("There are %d command line argument(s). Ya need mo than 2, ya goof\n", argc);
		exit(1);
	}
	printf("the argument that was accepted: %s\n", argv[1]);

	// Open directory
	DIR *d = opendir(argv[1]);
	if (d == NULL)
	{
		printf("GET REKT");
		exit(1);
	}

	// Repeatedly read and print entries
	ent = readdir(d);
	while (ent != NULL)
	{
		printf("%20lli   %s\n", GetSize(ent->d_name), ent->d_name);
		ent = readdir(d);
	}

	// Close directory
	closedir(d);

	return 0;
}
