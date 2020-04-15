OSNAME = FireOS
ASMNAME = main

$(OSNAME).iso : $(ASMNAME).bin
	truncate $(ASMNAME).bin -s 1200k
	mkisofs -o $(OSNAME).iso -b $(ASMNAME).bin ./

$(ASMNAME).bin : $(ASMNAME).s printf.s readDisk.s printh.s
	nasm -fbin $(ASMNAME).s -o $(ASMNAME).bin

run : $(ASMNAME).bin
	qemu-system-i386 $(ASMNAME).bin

clean :
	rm $(ASMNAME).bin
