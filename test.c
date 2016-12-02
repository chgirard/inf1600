#include<stdio.h>

int retourne1(){
	asm ("movl $1, %eax");
}

int main(void){
	int i = retourne1();
	printf("%i\n\n", i);
	return 0;
}
