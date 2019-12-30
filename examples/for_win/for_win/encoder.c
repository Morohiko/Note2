#include "encoder.h"

#include "stdlib.h"
#include <string.h>
#include <stdio.h>

int encode_string(char *src, char *dest) {
	return 0;
}

int decode_string(char *src, char *dest) {
	return 0;
}

int encode_string_by_key(char *key, char *src, char *dest) {
	if (key == NULL || src == NULL || dest == NULL) {
		printf("ERROR: wrong arguments");
		return -1;
	}
	
	char *iter_src = src;
	char *iter_dest = dest;
	char *iter_key = key;
	int i = 0;

	int d = 123;

	
	while (*iter_src) {
		*iter_dest = (unsigned char)*iter_src + (unsigned char)*iter_key;
		//sprintf(*iter_dest, "%c", (*iter_src + *iter_key));
		printf("%c, ", *iter_dest);
		*iter_dest = (unsigned char)*iter_src - (unsigned char)*iter_key;
		//sprintf(*iter_dest, "%c", (*iter_src - *iter_key));

		printf("%c\n", *iter_dest);

		iter_dest++; iter_src++; iter_key++;
		if (!*iter_dest) {
			iter_key = &key[0];
		}
		i++;
	}
	return 0;
}

int decode_string_by_key(char *key, char *src, char *dest) {
	if (key == NULL || src == NULL || dest == NULL || strlen(dest) < strlen(src)) {
		printf("ERROR: wrong arguments");
		return -1;
	}

	char *iter_src = &src[0];
	char *iter_dest = &dest[0];
	char *iter_key = &key[0];

	while (*iter_src) {
		*iter_dest = *iter_src - *iter_key;
		iter_dest++; iter_src++; iter_key++;
		if (!*iter_dest) {
			iter_key = &key[0];
		}
	}
	return 0;
}