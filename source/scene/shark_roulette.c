#include "scene/shark_roulette.h"

#include <iso646.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>

#include "control/dialogue2.h"
#include "control/selector.h"
#include "control/trigger.h"
#include "log/logger.h"
#include "runtime.h"

// static functions
static int ChapterIntroduction_(struct WarmRuntime *runtime, WINDOW *win);
static int ChapterShootingFromPlayer_(struct WarmRuntime *runtime, WINDOW *win);
static int ChapterShootingFromShark_(struct WarmRuntime *runtime, WINDOW *win);

static const char module_tag[] = "Scene.Shark-Roulette";

static struct DialogueDescription dialogue = {
    .position_y = 0,
    .position_x = 0,
    .interval_delay = 16,
};

enum PlayerTurn_ {
    kTurnPlayer_,
    kTurnShark_,
};

static struct SceneCache_ {
    int win_y;
    int win_x;
    struct WarmTriggerKeyboardEvent *key_event;
    enum PlayerTurn_ turn;
    int live_ammunition;
    int current_cycle;
} cache;

int SceneStart_SharkRoulette(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "Entered the scene");

    Dialogue2ResetPrintTextEvent(&dialogue);

    getmaxyx(win, cache.win_y, cache.win_x);
    WarmLog_GeneralLn(runtime, module_tag, "scene's window y: %d, x: %d", cache.win_y, cache.win_x);

    struct WarmTriggerKeyboardEvent *key_event;
    key_event = TriggerKeyboardCheckEventInit(runtime, 0, (int[]){' ', '\n'}, 2, NULL, NULL);
    cache.key_event = key_event;

    // init finished

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = "所以，你想跳过介绍吗？";
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    struct WarmSelectorActionEvent skip_introduction_select[] = {
        {.position_y = cache.win_y * 0.2,
         .position_x = cache.win_x * 0.1,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "不跳过"},
        {.position_y = cache.win_y * 0.2,
         .position_x = cache.win_x * 0.3,
         .attribute = A_NORMAL,
         .attribute_highlight = A_STANDOUT,
         .string = "跳过"},
    };
    int skip_introduction = DialogueSelector(runtime, win, skip_introduction_select, 2);

    DialogueWindowReset(runtime, win, &dialogue);
    if (skip_introduction == 0) {
        ChapterIntroduction_(runtime, win);
    }

    cache.live_ammunition = rand() % 6;
    cache.turn = kTurnPlayer_;
    WarmLog_GeneralLn(runtime, module_tag, "live ammunition is in: %d(start from 0)", cache.live_ammunition);
    for (cache.current_cycle = 0; cache.current_cycle < 6; cache.current_cycle++) {
        if (cache.turn == kTurnPlayer_) {
            if (ChapterShootingFromPlayer_(runtime, win) != 0) {
                break;
            }
        } else if (cache.turn == kTurnShark_) {
            if (ChapterShootingFromShark_(runtime, win) != 0) {
                break;
            }
        }
    }

    dialogue.text = "> 都是些有趣的生物呐（歪头笑） <";
    DialoguePrintCenter(runtime, win, &dialogue, cache.key_event);

    return 0;
}

static int ChapterIntroduction_(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "enter the chapter: Introduction");

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = "你好啊，";
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeWindowReset;
    dialogue.text = CrossPlatformGetUserName();
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "抱歉，刚才发生了一些小插曲";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "总之... 你好！";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "在我的记忆中，我们已经见了${见面次数}次了";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "这个作者怎么这样？居然用中文命名变量，好恶心哦~";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "而且就这么堂而皇之的打在了输出函数里，因为正式版没有出所以就这么敷衍观众吗？";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "无论发生了什么，我们现在都有一个公平的对决机会";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "这里有一张桌子";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = "桌上有一把很";
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = " ~酷~ ";
    dialogue.attribute = COLOR_PAIR(kColorDangerRed) | A_BOLD;
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeWindowReset;
    dialogue.text = "的左轮手枪，可以容纳六发子弹的弹仓，然而只有一个位置会被填充子弹";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = "我来简单的介绍一下规则吧:\n";
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    getyx(win, dialogue.position_y, dialogue.position_x);
    dialogue.position_x += 4;

    dialogue.text = "第一回合由你来选择，你可以对我开枪，也可以对自己开枪";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "当你对自己开枪，可以额外的获得一个行动回合";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "当然，你可以对着自己开满6枪，虽然这样一定会输掉的";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeWindowReset;
    dialogue.text = "你也可以对着我开枪，但是由于我的伸展角度有限，在下一回合只会向你开枪";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "别紧张啦~这不是一个可怕的游戏";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "枪里有一颗子弹，冲我开一枪试试？";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "（你尝试将枪瞄准小鲨鱼，但是扳机被锁死了）";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "想了想，算了，这个悬念留到游戏结束再揭晓吧";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.text = "> 所以... 游戏要开始咯";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    return 0;
}

