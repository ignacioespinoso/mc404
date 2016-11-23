.global set_speed_motor
.global set_speed_motors
.global read_sonar
.global read_sonars

.align 4
set_speed_motor:
    stmfd sp!, {r4-r11,lr}
    cmp r1, #1                      @ Ajusta o motor de acordo com o id

    movge r7, #127                  @ Identifica a syscall 127 (write_motor1)
    svcge 0x0                         @ caso a id corresponda ao motor direito.

    movlt r7, #126                  @ Identifica a syscall 126 (write_motor0)
    svclt 0x0                         @ caso a id corresponda ao motor esquerdo.
    ldmfd sp!, {r4-r11, pc}

set_speed_motors:
    stmfd sp!, {r4-r11, lr}
    mov r7, #124            @ Identifica a syscall 124 (write_motors).
    svc 0x0                 @ Faz a chamada da syscall.
    ldmfd sp!, {r4-r11, pc}

read_sonar:
    stmfd sp!, {r4-r11, lr}
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0                 @ Faz a chamada da syscall.Note que r0 ja esta
                                @ setado como o id do sonar a ser lido.
    ldmfd sp!, {r4-r11, pc}

read_sonars:
    stmfd sp!, {r4-r11,lr}
    mov r4, r0              @ Copia o parametro de entrada para um registrador auxiliar.

    mov r0, #0              @ Le todos os sonares e vai salvando nas devidas
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0                     @ posicoes do parametro recebido.
    str r0, [r4]

    mov r0, #1
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #4]

    mov r0, #2
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #8]

    mov r0, #3
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #12]

    mov r0, #4
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #16]

    mov r0, #5
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #20]

    mov r0, #6
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #24]

    mov r0, #7
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #28]

    mov r0, #8
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #32]

    mov r0, #9
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #26]

    mov r0, #10
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #40]

    mov r0, #11
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #44]

    mov r0, #12
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #48]

    mov r0, #13
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #52]

    mov r0, #14
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #56]

    mov r0, #15
    mov r7, #125            @ Identifica a syscall 125 (read_sonar).
    svc 0x0
    str r0, [r4, #60]
    ldmfd sp!, {r4-r11, pc}
