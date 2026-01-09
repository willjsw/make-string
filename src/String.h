#ifndef STRING_H
#define STRING_H
// #include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*Length)(void *str);
typedef void (*Append)(void *, char *);
typedef void (*Substring)(void *, int, int);
typedef void (*Replace)(void *, char *target, char *newstr);
// typedef void (*ToLowerCase)(void *str);
// typedef void (*ToUpperCase)(void *str);


typedef struct _String{
    char *head;
	struct _String *this;
	Length length;
	Append append;
	Substring substring;
	Replace replace;
}String;


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

int length(void *str){
	String *s = (String *)str;
	return strlength(s->head);
}

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
	free(originalstr);
}

void replace(void *str, char *target, char *newstr){ //target을 찾아서 모두 newstr로 바꾸기
	// String *s = (String *)str;
	// char *originalstr = s->head;
	// int originallen = length(originalstr);
	// int newstrlen = length(newstr);
	// //kmp

	// for(int i=0; i<originallen; i++){
	// 	int cnt = 0;
	// 	for(int j=0; j<newstrlen; j++){
	// 		if(originalstr+(i*newstrlen)+j==newstr[j]){
	// 			cnt++;
	// 		}else{
	// 			break;
	// 		}
	// 	}
	// 	if(cnt==newstrlen){
	// 	}
		
	// }
	// int addstrlen = length(newstr);
	// char *newhead = (char *)malloc(originallen+addstrlen+1);

	// s->head = newhead;
	// free(originalstr);
}

String newString(char *str){
	String s;
	int size = strlength(str); //strlen 직접 구현해보기
	s.head = (char *)malloc(size);
	// memcpy(s.head, str, size+1);
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