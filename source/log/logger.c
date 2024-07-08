#include "log/logger.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <execinfo.h>
#include <ncurses.h>

char *LevelToString_(const enum WarmLogLevel level)
{
    switch (level) {
    case kWarmLogLevel_General:
        return "Info";
        break;
    case kWarmLogLevel_Warning:
        return "Warning";
        break;
    case kWarmLogLevel_UserWarning:
        return "UserWarning";
        break;
    }

    // default return
    return "Unknow";
}

/*
    This function is mainly used by macro but not users directly. TBD
 */
int WarmLoggerMain(struct WarmRuntime *runtime, const enum WarmLogLevel level, const char *module_tag,
                   const char *format, ...)
{
    time_t now_time;
    time(&now_time);
    struct tm *tm = localtime(&now_time);
    va_list va;

    fprintf(runtime->log_handle, "[%d.%d.%d-%d:%d:%d] ", tm->tm_year + 1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min,
            tm->tm_sec);
    fprintf(runtime->log_handle, "[%s] ", LevelToString_(level));
    fprintf(runtime->log_handle, "[%s]: ", module_tag);
    va_start(va, format);
    vfprintf(runtime->log_handle, format, va);
    va_end(va);

    fflush(runtime->log_handle);
    return 0;
}

/*
    In addition to fprintf(), it can dump stack backtrace info.
 */
int WarmthMeltdownUniverse(struct WarmRuntime *runtime, const char *format, ...)
{
    time_t now_time;
    time(&now_time);
    va_list va;

    // get backtrack info
    void *stack_pointers[32];
    char **stack_strings;
    int stack_size = backtrace(stack_pointers, 32);
    stack_strings = backtrace_symbols(stack_pointers, stack_size);

    // tag
    fprintf(runtime->log_handle, "[%ld] [!!! Universe Meltdown !!!]\n", now_time);
    // main prompt string
    va_start(va, format);
    vfprintf(runtime->log_handle, format, va);
    va_end(va);
    // backtrack info
    fprintf(runtime->log_handle, "=== Obtained %d stack frames ===\n", stack_size);
    for (int i = 0; i < stack_size; i++) {
        fprintf(runtime->log_handle, "%s\n", stack_strings[i]);
    }
    fflush(runtime->log_handle);

    // free up
    EngineRuntimeUnload(runtime, 1);

    return 0;
}
