# dialogue.c

译为`对话`，它也确实是负责处理对话控件的。

这是一个旧的实现，现在也被完全删掉了

## 实践

~~开发终端中有相对完整的使用测试。~~\
[scene/develop_terminal.c](../source/scene/develop_terminal.c)

已经没有地方留着啦，去看看新的 [control/dialogue2.c](../source/control/dialogue2.c) 吧

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

已被转移到了单独的翻译单元中 [control/selector.c](../source/control/selector.c)\
提交哈希 6936aeb1ef23bbfce2e38c224779b1950217e6b3

这也是这个单元的最后一次有大变动的提交了

## 碎碎念

我是在给一个 .c 送终吗，赶快删掉啦
