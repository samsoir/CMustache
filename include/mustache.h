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
#ifndef __MUSTACHE_H__
#define __MUSTACHE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

/* Handles non-POSIX clients */
#ifndef LINE_MAX
#define LINE_MAX                    2048
#endif

/* Mustache tokens */
#define MUSTACHE_ESCAPE_CHARACTER   "="
#define MUSTACHE_BLOCK_VALID_OPEN   "#"
#define MUSTACHE_BLOCK_INVALID_OPEN "^"
#define MUSTACHE_BLOCK_CLOSE        "/"
#define MUSTACHE_COMMENT            "!"
#define MUSTACHE_PARTIAL            ">"

#define MUSTACHE_DEFAULT_OPEN       "{{"
#define MUSTACHE_DEFAULT_CLOSE      "}}"

#define MUSTACHE_TEMPLATE_EXTENSION ".mustache"

/* Type of mustache block */
typedef enum _mustache_type {
	MU_TYPE_ROOT,
	MU_TYPE_BLOCK_TEXT,
	MU_TYPE_BLOCK_VARIABLE,
	MU_TYPE_BLOCK_VALID,
	MU_TYPE_BLOCK_INVALID,
	MU_TYPE_COMMENT,
	MU_TYPE_PARTIAL
} mustache_type;

/* Contains the mustache delimeters */
struct mustache_delimiter {

	char *open_block;
	char *close_block;
};

/* Mustache block */
struct mustache_template_block {
	/* Pointer back to root block */
	struct mustache_template_block *root;
	struct mustache_template_block *next;

	/* Properties */
	char *key;
	char *value;
	mustache_type *type;

	struct mustache_template_block *parent;
	struct mustache_template_block *child;
};

char *mustache_format_tmplate_name (char *filename);
struct mustache_template_block *create_mustache_template_node(
	mustache_type *type);
size_t mustache_get_line(char **line_ptr, size_t *n, FILE *stream);
int mustache_init(char *filename);

#endif /* __MUSTACHE_H__ */