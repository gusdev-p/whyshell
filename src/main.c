#include "headers/config.h"
#include "headers/input.h"
#include "headers/command-parser.h"
#include "headers/executer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <locale.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>


int main() {
    setlocale(LC_ALL, "");
    Config config;

    if (!loadConfig("/home/gustavo/Projetos/why-shell/tests/config.conf", &config)) {
        printf("Cant load config file :(\n");
        return 1;
    }
    setInput(&config);
    char buffer[256];
    read_history("/home/gustavo/Projetos/why-shell/tests/whyshell_history");
    while (1)
    {
        char *input = readline(config.finalInput);
        add_history(input);
        write_history("/home/gustavo/Projetos/why-shell/tests/whyshell_history");
        parseCommand(input);
        input[strcspn(input, "\n")] = 0;

        char *args[64];
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            fprintf(stderr, "WhyShell: Cant found the command: '%s' :(\n", args[0], strerror(errno));
            exit(1);
        } else {
            wait(NULL);
        }

        free(input);
    }
    return 0;
}