static int ChapterShootingFromPlayer_(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "enter the chapter: Shooting from player");

    struct WarmSelectorActionEvent shooting_targets[] = {
        {
            .position_y = cache.win_y * 0.2,
            .position_x = cache.win_x * 0.1,
            .attribute = A_NORMAL,
            .attribute_highlight = A_STANDOUT,
            .string = "自己",
        },
        {
            .position_y = cache.win_y * 0.2,
            .position_x = cache.win_x * 0.3,
            .attribute = COLOR_PAIR(kColorDangerRed),
            .attribute_highlight = A_STANDOUT,
            .string = "亦或是小鲨鱼",
        },
    };

    switch (rand() % 5) {
    case 0:
        dialogue.text = "> 你会射向谁呢：";
        break;
    case 1:
        dialogue.text = "> 要继续下去总是要经历选择的嘛，抱歉：";
        break;
    case 2:
        dialogue.text = "> 你的目标是？";
        break;
    case 3:
        dialogue.text = "> ${管理员.对话.文本}...";
        break;
    case 4:
        dialogue.text = "> 作为一个从各个方面都绝对的第三者和创造者... 这样是不是有点太无情了呢";
        break;
    default:
        dialogue.text = "[Game: rand() Error]";
        break;
    }
    dialogue.type = kDialogueTypeStatic;
    dialogue.wait_key = false;
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    int shooting_to = DialogueSelector(runtime, win, shooting_targets, 2);

    DialogueWindowReset(runtime, win, &dialogue);

    switch (shooting_to) {
    case 0:
        dialogue.type = kDialogueTypeStatic;
        dialogue.text = "你对着自己扣动了扳机";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.type = kDialogueTypeWindowReset;
        dialogue.text = "，时间在这一刻仿佛静止了";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        if (cache.current_cycle == cache.live_ammunition) {
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

            dialogue.text = "结局-1：暴虐欢愉的收场";
            dialogue.attribute = COLOR_PAIR(kColorDangerRed);
            DialoguePrintCenter(runtime, win, &dialogue, cache.key_event);

            return 1;
        } else {
            dialogue.text = "你很幸运，此时枪里并没有子弹，而你也因此获得了额外的回合";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            cache.turn = kTurnPlayer_;
            return 0;
        }
        break;
    case 1:
        dialogue.type = kDialogueTypeStatic;
        dialogue.text = "你对着小鲨鱼扣动了扳机";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.type = kDialogueTypeStatic;
        dialogue.text = "，这一行为甚至没有让你产生任何负罪感";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.type = kDialogueTypeWindowReset;
        dialogue.text = "。好吧，我猜的";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        if (cache.current_cycle == cache.live_ammunition) {
            dialogue.text = "噗";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "枪口伸出了一朵小黄花，花芯是须状的，这并不是你在外面发现的那朵花";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "小鲨鱼看着这朵花愣了愣神，随后开口道";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "啊！我知道这是什么花了";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "这是弟切草";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "你知道弟切草的花语吗？";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            dialogue.text = "结局-2：弟切草";
            dialogue.attribute = COLOR_PAIR(kColorDangerRed);
            DialoguePrintCenter(runtime, win, &dialogue, cache.key_event);

            return 1;
        } else {
            dialogue.text = "没有预想中的枪声，显然，这一枪没有击发那颗子弹，而下一回合，就轮到小鲨鱼了";
            Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

            cache.turn = kTurnShark_;
            return 0;
        }
        break;
    }

    return -1;
}

static int ChapterShootingFromShark_(struct WarmRuntime *runtime, WINDOW *win)
{
    WarmLog_GeneralLn(runtime, module_tag, "enter the chapter: Shooting from player");

    dialogue.type = kDialogueTypeStatic;
    dialogue.text = "小鲨鱼努力的拿起枪，笨拙的做出了一个扣动扳机的动作";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    dialogue.type = kDialogueTypeWindowReset;
    dialogue.text = "，你的心跳近乎停止了";
    Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

    if (cache.current_cycle == cache.live_ammunition) {
        dialogue.text = "俯下头看了看自己的胸口，胸部的衣服被染成了暗红色";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "也许是右心房，或者右心室（笑）";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "可怜的小鲨鱼，由于高度原因，连给你一个干脆利落的结局都做不到";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "此时，你闻到了一股诡异的香甜，从小鲨鱼洞穿你身体的位置...";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "你以手指与指甲作为工具，从你的身体里探索那股香甜气味的来源";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "当你气若游丝之时，你找到了这颗气味的来源，用染成鲜红的双手捧起了它";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.type = kDialogueTypeStatic;
        dialogue.text = "结局-3：原罪、诱惑、智慧的化身";
        dialogue.attribute = COLOR_PAIR(kColorDangerRed);
        DialoguePrintCenter(runtime, win, &dialogue, cache.key_event);

        getyx(win, dialogue.position_y, dialogue.position_x);
        dialogue.position_y += 1;

        dialogue.type = kDialogueTypeWindowReset;
        dialogue.text = "> 是的，一颗苹果 <";
        DialoguePrintCenter(runtime, win, &dialogue, cache.key_event);

        return 1;
    } else {
        dialogue.text = "但过了不长时间又开始照常跳动，履行作为器官的职责，让你意识到你还活着";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        dialogue.text = "接下来是你的回合";
        Dialogue2PrintText(runtime, win, &dialogue, cache.key_event);

        cache.turn = kTurnPlayer_;
        return 0;
    }

    return -1;
}
