//
// Created by jefffu on 2020/11/8.
//

#include "kernel.h"
#include "iostream"
#include "string"
#include "PCB.h"
using namespace std;

bool proc_init = false;
// res: 0, 1, 2, 3
int res_remain[4] = {1, 1, 2, 2};
// priority 0, 1, 2: init, user, system
vector<PCB*> ready_list[3];
vector<PCB*> block_list[3];
PCB* running_proc;

void init() {
    cout << "Process init is running" << endl;
    proc_init = true;
}

void create_process(string name, int priority) {
    if (!proc_init) {
        cout << "Please run init process at first." << endl;
        return;
    }
    PCB* p = new PCB(name, "running", priority);
    ready_list[1].push_back(p);
    // create process 'name', priority 'priority'
    cout << "Process " << name << " is running" << endl;
}

void delete_process(string name) {
    if (!proc_init) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "Delete process " << name << endl;
}

void request_res(string name, int id) {
    if (!proc_init) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "request resource " << name << ", id=" << id << endl;
}

void release_res(string name, int id) {
    if (!proc_init) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "release resource " << name << ", id=" << id << endl;
}

void time_out() {
    if (!proc_init) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "System timeout interrupt" << endl;
}

void list_info(string option) {
//    if (!proc_init) {
//        cout << "Please run init process at first." << endl;
//        return;
//    }
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
        case 2: {
            for (int i = 0; i < 4; i++) {
                cout << "R" << i+1 << " " << res_remain[i] << endl;
            }
            break;
        }
        // invalid options
        default: cout << "Invalid list option, please input again." << endl;
    }
}

void print_info(string name) {
//    if (!proc_init) {
//        cout << "Please run init process at first." << endl;
//        return;
//    }
    PCB* p = NULL;
    // find in ready list
    for (int i = 0; i < 3; i++) {
        for (PCB* tmp : ready_list[i]) {
            if (tmp->get_pid() == name) p = tmp;
        }
    }
    // find in block list
    for (int i = 0; i < 3; i++) {
        for (PCB* tmp : block_list[i]) {
            if (tmp->get_pid() == name) p = tmp;
        }
    }
    if (p == NULL) cout << "Process " << name << " does not exist." << endl;
    else {
        cout << "****************************" << endl;
        cout << "Information of process " << name << endl;
        cout << "****************************" << endl;
        p->display();
    }
}
