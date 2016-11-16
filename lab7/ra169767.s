@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@
@ Codigo para controle basico de um robo.
@ Este codigo le os valores de 2 sonares frontais para decidir se o
@ robo deve rotacionar
@ 2 syscalls serao utilizadas para controlar o robo:
@   write_motors  (syscall de numero 124)
@                 Parametros:
@                       r0 : velocidade para o motor 0  (valor de 6 bits)
@                       r1 : velocidade para o motor 1  (valor de 6 bits)
@
@  read_sonar (syscall de numero 125)
@                 Parametros:
@                       r0 : identificador do sonar   (valor de 4 bits)
@                 Retorno:
@                       r0 : distancia capturada pelo sonar consultado (valor de 12 bits)
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.text
.align 4
.globl _start

_start:                         @ main

        mov r0, #0              @ Carrega em r0 a velocidade do motor 0.
                                @ Lembre-se: apenas os 6 bits menos significativos
                                @ serao utilizados.
        mov r1, #0              @ Carrega em r1 a velocidade do motor 1.
        mov r7, #124            @ Identifica a syscall 124 (write_motors).
        svc 0x0                 @ Faz a chamada da syscall.

        ldr r6, =1200           @ r6 <- 1200 (Limiar para rotacionar o robo)
        ldr r8, =600            @ r8 <- 1200 (Limiar para rotacionar para a direita o robo)
loop:
        mov r0, #3              @ Define em r0 o identificador do sonar a ser consultado.
        mov r7, #125            @ Identifica a syscall 125 (read_sonar).
        svc 0x0
        mov r5, r0              @ Armazena o retorno da syscall.

        mov r0, #4              @ Define em r0 o sonar.
        mov r7, #125
        svc 0x0

        cmp r5, r0              @ Compara o retorno (em r0) com r5.
        bge min                 @ Se r5 > r0: Salta pra min
        mov r0, r5              @ Senao: r0 <- r5
min:


        cmp r0, r6              @ Compara r0 com r6
        blt rotaciona_direita   @ Se r0 menor que o limiar: Rotaciona o robo

                                @ Senao define uma velocidade para os 2 motores
        mov r0, #50
        mov r1, #50
        mov r7, #124
        svc 0x0

        b loop                  @ Refaz toda a logica


rotaciona_direita:              @ Roda para a direita caso o lado esteja livre

        mov r0, #6              @ Define em r0 o identificador do sonar a ser consultado.
        mov r7, #125            @ Identifica a syscall 125 (read_sonar).
        svc 0x0
        mov r5, r0              @ Armazena o retorno da syscall.

        mov r0, #7              @ Define em r0 o sonar.
        mov r7, #125
        svc 0x0

        cmp r5, r0              @ Armazena o menor valor em r0.
        movlt r0, r5

        cmp r0, r8              @ Compara o valor com o limiar.
        blt rotaciona_esquerda  @ Roda para a esquerda caso esteja obstruido o lado direito.

        mov r0, #0              @ Ajusta os motores para rodar o robo para a direita.
        mov r1, #5
        mov r7, #124
        svc 0x0

        b loop

rotaciona_esquerda:
        mov r0, #5              @ Ajusta os motores para rodar o robo para a esquerda.
        mov r1, #0
        mov r7, #124
        svc 0x0

        b loop
