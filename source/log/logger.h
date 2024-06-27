#ifndef WARM_LOG_LOGGER_H_
#define WARM_LOG_LOGGER_H_

#include <stdarg.h>

#include "engine/engine_config.h"

enum WarmLogLevel {
    kWarmLogLevel_General,
    kWarmLogLevel_Warning,
    kWarmLogLevel_UserWarning,
    kWarmLogLevel_CoreMeltdown, // "meltdown" is more interesting
};

// TODO
struct WarmMeltdownDumpData {
    char *message;
};

int WarmLoggerMain(struct WarmRuntimeConfig *config, enum WarmLogLevel level, char *module_tag, char *format, ...);
int WarmthMeltdownUniverse(struct WarmRuntimeConfig *config, struct WarmMeltdownDumpData *dump_data);

// here is the final macro definition
#define WarmLog_General(runtime_config, module_tag, format, ...) WarmLoggerMain(runtime_config, kWarmLogLevel_General, module_tag, format, ##__VA_ARGS__)
#define WarmLog_Warning(runtime_config, module_tag, format, ...) WarmLoggerMain(runtime_config, kWarmLogLevel_Warning, module_tag, format, ##__VA_ARGS__)
#define WarmLog_UserWarning(runtime_config, module_tag, format, ...) WarmLoggerMain(runtime_config, kWarmLogLevel_UserWarning, module_tag, format, ##__VA_ARGS__)

#endif
