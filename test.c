#include<stdio.h>
/*
unsigned int fonction(unsigned int i){
	unsigned int j;
	asm
	(
		//(crypted & 0xf0000000) >> 12
		"movl %0, %ecx   \n"
		"movl %ecx, %ebx          \n"
		"andl $0xf0000000, %ebx   \n"
		"shr  $12, %ebx           \n"
		"movl %ebx, %eax          \n"
		//(crypted & 0xf000000)  >> 16
		"movl %ecx, %ebx          \n"
		"andl $0x0f000000, %ebx   \n"
		"shr  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf00000)   >> 16
		"movl %ecx, %ebx          \n"
		"andl $0x00f00000, %ebx   \n"
		"shr  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf0000)    << 8
		"movl %ecx, %ebx          \n"
		"andl $0x000f0000, %ebx   \n"
		"shl  $8, %ebx            \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf000)     << 16
		"movl %ecx, %ebx          \n"
		"andl $0x0000f000, %ebx   \n"
		"shl  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf00)      << 4
		"movl %ecx, %ebx          \n"
		"andl $0x00000f00, %ebx   \n"
		"shl  $4, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf0)       >> 4
		"movl %ecx, %ebx          \n"
		"andl $0x000000f0, %ebx   \n"
		"shr  $4, %ebx            \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf)        << 20
		"movl %ecx, %ebx          \n"
		"andl $0x0000000f, %ebx   \n"
		"shl  $20, %ebx           \n"
		"orl %ebx, %eax           \n"
		: "=q" (j)
		: "g" (i)
	);
	//return j;
}
*/
unsigned int fonction(unsigned int crypted){
	unsigned int decrypted;
	asm
	(
		//(crypted & 0xf0000000) >> 12
		"movl %0, %1\n"
		"incl %0"
		: "=q"(decrypted)
		: "g" (crypted)
	);
return decrypted;
}
unsigned int main(void){
	unsigned int crypted = 0x12345678;
	unsigned int decrypted = fonction(crypted);
	printf("%i\n", decrypted);
	return 0;
}
