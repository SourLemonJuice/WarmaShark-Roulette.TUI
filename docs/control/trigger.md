# 控件/触发器

用于简化场景中由用户触发的内容的组件，目前和以后可能都只有键盘输入。

## 键盘检查/KeyboardCheck

执行器的配置是一个链表，它由多个 `struct WarmTriggerKeyboardCheckEvent` 组成。\
每个结构体代表了一个事件，一个事件可以由多个按键触发，这些按键被作为 Array 配置在结构体的 `.keys` 变量中（当然也要写清 array 里的对象个数）

事件标识由结构体中的 `.index` 定义，一套配置中不能存在有着同样索引的事件（会直接抛出错误）

至于优先级... 谁先加进去谁的优先级就越高，但没事为什么要弄会冲突的按键？

检查器的原型是以前在开发终端里放着的这个：

```c
/*
    Result:
        0: continue
        1: ERROR
 */
static int GetKeyToContinue_(struct WarmRuntime *runtime, WINDOW *win)
{
    int input;
    while (true) {
        input = wgetch(win);
        if (input == ' ' or input == '\n') {
            return 0;
        } else if (input == 'q') {
            EngineRuntimeExit(runtime, 0);
        }
    }

    return 1;
}
```

更多详情都在函数的注释里
