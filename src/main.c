#include <stdio.h>
#include "String.h"


int main(){
	
	String* mystr = new_string("Hello");  

	printf("%s\n",mystr->head); //init string
	mystr->append(mystr, ", World!"); //append
	printf("%s\n",mystr->head);
	mystr->substring(mystr, 0, 7); //substring
	printf("%s\n",mystr->head);
	
	delete_string(mystr);

	return 0;
}
