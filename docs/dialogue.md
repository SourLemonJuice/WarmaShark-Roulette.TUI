# dialogue.c

译为`对话`，它也确实是负责处理对话控件的。

## 实践

开发终端中有相对完整的使用测试。\
[develop_terminal](../source/scene/develop_terminal.c)

## DialogueEvent

```c
struct WarmDialogueEvent;
int DialogueExecuteEvent(...);
```

`对话事件`被用来抽象对话这一功能，调用者可以通过 `struct WarmDialogueEvent` 组成的 Array 定义一系列对话。\
这些事件并非由**句子**分割，而是字符串的**属性**，比如 xxxyyy 中 xxx 为蓝色，而 yyy 为绿色，那虽然他们处于同一句话中但仍然是两个事件。\
此处的属性并非仅仅可以是颜色，确切的说实现中使用的就是 ncurses 的 属性/Attributes，颜色只是一个例子。

`DialogueExecuteEvent()` 函数用于执行事件。调用者需要自己实现循环来将一个又一个的 Event 结构喂给它。\
这么做的目的之一就是考虑到了 `getch()` 这类函数的兼容性，作为一个通用的库 `dialogue.c` 不知道场景需要什么按键用来继续下一个句子，与其说想办法为其构建一个统一的模型不如直接将其交给调用者处理。\
不要为调用者考虑太多，写好文档并保持接口稳定性就好。

其实接下来的问题会是，怎样处理完整的对话树。又要用什么方式储存它们，这些在现在仍然是个不大不小的问题呢，毕竟可以让场景自己硬搓一个出来嘛。

## Selector

```c
struct WarmSelectorActionEvent;
int DialogueSelector(...);
```

`选择器`被用来实现一些通用的选项操作，比如文字小说中经典的控制对话树的 **我** 的回答... 嗯... 或者之类的东西。

由于需要配置数量不定的按键对象，所以选择器 `int DialogueSelector()` 被定性要求输入一个由 `WarmSelectorActionEvent` 组成的 Array，相比于用更多的处理函数，这其实也利好配置时的代码可读性（虽说代码风格差也很难看）

目前用户可以用 `]` 选择下一个选项，`[` 选择上一个选项，这在未来可能会被改为可配置的。

该函数会在选择结束后清除屏幕上选项们的字符串，并返回用户所选对象的 index。
