#ifndef STRING_H
#define STRING_H
// #include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

// typedef int (*Length)(void *str);
typedef void (*Append)(void *, char *);
typedef void (*Substring)(void *, int, int);

typedef struct _String{
    char *head;
	int size;
	Append append;
	Substring substring;
} String;




int strlength(char *str){
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
	for(int i=0; i<size; i++){
			dest[i] = start[i];
	}
}

// int length(void *str){
// 	String *s = (String *)str;
// 	return strlength(s->head);
// }

void append(void *str, char *addstr){
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = strlength(originalstr);
	int addstrlen = strlength(addstr);
	int newstrlen = originallen+addstrlen;
	char *newhead = (char *)malloc(newstrlen+1);
	memorycopy(newhead, originalstr, originallen);
	memorycopy(newhead+originallen, addstr, newstrlen);
	s->head = newhead;
	s->size = newstrlen;
	free(originalstr);
}

void substring(void *str, int start, int end){// 부분 문자열 시작 인덱스, 마지막 인덱스
	String *s = (String *)str;
	char *originalstr = s->head;
	int originallen = strlength(originalstr);
	int substrlen = end-start+1;
	char *newhead = (char *)malloc(substrlen+1);
	memorycopy(newhead, originalstr+start, substrlen);
	s->head = newhead;
	s->size = substrlen;
	free(originalstr);
}

String *new_string(char *str){
	String s;
	int size = strlength(str); //strlen 직접 구현해보기
	s.head = (char *)malloc(size);
	// memcpy(s.head, str, size+1);
	memorycopy(s.head, str, size+1);
	s.append = append;
	s.substring = substring;
	return &s;
};

void delete_string(String *s){
	free(s->head);
	free(s->append);
	free(s->substring);
	free(s);
};
#endif
