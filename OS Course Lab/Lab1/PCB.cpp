//
// Created by jefffu on 2020/11/8.
//

#include "PCB.h"
#include "iostream"

using namespace std;

PCB::PCB(string pid, string status, int priority, PCB* father) {
    this->pid = pid;
    this->status = status;
    this->priority = priority;
    this->father = father;
}

PCB::~PCB() {
    if (this->father != NULL) delete this->father;
    for (PCB* son : this->sons) delete son;
}

string PCB::get_pid() {
    return pid;
}

string PCB::get_status() {
    return status;
}

int PCB::get_priority() {
    return priority;
}

void PCB::display() {
    cout << "PID: " << pid << endl;
    cout << "Status: " << status << endl;
    cout << "Priority: " << priority << endl;

    cout << "Resources: ";
    for (int res_id : res) {
        cout << res_id << " ";
    }
    cout << endl;
}

void PCB::kill() {
    for (PCB* son_ptr : sons) {
        if (son_ptr != NULL) son_ptr->kill();
    }
}
