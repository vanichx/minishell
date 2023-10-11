#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;
    char* prompt = "testcli> ";

    while (1) {
        input = readline(prompt);

        if (!input) {
            // Handle EOF or error
            break;
        }

        // Add the input to the history
        if (input[0] != '\0') {
            add_history(input);
        }

        // Do something with the input
        if (strcmp(input, "ifconfig") == 0) {
            system("ifconfig");
        } else if (strcmp(input, "date") == 0) {
            system("date");
        } else if (strcmp(input, "ls") == 0) {
            system("ls");
        } else if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "e") == 0 || strcmp(input, "q") == 0) {
            free(input);
            break;
        }

        // Clean up
        free(input);

        // Move to a new line and update the display
        rl_on_new_line(0);
        rl_forced_update_display();
    }

    return 0;
}
