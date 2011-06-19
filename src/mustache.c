/*
+----------------------------------------------------------------------------+
| CMustache                                                                  |
| Copyright (c) 2011 Adapter Pattern                                         |
| All rights reserved.                                                       |
+----------------------------------------------------------------------------+
| Redistribution and use in source and binary forms, with or without         |
| modification, are permitted provided that the following conditions are met:|
|  - Redistributions of source code must retain the above copyright notice,  |
|    this list of conditions and the following disclaimer.                   |
|  - Redistributions in binary form must reproduce the above copyright       | 
|    notice, this list of conditions and the following disclaimer in the     |
|    documentation and/or other materials provided with the distribution.    |
+----------------------------------------------------------------------------+
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"|
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE  |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE  |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR        |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF       |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS   |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN    |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)    |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE |
| POSSIBILITY OF SUCH DAMAGE.                                                |
+----------------------------------------------------------------------------+
*/
#include "../include/mustache.h"

/* Initialise template node */
struct mustache_template_block *create_mustache_template_node(
	mustache_type *type)
{
	struct mustache_template_block *node = 
		malloc(sizeof(struct mustache_template_block));

	node->type = type;

	return node;
}

/* Open mustache template, adds correct extension if
   missing.
 */
char *mustache_format_tmplate_name (char *filename)
{
	char *template_name;
	size_t template_name_size = strlen(filename) + 1;
	size_t ext_size = strlen(MUSTACHE_TEMPLATE_EXTENSION);
	size_t template_fullname_size = template_name_size;

	int ext = 0;

	if (strstr(filename, MUSTACHE_TEMPLATE_EXTENSION) == NULL)
	{
		template_fullname_size += ext_size;
		ext = 1;
	}

	/* initialize memory for name */
	template_name = (char*) malloc(template_fullname_size);

	if (template_name == NULL)
	{
		return 0;
	}

	memset(template_name, 0, template_fullname_size);

	strncpy(template_name, filename, template_name_size);

	if (ext > 0)
	{
		strncat(template_name, MUSTACHE_TEMPLATE_EXTENSION, ext_size);
	}

	return template_name;
}

/* Similar to the GNU C getline() implementation */
size_t mustache_get_line(char **line_ptr, size_t *n, FILE *stream)
{
	char *buffer_ptr = NULL;
	char *p = buffer_ptr;
	int offset;
	size_t size;
	int c;

	/* Check we have valid input */
	if ((line_ptr == NULL && n == 0) || stream == NULL || n == NULL)
	{
		return (size_t) -1;
	}

	/* Align buffer_ptr to line_ptr input */
	buffer_ptr = *line_ptr;
	size = *n;

	if ((c = fgetc(stream)) == EOF)
	{
		return -1;
	}

	if (buffer_ptr == NULL)
	{
		size = (sizeof(char) * size);
		// Initialize memory for buffer
		buffer_ptr = malloc(size);

		if (buffer_ptr == NULL)
		{
			return -1;
		}
	}

	p = buffer_ptr;

	while (c != EOF)
	{
		offset = p - buffer_ptr;

		if ((p - buffer_ptr) > (--size))
		{
			/* Tripple it to save on expensive realloc calls */
			size = (size * 3);
			buffer_ptr = realloc(buffer_ptr, size);

			if (buffer_ptr == NULL)
			{
				// Out of memory
				return -1;
			}

			/* Prevents p & buffer_ptr becoming detached after memory realloc */
			p = buffer_ptr + offset;
		}

		*p++ = c;

		if (c == '\n')
		{
			break;
		}

		c = fgetc(stream);
	}

	*p++ = '\0';
	*line_ptr = buffer_ptr;
	*n = size;

	return (p - buffer_ptr) - 1;
}

/* Initializes Mustache ready for processing */
int mustache_init(char *filename)
{
	struct mustache_template_block *parsed_template;
	struct mustache_delimiter *delimit;
	FILE *test_mustache;
	mustache_type type;

	if ((filename = mustache_format_tmplate_name(filename)) == NULL)
	{
		fprintf(stderr, "Error: unable to format filename\n\n");
	}

	delimit->open_block = MUSTACHE_DEFAULT_OPEN;
	delimit->close_block = MUSTACHE_DEFAULT_CLOSE;

	test_mustache = fopen(filename, "r");

	if (test_mustache == NULL)
	{
		fprintf(stderr, "Error: unable to open '%s'\n\n", filename);
		return -1;
	}

	fprintf(stderr, "Template '%s' opened successfully!\n\n", filename);


	type = MU_TYPE_ROOT;

	parsed_template = create_mustache_template_node(&type);

	if (parsed_template == NULL)
	{
		fprintf(stderr, "Error: unable to create node! (Out of memory?)");
		fclose(test_mustache);
		return -1;
	}

	/* Begin template tokenization */
	


	fclose(test_mustache);
	fprintf(stderr, "Template '%s' closed!\n\n", filename);

	return 0;
}

