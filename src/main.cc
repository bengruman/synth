#include "synth.h"

class Voice
{
public:
    Voice(Context * context, ALfloat frequency)
        :source(new Source(context))
        ,buffer(new Buffer(context))
    {
        ALshort * signal            = new ALshort[MAX_BUFFER_SIZE];
        ALfloat samples_per_period  = SAMPLE_RATE / frequency;
        ALsizei buffer_size         = ((int)samples_per_period % 2) ? samples_per_period + 1 : samples_per_period;
        ALfloat omega               = 2.f * M_PI / samples_per_period;

        for(int i = 0; i < buffer_size; i++)
        {
            signal[i] = INT16_MAX * sinf(omega * i);
        }

        alGetError();

        if(buffer->set(signal, buffer_size) != AL_NO_ERROR)
        {
            delete signal;
            return;
        }

        delete signal;

        if(source->attach(buffer) != AL_NO_ERROR) return;
        if(source->play(AL_TRUE) != AL_NO_ERROR) return;
    }
    ~Voice()
    {
        source->stop();
        delete source;
        delete buffer;
    }
private:
    Buffer * buffer;
    Source * source;
};

int main()
{
    Context * context;
    Voice ** voices = new Voice*[KEY_CNT];
    int keyboard_fd;
    struct input_event ev;

    context = new Context();

    keyboard_fd = open(KEYBOARD, O_RDONLY);
    if(keyboard_fd < 0)
    {
        std::cout << KEYBOARD_ACCESS_FAILURE_MSG << ": " << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    while(1)
    {
        if(read(keyboard_fd, &ev, sizeof(ev)) > 0 && ev.type == EV_KEY)
        {
            if(ev.code == KEY_ESC)
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
            else
            {
                if((ev.value == 1) && (voices[ev.code] == NULL))
                {
                    voices[ev.code] = new Voice(context, KEY2FREQ(ev.code));
                }
                else if((ev.value == 0) && (voices[ev.code] != NULL))
                {
                    delete voices[ev.code];
                    // memset(voices[ev.code], 0, sizeof(Voice));
                    voices[ev.code] = NULL;
                }
            }
        }
    }

    close(keyboard_fd);
    delete voices;
    delete context;
    return EXIT_SUCCESS;
}