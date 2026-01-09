#include <stdio.h>
#include "String.h"


int main(){
	
	String mystr = newString("Hello");

	printf("%s\n",mystr.head);
	// printf("%p\n",mystr.this);
	mystr.append(mystr.this, ", World!");
	printf("%s\n",mystr.head);
	mystr.substring(mystr.this, 1, 4);
	printf("%s\n",mystr.head);
	printf("%d\n",mystr.size);
	
	return 0;

	free(mystr.head);
}
