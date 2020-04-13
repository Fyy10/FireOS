ipl.bin : ipl.s
	nasm ipl.s -o ipl.bin

fireos.sys : fireos.s
	nasm fireos.s -o fireos.sys

run : ipl.bin fireos.sys
	qemu-system-i386 ipl.bin

clean :
	rm ipl.bin
	rm fireos.sys
