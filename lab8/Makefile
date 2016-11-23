all: disk.img

disk.img: robot_ctrl
	mksd.sh --so /home/specg12-1/mc404/simulador/simulador_player/bin/knrl --user robot_ctrl

robot_ctrl: api_robot.o main.o
	arm-eabi-ld main.o api_robot.o -o robot_ctrl -Ttext=0x77802000

api_robot.o: api_robot.s
	arm-eabi-as api_robot.s -o api_robot.o

main.o: main.s
	arm-eabi-as main.s -o main.o

main.s: main.c
	arm-eabi-gcc main.c -S -o main.s
