#ifndef STRING_H
#define STRING_H
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char *(*Append)(char*);
typedef char *(*Substring)(char*);
typedef char *(*Replace)(char*);
typedef int (*Length)(char *);



typedef struct _String{
    char *head;
	int size;
	struct _String *this;
	Substring substring;
	Append append;
	Replace replace;
	Length length;
}String;

int stringlength(char *str){
	int len = 0;
	char* nowchar = str;
	while(true){
		if(*nowchar=='\0'){
			break;
		}
		nowchar++;
		len++;
	}
	return len+1;
}

void memorycopy(char *dest, char *start, size_t size){
	for(int i=0; i<size+1; i++){
			dest[i] = start[i];
	}
}

String newString(char* str){
	String s;
	int size = stringlength(str); //strlen 직접 구현
	s.size = size;
	s.head = (char *)malloc(size);
	// memcpy(&s.head, &str,size);
	memorycopy(s.head, str, size);
	s.this = &s;
	return s;
};

#endif

//Class class = new Class();
//class 메모리 확보 후 포인터 넘겨주는 것