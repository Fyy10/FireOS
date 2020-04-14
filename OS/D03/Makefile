OSNAME = FireOS
ASMNAME = ipl

$(OSNAME).iso : $(ASMNAME).bin
	truncate $(ASMNAME).bin -s 1200k
	mkisofs -o $(OSNAME).iso -b $(ASMNAME).bin ./

$(ASMNAME).bin : $(ASMNAME).s
	nasm -fbin $(ASMNAME).s -o $(ASMNAME).bin

run : $(ASMNAME).bin $(OSNAME).iso
	qemu-system-i386 $(ASMNAME).bin

clean :
	rm $(OSNAME).iso
	rm $(ASMNAME).bin
