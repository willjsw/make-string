#ifndef STRING_H
#define STRING_H
// #include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void (*Append)(void *, char *);
typedef void (*Substring)(void *, int, int);
typedef void (*Replace)(void *, char *target, char *newstr);
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

int length(char *str){
	int len = 0;
	char* nowchar = str;
	while(true){
		if(*nowchar=='\0'){
			break;
		}
		nowchar++;
		len++;
	}
	return len;
}

void memorycopy(char *dest, char *start, size_t size){
	for(int i=0; i<size+1; i++){
			dest[i] = start[i];
	}
}

void append(void *str, char *addstr){
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = length(originalstr);
	int addstrlen = length(addstr);
	char *newhead = (char *)malloc(originallen+addstrlen+1);
	memorycopy(newhead, originalstr, originallen);
	memorycopy(newhead+originallen, addstr, originallen+addstrlen);
	s->head = newhead;
	free(originalstr);
}

void substring(void *str, int start, int end){// 부분 문자열 시작 인덱스, 마지막 인덱스
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = length(originalstr);
	int substrlen = end-start;
	char *newhead = (char *)malloc(substrlen+1);
	memorycopy(newhead, originalstr+start, substrlen);
	s->head = newhead;
	free(originalstr);
}

void replace(void *str, char *target, char *newstr){ //target을 찾아서 모두 newstr로 바꾸기

}


String newString(char *str){
	String s;
	int size = length(str); //strlen 직접 구현해보기
	s.size = size;
	s.head = (char *)malloc(size);
	// memcpy(s.head, str,size+1);
	memorycopy(s.head, str, size+1);
	s.this = &s;
	s.length = length;
	s.append = append;
	s.substring = substring;
	s.replace = replace;
	return s;
};

#endif

//Class class = new Class();