
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

	decrypted = ((crypted & 0xf0000000) >> 12 | 
			     (crypted & 0xf000000)  >> 16 |
			     (crypted & 0xf00000)   >> 16 |
			     (crypted & 0xf0000)    << 8  |
			     (crypted & 0xf000)     << 16 |
			     (crypted & 0xf00)      << 4  |
			     (crypted & 0xf0)       >> 4  |
			     (crypted & 0xf)        << 20 )  |
			     key;
	
	
	asm volatile (
		// instructions...
		
		// sorties (s'il y a lieu)
		: 
		// entrées
		: 
		// registres modifiés (s'il y a lieu)
		: 
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
