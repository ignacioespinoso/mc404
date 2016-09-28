ias-as.x: main.o label_interpreter.o directive_interpreter.o
	@echo "Ligando todos os códigos objeto..."
	ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -L/usr/lib64 main.o label_interpreter.o directive_interpreter.o -lc /usr/lib64/crtn.o -o ias-as.x

main.s: main.c
	@echo "Criando main em linguagem de montagem..."
	gcc -S main.c -o main.s
main.o: main.s
	@echo "Montando main.s ..."
	as main.s -o main.o

label_interpreter.s: label_interpreter.c
	@echo "Criando label_interpreter em linguagem de montagem..."
	gcc -S label_interpreter.c -o label_interpreter.s
label_interpreter.o: label_interpreter.s
	@echo "Montando label_interpreter.s ..."
	as label_interpreter.s -o label_interpreter.o

instruction_interpreter.s: instruction_interpreter.c
	@echo "Criando instruction_interpreter em linguagem de montagem..."
	gcc -S instruction_interpreter.c -o instruction_interpreter.s
instruction_interpreter.o: instruction_interpreter.s
	@echo "Montando instruction_interpreter.s ..."
	as instruction_interpreter.s -o instruction_interpreter.o

directive_interpreter.s: directive_interpreter.c
	@echo "Criando directive_interpreter em linguagem de montagem..."
	gcc -S directive_interpreter.c -o directive_interpreter.s
directive_interpreter.o: directive_interpreter.s
	@echo "Montando directive_interpreter.s ..."
	as directive_interpreter.s -o directive_interpreter.o

clean:
	rm -f *.s *.o *.x
