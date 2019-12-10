#include "synth_err.h"

char * alErrStr(ALenum error)
{
    static char str[24];
    switch(error)
    {
        case AL_NO_ERROR:
            sprintf(str, "AL_NO_ERROR");
            break;
        case AL_INVALID_NAME:
            sprintf(str, "AL_INVALID_NAME");
            break;
        case AL_INVALID_ENUM:
            sprintf(str, "AL_INVALID_ENUM");
            break;
        case AL_INVALID_VALUE:
            sprintf(str, "AL_INVALID_VALUE");
            break;
        case AL_INVALID_OPERATION:
            sprintf(str, "AL_INVALID_OPERATION");
            break;
        case AL_OUT_OF_MEMORY:
            sprintf(str, "AL_OUT_OF_MEMORY");
            break;
        default:
            sprintf(str, "%d", error);
            break;
    }
    return str;
}

char * alcErrStr(ALenum error)
{
    static char str[24];
    switch(error)
    {
        case ALC_NO_ERROR:
            sprintf(str, "ALC_NO_ERROR");
            break;
        case ALC_INVALID_DEVICE:
            sprintf(str, "ALC_INVALID_DEVICE");
            break;
        case ALC_INVALID_CONTEXT:
            sprintf(str, "ALC_INVALID_CONTEXT");
            break;
        case ALC_INVALID_ENUM:
            sprintf(str, "ALC_INVALID_ENUM");
            break;
        case ALC_INVALID_VALUE:
            sprintf(str, "ALC_INVALID_VALUE");
            break;
        case ALC_OUT_OF_MEMORY:
            sprintf(str, "ALC_OUT_OF_MEMORY");
            break;
        default:
            sprintf(str, "%d", error);
            break;
    }
    return str;
}
