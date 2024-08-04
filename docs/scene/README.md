# 场景

由于可能有边框的存在，不要在场景最后

```c
werase(win);
wrefresh(win);
```

这些应该交由管理场景的函数处理

## 场景合集

所有场景的头文件都已被 `scene/scene_collection.h` 引用，其他翻译单元只需要引用它就好了
