#include <AL/al.h>
#include <AL/alc.h>

#include "synth_err.h"

#define FORMAT          AL_FORMAT_MONO16
#define SAMPLE_RATE     44100
#define MAX_BUFFER_SIZE SAMPLE_RATE

class Context
{
public:
    Context(ALCchar * device_name = NULL);
    ~Context();
    ALCenum select();
private:
    ALCdevice   * ald;
    ALCcontext  * alc;
};

class Buffer
{
public:
    Buffer(Context * context);
    ~Buffer();
    ALuint get() {return alb;}
    ALenum set(ALvoid * signal, ALsizei size);
private:
    ALuint  alb;
    Context * c;
};

class Source
{
public:
    Source(Context * context);
    ~Source();
    ALenum play(ALboolean looping = AL_TRUE);
    ALenum stop();
    ALenum attach(Buffer * buffer);
private:
    ALuint  als;
    Context * c;
};
