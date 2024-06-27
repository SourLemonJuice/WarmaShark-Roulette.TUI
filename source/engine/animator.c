#include "animator.h"

#include "stdlib.h"

#include "log/logger.h"

struct EngineAnimatorEventSet *EngineAnimatorEventSetInit(struct WarmRuntimeConfig *runtime_config)
{
    struct EngineAnimatorEventSet *result_ = malloc(sizeof(struct EngineAnimatorEventSet));
    if (result_ == NULL) {
        struct WarmMeltdownDumpData meltdown_data_ = {.message = "Con't malloc() in EngineAnimatorEventSetInit()"};
        WarmthMeltdownUniverse(runtime_config, &meltdown_data_);
    }
    result_->next = NULL;
    return result_;
}

int EngineAnimatorEventSetAppend(struct WarmRuntimeConfig *runtime_config, struct EngineAnimatorEventSet *event_set)
{
    event_set->next = malloc(sizeof(struct EngineAnimatorEventSet));
    if (event_set->next == NULL) {
        struct WarmMeltdownDumpData meltdown_data_ = {.message = "Con't malloc() in EngineAnimatorEventSetAppend()"};
        WarmthMeltdownUniverse(runtime_config, &meltdown_data_);
    }
    return 0;
}
