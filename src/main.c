#include <stdio.h>
#include "String.h"


int main(){
	
	String mystr = newString("Hello");

	mystr.length = stringlength;
	mystr.append = stringappend;
	mystr.substring = stringsubstring;
	mystr.replace = stringreplace;

	printf("%s\n",mystr.head);
	// printf("%p\n",mystr.this);
	mystr.append(mystr.this, ", World!");
	printf("%s\n",mystr.head);
	mystr.substring(mystr.this, 0, 4);
	printf("%s\n",mystr.head);
	printf("%d\n",mystr.size);
	
	return 0;

	free(mystr.head);
}
