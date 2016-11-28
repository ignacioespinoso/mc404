ASSEMBLER=arm-eabi-as
LINKER=arm-eabi-ld
SDMAKER=mksd.sh
SIMULATOR=arm-sim
GDB=arm-eabi-gdb

sd: link assemble
	${SDMAKER} --so ra169767 --user faz_nada

link: assemble
	${LINKER} ra169767.o -o ra169767 -g --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0
	${LINKER} faz_nada.o -o faz_nada -Tdata=0x77801900


assemble: ra169767.s
	${ASSEMBLER} -g ra169767.s -o ra169767.o
	${ASSEMBLER} faz_nada.s -o faz_nada.o

run:
	${SIMULATOR} --rom=/home/specg12-1/mc404/simulador/simulador_player/bin/dumboot.bin --sd=disk.img -g

gdb:
	${GDB} ra169767

source:
	source /home/specg12-1/mc404/simulador/set_path_player.sh

clean:
	rm *.o ra156175 faz_nada disk.img -f
