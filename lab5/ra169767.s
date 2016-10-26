.globl _start

.data

input_buffer:   .skip 32
output_buffer:  .skip 32

.text
.align 4

@ Funcao inicial
_start:
    @ Chama a funcao "read" para ler 4 caracteres da entrada padrao
    ldr r0, =input_buffer
    mov r1, #5             @ 4 caracteres + '\n'
    bl  read
    mov r4, r0             @ copia o retorno para r4.

    @ Chama a funcao "atoi" para converter a string para um numero
    ldr r0, =input_buffer
    mov r1, r4
    bl  atoi

    @ Chama a funcao "encode" para codificar o valor de r0 usando
    @ o codigo de hamming.
    bl  encode
    mov r4, r0             @ copia o retorno para r4.

    @ Chama a funcao "itoa" para converter o valor codificado
    @ para uma sequencia de caracteres '0's e '1's
    ldr r0, =output_buffer
    mov r1, #7
    mov r2, r4
    bl  itoa

    @ Adiciona o caractere '\n' ao final da sequencia (byte 7)
    ldr r0, =output_buffer
    mov r1, #'\n'
    strb r1, [r0, #7]

    @ Chama a funcao write para escrever os 7 caracteres e
    @ o '\n' na saida padrao.
    ldr r0, =output_buffer
    mov r1, #8         @ 7 caracteres + '\n'
    bl  write

	@Realiza a decodificacao
	@ Chama a funcao "read" para ler 7 caracteres da entrada padrao
	ldr r0, =input_buffer
	mov r1, #8             @ 7 caracteres + '\n'
	bl  read
	mov r4, r0             @ copia o retorno para r4.

	@ Chama a funcao "atoi" para converter a string para um numero
	ldr r0, =input_buffer
	mov r1, r4
	bl  atoi

	@ Chama a funcao "decode" para codificar o valor de r0 usando
	@ o codigo de hamming.
	bl  decode
	mov r4, r0             @ copia o retorno da decodificacao para r4.
	mov r6, r1             @ copia o retorno da verificacao para r6.

	@ Chama a funcao "itoa" para converter o valor decodificado
	@ para uma sequencia de caracteres '0's e '1's
	ldr r0, =output_buffer
	mov r1, #4
	mov r2, r4
	bl  itoa

	@ Adiciona o caractere '\n' ao final da sequencia (byte 4)
	ldr r0, =output_buffer
	mov r1, #'\n'
	strb r1, [r0, #4]

	@ Chama a funcao write para escrever os 4 caracteres e
	@ o '\n' na saida padrao.
	ldr r0, =output_buffer
	mov r1, #5         @ 4 caracteres + '\n'
	bl  write

	@ Chama a funcao "itoa" para converter o valor decodificado
	@ para uma sequencia de caracteres '0's e '1's
	ldr r0, =output_buffer
	mov r1, #1
	mov r2, r6
	bl  itoa

	@ Adiciona o caractere '\n' ao final da sequencia (byte 4)
	ldr r0, =output_buffer
	mov r1, #'\n'
	strb r1, [r0, #1]

	@ Chama a funcao write para escrever os 1 caractere e
	@ o '\n' na saida padrao.
	ldr r0, =output_buffer
	mov r1, #2         @ 1 caracteres + '\n'
	bl  write

    @ Chama a funcao exit para finalizar processo.
    mov r0, #0
    bl  exit

@ Codifica o valor de entrada usando o codigo de hamming.
@ parametros:
@  r0: valor de entrada (4 bits menos significativos)
@ retorno:
@  r0: valor codificado (7 bits como especificado no enunciado).
encode:
    	push {r4-r11, lr}
		@Separa d1, d2, d3 e d4 em diferentes registradores.
    	@Obtem d1 e salva em r4
		mov r4, r0
		lsr r4, r4, #3
		@Obtem d2 e salva em r5
		and r5, r0, #4
		lsr r5, r5, #2
		@Obtem d3 e salva em r6
		and r6, r0, #2
		lsr r6, r6, #1
		@Obtem d4 e salva em r7
		and r7, r0, #1

		@Estabelesce p1, p2 e p3
		@Para d1, d2 e d4 obtem p1 e salva em r8
		eor r8, r4, r5
		eor r8, r8, r7
		@Para d1, d3 e d4 obtem p2 e salva em r9
		eor r9, r4, r6
		eor r9, r9, r7
		@Ṕara d2, d3 e d4 obtem p3 e salva em r10
		eor r10, r5, r6
		eor r10, r10, r7

		@Concatena os resultados seguindo a codificacao de hamming
		lsl r0, r8, #6 @p1 corresponde ao bit mais significativo

		lsl r9, r9, #5
		orr r0, r0, r9 @p2 corresponde ao bit mais significativo

		lsl r4, r4, #4
		orr r0, r0, r4 @d1 corresponde ao bit mais significativo

		lsl r10, r10, #3
		orr r0, r0, r10 @p3 corresponde ao bit mais significativo

		lsl r5, r5, #2
		orr r0, r0, r5 @d2 corresponde ao bit mais significativo

		lsl r6, r6, #1
		orr r0, r0, r6 @d3 corresponde ao bit mais significativo

		orr r0, r0, r7 @d4 corresponde ao bit mais significativo

    	pop  {r4-r11, lr}
    	mov  pc, lr

@ Decodifica o valor de entrada usando o codigo de hamming.
@ parametros:
@  r0: valor de entrada (7 bits menos significativos)
@ retorno:
@  r0: valor decodificado (4 bits como especificado no enunciado).
@  r1: 1 se houve erro e 0 se nao houve.
decode:
       push {r4-r11, lr}

		@Salva cada bit do valor de entrada em um registrador diferente
		@Obtem p1 e salva em r4
		and r4, r0, #64
		lsr r4, r4, #6
		and r4, r4, #1
		@Obtem p2 e salva em r5
		and r5, r0, #32
		lsr r5, r5, #5
		and r5, r5, #1
		@Obtem d1 e salva em r6
		and r6, r0, #16
		lsr r6, r6, #4
		and r6, r6, #1
		@Obtem p3 e salva em r7
		and r7, r0, #8
		lsr r7, r7, #3
		and r7, r7, #1
		@Obtem d2 e salva em r8
		and r8, r0, #4
		lsr r8, r8, #2
		and r8, r8, #1
		@Obtem d3 e salva em r9
		and r9, r0, #2
		lsr r9, r9, #1
		and r9, r9, #1
		@Obtem d4 e salva em r10
		and r10, r0, #1
		and r10, r10, #1

		@Avalia o valor codificado e verifica se ha erro.
		@ Verifica a paridade de p1 e salva em r4
		eor r4, r4, r6
		eor r4, r4, r8
		eor r4, r4, r10
		@ Verifica a paridade de p2 e salva em r5
		eor r5, r5, r6
		eor r5, r5, r9
		eor r5, r5, r10
		@ Verifica a paridade de p3 e salva em r7
		eor r7, r7, r8
		eor r7, r7, r9
		eor r7, r7, r10
		@Salva 1 em r1 caso haja algum erro no dado codificado
		mov r1, #0
		orr r1, r4, r5
		orr r1, r1, r7

		@Transfere d1, d2, d3 e d4 para r0 para obter o valor decodificado.
		mov r0, #0 @Zera o registrador

		lsl r6, r6, #3
		orr r0, r0, r6 @Transfere d1

		lsl r8, r8, #2
		orr r0, r0, r8 @Inclui d2 em sua devida posicao

		lsl r9, r9, #1
		orr r0, r0, r9 @Inclui d3 em sua devida posicao

		orr r0, r0, r10 @Inclui d4 em sua devida posicao

       pop  {r4-r11, lr}
       mov  pc, lr

@ Le uma sequencia de bytes da entrada padrao.
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de bytes.
@  r1: numero maximo de bytes que pode ser lido (tamanho do buffer).
@ retorno:
@  r0: numero de bytes lidos.
read:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #0         @ stdin file descriptor = 0
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho maximo.
    mov r7, #3         @ read
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Escreve uma sequencia de bytes na saida padrao.
@ parametros:
@  r0: endereco do buffer de memoria que contem a sequencia de bytes.
@  r1: numero de bytes a serem escritos
write:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #1         @ stdout file descriptor = 1
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho do buffer.
    mov r7, #4         @ write
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Finaliza a execucao de um processo.
@  r0: codigo de finalizacao (Zero para finalizacao correta)
exit:
    mov r7, #1         @ syscall number for exit
    svc 0x0

@ Converte uma sequencia de caracteres '0' e '1' em um numero binario
@ parametros:
@  r0: endereco do buffer de memoria que armazena a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@ retorno:
@  r0: numero binario
atoi:
    push {r4, r5, lr}
    mov r4, r0         @ r4 == endereco do buffer de caracteres
    mov r5, r1         @ r5 == numero de caracteres a ser considerado
    mov r0, #0         @ number = 0
    mov r1, #0         @ loop indice
atoi_loop:
    cmp r1, r5         @ se indice == tamanho maximo
    beq atoi_end       @ finaliza conversao
    mov r0, r0, lsl #1
    ldrb r2, [r4, r1]
    cmp r2, #'0'       @ identifica bit
    orrne r0, r0, #1
    add r1, r1, #1     @ indice++
    b atoi_loop
atoi_end:
    pop {r4, r5, lr}
    mov pc, lr

@ Converte um numero binario em uma sequencia de caracteres '0' e '1'
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@  r2: numero binario
itoa:
    push {r4, r5, lr}
    mov r4, r0
itoa_loop:
    sub r1, r1, #1         @ decremento do indice
    cmp r1, #0          @ verifica se ainda ha bits a serem lidos
    blt itoa_end
    and r3, r2, #1
    cmp r3, #0
    moveq r3, #'0'      @ identifica o bit
    movne r3, #'1'
    mov r2, r2, lsr #1  @ prepara o proximo bit
    strb r3, [r4, r1]   @ escreve caractere na memoria
    b itoa_loop
itoa_end:
    pop {r4, r5, lr}
    mov pc, lr
