[FORMAT "WCOFF"]    ; format of object file
[BITS 32]           ; 32 bit mode

; obj file

[FILE "func.s"]         ; information of source file
    GLOBAL  _io_hlt     ; function name

; function

[SECTION .text]
_io_hlt:    ; void io_hlt(void)
    HLT
    RET

_write_mem8:    ; void write_mem8(int addr, int data)
    MOV     ECX, [ESP+4]    ; [ESP + 4]中存放的是地址，将其读入到ECX
    MOV     AL, [ESP+8]     ; [ESP + 8]中存放的是数据，将其读入到AL
    MOV     [ECX], AL
    RET
