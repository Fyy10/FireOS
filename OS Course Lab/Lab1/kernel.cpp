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

void request_res(string name, int id) {
    cout << "request resource " << name << ", id=" << id << endl;
}

void release_res(string name, int id) {
    cout << "release resource " << name << ", id=" << id << endl;
}

void time_out() {
    cout << "System timeout interrupt" << endl;
}

void list_info(string option) {
    const int num_valid_op = 3;
    string valid_ops[num_valid_op] = {"ready", "block", "res"};
    // get option id
    int op_id;
    for (op_id = 0; op_id < num_valid_op; op_id++) {
        if (valid_ops[op_id] == option) break;
    }
    // execute command with option
    switch (op_id) {
        // valid options
        // todo: ready
        case 0: cout << "list ready" << endl; break;
        // todo: block
        case 1: cout << "list block" << endl; break;
        // todo: res
        case 2: cout << "list res" << endl; break;
        // invalid options
        default: cout << "Invalid list option, please input again." << endl;
    }
}
void print_info(string name) {
    cout << "Information of process " << name << endl;
}

