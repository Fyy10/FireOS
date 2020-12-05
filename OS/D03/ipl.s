; FireOS-ipl
; TAB=4

CYLS    EQU     10

    ORG     0x7c00      ; indicates the position to load program

; for FAT12 floppy only

    JMP     entry
    DB      0x90
    DB  "FIRE IPL"  ; 启动区名称，任意字符串（8字节）
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

    ; 设置显示模式
    MOV     AL, 0x13    ; VGA显卡，320x200x8位彩色
    MOV     AH, 0x00
    INT     0x10

; 读磁盘
; choose a free memory area
; view https://wiki.osdev.org/Memory_Map_(x86) for more information
    ; MOV     AX, 0x07e0
    ; MOV     AX, 0x0820
    MOV     AX, 0
    MOV     ES, AX
    MOV     CH, 0   ; 柱面0
    MOV     DH, 0   ; 磁头0
    MOV     CL, 2   ; 扇区2（第一个扇区装的是IPL）

readloop:
    ; retry if loading fails

    MOV     SI, 0   ; count the number of failures

retry:
    MOV     AH, 0x02    ; AH=0x02：读盘
    MOV     AL, 1       ; 1个扇区
    MOV     BX, 0
    ; MOV     DL, 0x00  ; A驱动器 (for floppy / flash drive)
    MOV     DL, 0x80    ; for hard disk (qemu emulates hard disk)
    INT     0x13        ; 调用磁盘BIOS

    ; 返回AH status为0x20（控制器失败）？？？

    JNC     next        ; jump to next if no error
    ADD     SI, 1       ; cnt++
    CMP     SI, 5       ; retry 5 times in total
    JAE     error       ; jump to error after 5 trails
    MOV     AH, 0x00
    MOV     DL, 0x00    ; A驱动器
    INT     0x13        ; 重置驱动器
    JMP     retry
next:
    MOV     AX, ES
    ADD     AX, 0x0020      ; move to next sector (0x0020 = 512 / 16)
    MOV     ES, AX          ; 最终目的是得到ES=ES+0x20
    ADD     CL, 1           ; 读取下一个扇区
    CMP     CL, 18          ; 读取到18扇区
    JBE     readloop        ; jump to readloop if CL <= 18
    MOV     CL, 1
    ADD     DH, 1
    CMP     DH, 2
    JB      readloop        ; jump to readloop if DH < 2
    MOV     DH, 0
    ADD     CH, 1
    CMP     CH, CYLS
    JB      readloop    ; jump to readloop if CH < CYLS

    MOV     [0x0ff0], CH    ; 将CYLS的值写到0x0ff0
    JMP     0xc200      ; 跳转到fireos.sys所在地址段，这里0xc200略存疑

error:
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
    DB      "Load Error"
    DB      0x0a        ; new line
    DB      0

    ; 这里前后不一致？0x1fe? 0x7dfe?
    RESB    0x1fe-($-$$)    ; fill 0x00 until 0x1fe
    DB  0x55, 0xaa          ;引导区的最后两字节必须是这俩(DW 0xAA55)
