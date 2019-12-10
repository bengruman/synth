#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

#define DEVICE_INIT_FAILURE_MSG             "Failed to initialize audio device"
#define CONTEXT_INIT_FAILURE_MSG            "Failed to initialize AL context"
#define CONTEXT_MAKE_CURRENT_FAILURE_MSG    "Failed to make context current"
#define CONTEXT_GET_DEVICE_FAILURE_MSG      "Failed to get context's device"
#define BUFFER_GEN_FAILURE_MSG              "Failed to create buffer"
#define BUFFER_DELETE_FAILURE_MSG           "Failed to delete buffer"
#define BUFFER_DATA_FAILURE_MSG             "Failed to write data to buffer"
#define SOURCE_GEN_FAILURE_MSG              "Failed to create virtual source"
#define SOURCE_DELETE_FAILURE_MSG           "Failed to delete virtual source"
#define BUFFER_ATTACH_FAILURE_MSG           "Failed to attach buffer to source"
#define SOURCE_SET_LOOPING_FAILURE_MSG      "Failed to set source looping property"
#define SOURCE_PLAY_FAILURE_MSG             "Failed to start source playback"
#define SOURCE_STOP_FAILURE_MSG             "Failed to stop source playback"
#define KEYBOARD_ACCESS_FAILURE_MSG         "Failed to access keyboard"

char * alErrStr(ALenum error);
char * alcErrStr(ALenum error);
