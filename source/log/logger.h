#ifndef WARM_LOG_LOGGER_H_
#define WARM_LOG_LOGGER_H_

#include "engine/engine_config.h"

enum WarmLogLevel {
    kWarmLogLevel_General,
    kWarmLogLevel_Warning,
    kWarmLogLevel_Error,
    kWarmLogLevel_CoreMeltdown, // "meltdown" is more interesting
};

struct WarmMeltdownDumpData {
};

// TODO
int WarmLoggerMain(struct WarmRuntimeConfig *config, enum WarmLogLevel level, char *fomart, ...);
int WarmMeltdownedUniverse(struct WarmRuntimeConfig *config, struct WarmMeltdownDumpData *dump_data);

#endif
