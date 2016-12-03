
#include <stdio.h>

unsigned int Decryption_fct(unsigned int crypted,unsigned int key)
{
	unsigned int decrypted;

	/*
	 * Remplacez le code suivant par de l'assembleur en ligne
	 * en utilisant le moins d'instructions possible

	permutation de décryptage; 4 bit = 1 nibble
	crypted[nib1,nib2,nib3,nib4,nib5,nib6,nib7,nib8] -->
	--> decrypted[nib5,nib4,nib8,nib1,nib6,nib2,nib3,nib7]
	*/
/*
	decrypted = ((crypted & 0xf0000000) >> 12 |
			     (crypted & 0xf000000)  >> 16 |
			     (crypted & 0xf00000)   >> 16 |
			     (crypted & 0xf0000)    << 8  |
			     (crypted & 0xf000)     << 16 |
			     (crypted & 0xf00)      << 4  |
			     (crypted & 0xf0)       >> 4  |
			     (crypted & 0xf)        << 20 )  |
			     key;

*/
	unsigned int operations;
 	unsigned int resultatTmp;
	// J'aurais pu mieux faire manuellement, mais c'est la manière la mieux
	// optimisée que j'ai pu obtenir en assembleur en ligne étendu.
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

	printf("Représentation cryptée  :   %08x\n"
	       "Représentation decryptée:   %08x\n",
	       data,
	       Decryption_fct(data,key));

	return 0;
}
