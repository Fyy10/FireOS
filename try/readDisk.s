; for main.s only
readDisk:
    pusha
    mov ah, 0x02
    ; mov dl, 0x00  ; 0x00: floppy / flash drive
    mov dl, 0x80    ; 0x80: hard disk (qemu emulates hard disk)
    mov ch, 0
    mov dh, 0

    push bx
    mov bx, 0
    mov es, bx
    pop bx
    mov bx, 0x7c00 + 512

    int 0x13
    jc disk_err

    popa
    ret

    disk_err:
        mov si, DISK_ERR_MSG
        call printf
        jmp fin
