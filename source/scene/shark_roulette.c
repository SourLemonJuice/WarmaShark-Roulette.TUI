#include "scene/shark_roulette.h"

#include <iso646.h>
#include <stdlib.h>

#include <ncurses.h>

#include "control/dialogue2.h"
#include "control/selector.h"
#include "control/trigger.h"
#include "log/logger.h"
#include "runtime.h"

// static functions
static void ChapterIntroduction_(struct WarmRuntime *runtime, WINDOW *win);
static void ChapterShooting_(struct WarmRuntime *runtime, WINDOW *win);

static const char module_tag[] = "Scene.Shark-Roulette";

static struct SceneCache_ {
    int win_y;
    int win_x;
    struct WarmTriggerKeyboardCheckEvent *key_event;
} cache;

int StartScene_SharkRoulette(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "Entered the scene");

    getmaxyx(win, cache.win_y, cache.win_x);
    WarmLog_GeneralLn(runtime, module_tag, "scene's window y: %d, x: %d", cache.win_y, cache.win_x);

    struct WarmTriggerKeyboardCheckEvent key_event;
    TriggerKeyboardCheckEventInit(runtime, &key_event, (int[]){' ', '\n'}, 2, 0);
    cache.key_event = &key_event;

    ChapterIntroduction_(runtime, win);

    return 0;
}

void ChapterIntroduction_(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "enter the chapter: Introduction");

    struct WarmDialogue2Description dialogue = {
        .position_y = 0,
        .position_x = 0,
    };
    Dialogue2EventSetDefaultPrintText(&dialogue);

    dialogue.text = "你好啊，Administrator";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "怎么又是Administrator？你们不能改一下用户名称吗？";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "咳咳，抱歉，刚才发生了一些小插曲";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "你好";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "在我的记忆中，我们已经见了${见面次数}次了";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "这个作者怎么这样？居然用中文命名变量，好恶心哦~";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "而且就这么堂而皇之的打在了输出函数里，因为正式版没有出所以就这么敷衍观众吗？";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "总之——我们有了一个公平对决的机会";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "我们的面前有一张桌子";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "桌子上有一把很~酷~的左轮手枪，可以容纳六发子弹的弹仓，然而只有一个位置会被填充子弹";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "我来简单的介绍一下规则:\n";
    dialogue.clear = false;
    dialogue.reset_position = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    getyx(win, dialogue.position_y, dialogue.position_x);
    dialogue.position_x += 4;
    Dialogue2UpdatePosition(runtime, win, &dialogue);

    dialogue.text = "第一回合由你来选择，你可以对我开枪，也可以对自己开枪";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "当你对自己开枪，可以额外的获得一个行动回合";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "当然，你可以对着自己开满6枪，这样一定会输掉的";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "你也可以对着我开枪，但是由于我的伸展角度有限，在下一回合只会向你开枪";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.position_y = 0;
    dialogue.position_x = 0;
    werase(win);
    Dialogue2UpdatePosition(runtime, win, &dialogue);

    dialogue.text = "别紧张啦~这不是一个可怕的游戏";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "枪里有一颗子弹，冲我开一枪试试？";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "（你尝试将枪瞄准小鲨鱼，但是扳机被锁死了）";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "想了想，算了，这个悬念留到游戏结束再揭晓吧";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    ChapterShooting_(runtime, win);

    werase(win);
    dialogue.text = "> 有趣的生物们呐";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);
}

static void ChapterShooting_(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "enter the chapter: Shooting");

    struct WarmSelectorActionEvent shooting_targets[] = {
        {.position_y = cache.win_y * 0.2,
         .position_x = cache.win_x * 0.1,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "自己"},
        {.position_y = cache.win_y * 0.2,
         .position_x = cache.win_x * 0.3,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "亦或是小鲨鱼"},
    };

    struct WarmDialogue2Description dialogue = {
        .position_y = 0,
        .position_x = 0,
    };
    Dialogue2EventSetDefaultPrintText(&dialogue);

    dialogue.text = "> 所以... 游戏要开始咯";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    int live_ammunition = rand() % 6;
    for (int i = 0; i < 6; i++) {
        dialogue.text = "> 你会选谁呢:";
        dialogue.clear = false;
        Dialogue2PrintText(runtime, win, &dialogue, NULL);

        switch (DialogueSelector(runtime, win, shooting_targets, 2)) {
        case 0:
            werase(win);

            dialogue.text = "你对着自己扣动了扳机";
            dialogue.clear = false;
            dialogue.reset_position = false;
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "，时间在这一刻仿佛静止了";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            if (i == live_ammunition) {
                dialogue.text = "伴随着一声巨响，仿佛有人给你来了一记下勾拳";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "你倒在地上，一些黏腻的内容物从你头部刚打开的孔洞里流了出来";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "此刻，你的视线变得血红，意识开始逐渐模糊";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "你甚至产生了身后墙上溅出的一部分内容物仍然保有自己意识的错觉";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text =
                    "地上，墙上，还有保留在你身体里的一小部分，正在和这个空间融为一体，都让你清晰的感受到生命的流逝";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "你好！我想吃苹果！";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "这便是你的结局";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                dialogue.text = "结局-1:暴虐欢愉的收场";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

                return;
            } else {
                dialogue.text = "你很幸运，此时枪里并没有子弹，而你因此获得了额外的回合";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);
            }
            break;
        case 1:
                werase(win);

                dialogue.text = "develop";
                Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);
            break;
        }
    }
}
