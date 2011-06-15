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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Buffer size maximum */
#define MUSTACHE_MAX_BUFFER         10000

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

int mustache_init();
char * mustache_format_tmplname (char *filename);

/* Contains the mustache delimeters */
struct mustache_delimiter {

	char *open_block;
	char *close_block;
};

/* Type of mustache block */
typedef enum mustache_type {
	MU_TYPE_BLOCK_VALID,
	MU_TYPE_BLOCK_INVALID,
	MU_TYPE_COMMENT,
	MU_TYPE_PARTIAL
} mustache_type;

/* Hash node */
struct mustache_hash_value_node {
	/* Pointer back to root node */
	struct mustache_hash_value_node *root;

	/* Properties */
	char *key;
	char *value;

	/* Child nodes */
	size_t num_child_nodes;
	struct mustache_hash_value_node **nodes;
};

/* Mustache block */
struct mustache_template_block {
	/* Pointer back to root block */
	struct mustache_template_block *root;

	/* Properties */
	char *key;
	char *value;
	mustache_type *type;

	/* Child blocks */
	size_t num_child_blocks;
	struct mustache_template_block **blocks;
};