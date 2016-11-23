	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	_start
	.type	_start, %function
_start:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #72
.L4:
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-12]
	ldr	r3, .L6
	cmp	r2, r3
	bls	.L2
	ldr	r2, [fp, #-8]
	ldr	r3, .L6
	cmp	r2, r3
	bhi	.L3
.L2:
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
	bl	rotaciona_robo
.L3:
	mov	r0, #50
	mov	r1, #50
	bl	set_speed_motors
	b	.L4
.L7:
	.align	2
.L6:
	.word	1199
	.size	_start, .-_start
	.align	2
	.global	rotaciona_robo
	.type	rotaciona_robo, %function
rotaciona_robo:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-24]
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-20]
	mov	r0, #5
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-16]
	mov	r0, #6
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	mov	r0, #7
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]
	cmp	r3, #600
	bls	.L9
	ldr	r3, [fp, #-12]
	cmp	r3, #600
	bls	.L9
	ldr	r3, [fp, #-8]
	cmp	r3, #600
	bls	.L9
	mov	r0, #0
	mov	r1, #5
	bl	set_speed_motors
	mov	r0, r0	@ nop
	b	.L11
.L9:
	mov	r0, #5
	mov	r1, #0
	bl	set_speed_motors
	b	.L11
.L12:
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-24]
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-20]
.L11:
	ldr	r2, [fp, #-24]
	ldr	r3, .L14
	cmp	r2, r3
	bls	.L12
	ldr	r2, [fp, #-20]
	ldr	r3, .L14
	cmp	r2, r3
	bls	.L12
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L15:
	.align	2
.L14:
	.word	1199
	.size	rotaciona_robo, .-rotaciona_robo
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
