OSNAME = FireOS
ASMNAME = ipl
DEBUG = -d guest_errors

$(OSNAME).iso : $(ASMNAME).bin
	truncate $(ASMNAME).bin -s 1200k
	mkisofs -o $(OSNAME).iso -b $(ASMNAME).bin ./

$(ASMNAME).bin : $(ASMNAME).s
	nasm -fbin $(ASMNAME).s -o $(ASMNAME).bin

run : $(ASMNAME).bin $(OSNAME).iso
	qemu-system-i386 -m 4M $(ASMNAME).bin $(DEBUG)

clean :
	touch $(OSNAME).iso && rm $(OSNAME).iso
	touch $(ASMNAME).bin && rm $(ASMNAME).bin
