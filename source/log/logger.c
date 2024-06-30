#include "log/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    This function is mainly used by macro but not users directly. TBD
 */
int WarmLoggerMain(const struct WarmRuntimeConfig *config, const enum WarmLogLevel level, const char *module_tag,
                   const char *format, ...)
{
    time_t now_time_;
    time(&now_time_);

    va_list va_;
    va_start(va_, format);
    fprintf(config->log_handle, "- %s", ctime(&now_time_)); // TODO This time format is so bad
    fprintf(config->log_handle, "[%s]: ", module_tag);
    vfprintf(config->log_handle, format, va_);
    fflush(config->log_handle);
    va_end(va_);

    return 0;
}

/*
    TODO They are all TBD.
 */
int WarmthMeltdownUniverse(const struct WarmRuntimeConfig *config, const struct WarmMeltdownDumpData *dump_data)
{
    fprintf(config->log_handle, "[Universe Meltdown]: ");
    fprintf(config->log_handle, "%s\n", dump_data->message);
    fflush(config->log_handle);
    exit(1);
    return 0;
}
