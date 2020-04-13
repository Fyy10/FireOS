hello.img : hello.s
	nasm hello.s -fbin -o hello.img

ipl.bin : ipl.s
	nasm ipl.s -fbin -o ipl.bin

run : hello.img
	qemu-system-i386 hello.img

clean :
	rm hello.img
