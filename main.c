#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char line1[] = "0x0000555555555358 <+17>:    jbe    0x555555555368 <word_to_str_ex+33>\n";
static char line2[] = "0x000055555555536b <+36>:    call   0x55555555520f <hex_to_str>\n";
static char line3[] = "0x00005555555553ad <+45>:    pop    %r12\n";

static char teststr[] = ":::56?:78:89?A B???";

/* more similar to strsep() than strtok() */
static char *my_strtok(char **ptr, char *delim)
{
	if (!ptr || !*ptr || !delim)
		return NULL;

	char *tok = *ptr;
	int tok_len = 0;
	for (int i = 0; (*ptr)[i]; i++)
	{
		for (int j = 0; delim[j]; j++)
		{
			if (delim[j] == (*ptr)[i])
			{
				(*ptr)[i] = 0;
				if (tok_len)
				{
					*ptr = &((*ptr)[i + 1]);
					return tok;
				}
				tok_len--;
				tok++;
				break;
			}
		}
		tok_len++;
	}

	*ptr = NULL;
	return tok;
}

static int eval_line(char *str, char *tag)
{
	char out[1024];
	out[0] = 0;

	/* split from : */
	char *label = my_strtok(&str, ":");
	if (!str)
		return 0;
	char *offset = my_strtok(&label, "<");
	if (!label)
		return 0;
	offset = my_strtok(&label, ">");
	offset[0] = '_';
	strcat(out, tag);
	strcat(out, offset);
	strcat(out, ":");

	/* handle asm code */
	/* split from  < */
	char *asm_code = my_strtok(&str, "<");
	if (str)
	{
		strcat(out, my_strtok(&asm_code, "0"));
		offset = str;
		my_strtok(&str, "+");
		if (str)
		{
			strcat(out, tag);
			strcat(out, "_");
			offset = my_strtok(&str, ">");
			strcat(out, offset);
		}
		else
			strcat(out, my_strtok(&offset, ">"));
		puts(out);
	}
	else
	{
		strcat(out, asm_code);
		printf("%s", out);
	}

	return 1;
}

static void print_file(FILE *fp)
{
	/* for all lines convert */
	char line[1024];
	while (fgets(line, 1024, fp))
		printf("%s", line);

	/* for fancy, only last line important */
	fseek(fp, 0, SEEK_END); // point to END
	ftell(fp);				// bytes from 0 to pointer
	fseek(fp, 0, SEEK_SET); // rewind to START
}

int main(int argc, char *argv[])
{
	if (0 == (argc & 1))
	{
		puts("Incomplete arguments: they must be a <file> <tag> pair.");
		exit(0);
	}

	if (1 == argc)
	{
		puts("No arguments, nothing to do!");
		exit(0);
	}

	puts(".data\n");
	puts(".bss\n");
	puts(".text\n");
	for (int i = 1; i < argc; i += 2)
	{
		FILE *fp = fopen(argv[i], "r");
		if (!fp)
		{
			puts("File doesn't exist!");
			exit(0);
		}

		// print_file(fp);

		/* for all lines convert */
		char line[1024];
		printf(".global %s\n.p2align 4\n.section .text.%s\n%s:\n", argv[i + 1], argv[i + 1], argv[i + 1]);
		while (fgets(line, 1024, fp))
			eval_line(line, argv[i + 1]);

		fclose(fp);
		puts("\n\n");
	}

	puts(".section .note.GNU-stack");
	return 0;
}
