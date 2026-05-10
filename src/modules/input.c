#include "../headers/input.h"
#include "../headers/config.h"
//#include "../headers/whyshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

#define RESET "\033[0m"

/*
Why-shell input.c | Made by: GusDev
--------------------
*/

int setInput(Config *config) {
    char *inputToCheck = config->inputForUser;
    char *output = config->finalInput;

    int j = 0;

    for (int i = 0;inputToCheck[i] != '\0'; i++) {
        if (inputToCheck[i] == '\\') {
            switch (inputToCheck[i+1]) {
                // p = path
                case 'p': {
                    char cwd[1024];
                    getcwd(cwd, sizeof(cwd));

                    char *folder = strrchr(cwd, '/');

                    if (folder != NULL) {
                        strcpy(&output[j], config->pathColor);
                        j += strlen(config->pathColor);
                        strcpy(&output[j], folder);
                        j += strlen(folder);
                        strcpy(&output[j], RESET);
                        j += strlen(RESET);
                    }

                    i++;
                    continue;
                }

                // P = complete path
                case 'P': {
                    char cwd[1024];
                    getcwd(cwd, sizeof(cwd));
                    strcpy(&output[j], config->pathColor);
                    j += strlen(config->pathColor);
                    strcpy(&output[j], cwd);
                    j += strlen(cwd);
                    strcpy(&output[j], RESET);
                    j += strlen(RESET);

                    i++;
                    continue;
                }

                // u = user
                case 'u': {
                    struct passwd *pw;
                    pw = getpwuid(geteuid());
                    if (pw != NULL) {
                        strcpy(&output[j], config->userColor);
                        j += strlen(config->userColor);
                        strcpy(&output[j], pw->pw_name);
                        j += strlen(pw->pw_name);
                        strcpy(&output[j], RESET);
                        j += strlen(RESET);
                    }

                    i++;
                    continue;
                }

                // h = hostname
                case 'h': {
                    char hostname[256];
                    if (gethostname(hostname, sizeof(hostname)) == 0) {
                        strcpy(&output[j], config->hostnameColor);
                        j += strlen(config->hostnameColor);
                        strcpy(&output[j], hostname);
                        j += strlen(hostname);
                        strcpy(&output[j], RESET);
                        j += strlen(RESET);
                    }

                    i++;
                    continue;
                }

                //t = time
                case 't': {
                    time_t now = time(NULL);

                    struct tm *t = localtime(&now);
                    char date[64];

                    strftime(date, sizeof(date), "%H:%M", t);
                    strcpy(&output[j], date);
                    j += strlen(date);

                    i++;
                    continue;
                }

                // T = complete-time
                case 'T': {
                    time_t now = time(NULL);

                    struct tm *t = localtime(&now);
                    char date[64];

                    strftime(date, sizeof(date), "%H:%M:%S", t);

                    strcpy(&output[j], date);
                    j += strlen(date);

                    i++;
                    continue;
                }
                
                // d = date
                case 'd': {
                    time_t now = time(NULL);

                    struct tm *t = localtime(&now);
                    char date[64];

                    strftime(date, sizeof(date), "%d/%m/%Y", t);

                    strcpy(&output[j], date);
                    j += strlen(date);

                    i++;
                    continue;
                }

                // D = better date
                case 'D': {
                    time_t now = time(NULL);

                    struct tm *t = localtime(&now);
                    char date[64];

                    strftime(date, sizeof(date), "%A (%d) of %B, %Y", t);

                    strcpy(&output[j], date);
                    j += strlen(date);

                    i++;
                    continue;
                }

                // v = version
                case 'v': {
                    char version[256] = "";
                    strcat(version, __NAME);
                    strcat(version, " ");
                    strcat(version, __VERSION);
                    
                    strcpy(&output[j], version);
                    j += strlen(version);

                    i++;
                    continue;
                }
            }
        }
        output[j++] = inputToCheck[i];
    }
    output[j] = '\0';
    return 0;
}