.global set_motor_speed
.global set_motors_speed
.global read_sonar
.global read_sonars
.global register_proximity_callback
.global add_alarm
.global get_time
.global set_time

.align 4
set_motor_speed:
    stmfd sp!, {r4-r11,lr}

    ldr r2, [r0]
    ldr r1, [r0, #1]
    mov r0, r2

    mov r7, #18                     @ Identifica a syscall 18 (set_motor_speed).
    svc 0x0

    ldmfd sp!, {r4-r11, pc}

set_motors_speed:
    stmfd sp!, {r4-r11, lr}
    mov r7, #19                     @ Identifica a syscall 19 (set_motors_speed).
    svc 0x0                         @ Faz a chamada da syscall.
    ldmfd sp!, {r4-r11, pc}

read_sonar:
    stmfd sp!, {r4-r11, lr}
    mov r7, #16                     @ Identifica a syscall 16 (read_sonar).
    svc 0x0                      @ Faz a chamada da syscall.Note que r0 ja esta
                                    @ setado como o id do sonar a ser lido.
    ldmfd sp!, {r4-r11, pc}

read_sonars:
    stmfd sp!, {r4-r11, lr}

    ldmfd sp!, {r4-r11, pc}
register_proximity_callback:
    stmfd sp!, {r4-r11, lr}

    mov r7, #17
    svc 0x0
    ldmfd sp!, {r4-r11, pc}
add_alarm:
    stmfd sp!, {r4-r11, lr}

    ldmfd sp!, {r4-r11, pc}
get_time:
    stmfd sp!, {r4-r11, lr}

    mov r7, #20
    svc 0x0
    ldmfd sp!, {r4-r11, pc}
set_time:
    stmfd sp!, {r4-r11, lr}

    mov r7, #21
    svc 0x0
    ldmfd sp!, {r4-r11, pc}
