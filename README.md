# FireOS

An OS using C/C++, for personal use and practice.

计划用C/C++开发的弱鸡操作系统，仅供个人沙雕开发用。

## 使用方法

在linux环境中用nasm编译hello.s

```shell
nasm hello.s -o hello.img
```

用QEMU运行

```shell
qemu-system-i386 hello.img
```

或者使用如下方式：

```shell
make
make run
make clean
```
