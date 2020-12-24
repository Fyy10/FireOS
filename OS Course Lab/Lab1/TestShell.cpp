//
// Created by jefffu on 2020/11/8.
//

#include "TestShell.h"
#include "kernel.h"
#include "iostream"
#include "string"
#include "vector"
#include "stdlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    // define the number of valid commands
    const int num_commands = 8;
    // list of valid commands
    string commands[num_commands] = {"init", "cr", "de", "req", "rel", "to", "list", "pr"};
    // read command
    string command;
    while (1) {
        cout << "TestShell> ";
        getline(cin, command);
        if (command.empty()) continue;
        // array for analyzing params
        string params[10];
        extract_parameters(command, params);
        // exit test shell
        if (params[0] == "exit")
            break;
        // get command id
        int command_id;
        for (command_id = 0; command_id < num_commands; command_id++) {
            if (commands[command_id] == params[0]) break;
        }
        // execute commands
        switch (command_id) {
            // valid commands
            // init
            case 0: init(); break;
            // cr
            case 1: create_process(params[1], stoi(params[2])); break;
            // de
            case 2: delete_process(params[1]); break;
            // req
            case 3: request_res(params[1], stoi(params[2])); break;
            // rel
            case 4: release_res(params[1], stoi(params[2])); break;
            // to
            case 5: time_out(); break;
            // list
            case 6: list_info(params[1]); break;
            // pr
            case 7: print_info(params[1]); break;
            // invalid commands
            default: {
                cout << "Invalid command, using system shell:" << endl;
                system(command.data());
            }
        }
    }
    return 0;
}

// extract parameters from command
int extract_parameters(string command, string* params) {
    int n = command.length();
    int i = 0, j = 0, pid = 0;
    // i: left index of param
    // j: right index of param
    // pid: param id
    for (i = 0; i < n; i++) {
        if (command[i] == ' ' || command[i] == '\t') continue;
        for (j = i; j < n; j++) {
            if (command[j] == ' ' || command[j] == '\t') break;
        }
        // cout << i << ", " << j << endl;
        params[pid++] = command.substr(i, j - i);
        i = j;
    }
    // output params
    /*for (i = 0; i < pid; i++) {
        // cout << i << endl;
        cout << params[i] << endl;
    }*/
    // return number of params
    return pid;
}
