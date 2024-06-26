#include "log/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/*
    This function is mainly used by macro but not users directly. TBD
 */
int WarmLoggerMain(struct WarmRuntimeConfig *config, char *module_tag, enum WarmLogLevel level, char *format, ...)
{
    time_t now_time;
    time(&now_time);

    va_list VA_;
    va_start(VA_, format);
    fprintf(config->log_handle, "- %s", ctime(&now_time));
    fprintf(config->log_handle, "[%s]: ", module_tag);
    vfprintf(config->log_handle, format, VA_);
    fflush(config->log_handle);
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
