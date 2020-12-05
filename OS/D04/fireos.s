; BOOT_INFO
CYLS    EQU     0x0ff0      ; 设定启动区
LEDS    EQU     0x0ff1
VMODE   EQU     0x0ff2      ; 关于颜色数目的信息，颜色的位数
SCRNX   EQU     0x0ff4      ; 分辨率的X
SCRNY   EQU     0x0ff6      ; 分辨率的Y
VRAM    EQU     0x0ff8      ; 图像缓冲区的开始地址

; floppy:
; 0x002600: filename
; 0x004200: content
    ORG     0xc200  ; 0x8000（不应该是0x8200？） + 0x4200

    ; video mode:
    ; AH=0x00
    ; AL=mode(0x03, 0x12, 0x13, 0x6a)
    MOV     AL, 0x13    ; VGA显卡，320x200x8位彩色
    MOV     AH, 0x00
    INT     0x10

    MOV     BYTE [VMODE], 8     ; 记录画面模式
    MOV     WORD [SCRNX], 320
    MOV     WORD [SCRNY], 200
    MOV     DWORD [VRAM], 0x000a0000

    ; 用BIOS取得键盘上的LED灯状态
    MOV     AH, 0x02
    INT     0x16        ; keyboard BIOS
    MOV     [LEDS], AL

fin:
    HLT
    JMP fin
