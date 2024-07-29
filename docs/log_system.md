# 日志系统

项目中的日志系统能由什么组成又需要由什么组成呢

## 日志位置

日志位置和 handle 被储存在了程序 runtime 中，并在程序初始化的时候被设定默认值。\
日志的默认位置是 `./Engine.log`

在 `git describe` 的输出为 build-1-15-xxx 以后的版本中日志默认为关闭状态。\
可以使用命令行标志 `--logging` 开启。\
同时也允许使用 `--log-path <path>` 标志来控制日志文件的路径

## 定义方式

日志的标头(`source/log/logger.h`)定义了一个枚举器，其中枚举了日志等级，比如: `kWarmLogLevel_General`\
同时也定义了 `int WarmLoggerMain(...)` 函数，这些组合起来就变成了项目的日志系统。

不过它们不是直接交给其他组件的，标头定义了一系列宏来简化这长的要命的日志等级。这些定义在下文中写到了。

## 输出方式

这些定义与 fprintf() 类似，但唯一的不同是会在每一行的前面加上一个 `module_tag` 作为标识。\
需要被写入文件在 runtime 中定义和初始化

## 按等级分类

- General(宏)
  - 常规日志输出，但不包括想要给用户显示的内容
- Warning(宏)
  - 轻度/中度 程序警告
- UserWarning(宏) - (unstable)
  - 用户交互错误，这一部分可能需要显示在 ncurses 上
- CoreMeltdown(函数)
  - 最严重的错误，程序在逻辑与代码层面均不符合设想。或许它可以被称为转储
  - [已放弃] 需要提交包含更多错误信息的结构体，而非一行 printf() 的参数。\
    虽说在调用 meltdown 时很可能是内存出错，但也不是不行吧，大概吧...

### WarmthMeltdownUniverse()

也就是 Warmth meltdown universe/温暖的融化（这个）宇宙\
从 Warm 这个全局命名空间为基础意外想出来的，挺有趣不是么

- 输入一个 printf 格式的参数作为崩溃简介
- 转储当前的堆栈调用信息

## 最终实现

我也不知道这些宏有多稳定，但现在改起来也不费劲就是了\
注：以头文件中的定义为准

```c
/* macros */
WarmLog_General(&runtime_config, "module_tag", "format %d\n", 128);
WarmLog_Warning(...);
WarmLog_UserWarning(...);
// ...Ln series don't need '\n'
WarmLog_GeneralLn(&runtime, "module_tag", "format %d", 256);
WarmLog_WarningLn(...);

/* functions */
int WarmthMeltdownUniverse(struct WarmRuntimeConfig *config, const char *format, ...);
```
