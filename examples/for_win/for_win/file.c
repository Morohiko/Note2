#include "file.h"

#include <stdio.h>

static int cfileexists(const char * filename) {
	FILE *file;
	if (file = fopen(filename, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

int write_to_end_file(char *path, char *text) {
	if (path == NULL) {
		printf("ERROR: path is null");
		return -1;
	}
	if (text == NULL) {
		printf("ERROR: text is null");
		return -1;
	}

	if (!cfileexists(path)) {
		printf("ERROR: file with path %s not exist", path);
		return -1;
	}

	FILE *fd = NULL;
	fd = fopen(path, "a");
	if (!fd) {
		printf("ERROR: cannot open file");
		return -1;
	}

	if (!fprintf(fd, "%s", text)) {
		printf("ERROR: cannot write to file ");
		fclose(fd);
		return -1;
	}

	if (fclose(fd)) {
		printf("ERROR, cannot close file %s", path);
		return -1;
	}
	printf("path = %s, text = %s", path, text);

	return 0;
}