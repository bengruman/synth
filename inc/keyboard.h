#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <pthread.h>

#include "al_api.h"
#include "synth.h"

#define KEYBOARD "/dev/input/event4"

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();
private:
    static void * listen(void * args);
    int fd;
    Voice ** voices;
    Context * context;
    pthread_t thread;
};

#endif