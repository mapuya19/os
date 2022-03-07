	.file	"shell.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Hey there!\0"
	.text
	.globl	hello
	.def	hello;	.scl	2;	.type	32;	.endef
	.seh_proc	hello
hello:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "See ya later!\0"
	.text
	.globl	bye
	.def	bye;	.scl	2;	.type	32;	.endef
	.seh_proc	bye
bye:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC1(%rip), %rcx
	call	puts
	movl	$0, %ecx
	call	exit
	nop
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "202 lab #1 (Spring 2022)\0"
	.text
	.globl	assignment
	.def	assignment;	.scl	2;	.type	32;	.endef
	.seh_proc	assignment
assignment:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC2(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC3:
	.ascii "Matthew Apuya \342\200\242 N13953137 \342\200\242 mja610\0"
	.text
	.globl	author
	.def	author;	.scl	2;	.type	32;	.endef
	.seh_proc	author
author:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC3(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC4:
	.ascii "002\0"
	.text
	.globl	section
	.def	section;	.scl	2;	.type	32;	.endef
	.seh_proc	section
section:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC4(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC5:
	.ascii "hello\0"
.LC6:
	.ascii "bye\0"
.LC7:
	.ascii "assignment\0"
.LC8:
	.ascii "author\0"
.LC9:
	.ascii "section\0"
	.text
	.globl	isBuiltIn
	.def	isBuiltIn;	.scl	2;	.type	32;	.endef
	.seh_proc	isBuiltIn
isBuiltIn:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	leaq	.LC5(%rip), %rdx
	movq	16(%rbp), %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L7
	call	hello
	movl	$1, %eax
	jmp	.L8
.L7:
	leaq	.LC6(%rip), %rdx
	movq	16(%rbp), %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L9
	call	bye
	jmp	.L10
.L9:
	leaq	.LC7(%rip), %rdx
	movq	16(%rbp), %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L11
	call	assignment
	movl	$1, %eax
	jmp	.L8
.L11:
	leaq	.LC8(%rip), %rdx
	movq	16(%rbp), %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L12
	call	author
	movl	$1, %eax
	jmp	.L8
.L12:
	leaq	.LC9(%rip), %rdx
	movq	16(%rbp), %rcx
	call	strcmp
	testl	%eax, %eax
	jne	.L10
	call	section
	movl	$1, %eax
	jmp	.L8
.L10:
	movl	$0, %eax
.L8:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC10:
	.ascii "/bin/\0"
.LC11:
	.ascii "apuya_shell >> \0"
.LC12:
	.ascii "\12\0"
.LC13:
	.ascii " \0"
.LC14:
	.ascii "could not execve\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$1544, %rsp
	.seh_stackalloc	1544
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	call	__main
	leaq	.LC10(%rip), %rax
	movq	%rax, 1384(%rbp)
.L24:
	leaq	.LC11(%rip), %rcx
	call	printf
	call	__getreent
	movq	8(%rax), %rdx
	leaq	352(%rbp), %rax
	movq	%rdx, %r8
	movl	$1024, %edx
	movq	%rax, %rcx
	call	fgets
	testq	%rax, %rax
	je	.L27
	leaq	352(%rbp), %rax
	leaq	.LC12(%rip), %rdx
	movq	%rax, %rcx
	call	strcspn
	movb	$0, 352(%rbp,%rax)
	leaq	352(%rbp), %rax
	movq	%rax, %rcx
	call	isBuiltIn
	testl	%eax, %eax
	jne	.L28
	leaq	352(%rbp), %rax
	leaq	.LC13(%rip), %rdx
	movq	%rax, %rcx
	call	strtok
	movq	%rax, 1400(%rbp)
	movl	$0, 1396(%rbp)
	jmp	.L18
.L19:
	movl	1396(%rbp), %eax
	cltq
	movq	1400(%rbp), %rdx
	movq	%rdx, -48(%rbp,%rax,8)
	leaq	.LC13(%rip), %rdx
	movl	$0, %ecx
	call	strtok
	movq	%rax, 1400(%rbp)
	addl	$1, 1396(%rbp)
.L18:
	cmpq	$0, 1400(%rbp)
	jne	.L19
	movl	1396(%rbp), %eax
	cltq
	movq	$0, -48(%rbp,%rax,8)
	movl	1396(%rbp), %eax
	movl	%eax, 1380(%rbp)
	movq	1384(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	strcpy
	movq	-48(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	strcat
	movl	$0, 1396(%rbp)
	jmp	.L20
.L22:
	movl	1396(%rbp), %eax
	cltq
	movzbl	-80(%rbp,%rax), %eax
	cmpb	$10, %al
	jne	.L21
	movl	1396(%rbp), %eax
	cltq
	movb	$0, -80(%rbp,%rax)
.L21:
	addl	$1, 1396(%rbp)
.L20:
	movl	1396(%rbp), %eax
	movslq	%eax, %rbx
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	strlen
	cmpq	%rax, %rbx
	jb	.L22
	call	fork
	movl	%eax, 1376(%rbp)
	cmpl	$0, 1376(%rbp)
	jne	.L23
	leaq	-48(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movl	$0, %r8d
	movq	%rax, %rcx
	call	execve
	call	__getreent
	movq	24(%rax), %rax
	movq	%rax, %r9
	movl	$17, %r8d
	movl	$1, %edx
	leaq	.LC14(%rip), %rcx
	call	fwrite
	jmp	.L24
.L23:
	leaq	-84(%rbp), %rax
	movq	%rax, %rcx
	call	wait
	jmp	.L24
.L28:
	nop
	jmp	.L24
.L27:
	nop
	movl	$0, %eax
	addq	$1544, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 7.4.0"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	__getreent;	.scl	2;	.type	32;	.endef
	.def	fgets;	.scl	2;	.type	32;	.endef
	.def	strcspn;	.scl	2;	.type	32;	.endef
	.def	strtok;	.scl	2;	.type	32;	.endef
	.def	strcpy;	.scl	2;	.type	32;	.endef
	.def	strcat;	.scl	2;	.type	32;	.endef
	.def	strlen;	.scl	2;	.type	32;	.endef
	.def	fork;	.scl	2;	.type	32;	.endef
	.def	execve;	.scl	2;	.type	32;	.endef
	.def	fwrite;	.scl	2;	.type	32;	.endef
	.def	wait;	.scl	2;	.type	32;	.endef
