	.file	"tp5.c"
	.text
	.globl	Decryption_fct
	.type	Decryption_fct, @function
Decryption_fct:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	-4(%ebp), %eax
#APP
# 31 "tp5.c" 1
	movl 8(%ebp), %eax            
andl $0xF0000000, %eax   
shrl $12, %eax           
movl %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x0FF00000, %eax   
shrl $16, %eax           
orl  %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x000F0000, %eax   
shll $8, %eax            
orl  %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x0000F000, %eax   
shll $16, %eax           
orl  %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x00000F00, %eax   
shll $4, %eax            
orl  %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x000000F0, %eax   
shrl $4, %eax            
orl  %eax, -8(%ebp)            
movl 8(%ebp), %eax            
andl $0x0000000F, %eax   
shll $20, %eax           
orl  %eax, -8(%ebp)            
orl  12(%ebp), -8(%ebp)            

# 0 "" 2
#NO_APP
	movl	-8(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	Decryption_fct, .-Decryption_fct
	.section	.rodata
	.align 4
.LC0:
	.string	"Repr\303\251sentation crypt\303\251e  :   %08x\nRepr\303\251sentation decrypt\303\251e:   %08x\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	movl	$305419896, -16(%ebp)
	movl	$12589068, -12(%ebp)
	pushl	-12(%ebp)
	pushl	-16(%ebp)
	call	Decryption_fct
	addl	$8, %esp
	subl	$4, %esp
	pushl	%eax
	pushl	-16(%ebp)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
