#ifndef CONFIG_H
#define CONFIG_H

/**
 * ## Config
 *  @brief Base for all why-shell configs
 */
typedef struct {
    // input
    char inputForUser[256];
    // the final input
    char finalInput[256];
    // colors
    char userColor[16];
    char pathColor[16];
    char hostnameColor[16];
} Config;

/**
 * ## loadConfig
 * @brief Load a config from a config file
 * @param filename The config file path
 * @param config The config content
 */
int loadConfig(const char *filename, Config *config);

#endif