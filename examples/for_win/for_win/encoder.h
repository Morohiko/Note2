#pragma once
#define _CRT_SECURE_NO_WARNINGS

int encode_string(char *src, char *dest);
int decode_string(char *src, char *dest);

int encode_string_by_key(char *key, char *src, char *dest);
int decode_string_by_key(char *key, char *src, char *dest);