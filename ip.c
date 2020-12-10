#include <stdio.h>

int main(void){
	int ip = 16777343;

	char* ipPointer = (char*)&ip;
	printf("IP as integer: %d\n", ip);

	printf("IP: %d.%d.%d.%d\n", ipPointer[0], ipPointer[1], ipPointer[2], ipPointer[3]);

	return 0;
}