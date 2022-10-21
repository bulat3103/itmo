%include "lib.inc"
%include "words.inc"
%define MAX_CAPACITY 256

extern find_word

global _start

section .data

not_found: db "Key not found!", 0
buffer_overflow: db 'Error. Can not read the word', 0
string_buffer: times MAX_CAPACITY db 0

section .text

_start:
	xor rax, rax
	mov rdi, string_buffer
	mov rsi, MAX_CAPACITY
	call read_word
	test rax, rax
	jne .success_read
	mov rdi, buffer_overflow
	call print_errorMessage
	call print_newline
	call exit
	.success_read:
		mov rdi, rax
		mov rsi, first
		push rdx
		call find_word
		test rax, rax
		jne .found
		call print_errorMessage
		call print_newline
		call exit
	.found:
		pop rdx
		add rax, 8
		add rax, rdx
		add rax, 1
		mov rdi, rax
		call print_string
		call print_newline
		call exit

print_errorMessage:
	xor rax, rax
	mov rsi, rdi
	call string_length
	mov rdx, rax
	mov rdi, 2
	mov rax, 1
	syscall
	ret