#include "runtime.h"

#include <locale.h>
#include <stdio.h>

int EngineReloadLocale(const struct WarmRuntimeConfig *config)
{
    setlocale(LC_ALL, config->locale_string);
    return 0;
}

// TODO error detect
int EngineRuntimeInit(struct WarmRuntimeConfig *config)
{
    // set all default config
    config->log_path = "./Engine.log";
    config->log_handle = fopen(config->log_path, "w");
    config->locale_string = "en_US.UTF-8";

    // when everyone all be setted, apply those config
    EngineReloadLocale(config); // setup program locale
    fprintf(config->log_handle, "==== Engine runtime has been inited ====\n");
    fflush(config->log_handle);
    return 0;
}

int EngineRuntimeFreeUp(struct WarmRuntimeConfig *config)
{
    fclose(config->log_handle);
    return 0;
}
