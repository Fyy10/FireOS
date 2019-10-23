;helloworld!
;TAB = 4
;FAT12 format floppy only

    DB  0xeb, 0x4e, 0x90
    DB  "HELLOIPL"  ;启动区名称，任意字符串（8字节）
    DW  512         ;每个扇区的大小，只能为512字节
    DB  1           ;簇的大小，只能为1字节
    DW  1           ;FAT starting position (usually from 1)
    DB  2           ;number of FAT (ought to be 2)
    DW  224         ;size of root menu (usually set to 224)
    DW  2880        ;size of disk (ought to be 2880)
    DB  0xf0        ;type of disk (ought to be 0xf0)
    DW  9           ;length of FAT (ought to be 9)
    DW  18          ;how many tracks in one sector (ought to be 18)
    DW  2           ;number of head (ought to be 2)
    DD  0           ;no separate, ought to be 0
    DD  2880        ;rewrite the size of disk
    DB  0, 0, 0x29  ;unknown
    DD  0xffffffff  ;(maybe) the number of file
    DB  "FIRE-OS    "   ;name of the disk (11 bytes)
    DB  "FAT12   "      ;format of the disk (8 bytes)
    RESB    18;

;main
    DB  0xb8, 0x00, 0x00, 0x8e, 0xd0, 0xbc, 0x00, 0x7c
    DB  0x8e, 0xd8, 0x8e, 0xc0, 0xbe, 0x74, 0x7c, 0x8a
    DB  0x04, 0x83, 0xc6, 0x01, 0x3c, 0x00, 0x74, 0x09
    DB  0xb4, 0x0e, 0xbb, 0x0f, 0x00, 0xcd, 0x10, 0xeb
    DB  0xee, 0xf4, 0xeb, 0xfd

;display information
    DB  0x0a, 0x0a  ;2 new lines
    DB  "Hello world!"
    DB  0x0a
    DB  0

    ;RESB    378     ;fill 0x00 until 0x001fe    本应该是0x1fe-$但不知道为啥报错了Orz
	TIMES	0x1fe-($-$$) DB 0x00
    DB  0x55, 0xaa  ;引导区的最后两字节必须是这俩

;启动区以外部分的输出
    DB  0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
    RESB    4600
    DB  0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
    RESB    1469432
