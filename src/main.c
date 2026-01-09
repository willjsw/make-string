#include <stdio.h>
#include "String.h"


int main(){
	
	String mystr = newString("Hello"); //construct

	printf("%s\n",mystr.head); //init string
	mystr.append(mystr.this, ", World!"); //append
	printf("%s\n",mystr.head);
	mystr.substring(mystr.this, 0, 7); //substring
	printf("%s\n",mystr.head);
	printf("%d\n",mystr.length(mystr.this)); //length
	
	return 0;

	free(mystr.head);
}
