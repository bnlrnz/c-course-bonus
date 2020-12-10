#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char makeSmall(char character){
	if (character >= 'A' && character <= 'Z'){
		return character +  32;
	}

	return character;
}

int main(int argc, char** argv){

	//argc, argv siehe: http://www.c-howto.de/tutorial/funktionen-teil-2/hauptfunktion/
	if(argc < 2){
		printf("Please pass a word...\n");
		return 0;
	}

	int wordLen = strlen(argv[1]);

	int palindrom = 0;
	char front;
	char rear;

	for (int i = 0; i < wordLen / 2; ++i){
		front = argv[1][i]; // front
		rear = argv[1][wordLen - i - 1]; // back

		if (makeSmall(front) == makeSmall(rear)){
			palindrom = 1;
		}else{
			palindrom = 0;
			break;
		}
	}

	if(palindrom){
		printf("%s is a palindrom\n", argv[1]);
	}else{
		printf("%s is not a palindrom\n", argv[1]);
	}

	return 0;
}