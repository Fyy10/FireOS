//
// Created by jefffu on 2020/11/8.
//

#include "kernel.h"
#include "iostream"
#include "string"
#include "list"
#include "PCB.h"
using namespace std;

// res: 0, 1, 2, 3
int res_remain[4] = {1, 1, 2, 2};
// priority 0, 1, 2: init, user, system
list<PCB*> ready_list[3];
list<PCB*> block_list[3];
// NULL if not initialized
PCB* running_proc = NULL;

void scheduler() {
    // choose the correct process from ready list and set the status to running
    // make sure init is in the ready list
    for (int i = 2; i >= 0; i--) {
        if (ready_list[i].empty()) continue;
        // else
        running_proc = ready_list[i].front();
        ready_list[i].pop_front();
        running_proc->set_status("running");
        break;
    }
    cout << "Process " << running_proc->get_pid() << " is running." << endl;
}

void init() {
    if (running_proc != NULL) {
        cout << "Already initialized." << endl;
        cout << "Process " << running_proc->get_pid() << " is running." << endl;
        return;
    }
    PCB* p = new PCB("init", 0);
    ready_list[0].push_back(p);
    scheduler();
}

void create_process(string name, int priority) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    // create process 'name', priority 'priority'
    PCB* p = new PCB(name, priority);
    ready_list[priority].push_back(p);
    running_proc->set_status("ready");
    ready_list[running_proc->get_priority()].push_front(running_proc);
    scheduler();
}

void delete_process(string name) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "Delete process " << name << endl;
}

void request_res(string name, int id) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "request resource " << name << ", id=" << id << endl;
}

void release_res(string name, int id) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    cout << "release resource " << name << ", id=" << id << endl;
}

void time_out() {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    running_proc->set_status("ready");
    ready_list[running_proc->get_priority()].push_back(running_proc);
    scheduler();
}

void list_info(string option) {
    // number of valid options
    const int num_valid_op = 3;
    // valid options
    string valid_ops[num_valid_op] = {"ready", "block", "res"};
    // get option id
    int op_id;
    for (op_id = 0; op_id < num_valid_op; op_id++) {
        if (valid_ops[op_id] == option) break;
    }
    // execute command with option
    switch (op_id) {
        // valid options
        // list ready
        case 0: {
            for (int i = 2; i >= 0; i--) {
                cout << i << ": ";
                for (PCB* tmp : ready_list[i]) {
                    cout << tmp->get_pid();
                    if (tmp != ready_list[i].back()) cout << "-";
                }
                cout << endl;
            }
            break;
        }
        // list block
        case 1: {
            for (int i = 2; i >= 0; i--) {
                cout << i << ": ";
                for (PCB* tmp : block_list[i]) {
                    cout << tmp->get_pid();
                    if (tmp != block_list[i].back()) cout << "-";
                }
                cout << endl;
            }
            break;
        }
        // list res
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
