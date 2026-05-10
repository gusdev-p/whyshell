#include "../headers/command-parser.h"
//#include "../headers/whyshell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void parseCommand(char *input) {
    char *token = strtok(input, " ");

    while (token != NULL) {
        if (strcmp(token, "exit") == 0 || strcmp(token, "quit") == 0 || strcmp(token, "give-up") == 0) {
            char *arg = strtok(NULL, " ");
            if (arg && strcmp(arg, "bad") == 0) {
                exit(1);
            }
            exit(0);
        } else if (strcmp(token, "version") == 0) {
            // logo arrays
            char *topLeft[] = {
                "██▒         ██▒   ██▒     ██▒   ██▒     ██▒                         |",
                "██▒   ██▒   ██▒   ██▒     ██▒     ██▒ ██▒                           |",
                "██▒   ██▒   ██▒   ██████████▒       ██▒                             |",
                "██▒   ██▒   ██▒   ██▒     ██▒       ██▒                             |",
                "██████████████▒   ██▒     ██▒       ██▒                             |"};
            char *downLeft[] = {
                "  ████████████▒   ██▒     ██▒   █████████▒   ██▒         ██▒        |",
                "██▒               ██▒     ██▒   ██▒          ██▒         ██▒        |",
                "  ██████████▒     ██████████▒   ███████▒     ██▒         ██▒        |",
                "            ██▒   ██▒     ██▒   ██▒          ██▒         ██▒        |",
                "  ██████████▒     ██▒     ██▒   █████████▒   ████████▒   ███████▒   |"
            };
            // infos array
            char *topRight[] = {
                "Compilation informations:",
                "├──Name:",
                "├──Version:",
                "├──Complete name:",
                "└──Developer(s):"
            };
            // top line
            for (int i = 0; i < 100; i++)
            {
                printf("-");
            }
            printf("\n");

            // print the topLeft and the topRight
            for (int i = 0; i < 5; i++) {

                printf(
                    "\033[38;2;255;165;0m%-70s\033[0m ",
                        topLeft[i]
                );

                switch (i)
                {
                case 0:
                    printf("%s", topRight[i]);
                    break;
                case 1:
                    printf("%s %s", topRight[i], __NAME);
                    break;
                case 2:
                    printf("%s %s", topRight[i], __VERSION);
                    break;
                case 3:
                    printf(
                        "%s %s version %s",
                        topRight[i],
                        __NAME,
                        __VERSION
                    );
                    break;
                case 4:
                    printf("%s %s", topRight[i], __DEVS);
                    break;
                }
                printf("\n");
            }
            
            // space
            printf("\n");
            
            // print downLeft
            for (int i = 0; i < 5; i++) {
                printf("\033[38;2;255;165;0m%s\033[0m\n", downLeft[i]);
            }
            

            // down line
            for (int i = 0; i < 100; i++)
            {
                printf("-");
            }
            printf("\n");
        }

        token = strtok(NULL, " ");
    }
}
