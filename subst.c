#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table_entry {
	size_t keysize;
	char *key;
	char *value;
};

char *readfile(const char *filename)
{
	size_t size;
	char *buffer;
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("Failed to open '%s'!\n", filename);
		exit(1);
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	
	buffer = malloc(size);

	fread(buffer, size, 1, file);
	

	fclose(file);
	return buffer;
}

void print_help()
{
	// TODO: implement help
}

void putchar_in_output(char c)
{
	putchar(c);
	fflush(stdout);
}

int main(int argc, char *argv[])
{
	size_t i;
	size_t table_counter = 0;
	struct table_entry *table = malloc((argc - 2) / 3 * sizeof(struct table_entry));
	char *infile;
	char *ident_begin;
	char *table_str;
	size_t ident_len;

	if (argc < 2) {
		printf("No input file was specified\n");
		exit(1);
	}
	
	infile = readfile(argv[1]);
	
	for (i = 2; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch(argv[i][1]) {
			case 'd':
				if (i++ == argc) {
					printf("supplied not enough arguments\n");
				}
				table[table_counter].keysize = strlen(argv[i]);
				table[table_counter].key = argv[i];
				i++;
				table[table_counter].value = argv[i];
				table_counter++;
				break;
			case 'f':
				if (i++ == argc) {
					printf("supplied not enough arguments\n");
				}
				table[table_counter].keysize = strlen(argv[i]);
				table[table_counter].key = argv[i];
				i++;
				table[table_counter].value = readfile(argv[i]);
				table_counter++;
				break;
			case 'h':
				print_help();
				return 0;
			}
		}

	}

	while (*infile) {
		if (!(*infile == '$' && infile[1] == '{')) {
			putchar_in_output(*infile);
			infile++;
			continue;
		}
		infile += 2;
		ident_begin = infile;
		ident_len = 0;
		while (*infile != '}') {
			if (*infile == 0x00) {
				printf("Unclosed variable refrence!\n");
				exit(1);
			}
			infile++;
			ident_len++;
		}
		for (i = 0; i < table_counter; i++) {
			if (table[i].keysize != ident_len)
				continue;
			if (strncmp(table[i].key, ident_begin, ident_len) != 0)
				continue;
			table_str = table[i].value;
			while (*table_str)
				putchar_in_output(*table_str++);
		}

		infile++;
	}

	return 0;
}
