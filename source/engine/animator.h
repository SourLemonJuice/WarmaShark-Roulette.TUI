#ifndef WARN_ENGINE_ANIMATOR_H_
#define WARN_ENGINE_ANIMATOR_H_

#include "engine_config.h"

// this is a linked list structure
struct EngineAnimatorEventSet {
    // TODO because we don't have any event now
    struct EngineAnimatorEventSet *next;
};

struct EngineAnimatorEventSet *EngineAnimatorEventSetInit(struct WarmRuntimeConfig *runtime_config);
int EngineAnimatorEventSetAppend(struct WarmRuntimeConfig *runtime_config, struct EngineAnimatorEventSet *event_set);

#endif
