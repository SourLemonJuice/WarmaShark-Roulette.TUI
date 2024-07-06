#include "scene/shark_roulette.h"

#include <iso646.h>

#include <ncurses.h>

#include "dialogue.h"
#include "log/logger.h"
#include "runtime.h"

static const char module_tag[] = "scene - Shark Roulette";

static struct WarmDialogueEvent dialogue1[] = {
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "你好啊，Administrator"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "怎么又是 Administrator ？你们不能改一下用户名称吗？"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "咳咳，抱歉，刚才发生了一些小插曲"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "你好"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "在我的记忆中，我们已经见了${见面次数}次了"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "这个作者怎么这样？居然用中文命名变量，好恶心哦"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "而且就这么堂而皇之的打在了输出函数里，因为正式版没有出所以就这么敷衍观众吗？"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "总之——我们有了一个公平对决的机会"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "我们的面前有一张桌子"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "桌子上有一把很~酷~的左轮手枪，可以容纳六发子弹的弹仓，然而只有一个位置会被填充子弹"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "我来简单的介绍一下规则："},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "第一回合由你来选择，你可以对我开枪，也可以对自己开枪"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "当你对自己开枪，可以额外的获得一个行动回合"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "当然，你可以对着自己开满6枪，这样一定会输掉的"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "你也可以对着我开枪，但是由于我的伸展角度有限，在下一回合只会向你开枪"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "别紧张啦~这不是一个可怕的游戏"},
    {.type = kWarmDialogueType_SentenceEnd, .attribute = A_NORMAL, .text = "枪里有一颗子弹，冲我开一枪试试？"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "（你尝试将枪瞄准小鲨鱼，但是扳机被锁死了）"},
    {.type = kWarmDialogueType_SentenceEnd,
     .attribute = A_NORMAL,
     .text = "想了想，算了，这个悬念留到游戏结束再揭晓吧"},
};

static const struct WarmDialogueEvent dialogue2[] = {{}};

int StartScene_SharkRoulette(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_General(runtime, module_tag, "Entered the scene\n");

    int d1_index = 0;
    int event_result = 0;

    do {
        event_result = DialogueExecuteEvent(runtime, win, &dialogue1[d1_index]);
        if (event_result < 0) {
            return 1;
        } else if (event_result == 0) {
            wgetch(win);
            werase(win);
            d1_index++;
        } else if (event_result == 1) {
            d1_index++;
        }
    } while (d1_index < (sizeof(dialogue1) / sizeof(struct WarmDialogueEvent)));

    WarmLog_General(runtime, module_tag, "Exit the scene normally\n");
    return 0;
}
