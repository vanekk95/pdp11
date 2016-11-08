#include "widget.h"
#include "formain.h"

void *cpu(void *p){
    // fulled struct global
    Arg *arg = (Arg *)p;
    Process process(arg->startMem);
    pthread_mutex_unlock(arg->mutex);
    return p;
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
    char shared_mem_name[] = "my_shared_memory";
    int shared_mem_size = 128*1024;
    int shm;

    if ( (shm = shm_open(shared_mem_name, O_CREAT|O_RDWR, 0777)) == -1 ) {
        perror("shm_open");
        return 1;
    }

    if ( ftruncate(shm, shared_mem_size+1) == -1 ) {
        perror("ftruncate");
        return 1;
    }

    void *addr = mmap(0, shared_mem_size+1, PROT_WRITE|PROT_READ, MAP_SHARED, shm, 0);
    if ( addr == (char*)-1 ) {
        perror("mmap");
        return 1;
    }

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);

    pthread_t gui_st, cpu_st;
    Arg arg;

    arg.argc = argc;
    arg.argv = argv;
    arg.mutex = &mutex;
    arg.startMem = addr;

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
    if (pthread_join(gui_st, NULL)) {
        printf("error pthread_join gui\n");
        return errno;
    }
    if (pthread_join(cpu_st, NULL)) {
        printf("error pthread_join cpu\n");
        return errno;
    }

    pthread_mutex_destroy(&mutex);

    munmap(addr, shared_mem_size);
    close(shm);
    shm_unlink(shared_mem_name);

    return 0;
}
