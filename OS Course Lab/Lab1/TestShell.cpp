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
    const int num_commands = 8;
    string commands[num_commands] = {"init", "cr", "de", "req", "rel", "to", "list", "pr"};
    // read command
    string command;
    while (1) {
        cout << "TestShell> ";
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
            // init
            case 0: init(); break;
            // cr
            case 1: create_process(command, 1); break;
            // de
            case 2: delete_process(command); break;
            // req
            case 3: request_res("CPU", 0); break;
            // rel
            case 4: release_res("GPU", 0); break;
            // to
            case 5: time_out(); break;
            // list
            case 6: list_info("block"); break;
            // pr
            case 7: print_info("process 1"); break;
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
