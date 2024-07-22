# 控件/对话组件2

`dialogue` 组件的第二版，有着不同的设计风格，没有完全实现。\
详情可以看看函数的注释什么的

TODO

## 坐标/Position

事件中的 `.position_*` 用于确定当前事件的打印位置。

如果事件类型为 `kDialogueTypeStatic` 那执行器将会自动用当前光标坐标更新它。\
这是为了下一次的打印事件所做的，不然之前的句子就被覆盖掉了嘛

要结束静态元素需要将类型设定为 `kDialogueTypeWindowReset` 或者调用 `DialogueWindowReset()`函数，这将清空 window/窗口 并重设事件结构体中的坐标到原点(0, 0)。\
两个选择里总会有一个方便用的哦

比如如果使用函数就不用写这么大一堆了：

```c
dialogue.type = kDialogueTypeWindowReset;
dialogue.text = NULL;
dialogue.wait_key = false;
Dialogue2PrintText(runtime, win, &dialogue_event, &key_event);
```
