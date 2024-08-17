# WarmaShark Text-based Game.TUI

或者 `WarmaShark-Roulette`？

一个关于沃玛的小鲨鱼的游戏，的二创！\
关于源项目的信息都在这里: [docs/original_project.md](docs/original_project.md)

项目已经基本接近开发完毕，至少对我个人来说写的还行，风格也还算统一。\
同时，这也是我写的第一个代码量超过1000行的东西

这次将原项目翻新成了用 ncurses 实现的占用整个终端的程序，也实现了选择和还算易于使用的对话系统。\
我的目标从一开始就是为了认识 C 语言，所以其实并不是太关心剧情，几乎所有的内容都是从原项目里抄来的。但依旧希望有人能喜欢这些东西吧

程序使用 C 语言实现，一方面是在表达我对 Python 的敌对情绪，另一方面也是因为我要继续深入的理解 C 语言的设计内核。\
在这个项目之前我做了 [SourLemonJuice/i18nglish.c](https://github.com/SourLemonJuice/i18nglish.c) 这是一个简短的命令行搞笑软件，我也因为它学到了些与C语言相关的外围部件。\
与它不同的是，这次的程序更偏向于 C 语言的流程设计风格，怎样让结构体和函数发挥出不同于面向对象的光芒，是这次开发中乃至今后我要一直思考的问题

软件的下载在 Release 里，或者也可以看看最新的 GitHub Action(CI) 工件

目前主要的支持系统是 Linux，至于 Windows 构建相关的事情写在这里：[#Sorry for Windows version](#sorry-for-windows-version)\
关于构建系统的更多信息写在 [#Build system](#build-system) 章节。\
都去用 WSL 吧！！！（发疯）（难受）（这也不是什么好玩的游戏，无所谓了...）（这点事情真的很浪费心情的，我受不了了... 抱歉）（Microsoft Windows 与终端八字不合...）\
唉，人是要开始学新东西才会有长进的吧。等等未来的我回来修吧（苦笑）

嘛，下次开始这样的项目会是在什么时候呢。\
希望你我都能找到适合自己的未来

对了对了，如果对代码有些兴趣的话可以去看看 [#Documentations/文档](#documentations文档) 章节，和注释一起食用效果更加。\
毕竟是不是直接以程序功能为目标来写的，这些具体说明算是相当多了，还能反映出一部分我的心路历程（真的能吗？）

## Documentations/文档

Some documents here: [docs/](docs/)\
（所有文档都是中文写的哦）

## Preview/预览

写在另一个文件里 [docs/preview.md](docs/preview.md)

## Build system

### Build flags

The variable `build_type` of make can set some build macro and compiler's flags

- `...=debug` is default one, no optimization and have some debug flags
- `...=CI` use for GitHub Action.
- `...=<Anything>`, yes, just anything, not a keyword, it means Release mode

### Build for Linux

Install some package like:

- clang
- make
- git
- ncurses-devel

Goto `source/` folder and run `make` or specify the target name: run `make warmaShark`.\
The executable file will be named `warmaShark`

There has another target named `warmaShark-Linux-Static`, it will generate a static executable.\
The premise is that if you have a `.a` file(Archive file) of ncursesw(file path: /usr/lib/libncursesw.a), for example... Archlinux package don't have it(unhappy)

My test OS is Archlinux(main) and Ubuntu(verification, GitHub CI)

### Sorry for Windows version

I know the Windows version is essential for this game. Because most fans of Warma only use Windows, or seriously say no any normal one uses Linux daily.\
But I don't know much about Mingw64 or other ways to build it for Windows

You see, I've already tried this, the target `warmaShark-Windows.exe` of `make` and workflow `build_windows.yml` is for that.\
But this didn't work...

So, should I fix it?\
I don't think so, I spent a lot of time on this project, it's for learning C language but not fighting with Windows

Anyway, it will be a large Todo item, but not now... Sorry

Windows should be the second main support platform. From now on

### Build for Windows

Note: It's a **Unstable** target

In Archlinux, install the `mingw-w64-gcc`(package) `mingw-w64-ncurses`(AUR).\
Then just run `make warmaShark-Windows.exe`, I hope...

The problem is MinGW looked like don't allow me to set this: `setlocale(LC_ALL, ".UTF-8");`, but it works in MSVC compiler.\
`".65001"` and `SetConsoleOutputCP(65001);` function are also won't fix the garbled

## Known issues

- Chinese characters may be garbled due to the ncurses/ncursesw dynamic link issue. It is just in some platforms like Ubuntu.
- Garbled also happens in the Windows version.

## Todo

- Recreate windows with the correct size, when resizing the terminal.
- The full system uses `char` now, maybe we can change it to `wchat_t`?

## License

If those code can help you, I will also be happy

The main framework(repo://): Apache License Version 2.0(LICENSE.txt)\
Copyright 2024 酸柠檬猹/SourLemonJuice

Some dialogue scene idea(repo://source/scene/shark_roulette.*): 木兰宽松许可证，第2版(license/MulanPSL2.txt)\
<https://gitee.com/mr-scorpion/shark_roulette>

Full licensing information in [LICENSE.txt](LICENSE.txt), [NOTICE.txt](NOTICE.txt)
