//
// Created by jefffu on 2020/11/8.
//

#include "TestShell.h"
#include "kernel.h"
#include "iostream"
#include "string"
#include "vector"

using namespace std;

int main(int argc, char* argv[]) {
    const int num_commands = 6;
    string commands[num_commands] = {"-init", "-cr", "-de", "-req", "-rel", "-to"};
    // read command
    string command;
    while (1) {
        getline(cin, command);
        // exit test shell
        if (command == "exit")
            break;
        // get command id
        int command_id;
        for (command_id = 0; command_id < num_commands; command_id++) {
            if (commands[command_id] == command) break;
        }
        // execute commands
        switch (command_id) {
            // valid commands
            case 0: init(); break;
            case 1: create_process(command, 1); break;
            case 2: delete_process(command); break;
            // invalid commands
            default: cout << "Invalid command, please input again." << endl;
        }
    }
    return 0;
}

// extract parameters from commands
vector<string> extract_parameters(string) {
    vector<string> params;
    params[0] = "a";
    return params;
}
