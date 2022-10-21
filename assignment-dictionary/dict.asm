section .text
global find_word

extern string_length
extern string_equals

find_word:
	xor rax, rax
	.loop:
		push rsi
		add rsi, 8
		call string_equals
		pop rsi
		cmp rax, 0
		jne .found
		mov rsi, [rsi]
		cmp rsi, 0
		je .endLoop
		jmp.loop
	.found:
		add rsi, 8
		push rsi
		call string_length
		pop rsi
		add rax, rsi
		inc rax
		ret
	.endLoop:
		xor rax, rax
		ret