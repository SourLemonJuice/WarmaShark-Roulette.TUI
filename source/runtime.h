#ifndef WARM_ENGINE_CONFIG_H_
#define WARM_ENGINE_CONFIG_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct WarmRuntime {
    char *log_path;
    FILE *log_handle;
    bool logging;
    char *locale_string;
    // TODO useless
    int terminal_y; // terminal maximum y
    int terminal_x; // terminal maximum x
};

enum WarmProgramExitErrorCode {
    kWarmErrorNormal = EXIT_FAILURE,
    kWarmErrorFlagProcess,
    kWarmErrorStreamOperation,
};

enum WarmNcursesColorId {
    kColorTest = 1,
    kColorDangerRed,
};

int EngineRuntimeInit(struct WarmRuntime *runtime);
void EngineSetLocale(struct WarmRuntime *runtime);
int EngineLogSystemInit(struct WarmRuntime *runtime);
int EngineNcursesInit(struct WarmRuntime *runtime);
void EngineLogSystemUnload(struct WarmRuntime *runtime);
void EngineFullExit(struct WarmRuntime *runtime, int return_code);

#endif
