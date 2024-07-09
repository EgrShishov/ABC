all: main asm_functions.o

asm_functions.o:
	nasm -f elf64 asm_functions.asm -o asm_functions.o

main: asm_functions.o
	g++ -std=c++11 -fopenmp -no-pie main.cpp asm_functions.o -o ./out.bin -lOpenCL

clean:
	rm -rf *.o
