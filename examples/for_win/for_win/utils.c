#include "utils.h"
#include <string.h>
#include <stdio.h>

#include <time.h>

int get_string_date_time(char *datetime) {
	if (datetime == NULL) {
		printf("ERROR: datetime == NULL");
		return -1;
	}

	if (strlen(datetime) < SIZE_DATE_TIME + 1) {
		printf("ERROR: datetime to small strlen(datetime) = %zu", strlen(datetime));
		return -1;
	}

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(datetime, "%d:%d:%d:%d:%d:%d:",
		(tm.tm_year + 1900), tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 0;
}