#include <AL/al.h>

#include "al_api.h"
#include "synth.h"

Voice::Voice(Context * context, ALfloat frequency)
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


Voice::~Voice()
{
    source->stop();
    delete source;
    delete buffer;
}