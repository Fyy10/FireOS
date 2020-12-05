void io_hlt(void);

void FireMain(void)
{
fin:
    io_hlt();
    goto fin;
}
