[org 0x7c00]
[bits 16]

section .text

    global main

main:   ; entry point

; initializations
cli
jmp 0x0000:ZeroSeg
ZeroSeg:
    xor ax, ax  ; mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, main    ; stack pointer
    cld             ; clear direction flag, to read string from left to right
sti

; reset disk
push ax
xor ax, ax
mov dl, 0x80    ; hard disk (qemu)
int 0x13
pop ax

; start
mov si, STR_1
call printf

mov si, STR_2
call printf

mov al, 1       ; number of sectors to read
mov cl, 2       ; first sector to read (sector 1 is for ipl)
call readDisk

call test

mov dl, [0x7c00+510]    ; 0x55
mov dh, [0x7c00+511]    ; 0xaa
call printh

; to disable A20 line
; mov ax, 0x2400
; int 0x15

call testA20

jmp fin

; functions
%include "printf.s"
%include "readDisk.s"
%include "printh.s"
%include "testA20.s"

; string here
STR_1: db "Welcome to FireOS", 0x0a, 0x0d, 0
STR_2: db "Loaded in 16-bit Real Mode to memory location at 0x7c00", 0x0a, 0x0d, 0
DISK_ERR_MSG: db "Error Loading Disk...", 0x0a, 0x0d, 0
TEST_STR: db "Disk loaded successfully, you are in the second sector now", 0x0a, 0x0d, 0

fin:
    hlt
    jmp fin

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55

; the second sector
test:
    mov si, TEST_STR
    call printf
    ret

times 512 db 0
