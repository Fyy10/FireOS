//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_KERNEL_H
#define FIREOS_KERNEL_H

#include "string"
using namespace std;

// kernel functions
void init();
void create_process(string, int);
void delete_process(string);

#endif //FIREOS_KERNEL_H
