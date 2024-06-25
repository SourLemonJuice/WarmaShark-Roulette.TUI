#include "develop_terminal.h"

struct dialogue_event dialogue1[] = {
    {.text = "Hello"},
    {.text = "This is a Develop Terminal or just a dialogue tree for text output test."},
    {.text = "The protagonist of this program(or videogame), it's a shark. But live in another universe."},
    {.text = "Maybe his name is littleShark, sounds weird? But it is."},
    {.text = "Here is the last line(string pointer), be careful of this pointer index..."},
};

int sceneInit(struct scene_runtime *runtime)
{
    runtime->dialogue1_size = sizeof(dialogue1) / sizeof(struct dialogue_event);
    return 0;
}

char *getCurrentEventText(int index)
{
    return dialogue1[index].text;
}
