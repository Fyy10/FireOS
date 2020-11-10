//
// Created by jefffu on 2020/11/8.
//

#include "kernel.h"
#include "iostream"
#include "string"
using namespace std;

void init() {
    cout << "init program" << endl;
}

void create_process(string name, int priority) {
    cout << "Create process " << name << ", priority " << priority << endl;
}

void delete_process(string name) {
    cout << "Delete process " << name << endl;
}
