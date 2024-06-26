#include "log/logger.h"

#include <stdarg.h>
#include <stdio.h>

/*
    This function is mainly used by macro but not users directly. TBD
 */
int WarmLoggerMain(struct WarmRuntimeConfig *config, enum WarmLogLevel level, char *fomart, ...)
{
    va_list VA_;
    va_start(VA_, fomart);
    vprintf(fomart, VA_);
    va_end(VA_);

    return 0;
}

/*
    They are all TBD.
 */
int WarmMeltdownedUniverse(struct WarmRuntimeConfig *config, struct WarmMeltdownDumpData *dump_data)
{
    return 0;
}
