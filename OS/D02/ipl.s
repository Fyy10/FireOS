; hello
; TAB=4

    ORG     0x7c00      ; indicates the position to load program

; for FAT12 floppy only

    JMP     entry
    DB      0x90
    DB  "HELLOIPL"  ; 启动区名称，任意字符串（8字节）
    DW  512         ; 每个扇区的大小，只能为512字节
    DB  1           ; 簇的大小，只能为1字节
    DW  1           ; FAT starting position (usually from 1)
    DB  2           ; number of FAT (ought to be 2)
    DW  224         ; size of root menu (usually set to 224)
    DW  2880        ; size of disk (ought to be 2880)
    DB  0xf0        ; type of disk (ought to be 0xf0)
    DW  9           ; length of FAT (ought to be 9)
    DW  18          ; how many tracks in one sector (ought to be 18)
    DW  2           ; number of head (ought to be 2)
    DD  0           ; no separate, ought to be 0
    DD  2880        ; rewrite the size of disk
    DB  0, 0, 0x29  ; unknown
    DD  0xffffffff  ; (maybe) the number of file
    DB  "FIRE-OS    "   ; name of the disk (11 bytes)
    DB  "FAT12   "      ; format of the disk (8 bytes)
    RESB    18

entry:
    MOV     AX, 0   ; initialize registers
    MOV     SS, AX
    MOV     SP, 0x7c00
    MOV     DS, AX
    MOV     ES, AX

    MOV     SI, msg

; display msg
putloop:
; 显示一个字符：
; AH=0x0e
; AL=character code
; BH=0
; BL=color code
; 用INT 0x10调用显卡BIOS
    MOV     AL, [SI]
    ADD     SI, 1
    CMP     AL, 0
    JE      fin

    MOV     AH, 0x0e    ; 显示一个文字
    MOV     BX, 15      ; 指定字符颜色
    INT     0x10        ; 调用显卡BIOS
    JMP     putloop

fin:
    HLT             ; 让CPU停止，等待指令
    JMP     fin     ; loop

msg:
    DB      0x0a, 0x0a  ; 2 new lines
    DB      "Hello, World!"
    DB      0x0a        ; new line
    DB      0

    ; 这里前后不一致？0x1fe? 0x7dfe?
    RESB    0x1fe-($-$$)    ; fill 0x00 until 0x1fe
    DB  0x55, 0xaa          ;引导区的最后两字节必须是这俩

