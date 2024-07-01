#include <locale.h>
#include <string.h>

#include "unity/src/unity.h"

#include "runtime.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_EngineReloadLocale(void)
{
    struct WarmRuntimeConfig config;
    EngineRuntimeInit(&config);
    config.locale_string = "zh_CN.UTF-8";
    EngineReloadLocale(&config);
    TEST_ASSERT_EQUAL_INT(0, strcmp(setlocale(LC_ALL, NULL), "zh_CN.UTF-8"));
}

void test_EngineRuntimeInit(void)
{
    struct WarmRuntimeConfig config;
    EngineRuntimeInit(&config);
    TEST_ASSERT_NOT_NULL(config.log_handle);
    TEST_ASSERT_EQUAL_INT(0, strcmp(config.locale_string, "en_US.UTF-8"));
}

void test_EngineRuntimeFreeUp(void)
{
    TEST_MESSAGE("This test unit doesn't have any actual code.");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_EngineReloadLocale);
    RUN_TEST(test_EngineRuntimeInit);
    RUN_TEST(test_EngineRuntimeFreeUp);

    return UNITY_END();
}
