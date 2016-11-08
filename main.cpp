#include "widget.h"
#include "formain.h"

void *cpu(void *p){
    // fulled struct global
    Arg *arg = (Arg *)p;
    Process process(arg->sharedMem, arg->callList);
//    pthread_mutex_unlock(arg->mutex);
    useconds_t usec = 300;
    while (arg->working){
        process.checkCallList();
        usleep(usec);
    }
    return NULL;
}

void *gui(void *p) {
    Arg *arg = (Arg *)p;
    QApplication a(arg->argc, arg->argv);
    Widget *w = new Widget(NULL, arg);
    w->show();

    a.exec();
    return NULL;
}

int main(int argc, char *argv[])
{
//    pthread_mutex_t mutex;
//    pthread_mutex_init(&mutex, NULL);
//    pthread_mutex_lock(&mutex);

    Arg arg;
    CallList callList;
    callList.doRun = 0;
    callList.doStep = 0;
    callList.doStopReset = 0;
    callList.setBreakPointForAddress = -1;

    SharedMem sharedMem;
    sharedMem.isFull = 0;

    arg.argc = argc;
    arg.argv = argv;
//    arg.mutex = &mutex;
    arg.sharedMem = &sharedMem;
    arg.callList = &callList;
    arg.working = 1;

    pthread_t gui_st, cpu_st;
    errno = 0;
    if (pthread_create(&gui_st, NULL, gui, &arg) > 0) {
        printf("error pthread_create gui\n");
        return errno;
    }
    errno = 0;
    if (pthread_create(&cpu_st, NULL, cpu, &arg) > 0) {
        printf("error pthread_create cpu\n");
        return errno;
    }
    errno = 0;
    if (pthread_join(gui_st, NULL)) {
        printf("error pthread_join gui\n");
        return errno;
    }
    arg.working = 0;
    errno = 0;
    if (pthread_join(cpu_st, NULL)) {
        printf("error pthread_join cpu\n");
        return errno;
    }

//    pthread_mutex_destroy(&mutex);

    return 0;
}
