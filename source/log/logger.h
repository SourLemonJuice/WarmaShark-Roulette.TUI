#ifndef WARM_LOG_LOGGER_H_
#define WARM_LOG_LOGGER_H_

#include "engine/engine_config.h"

enum WarmLogLevel {
    kLogLevel_General,
    kLogLevel_Warning,
    kLogLevel_Error,
    kLogLevel_CoreMeltdown, // "meltdown" is more interesting
};

struct WarmMeltdownDumpData {
};

// TODO
int WarmLoggerMain(struct WarmRuntimeConfig *config, char *module_tag, enum WarmLogLevel level, char *format, ...);
int WarmMeltdownedUniverse(struct WarmRuntimeConfig *config, struct WarmMeltdownDumpData *dump_data);

#endif
