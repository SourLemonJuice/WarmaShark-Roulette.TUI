# 代码风格

```c
#include <Linux>
#include <GoogleStyle/c++>
#include ".clang-format"
```

其余部分是这些前置条件的附加

## 标识符的命名

Google C++ 中所说成员变量用 `_` 结尾(class_var_)，C 没有类，但每个翻译单元(.c)的私有变量，也就是没有被放进头文件(.h)里的标识符都需要按照此规则命名

## 简写与缩写

- WARM/warm
  - 全称: warm
  - 意义: 表示这是有关于 Warma 的游戏
  - 用于: 作为整个程序的命名空间使用
  - 例子: define WARM_LOG_LEVEL
