#include<stdio.h>
/*
unsigned int fonction(unsigned int i){
	unsigned int decrypted;
	asm
	(
		//(crypted & 0xf0000000) >> 12
		"movl 8(%ebp), %ebx          \n"
		"andl $0xf0000000, %ebx   \n"
		"shr  $12, %ebx           \n"
		"movl %ebx, %eax          \n"
		//(crypted & 0xf000000)  >> 16
		"movl 8(%ebp), %ebx          \n"
		"andl $0x0f000000, %ebx   \n"
		"shr  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf00000)   >> 16
		"movl 8(%ebp), %ebx          \n"
		"andl $0x00f00000, %ebx   \n"
		"shr  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf0000)    << 8
		"movl 8(%ebp), %ebx          \n"
		"andl $0x000f0000, %ebx   \n"
		"shl  $8, %ebx            \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf000)     << 16
		"movl 8(%ebp), %ebx          \n"
		"andl $0x0000f000, %ebx   \n"
		"shl  $16, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf00)      << 4
		"movl 8(%ebp), %ebx          \n"
		"andl $0x00000f00, %ebx   \n"
		"shl  $4, %ebx           \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf0)       >> 4
		"movl 8(%ebp), %ebx          \n"
		"andl $0x000000f0, %ebx   \n"
		"shr  $4, %ebx            \n"
		"orl %ebx, %eax           \n"
		//(crypted & 0xf)        << 20
		"movl 8(%ebp), %ebx          \n"
		"andl $0x0000000f, %ebx      \n"
		"shl  $20, %ebx              \n"
		"orl %ebx, %eax              \n"
		"orl 12(%ebp), %eax            "
	);
	//return decrypted;
}
*/
unsigned int fonction(unsigned int crypted, unsigned int key){
	unsigned int decrypted;
	unsigned int operations;
	unsigned int resultatTmp;
	asm volatile
	(
		//(crypted & 0xf0000000) >> 12
		"movl %1, %2            \n"
		"andl $0xF0000000, %2   \n"
		"shrl $12, %2           \n"
		"movl %2, %3            \n"
		//(crypted & 0xf000000) >> 16 et (crypted & 0x0f00000) >> 16 =
		//(crypted & 0xff00000) >> 16
		"movl %1, %2            \n"
		"andl $0x0FF00000, %2   \n"
		"shrl $16, %2           \n"
		"orl  %2, %3            \n"
		//(crypted & 0xf0000)    << 8
		"movl %1, %2            \n"
		"andl $0x000F0000, %2   \n"
		"shll $8, %2            \n"
		"orl  %2, %3            \n"
		//(crypted & 0xf000)     << 16
		"movl %1, %2            \n"
		"andl $0x0000F000, %2   \n"
		"shll $16, %2           \n"
		"orl  %2, %3            \n"
		//(crypted & 0xf00)      << 4
		"movl %1, %2            \n"
		"andl $0x00000F00, %2   \n"
		"shll $4, %2            \n"
		"orl  %2, %3            \n"
		//(crypted & 0xf0)       >> 4
		"movl %1, %2            \n"
		"andl $0x000000F0, %2   \n"
		"shrl $4, %2            \n"
		"orl  %2, %3            \n"
		//(crypted & 0xf)        << 20
		"movl %1, %2            \n"
		"andl $0x0000000F, %2   \n"
		"shll $20, %2           \n"
		"orl  %2, %3            \n"
		//resultatTmp |= key
		"orl  %4, %3            \n"
		//decrypted = resultatTmp
		"movl %3, %0              "
		: "=q"(decrypted)
		: "g" (crypted), "r" (operations), "r" (resultatTmp), "g" (key)
	);
return decrypted;
}
int main()
{
	unsigned int data = 0x12345678;
	unsigned int key =0x0c0180c;

	unsigned int decrypted = fonction(data, key);
	printf("%i\n", decrypted);

	return 0;
}
