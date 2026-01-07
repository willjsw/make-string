#include <stdio.h>
#include "String.h"

int main(){
    String s;
	s.new = StringNew;
	String* myString = s.new("Hello, World!");
	printf("String: %s, Size: %d\n", myString->head, myString->size);
	return 0;
}