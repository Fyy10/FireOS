//
// Created by jefffu on 2020/11/8.
//

#ifndef FIREOS_PCB_H
#define FIREOS_PCB_H

//#include "bits/stdc++.h"
#include "vector"
using namespace std;

class PCB {
private:
    int process_id;
    PCB* father;
    vector<PCB*> son;
};


#endif //FIREOS_PCB_H
