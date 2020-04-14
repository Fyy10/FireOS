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
