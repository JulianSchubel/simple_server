	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"listen: %d"
.LC1:
	.string	"%d\n"
.LC2:
	.string	"Received connection from: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket@PLT
	movl	%eax, -116(%rbp)
	movw	$2, -96(%rbp)
	movl	$9002, %edi
	call	htons@PLT
	movw	%ax, -94(%rbp)
	movl	$0, -92(%rbp)
	movzwl	-96(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	print_comm_domain
	leaq	-96(%rbp), %rcx
	movl	-116(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind@PLT
	movl	%eax, -112(%rbp)
	movl	-116(%rbp), %eax
	movl	$5, %esi
	movl	%eax, %edi
	call	listen@PLT
	movl	%eax, -108(%rbp)
	movl	-108(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L2:
	movl	$46, -104(%rbp)
	movl	$16, -120(%rbp)
	leaq	-120(%rbp), %rdx
	leaq	-80(%rbp), %rcx
	movl	-116(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	accept@PLT
	movl	%eax, -100(%rbp)
	movl	-100(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	get_in_addr_type
	movq	%rax, %rsi
	movzwl	-80(%rbp), %eax
	movzwl	%ax, %eax
	movl	-104(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	%eax, %edi
	call	inet_ntop@PLT
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-100(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	jmp	.L2
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.globl	get_in_addr_type
	.type	get_in_addr_type, @function
get_in_addr_type:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzwl	(%rax), %eax
	cmpw	$2, %ax
	jne	.L5
	movq	-8(%rbp), %rax
	addq	$4, %rax
	jmp	.L6
.L5:
	movq	-8(%rbp), %rax
	addq	$8, %rax
.L6:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	get_in_addr_type, .-get_in_addr_type
	.section	.rodata
.LC3:
	.string	"Communication domain: IPv4"
.LC4:
	.string	"Communication domain: IPv6"
	.align 8
.LC5:
	.string	"Communication domain: Controller Area Network (automotive bus protocol)"
	.align 8
.LC6:
	.string	"Unrecognized communication domain"
	.text
	.globl	print_comm_domain
	.type	print_comm_domain, @function
print_comm_domain:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$29, -4(%rbp)
	je	.L8
	cmpl	$29, -4(%rbp)
	ja	.L9
	cmpl	$2, -4(%rbp)
	je	.L10
	cmpl	$10, -4(%rbp)
	je	.L11
	jmp	.L9
.L10:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L12
.L11:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L12
.L8:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L12
.L9:
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
.L12:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	print_comm_domain, .-print_comm_domain
	.globl	handle_error
	.type	handle_error, @function
handle_error:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE9:
	.size	handle_error, .-handle_error
	.section	.rodata
.LC7:
	.string	"Socket error"
	.text
	.globl	check_socket
	.type	check_socket, @function
check_socket:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jns	.L16
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	handle_error
.L16:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	check_socket, .-check_socket
	.section	.rodata
.LC8:
	.string	"Socket binding error"
	.text
	.globl	check_binding
	.type	check_binding, @function
check_binding:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jns	.L19
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	handle_error
.L19:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	check_binding, .-check_binding
	.globl	get_flen
	.type	get_flen, @function
get_flen:
.LFB12:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$2, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ftell@PLT
	movl	%eax, -4(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	fseek@PLT
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	get_flen, .-get_flen
	.globl	get_fdata
	.type	get_fdata, @function
get_fdata:
.LFB13:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L23
.L25:
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-5(%rbp), %eax
	movb	%al, (%rdx)
.L23:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movb	%al, -5(%rbp)
	cmpb	$-1, -5(%rbp)
	je	.L24
	movl	-4(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jl	.L25
.L24:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	get_fdata, .-get_fdata
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
