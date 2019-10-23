hello.img : hello.s
	nasm hello.s -fbin -o hello.img

run : hello.img
	qemu-system-i386 hello.img

clean :
	rm hello.img
