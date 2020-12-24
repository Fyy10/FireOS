//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_KERNEL_H
#define FIREOS_KERNEL_H

#include "string"
#include "PCB.h"
using namespace std;

// scheduler
void scheduler();
// kernel functions
PCB* find_process(string name);
void kill_tree(PCB*);

void init();
void create_process(string, int);
void delete_process(string);
void request_res(string, int);
void release_res(string, int);
void time_out();
void list_info(string);
void print_info(string);

#endif //FIREOS_KERNEL_H
