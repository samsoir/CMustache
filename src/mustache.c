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

struct mustache_delimiter delimiter;

FILE *test_mustache;

/* Initializes Mustache ready for processing */
int mustache_init()
{
	struct mustache_delimiter *delimit;
	char *template_name;
	
	template_name = mustache_format_tmplname("../example/test.mustache");

	delimit = &delimiter;
	delimit->open_block = MUSTACHE_DEFAULT_OPEN;
	delimit->close_block = MUSTACHE_DEFAULT_CLOSE;

	test_mustache = fopen(template_name, "r");

	if (test_mustache == NULL)
	{
		fprintf(stderr, "Error: unable to open '%s'\n\n", template_name);
		fclose(test_mustache);
		return -1;
	}

	// Begin template tokenization

	fclose(test_mustache);
	free(template_name);

	return 0;
}

/* Open mustache template, adds correct extension if
   missing.
 */
char * mustache_format_tmplname (char *filename)
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
	memset(template_name, 0, template_fullname_size);

	strncpy(template_name, filename, template_name_size);

	if (ext > 0)
	{
		strncat(template_name, MUSTACHE_TEMPLATE_EXTENSION, ext_size);
	}

	return template_name;
}
