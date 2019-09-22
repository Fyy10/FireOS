hello.img : hello.asm
	nasm hello.asm -o hello.img

run :
	qemu-system-i386 hello.img

clean :
	rm hello.img
