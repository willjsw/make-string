#ifndef STRING_H
#define STRING_H
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
	return len;
}

void memorycopy(char *dest, char *start, size_t size){
	for(int i=0; i<size+1; i++){
			dest[i] = start[i];
	}
}

void stringappend(void *str, char *addstr){
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = stringlength(originalstr);
	int addstrlen = stringlength(addstr);
	char *newhead = (char *)malloc(originallen+addstrlen+1);
	memorycopy(newhead, originalstr, originallen);
	memorycopy(newhead+originallen, addstr, originallen+addstrlen);
	s->head = newhead;
	free(originalstr);
}

void stringsubstring(void *str, int start, int end){// 부분 문자열 시작 인덱스, 마지막 인덱스
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = stringlength(originalstr);
	int substrlen = end-start;
	char *newhead = (char *)malloc(substrlen+1);
	memorycopy(newhead, originalstr+start, substrlen);
	s->head = newhead;
	free(originalstr);
}

void stringreplace(void *str, char *target, char *newstr){ //target을 찾아서 모두 newstr로 바꾸기

}


String newString(char *str){
	String s;
	int size = stringlength(str)+1; //strlen 직접 구현해보기
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