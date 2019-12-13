#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>

#include "keyboard.h"
#include "synth.h"
#include "synth_err.h"

Keyboard::Keyboard()
    :fd(open(KEYBOARD, O_RDONLY))
    ,context(new Context())
    ,voices(new Voice*[KEY_CNT])
{
    if(fd < 0)
    {
        std::cout << KEYBOARD_ACCESS_FAILURE_MSG << ": " << strerror(errno) << std::endl;
        return;
    }

    pthread_create(&thread, NULL, listen, this);
}

Keyboard::~Keyboard()
{
    pthread_join(thread, NULL);
    delete voices;
    delete context;
    close(fd);
}

void * Keyboard::listen(void * args)
{
    Keyboard * instance = (Keyboard*)args;
    struct input_event ev;
    while(1)
    {
        if(read(instance->fd, &ev, sizeof(ev)) > 0 && ev.type == EV_KEY)
        {
            if(ev.code == KEY_ESC)
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            else
            {
                if((ev.value == 1) && (instance->voices[ev.code] == NULL))
                {
                    instance->voices[ev.code] = new Voice(instance->context, KEY2FREQ(ev.code));
                }
                else if((ev.value == 0) && (instance->voices[ev.code] != NULL))
                {
                    delete instance->voices[ev.code];
                    instance->voices[ev.code] = (Voice*)NULL;
                }
            }
        }
    }
}