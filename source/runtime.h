#ifndef WARM_ENGINE_CONFIG_H_
#define WARM_ENGINE_CONFIG_H_

#include <stdio.h>

struct WarmRuntimeConfig {
    char *log_path;
    FILE *log_handle;
    char *locale_string;
    int terminal_y; // terminal maximum y
    int terminal_x; // terminal maximum x
};

int EngineReloadLocale(const struct WarmRuntimeConfig *config);
int EngineRuntimeInit(struct WarmRuntimeConfig *config);
int EngineRuntimeFreeUp(struct WarmRuntimeConfig *config);

#endif
