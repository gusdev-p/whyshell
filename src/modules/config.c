#include <stdio.h>
#include <string.h>
#include "../headers/config.h"

/*
Why-Shell config.c | Made by: GusDev
---------------------

*/

void trimQuotes(char *str) {
    int len = strlen(str);

    if (str[0] == '"') {
        memmove(str, str + 1, len);
        len--;
    }
    if (len > 0 && str[len - 1] == '"') {
        str[len - 1] = '\0';
    }
}

void parseEscapeSequences(char *str) {
    char buffer[128];
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && str[i + 1] == '0' &&
            str[i + 2] == '3' && str[i+ 3] == '3') {
            buffer[j++] = '\033';
            i += 3;
        } else if (str[i] == '\\' && str[i+1] == 'n') {
            buffer[j++] = '\n';
            i++;
        } else {
            buffer[j++] = str[i];
        }
    }

    buffer[j] = '\0';
    strcpy(str, buffer);
}

int loadConfig(const char *filename, Config *config) {
    // init basic configs
    strcpy(config->userColor, "\033[0m");
    strcpy(config->pathColor, "\033[0m");
    strcpy(config->hostnameColor, "\033[0m");
    
    FILE *file = fopen(filename, "r");
    if (!file)
        return 0;

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n')
            continue;

        char key[128], value[128];

        if (sscanf(line, "%127[^=]=%127[^\n]", key, value) == 2) {

            trimQuotes(value);
            parseEscapeSequences(value);

            if (strcmp(key, "inputForUser") == 0) {
                strcpy(config->inputForUser, value);
            } else if (strcmp(key, "userColor") == 0) {
                strcpy(config->userColor, value);
            } else if (strcmp(key, "pathColor") == 0) {
                strcpy(config->pathColor, value);
            } else if (strcmp(key, "hostnameColor") == 0) {
                strcpy(config->hostnameColor, value);
            }
        }
    }

    fclose(file);
    return 1;
}

