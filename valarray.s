	.file	"valarray.cpp"
	.text
	.section	.text.unlikely,"ax",@progbits
.LCOLDB4:
	.section	.text.startup,"ax",@progbits
.LHOTB4:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1980:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1980
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$80000, %edi
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	vbroadcastsd	.LC1(%rip), %ymm0
	movq	%rax, %rbx
	leaq	80000(%rax), %rdx
.L2:
	vmovupd	%ymm0, (%rax)
	addq	$64, %rax
	vmovupd	%ymm0, -32(%rax)
	cmpq	%rdx, %rax
	jne	.L2
	movl	$80000, %edi
	vzeroupper
.LEHB1:
	call	_Znwm@PLT
.LEHE1:
	vbroadcastsd	.LC3(%rip), %ymm0
	movq	%rax, %r12
	leaq	80000(%rax), %rdx
.L3:
	vmovupd	%ymm0, (%rax)
	addq	$64, %rax
	vmovupd	%ymm0, -32(%rax)
	cmpq	%rdx, %rax
	jne	.L3
	movl	$80000, %edi
	vzeroupper
.LEHB2:
	call	_Znwm@PLT
.LEHE2:
	movq	%rax, %rdi
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L4:
	vmovupd	(%rbx,%rdx), %ymm1
	vaddpd	(%r12,%rdx), %ymm1, %ymm0
	vmovupd	%ymm0, (%rdi,%rdx)
	addq	$32, %rdx
	cmpq	$80000, %rdx
	jne	.L4
	vcvttsd2sil	(%rdi), %r13d
	vzeroupper
	call	_ZdlPv@PLT
	movq	%r12, %rdi
	call	_ZdlPv@PLT
	movq	%rbx, %rdi
	call	_ZdlPv@PLT
	leaq	-24(%rbp), %rsp
	popq	%rbx
	movl	%r13d, %eax
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L7:
	.cfi_restore_state
	endbr64
	movq	%rax, %r13
	vzeroupper
	jmp	.L6
.L8:
	endbr64
	movq	%rax, %r13
	jmp	.L5
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1980:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1980-.LLSDACSB1980
.LLSDACSB1980:
	.uleb128 .LEHB0-.LFB1980
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1980
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L7-.LFB1980
	.uleb128 0
	.uleb128 .LEHB2-.LFB1980
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L8-.LFB1980
	.uleb128 0
.LLSDACSE1980:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC1980
	.type	main.cold, @function
main.cold:
.LFSB1980:
.L5:
	.cfi_def_cfa 6, 16
	.cfi_offset 3, -40
	.cfi_offset 6, -16
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	movq	%r12, %rdi
	vzeroupper
	call	_ZdlPv@PLT
.L6:
	movq	%rbx, %rdi
	call	_ZdlPv@PLT
	movq	%r13, %rdi
.LEHB3:
	call	_Unwind_Resume@PLT
.LEHE3:
	.cfi_endproc
.LFE1980:
	.section	.gcc_except_table
.LLSDAC1980:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC1980-.LLSDACSBC1980
.LLSDACSBC1980:
	.uleb128 .LEHB3-.LCOLDB4
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSEC1980:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE4:
	.section	.text.startup
.LHOTE4:
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 8
.LC3:
	.long	0
	.long	1073741824
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
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
