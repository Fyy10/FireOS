testA20:
    pusha

    ; es = 0 (maybe by default)
    ; 0x7c00 + 510 = 0x7dfe
    mov ax, [0x7dfe]
    mov dx, ax
    call printh
    ; dx=0xaa55

    push bx
    mov bx, 0xffff
    mov es, bx
    pop bx

    ; 0x107dfe - 0xffff0 = 0x7e0e
    mov bx, 0x7e0e
    mov dx, [es:bx]
    call printh
    ; dx!=0xaa55, A20 enabled

    popa
    ret
