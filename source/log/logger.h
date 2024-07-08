#ifndef WARM_LOG_LOGGER_H_
#define WARM_LOG_LOGGER_H_

#include <stdarg.h>

#include "runtime.h"

enum WarmLogLevel {
    kWarmLogLevel_General,
    kWarmLogLevel_Warning,
    kWarmLogLevel_UserWarning,
};

int WarmLoggerMain(struct WarmRuntime *config, const enum WarmLogLevel level, const char *module_tag,
                   const char *format, ...);
int WarmthMeltdownUniverse(struct WarmRuntime *config, const char *format, ...); // "meltdown" is more interesting

// here is the final macro definition
#define WarmLog_General(runtime_config, module_tag, format, ...)                                                       \
    WarmLoggerMain(runtime_config, kWarmLogLevel_General, module_tag, format, ##__VA_ARGS__)
#define WarmLog_Warning(runtime_config, module_tag, format, ...)                                                       \
    WarmLoggerMain(runtime_config, kWarmLogLevel_Warning, module_tag, format, ##__VA_ARGS__)
#define WarmLog_UserWarning(runtime_config, module_tag, format, ...)                                                   \
    WarmLoggerMain(runtime_config, kWarmLogLevel_UserWarning, module_tag, format, ##__VA_ARGS__)

#endif
