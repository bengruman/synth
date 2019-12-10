#include "al_api.h"
#define DEBUG std::cout << "DEBUG" << std::endl;

Context::Context(ALCchar * device_name)
{
    ALCenum result;
    ald = alcOpenDevice(device_name);
    if(ald == NULL)
    {
        std::cout << DEVICE_INIT_FAILURE_MSG << std::endl;
        return;
    }

    alcGetError(ald);

    alc = alcCreateContext(ald, NULL);
    if((result = alcGetError(ald)) != ALC_NO_ERROR)
    {
        std::cout << CONTEXT_INIT_FAILURE_MSG << ": " << alcErrStr(result) << std::endl;
        return;
    }
}

Context::~Context()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(alc);
    alcCloseDevice(ald);
}

ALCenum Context::select()
{
    ALCenum result = alcGetError(ald);
    alcMakeContextCurrent(alc);
    if((result = alcGetError(ald)) != ALC_NO_ERROR)
    {
        std::cout << CONTEXT_MAKE_CURRENT_FAILURE_MSG << ": " << alcErrStr(result) << std::endl;
        return result;
    }
    return result;
}

Source::Source(Context * context)
    :c(context)
{
    ALenum result = alGetError();

    if(c->select() != AL_NO_ERROR) return;

    alGenSources(1, &als);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << SOURCE_GEN_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return;
    }
}

Source::~Source()
{
    ALenum result = alGetError();

    if(c->select() != AL_NO_ERROR) return;

    alDeleteSources(1, &als);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << SOURCE_DELETE_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return;
    }
}

ALenum Source::play(ALboolean looping)
{
    ALenum result = alGetError();

    if((result = c->select()) != AL_NO_ERROR) return result;

    alSourcei(als, AL_LOOPING, looping);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << SOURCE_SET_LOOPING_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return result;
    }

    alSourcePlay(als);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << SOURCE_PLAY_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return result;
    }
    return result;
}

ALenum Source::stop()
{
    ALenum result = alGetError();

    if((result = c->select()) != AL_NO_ERROR) return result;

    alSourceStop(als);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << SOURCE_STOP_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return result;
    }
    return result;
}

ALenum Source::attach(Buffer * buffer)
{
    ALenum result = alGetError();

    if((result = c->select()) != AL_NO_ERROR) return result;

    alSourcei(als, AL_BUFFER, buffer->get());
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << BUFFER_ATTACH_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return result;
    }
    return result;
}

Buffer::Buffer(Context * context)
    :c(context)
{
    ALenum result = alGetError();

    if(c->select() != AL_NO_ERROR) return;

    alGenBuffers(1, &alb);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << BUFFER_GEN_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return;
    }
}

Buffer::~Buffer()
{
    ALenum result = alGetError();

    if(c->select() != AL_NO_ERROR) return;

    alDeleteBuffers(1, &alb);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << BUFFER_DELETE_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return;
    }
}

ALenum Buffer::set(ALvoid * signal, ALsizei size)
{
    ALenum result = alGetError();

    if((result = c->select()) != AL_NO_ERROR) return result;

    alBufferData(alb, FORMAT, signal, size, SAMPLE_RATE);
    if((result = alGetError()) != AL_NO_ERROR)
    {
        std::cout << BUFFER_DATA_FAILURE_MSG << ": " << alErrStr(result) << std::endl;
        return result;
    }
    return result;
}