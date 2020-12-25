//
// Created by jefffu on 2020/11/8.
//

#include "kernel.h"
#include "iostream"
#include "string"
#include "list"
#include "PCB.h"
#include "RCB.h"
using namespace std;

// initialize resource list (waiting list is the block list)
RCB res_list[4] = {RCB("R1", 1), RCB("R2", 2), RCB("R3", 3), RCB("R4", 4)};
// priority 0, 1, 2: init, user, system
list<PCB*> ready_list[3];
// NULL if not initialized
PCB* running_proc = NULL;
//PCB* timeout_proc = NULL;

void scheduler() {
    // check the block list (res), allocate res and change status
    for (int i = 0; i < 4; i++) {
        while (!res_list[i].waiting_list.empty()) {
            PCB* p = res_list[i].waiting_list.front();
            if (res_list[i].available >= p->req_res[i]) {
                res_list[i].waiting_list.pop_front();
                res_list[i].available -= p->req_res[i];
                p->res[i] += p->req_res[i];
                p->req_res[i] = 0;
                p->status = "ready";
                cout << "Wake up process " << p->pid << endl;
                ready_list[p->priority].push_back(p);
            }
            else break;
        }
    }
    // choose the correct process from ready list and set the status to running
    // make sure init is in the ready list
    for (int i = 2; i >= 0; i--) {
        if (ready_list[i].empty()) continue;
        // else
        running_proc = ready_list[i].front();
        ready_list[i].pop_front();
        running_proc->status = "running";
        break;
    }
    cout << "Process " << running_proc->pid << " is " << running_proc->status << "." << endl;
//    if (timeout_proc != NULL && timeout_proc != running_proc) {
//        cout << "Process " << timeout_proc->pid << " is " << timeout_proc->status << "." << endl;
//    }
//    timeout_proc = NULL;
}

// find in ready/block list
PCB* find_process(string name) {
    PCB* p = NULL;
    // find in ready list
    for (int i = 0; i < 3; i++) {
        for (PCB* tmp : ready_list[i]) {
            if (tmp->pid == name) p = tmp;
        }
    }
    // find in block list
    for (int i = 0; i < 4; i++) {
        for (PCB* tmp : res_list[i].waiting_list) {
            if (tmp->pid == name) p = tmp;
        }
    }
    return p;
}

// used for deleting process
void kill_tree(PCB* p) {
    cout << "Delete process " << p->pid << ":" << endl;
    // recursively release resource
    for (int i = 0; i < 4; i++) {
        res_list[i].available += p->res[i];
        cout << "    " << "Release " << p->res[i] << " " << res_list[i].rid << endl;
    }
    for (PCB* son_ptr : p->sons) {
        kill_tree(son_ptr);
    }

    if (p == running_proc) {
        p->status = "dead";
        return;
    }
    // remove from ready/block list
    int i;
    for (i = 0; i < 4; i++) {
        if (p->req_res[i] > 0) break;
    }
    if (i == 4) {
        // ready
        ready_list[p->priority].remove(p);
    }
    else {
        // blocked
        res_list[i].waiting_list.remove(p);
    }
}

void init() {
    if (running_proc != NULL) {
        cout << "Already initialized." << endl;
        cout << "Process " << running_proc->pid << " is running." << endl;
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
    running_proc->status = "ready";
    ready_list[running_proc->priority].push_front(running_proc);
    scheduler();
}

void delete_process(string name) {
    PCB* p = find_process(name);
    if (p != NULL) {
        kill_tree(p);
        delete p;
    }
    // find in running
    if (running_proc->pid == name) {
        p = running_proc;
        kill_tree(p);
        delete p;
    }
    else ready_list[running_proc->priority].push_front(running_proc);
    if (p == NULL) cout << "Process " << name << " does not exist." << endl;
    scheduler();
}

void request_res(string name, int n) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    int i;
    for (i = 0; i < 4; i++) {
        if (res_list[i].rid == name) break;
    }
    if (i == 4) {
        cout << "Resource " << name << " not found." << endl;
        return;
    }
    if (res_list[i].available >= n) {
        cout << "Process " << running_proc->pid << " requests " << n << " " << name << endl;
        res_list[i].available -= n;
        running_proc->res[i] += n;
        running_proc->status = "ready";
        ready_list[running_proc->priority].push_front(running_proc);
    }
    else {
        if (res_list[i].num < n) {
            cout << "Error: requested more than total, killing process " << running_proc->pid << "..." << endl;
            delete_process(running_proc->pid);
            return;
        }
        running_proc->status = "blocked";
        running_proc->req_res[i] += n;
        cout << "Process " << running_proc->pid << " is " << running_proc->status << "." << endl;
        res_list[i].waiting_list.push_back(running_proc);
    }
    scheduler();
}

void release_res(string name, int n) {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    int i;
    for (i = 0; i < 4; i++) {
        if (res_list[i].rid == name) break;
    }
    if (i == 4) {
        cout << "Resource " << name << " not found." << endl;
        return;
    }
    if (n > running_proc->res[i]) {
        cout << "Error: released more than requested." << endl;
        return;
    }
    cout << "Process " << running_proc->pid << " releases " << n << " " << name << endl;
    res_list[i].available += n;
    running_proc->res[i] -= n;
    if (!res_list[i].waiting_list.empty()) {
        list<PCB*>::iterator it;
        for (it = res_list[i].waiting_list.begin(); it != res_list[i].waiting_list.end(); it++) {
            if ((*it)->req_res[i] <= res_list[i].available) break;
        }
        PCB* p = *it;
        p->req_res[i] = 0;
        bool ready_flag = true;
        for (int i = 0; i < 4; i++) {
            if (p->req_res[i] != 0) ready_flag = false;
        }
        if (ready_flag) {
            p->status = "ready";
            ready_list[p->priority].push_back(p);
        }
    }
    running_proc->status = "ready";
    ready_list[running_proc->priority].push_front(running_proc);
    scheduler();
}

void time_out() {
    if (running_proc == NULL) {
        cout << "Please run init process at first." << endl;
        return;
    }
    running_proc->status = "ready";
    cout << "Process " << running_proc->pid << " is " << running_proc->status << "." << endl;
    ready_list[running_proc->priority].push_back(running_proc);
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
                    cout << tmp->pid;
                    if (tmp != ready_list[i].back()) cout << "-";
                }
                cout << endl;
            }
            break;
        }
        // list block
        case 1: {
            for (int i = 0; i < 4; i++) {
                cout << res_list[i].rid << " ";
                for (PCB* p : res_list[i].waiting_list) {
                    cout << p->pid;
                    if (p != res_list[i].waiting_list.back()) cout << "-";
                }
                cout << endl;
            }
            break;
        }
        // list res
        case 2: {
            for (int i = 0; i < 4; i++) {
                cout << res_list[i].rid << " " << res_list[i].available << endl;
            }
            break;
        }
        // invalid options
        default: cout << "Invalid list option, please input again." << endl;
    }
}

void print_info(string name) {
    PCB* p = find_process(name);
    if (running_proc->pid == name) p = running_proc;
    if (p == NULL) cout << "Process " << name << " does not exist." << endl;
    else {
        cout << "****************************" << endl;
        cout << "Information of process " << name << endl;
        cout << "****************************" << endl;

        cout << "PID: " << p->pid << endl;
        cout << "Status: " << p->status << endl;
        cout << "Priority: " << p->priority << endl;
        cout << "Resources requested:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "    " << res_list[i].rid << " " << p->res[i] << endl;
        }
        cout << "Resources requesting:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "    " << res_list[i].rid << " " << p->req_res[i] << endl;
        }
    }
}
