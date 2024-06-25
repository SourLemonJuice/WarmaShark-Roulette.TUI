struct dialogue_event
{
    char *text;
};

struct scene_runtime
{
    int dialogue1_size;
};

int sceneInit(struct scene_runtime *runtime);
char *getCurrentEventText(int index);
