#include "file.h"
#include "utils.h"
#include "encoder.h"

#include "stdlib.h"
#include "stdio.h"

void test_write_to_end_file() {
	char *path = "D:\\projs\\note2\\test.txt";
	char text[100] = "text";
	while (1) {
		scanf("%s", &text);

		write_to_end_file(path, text);
	}
	printf("text = %s\n", text);

}

void test_get_date_time() {
	char buff[100];

	get_string_date_time(&buff[0]);
	printf("strlen = %zu buff = %s", strlen(buff), buff);

}

void test_encode_decode() {
	char *key = "key";
	char src[20] = "somesource123";
	char dest[20] = "0";
	printf("key: %s, src: %s, dest: %s\n", key, src, dest);
	encode_string_by_key(key, src, dest);

	printf("key: %s, src: %s, dest: %s\n", key, src, dest);
	decode_string_by_key(key, dest, src);

	printf("key: %s, src: %s, dest: %s\n", key, src, dest);
}

void simple_test() {
	char c = 'a';
	char *p = &c;
	*p = *p + 1;
	printf("%c", *p);
}

int main() {
	printf("hello\n");
	//test_write_to_end_file();
	//test_get_date_time();
	//test_encode_decode();
	simple_test();
	system("pause");
	return 0;
}