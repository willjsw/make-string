#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdlib.h>

void setup();
typedef void (*IndexOf)(int);
typedef char* (*ToLowerCase)(char*);
typedef char* (*ToUpperCase)(char*);
typedef String* (*New)(char*);

typedef struct _String{
    char *head;
	int size;
	struct _String *this;
	New new;

} String;


String* StringNew(char* str){
	String s;
	s.head = str;
	s.size = strlen(str);
	s.this = &s;
	return &s;
};
   	/*
	- 고정 배열 + 1(마지막 NULL)
	- string->char[] 배열 시작 메모리 주소 받기
	- 시작 포인터 / 배열
	- String 이라는 구조체를 쓰기 위해서는? 해당 멤버들의 함수 포인터들을 초기화 해야함
	*/


#endif
