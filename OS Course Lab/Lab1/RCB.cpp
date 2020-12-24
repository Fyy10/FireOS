//
// Created by jefffu on 2020/12/22.
//

#include "RCB.h"

RCB::RCB(string rid, int n) {
    this->rid = rid;
    this->available = this->num = n;
}

RCB::~RCB() {
}
