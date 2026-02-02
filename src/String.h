#ifndef STRING_H
#define STRING_H
// #include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

// typedef int (*Length)(void *str);
typedef void (*Append)(void *, char *);
typedef void (*Substring)(void *, size_t, size_t);

typedef struct _String{
    char *head;
	int size;
	Append append;
	Substring substring;
} String;




size_t strlength(const char *str){
	size_t len = 0;
	const char* nowchar = str;
	while(true){
		if(*nowchar=='\0'){
			break;
		}
		nowchar++;
		len++;
	}
	return len;
}

void memorycopy(char *dest, const char *start, size_t size){
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
	size_t originallen = strlength(originalstr);
	size_t addstrlen = strlength(addstr);
	size_t newstrlen = originallen+addstrlen;
	char *newhead = (char *)malloc(newstrlen+1);
	memorycopy(newhead, originalstr, originallen);
	memorycopy(newhead+originallen, addstr, newstrlen);
	s->head = newhead;
	s->size = newstrlen;
	free(originalstr);
}

void substring(void *str, size_t start, size_t end){// 부분 문자열 시작 인덱스, 마지막 인덱스
	String *s = (String *)str;
	char *originalstr = s->head;
	size_t originallen = strlength(originalstr);
	size_t substrlen = end-start+1;
	char *newhead = (char *)malloc(substrlen+1);
	memorycopy(newhead, originalstr+start, substrlen);
	s->head = newhead;
	s->size = substrlen;
	free(originalstr);
}

String* new_string(const char *str){
	String* s = (String *)malloc(sizeof(String));
	size_t size = strlength(str); //strlen 직접 구현해보기
	s->head = (char *)malloc(size+1);
	// memcpy(s.head, str, size+1);
	memorycopy(s->head, str, size+1);
	s->append = append;
	s->substring = substring;
	return s;
};

void delete_string(String *s){
	if(s!=NULL){
		if(s->head!=NULL) free(s->head);
		free(s);
	}
	
};
#endif
