; print hex number, for main.s only
; print data in DX in hex mode

printh:
    mov si, HEX_PATTERN

    mov bx, dx
    shr bx, 12
    mov bx, [bx + HEX_TABLE]
    mov [HEX_PATTERN+2], bl

    mov bx, dx
    and bx, 0x0FFF
    shr bx, 8
    mov bx, [bx + HEX_TABLE]
    mov [HEX_PATTERN+3], bl

    mov bx, dx
    and bx, 0x00FF
    shr bx, 4
    mov bx, [bx + HEX_TABLE]
    mov [HEX_PATTERN+4], bl

    mov bx, dx,
    and bx, 0x000F
    mov bx, [bx + HEX_TABLE]
    mov [HEX_PATTERN+5], bl

    call printf
    ret

HEX_PATTERN: db '0x****', 0x0a, 0x0d, 0
HEX_TABLE: db '0123456789abcdef'
