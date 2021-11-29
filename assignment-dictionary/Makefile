lib.o: lib.asm
	nasm -f elf64 -o lib.o lib.asm
dict.o: dict.asm lib.o 
	nasm -f elf64 -o dict.o dict.asm
main.o: main.asm dict.o words.inc
	nasm -f elf64 -o main.o main.asm
program: main.o dict.o lib.o
	ld -o program dict.o main.o lib.o
.PHONY: clean
clean:
	rm -f ./*.o