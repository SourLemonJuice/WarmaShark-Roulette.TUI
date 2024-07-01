#ifndef WARM_ENGINE_CONFIG_H_
#define WARM_ENGINE_CONFIG_H_

#include <stdio.h>

struct WarmRuntimeConfig {
    char *log_path;
    FILE *log_handle;
    char *locale_string;
};

int EngineRuntimeInit(struct WarmRuntimeConfig *config);
int EngineRuntimeFreeUp(struct WarmRuntimeConfig *config);

#endif
